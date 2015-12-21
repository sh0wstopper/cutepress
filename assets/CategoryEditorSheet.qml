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

CutePressSheet {
    id: iSheet
    property variant categoryItem: 0
    property variant categoryObject: 0
    property int iState: cpUtil.categoryEditionState
    property string iStatus: cpUtil.categoryEditionStatus
    onIStateChanged: {
        if(iState===UI.ProgressState.Success) {
            iSheet.close()
            cpUtil.fetchCategories()
        }
    }
    property bool isEditing: false
    property string categoryId: ""
    property alias nameText: nameInput.text
    property alias descriptionText: descriptionInput.text
    property alias slugText: slugInput.text
    
    function edit() {
//        if(categoryItem==0 && categoryObject==0) return;
//        var iTime="", iTitle="", iBody="", iExcerpt="", iSlug="", iPStatus="", iPass="", iCats="", iTags="", iCmtsOpen="", iPingsOpen=""
//        if(categoryItem!=0) {
//            console.log(categoryItem.pageDate,timeInput.value)
//            if(categoryItem.pageDate != timeInput.value)
//                iTime = timeInput.value.toISOString()
//            if(categoryItem.pageTitle != titleInput.text)
//                iTitle = titleInput.text
//            if(categoryItem.pageContent != bodyInput.text)
//                iBody = bodyInput.text
//            if(categoryItem.pageExcerpt != excerptInput.text)
//                iExcerpt = excerptInput.text
//            if(categoryItem.pageSlug != slugInput.text)
//                iSlug = slugInput.text
//            if(categoryItem.pageStatus != statusInput.selectedValue)
//                iPStatus = statusInput.selectedValue
//            if(categoriesInput.text != appUtil.categoriesFromHash(categoryItem.pageCategories))
//                iCats = categoriesInput.text
//            if(tagsInput.text != appUtil.tagsFromHash(categoryItem.pageTags))
//                iTags = tagsInput.text
//            if(categoryItem.pagePassword != passwordInput.text)
//                iPass = passwordInput.text
//            if(categoryItem.pageCommentsOpen != commentsOpenInput.checked)
//                iCmtsOpen = commentsOpenInput.checked
//            if(categoryItem.pagePingsOpen != pingsOpenInput.checked)
//                iPingsOpen = pingsOpenInput.checked
//        } else {
//            if(categoryObject.date != timeInput.value)
//                iTime = timeInput.value.toISOString()
//            if(categoryObject.title != titleInput.text)
//                iTitle = titleInput.text
//            if(categoryObject.content != bodyInput.text)
//                iBody = bodyInput.text
//            if(categoryObject.excerpt != excerptInput.text)
//                iExcerpt = excerptInput.text
//            if(categoryObject.slug != slugInput.text)
//                iSlug = slugInput.text
//            if(categoryObject.status != statusInput.selectedValue)
//                iPStatus = statusInput.selectedValue
//            if(categoriesInput.text != categoryObject.categoriesAsString)
//                iCats = categoriesInput.text
//            if(tagsInput.text != categoryObject.tagsAsString)
//                iTags = tagsInput.text
//            if(categoryObject.password != passwordInput.text)
//                iPass = passwordInput.text
//            if(categoryObject.commentsOpen != commentsOpenInput.checked)
//                iCmtsOpen = commentsOpenInput.checked
//            if(categoryObject.pingsOpen != pingsOpenInput.checked)
//                iPingsOpen = pingsOpenInput.checked
//        }
//        cpUtil.editpage(pageId, iTime, iTitle, iBody, iExcerpt, iSlug, iPStatus, iPass, iCats, iTags, iCmtsOpen, iPingsOpen)
    }
    
    content: Page {
        
        titleBar: TitleBar {
            title: qsTr("New category")
            dismissAction: ActionItem {
                enabled: iState != UI.ProgressState.Processing
                title: qsTr("Cancel")
                onTriggered: {
                    iSheet.close()
                }
            } // ActionItem
            acceptAction: ActionItem {
                enabled: iState != UI.ProgressState.Processing //&& titleInput.text != ""
                title: isEditing ? qsTr("Ok") : qsTr("Create")
                onTriggered: {
                    pageScroll.scrollToPoint(0, 0)
                    if (isEditing) {
                        iSheet.edit()
                    } else {
                        cpUtil.createNewCategory(nameInput.text,
                        			slugInput.text,
                        			0,
                        			descriptionInput.text)
                    }
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
                        text: qsTr("Name")
                    }
                    
                    TextField {
                        id: nameInput
                        hintText: qsTr("Name")
                    }
                    
                    SmallHeadingText {
                        text: qsTr("Slug")
                    }
                    
                    TextField {
                        id: slugInput
                        hintText: qsTr("Slug")
                    }
                    
                    SmallHeadingText {
                        text: qsTr("Description")
                    }
                    
                    TextArea {
                        id: descriptionInput
                        hintText: qsTr("Description")
                        textFormat: TextFormat.Plain
                        minHeight: 400
                        content.flags: TextContentFlag.ActiveTextOff
                    }         
                }
            }
        }
    }
    onCreationCompleted: {        
//        bodyInput.text = appSettings.readData("Default_Caption")
    }
}
