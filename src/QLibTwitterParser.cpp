/**
  * QLibTwitter
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  */

#include "QLibTwitterParser.h"

#include <QtXml/QDomDocument>
#include <QtCore/QDebug>
#include <QtCore/QStringList>

using namespace QLibTwitter;

RespTimeline *Parser::FriendsTimeline(QString xml)
{
  RespTimeline *resp = NULL;
  QList<elStatus*> list = getStatusList(xml);

  if(!list.isEmpty()) {
    resp = new RespTimeline(FRIENDS_TIMELINE);
    resp->list = list;
  }

  return resp;
}

RespTimeline *Parser::PublicTimeline(QString xml)
{
  RespTimeline *resp = NULL;
  QList<elStatus*> list = getStatusList(xml);

  if(!list.isEmpty()) {
    resp = new RespTimeline(PUBLIC_TIMELINE);
    resp->list = list;
  }

  return resp;
}

RespTimeline *Parser::UserTimeline(QString xml)
{
  RespTimeline *resp = NULL;
  QList<elStatus*> list = getStatusList(xml);

  if(!list.isEmpty()) {
    resp = new RespTimeline(USER_TIMELINE);
    resp->list = list;
  }

  return resp;
}

RespTimeline *Parser::HomeTimeline(QString xml)
{
  RespTimeline *resp = NULL;
  QList<elStatus*> list = getStatusList(xml);

  if(!list.isEmpty()) {
    resp = new RespTimeline(HOME_TIMELINE);
    resp->list = list;
  }

  return resp;
}

RespTimeline *Parser::Mentions(QString xml)
{
  RespTimeline *resp = NULL;
  QList<elStatus*> list = getStatusList(xml);

  if(!list.isEmpty()) {
    resp = new RespTimeline(MENTIONS);
    resp->list = list;
  }

  return resp;
}

RespRateLimit *Parser::RateLimit(QString xml)
{
  RespRateLimit *resp = new RespRateLimit();

  QDomDocument dom;
  dom.setContent(xml);

  QDomNodeList remainingHits = dom.elementsByTagName("remaining-hits");
  if(remainingHits.count() > 0) {
    resp->remainingHits = remainingHits.at(0).toElement().text().toInt();
  }

  QDomNodeList hourlyLimit = dom.elementsByTagName("hourly-limit");
  if(hourlyLimit.count() > 0) {
    resp->hourlyLimit = hourlyLimit.at(0).toElement().text().toInt();
  }

  QDomNodeList resetTime = dom.elementsByTagName("reset-time");
  if(resetTime.count() > 0) {
    resp->resetTime = QDateTime::fromString(resetTime.at(0).toElement().text(), Qt::ISODate);
  }

  QDomNodeList resetTimeSec = dom.elementsByTagName("reset-time-in-seconds");
  if(resetTimeSec.count() > 0) {
    resp->resetTimeSec = resetTimeSec.at(0).toElement().text().toInt();
  }

  return resp;
}

RespStatusUpdate *Parser::StatusUpdate(QString xml)
{
  RespStatusUpdate *resp = new RespStatusUpdate();
  resp->status = getStatusList(xml).at(0);
  return resp;
}

RespTimeline *Parser::Favourites(QString xml)
{
  RespTimeline *resp = NULL;
  QList<elStatus*> list = getStatusList(xml);

  if(!list.isEmpty()) {
    resp = new RespTimeline(FAVOURITES);
    resp->list = list;
  }

  return resp;
}

QList<elStatus*> Parser::getStatusList(QString xml)
{
  QList<elStatus*> list;

  QDomDocument dom;
  dom.setContent(xml);

  QDomNodeList nodes = dom.elementsByTagName("status");
  for(int i = nodes.count()-1; i >= 0; i--) {
    elStatus *el = new elStatus();

    QDomNode status = nodes.at(i);
    if(!status.isNull()) {
      el->createdAt = toDateTime(status.namedItem("created_at").toElement().text());
      el->id = status.namedItem("id").toElement().text().toLongLong();
      el->inReplyToScreenName = status.namedItem("in_reply_to_screen_name").toElement().text();
      el->inReplyToStatusId = status.namedItem("in_reply_to_status_id").toElement().text().toLongLong();
      el->inReplyToUserId = status.namedItem("in_reply_to_user_id").toElement().text().toLongLong();
      el->isFavorited = toBool(status.namedItem("favorited").toElement().text());
      el->isTruncated = toBool(status.namedItem("truncated").toElement().text());
      el->source = status.namedItem("source").toElement().text();
      el->text = status.namedItem("text").toElement().text();

      QDomNode user = status.namedItem("user");
      if(!user.isNull()) {
        if(!user.namedItem("id").isNull()) {
          el->user.id = user.namedItem("id").toElement().text().toInt();
        }

        if(!user.namedItem("screen_name").isNull()) {
          if(!user.namedItem("created_at").isNull()) {
            el->user.createdAt = toDateTime(user.namedItem("created_at").toElement().text());
          }

          if(!user.namedItem("description").isNull()) {
            el->user.description = user.namedItem("description").toElement().text();
          }

          if(!user.namedItem("favourites_count").isNull()) {
            el->user.favoritesCount = user.namedItem("favourites_count").toElement().text().toInt();
          }

          if(!user.namedItem("followers_count").isNull()) {
            el->user.followersCount = user.namedItem("followers_count").toElement().text().toInt();
          }

          if(!user.namedItem("follow_request_sent").isNull()) {
            el->user.followRequestSent = toBool(user.namedItem("follow_request_sent").toElement().text());
          }

          if(!user.namedItem("friends_count").isNull()) {
            el->user.friendsCount = user.namedItem("friends_count").toElement().text().toInt();
          }

          if(!user.namedItem("contributors_enabled").isNull()) {
            el->user.hasContributorsEnabled = toBool(user.namedItem("contributors_enabled").toElement().text());
          }

          if(!user.namedItem("following").isNull()) {
            el->user.isFollowed = toBool(user.namedItem("following").toElement().text());
          }

          if(!user.namedItem("geo_enabled").isNull()) {
            el->user.isGeoEnabled = toBool(user.namedItem("geo_enabled").toElement().text());
          }

          if(!user.namedItem("profile_background_tile").isNull()) {
            el->user.isProfileBackgroundTiled = toBool(user.namedItem("profile_background_tile").toElement().text());
          }

          if(!user.namedItem("profile_use_background_image").isNull()) {
            el->user.isProfileBackgroundUsed = toBool(user.namedItem("profile_use_background_image").toElement().text());
          }

          if(!user.namedItem("protected").isNull()) {
            el->user.isProtected = toBool(user.namedItem("protected").toElement().text());
          }

          if(!user.namedItem("verified").isNull()) {
            el->user.isVerified = toBool(user.namedItem("verified").toElement().text());
          }

          if(!user.namedItem("lang").isNull()) {
            el->user.lang = user.namedItem("lang").toElement().text();
          }

          if(!user.namedItem("listed_count").isNull()) {
            el->user.listedCount = user.namedItem("listed_count").toElement().text().toInt();
          }

          if(!user.namedItem("location").isNull()) {
            el->user.location = user.namedItem("location").toElement().text();
          }

          if(!user.namedItem("name").isNull()) {
            el->user.name = user.namedItem("name").toElement().text();
          }

          if(!user.namedItem("notifications").isNull()) {
            el->user.notifications = toBool(user.namedItem("notifications").toElement().text());
          }

          if(!user.namedItem("profile_background_color").isNull()) {
            el->user.profileBackgroundColor = user.namedItem("profile_background_color").toElement().text();
          }

          if(!user.namedItem("profile_background_image_url").isNull()) {
            el->user.profileBackgroundImageUrl = user.namedItem("profile_background_image_url").toElement().text();
          }

          if(!user.namedItem("profile_image_url").isNull()) {
            el->user.profileImageUrl = user.namedItem("profile_image_url").toElement().text();
          }

          if(!user.namedItem("profile_link_color").isNull()) {
            el->user.profileLinkColor = user.namedItem("profile_link_color>").toElement().text();
          }

          if(!user.namedItem("profile_sidebar_border_color").isNull()) {
            el->user.profileSidebarBorderColor = user.namedItem("profile_sidebar_border_color").toElement().text();
          }

          if(!user.namedItem("profile_sidebar_fill_color").isNull()) {
            el->user.profileSidebarFillColor = user.namedItem("profile_sidebar_fill_color").toElement().text();
          }

          if(!user.namedItem("profile_text_color").isNull()) {
            el->user.profileTextColor = user.namedItem("profile_text_color").toElement().text();
          }

          if(!user.namedItem("screen_name").isNull()) {
            el->user.screenName = user.namedItem("screen_name").toElement().text();
          }

          if(!user.namedItem("show_all_inline_media").isNull()) {
            el->user.showAllInlineMedia = toBool(user.namedItem("show_all_inline_media").toElement().text());
          }

          if(!user.namedItem("statuses_count").isNull()) {
            el->user.statusesCount = user.namedItem("statuses_count").toElement().text().toInt();
          }

          if(!user.namedItem("time_zone").isNull()) {
            el->user.timeZone = user.namedItem("time_zone").toElement().text();
          }

          if(!user.namedItem("url").isNull()) {
            el->user.url = user.namedItem("url").toElement().text();
          }

          if(!user.namedItem("utc_offset").isNull()) {
            el->user.utcOffset = user.namedItem("utc_offset").toElement().text().toInt();
          }
        }
      }
    }

    list.append(el);
  }

  return list;
}

QString Parser::getError(QString xml)
{
  QDomDocument dom;
  dom.setContent(xml);

  QDomNodeList hash = dom.elementsByTagName("hash");
  if(hash.count() > 0) {
    if(!hash.at(0).namedItem("error").isNull()) {
      return hash.at(0).namedItem("error").toElement().text();
    }
  }

  return "";
}

QDateTime Parser::toDateTime(QString str)
{
  QStringList list = str.split(" ");
  QStringList months = QStringList() << "zero" << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun" << "Jul" << "Aug" << "Sep" << "Oct" << "Nov" << "Dec";

  return QDateTime(QDate(list.at(5).toInt(), months.indexOf(list.at(1)), list.at(2).toInt()), QTime::fromString(list.at(3)));
}

bool Parser::toBool(QString str)
{
  return (str == "true");
}
