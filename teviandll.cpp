#include "teviandll.h"

TevianDLL::TevianDLL()
{
    ///Создание указателя на запрос распознавания
    detectReq = new DetectRequest();

    ///Создание указателя на запрос авторизации
    loginReq = new LoginRequest();

    ///Подключение к сигналам запроса login об успешном выполнении и ошибке запроса
    connect(loginReq, &LoginRequest::requestSuccess, this, &TevianDLL::loginSuccess);
    connect(loginReq, &LoginRequest::requestError, this, &TevianDLL::requestError);

    ///Подключение к сигналам запроса detect об успешном выполнении и ошибке запроса
    connect(detectReq, &DetectRequest::rawJSON,        this, &TevianDLL::detectSuccess);
    connect(detectReq, &DetectRequest::requestError,   this, &TevianDLL::requestError);
}

void TevianDLL::doLogin(QString url, QString email, QString password)
{
    ///Создание списка параметров
    QStringList requestParameters;

    ///Заполнение списка данными об имени пользователя и пароле
    requestParameters.append(email);
    requestParameters.append(password);

    ///Выполнение запроса
    loginReq->doRequest(url, requestParameters);
}

void TevianDLL::detect(QString url, QString imagePath, QString token)
{
    ///Создание списка параметров
    QStringList requestParameters;

    ///Заполнение списка токеном и пути к файлу с изображением
    requestParameters.append(token);
    requestParameters.append(imagePath);

    ///Выполнение запроса
    detectReq->doRequest(url, requestParameters);
}

TevianDLL::~TevianDLL()
{
    delete loginReq;
    delete detectReq;
}
