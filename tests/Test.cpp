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
  m_lib = new TwitOAvis("vP69u6PGSakKTIoE2ApvVw", "g2PjaAttF0prUfmMTSlzVe9Dr7LBqCGcJXlWwhlwA");

  connect(m_lib, SIGNAL(signalRequestToken(OAvis::Token*)), this, SLOT(slotGotRequestToken(OAvis::Token*)));
  connect(m_lib, SIGNAL(signalAccessToken(OAvis::Token*)), this, SLOT(slotGotAccessToken(OAvis::Token*)));


  m_lib->slotRequestToken();
  //m_lib->slotMakeRequest("https://api.twitter.com/1/statuses/friends_timeline.xml");
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
  token->debug();
  m_lib->slotMakeRequest("http://api.twitter.com/1/statuses/friends_timeline.xml");
}
