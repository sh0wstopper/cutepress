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

#include "cpengine.h"

#include <QtCore/QDateTime>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QRegExp>
#include <QtCore/QStringList>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

class CPEngine::Private : public QObject {
    Q_OBJECT
public:
    Private(CPEngine *parent);

    QNetworkReply *request(const QString &method, const QUrl &url, const QByteArray &data, bool multiPart, const QByteArray &acceptEncoding = QByteArray());

    QNetworkAccessManager *networkAccessManager;

    QString blogId;
    QString blogName;
    QString blogUrl;
    QString blogRPCUrl;
    QString blogSanitizedUrl;
    QString blogUsername;
    QString blogPassword;
    QString blogHtAccessUsername;
    QString blogHtAccessPassword;
    QString authorizationUrl;

private slots:
private:
    CPEngine *q;

    QByteArray parameterEncoding(const QString &str) const;
    QByteArray normalize(const QMultiMap<QString, QByteArray> &param) const;
    QByteArray signature(const QString &method, const QUrl &url, const QByteArray &params) const;
    QMultiMap<QString, QByteArray> signatureParams(const QMultiMap<QString, QByteArray> &params) const;
    QByteArray authHeader(const QMultiMap<QString, QByteArray> &params, const QUrl &realm = QUrl()) const;
    void getTokenCredential();
};

CPEngine::Private::Private(CPEngine *parent)
    : QObject(parent)
    , networkAccessManager(0)
    , q(parent)
{
}


QNetworkReply *CPEngine::Private::request(const QString &method, const QUrl &url, const QByteArray &data, bool multiPart, const QByteArray &acceptEncoding)
{
    QNetworkRequest request;
    request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::AlwaysNetwork);
    request.setAttribute(QNetworkRequest::HttpPipeliningAllowedAttribute, true);
    request.setRawHeader("Accept-Encoding",acceptEncoding);

    QNetworkReply *ret = 0;

    QString timestamp;
    if (method == "POST") {
		qDebug()<< "CPEngine---request-POST"<<url;
		if (multiPart) {
		} else {
			if(!blogHtAccessUsername.isEmpty())
			    request.setRawHeader("Authorization", "Basic "+QByteArray(blogHtAccessUsername.toUtf8()+":"+blogHtAccessPassword.toUtf8()).toBase64());
			request.setRawHeader("User-Agent", "wp-bb10-cutepress/1.0.0");
			request.setHeader(QNetworkRequest::ContentTypeHeader, "text/xml");
			request.setUrl(url);
			ret = q->networkAccessManager()->post(request, data);
		}

    } else if (method == "GET") {
    }
    return ret;
}

CPEngine &CPEngine::instance()
{
    static CPEngine ret;
    return ret;
}

CPEngine::CPEngine(QObject *parent)
    : QObject(parent)
{
    d = new Private(this);
}

QNetworkAccessManager *CPEngine::networkAccessManager() const
{
    if (!d->networkAccessManager)
        d->networkAccessManager = new QNetworkAccessManager(d);
    return d->networkAccessManager;
}

void CPEngine::setNetworkAccessManager(QNetworkAccessManager *networkAccessManager)
{
    if (d->networkAccessManager == networkAccessManager) return;
    d->networkAccessManager = networkAccessManager;
    emit networkAccessManagerChanged(networkAccessManager);
}

const QString &CPEngine::blogId() const
{
    return d->blogId;
}

void CPEngine::setBlogId(const QString &blogId)
{
    if (d->blogId == blogId) return;
    d->blogId = blogId;
    emit blogIdChanged(blogId);
}

const QString &CPEngine::blogName() const
{
    return d->blogName;
}

void CPEngine::setBlogName(const QString &blogName)
{
    if (d->blogName == blogName) return;
    d->blogName = blogName;
    emit blogNameChanged(blogName);
}

const QString &CPEngine::blogUrl() const
{
    return d->blogUrl;
}

void CPEngine::setBlogUrl(const QString &blogUrl)
{
    if (d->blogUrl == blogUrl) return;
    d->blogUrl = blogUrl;
    emit blogUrlChanged(blogUrl);
}

const QString &CPEngine::blogRPCUrl() const
{
    return d->blogRPCUrl;
}

void CPEngine::setBlogRPCUrl(const QString &blogRPCUrl)
{
    if (d->blogRPCUrl == blogRPCUrl) return;
    d->blogRPCUrl = blogRPCUrl;
    emit blogRPCUrlChanged(blogRPCUrl);
}

const QString &CPEngine::blogSanitizedUrl() const
{
    return d->blogSanitizedUrl;
}

void CPEngine::setBlogSanitizedUrl(const QString &blogSanitizedUrl)
{
    if (d->blogSanitizedUrl == blogSanitizedUrl) return;
    d->blogSanitizedUrl = blogSanitizedUrl;
    emit blogSanitizedUrlChanged(blogSanitizedUrl);
}

const QString &CPEngine::blogUsername() const
{
    return d->blogUsername;
}

void CPEngine::setBlogUsername(const QString &blogUsername)
{
    if (d->blogUsername == blogUsername) return;
    d->blogUsername = blogUsername;
    emit blogUsernameChanged(blogUsername);
}

const QString &CPEngine::blogPassword() const
{
    return d->blogPassword;
}

void CPEngine::setBlogPassword(const QString &blogPassword)
{
    if (d->blogPassword == blogPassword) return;
    d->blogPassword = blogPassword;
    emit blogPasswordChanged(blogPassword);
}

const QString &CPEngine::blogHtAccessUsername() const
{
    return d->blogHtAccessUsername;
}

void CPEngine::setBlogHtAccessUsername(const QString &blogHtAccessUsername)
{
    if (d->blogHtAccessUsername == blogHtAccessUsername) return;
    d->blogHtAccessUsername = blogHtAccessUsername;
    emit blogHtAccessUsernameChanged(blogHtAccessUsername);
}

const QString &CPEngine::blogHtAccessPassword() const
{
    return d->blogHtAccessPassword;
}

void CPEngine::setBlogHtAccessPassword(const QString &blogHtAccessPassword)
{
    if (d->blogHtAccessPassword == blogHtAccessPassword) return;
    d->blogHtAccessPassword = blogHtAccessPassword;
    emit blogHtAccessPasswordChanged(blogHtAccessPassword);
}

QNetworkReply *CPEngine::request(const QString &method, const QUrl &url, const QByteArray &data, bool multiPart)
{
    return d->request(method, url, data, multiPart);
}

#include "cpengine.moc"
