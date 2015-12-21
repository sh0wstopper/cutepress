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
import com.cutepress.timer 1.0
import "UIConstants.js" as UI

CutePressSheet {
    id: iSheet
    property variant caller: 0
    property variant postItem: 0
    property variant postObject: 0
    property int iState: cpUtil.postEditionState
    property string iStatus: cpUtil.postEditionStatus
    onIStateChanged: {
        if(iState===UI.ProgressState.Success) {
            iSheet.close()
            cpUtil.clearEditorData()
            if(isEditing) {
                if(editedPostOriginalStatus()!="localdraft")
                    cpUtil.fetchPost(postId)
                else {
                    cpUtil.deleteLocalPost(postId)
//                    cpUtil.fetchRecentPosts()
                }
                if(caller!=0)
                    mainWindow.pop()
            }
        }
    }
    property bool isEditing: false
    property string postId: ""
    property alias titleText: titleInput.text
    property alias bodyText: bodyInput.text
    property alias statusIndex: statusInput.selectedIndex
    property alias passwordText: passwordInput.text
    property alias timeValue: timeInput.value
    property alias slugText: slugInput.text
    property alias excerptText: excerptInput.text
    property alias tagsText: tagsInput.text
    property alias categoriesText: categoriesInput.text
    property alias commentsOpenValue: commentsOpenInput.checked
    property alias pingsOpenValue: pingsOpenInput.checked
    
    function editedPostOriginalStatus() {
       if(postItem!=0)
           return postItem.postPublishStatus 
       if(postObject!=0)
           return postObject.status
    }
    
    function edit() {
        if(postItem==0 && postObject==0) return;
        var iTime="", iTitle="", iBody="", iExcerpt="", iSlug="", iPStatus="", iPass="", iCats="", iTags="", iCmtsOpen="", iPingsOpen=""
        iTime = timeInput.value.toISOString()
        iTitle = titleInput.text
        iBody = bodyInput.text
        iExcerpt = excerptInput.text
        iSlug = slugInput.text
        iPStatus = statusInput.selectedValue
        iPass = passwordInput.text
        iCats = categoriesInput.text
        iTags = tagsInput.text
        iCmtsOpen = commentsOpenInput.checked
        iPingsOpen = pingsOpenInput.checked
        cpUtil.editPost(postId, iTime, iTitle, iBody, iExcerpt, iSlug, iPStatus, iPass, iCats, iTags, iCmtsOpen, iPingsOpen)
    }
    
    property string uploadedImageUrl: cpUtil.editorUploadedImageUrl
    onUploadedImageUrlChanged: {
        if(uploadedImageUrl!="") {
            bodyInput.text=bodyInput.text.replace(cpUtil.editorUploadImageUrl, cpUtil.editorUploadedImageUrl)
            cpUtil.removeEditorUploadImage(cpUtil.editorUploadImageUrl)
            makePostRequest()
        }
    }
    
    function insertImage(insertPos, insertImg) {
        if(insertPos==0) {
            bodyInput.text = bodyInput.text.substring(0, insertPos)+
            "<img src=\""+insertImg+"\" />\n"+
            bodyInput.text.substring(insertPos, bodyInput.text.length)
        } else {
            bodyInput.text = bodyInput.text.substring(0, insertPos)+
            "\n<img src=\""+insertImg+"\" />\n"+
            bodyInput.text.substring(insertPos, bodyInput.text.length)            
        }
        var str = insertImg
        if(str.indexOf("file://")==0)
            cpUtil.appendEditorUploadImage(insertImg)
    }
    
    function makePostRequest() {        
        if(cpUtil.editorUploadImagesCount()>0) {
            cpUtil.editorType="post"
            cpUtil.uploadEditorImage(cpUtil.getEditorUploadImage())
        } else {
            if (isEditing && editedPostOriginalStatus()!="localdraft") {
                iSheet.edit()
                //                        appUser.editTextPost(postMeta.blogShortUrl, postId, titleInput.text, bodyInput.text, pagePostState == "" ? postMeta.postState : pagePostState, postMeta.tags, "", "current", postFormat)
            } else {
                cpUtil.createNewPost(timeInput.value.toISOString(),
                titleInput.text,
                bodyInput.text,
                excerptInput.text,
                slugInput.text,
                statusInput.selectedValue,
                passwordInput.text,
                categoriesInput.text,
                tagsInput.text,
                commentsOpenInput.checked,
                pingsOpenInput.checked,
                stickyInput.checked)
            }
        }
    }
    
    function getMarkedCategoriesFromModel() {
        categoriesInput.text = cpUtil.getMarkedCategoriesFromModel()
    }
    
    content: Page {
        
        attachedObjects: [
            ComponentDefinition {
                id: categoriesSelectionSheetDefinition
                source: "PostCategoriesSelectionSheet.qml"
            }
        ]
        
        titleBar: TitleBar {
            title: isEditing?qsTr("Edit post"):qsTr("New post")
            dismissAction: ActionItem {
                enabled: iState != UI.ProgressState.Processing
                title: qsTr("Cancel")
                onTriggered: {
                    iSheet.close()
                    cpUtil.clearEditorData()
                }
            } // ActionItem
            acceptAction: ActionItem {
                enabled: iState != UI.ProgressState.Processing //&& titleInput.text != ""
                title: isEditing ? qsTr("Ok") : qsTr("Create")
                onTriggered: {
                    pageScroll.scrollToPoint(0, 0)
                    if(statusInput.selectedValue=="localdraft") {
                        if(isEditing && editedPostOriginalStatus()!="localdraft") {
                            mainWindow.showInfoBanner(qsTr("Saving already published or drafted post as local draft is not available at present!"))
                            return
                        }
                        cpUtil.saveLocalDraftPost(postId,
                        timeInput.value.toISOString(),
                        titleInput.text,
                        bodyInput.text,
                        excerptInput.text,
                        slugInput.text,
                        statusInput.selectedValue,
                        passwordInput.text,
                        categoriesInput.text,
                        tagsInput.text,
                        commentsOpenInput.checked,
                        pingsOpenInput.checked,
                        stickyInput.checked)
                        iSheet.close()
                        cpUtil.clearEditorData()
                        return;
                    }
                    makePostRequest()
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
            Container {
                id: bodyTextToolbar
                horizontalAlignment: HorizontalAlignment.Fill
                background: Color.Gray
                bottomPadding: 1
                visible: bodyInput.focused && (iSheet.iState === UI.ProgressState.None || iSheet.iState === UI.ProgressState.Error)
                Container {
                    background: Color.create("#f8f8f8")
                    horizontalAlignment: HorizontalAlignment.Fill
                    topPadding: ui.sdu(1)
                    bottomPadding: topPadding
                    leftPadding: ui.sdu(2)
                    rightPadding: leftPadding
                    layout: DockLayout {}
                    ImageButton {
                        defaultImageSource: "asset:///images/image.png"
                        pressedImageSource: "asset:///images/image.png"
                        horizontalAlignment: HorizontalAlignment.Center
                        verticalAlignment: VerticalAlignment.Center
                        onClicked: {
                            mainWindow.openImageSelector(iSheet, bodyInput.editor.cursorPosition)
                        }
                    }
                }
            }
            ScrollView {
                id: pageScroll
                horizontalAlignment: HorizontalAlignment.Fill
                Container {
                    topPadding: ui.sdu(2)
                    bottomPadding: topPadding
                    leftPadding: topPadding
                    rightPadding: topPadding
                    horizontalAlignment: HorizontalAlignment.Fill
                    layout: StackLayout {
                    }
                    
                    SmallHeadingText {
                        text: qsTr("Title")
                    }
                    
                    TextField {
                        id: titleInput
                        hintText: qsTr("Title")
                    }
                    
                    SmallHeadingText {
                        text: qsTr("Slug")
                    }
                    
                    TextField {
                        id: slugInput
                        hintText: qsTr("Slug")
                    }
                    
                    SmallHeadingText {
                        text: qsTr("Body")
                    }
                    
                    TextArea {
                        id: bodyInput
                        hintText: qsTr("Post body")
                        textFormat: TextFormat.Plain
                        minHeight: 400
                        content.flags: TextContentFlag.ActiveTextOff
                        onFocusedChanged: {
                            if(focused)
                                bodyTextToolbar.visible=true
                            else {
                                toolbarTimer.start()
                            }
                        }
                        attachedObjects: [
                            Timer {
                                id: toolbarTimer
                                interval: 200
                                singleShot: true
                                onTimeout: {
                                    bodyTextToolbar.visible=false
                                }
                            }
                        ]
                    }
                    
                    SmallHeadingText {
                        text: qsTr("Tags")
                    }
                    
                    TextField {
                        id: tagsInput
                        hintText: qsTr("Tags")
                    }
                    
                    SmallHeadingText {
                        text: qsTr("Categories")
                    }
                    
                    Container {
                        horizontalAlignment: HorizontalAlignment.Fill
                        topPadding: 1
                        bottomPadding: topPadding
                        bottomMargin: 5
                        leftPadding: 1
                        rightPadding: leftPadding
                        background: Color.Gray
                        layout: DockLayout {}
                        Container {                            
                            horizontalAlignment: HorizontalAlignment.Fill
                            background: Color.create("#F8F8F8")
                            layout: DockLayout {}
                            topPadding: ui.sdu(1.5)
                            bottomPadding: topPadding
                            leftPadding: ui.sdu(1.5)
                            rightPadding: leftPadding
                            Label {
                                id: categoriesInput
                                horizontalAlignment: HorizontalAlignment.Fill
                                multiline: true
                                textFormat: TextFormat.Html
                                textStyle.color: Color.Black
                            }
                            gestureHandlers: [
                                TapHandler {
                                    onTapped: {
                                        cpUtil.markCategoriesInModel(categoriesInput.text)
                                        var catSheet = categoriesSelectionSheetDefinition.createObject(mainWindow.top())
                                        catSheet.caller = iSheet
                                        catSheet.open()
                                    }
                                }
                            ]
                        }
                    }
                    
//                    TextField {
//                        id: categoriesInput
//                        enabled: false
//                        hintText: qsTr("Categories")
//                    }
                    
                    DropDown {
                        id: statusInput
                        title: qsTr("Status")
                        
                        Option {
                        	text: qsTr("Publish")
                        	value: "publish"
                        	selected: true
                        }
                        Option {
                            text: qsTr("Private")
                            value: "private"
                        }
                        Option {
                            text: qsTr("Draft")
                            value: "draft"
                        }
                        Option {
                            text: qsTr("Pending")
                            value: "pending"
                        }
                        Option {
                            text: qsTr("Local draft")
                            value: "localdraft"
                        }
                    }
                    
                    SmallHeadingText {
                        text: qsTr("Password")
                    }
                    
                    TextField {
                        id: passwordInput
                        hintText: qsTr("Password")
                    }
                    
                    DateTimePicker {
                        id: timeInput
                        title: qsTr("Time")
                        minuteInterval: 1
                        visible: statusInput.selectedValue!="draft"
                        mode: DateTimePickerMode.DateTime
                        value: { new Date(); }
                    }
                    
                    SmallHeadingText {
                        text: qsTr("Excerpt")
                    }
                    
                    TextArea {
                        id: excerptInput
                        hintText: qsTr("Excerpt")
                    }  
                    
                    Container {
                        horizontalAlignment: HorizontalAlignment.Fill
                        topPadding: ui.sdu(0.5)
                        bottomPadding: topPadding
                        layout: DockLayout {}
                        
                        SmallHeadingText {
                            text: qsTr("Sticky")
                        }
                        ToggleButton {
                            id: stickyInput
                            horizontalAlignment: HorizontalAlignment.Right
                            checked: false
                        } 
                    }  
                    
                    Container {
                        horizontalAlignment: HorizontalAlignment.Fill
                        topPadding: ui.sdu(0.5)
                        bottomPadding: topPadding
                        layout: DockLayout {}
                        
                        SmallHeadingText {
                            text: qsTr("Comments open")
                        }
                        ToggleButton {
                        	id: commentsOpenInput
                        	horizontalAlignment: HorizontalAlignment.Right
                        	checked: true
                        } 
                    }   
                    
                    Container {
                        horizontalAlignment: HorizontalAlignment.Fill
                        topPadding: ui.sdu(0.5)
                        bottomPadding: topPadding
                        layout: DockLayout {}
                        
                        SmallHeadingText {
                            text: qsTr("Pings open")
                        }
                        ToggleButton {
                            id: pingsOpenInput
                            horizontalAlignment: HorizontalAlignment.Right
                            checked: true
                        } 
                    }              
                }
            }
        }
    }
    onCreationCompleted: {        
        cpUtil.clearEditorUploadImages()
//        bodyInput.text = appSettings.readData("Default_Caption")
    }
}
