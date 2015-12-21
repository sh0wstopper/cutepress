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

#ifndef SETTINGS_H
#define SETTINGS_H
#include <QString>
#include <QStringList>
#include <QSettings>
#include <QDebug>
#include "roleitemmodel.h"
#include "common.h"


/** An item. */
class AppSettings: public QObject {
    Q_OBJECT

public:
    /** Default constructor. */
    AppSettings(QObject *parent = 0);

    /** Destructor. */
    ~AppSettings();

public slots:
    void check();
    QString readData(QString key);
    void saveData(QString key, QString value);
    void saveData(QString key, int value);
    void restoreDefault();

protected:
};

#endif // SETTINGS_H