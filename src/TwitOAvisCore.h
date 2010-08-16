/**
  * TwitOAvis
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#ifndef TWITOAVISCORE_H
#define TWITOAVISCORE_H

#include "OAvis/OAvisRequest.h"
#include "TwitOAvisCommon.h"

#include <QtNetwork/QNetworkAccessManager>

class QNetworkReply;
class QAuthenticator;

namespace TwitOAvis
{
  class Core: public QObject
  {
    Q_OBJECT

    public:
      explicit Core(QString consumerKey, QString consumerSecret, QString tokenKey = QString::null, QString tokenSecret = QString::null);

      QString getHost() { return "https://api.twitter.com/1/"; }
      QString getFormat();

      QString getAuthorizeUrl(QString token) { return "https://api.twitter.com/oauth/authorize?oauth_token=" + token; }

      void setToken(OAvis::Token *token) { if(m_token) { delete m_token; } m_token = token; }

    signals:
      void signalResponseReceived(TwitOAvis::Response *resp);
      void signalRequestToken(OAvis::Token *token);
      void signalAccessToken(OAvis::Token *token);

    public slots:
      void slotRequestToken();
      void slotAccessToken(QString verifier = QString::null);
      void slotMakeRequest(QString url, OAvis::HttpMethod method = OAvis::GET, OAvis::ParamMap params = OAvis::ParamMap());

    private slots:
      void slotMakeRequestFull(QString url, OAvis::HttpMethod method = OAvis::GET, OAvis::ParamMap params = OAvis::ParamMap());
      void slotReplyFinished(QNetworkReply *reply);

    private:
      DataFormat m_format;
      OAvis::Consumer *m_consumer;
      OAvis::Token *m_token;
      QNetworkAccessManager *m_netMgr;
  };
}

#endif // TWITOAVISCORE_H
