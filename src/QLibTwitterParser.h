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
      static RespTimeline *Favourites(QString xml);
      
      static RespRateLimit *RateLimit(QString xml);

      static RespStatus *StatusUpdate(QString xml);
      static RespStatus *AddFavourite(QString xml);
      static RespStatus *RemoveFavourite(QString xml);

      static QList<elStatus*> getStatusList(QString xml);
      static QString getError(QString xml);

      static QDateTime toDateTime(QString str);
      static bool toBool(QString str);
  };
}

#endif // TWITOAVISPARSER_H
