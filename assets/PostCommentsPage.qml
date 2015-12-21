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
    id: initialPage
    property variant post: 0
    property string newlyAddedCommentId: post.newCommentId
    onNewlyAddedCommentIdChanged: {
        if(newlyAddedCommentId!="" || newlyAddedCommentId!=undefined) {
            cpUtil.fetchComment(newlyAddedCommentId)
        }
    }
    
    attachedObjects: [
        Sheet {
            id: iSheet
            property string newCommentParent: "0"
            property int iState: post.addCommentState
            onIStateChanged: {
                if(iState==UI.ProgressState.Success)
                    iSheet.close()
            }
            function clearText() {
                commentInput.text = "";
            }
            onOpened: {
                commentInput.requestFocus();
            }
            content: Page {
                titleBar: TitleBar {
                    title: qsTr("New comment")
                    dismissAction: ActionItem {
                        title: qsTr("Cancel")
                        enabled: iSheet.iState!=UI.ProgressState.Processing
                        onTriggered: {
                            iSheet.close()
                        }
                    } // ActionItem
                    acceptAction: ActionItem {
                        title: qsTr("Ok")
                        enabled: iSheet.iState!=UI.ProgressState.Processing
                        onTriggered: {
                            post.addComment(commentInput.text)
//                            iSheet.close()
                        }
                    } // ActionItem
                }
                content: Container {
                    horizontalAlignment: HorizontalAlignment.Fill
                    verticalAlignment: VerticalAlignment.Fill
                    layout: StackLayout {
                    }
                    EditorStatusElement {
                        parentObject: iSheet
                    }
                    ScrollView {
                        horizontalAlignment: HorizontalAlignment.Fill
                        Container {
                            topPadding: ui.sdu(2)
                            bottomPadding: topPadding
                            leftPadding: topPadding
                            rightPadding: topPadding
                            horizontalAlignment: HorizontalAlignment.Fill
                            layout: StackLayout {
                            }
                            TextArea {
                                id: commentInput
                                minHeight: 240
                                horizontalAlignment: HorizontalAlignment.Fill
                                verticalAlignment: VerticalAlignment.Fill
                            }
                        }
                    }
                }
            }
        }
    ]
    actions: [
        ActionItem {
            title: qsTr("New comment")
            imageSource: "asset:///images/edit.png"
            onTriggered: {
                iSheet.newCommentParent = "0"
                iSheet.open()
            }
            ActionBar.placement: ActionBarPlacement.OnBar
        },
        ActionItem {
            title: qsTr("Refresh")
            imageSource: "asset:///images/refresh.png"
            onTriggered: {
                post.fetchComments()
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
            visible: post.commentsState==UI.ProgressState.Processing || cpUtil.commentsState == UI.ProgressState.Error || post.commentsState == UI.ProgressState.Error || (post.commentsState == UI.ProgressState.Success && post.comments.size() == 0)
            indicatorVisible: post.commentsState==UI.ProgressState.Processing
            labelVisible: post.commentsState == UI.ProgressState.Error || (post.commentsState == UI.ProgressState.Success && post.comments.size() == 0)
            labelText: (post.commentsState == UI.ProgressState.Success && post.comments.size() == 0) ? qsTr("No comments") : post.commentsStatus
        }
        
        PageCommentsListView {
            id: iList
            dataModel: post.comments
        }
    }   
    onCreationCompleted: {
    }            
}
