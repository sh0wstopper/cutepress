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
import com.cutepress.webimageview 1.0

CutePressListView {
    id: iList
    signal flickedAtEnd()
    
    horizontalAlignment: HorizontalAlignment.Fill
    verticalAlignment: VerticalAlignment.Fill
    
    listItemComponents: [
        ListItemComponent {
            id: listComponent
            type: "item"
            Container {
                id: rootContainer
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill
                property bool isHighlighted
                
                layout: DockLayout {
                }
                Container {
                    background: {
                        if(ListItemData.postDisplayStatus=="private")
                        	return Color.Green
                        else if(ListItemData.postDisplayStatus=="pending")
                            return Color.create("#FF8C00")
                        else if(ListItemData.postDisplayStatus=="draft")
                            return Color.Yellow
                        else if(ListItemData.postDisplayStatus=="localdraft")
                            return Color.DarkYellow
                        else if(ListItemData.postDisplayStatus=="future")
                            return Color.DarkCyan
                        else if(ListItemData.postDisplayStatus=="trash")
                            return Color.Red
                    }
                    minWidth: 10
                    maxWidth: minWidth
                    horizontalAlignment: HorizontalAlignment.Left
                    verticalAlignment: VerticalAlignment.Fill
                }
                Container {
                    horizontalAlignment: HorizontalAlignment.Fill
                    layout: StackLayout {}
                    Container {
                        horizontalAlignment: HorizontalAlignment.Fill
                        leftPadding: ui.sdu(2)
                        rightPadding: leftPadding
                        layout: StackLayout {}
                        Container {
                            horizontalAlignment: HorizontalAlignment.Fill
                            topPadding: ui.sdu(0.8)
                            bottomPadding: ui.sdu(1)
                            layout: DockLayout {}
                            Container {
                                rightPadding: ListItemData.postCommentsCount>0?75:0
                                Label {
                                    text: ListItemData.postTitle
                                    textStyle.fontWeight: FontWeight.Bold
                                    textFormat: TextFormat.Html
                                    multiline: true
                                }
                                Label {
                                    text: ListItemData.postContentSnippet
                                    multiline: true
                                    visible: text!=""
                                    autoSize.maxLineCount: 3//ListItemData.postFeaturedImage!=""?4:2
                                    textStyle.fontWeight: FontWeight.W400
                                    textStyle.fontSize: FontSize.Small
                                    textFormat: TextFormat.Html
                                }
                            }
                            ControlDelegate {
                                horizontalAlignment: HorizontalAlignment.Right
                                verticalAlignment: VerticalAlignment.Top
                                delegateActive: ListItemData.postCommentsCount>0
                                sourceComponent: ComponentDefinition {                                    
                                    Container {
                                        topPadding: ui.sdu(0.8)
                                        Label {
                                            text: ListItemData.postCommentsCount>999?"999+":ListItemData.postCommentsCount
                                            textStyle.color: Color.DarkGray
                                            textStyle.fontSize: FontSize.XSmall
                                            textStyle.fontWeight: FontWeight.Bold
                                            textFormat: TextFormat.Html
                                            visible: text!=""
                                        }
                                    }
                                }
                            }
                        }
		                Container {
                      		horizontalAlignment: HorizontalAlignment.Fill
                      		topPadding: ui.sdu(1.2)
                      		layout: DockLayout {}
                          	Container {
                                  rightPadding: ListItemData.postPassword!=""?35:0
			                    Label {
                                    text: qsTr("<em>%1</em> | %2").arg(ListItemData.postWpAuthorDisplayName).arg(ListItemData.postDisplayDate)
			//                        textStyle.fontStyle: FontStyle.Italic
			                        textStyle.color: Color.Gray
			                        textStyle.fontSize: FontSize.XSmall
			                        textFormat: TextFormat.Html
	                            }
                            }
	                        ControlDelegate {
	                            horizontalAlignment: HorizontalAlignment.Right
	                            verticalAlignment: VerticalAlignment.Center
	                            delegateActive: ListItemData.postPassword!=""  
	                            sourceComponent: ComponentDefinition {
	                                ImageView {
	                                    imageSource: "asset:///images/lock.png"
	                                }
	                            }
	                        }
                        }
                    }
                    Divider {}
                }
                
                // A colored Container is used to highlight the item on selection.
                Container {
                    id: highlight
                    background: Color.Gray
                    opacity: rootContainer.isHighlighted? 0.8: 0.0
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
                        title: qsTr("Post options")
                        subtitle: ListItemData.postTitle //"This is an action set."
                        
                        actions: [
//                            ActionItem {
//                                title: qsTr("View details")
//                                imageSource: "asset:///images/details.png"
//                                onTriggered: {
//                                    rootContainer.ListItem.view.openPhotoDetails(rootContainer.ListItem.view.dataModel, rootContainer.ListItem.indexPath);
//                                }
//                            }
                            ActionItem {
                                title: qsTr("Edit")
//                                enabled: rootContainer.ListItem.view.isUserAuthorized && ListItemData.postBlogId == rootContainer.ListItem.view.appBlogId
                                imageSource: "asset:///images/edit.png"
                                onTriggered: {
                                    rootContainer.ListItem.view.openEditPostEditor(rootContainer.ListItem.view.dataModel.data(rootContainer.ListItem.indexPath));
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
                                    data = ListItemData.postTitle+" " + ListItemData.postLink;
                                }
                            },
                            ActionItem {
                                title: qsTr("Copy link")
                                imageSource: "asset:///images/copy_link.png"
                                onTriggered: rootContainer.ListItem.view.copyToClipboard(ListItemData.postLink)
                            },
                            ActionItem {
                                title: qsTr("Open in browser")
                                imageSource: "asset:///images/open_link.png"
                                onTriggered: rootContainer.ListItem.view.openLink(ListItemData.postLink)
                            },
                            DeleteActionItem {
                                title: qsTr("Delete")
//                                enabled: rootContainer.ListItem.view.isUserAuthorized && ListItemData.postBlogId == rootContainer.ListItem.view.appBlogId
                                imageSource: "asset:///images/delete.png"
                                onTriggered: {
                                    rootContainer.ListItem.view.openDialog(qsTr("Delete post"), 
                                        qsTr("Delete post '%1'?").arg(ListItemData.postTitle), "post-delete",
                                        ListItemData.postId, "")
                                }
                            }
                        ]
                    } // end of ActionSet
                ] // end of contextActions list
            }
        }
    ]
    onTriggered: {
        mainWindow.openPost(dataModel.data(indexPath))
    }
    attachedObjects: [
        ListScrollStateHandler {
            id: scrollStateHandler
            onAtEndChanged: {
                if (scrollStateHandler.atEnd) {
                    iList.flickedAtEnd();
                }
            }
        }
    ]
}