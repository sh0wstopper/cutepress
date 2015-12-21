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

#ifndef ABSTRACTCPOBJECT_H_
#define ABSTRACTCPOBJECT_H_

#include <QString>
#include <QObject>
#include <QDateTime>
#include <QStringList>
#include <QUrl>
#include "common.h"
#include "roleitemmodel.h"
#include "cpaction.h"

/** Abstract CP User. */
class AbstractCPObject: public QObject {
    Q_OBJECT

    Q_PROPERTY(QString infoMessage READ infoMessage NOTIFY infoMessageChanged)

public:
    /** Default constructor. */
    AbstractCPObject(QObject *parent = 0);

    /** Destructor. */
    ~AbstractCPObject();

    void prepareRoleNames();
    QString infoMessage() { return _infoMessage; }

    void setInfoMessage(const QString infoMessage) {_infoMessage = infoMessage; emit infoMessageChanged(_infoMessage);}
public slots:
	void appendPosts(RoleItemModel *model, const QVariantList posts);
    int updatePost(RoleItemModel *model, const QVariantMap post);
	void appendPages(RoleItemModel *model, const QVariantList pages);
    int updatePage(RoleItemModel *model, const QVariantMap page);
	void appendComments(RoleItemModel *model, const QVariantList comments);
    int updateComment(RoleItemModel *model, const QVariantMap comments);
	void appendMediaItems(RoleItemModel *model, const QVariantList mediaItems);
	int updateMediaItem(RoleItemModel *model, const QVariantMap mediaItem);
	void appendCategories(RoleItemModel *model, const QVariantList categories);
	void appendTags(RoleItemModel *model, const QVariantList tags);
	void deletePostInModel(RoleItemModel *model, const QString postId);
	void deletePageInModel(RoleItemModel *model, const QString pageId);
	void deleteCategoryInModel(RoleItemModel *model, const QString categoryId);

signals:
    void infoMessageChanged(const QString);

protected:
    QString localFilePath(QString link);
    QString getHtmlTextSnippet(const QString txt);
	QString _infoMessage;

    QHash<int, CPAction*> requests;

    QHash<int, QString> blogRoleNames;
    QHash<int, QString> postRoleNames;
    QHash<int, QString> pageRoleNames;
    QHash<int, QString> commentRoleNames;
    QHash<int, QString> categoryRoleNames;
    QHash<int, QString> mediaRoleNames;
    QHash<int, QString> tagRoleNames;
};
#endif /* ABSTRACTCPOBJECT_H_ */
