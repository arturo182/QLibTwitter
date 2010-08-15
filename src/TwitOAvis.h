/**
  * TwitOAvis
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#ifndef TWITOAVIS_H
#define TWITOAVIS_H

#include "OAvis/OAvisRequest.h"

#include <QtNetwork/QNetworkAccessManager>

class QNetworkReply;
class QAuthenticator;

class TwitOAvis: public QObject
{
  Q_OBJECT

  enum DataFormat
  {
    JSON = 0,
    XML = 1
  };

  public:
    explicit TwitOAvis(QString consumerKey, QString consumerSecret, QString tokenKey = QString::null, QString tokenSecret = QString::null);

    QString getHost() { return "https://api.twitter.com/1/"; }
    QString getFormat();

    QString getAuthorizeUrl(QString token) { return "https://api.twitter.com/oauth/authorize?oauth_token=" + token; }

    void setToken(OAvis::Token *token) { if(m_token) { delete m_token; } m_token = token; }

  signals:
    void signalReponseReceived();
    void signalRequestToken(OAvis::Token *token);
    void signalAccessToken(OAvis::Token *token);

  public slots:
    void slotRequestToken();
    void slotAccessToken(QString verifier = QString::null);

  //private slots:
    void slotMakeRequest(QString url, OAvis::HttpMethod method = OAvis::GET, OAvis::ParamMap params = OAvis::ParamMap());
    void slotReplyFinished(QNetworkReply *reply);

  private:
    DataFormat m_format;
    OAvis::Consumer *m_consumer;
    OAvis::Token *m_token;
    QNetworkAccessManager *m_netMgr;

};

#endif // TWITOAVIS_H
