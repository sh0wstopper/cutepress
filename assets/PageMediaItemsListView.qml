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
    property bool isOpenImageViewer: true
    signal flickedAtEnd()
    
    //    property string lastDeletedPostId: appBlog.lastDeletedPostId
    //    onLastDeletedPostIdChanged: {
    //        if(lastDeletedPostId!="")
    //        	appUtil.deletePostInModel(dataModel, lastDeletedPostId)
    //    }
    function openImageViewer(iUrl, name) {
        mainWindow.openImageViewer(iUrl, name)
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
                //                Container {
                //                    background: {
                //                        if(ListItemData.postPublishStatus=="private")
                //                        	return Color.Green
                //                        else if(ListItemData.postPublishStatus=="pending")
                //                            return Color.create("#FF8C00")
                //                        else if(ListItemData.postPublishStatus=="draft")
                //                            return Color.Yellow
                //                        else if(ListItemData.postPublishStatus=="future")
                //                            return Color.DarkCyan
                //                        else if(ListItemData.postPublishStatus=="trash")
                //                            return Color.Red
                //                    }
                //                    minWidth: 10
                //                    maxWidth: minWidth
                //                    horizontalAlignment: HorizontalAlignment.Right
                //                    verticalAlignment: VerticalAlignment.Fill
                //                }
                Container {
                    horizontalAlignment: HorizontalAlignment.Fill
                    layout: StackLayout {}
                    Container {
                        horizontalAlignment: HorizontalAlignment.Fill
                        topPadding: ui.sdu(0.8)
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
                                url: ListItemData.mediaThumbnail
                                scalingMethod: ScalingMethod.AspectFit
                                minWidth: 84
                                maxWidth: 150
                                maxHeight: 150
                                visible: url!=""
                            }
                                                        
                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill
                                leftPadding: thumb.status==WebImageView.Success?20:0
                                layout: StackLayout {}
                                Label {
                                    text: ListItemData.mediaTitle
                                    textStyle.fontWeight: FontWeight.Bold
                                    textFormat: TextFormat.Html
                                    multiline: true
                                    visible: text!=""
                                }
                                Label {
                                    text: ListItemData.mediaLink
                                    textFormat: TextFormat.Html
                                    textStyle.fontSize: FontSize.XSmall
                                    textStyle.color: Color.Gray
                                    multiline: true
                                    visible: text!=""
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
                            InvokeActionItem {
                                title: qsTr("Share")
                                imageSource: "asset:///images/share.png"
                                query {
                                    mimeType: "text/plain"
                                    invokeActionId: "bb.action.SHARE"
                                }
                                onTriggered: {
                                    data = ListItemData.mediaTitle+" " + ListItemData.mediaLink;
                                }
                            },
                            ActionItem {
                                title: qsTr("Copy link")
                                imageSource: "asset:///images/copy_link.png"
                                onTriggered: rootContainer.ListItem.view.copyToClipboard(ListItemData.mediaLink)
                            },
                            ActionItem {
                                title: qsTr("Open in browser")
                                imageSource: "asset:///images/open_link.png"
                                onTriggered: rootContainer.ListItem.view.openLink(ListItemData.mediaLink)
                            }
                        ]
                    } // end of ActionSet
                ] // end of contextActions list
            }
        }
    ]
    onTriggered: {
        //        mainWindow.openPost(dataModel.data(indexPath))
        if(isOpenImageViewer) {
            var currentItem = dataModel.data(indexPath)
            if(currentItem.mediaFileType=="jpg"||currentItem.mediaFileType=="jpeg"||currentItem.mediaFileType=="png"||currentItem.mediaFileType=="bmp")
                mainWindow.openImageViewer(currentItem.mediaLink,
                currentItem.mediaTitle,
                currentItem.mediaDescription,
                currentItem.mediaDisplayDate)
        }
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