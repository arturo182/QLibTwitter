/************************************************************************
 * QLibTwitter                                                          *
 * Copyright (C) 2010 arturo182 <arturo182@tlen.pl>                     *
 *                                                                      *
 * This library is free software: you can redistribute it and/or modify *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation; version 3 only.                        *
 *                                                                      *
 * This library is distributed in the hope that it will be useful,      *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the         *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with this library. If not, see <http://www.gnu.org/licenses/>. *
 ************************************************************************/

#include "QLibTwitterCore.h"
#include "QLibTwitterParser.h"

#include <QtCore/QDebug>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QAuthenticator>

using namespace QLibTwitter;

Core::Core(QString consumerKey, QString consumerSecret, QString tokenKey, QString tokenSecret): QObject(0)
{
  m_netMgr = new QNetworkAccessManager();
  m_consumer = new QLibOA::Consumer(consumerKey, consumerSecret);

  if(!tokenKey.isNull() && !tokenSecret.isNull()) {
    m_token = new QLibOA::Token(tokenKey, tokenSecret);
  } else {
    m_token = NULL;
  }

  connect(m_netMgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotReplyFinished(QNetworkReply*)));
}

void Core::slotRequestToken()
{
  slotMakeRequest("https://api.twitter.com/oauth/request_token", QLibOA::POST);
}

void Core::slotAccessToken(QString verifier)
{
  QLibOA::ParamMap params;
  if(!verifier.isNull()) {
    params.insert("oauth_verifier", verifier);
  }

  slotMakeRequest("https://api.twitter.com/oauth/access_token", QLibOA::POST, params);
}

void Core::getFriendsTimeline(QLibOA::ParamMap params)
{
  QString url = getHost() + "statuses/friends_timeline.xml";
  slotMakeRequest(url, QLibOA::GET, params);
}

void Core::getPublicTimeline(QLibOA::ParamMap params)
{
  QString url = getHost() + "statuses/public_timeline.xml";
  slotMakeRequest(url, QLibOA::GET, params);
}

void Core::getUserTimeline(QString screenName, QLibOA::ParamMap params)
{
  if(!params.contains("screen_name")) {
    params.insert("screen_name", screenName);
  }

  QString url = getHost() + "statuses/user_timeline.xml";
  slotMakeRequest(url, QLibOA::GET, params);
}

void Core::getUserTimeline(int id, QLibOA::ParamMap params)
{
  if(!params.contains("user_id")) {
    params.insert("user_id", QString::number(id));
  }

  QString url = getHost() + "statuses/user_timeline.xml";
  slotMakeRequest(url, QLibOA::GET, params);
}

void Core::getHomeTimeline(QLibOA::ParamMap params)
{
  QString url = getHost() + "statuses/home_timeline.xml";
  slotMakeRequest(url, QLibOA::GET, params);
}

void Core::getMentions(QLibOA::ParamMap params)
{
  QString url = getHost() + "statuses/mentions.xml";
  slotMakeRequest(url, QLibOA::GET, params);
}

void Core::getFavourites(QLibOA::ParamMap params)
{
  QString url = getHost() + "favorites.xml";
  slotMakeRequest(url, QLibOA::GET, params);
}

void Core::getUserFavourites(QString screenName, QLibOA::ParamMap params)
{
  QString url = getHost() + "favorites/" + screenName + ".xml";
  slotMakeRequest(url, QLibOA::GET, params);
}

void Core::getUserFavourites(int id, QLibOA::ParamMap params)
{
  getUserFavourites(QString::number(id), params);
}

void Core::getRateLimit()
{
  QString url = getHost() + "account/rate_limit_status.xml";
  slotMakeRequest(url, QLibOA::GET);
}

void Core::sendStatusUpdate(QString status, QLibOA::ParamMap params)
{
  if(!params.contains("status")) {
    params.insert("status", status);
  }

  QString url = getHost() + "statuses/update.xml";

  slotMakeRequest(url, QLibOA::POST, params);
}

void Core::search(QString query, QLibOA::ParamMap params)
{
  if(!params.contains("q")) {
    params.insert("q", query);
  }

  QNetworkRequest req;
  QLibOA::Request *oReq = new QLibOA::Request(QLibOA::GET, "http://search.twitter.com/search.rss", params);

  req.setUrl(oReq->toUrl());
  m_netMgr->get(req);

  delete oReq;
}

void Core::slotMakeRequest(QString url, QLibOA::HttpMethod method, QLibOA::ParamMap params)
{
  QNetworkRequest req;

  QLibOA::Request *oReq = QLibOA::Request::fromConsumerAndToken(m_consumer, m_token, method, url, params);
  oReq->sign(QLibOA::HMAC_SHA1, m_consumer, m_token);

  switch(method) {
    case QLibOA::GET:
    {
      req.setUrl(oReq->toUrl());
      qDebug() << oReq->toUrl() << "\n";

      req.setRawHeader("Authorization", oReq->toHeader().toAscii());
      m_netMgr->get(req);
    }
    break;

    case QLibOA::POST:
    {
      req.setUrl(oReq->getNormalizedUrl());
      m_netMgr->post(req, oReq->toPostdata().toAscii());
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
        RespTimeline *resp = Parser::FriendsTimeline(data);
        emit signalResponseReceived(resp);
      } else if(reply->url().toString().indexOf("statuses/update") > -1) {
        RespStatusUpdate *resp = Parser::StatusUpdate(data);
        emit signalResponseReceived(resp);
      } else if(reply->url().toString().indexOf("statuses/public_timeline") > -1) {
        RespTimeline *resp = Parser::PublicTimeline(data);
        emit signalResponseReceived(resp);
      } else if(reply->url().toString().indexOf("statuses/user_timeline") > -1) {
        RespTimeline *resp = Parser::UserTimeline(data);
        emit signalResponseReceived(resp);
      } else if(reply->url().toString().indexOf("statuses/home_timeline") > -1) {
        RespTimeline *resp = Parser::HomeTimeline(data);
        emit signalResponseReceived(resp);
      } else if(reply->url().toString().indexOf("statuses/mentions") > -1) {
        RespTimeline *resp = Parser::Mentions(data);
        emit signalResponseReceived(resp);
      } else if(reply->url().toString().indexOf("account/rate_limit_status") > -1) {
        RespRateLimit *resp = Parser::RateLimit(data);
        emit signalResponseReceived(resp);
      } else if(reply->url().toString().indexOf("search") > -1) {
        qDebug() << data;
        //RespRateLimit *resp = Parser::RateLimit(data);
        //emit signalResponseReceived(resp);
      } else if(reply->url().toString().indexOf("favorites") > -1) {
        RespTimeline *resp = Parser::Favourites(data);
        emit signalResponseReceived(resp);        
      }
    }
  }

  reply->deleteLater();
}
