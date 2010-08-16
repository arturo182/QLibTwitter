/**
  * QLibTwitter
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#ifndef TEST_H
#define TEST_H

#include "QLibTwitterCore.h"

class Test: public QObject
{
  Q_OBJECT

  public:
    explicit Test(QObject *parent = 0);

  signals:

  public slots:
    void slotGotRequestToken(QLibOA::Token *token);
    void slotGotAccessToken(QLibOA::Token *token);
    void slotGotResponse(QLibTwitter::Response *resp);

  private:
    QLibTwitter::Core *m_lib;

};

#endif // TEST_H
