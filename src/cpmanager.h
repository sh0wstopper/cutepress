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

#ifndef CPMANAGER_H
#define CPMANAGER_H

#include <QObject>
#include <QDebug>
#include <QUrl>
#include <QDateTime>

class CPManager : public QObject
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
    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY errorMessageChanged)
public:

    explicit CPManager(QObject *parent = 0);

    const QString &blogId() const;
    const QString &blogName() const;
    const QString &blogUrl() const;
    const QString &blogRPCUrl() const;
    const QString &blogSanitizedUrl() const;
    const QString &blogUsername() const;
    const QString &blogPassword() const;
    const QString &blogHtAccessUsername() const;
    const QString &blogHtAccessPassword() const;
    void setBlogId(const QString &blogId);
    void setBlogName(const QString &blogName);
    void setBlogUrl(const QString &blogUrl);
    void setBlogRPCUrl(const QString &blogRPCUrl);
    void setBlogSanitizedUrl(const QString &blogSanitizedUrl);
    void setBlogUsername(const QString &blogUsername);
    void setBlogPassword(const QString &blogPassword);
    void setBlogHtAccessUsername(const QString &blogHtAccessUsername);
    void setBlogHtAccessPassword(const QString &blogHtAccessPassword);

    QString errorMessage() { return _errorMessage; }
    void setErrorMessage(const QString &errorMessage) { _errorMessage = errorMessage; emit errorMessageChanged(_errorMessage); }

public slots:
    void clear();

signals:
    void blogIdChanged(const QString &blogId);
    void blogNameChanged(const QString &blogName);
    void blogUrlChanged(const QString &blogUrl);
    void blogRPCUrlChanged(const QString &blogRPCUrl);
    void blogSanitizedUrlChanged(const QString &blogSanitizedUrl);
    void blogUsernameChanged(const QString &blogUsername);
    void blogPasswordChanged(const QString &blogPassword);
    void blogHtAccessUsernameChanged(const QString &blogHtAccessUsername);
    void blogHtAccessPasswordChanged(const QString &blogHtAccessPassword);
    void errorMessageChanged(const QString &errorMessage);
    void openUrl();

private:
    QString _errorMessage;
    class Private;
    Private *d;
};

#endif // CPMANAGER_H
