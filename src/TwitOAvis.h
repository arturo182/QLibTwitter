/**
  * TwitOAvis
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#ifndef TWITOAVIS_H
#define TWITOAVIS_H

#include <QObject>

class TwitOAvis: public QObject
{
  Q_OBJECT

  enum DataFormat
  {
    JSON = 0,
    XML = 1
  };

  public:
  explicit TwitOAvis(QString consumerKey, QString consumerSecret, QString tokenKey = QString::null, QString tokenSecret = QString::null);

  signals:
    void signalReponseReceived();

  public slots:
    void slotMakeRequest();

  private:
    OAvis::

};

#endif // TWITOAVIS_H
