/**
  * TwitOAvis
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#include "TwitOAvis.h"

#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

TwitOAvis::TwitOAvis(QString consumerKey, QString consumerSecret, QString tokenKey, QString tokenSecret): QObject(0)
{
  m_netMgr = new QNetworkAccessManager();
  m_consumer = new OAvis::Consumer(consumerKey, consumerSecret);

  if(!tokenKey.isNull() && !tokenSecret.isNull()) {
    m_token = new OAvis::Token(tokenKey, tokenSecret);
  } else {
    m_token = NULL;
  }

  connect(m_netMgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotReplyFinished(QNetworkReply*)));
}

void TwitOAvis::slotMakeRequest(QString url, OAvis::HttpMethod method, QString params)
{
  QNetworkReply *reply = 0;
  QNetworkRequest req;

  req.setUrl(url);

  switch(method) {
    case OAvis::GET:
      reply = m_netMgr->get(req);
    break;

    case OAvis::POST:
      reply = m_netMgr->post(req, params.toUtf8());
    break;
  }
}
