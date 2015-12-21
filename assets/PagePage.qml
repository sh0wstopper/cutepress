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
import com.cutepress.page 1.0
import "UIConstants.js" as UI

Page {
    id: page
    
    function setPageInfo(iPage) {
        cpPage.setInfo(iPage)
    }
    
    actions: [
        ActionItem {
            title: qsTr("Comment")
            imageSource: "asset:///images/comment.png"
            onTriggered: {
                page.fetchComments()
                var nPage = pageCommentsPageDefinition.createObject()
                nPage.page = cpPage
                mainWindow.push(nPage)
            }
            ActionBar.placement: ActionBarPlacement.OnBar
            attachedObjects: [
                ComponentDefinition {
                    id: pageCommentsPageDefinition
                    source: "PageCommentsPage.qml"
                }
            ]
        },
        ActionItem {
            title: qsTr("Edit")
            imageSource: "asset:///images/edit.png"
            onTriggered: {
                mainWindow.openEditPageEditorUsingObject(cpPage)
            }
            ActionBar.placement: ActionBarPlacement.OnBar
        },
        ActionItem {
            title: qsTr("Reload")
            imageSource: "asset:///images/refresh.png"
            onTriggered: {
                cpPage.fetchInfo()
            }
            ActionBar.placement: ActionBarPlacement.InOverflow
        },
        InvokeActionItem {
            title: qsTr("Share")
            imageSource: "asset:///images/share.png"
            query {
                mimeType: "text/plain"
                invokeActionId: "bb.action.SHARE"
            }
            onTriggered: {
                data = cpPage.title + " " + cpPage.url + " by " + cpPage.authorName;
            }
            ActionBar.placement: ActionBarPlacement.OnBar
        },
        ActionItem {
            title: qsTr("Copy link")
            imageSource: "asset:///images/copy_link.png"
            onTriggered: appUtil.copyTextToClipboard(cpPage.url)
        },
        ActionItem {
            title: qsTr("Open in web browser")
            imageSource: "asset:///images/open_link.png"
            onTriggered: {
                appUtil.launchBrowser(cpPage.url)
            }
        },
        DeleteActionItem {
            title: qsTr("Delete")
            onTriggered: {
                mainWindow.openDialog(qsTr("Delete page"), 
                    qsTr("Delete page '%1'?").arg(cpPage.title), "page-delete",
                    cpPage.cpId, "pop")
            }
        }
    ]
    attachedObjects: [
        CutePressPage {
            id: cpPage
            onCpIdChanged: {
//                fetchInfo()
            }
            onInfoMessageChanged: {
                if(infoMessage!="")
                	mainWindow.showInfoBanner(infoMessage)
            }
            onPageRefreshed: {
                cpUtil.updatePageInfoFromPagePage(cpId, newPage)
            }
        }
    ]
    content:   Container {
        horizontalAlignment: HorizontalAlignment.Fill
        verticalAlignment: VerticalAlignment.Fill
        layout: StackLayout {}
        
        PageStatusContainer {
            visible: cpPage.infoState==UI.ProgressState.Processing
            indicatorVisible: cpPage.infoState==UI.ProgressState.Processing
            labelVisible: cpPage.infoState == UI.ProgressState.Error
            labelText: cpPage.infoStatus
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
                        if(cpPage.displayStatus=="private")
                            return Color.Green
                        else if(cpPage.displayStatus=="pending")
                            return Color.create("#FF8C00")
                        else if(cpPage.displayStatus=="draft")
                            return Color.Yellow
                        else if(cpPage.displayStatus=="localdraft")
                            return Color.DarkYellow
                        else if(cpPage.displayStatus=="future")
                            return Color.DarkCyan
                        else if(cpPage.displayStatus=="trash")
                            return Color.Red
                    }
                    layout: StackLayout {}
                    topPadding: ui.sdu(0.5)
                    bottomPadding: topPadding
                    Label {
                        textStyle.base: SystemDefaults.TextStyles.SmallText
                        text: {
                            if(cpPage.displayStatus=="localdraft")
                                return "LOCAL DRAFT"
                            else
                                return cpPage.displayStatus.toUpperCase()
                        }
                    	horizontalAlignment: HorizontalAlignment.Center
                    	textStyle.fontWeight: FontWeight.Bold
                        textStyle.color: {
                            if(cpPage.displayStatus=="private" || cpPage.displayStatus=="draft")
                                return Color.Black
                            else
                                return Color.White
                        }
                    	visible: cpPage.displayStatus!="" && cpPage.displayStatus!="publish"
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
    		          text: cpPage.title
    		          textFormat: TextFormat.Html
    		          multiline: true
                    }
                    Label {
                        text: cpPage.categoriesAsString
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
                            rightPadding: cpPage.password!=""?35:0
                            Label {
                                text: qsTr("<em>%1</em> | %2").arg(cpPage.wpAuthorDisplayName).arg(cpPage.displayDate)
                                //                        textStyle.fontStyle: FontStyle.Italic
                                textStyle.color: Color.Gray
                                textStyle.fontSize: FontSize.XSmall
                                textFormat: TextFormat.Html
                            }
                        }
                        ControlDelegate {
                            horizontalAlignment: HorizontalAlignment.Right
                            verticalAlignment: VerticalAlignment.Center
                            delegateActive: cpPage.wpPassword!=""  
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
    //                text: cpPage.descriptionForHtml
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
                        cpPage.descriptionSnippet.length<200?qsTr("<html><body><style>img {max-width:700px;}</style>%1<p style='visibility:hidden;'>Hiding an element can be done by setting the display property to or the visibility property to. However, notice that these two methods produce different results:visibility:hidden hides an element, but it will still take up the same space as before..</p></body></html>").arg(cpPage.descriptionHtml):qsTr("<html><body><style>img {max-width:700px; }</style>%1</body></html>").arg(cpPage.descriptionHtml):
                        cpPage.descriptionSnippet.length<200?qsTr("<html><head><style>body {color: white;} img {max-width:700px;}</style></head><body>%1<p style='visibility:hidden;'>Hiding an element can be done by setting the display property to or the visibility property to. However, notice that these two methods produce different results:visibility:hidden hides an element, but it will still take up the same space as before..</p></body></html>").arg(cpPage.descriptionHtml):qsTr("<html><head><style>body {color: white;} img {max-width:700px;}</style></head><body>%1</body></html>").arg(cpPage.descriptionHtml)
                    	
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
                    visible: cpPage.tagsAsString!="" || cpPage.commentCount>0 || metaLabel.text!=""
                    layout: StackLayout {}
                    Label {
                        text: cpPage.tagsAsString
                        textStyle.color: Color.Gray
                        textStyle.fontSize: FontSize.XSmall
                        textFormat: TextFormat.Html
                        visible: text!=""
                        multiline: true
                    }
                    Label {
                    	text: cpPage.commentCount>0?cpPage.commentCount>1?qsTr("%1 comments").arg(cpPage.commentCount):qsTr("%1 comment").arg(cpPage.commentCount):""
                        textStyle.color: Color.DarkGray
                        textStyle.fontSize: FontSize.Small
                        visible: text!=""
                    }
                    Label {
                        id: metaLabel
                        text: {
                            if(!cpPage.mtAllowComments & !cpPage.mtAllowPings)
                            	return qsTr("Comments & pings are not allowed.")
                            else {
                                if(!cpPage.mtAllowComments & cpPage.mtAllowPings)
                                    return qsTr("Comments are not allowed.")
                                else if(cpPage.mtAllowComments & !cpPage.mtAllowPings)
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
                mainWindow.openEditPageEditorUsingObject(cpPage)
            }
        }
    ] 
    onCreationCompleted: {
    }
}
