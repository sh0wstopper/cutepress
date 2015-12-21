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
import bb.system 1.0
import "UIConstants.js" as UI

Page {
    id: page
    titleBar: TitleBar {
        title: qsTr("Help")
    }
    content: ScrollView {
        horizontalAlignment: HorizontalAlignment.Fill
        verticalAlignment: VerticalAlignment.Fill
        Container {
	        topPadding: ui.sdu(2)
	        bottomPadding: topPadding
	        leftPadding: ui.sdu(2)
	        rightPadding: leftPadding
	        horizontalAlignment: HorizontalAlignment.Fill
	//        verticalAlignment: VerticalAlignment.Fill
	        layout: StackLayout {
	        }
	        Container {
            	horizontalAlignment: HorizontalAlignment.Fill
                layout: StackLayout {}
                Label {
                    textStyle.fontWeight: FontWeight.Bold
                    text: qsTr("Color indicators for post & comment status")
                    multiline: true
                } 
                Container {
                    horizontalAlignment: HorizontalAlignment.Fill
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    } 
                    Container {
                        topMargin: 20
                        minWidth: 64
                        maxWidth: 64
                        minHeight: 20
                        maxHeight: 20
                        background: Color.Green
                        verticalAlignment: VerticalAlignment.Center
                    }
                    Label {
                        text: qsTr("Private") 
                        textStyle.fontStyle: FontStyle.Italic
                        verticalAlignment: VerticalAlignment.Center
                    }
                } 
                Container {
                    horizontalAlignment: HorizontalAlignment.Fill
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    } 
                    Container {
                        topMargin: 20
                        minWidth: 64
                        maxWidth: 64
                        minHeight: 20
                        maxHeight: 20
                        background: Color.create("#FF8C00")
                        verticalAlignment: VerticalAlignment.Center
                    }
                    Label {
                        text: qsTr("Pending for review") 
                        textStyle.fontStyle: FontStyle.Italic
                        verticalAlignment: VerticalAlignment.Center
                    }
                } 
                Container {
                    horizontalAlignment: HorizontalAlignment.Fill
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    } 
                    Container {
                        topMargin: 20
                        minWidth: 64
                        maxWidth: 64
                        minHeight: 20
                        maxHeight: 20
                        background: Color.Yellow
                        verticalAlignment: VerticalAlignment.Center
                    }
                    Label {
                        text: qsTr("Draft") 
                        textStyle.fontStyle: FontStyle.Italic
                        verticalAlignment: VerticalAlignment.Center
                    }
                } 
                Container {
                    horizontalAlignment: HorizontalAlignment.Fill
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    } 
                    Container {
                        topMargin: 20
                        minWidth: 64
                        maxWidth: 64
                        minHeight: 20
                        maxHeight: 20
                        background: Color.DarkYellow
                        verticalAlignment: VerticalAlignment.Center
                    }
                    Label {
                        text: qsTr("Local Draft") 
                        textStyle.fontStyle: FontStyle.Italic
                        verticalAlignment: VerticalAlignment.Center
                    }
                }
                Container {
                    horizontalAlignment: HorizontalAlignment.Fill
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    } 
                    Container {
                        topMargin: 20
                        minWidth: 64
                        maxWidth: 64
                        minHeight: 20
                        maxHeight: 20
                        background: Color.DarkCyan
                        verticalAlignment: VerticalAlignment.Center
                    }
                    Label {
                        text: qsTr("Furture") 
                        textStyle.fontStyle: FontStyle.Italic
                        verticalAlignment: VerticalAlignment.Center
                    }
                } 
            	Container {
                	horizontalAlignment: HorizontalAlignment.Fill
                	layout: StackLayout {
                	    orientation: LayoutOrientation.LeftToRight
                	} 
                	Container {
                	    topMargin: 20
                	    minWidth: 64
                    	maxWidth: 64
                    	minHeight: 20
                    	maxHeight: 20
                    	background: Color.Red 
                    	verticalAlignment: VerticalAlignment.Center
                    }
                	Label {
                    	text: qsTr("Trash") 
                        textStyle.fontStyle: FontStyle.Italic
                        verticalAlignment: VerticalAlignment.Center
                    }
                } 
                Container {
                    horizontalAlignment: HorizontalAlignment.Fill
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    } 
                    Container {
                        topMargin: 20
                        minWidth: 64
                        maxWidth: 64
                        minHeight: 20
                        maxHeight: 20
                        background: Color.DarkRed 
                        verticalAlignment: VerticalAlignment.Center
                    }
                    Label {
                        text: qsTr("Spam") 
                        textStyle.fontStyle: FontStyle.Italic
                        verticalAlignment: VerticalAlignment.Center
                    }
                } 
            }
            Label {
                textStyle.fontWeight: FontWeight.Bold
                text: qsTr("Other indicators")
                multiline: true
            }
	        Label {
	            multiline: true
	            textFormat: TextFormat.Html
                text: qsTr("'Lock' icon in page/post list view indicates private.")
            }
            Label {
                textStyle.fontWeight: FontWeight.Bold
                text: qsTr("Notes")
                multiline: true
            }
            Label {
                multiline: true
                textFormat: TextFormat.Html
                text: qsTr("If you are using early versions of WordPress on your self-hosted blog and facing error while adding it in app, enable XML-RPC from the admin end. For this go to Dashboard->Settings->Writing->Remote Publishing and check XML-RPC.")
            }
	        Button {
	            text: qsTr("Privacy Policy")
	            horizontalAlignment: HorizontalAlignment.Fill
	            onClicked: {
	                var npage = privacyPageDefinition.createObject();
	                mainWindow.push(npage);
	            }
	            attachedObjects: [
	                ComponentDefinition {
	                    id: privacyPageDefinition
	                    source: "PrivacyPolicyPage.qml"
	                }
	            ]
	        }
	    }
    }
}
