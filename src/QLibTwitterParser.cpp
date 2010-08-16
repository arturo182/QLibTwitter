/**
  * QLibTwitter
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#include "QLibTwitterParser.h"

#include <QtXml/QDomDocument>
#include <QtCore/QDebug>
#include <QtCore/QStringList>

using namespace QLibTwitter;

RespFriendsTimeline *Parser::FriendsTimeline(QString xml)
{
  RespFriendsTimeline *resp = NULL;
  QList<elStatus*> list = getStatusList(xml);

  if(!list.isEmpty()) {
    resp = new RespFriendsTimeline();
    resp->list = list;
  }

  return resp;
}

RespPublicTimeline *Parser::PublicTimeline(QString xml)
{
  RespPublicTimeline *resp = NULL;
  QList<elStatus*> list = getStatusList(xml);

  if(!list.isEmpty()) {
    resp = new RespPublicTimeline();
    resp->list = list;
  }

  return resp;
}

RespStatusUpdate *Parser::StatusUpdate(QString xml)
{
  RespStatusUpdate *resp = new RespStatusUpdate();
  resp->status = getStatusList(xml).at(0);
  return resp;
}

QList<elStatus*> Parser::getStatusList(QString xml)
{
  QList<elStatus*> list;

  QDomDocument dom;
  dom.setContent(xml);

  QDomNodeList nodes = dom.elementsByTagName("status");
  for(int i = 0; i < nodes.count(); i++) {
    elStatus *el = new elStatus();

    el->createdAt = toDateTime(nodes.at(i).namedItem("created_at").toElement().text());
    el->id = nodes.at(i).namedItem("id").toElement().text().toLongLong();
    el->inReplyToScreenName = nodes.at(i).namedItem("in_reply_to_screen_name").toElement().text();
    el->inReplyToStatusId = nodes.at(i).namedItem("in_reply_to_status_id").toElement().text().toLongLong();
    el->inReplyToUserId = nodes.at(i).namedItem("in_reply_to_user_id").toElement().text().toLongLong();
    el->isFavorited = toBool(nodes.at(i).namedItem("favorited").toElement().text());
    el->isTruncated = toBool(nodes.at(i).namedItem("truncated").toElement().text());
    el->source = nodes.at(i).namedItem("source").toElement().text();
    el->text = nodes.at(i).namedItem("text").toElement().text();

    el->user.createdAt = toDateTime(nodes.at(i).namedItem("user").namedItem("created_at").toElement().text());
    el->user.description = nodes.at(i).namedItem("user").namedItem("description").toElement().text();
    el->user.favoritesCount = nodes.at(i).namedItem("user").namedItem("favourites_count").toElement().text().toInt();
    el->user.followersCount = nodes.at(i).namedItem("user").namedItem("followers_count").toElement().text().toInt();
    el->user.followRequestSent = toBool(nodes.at(i).namedItem("user").namedItem("follow_request_sent").toElement().text());
    el->user.friendsCount = nodes.at(i).namedItem("user").namedItem("friends_count").toElement().text().toInt();
    el->user.hasContributorsEnabled = toBool(nodes.at(i).namedItem("user").namedItem("contributors_enabled").toElement().text());
    el->user.id = nodes.at(i).namedItem("user").namedItem("id").toElement().text().toInt();
    el->user.isFollowed = toBool(nodes.at(i).namedItem("user").namedItem("following").toElement().text());
    el->user.isGeoEnabled = toBool(nodes.at(i).namedItem("user").namedItem("geo_enabled").toElement().text());
    el->user.isProfileBackgroundTiled = toBool(nodes.at(i).namedItem("user").namedItem("profile_background_tile").toElement().text());
    el->user.isProfileBackgroundUsed = toBool(nodes.at(i).namedItem("user").namedItem("profile_use_background_image").toElement().text());
    el->user.isProtected = toBool(nodes.at(i).namedItem("user").namedItem("protected").toElement().text());
    el->user.isVerified = toBool(nodes.at(i).namedItem("user").namedItem("verified").toElement().text());
    el->user.lang = nodes.at(i).namedItem("user").namedItem("lang").toElement().text();
    el->user.listedCount = nodes.at(i).namedItem("user").namedItem("listed_count").toElement().text().toInt();
    el->user.location = nodes.at(i).namedItem("user").namedItem("location").toElement().text();
    el->user.name = nodes.at(i).namedItem("user").namedItem("name").toElement().text();
    el->user.notifications = toBool(nodes.at(i).namedItem("user").namedItem("notifications").toElement().text());
    el->user.profileBackgroundColor = nodes.at(i).namedItem("user").namedItem("profile_background_color").toElement().text();
    el->user.profileBackgroundImageUrl = nodes.at(i).namedItem("user").namedItem("profile_background_image_url").toElement().text();
    el->user.profileImageUrl = nodes.at(i).namedItem("user").namedItem("profile_image_url").toElement().text();
    el->user.profileLinkColor = nodes.at(i).namedItem("user").namedItem("profile_link_color>").toElement().text();
    el->user.profileSidebarBorderColor = nodes.at(i).namedItem("user").namedItem("profile_sidebar_border_color").toElement().text();
    el->user.profileSidebarFillColor = nodes.at(i).namedItem("user").namedItem("profile_sidebar_fill_color").toElement().text();
    el->user.profileTextColor = nodes.at(i).namedItem("user").namedItem("profile_text_color").toElement().text();
    el->user.screenName = nodes.at(i).namedItem("user").namedItem("screen_name").toElement().text();
    el->user.showAllInlineMedia = toBool(nodes.at(i).namedItem("user").namedItem("show_all_inline_media").toElement().text());
    el->user.statusesCount = nodes.at(i).namedItem("user").namedItem("statuses_count").toElement().text().toInt();
    el->user.timeZone = nodes.at(i).namedItem("user").namedItem("time_zone").toElement().text();
    el->user.url = nodes.at(i).namedItem("user").namedItem("url").toElement().text();
    el->user.utcOffset = nodes.at(i).namedItem("user").namedItem("utc_offset").toElement().text().toInt();

    list.append(el);
  }

  return list;
}

QString Parser::getError(QString xml)
{
  QDomDocument dom;
  dom.setContent(xml);

  return dom.elementsByTagName("hash").at(0).namedItem("error").toElement().text();
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
