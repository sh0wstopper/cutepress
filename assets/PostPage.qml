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
import com.cutepress.post 1.0
import "UIConstants.js" as UI

Page {
    id: page
    
    function setPostInfo(iPost) {
        post.setInfo(iPost)
    }
    
    actions: [
        ActionItem {
            title: qsTr("Comments")
            imageSource: "asset:///images/comment.png"
            onTriggered: {
                if(post.commentsState!=UI.ProgressState.Success)
                    post.fetchComments()
                var nPage = postCommentsPageDefinition.createObject()
                nPage.post = post
                mainWindow.push(nPage)
            }
            ActionBar.placement: ActionBarPlacement.OnBar
            attachedObjects: [
                ComponentDefinition {
                    id: postCommentsPageDefinition
                    source: "PostCommentsPage.qml"
                }
            ]
        },
        ActionItem {
            title: qsTr("Edit")
            imageSource: "asset:///images/edit.png"
            onTriggered: {
//                mainWindow.pop()
                mainWindow.openEditPostEditorUsingObject(post)
            }
            ActionBar.placement: ActionBarPlacement.OnBar
        },
        ActionItem {
            title: qsTr("Reload")
            imageSource: "asset:///images/refresh.png"
            onTriggered: {
                post.fetchInfo()
            }
            ActionBar.placement: ActionBarPlacement.InOverflow
        },
//        ActionItem {
//            title: qsTr("Debug")
//            onTriggered: {
//                var nPage = postObjectDebugPageDefinition.createObject()
//                nPage.post = post
//                mainWindow.push(nPage)
//            }
//            ActionBar.placement: ActionBarPlacement.InOverflow
//            attachedObjects: [
//                ComponentDefinition {
//                    id: postObjectDebugPageDefinition
//                    source: "PostObjectDebugPage.qml"
//                }
//            ]
//        },
        InvokeActionItem {
            title: qsTr("Share")
            imageSource: "asset:///images/share.png"
            query {
                mimeType: "text/plain"
                invokeActionId: "bb.action.SHARE"
            }
            onTriggered: {
                data = post.title + " " + post.url + " by " + post.authorName;
            }
            ActionBar.placement: ActionBarPlacement.OnBar
        },
        ActionItem {
            title: qsTr("Copy link")
            imageSource: "asset:///images/copy_link.png"
            onTriggered: appUtil.copyTextToClipboard(post.url)
        },
        ActionItem {
            title: qsTr("Open in web browser")
            imageSource: "asset:///images/open_link.png"
            onTriggered: {
                appUtil.launchBrowser(post.url)
            }
        },
        DeleteActionItem {
            title: qsTr("Delete")
            onTriggered: {
                mainWindow.openDialog(qsTr("Delete post"), 
                    qsTr("Delete post '%1'?").arg(post.title), "post-delete",
                    post.cpId, "pop")
            }
        }
    ]
    attachedObjects: [
        CutePressPost {
            id: post
            onCpIdChanged: {
//                fetchInfo()
            }
            onPostRefreshed: {
                cpUtil.updatePostInfoFromPostPage(cpId, newPost)
            }
            onInfoMessageChanged: {
                if(infoMessage!="")
                	mainWindow.showInfoBanner(infoMessage)
            }
        }
    ]
    content:  Container {
        horizontalAlignment: HorizontalAlignment.Fill
        verticalAlignment: VerticalAlignment.Fill
        layout: StackLayout {}
        
        PageStatusContainer {
            visible: post.infoState==UI.ProgressState.Processing
            indicatorVisible: post.infoState==UI.ProgressState.Processing
            labelVisible: post.infoState == UI.ProgressState.Error
            labelText: post.infoStatus
        }
        
        ScrollView {
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Fill
            attachedObjects: [
                LayoutUpdateHandler {
                    id: handler
                }
            ]
            Container {
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill
                layout: StackLayout {}
                Container {
                    horizontalAlignment: HorizontalAlignment.Fill
                    verticalAlignment: VerticalAlignment.Fill
                    background: {
                        if(post.displayStatus=="private")
                            return Color.Green
                        else if(post.displayStatus=="pending")
                            return Color.create("#FF8C00")
                        else if(post.displayStatus=="draft")
                            return Color.Yellow
                        else if(post.displayStatus=="localdraft")
                            return Color.DarkYellow
                        else if(post.displayStatus=="future")
                            return Color.DarkCyan
                        else if(post.displayStatus=="trash")
                            return Color.Red
                    }
                    layout: StackLayout {}
                    topPadding: ui.sdu(0.5)
                    bottomPadding: topPadding
                    Label {
                        textStyle.base: SystemDefaults.TextStyles.SmallText
                        text: {
                            if(post.displayStatus=="localdraft")
                                return "LOCAL DRAFT"
                            else
                                return post.displayStatus.toUpperCase()
                        }
                    	horizontalAlignment: HorizontalAlignment.Center
                    	textStyle.fontWeight: FontWeight.Bold
                        textStyle.color: {
                            if(post.displayStatus=="private" || post.displayStatus=="draft")
                                return Color.Black
                            else
                                return Color.White
                        }
                    	visible: post.displayStatus!="" && post.displayStatus!="publish"
                    }
                }
                
                Container {
                    horizontalAlignment: HorizontalAlignment.Fill
                    verticalAlignment: VerticalAlignment.Fill
                    leftPadding: ui.sdu(1)
                    rightPadding: leftPadding
                    layout: StackLayout {}
    	    		Label {
    		          textStyle.base: SystemDefaults.TextStyles.BigText
    		          text: post.title
    		          textFormat: TextFormat.Html
    		          multiline: true
                    }
                    Label {
                        text: post.categoriesAsString
                        textStyle.fontWeight: FontWeight.Bold
                        textStyle.color: Color.DarkGray
                        textStyle.fontSize: FontSize.Small
                        textFormat: TextFormat.Html
                        visible: text!=""
                    }
                    Container {
                        horizontalAlignment: HorizontalAlignment.Fill
                        topPadding: ui.sdu(1.2)
                        layout: DockLayout {}
                        Container {
                            rightPadding: post.password!=""?35:0
                            Label {
                                text: qsTr("<em>%1</em> | %2").arg(post.authorDisplayName).arg(post.displayDate)
                                //                        textStyle.fontStyle: FontStyle.Italic
                                textStyle.color: Color.Gray
                                textStyle.fontSize: FontSize.XSmall
                                textFormat: TextFormat.Html
                            }
                        }
                        ControlDelegate {
                            horizontalAlignment: HorizontalAlignment.Right
                            verticalAlignment: VerticalAlignment.Center
                            delegateActive: post.password!=""  
                            sourceComponent: ComponentDefinition {
                                ImageView {
                                    imageSource: "asset:///images/lock.png"
                                }
                            }
                        }
                    }
    	        }
                Divider {}
    //            Label {
    //                text: post.descriptionForHtml
    //                textFormat: TextFormat.Plain
    //                horizontalAlignment: HorizontalAlignment.Fill
    //                verticalAlignment: VerticalAlignment.Fill
    //                multiline: true
    //            }
    	        WebView {
    	            id: webView
    //	            minHeight: handler.layoutFrame.height-150
    	            horizontalAlignment: HorizontalAlignment.Fill
    	            verticalAlignment: VerticalAlignment.Fill
    	            settings.defaultFontSize: 16
    	            settings.background: Application.themeSupport.theme.colorTheme.style==VisualStyle.Bright?Color.White:Color.Black
    	            settings.viewport: {
    //	                "width": "device-width",
    //	                "initial-scale": 1.0
    	            }
                    html: Application.themeSupport.theme.colorTheme.style==VisualStyle.Bright?
                        post.descriptionSnippet.length<200?qsTr("<html><body><style>img {max-width:700px;}</style>%1<p style='visibility:hidden;'>Hiding an element can be done by setting the display property to or the visibility property to. However, notice that these two methods produce different results:visibility:hidden hides an element, but it will still take up the same space as before..</p></body></html>").arg(post.descriptionForHtml):qsTr("<html><body><style>img {max-width:700px; }</style>%1</body></html>").arg(post.descriptionForHtml):
                        post.descriptionSnippet.length<200?qsTr("<html><head><style>body {color: white;} img {max-width:700px;}</style></head><body>%1<p style='visibility:hidden;'>Hiding an element can be done by setting the display property to or the visibility property to. However, notice that these two methods produce different results:visibility:hidden hides an element, but it will still take up the same space as before..</p></body></html>").arg(post.descriptionForHtml):qsTr("<html><head><style>body {color: white;} img {max-width:700px;}</style></head><body>%1</body></html>").arg(post.descriptionForHtml)
                    onNavigationRequested: {
                        if (request.navigationType == WebNavigationType.LinkClicked || request.navigationType == WebNavigationType.OpenWindow) {
                            request.action = WebNavigationRequestAction.Ignore
                            appUtil.launchBrowser(request.url)
                        } else request.action = WebNavigationRequestAction.Accept
                    }
                }
                Divider {}
                Container {
                    horizontalAlignment: HorizontalAlignment.Fill
                    leftPadding: ui.sdu(1)
                    rightPadding: leftPadding
                    bottomPadding: ui.sdu(2)
                    visible: post.tagsAsString!="" || post.commentCount>0 || metaLabel.text!=""
                    layout: StackLayout {}
                    Label {
                        text: post.tagsAsString
                        textStyle.color: Color.Gray
                        textStyle.fontSize: FontSize.XSmall
                        textFormat: TextFormat.Html
                        visible: text!=""
                        multiline: true
                    }
                    Label {
                    	text: post.commentCount>0?post.commentCount>1?qsTr("%1 comments").arg(post.commentCount):qsTr("%1 comment").arg(post.commentCount):""
                        textStyle.color: Color.DarkGray
                        textStyle.fontSize: FontSize.Small
                        visible: text!=""
                    }
                    Label {
                        id: metaLabel
                        text: {
                            if(!post.commentsOpen & !post.pingsOpen)
                            	return qsTr("Comments & pings are not allowed.")
                            else {
                                if(!post.commentsOpen & post.pingsOpen)
                                    return qsTr("Comments are not allowed.")
                                else if(post.commentsOpen & !post.pingsOpen)
                                    return qsTr("Pings are not allowed.")
                            }
                            return ""
                        }
                        textStyle.color: Color.Gray
                        textStyle.fontSize: FontSize.XXSmall
                        textStyle.fontStyle: FontStyle.Italic
                        textFormat: TextFormat.Html
                        visible: text!=""
                    }
                }
            }
        }
    }
    shortcuts: [
        SystemShortcut {
            type: SystemShortcuts.Edit
            onTriggered: {               
                mainWindow.openEditPostEditorUsingObject(post)
            }
        }
    ] 
    onCreationCompleted: {
    }
}
