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

#include <bb/cascades/Application>

#include <QLocale>
#include <QTranslator>
#include <QTimer>
#include "applicationui.hpp"
#include "WebImageView.h"
#include "cpmanager.h"
#include "cputil.h"
#include "cppost.h"
#include "cppage.h"
#include "apputil.h"
#include "settings.h"
#include <Qt/qdeclarativedebug.h>

using namespace bb::cascades;

Q_DECL_EXPORT int main(int argc, char **argv)
{
    Application app(argc, argv);

    qmlRegisterType<WebImageView>("com.cutepress.webimageview", 1, 0, "WebImageView");
    qmlRegisterType<RoleItemModel>("com.cutepress.roleitemmodel", 1, 0, "RoleItemModel");
    qmlRegisterType<CPManager>("com.cutepress.manager", 1, 0, "CPManager");
    qmlRegisterType<CPUtil>("com.cutepress.cputil", 1, 0, "CPUtil");
    qmlRegisterType<CPPost>("com.cutepress.post", 1, 0, "CutePressPost");
    qmlRegisterType<CPPage>("com.cutepress.page", 1, 0, "CutePressPage");
    qmlRegisterType<QTimer>("com.cutepress.timer", 1, 0, "Timer");
    qmlRegisterType<AppUtil>("com.cutepress.util", 1, 0, "AppUtil");
    qmlRegisterType<AppSettings>("com.cutepress.settings", 1, 0, "AppSettings");
    // Create the Application UI object, this is where the main.qml file
    // is loaded and the application scene is set.
    new ApplicationUI(&app);

    // Enter the application main event loop.
    return Application::exec();
}
