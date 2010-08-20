/**
  * QLibTwitter
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  */

#ifndef TWITOAVISPARSER_H
#define TWITOAVISPARSER_H

#include "QLibTwitterCommon.h"
#include "QLibTwitterParser.h"

#include <QtCore/QObject>

namespace QLibTwitter
{
  class Parser: public QObject
  {
    Q_OBJECT

    public:
      explicit Parser(QObject *parent = 0): QObject(parent) { }

      static RespTimeline *FriendsTimeline(QString xml);
      static RespTimeline *PublicTimeline(QString xml);
      static RespTimeline *UserTimeline(QString xml);
      static RespTimeline *HomeTimeline(QString xml);
      static RespTimeline *Mentions(QString xml);

      static RespRateLimit *RateLimit(QString xml);

      static RespStatusUpdate *StatusUpdate(QString xml);

      static QList<elStatus*> getStatusList(QString xml);
      static QString getError(QString xml);

      static QDateTime toDateTime(QString str);
      static bool toBool(QString str);
  };
}

#endif // TWITOAVISPARSER_H
