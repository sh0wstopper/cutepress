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
import "UIConstants.js" as UI

CutePressSheet {
    id: iSheet
    property variant caller: 0
    property int insertPosition: 0
    content: Page {
        attachedObjects: [
            FilePicker {
                id: filePicker
                type: FileType.Picture
                title: "Select Picture"
                //            directories: [ "/accounts/1000/shared/misc" ]
                onFileSelected: {
                    caller.insertImage(iSheet.insertPosition, "file://" + selectedFiles[0])
                    iSheet.close()
                }
            }
        ]
        titleBar: TitleBar {
            title: qsTr("Select image")
            dismissAction: ActionItem {
                title: qsTr("Cancel")
                onTriggered: {
                    iSheet.close()
                }
            } // ActionItem
        }
        Container {
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Fill
            topPadding: ui.sdu(1)
            layout: StackLayout {}
            
            Button {
                horizontalAlignment: HorizontalAlignment.Center
                text: "Add from gallery"
                onClicked: {
                    filePicker.open()
                }
            }
            
            Divider {}
            
            PageMediaItemsListView {
                id: iList
                isOpenImageViewer: false
                topMargin: 10
                dataModel: cpUtil.mediaItems
                onFlickedAtEnd: {}
                onTriggered: {
                    var currentItem = dataModel.data(indexPath)
                    caller.insertImage(iSheet.insertPosition, currentItem.mediaLink)
                    iSheet.close()
                }
            }
        }
    }    
}
