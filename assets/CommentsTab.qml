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

Tab {
    id: iTab
    property alias initialContent: initialPage.content
    property alias initialActions: initialPage.actions
    function push(iPage) {
        navigationPane.push(iPage)
    }
    function pop(iPage) {
        navigationPane.pop(iPage)
    }
    function count() {
        return navigationPane.count()
    }
    function top() {
        return navigationPane.top
    }
    function navigateToFirst() {
        navigationPane.navigateTo(navigationPane.at(0))
    }
    onTriggered: {
        if(mainWindow.activeTab==commentsTab )
            iList.scrollToTop();
        else {
            //            if(oauth.isAuthorized) {
            //                if(cpUtil.commentsState==UI.ProgressState.None || cpUtil.commentsState==UI.ProgressState.Error) {
            //                    cpUtil.fetchPosts()
            //                }
            //            }
        } 
    }
    NavigationPane { 
        id: navigationPane
        onTopChanged: {
            //            if (count() == 1 && oauth.state == OAuth.UserAuthorizes) oauth.unauthorize();
        }
        onPopTransitionEnded: { page.destroy(); }
        Page {
            id: initialPage
            
            actions: [
                ActionItem {
                    title: qsTr("Refresh")
                    imageSource: "asset:///images/refresh.png"
                    //                    enabled: oauth.state==OAuth.Authorized
                    onTriggered: {
                        cpUtil.fetchComments()
                    }
                    ActionBar.placement: ActionBarPlacement.InOverflow
                }
            ]
            titleBar: TitleBar {
                title: qsTr("Comments")
            }
            content: Container {
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill
                layout: StackLayout {}
                
                PageStatusContainer {
                    visible: cpUtil.commentsState==UI.ProgressState.Processing || cpUtil.commentsState == UI.ProgressState.Error || (cpUtil.commentsState == UI.ProgressState.Success && cpUtil.comments.size() == 0)
                    indicatorVisible: cpUtil.commentsState==UI.ProgressState.Processing
                    labelVisible: cpUtil.commentsState == UI.ProgressState.Error || (cpUtil.commentsState == UI.ProgressState.Success && cpUtil.comments.size() == 0)
                    labelText: (cpUtil.commentsState == UI.ProgressState.Success && cpUtil.comments.size() == 0) ? qsTr("No comments") : cpUtil.commentsStatus
                }
                
                PageCommentsListView {
                    id: iList
                    dataModel: cpUtil.comments
                    onFlickedAtEnd: {
                    }
                }
//                ActivityIndicatorLarge {
//                    visible: cpUtil.comments.size() == 0 && cpUtil.commentsState==UI.ProgressState.Processing
//                }
//                PageProgressStatusLabel {
//                    visible: cpUtil.commentsState == UI.ProgressState.Error || (cpUtil.commentsState == UI.ProgressState.Success && cpUtil.comments.size() == 0)
//                    text: (cpUtil.commentsState == UI.ProgressState.Success && cpUtil.comments.size() == 0) ? qsTr("No comments") : cpUtil.commentsStatus
//                }
            } 
            onCreationCompleted: {
                //                if(oauth.isAuthorized) {
                //                    if(cpUtil.commentsState==UI.ProgressState.None || cpUtil.commentsState==UI.ProgressState.Error) {
                //                        cpUtil.fetchPosts()
                //                    }
                //                }
            }                  
        }
    }
}
