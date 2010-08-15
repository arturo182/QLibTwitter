/**
  * TwitOAvis
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#include "TwitOAvis.h"

#include <QtCore/QDebug>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QAuthenticator>

TwitOAvis::TwitOAvis(QString consumerKey, QString consumerSecret, QString tokenKey, QString tokenSecret): QObject(0)
{
  m_format = XML;
  m_netMgr = new QNetworkAccessManager();
  m_consumer = new OAvis::Consumer(consumerKey, consumerSecret);

  if(!tokenKey.isNull() && !tokenSecret.isNull()) {
    m_token = new OAvis::Token(tokenKey, tokenSecret);
  } else {
    m_token = NULL;
  }

  connect(m_netMgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotReplyFinished(QNetworkReply*)));
}

QString TwitOAvis::getFormat()
{
  switch(m_format) {
    case JSON:
      return "json";
    break;

    case XML:
      return "xml";
    break;
  }

  return "";
}

void TwitOAvis::slotRequestToken()
{
  slotMakeRequest("https://api.twitter.com/oauth/request_token", OAvis::POST);
}

void TwitOAvis::slotAccessToken(QString verifier)
{
  OAvis::ParamMap params;
  if(!verifier.isNull()) {
    params.insert("oauth_verifier", verifier);
  }

  slotMakeRequest("https://api.twitter.com/oauth/access_token", OAvis::POST, params);
}

void TwitOAvis::slotMakeRequest(QString url, OAvis::HttpMethod method, OAvis::ParamMap params)
{
  QNetworkReply *reply = 0;
  QNetworkRequest req;

  OAvis::Request *oReq = OAvis::Request::fromConsumerAndToken(m_consumer, m_token, method, url, params);
  oReq->sign(OAvis::HMAC_SHA1, m_consumer, m_token);

  switch(method) {
    case OAvis::GET:
      //qDebug() << "GET requesting " << oReq->getNormalizedUrl() << "with header" << oReq->toHeader();
      req.setRawHeader("Authorization", oReq->toHeader().toAscii());

      req.setUrl(oReq->getNormalizedUrl());
      reply = m_netMgr->get(req);
    break;

    case OAvis::POST:
      //qDebug() << "POST requesting" << oReq->getNormalizedUrl() << " with data " << oReq->toPostdata();
      req.setUrl(oReq->getNormalizedUrl());
      reply = m_netMgr->post(req, oReq->toPostdata().toAscii());
    break;
  }

  delete oReq;
}

void TwitOAvis::slotReplyFinished(QNetworkReply *reply)
{
  if(reply->error() != QNetworkReply::NoError) {
    qDebug() << reply->errorString();
  } else {
    if(reply->bytesAvailable() > 0) {
      QByteArray data = reply->readAll();
      qDebug() << data;

      if(reply->url().toString().indexOf("request_token") > -1) {
        OAvis::Token *token = OAvis::Token::fromString(data);
        emit signalRequestToken(token);
      } else if(reply->url().toString().indexOf("access_token") > -1) {
        OAvis::Token *token = OAvis::Token::fromString(data);
        emit signalAccessToken(token);
      }
    }
  }

  reply->deleteLater();
}
