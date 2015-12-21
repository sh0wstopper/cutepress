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

TitleBar {
    signal labelClicked()
    signal buttonClicked()
    property alias titleText: heading.text
    property alias buttonEnabled: btn.enabled
    property alias defaultImgSource: btn.defaultImageSource
    property alias pressedImgSource: btn.pressedImageSource
    kind: TitleBarKind.FreeForm
    kindProperties: FreeFormTitleBarKindProperties {
        Container {
            horizontalAlignment: HorizontalAlignment.Fill
            layout: StackLayout { orientation: LayoutOrientation.LeftToRight }
            leftPadding: ui.sdu(2)
            rightPadding: ui.sdu(1)
            Label {
                id: heading
                textStyle {
                    base: SystemDefaults.TextStyles.TitleText
                }
                multiline: false
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Center
                textFormat: TextFormat.Html
                layoutProperties: StackLayoutProperties { spaceQuota: 1 }
                onTouch: {
                    labelClicked()
                }
            }
            ImageButton {
                id: btn
                verticalAlignment: VerticalAlignment.Center
                horizontalAlignment: HorizontalAlignment.Right
                onClicked: {                     
                    buttonClicked()
                }
            }
        }
    }
}