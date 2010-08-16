/**
  * QLibTwitter
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#ifndef TWITOAVISCORE_H
#define TWITOAVISCORE_H

#include "QLibOA/QLibOARequest.h"
#include "QLibTwitterCommon.h"

#include <QtNetwork/QNetworkAccessManager>

class QNetworkReply;
class QAuthenticator;

namespace QLibTwitter
{
  class Core: public QObject
  {
    Q_OBJECT

    public:
      explicit Core(QString consumerKey, QString consumerSecret, QString tokenKey = QString::null, QString tokenSecret = QString::null);

      QString getHost() { return "https://api.twitter.com/1/"; }
      QString getFormat();

      QString getAuthorizeUrl(QString token) { return "https://api.twitter.com/oauth/authorize?oauth_token=" + token; }

      void setToken(QLibOA::Token *token) { if(m_token) { delete m_token; } m_token = token; }

      void getFriendsTimeline(QLibOA::ParamMap params = QLibOA::ParamMap());
      void getPublicTimeline(QLibOA::ParamMap params = QLibOA::ParamMap());
      void getUserTimeline(QString screenName, QLibOA::ParamMap params = QLibOA::ParamMap());
      void getUserTimeline(int id, QLibOA::ParamMap params = QLibOA::ParamMap());
      void getHomeTimeline(QLibOA::ParamMap params = QLibOA::ParamMap());
      void getMentions(QLibOA::ParamMap params = QLibOA::ParamMap());

      void getRateLimit();

      void sendStatusUpdate(QString status, QLibOA::ParamMap params = QLibOA::ParamMap());

    signals:
      void signalResponseReceived(QLibTwitter::Response *resp);
      void signalRequestToken(QLibOA::Token *token);
      void signalAccessToken(QLibOA::Token *token);

    public slots:
      void slotRequestToken();
      void slotAccessToken(QString verifier = QString::null);

    private slots:
      void slotMakeRequest(QString url, QLibOA::HttpMethod method = QLibOA::GET, QLibOA::ParamMap params = QLibOA::ParamMap());
      void slotReplyFinished(QNetworkReply *reply);

    private:
      DataFormat m_format;
      QLibOA::Consumer *m_consumer;
      QLibOA::Token *m_token;
      QNetworkAccessManager *m_netMgr;
  };
}

#endif // TWITOAVISCORE_H
