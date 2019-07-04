#include "teviandll.h"

DetectRequest::DetectRequest()
{
    ///Создание указателя на экземпеляр менеджера http-запросов
    manager = new QNetworkAccessManager(this);
}

DetectRequest::~DetectRequest()
{
    delete manager;
}

void DetectRequest::doRequest(QString url, QStringList requestParameters)
{
    ///Создание запроса
    QUrl qurl(url);
    QNetworkRequest request(qurl);

    ///Формирование поля Bearer: Bearer+Token
    QString bearer = "Bearer " + requestParameters[TOKEN];

    ///Заполнение заголовков
    request.setRawHeader("Content-Type", "image/jpeg");
    request.setRawHeader("Authorization", bearer.toUtf8());


    ///Создание экземпляра для чтения файла изображения
    QFile imageFile(requestParameters[IMAGE_PATH]);

    ///Проверка на возможность чтения файла
    if(!imageFile.open(QIODevice::ReadOnly))
    {
        ///Передача сигнала о неуспешном чтении файла
        cantOpenFile();
        return;
    }

    ///Чтение содержимого файла
    QByteArray imageData = imageFile.readAll();

    ///Заполнение поля заголовка с длиной передаваемых данных
    request.setRawHeader("Content-Length", QString::number(imageFile.size()).toUtf8());

    ///Выполнение post запроса
    reply = manager->post(request, imageData);

    ///Подключение сигналов о приходе ответа или истечении таймера ожидания
    connect(reply, &QNetworkReply::finished,this, &DetectRequest::processResponse);

    ///Запуск таймера
    //responseTimer.start(3000);
}


void DetectRequest::processResponse()
{
    ///Получение тела ответа от sender
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    ///Чтение содержимого ответа
    QByteArray replyBody = reply->readAll();

    ///Определение кода ответа
    int status_code = getResponseStatus(replyBody);

    ///Передача сигнала о коде ответа
    statusCode(status_code);

    ///Если код "плохой" - выдать сигнал и остановить выполнение
    if(status_code != 200)
    {
        requestError(errorMap.value(status_code));
        return;
    }

    ///В случае "хорошего" ответа - передать сигнал с сырыми json данными
    rawJSON(replyBody);
}
