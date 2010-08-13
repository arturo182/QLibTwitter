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

  signals:
    void signalReponseReceived();

  public slots:

  private slots:
    void slotMakeRequest(QString url, OAvis::HttpMethod method = OAvis::GET, QString params = QString::null);
    void slotReplyFinished(QNetworkReply *reply);

  private:
    OAvis::Consumer *m_consumer;
    OAvis::Token *m_token;
    QNetworkAccessManager *m_netMgr;

};

#endif // TWITOAVIS_H
