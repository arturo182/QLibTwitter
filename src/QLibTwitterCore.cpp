/**
  * QLibTwitter
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#include "QLibTwitterCore.h"
#include "QLibTwitterParser.h"

#include <QtCore/QDebug>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QAuthenticator>

using namespace QLibTwitter;

Core::Core(QString consumerKey, QString consumerSecret, QString tokenKey, QString tokenSecret): QObject(0)
{
  m_format = XML;
  m_netMgr = new QNetworkAccessManager();
  m_consumer = new QLibOA::Consumer(consumerKey, consumerSecret);

  if(!tokenKey.isNull() && !tokenSecret.isNull()) {
    m_token = new QLibOA::Token(tokenKey, tokenSecret);
  } else {
    m_token = NULL;
  }

  connect(m_netMgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotReplyFinished(QNetworkReply*)));
}

QString Core::getFormat()
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

void Core::slotRequestToken()
{
  slotMakeRequestFull("https://api.twitter.com/oauth/request_token", QLibOA::POST);
}

void Core::slotAccessToken(QString verifier)
{
  QLibOA::ParamMap params;
  if(!verifier.isNull()) {
    params.insert("oauth_verifier", verifier);
  }

  slotMakeRequestFull("https://api.twitter.com/oauth/access_token", QLibOA::POST, params);
}

void Core::slotMakeRequest(QString url, QLibOA::HttpMethod method, QLibOA::ParamMap params)
{
  url.prepend(getHost());
  url.append(".");
  url.append(getFormat());

  slotMakeRequestFull(url, method, params);
}

void Core::slotMakeRequestFull(QString url, QLibOA::HttpMethod method, QLibOA::ParamMap params)
{
  QNetworkReply *reply = 0;
  QNetworkRequest req;

  QLibOA::Request *oReq = QLibOA::Request::fromConsumerAndToken(m_consumer, m_token, method, url, params);
  oReq->sign(QLibOA::HMAC_SHA1, m_consumer, m_token);

  req.setUrl(oReq->getNormalizedUrl());

  switch(method) {
    case QLibOA::GET:
    {
      req.setRawHeader("Authorization", oReq->toHeader().toAscii());
      reply = m_netMgr->get(req);
    }
    break;

    case QLibOA::POST:
    {
      reply = m_netMgr->post(req, oReq->toPostdata().toAscii());
    }
    break;
  }

  delete oReq;
}

void Core::slotReplyFinished(QNetworkReply *reply)
{
  if(reply->error() != QNetworkReply::NoError) {
    QByteArray data = reply->readAll();

    qDebug() << reply->errorString();
    qDebug() << "Twitter error:" << Parser::getError(data);
  } else {
    if(reply->bytesAvailable() > 0) {
      QByteArray data = reply->readAll();

      if(reply->url().toString().indexOf("request_token") > -1) {
        QLibOA::Token *token = QLibOA::Token::fromString(data);
        emit signalRequestToken(token);
      } else if(reply->url().toString().indexOf("access_token") > -1) {
        QLibOA::Token *token = QLibOA::Token::fromString(data);
        emit signalAccessToken(token);
      } else if(reply->url().toString().indexOf("statuses/friends_timeline") > -1) {
        RespFriendsTimeline *resp = Parser::FriendsTimeline(data);
        emit signalResponseReceived(resp);
      } else if(reply->url().toString().indexOf("statuses/update") > -1) {
        RespStatusUpdate *resp = Parser::StatusUpdate(data);
        emit signalResponseReceived(resp);
      } else if(reply->url().toString().indexOf("statuses/public_timeline") > -1) {
        RespPublicTimeline *resp = Parser::PublicTimeline(data);
        emit signalResponseReceived(resp);
      }
    }
  }

  reply->deleteLater();
}
