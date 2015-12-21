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
import com.cutepress.settings 1.0
import "UIConstants.js" as UI

CutePressSheet {
    id: iSheet
    
    content: Page {
        id: page
        
        titleBar: TitleBar {
            title: qsTr("Settings")
            dismissAction: ActionItem {
                title: qsTr("Cancel")
                onTriggered: {
                    iSheet.close()
                }
            } // ActionItem
            acceptAction: ActionItem {
                title: qsTr("Save")
                onTriggered: {
                    appSettings.saveData("Is_Get_Post_Comment_Count", postCommentCountCheck?"true":"false")
                    iSheet.close()
                }
            } // ActionItem
        }
        content: ScrollView {
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Fill
            content: Container {
		        topPadding: ui.sdu(2)
                bottomPadding: topPadding
                leftPadding: ui.sdu(2)
                rightPadding: leftPadding
		        horizontalAlignment: HorizontalAlignment.Fill
		        verticalAlignment: VerticalAlignment.Fill
		        layout: StackLayout {
		        }
		        Label {
		            text: qsTr("Post Comments Count")
                }
	            Container {
	                horizontalAlignment: HorizontalAlignment.Fill
	                layout: DockLayout {}
	                Container {
	                    horizontalAlignment: HorizontalAlignment.Left
	                    rightPadding: ui.sdu(22)
	                    layout: StackLayout {}
                        Label {
                            text: qsTr("Get post's comments count on post refresh")
                            multiline: true
                            textStyle.fontSize: FontSize.Small
    	                    textStyle.color: Color.DarkGray
    	                }
    	            }
    	            ToggleButton {
    	                id: postCommentCountCheck
    	                horizontalAlignment: HorizontalAlignment.Right
                        checked: appSettings.readData("Is_Get_Post_Comment_Count")=="true"
    	            }
	            }
	        }        
	    }
    }
    onCreationCompleted: {
    }
}
