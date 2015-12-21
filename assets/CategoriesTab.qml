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
        if(mainWindow.activeTab==categoriesTab )
            iList.scrollToTop();
        else {
            //            if(oauth.isAuthorized) {
            //                if(cpUtil.categoriesState==UI.ProgressState.None || cpUtil.categoriesState==UI.ProgressState.Error) {
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
                        cpUtil.fetchCategories()
                    }
                    ActionBar.placement: ActionBarPlacement.InOverflow
                }
            ]
            titleBar: ButtonTitleBar {
                titleText: qsTr("Categories")//qsTr("%1::Posts").arg(cpUtil.name==""?oauth.blogId:cpUtil.name)
                defaultImgSource: Application.themeSupport.theme.colorTheme.style==VisualStyle.Bright?"asset:///images/toolbaradd-black.png":"asset:///images/toolbaradd.png"
                pressedImgSource: Application.themeSupport.theme.colorTheme.style==VisualStyle.Bright?"asset:///images/toolbaradd-black.png":"asset:///images/toolbaradd.png"
                buttonEnabled: cpUtil.blogs.size()>0
                onButtonClicked: {
                    mainWindow.openNewCategoryEditor()
                }
            }
            content: Container {
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill
                layout: StackLayout {}
                
                PageStatusContainer {
                    visible: cpUtil.categoriesState==UI.ProgressState.Processing || cpUtil.categoriesState == UI.ProgressState.Error || (cpUtil.categoriesState == UI.ProgressState.Success && cpUtil.categories.size() == 0)
                    indicatorVisible: cpUtil.categoriesState==UI.ProgressState.Processing
                    labelVisible: cpUtil.categoriesState == UI.ProgressState.Error || (cpUtil.categoriesState == UI.ProgressState.Success && cpUtil.categories.size() == 0)
                    labelText: (cpUtil.categoriesState == UI.ProgressState.Success && cpUtil.categories.size() == 0) ? qsTr("No categories") : cpUtil.categoriesStatus
                }
                
                PageCategoriesListView {
                    id: iList
                    dataModel: cpUtil.categories
                    onFlickedAtEnd: {
                    }
                }
                ActivityIndicatorLarge {
                    visible: cpUtil.categories.size() == 0 && cpUtil.categoriesState==UI.ProgressState.Processing
                }
                PageProgressStatusLabel {
                    visible: cpUtil.categoriesState == UI.ProgressState.Error || (cpUtil.categoriesState == UI.ProgressState.Success && cpUtil.categories.size() == 0)
                    text: (cpUtil.categoriesState == UI.ProgressState.Success && cpUtil.categories.size() == 0) ? qsTr("No categories") : cpUtil.categoriesStatus
                }
            } 
            shortcuts: [
                SystemShortcut {
                    type: SystemShortcuts.CreateNew
                    enabled: cpUtil.blogs.size()>0
                    onTriggered: {               
                        mainWindow.openNewCategoryEditor()
                    }
                }
            ] 
            onCreationCompleted: {
                //                if(oauth.isAuthorized) {
                //                    if(cpUtil.categoriesState==UI.ProgressState.None || cpUtil.categoriesState==UI.ProgressState.Error) {
                //                        cpUtil.fetchPosts()
                //                    }
                //                }
            }                  
        }
    }
}
