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
        if(mainWindow.activeTab==postsTab )
            iList.scrollToTop();
        else {
//            if(oauth.isAuthorized) {
//                if(cpUtil.postsState==UI.ProgressState.None || cpUtil.postsState==UI.ProgressState.Error) {
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
                        cpUtil.fetchRecentPosts()
                    }
                    ActionBar.placement: ActionBarPlacement.InOverflow
                },
                ActionItem {
                    title: qsTr("Tags")
                    imageSource: "asset:///images/tags.png"
//                    enabled: oauth.state==OAuth.Authorized
                    onTriggered: {
                        mainWindow.openTagsPage()
                    }
                    ActionBar.placement: ActionBarPlacement.InOverflow
                }//,
//                ActionItem {
//                    title: qsTr("Test")
//                    onTriggered: {
//                        cpUtil.testSlot()
//                    }
//                    ActionBar.placement: ActionBarPlacement.InOverflow
//                }
            ]
            titleBar: ButtonTitleBar {
                titleText: qsTr("Posts")//qsTr("%1::Posts").arg(cpUtil.name==""?oauth.blogId:cpUtil.name)
                defaultImgSource: Application.themeSupport.theme.colorTheme.style==VisualStyle.Bright?"asset:///images/toolbarcompose-black.png":"asset:///images/toolbarcompose.png"
                pressedImgSource: Application.themeSupport.theme.colorTheme.style==VisualStyle.Bright?"asset:///images/toolbarcompose-black.png":"asset:///images/toolbarcompose.png"
                buttonEnabled: cpUtil.blogs.size()>0
                onButtonClicked: {
                    mainWindow.openNewPostEditor()
                }
            }
            content: Container {
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill
                layout: StackLayout {}
                
                PageStatusContainer {
                    visible: cpUtil.postsState==UI.ProgressState.Processing || cpUtil.postsState==UI.ProgressState.Processing || cpUtil.postsState == UI.ProgressState.Error || (cpUtil.postsState == UI.ProgressState.Success && cpUtil.posts.size() == 0)
                    indicatorVisible: cpUtil.postsState==UI.ProgressState.Processing
                    labelVisible: cpUtil.postsState == UI.ProgressState.Error || (cpUtil.postsState == UI.ProgressState.Success && cpUtil.posts.size() == 0)
                    labelText: cpUtil.postsStatus
                }

                PagePostsListView {
                    id: iList
                    dataModel: cpUtil.posts
                    onFlickedAtEnd: {
                    }
                }
//                ActivityIndicatorLarge {
//                    visible: cpUtil.posts.size() == 0 && cpUtil.postsState==UI.ProgressState.Processing
//                }
//                PageProgressStatusLabel {
//                    visible: cpUtil.postsState == UI.ProgressState.Error || (cpUtil.postsState == UI.ProgressState.Success && cpUtil.posts.size() == 0)
//                    text: (cpUtil.postsState == UI.ProgressState.Success && cpUtil.posts.size() == 0) ? qsTr("No posts") : cpUtil.postsStatus
//                }
            } 
            shortcuts: [
                SystemShortcut {
                    type: SystemShortcuts.CreateNew
                    enabled: cpUtil.blogs.size()>0
                    onTriggered: {               
                        mainWindow.openNewPostEditor()
                    }
                }
            ]  
            onCreationCompleted: {
//                if(oauth.isAuthorized) {
//                    if(cpUtil.postsState==UI.ProgressState.None || cpUtil.postsState==UI.ProgressState.Error) {
//                        cpUtil.fetchPosts()
//                    }
//                }
            }                  
        }
    }
}
