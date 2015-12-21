/**************************************************************************
 *   CutePress
 *   Copyright (C) 2015 Abhishek Kumar <abhishek.mrt22@gmail.com>
 *
 *   This file is part of CutePress.
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **************************************************************************/

#ifndef APPUTIL_H
#define APPUTIL_H
#include <QObject>
#include <QDateTime>
#include <QStringList>
#include <QUrl>
#include <bb/system/Clipboard>
#include <bps/navigator.h>
#include "common.h"
#include "roleitemmodel.h"

/** An item. */
class AppUtil: public QObject {
    Q_OBJECT
public:
    /** Default constructor. */
    AppUtil(QObject *parent = 0);

    /** Destructor. */
    ~AppUtil();

public slots:
    QString normalizeText(QString myChat);
    void copyTextToClipboard(const QString txt);
    void launchBrowser(QString url);
    QString removeImgFromString(const QString txt);
    QVariant fixHTML(const QString txt);
    void likeItemInModel(RoleItemModel*, const QString);
    void unlikeItemInModel(RoleItemModel*, const QString);
    bool deleteItemInModel(RoleItemModel*, const QString);
    bool deletePostInModel(RoleItemModel*, const QString);
    bool approveCommentInModel(RoleItemModel*, const QString);
    bool unapproveCommentInModel(RoleItemModel*, const QString);
    bool spamCommentInModel(RoleItemModel*, const QString);
    bool deleteCommentInModel(RoleItemModel*, const QString);
    bool modelContainsItem(RoleItemModel*, const QString);
    int itemPositionInModel(RoleItemModel*, const QString);
    QString getWPUrl(const QString txt);

    QVariant getItemData(RoleItemModel*, const int, const QByteArray);
    QString getFileExtension(const QString filename);
    void changeValueInModel(RoleItemModel* model, const int idx, const QString key, const QVariant value);
    void changeValueInModelWithItemId(RoleItemModel* model, const QString id, const QString key, const QVariant value);
    QString tagsFromList(const QStringList tags);
    QString categoriesFromList(const QStringList categories);
    bool isImageFile(const QString file);

protected:
    QHash<int, QString> postsRoleNames;
    bb::system::Clipboard clipboard;
};
#endif // APPUTIL_H
