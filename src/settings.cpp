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

#include "settings.h"

AppSettings::AppSettings(QObject *parent)
    :QObject(parent)
{
    check();
}

AppSettings::~AppSettings()
{

}

void AppSettings::check()
{
    QSettings settings("ShowStopper","CutePress");

    if(settings.value("Is_Get_Post_Comment_Count").toString().isEmpty()) {
        settings.setValue("Is_Get_Post_Comment_Count", false);
    }
}

void AppSettings::restoreDefault()
{
}

QString AppSettings::readData(QString key)
{
    QSettings settings("ShowStopper","CutePress");
    qDebug()<<"AppSettings---From settings---->Reading"<<key<<settings.value(key).toString();
    return settings.value(key).toString();
}

void AppSettings::saveData(QString key, QString value)
{
    QSettings settings("ShowStopper","CutePress");
    qDebug()<<"AppSettings---From settings---->Saving"<<key<<value;
    settings.setValue(key, value);
}

void AppSettings::saveData(QString key, int value)
{
    saveData(key, QString::number(value));
}
