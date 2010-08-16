/**
  * TwitOAvis
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#include "Test.h"

Test::Test(QObject *parent): QObject(parent)
{
  m_lib = new TwitOAvis::Core("vP69u6PGSakKTIoE2ApvVw", "g2PjaAttF0prUfmMTSlzVe9Dr7LBqCGcJXlWwhlwA", "15699469-7Vcdc62ym4blRrHgCRjKCYaDBYoVDhAIlubUPmg", "NM0X0rXn4imPw0hm4MoQGe5tcYIZBxqbyfXSxykvNg");

  connect(m_lib, SIGNAL(signalRequestToken(OAvis::Token*)), this, SLOT(slotGotRequestToken(OAvis::Token*)));
  connect(m_lib, SIGNAL(signalAccessToken(OAvis::Token*)), this, SLOT(slotGotAccessToken(OAvis::Token*)));
  connect(m_lib, SIGNAL(signalResponseReceived(TwitOAvis::Response*)), this, SLOT(slotGotResponse(TwitOAvis::Response*)));

  OAvis::ParamMap params;

  //m_lib->slotRequestToken();

  params.insert("count", "200");
  m_lib->slotMakeRequest("statuses/friends_timeline", OAvis::GET, params);

  //params.insert("status", "Hello world 3!");
  //m_lib->slotMakeRequest("statuses/update", OAvis::POST, params);
}

void Test::slotGotRequestToken(OAvis::Token *token)
{
  m_lib->setToken(token);

  QTextStream in(stdin);
  QString pin;
  in >> pin;

  m_lib->slotAccessToken(pin);
}

void Test::slotGotAccessToken(OAvis::Token *token)
{
  m_lib->setToken(token);
  //token->debug();
  //m_lib->slotMakeRequest("statuses/friends_timeline");
}

void Test::slotGotResponse(TwitOAvis::Response *resp)
{
  switch(resp->getType()) {
    case TwitOAvis::FRIENDS_TIMELINE:
    {
      TwitOAvis::RespFriendsTimeline *r = static_cast<TwitOAvis::RespFriendsTimeline*>(resp);

      for(int i = 0; i < r->list.count(); i++) {
        qDebug() << r->list.at(i)->user.screenName << "wrote" << r->list.at(i)->text << "at" << r->list.at(i)->createdAt.toString("dd.MM.yyyy hh:mm:ss");
      }

      delete r;
    }
    break;

    case TwitOAvis::STATUS_UPDATE:
    {
      TwitOAvis::RespStatusUpdate *r = static_cast<TwitOAvis::RespStatusUpdate*>(resp);

      qDebug() << *r->status;

      delete r;
    }
    break;

    case TwitOAvis::PUBLIC_TIMELINE:
    {
      TwitOAvis::RespFriendsTimeline *r = static_cast<TwitOAvis::RespFriendsTimeline*>(resp);

      qDebug() << r->list.count();

      delete r;
    }
    break;
  }
}
