/**
  * TwitOAvis
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#ifndef TEST_H
#define TEST_H

#include "TwitOAvisCore.h"

class Test: public QObject
{
  Q_OBJECT

  public:
    explicit Test(QObject *parent = 0);

  signals:

  public slots:
    void slotGotRequestToken(OAvis::Token *token);
    void slotGotAccessToken(OAvis::Token *token);
    void slotGotResponse(TwitOAvis::Response *resp);

  private:
    TwitOAvis::Core *m_lib;

};

#endif // TEST_H
