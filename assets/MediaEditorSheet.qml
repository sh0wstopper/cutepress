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
import bb.cascades.pickers 1.0
import com.cutepress.webimageview 1.0
import "UIConstants.js" as UI

CutePressSheet {
    id: iSheet
    property variant mediaItem: 0
    property variant mediaObject: 0
    property int iState: cpUtil.mediaUploadState
    property string iStatus: cpUtil.mediaUploadStatus
    onIStateChanged: {
        if(iState===UI.ProgressState.Success) {
            iSheet.close()
            cpUtil.fetchMediaItems()
        }
    }
    property bool isEditing: false
    property string categoryId: ""
    property alias fileText: fileInput.text
    property alias nameText: nameInput.text
    
    function edit() {
    }
    
    content: Page {
        attachedObjects: [
            FilePicker {
                id: filePicker
//                type: FileType.
                title: "Select Picture"
                //            directories: [ "/accounts/1000/shared/misc" ]
                onFileSelected: {
                    fileInput.text = "file://" + selectedFiles[0];
                    if(appUtil.isImageFile(fileInput.text)) {
                        thumb.url = fileInput.text
                	}
                }
            }
        ]
        
        titleBar: TitleBar {
            title: qsTr("New media")
            dismissAction: ActionItem {
                enabled: iState != UI.ProgressState.Processing
                title: qsTr("Cancel")
                onTriggered: {
                    iSheet.close()
                }
            } // ActionItem
            acceptAction: ActionItem {
                enabled: iState != UI.ProgressState.Processing && fileInput.text != ""
                title: isEditing ? qsTr("Ok") : qsTr("Upload")
                onTriggered: {
                    pageScroll.scrollToPoint(0, 0)
                    if (isEditing) {
                        iSheet.edit()
                    } else {
                        cpUtil.uploadFile(fileInput.text,
                        			nameInput.text)
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
                    
                    Button {
                        horizontalAlignment: HorizontalAlignment.Center
                        text: qsTr("Select")
                        enabled: iState != UI.ProgressState.Processing
                        onClicked: {
                            filePicker.open()
                        }
                    }
                    
                    SmallHeadingText {
                        text: qsTr("File")
                    }
                    
                    TextField {
                        id: fileInput
                        hintText: qsTr("File")
                        enabled: false
                    }
                    
                    WebImageView {
                        id: thumb
                        visible: url!=""
                        horizontalAlignment: HorizontalAlignment.Fill
                        scalingMethod: ScalingMethod.AspectFit
                        maxHeight: 600
                    }
                    
                    SmallHeadingText {
                        text: qsTr("Name")
                    }
                    
                    TextField {
                        id: nameInput
                        hintText: qsTr("Name")
                    }       
                }
            }
        }
    }
    onCreationCompleted: {        
//        bodyInput.text = appSettings.readData("Default_Caption")
    }
}
