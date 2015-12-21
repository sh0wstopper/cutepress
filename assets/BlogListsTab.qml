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
    function getNewRandomNumber() {
        return Math.floor((Math.random()*20)+1)
    }

    NavigationPane { 
        id: navigationPane
        onPopTransitionEnded: { page.destroy(); }
        Page {
            id: initialPage
            titleBar: ButtonTitleBar {
                titleText: qsTr("Blogs")
                defaultImgSource: Application.themeSupport.theme.colorTheme.style==VisualStyle.Bright?"asset:///images/toolbaradd-black.png":"asset:///images/toolbaradd.png"
                pressedImgSource: Application.themeSupport.theme.colorTheme.style==VisualStyle.Bright?"asset:///images/toolbaradd-black.png":"asset:///images/toolbaradd.png"
                onButtonClicked: {
                    mainWindow.openNewBlogSheet()
                }
                
            }
            actions: [
                ActionItem {
                    title: qsTr("Add blog")
                    imageSource: "asset:///images/add.png"
                    ActionBar.placement: ActionBarPlacement.Signature
                    onTriggered: {
                        mainWindow.openNewBlogSheet()
                    }
                },
                ActionItem {
                    title: qsTr("Refresh active blog")
                    enabled: cpUtil.blogs.size()>0
                    ActionBar.placement:ActionBarPlacement.InOverflow
                    onTriggered: {        
                        cpUtil.fetchRecentPosts();
                        cpUtil.fetchPages();
                        cpUtil.fetchComments();
                        cpUtil.fetchMediaItems();
                        cpUtil.fetchTags();
                        cpUtil.fetchCategories();
                    }
                },
                DeleteActionItem {
                    title: qsTr("Remove all blogs")
                    enabled: cpUtil.blogs.size()>0
                    onTriggered: {
                        mainWindow.openDialog(qsTr("Remove blogs"), 
                            qsTr("Remove all blogs?"), "blogs-remove",
                            "", "")
                    }
                }
            ]
            content: Container {
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill
                layout: DockLayout {}

                PageProgressStatusLabelSmall {
                    horizontalAlignment: HorizontalAlignment.Center
                    verticalAlignment: VerticalAlignment.Center
                    textStyle.base: SystemDefaults.TextStyles.BodyText
                    visible: cpUtil.blogs.size()==0
                    text: qsTr("<b>Currently no blogs added!</b>\nAdd new WordPress.com or self-hosted blog.")
                }
                
                CutePressListView {
                    id: iList
                    visible: cpUtil.blogs.size()>0
                    function activateBlog(iIndex) {
                        cpUtil.changeActiveBlog(iIndex)
                    }
                    
                    function removeBlog(iIndex) {
                        cpUtil.removeBlog(iIndex)                    
                    }
                    
                    dataModel: cpUtil.blogs
                    horizontalAlignment: HorizontalAlignment.Fill
                    verticalAlignment: VerticalAlignment.Fill
                    listItemComponents: [
                        ListItemComponent {
                            type: "item"
                            Container {
                                id: rootContainer
                                property bool isHighlighted: false
                                horizontalAlignment: HorizontalAlignment.Fill
                                verticalAlignment: VerticalAlignment.Fill
                                layout: DockLayout {
                                }
                                Container {
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    layout: StackLayout {
                                    }
                                    Container {
                                        leftPadding: ui.sdu(2)
                                        rightPadding: leftPadding
                                        topPadding: ui.sdu(0.8)
                                        horizontalAlignment: HorizontalAlignment.Fill
                                        verticalAlignment: VerticalAlignment.Fill
                                        layout: StackLayout {
                                        }
                                        Label {
                                            multiline: true
                                            textStyle {
                                                base: SystemDefaults.TextStyles.BodyText
                                                fontSize: FontSize.Small
                                                fontWeight: ListItemData.blogIsActive?FontWeight.Bold:FontWeight.Normal
                                            }
                                            textFormat: TextFormat.Html
                                            visible: text != ""
                                            text: ListItemData.blogName
                                        } // Label
                                        Label {
                                            textStyle {
                                                color: Color.Gray
                                                fontSize: FontSize.XSmall
                                            }
                                            visible: text != ""
                                            text: ListItemData.blogUrl
                                        } // Label
                                        HeadingText {
                                            textFormat: TextFormat.Html
                                            textStyle.fontWeight: FontWeight.Normal
                                            text: ListItemData.blogIsAdmin?qsTr("<b>%1</b> | Admin").arg(ListItemData.blogUsername):qsTr("<b>%1</b>").arg(ListItemData.blogUsername)
                                        }
                                    }
                                    Divider {
                                    }
                                }
                                Container {
                                    id: highlight
                                    background: Color.Gray
                                    opacity: (rootContainer.isHighlighted) ? 0.5 : 0.0
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    verticalAlignment: VerticalAlignment.Fill
                                }
                                
                                // Both the activation and selection of an item has the same visual appearance, we alter the opacity of the item.
                                function setHighlight(highlighted) {
                                    rootContainer.isHighlighted = highlighted
                                }
                                
                                // Signal handler for ListItem activation
                                ListItem.onActivationChanged: {
                                    setHighlight(ListItem.active);
                                }
                                
                                // Signal handler for ListItem selection
                                ListItem.onSelectionChanged: {
                                    setHighlight(ListItem.selected);
                                }
                                
                                contextActions: [
                                    ActionSet {
                                        id: cntxtMenu
                                        title: qsTr("Blog options")
                                        subtitle: ListItemData.blogName //"This is an action set."
                                        
                                        actions: [
                                            ActionItem {
                                                title: qsTr("Activate")
                                                imageSource: "asset:///images/done.png"
                                                onTriggered: {
                                                    if(!ListItemData.blogIsActive)
                                                        rootContainer.ListItem.view.activateBlog(ListItemData.blogUrl);
                                                }
                                            },
                                            InvokeActionItem {
                                                title: qsTr("Share")
                                                imageSource: "asset:///images/share.png"
                                                query {
                                                    mimeType: "text/plain"
                                                    invokeActionId: "bb.action.SHARE"
                                                }
                                                onTriggered: {
                                                    data = ListItemData.blogName+" " + ListItemData.blogUrl;
                                                }
                                            },
                                            ActionItem {
                                                title: qsTr("Copy link")
                                                imageSource: "asset:///images/copy_link.png"
                                                onTriggered: rootContainer.ListItem.view.copyToClipboard(ListItemData.blogUrl)
                                            },
                                            ActionItem {
                                                title: qsTr("Open in browser")
                                                imageSource: "asset:///images/open_link.png"
                                                onTriggered: rootContainer.ListItem.view.openLink(ListItemData.blogUrl)
                                            },
                                            DeleteActionItem {
                                                title: qsTr("Remove")
                                                imageSource: "asset:///images/delete.png"
                                                onTriggered: {
                                                    rootContainer.ListItem.view.openDialog(qsTr("Remove blog"), 
                                                    qsTr("Remove blog '%1'?").arg(ListItemData.blogName), "blog-remove",
                                                    ListItemData.index, "")
                                                }
                                            }
                                        ]
                                    } // end of ActionSet
                                ] // end of contextActions list
                            }
                        }
                    ]
//                    attachedObjects: [
//                        ListScrollStateHandler {
//                            id: scrollStateHandler
//                            onAtEndChanged: {
//                                if (scrollStateHandler.atEnd) {
//                                    //Load more
//                                }
//                            }
//                        }
//                    ]
                }
            } 
            shortcuts: [
                SystemShortcut {
                    type: SystemShortcuts.CreateNew
                    onTriggered: {               
                        mainWindow.openNewBlogSheet()
                    }
                }
            ]  
        }
    }
}


