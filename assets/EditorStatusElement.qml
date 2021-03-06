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
import "UIConstants.js" as UI

Container {
    property variant parentObject: 0
    horizontalAlignment: HorizontalAlignment.Fill
    topPadding: ui.sdu(2)
    bottomPadding: topPadding
    leftPadding: topPadding
    rightPadding: topPadding
    visible: parentObject.iState === UI.ProgressState.Processing || parentObject.iState === UI.ProgressState.Error
    layout: StackLayout {
    }

    ActivityIndicatorSmall {
        running: visible
        visible: parentObject.iState === UI.ProgressState.Processing
        horizontalAlignment: HorizontalAlignment.Center
    }

    Label {
        id: statusLabel
        horizontalAlignment: HorizontalAlignment.Fill
        visible: text != "" && parentObject.iState === UI.ProgressState.Error
        text: parentObject.iStatus
        multiline: true
        textFormat: TextFormat.Html
        textStyle {
            color: Color.Red
            textAlign: TextAlign.Center
            fontWeight: FontWeight.W300
        }
    }
}
