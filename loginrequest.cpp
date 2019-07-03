#include "teviandll.h"

LoginRequest::LoginRequest()
{
    ///Заполение словаря с кодами ответов
    errorMap.insert(400, "error detected in request");
    errorMap.insert(401, "invalid email or password provided");

    ///Создание указателя на экземпеляр менеджера http-запросов
    manager = new QNetworkAccessManager(this);
}

LoginRequest::~LoginRequest()
{
    delete manager;
}

void LoginRequest::doRequest(QString url, QStringList requestParameters)
{
    ///Создание запроса
    QUrl qurl(url);
    QNetworkRequest request(qurl);

    ///Заполнение заголовков
    request.setRawHeader("Content-Type", "application/json");

    ///Создание строки с полезными данными
    QString payload = "{\"email\":\"%email%\",\"password\":\"%password%\"}";

    payload = payload.replace("%email%",    requestParameters[EMAIL]);
    payload = payload.replace("%password%", requestParameters[PASSWORD]);

    ///Выполнение post запроса
    reply = manager->post(request,payload.toUtf8());

    ///Подключение сигналов о приходе ответа или истечении таймера ожидания
    connect(reply, &QNetworkReply::finished,this, &LoginRequest::processResponse);
    connect(&responseTimer, &QTimer::timeout, this, &Request::responseTimeoutExpired);

    ///Запуск таймера
    responseTimer.start(3000);
}

void LoginRequest::processResponse()
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
    ///В случае "хорошего" ответа - передать сигнал с сырыми json данными и токеном
    rawJSON(replyBody);
    requestSuccess(getToken(replyBody));
}

QString LoginRequest::getToken(QByteArray replyBody)
{
    QJsonParseError parseError;

    QJsonDocument doc = QJsonDocument::fromJson(replyBody, &parseError);

    QMap<QString, QVariant> data = doc.toVariant().toMap()["data"].toMap();
    return data["access_token"].toString();
}
