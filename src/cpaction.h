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

#ifndef CPACTION_H
#define CPACTION_H

#include <QtCore/QObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QtXml/QDomNode>
#include <QDebug>
#include <QDateTime>
#include <QMultiMap>
#include <QStringList>
#include <QtXml/QXmlStreamWriter>
#include "cpengine.h"


class CPAction : public QObject
{
    Q_OBJECT
public:
    CPAction(int action, QObject *parent = 0);
    ~CPAction();
    enum CPOperation {
        GetUserBlogs,
        GetPages,
        GetPageStatuses,
        GetPage,
        NewPage,
        EditPage,
        DeletePage,
        GetPosts,
        GetPostStatuses,
        GetPost,
        NewPost,
        EditPost,
        DeletePost,
        GetCategories,
        NewCategory,
        DeleteCategory,
        GetTags,
        GetComments,
        GetPostComments,
        GetPostCommentsCount,
        GetCommentStatusList,
        GetComment,
        NewComment,
        EditComment,
        ApproveComment,
        UnapproveComment,
        SpamComment,
        DeleteComment,
        UploadFile,
        UploadEditorImage,
        UploadMultipleFiles,
        GetStats,
        Report,
        FetchingApiKey,
        GetMediaSettings,
        GetMediaLibrary,
        GetMediaItem
    };
    QByteArray xmlData;

public slots:
    void exec(const QString &httpMethod,
                 const QMultiMap<QString, QVariant> &params,
                 const QStringList order = QStringList(),
                 const bool isMultiPart = false);
    void abortRequest();
private slots:
    void requestFinished();
    void readData();
    void requestError(QNetworkReply::NetworkError);
    void dataParsed(const QVariant &result);
signals:
    void error(const int op, const int code, const QString msg);
    void finished(const int op, const QVariant);

private:
    void prepareRequestData(QByteArray *xml, const QMultiMap<QString, QVariant> &params, QStringList order = QStringList());
    QString prepareRPCUrl(const QString url);
    QByteArray methodName();
    int iAction;
    QNetworkReply* iRequest;
    QNetworkReply::NetworkError iError;
    QString iErrorString;
    QByteArray buffer;
	QVariant parse(const QByteArray data);
	QVariant readParams(const QDomNode params);
	QVariant readParam(QDomNode param);
	QVariantList readArray(QDomNode array);
	QVariantMap readStruct(QDomNode strct);
	QPair<QString, QVariant> readMember(QDomNode member);
	QVariant readValue(QDomNode val);
	QVariant readFault(QDomNode fault);
	void writeStruct(QXmlStreamWriter *sw, QVariantMap strct);
	void writeMember(QXmlStreamWriter *sw, QString key, QVariant value);
	void writeArray(QXmlStreamWriter *sw, QVariantList list);
	void writeValue(QXmlStreamWriter *sw, QVariant value);
};
#endif // CPACTION_H
