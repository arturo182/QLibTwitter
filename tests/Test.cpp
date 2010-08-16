/**
  * QLibTwitter
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#include "Test.h"

Test::Test(QObject *parent): QObject(parent)
{
  m_lib = new QLibTwitter::Core("vP69u6PGSakKTIoE2ApvVw", "g2PjaAttF0prUfmMTSlzVe9Dr7LBqCGcJXlWwhlwA", "15699469-7Vcdc62ym4blRrHgCRjKCYaDBYoVDhAIlubUPmg", "NM0X0rXn4imPw0hm4MoQGe5tcYIZBxqbyfXSxykvNg");

  connect(m_lib, SIGNAL(signalRequestToken(QLibOA::Token*)), this, SLOT(slotGotRequestToken(QLibOA::Token*)));
  connect(m_lib, SIGNAL(signalAccessToken(QLibOA::Token*)), this, SLOT(slotGotAccessToken(QLibOA::Token*)));
  connect(m_lib, SIGNAL(signalResponseReceived(QLibTwitter::Response*)), this, SLOT(slotGotResponse(QLibTwitter::Response*)));

  QLibOA::ParamMap params;

  //m_lib->slotRequestToken();

  params.insert("count", "200");
  m_lib->slotMakeRequest("statuses/friends_timeline", QLibOA::GET, params);

  //params.insert("status", "Hello world 3!");
  //m_lib->slotMakeRequest("statuses/update", QLibOA::POST, params);
}

void Test::slotGotRequestToken(QLibOA::Token *token)
{
  m_lib->setToken(token);

  QTextStream in(stdin);
  QString pin;
  in >> pin;

  m_lib->slotAccessToken(pin);
}

void Test::slotGotAccessToken(QLibOA::Token *token)
{
  m_lib->setToken(token);
  //token->debug();
  //m_lib->slotMakeRequest("statuses/friends_timeline");
}

void Test::slotGotResponse(QLibTwitter::Response *resp)
{
  switch(resp->getType()) {
    case QLibTwitter::FRIENDS_TIMELINE:
    {
      QLibTwitter::RespFriendsTimeline *r = static_cast<QLibTwitter::RespFriendsTimeline*>(resp);

      for(int i = 0; i < r->list.count(); i++) {
        qDebug() << r->list.at(i)->user.screenName << "wrote" << r->list.at(i)->text << "at" << r->list.at(i)->createdAt.toString("dd.MM.yyyy hh:mm:ss");
      }

      delete r;
    }
    break;

    case QLibTwitter::STATUS_UPDATE:
    {
      QLibTwitter::RespStatusUpdate *r = static_cast<QLibTwitter::RespStatusUpdate*>(resp);

      qDebug() << *r->status;

      delete r;
    }
    break;

    case QLibTwitter::PUBLIC_TIMELINE:
    {
      QLibTwitter::RespFriendsTimeline *r = static_cast<QLibTwitter::RespFriendsTimeline*>(resp);

      qDebug() << r->list.count();

      delete r;
    }
    break;
  }
}
