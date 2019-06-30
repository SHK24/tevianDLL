#include "teviandll.h"

TevianDLL::TevianDLL()
{
    detectReq = new DetectRequest();
    loginReq = new LoginRequest();

    connect(loginReq, &LoginRequest::requestSuccess, this, &TevianDLL::loginSuccess);
    connect(loginReq, &LoginRequest::requestError, this, &TevianDLL::requestError);

    connect(detectReq, &DetectRequest::rawJSON,        this, &TevianDLL::detectSuccess);
    connect(detectReq, &DetectRequest::requestError,   this, &TevianDLL::requestError);
}

void TevianDLL::doLogin(QString url, QString email, QString password)
{
    QStringList requestParameters;

    requestParameters.append(email);
    requestParameters.append(password);

    loginReq->doRequest(url, requestParameters);
}

void TevianDLL::detect(QString url, QString imagePath, QString token)
{
    QStringList requestParameters;

    requestParameters.append(token);
    requestParameters.append(imagePath);

    detectReq->doRequest(url, requestParameters);
}

TevianDLL::~TevianDLL()
{
    delete loginReq;
    delete detectReq;
}
