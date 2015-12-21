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

Page {
    
    actions: [
        ActionItem {
            title: qsTr("Refresh")
            imageSource: "asset:///images/refresh.png"
//            enabled: oauth.state==OAuth.Authorized
            onTriggered: {
                cpUtil.fetchTags()
            }
            ActionBar.placement: ActionBarPlacement.InOverflow
        }
    ]
    titleBar: TitleBar {
        title: qsTr("Tags")
    }
    content: Container {
        horizontalAlignment: HorizontalAlignment.Fill
        verticalAlignment: VerticalAlignment.Fill
        layout: DockLayout {}
        
        PageTagsListView {
            id: iList
            dataModel: cpUtil.tags
        }
        ActivityIndicatorLarge {
            visible: cpUtil.tags.size() == 0 && cpUtil.tagsState==UI.ProgressState.Processing
        }
        PageProgressStatusLabel {
            visible: cpUtil.tagsState == UI.ProgressState.Error || (cpUtil.tagsState == UI.ProgressState.Success && cpUtil.tags.size() == 0)
            text: (cpUtil.tagsState == UI.ProgressState.Success && cpUtil.tags.size() == 0) ? qsTr("No tags") : cpUtil.tagsStatus
        }
    } 
    onCreationCompleted: {}                  
}
