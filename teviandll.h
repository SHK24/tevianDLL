#ifndef TEVIANDLL_H
#define TEVIANDLL_H

#include <QObject>
#include "teviandll_global.h"

#define EMAIL 0
#define PASSWORD 1

#define DB_ID 0

#define TOKEN 0

#define IMAGE_PATH 1

#include <QUrl>
#include <QFile>
#include <QObject>
#include <QVariant>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonParseError>
#include <QNetworkAccessManager>

///структура для хранения данных о распознанных лицах
struct FaceBox
{
    int x,y;
    int width, height;
};


///Базовый класс "Запрос", содержит методы для выполнени запроса и обработки ответа
class Request : public QObject
{
    Q_OBJECT

protected:
    ///Менеджер http запросов
    QNetworkAccessManager * manager;

    ///Объект для хранения ответа на запрос
    QNetworkReply * reply;


    ///Словарь расшифровки кодов ответов
    QMap<int, QString> errorMap;

    ///Метод определения кода ответа
    int getResponseStatus(QByteArray replyBody);

public:
    ///Конструктор
    Request();

    ///Виртуальный метод для выполнения запроса
    virtual void doRequest(QString url, QStringList requestParameters);

    ///Вирутальный метод для обработки ответа
    virtual void processResponse();

    ///Деструктор
    ~Request();
signals:
    ///Сигнал об ошибке запроса
    void requestError(QString errorMessage);

    ///Сигнал статуса ответа
    void statusCode(int code);

    /// Сигнал передачи "сырого" ответа в формате JSON
    void rawJSON(QByteArray json);
};

///Класс запроса на обработку изображения, наследован от Request
class DetectRequest : public Request
{
    Q_OBJECT

public:
    ///Конструктор
    DetectRequest();
    ~DetectRequest();

    ///Метод выполнения запроса: параметры - url-адрес, набор параметров - путь к изображению
    void doRequest(QString url, QStringList requestParameters);

    ///Метод обработки ответа
    void processResponse();
signals:
    ///Сигнал об ошибке открытия файла с изображением
    void cantOpenFile();
};

///Класс запроса авторизации, наследован от Request
class LoginRequest : public Request
{
    Q_OBJECT

    ///Переопределенный словарь ошибок
    QMap<int, QString> errorMap;
public:
    ///Конструктор
    LoginRequest();
    ~LoginRequest();

    ///Метод выполнения запроса: параметры - url-адрес, набор параметров - строка "логин:пароль"
    void doRequest(QString url, QStringList requestParameters);

    ///Метод обработки ответа
    void processResponse();
};

extern "C++" class TEVIANDLLSHARED_EXPORT TevianDLL : public QObject
{
    Q_OBJECT

    ///Указатель на экземпляр запроса Login
    LoginRequest * loginReq;

    ///Указатель на экземпляр запроса Detect
    DetectRequest * detectReq;

signals:

    ///Сигнал об успешной авторизации
    void loginSuccess(QByteArray rawJSON);

    ///Сигнал об успешном распознавании
    void detectSuccess(QByteArray rawJSON);

    ///Сигнал об ошибке запроса
    void requestError(QString errorMessage);
public:
    ///Конструктор
    TevianDLL();

    ///Метод для выполнения авторизации, параметры: url-адрес для отправки запроса, email - имя пользователья, password - пароль
    void doLogin(QString url, QString email, QString password);

    ///Метод для выполнения распознавания, параметры: imagePath - путь к файлу, token - JWT токен
    void detect(QString url, QString imagePath, QString token);

    ///Деструктор
    ~TevianDLL();
};

#endif // TEVIANDLL_H
