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
        title: qsTr("About")
    }
    content: ScrollView {
        scrollViewProperties.scrollMode: ScrollMode.Vertical
        content: Container {
            topPadding: ui.sdu(5)
            leftPadding: ui.sdu(2)
            rightPadding: leftPadding
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Fill
            layout: StackLayout {
            }
            ImageView {
                horizontalAlignment: HorizontalAlignment.Center
                imageSource: "asset:///images/CutePress-logo.png"
            }
            Label {
                text: qsTr("CutePress")
                textStyle.base: SystemDefaults.TextStyles.BigText
                textStyle.textAlign: TextAlign.Center
                horizontalAlignment: HorizontalAlignment.Center
            }
            Label {
                multiline: true
                textFormat: TextFormat.Html
                textStyle.textAlign: TextAlign.Center
                text: qsTr("Developed by Abhishek Kumar.<br/>Copyright© 2014 Abhishek Kumar.")
                horizontalAlignment: HorizontalAlignment.Center
            }
            Label {
                multiline: true
                textFormat: TextFormat.Html
                textStyle.textAlign: TextAlign.Center
                textStyle.color: Color.DarkGray
                text: qsTr("For suggestions and queries contact <a href='mailto:abhishek.mrt22@gmail.com'>abhishek.mrt22@gmail.com</a>")
                horizontalAlignment: HorizontalAlignment.Center
            } // Label
        }
    }
}
