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

#ifndef CPENGINE_H
#define CPENGINE_H

#include <QtCore/QObject>
#include <QtCore/QMultiMap>
#include <QtCore/QUrl>
#include <QDebug>

class QNetworkAccessManager;
class QNetworkReply;
class QNetworkRequest;

class CPEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString blogId READ blogId WRITE setBlogId NOTIFY blogIdChanged)
    Q_PROPERTY(QString blogName READ blogName WRITE setBlogName NOTIFY blogNameChanged)
    Q_PROPERTY(QString blogUrl READ blogUrl WRITE setBlogUrl NOTIFY blogUrlChanged)
    Q_PROPERTY(QString blogRPCUrl READ blogRPCUrl WRITE setBlogRPCUrl NOTIFY blogRPCUrlChanged)
    Q_PROPERTY(QString blogSanitizedUrl READ blogSanitizedUrl WRITE setBlogSanitizedUrl NOTIFY blogSanitizedUrlChanged)
    Q_PROPERTY(QString blogUsername READ blogUsername WRITE setBlogUsername NOTIFY blogUsernameChanged)
    Q_PROPERTY(QString blogPassword READ blogPassword WRITE setBlogPassword NOTIFY blogPasswordChanged)
    Q_PROPERTY(QString blogHtAccessUsername READ blogHtAccessUsername WRITE setBlogHtAccessUsername NOTIFY blogHtAccessUsernameChanged)
    Q_PROPERTY(QString blogHtAccessPassword READ blogHtAccessPassword WRITE setBlogHtAccessPassword NOTIFY blogHtAccessPasswordChanged)

public:
    static CPEngine &instance();

    QNetworkAccessManager *networkAccessManager() const;

    const QString &blogId() const;
    const QString &blogName() const;
    const QString &blogUrl() const;
    const QString &blogRPCUrl() const;
    const QString &blogSanitizedUrl() const;
    const QString &blogUsername() const;
    const QString &blogPassword() const;
    const QString &blogHtAccessUsername() const;
    const QString &blogHtAccessPassword() const;

    QNetworkReply *request(const QString &method, const QUrl &url, const QByteArray &data, bool multiPart = false);
//    QNetworkReply *request(const QString &method, const QUrl &url, const QMultiMap<QString, QByteArray> &params, const QByteArray &acceptEncoding);
//    QNetworkReply *echo(const QString &method, const QUrl &url, const QMultiMap<QString, QByteArray> &params, const QUrl& serviceProvider, const QUrl &realm, bool multiPart = false);

    bool updateToken(QNetworkReply *reply);

public slots:
    void setNetworkAccessManager(QNetworkAccessManager *networkAccessManager);
    void setBlogId(const QString &blogId);
    void setBlogName(const QString &blogName);
    void setBlogUrl(const QString &blogUrl);
    void setBlogRPCUrl(const QString &blogRPCUrl);
    void setBlogSanitizedUrl(const QString &blogSanitizedUrl);
    void setBlogUsername(const QString &blogUsername);
    void setBlogPassword(const QString &blogPassword);
    void setBlogHtAccessUsername(const QString &blogHtAccessUsername);
    void setBlogHtAccessPassword(const QString &blogHtAccessPassword);

signals:
    void networkAccessManagerChanged(QNetworkAccessManager *networkAccessManager);
    void blogIdChanged(const QString &blogId);
    void blogNameChanged(const QString &blogName);
    void blogUrlChanged(const QString &blogUrl);
    void blogRPCUrlChanged(const QString &blogRPCUrl);
    void blogSanitizedUrlChanged(const QString &blogSanitizedUrl);
    void blogUsernameChanged(const QString &blogUsername);
    void blogPasswordChanged(const QString &blogPassword);
    void blogHtAccessUsernameChanged(const QString &blogHtAccessUsername);
    void blogHtAccessPasswordChanged(const QString &blogHtAccessPassword);

private:
    explicit CPEngine(QObject *parent = 0);
    class Private;
    Private *d;
};

#endif // CPENGINE_H
