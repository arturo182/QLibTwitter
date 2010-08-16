/**
  * QLibTwitter
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#ifndef TWITOAVISCOMMON_H
#define TWITOAVISCOMMON_H

#include <QtCore/QString>
#include <QtCore/QDateTime>
#include <QtCore/QDebug>

namespace QLibTwitter
{
  enum DataFormat
  {
    XML = 0,
    JSON
  };

  enum RequestType
  {
    FRIENDS_TIMELINE = 0,
    STATUS_UPDATE,
    PUBLIC_TIMELINE,
    USER_TIMELINE,
    HOME_TIMELINE,
    MENTIONS,
    RATE_LIMIT
  };

  struct elUser
  {
    qint64 id;
    QString name;
    QString screenName;
    QString description;
    QString location;
    QString profileImageUrl;
    QString url;
    bool isProtected;
    int followersCount;
    QString profileBackgroundColor;
    QString profileTextColor;
    QString profileLinkColor;
    QString profileSidebarFillColor;
    QString profileSidebarBorderColor;
    int friendsCount;
    QDateTime createdAt;
    int favoritesCount;
    int utcOffset;
    QString timeZone;
    QString profileBackgroundImageUrl;
    bool isProfileBackgroundTiled;
    bool isProfileBackgroundUsed;
    bool notifications;
    bool isGeoEnabled;
    bool isVerified;
    bool isFollowed;
    int statusesCount;
    QString lang;
    bool hasContributorsEnabled;
    bool followRequestSent;
    int listedCount;
    bool showAllInlineMedia;
  };

  struct elStatus
  {
    QDateTime createdAt;
    qint64 id;
    QString text;
    QString source;
    bool isTruncated;
    qint64 inReplyToStatusId;
    qint64 inReplyToUserId;
    bool isFavorited;
    QString inReplyToScreenName;
    elUser user;
  };

  class Response
  {
    public:
      Response() { }
      Response(RequestType type) { m_type = type; }
      RequestType getType() { return m_type; }

    protected:
      RequestType m_type;
  };

  class RespStatusUpdate: public Response
  {
    public:
      RespStatusUpdate(): Response(STATUS_UPDATE) { status = NULL; }
      ~RespStatusUpdate() { if(status) { delete status; } }
      elStatus *status;
  };

  class RespTimeline: public Response
  {
    public:
      RespTimeline(RequestType type): Response(type) {  }
      QList<elStatus*> list;
  };

  class RespRateLimit: public Response
  {
    public:
      RespRateLimit(): Response(RATE_LIMIT) { }
      int remainingHits;
      int hourlyLimit;
      int resetTimeSec;
      QDateTime resetTime;
  };

  inline QDebug operator<<(QDebug debug, const elStatus status)
  {
    debug.nospace() << "QLibTwitter::elStatus(\n";

    debug << "  createdAt = " << status.createdAt << "\n";
    debug << " id =" << status.id << "\n";
    debug << " inReplyToScreenName =" << status.inReplyToScreenName << "\n";
    debug << " inReplyToStatusId =" << status.inReplyToStatusId << "\n";
    debug << " inReplyToUserId =" << status.inReplyToUserId << "\n";
    debug << " isFavorited =" << status.isFavorited << "\n";
    debug << " isTruncated =" << status.isTruncated << "\n";
    debug << " source =" << status.source << "\n";
    debug << " text =" << status.text << "\n";

    debug << " user = QLibTwitter::elUser(\n";
    debug << "   createdAt =" << status.user.createdAt << "\n";
    debug << "   description =" << status.user.description << "\n";
    debug << "   favoritesCount =" << status.user.favoritesCount << "\n";
    debug << "   followersCount =" << status.user.followersCount << "\n";
    debug << "   followRequestSent =" << status.user.followRequestSent << "\n";
    debug << "   friendsCount =" << status.user.friendsCount << "\n";
    debug << "   hasContributorsEnabled =" << status.user.hasContributorsEnabled << "\n";
    debug << "   id =" << status.user.id << "\n";
    debug << "   isFollowed =" << status.user.isFollowed << "\n";
    debug << "   isGeoEnabled =" << status.user.isGeoEnabled << "\n";
    debug << "   isProfileBackgroundTiled =" << status.user.isProfileBackgroundTiled << "\n";
    debug << "   isProfileBackgroundUsed =" << status.user.isProfileBackgroundUsed << "\n";
    debug << "   isProtected =" << status.user.isProtected << "\n";
    debug << "   isVerified =" << status.user.isVerified << "\n";
    debug << "   lang =" << status.user.lang << "\n";
    debug << "   listedCount =" << status.user.listedCount << "\n";
    debug << "   location =" << status.user.location << "\n";
    debug << "   name =" << status.user.name << "\n";
    debug << "   notifications =" << status.user.notifications << "\n";
    debug << "   profileBackgroundColor =" << status.user.profileBackgroundColor << "\n";
    debug << "   profileBackgroundImageUrl =" << status.user.profileBackgroundImageUrl << "\n";
    debug << "   profileImageUrl =" << status.user.profileImageUrl << "\n";
    debug << "   profileLinkColor =" << status.user.profileLinkColor << "\n";
    debug << "   profileSidebarBorderColor =" << status.user.profileSidebarBorderColor << "\n";
    debug << "   profileSidebarFillColor =" << status.user.profileSidebarFillColor << "\n";
    debug << "   profileTextColor =" << status.user.profileTextColor << "\n";
    debug << "   screenName =" << status.user.screenName << "\n";
    debug << "   showAllInlineMedia =" << status.user.showAllInlineMedia << "\n";
    debug << "   statusesCount =" << status.user.statusesCount << "\n";
    debug << "   timeZone =" << status.user.timeZone << "\n";
    debug << "   url =" << status.user.url << "\n";
    debug << "   utcOffset =" << status.user.utcOffset << "\n";
    debug << " )\n";

    debug << ")";

    return debug.space();
  }
}

#endif // TWITOAVISCOMMON_H
