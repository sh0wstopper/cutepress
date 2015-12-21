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
    property int iState: cpUtil.blogAdditionState
    property string tempBlogUrl: ""
    property string tempBlogRPCUrl: ""
    property string tempBlogUsername: ""
    property string tempBlogPassword: ""
    onIStateChanged: {
        if(iState==UI.ProgressState.Success) {
        	iSheet.close()
        	if(cpUtil.selectBlogs.size()>1)
            	mainWindow.openBlogListForSelection()
            else {                
                cpUtil.addSelectedBlogs()
                cpUtil.activateBlog()
            }
    	}
    }
    property string iStatus: cpUtil.blogAdditionStatus
    content: Page {
        titleBar: TitleBar {
            title: qsTr("New blog")
            dismissAction: ActionItem {
                title: qsTr("Cancel")
                onTriggered: {
                    if(tempBlogUrl != cpManager.blogUrl)
                        cpManager.blogUrl = tempBlogUrl
                    if(tempBlogRPCUrl != cpManager.blogRPCUrl)
                        cpManager.blogRPCUrl = tempBlogRPCUrl
                    if(tempBlogUsername != cpManager.blogUsername)
                        cpManager.blogUsername = tempBlogUsername
                    if(tempBlogPassword != cpManager.blogPassword)
                        cpManager.blogPassword = tempBlogPassword
                    iSheet.close()
                }
            } // ActionItem
            acceptAction: ActionItem {
                title: qsTr("Ok")
                enabled: iState!=UI.ProgressState.Processing
                onTriggered: {      
                    cpManager.blogRPCUrl = "";
                    if(blogAddressInput.text=="" || blogUsernameInput.text=="" || blogPasswordInput.text=="") {
                        mainWindow.showInfoBanner(qsTr("Blog details missing!"))           
                        return
                    }
                    if(blogSegment.selectedIndex==0) {
                        cpManager.blogUrl = schemeSelector.selectedValue+blogAddressInput.text.toLowerCase()+".wordpress.com"
	                    cpManager.blogUsername = blogUsernameInput.text
	                    cpManager.blogPassword = blogPasswordInput.text
	                    cpUtil.getBlogs()
                    } else {
                        cpManager.blogUrl = schemeSelector.selectedValue+blogAddressInput.text
                        if(htaccessCheck.checked) {
                            if(htUsernameInput.text!="") {
                                cpManager.blogHtAccessUsername = htUsernameInput.text
                            } else 
                                return
                            if(htPasswordInput.text!="") {
                                cpManager.blogHtAccessPassword = htPasswordInput.text
                            }
                            else
                                return
                        }
                        cpManager.blogUsername = blogUsernameInput.text
                        cpManager.blogPassword = blogPasswordInput.text
                        cpUtil.getBlogs()
                    }
                }
            } // ActionItem
        }
        content: ScrollView {
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Fill
            scrollViewProperties.scrollMode: ScrollMode.Vertical
            content: Container {
                layout: StackLayout {}
                leftPadding: ui.sdu(1)
                rightPadding: ui.sdu(1)
                EditorStatusElement {
                    parentObject: iSheet
                }
                SegmentedControl {
                    id: blogSegment
                    Option {
                        id: option1
                        text: "WordPress.com"
                        value: "0"
                        selected: true
                    }
                    Option {
                        id: option2
                        text: "Self-hosted"
                        value: "1"
                    }
                }
                HeadingText {
                    text: qsTr("URL")
                }
                Container {
                    layout: StackLayout { 
                        orientation: LayoutOrientation.LeftToRight               
                    }
                    DropDown {
                        id: schemeSelector
                        maxWidth: 240
                        Option {
                            text: "http://"
                            value: text
                            selected: true
                        }
                        Option {
                            text: "https://"
                            value: text
                        }
                    }
                    Container {
                        layout: StackLayout { 
                            orientation: LayoutOrientation.LeftToRight               
                        }      
    		            TextField {
    		                id: blogAddressInput
                            hintText: qsTr("URL")
                            validator: Validator {
                                mode: ValidationMode.FocusLost
                                errorMessage: "Invalid address"
                                onValidate: {
                                    if(blogAddressInput.text=="")
                                        state = ValidationState.Invalid
                                }
                            }
                            onFocusedChanged: {
                                if(!focused && blogSegment.selectedIndex==0 &&
                                    text!="" && blogUsernameInput.text=="")
                                    blogUsernameInput.text = text
                            }
    		            }
    		            Label {
    		            	text: ".wordpress.com"
    		            	textStyle.fontSize: FontSize.XXSmall
    		            	textStyle.fontWeight: FontWeight.Bold
    		            	visible: blogSegment.selectedValue==0 
    		            	verticalAlignment: VerticalAlignment.Center   
    	             	}
    		        }
                }
                HeadingText {
                    text: qsTr("Username")
                }            
                TextField {
                    id: blogUsernameInput
                    hintText: qsTr("Username")
                    validator: Validator {
                        mode: ValidationMode.FocusLost
                        errorMessage: "Invalid username"
                        onValidate: {
                            if(blogUsernameInput.text=="")
                                state = ValidationState.Invalid
                        }
                    }     
                }
                HeadingText {
                    text: qsTr("Password")
                }            
                TextField {
                    id: blogPasswordInput   
                    hintText: qsTr("Password")
                    inputMode: TextFieldInputMode.Password  
                    validator: Validator {
                        mode: ValidationMode.FocusLost
                        errorMessage: "Invalid password"
                        onValidate: {
                            if(blogPasswordInput.text=="")
                                state = ValidationState.Invalid
                        }
                    }      
                }
                Container {
                    horizontalAlignment: HorizontalAlignment.Fill
                    layout: StackLayout {}
                    visible: blogSegment.selectedIndex==1
                    Container {
                        horizontalAlignment: HorizontalAlignment.Fill
                        layout: DockLayout {}
                        HeadingText {
                            text: qsTr("htaccess Credentials")
                            verticalAlignment: VerticalAlignment.Center
                        }
                        ToggleButton {
                            id: htaccessCheck
                            horizontalAlignment: HorizontalAlignment.Right
                            checked: false
                        }
                    }
                    Container {
                        horizontalAlignment: HorizontalAlignment.Fill
                        topPadding: ui.sdu(1)
                        leftPadding: ui.sdu(7.5)
                        visible: htaccessCheck.checked
                        layout: StackLayout {
                            orientation: LayoutOrientation.LeftToRight
                        }
                        SmallHeadingText {
                            minWidth: 150
                            maxWidth: 150
                            text: qsTr("Username")
                            verticalAlignment: VerticalAlignment.Center
                        }
                        TextField {
                            id: htUsernameInput
                            hintText: qsTr("htaccess Username")
                            validator: Validator {
                                mode: ValidationMode.FocusLost
                                errorMessage: "Invalid username"
                                onValidate: {
                                    if(htUsernameInput.text=="")
                                        state = ValidationState.Invalid
                                }
                            }
                        }
                    }
                    Container {
                        horizontalAlignment: HorizontalAlignment.Fill
                        topPadding: ui.sdu(1)
                        leftPadding: ui.sdu(7.5)
                        visible: htaccessCheck.checked
                        layout: StackLayout {
                            orientation: LayoutOrientation.LeftToRight
                        }
                        SmallHeadingText {
                            minWidth: 150
                            maxWidth: 150
                            text: qsTr("Password")
                            verticalAlignment: VerticalAlignment.Center
                        }
                        TextField {
                            id: htPasswordInput
                            hintText: qsTr("htaccess Password")
                            inputMode: TextFieldInputMode.Password  
                            validator: Validator {
                                mode: ValidationMode.FocusLost
                                errorMessage: "Invalid username"
                                onValidate: {
                                    if(htPasswordInput.text=="")
                                        state = ValidationState.Invalid
                                }
                            }
                        }
                    }
                }
            }
        }
        onCreationCompleted: {
            tempBlogUrl = cpManager.blogUrl
            tempBlogRPCUrl = cpManager.blogRPCUrl
            tempBlogUsername = cpManager.blogUsername
            tempBlogPassword = cpManager.blogPassword
        }
    }    
}
