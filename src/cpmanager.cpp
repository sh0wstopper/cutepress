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

#include "cpmanager.h"
#include "cpengine.h"

#include <QtGui/QDesktopServices>
#include <QtNetwork/QNetworkReply>

class CPManager::Private : public QObject
{
    Q_OBJECT
public:
    Private(CPManager *parent);

private slots:
    void finished();
    void error(QNetworkReply::NetworkError networkError);

private:
    CPManager *q;
};

CPManager::Private::Private(CPManager *parent)
    : QObject(parent)
    , q(parent)
{
    connect(&CPEngine::instance(), SIGNAL(blogIdChanged(QString)), q, SIGNAL(blogIdChanged(QString)));
    connect(&CPEngine::instance(), SIGNAL(blogNameChanged(QString)), q, SIGNAL(blogNameChanged(QString)));
    connect(&CPEngine::instance(), SIGNAL(blogUrlChanged(QString)), q, SIGNAL(blogUrlChanged(QString)));
    connect(&CPEngine::instance(), SIGNAL(blogRPCUrlChanged(QString)), q, SIGNAL(blogRPCUrlChanged(QString)));
    connect(&CPEngine::instance(), SIGNAL(blogSanitizedUrlChanged(QString)), q, SIGNAL(blogSanitizedUrlChanged(QString)));
    connect(&CPEngine::instance(), SIGNAL(blogUsernameChanged(QString)), q, SIGNAL(blogUsernameChanged(QString)));
    connect(&CPEngine::instance(), SIGNAL(blogPasswordChanged(QString)), q, SIGNAL(blogPasswordChanged(QString)));
    connect(&CPEngine::instance(), SIGNAL(blogHtAccessUsernameChanged(QString)), q, SIGNAL(blogHtAccessUsernameChanged(QString)));
    connect(&CPEngine::instance(), SIGNAL(blogHtAccessPasswordChanged(QString)), q, SIGNAL(blogHtAccessPasswordChanged(QString)));
}

void CPManager::Private::finished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply) return;


    reply->deleteLater();
}

void CPManager::Private::error(QNetworkReply::NetworkError networkError)
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply) return;
    qDebug() << "CPAction---error" << networkError << reply->url() << reply->errorString();
    q->setErrorMessage(QString::fromUtf8(reply->readAll())+reply->errorString());
    reply->deleteLater();
}

CPManager::CPManager(QObject *parent)
    : QObject(parent)
    , d(new Private(this))
{
}

const QString &CPManager::blogId() const
{
    return CPEngine::instance().blogId();
}

void CPManager::setBlogId(const QString &blogId)
{
    CPEngine::instance().setBlogId(blogId);
}

const QString &CPManager::blogName() const
{
    return CPEngine::instance().blogName();
}

void CPManager::setBlogName(const QString &blogName)
{
    CPEngine::instance().setBlogName(blogName);
}

const QString &CPManager::blogUrl() const
{
    return CPEngine::instance().blogUrl();
}

void CPManager::setBlogUrl(const QString &token)
{
    CPEngine::instance().setBlogUrl(token);
}

const QString &CPManager::blogRPCUrl() const
{
    return CPEngine::instance().blogRPCUrl();
}

void CPManager::setBlogRPCUrl(const QString &blogRPCUrl)
{
    CPEngine::instance().setBlogRPCUrl(blogRPCUrl);
}

const QString &CPManager::blogSanitizedUrl() const
{
    return CPEngine::instance().blogSanitizedUrl();
}

void CPManager::setBlogSanitizedUrl(const QString &blogSanitizedUrl)
{
    CPEngine::instance().setBlogSanitizedUrl(blogSanitizedUrl);
}

const QString &CPManager::blogUsername() const
{
    return CPEngine::instance().blogUsername();
}

void CPManager::setBlogUsername(const QString &blogUsername)
{
    CPEngine::instance().setBlogUsername(blogUsername);
}

const QString &CPManager::blogPassword() const
{
    return CPEngine::instance().blogPassword();
}

void CPManager::setBlogPassword(const QString &blogPassword)
{
    CPEngine::instance().setBlogPassword(blogPassword);
}

const QString &CPManager::blogHtAccessUsername() const
{
    return CPEngine::instance().blogHtAccessUsername();
}

void CPManager::setBlogHtAccessUsername(const QString &blogHtAccessUsername)
{
    CPEngine::instance().setBlogHtAccessUsername(blogHtAccessUsername);
}

const QString &CPManager::blogHtAccessPassword() const
{
    return CPEngine::instance().blogHtAccessPassword();
}

void CPManager::setBlogHtAccessPassword(const QString &blogHtAccessPassword)
{
    CPEngine::instance().setBlogHtAccessPassword(blogHtAccessPassword);
}

void CPManager::clear()
{
    CPEngine::instance().setBlogId(QString());
    CPEngine::instance().setBlogName(QString());
    CPEngine::instance().setBlogUrl(QString());
    CPEngine::instance().setBlogRPCUrl(QString());
    CPEngine::instance().setBlogSanitizedUrl(QString());
    CPEngine::instance().setBlogUsername(QString());
    CPEngine::instance().setBlogPassword(QString());
}

#include "cpmanager.moc"
