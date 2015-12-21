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

import bb.cascades 1.3

Page {
    id: page
    titleBar: TitleBar {
        title: qsTr("Privacy Policy")
    }
    content: ScrollView {
        horizontalAlignment: HorizontalAlignment.Fill
        verticalAlignment: VerticalAlignment.Fill
        scrollViewProperties.scrollMode: ScrollMode.Vertical
        content: Container {
            topPadding: ui.sdu(2)
            bottomPadding: topPadding
            leftPadding: ui.sdu(2)
            rightPadding: leftPadding
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Fill
            layout: StackLayout {
            }
            Label {
                multiline: true
                textFormat: TextFormat.Html
                text: qsTr("CutePress lets you connect you to your WordPress blog.<br/><br/>") + qsTr("==Information Collection and Use==<br/>") + qsTr("Information collected by CutePress is stored through database and settings mechanism. User blogs data is stored in '<i>cutepress.sqlite</i>' database file which can be found application's <b>data</b> directory while login details for user blogs can be stored through settings mechanism provided by the host operating system.<br/>") + qsTr("Rest all  details related with blog viewed in the application are fetched from the Internet at the time of display.<br/><br/>") + qsTr("For WordPress.com privacy policy visit <a href='http://automattic.com/privacy/'>automattic.com/privacy/</a>")
            } 
        }    
    }
}
