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

CutePressCommentsListView {
    id: iList
    signal flickedAtEnd()
    
    function updateModel() {
        cpUtil.commentsChanged()
    }
    
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
                        if(ListItemData.commentStatus=="hold")
                            return Color.create("#FF8C00")
                        else if(ListItemData.commentStatus=="spam")
                            return Color.DarkRed
                        else if(ListItemData.commentStatus=="trash")
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
                        topPadding: ui.sdu(1)
                        leftPadding: ui.sdu(2)
                        rightPadding: leftPadding
                        layout: StackLayout {}
                        
                        Container {
                            horizontalAlignment: HorizontalAlignment.Fill
                            layout: StackLayout {
                                orientation: LayoutOrientation.LeftToRight
                            }
                            WebImageView {
                                id: thumb
                                url: ListItemData.commentAuthorAvatarUrl
                                minWidth: 100
                                maxWidth: 100
                                scalingMethod: ScalingMethod.AspectFit
                            }
                            
                            
                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill
                                leftPadding: thumb.status==WebImageView.Success?20:0
                                layout: StackLayout {}
                                
                                Label {
                                    text: ListItemData.commentAuthorName
                                    textStyle.fontWeight: FontWeight.Bold
                                    //                            textFormat: TextFormat.Html
                                }
                                Label {
                                    text: ListItemData.commentDate
                                    textStyle.color: Color.Gray
                                    textStyle.fontSize: FontSize.XSmall
                                }
                            }
                        }
                        Label {
                            text: ListItemData.commentPostTitle
                            textStyle.color: Color.Gray
                            textStyle.fontSize: FontSize.XSmall
                        }
                        Label {
                            text: ListItemData.commentContent
                            multiline: true
                            textStyle.fontWeight: FontWeight.W400
                            textStyle.fontSize: FontSize.Small
                            textFormat: TextFormat.Html
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
                        title: qsTr("Comment options")
                        subtitle: ListItemData.commentId //"This is an action set."
                        
                        actions: [
                            ActionItem {
                                title: ListItemData.commentStatus=="approve"?qsTr("Unapprove"):qsTr("Approve")
                                imageSource: ListItemData.commentStatus=="approve"?"asset:///images/unapprove.png":"asset:///images/approve.png"
                                //                                enabled: ListItemData.commentStatus=="approve" || ListItemData.commentStatus=="unapprove"
                                onTriggered: {
                                    if(ListItemData.commentStatus=="approve")
                                        rootContainer.ListItem.view.unapproveComment(ListItemData.commentId);
                                    else
                                        rootContainer.ListItem.view.approveComment(ListItemData.commentId);
                                }
                            },
                            ActionItem {
                                title: qsTr("Spam")
                                imageSource: "asset:///images/spam.png"
                                enabled: ListItemData.commentStatus!="spam"
                                onTriggered: {
                                    rootContainer.ListItem.view.spamComment(ListItemData.commentId);
                                }
                            },
//                            ActionItem {
//                                title: qsTr("Edit")
//                                enabled: rootContainer.ListItem.view.isUserAuthorized && ListItemData.photoUserId == rootContainer.ListItem.view.appUserId
//                                imageSource: "asset:///images/edit.png"
//                                onTriggered: {
//                                    rootContainer.ListItem.view.openPhotoEditor(ListItemData.photoId, ListItemData.photoName, ListItemData.photoDescription, ListItemData.photoThumbUrl);
//                                }
//                            },
                            InvokeActionItem {
                                title: qsTr("Share")
                                imageSource: "asset:///images/share.png"
                                query {
                                    mimeType: "text/plain"
                                    invokeActionId: "bb.action.SHARE"
                                }
                                onTriggered: {
                                    data = ListItemData.commentShortUrl;
                                }
                            },
                            ActionItem {
                                title: qsTr("Copy link")
                                imageSource: "asset:///images/copy_link.png"
                                onTriggered: rootContainer.ListItem.view.copyToClipboard(ListItemData.commentLink)
                            },
                            ActionItem {
                                title: qsTr("Open in browser")
                                imageSource: "asset:///images/open_link.png"
                                onTriggered: rootContainer.ListItem.view.openLink(ListItemData.commentLink)
                            },
                            DeleteActionItem {
                                title: qsTr("Delete")
//                                enabled: rootContainer.ListItem.view.isUserAuthorized //&& ListItemData.photoUserId == rootContainer.ListItem.view.appUserId
                                imageSource: "asset:///images/delete.png"
                                onTriggered: {
                                    rootContainer.ListItem.view.deleteComment(ListItemData.commentId)
                                }
                            }
                        ]
                    } // end of ActionSet
                ] // end of contextActions list
            }
        }
    ]
    onTriggered: {
//        mainWindow.openComment(dataModel.data(indexPath))
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