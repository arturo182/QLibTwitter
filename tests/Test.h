/**
  * TwitOAvis
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#ifndef TEST_H
#define TEST_H

#include "TwitOAvis.h"

class Test: public QObject
{
  Q_OBJECT

  public:
    explicit Test(QObject *parent = 0);

  signals:

  public slots:
    void slotGotRequestToken(OAvis::Token *token);
    void slotGotAccessToken(OAvis::Token *token);

  private:
    TwitOAvis *m_lib;

};

#endif // TEST_H
