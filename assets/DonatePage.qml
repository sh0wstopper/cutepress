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
        title: qsTr("Donate")
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
                    text: qsTr("Liked this app, found it useful? Motivate me to make it better")
                    multiline: true
                }
                DropDown {
                    id: donateDropDown
                    
                    Option {
                        selected: true
                        value: 1
                        text: qsTr("Little bit ($1)")
                    }
                    Option {
                        value: 2
                        text: qsTr("A little bit more ($2)")
                    } 
                    Option {
                        value: 3
                        text: qsTr("Even more ($3)")
                    } 
                    Option {
                        value: 5
                        text: qsTr("Decent ($5)")
                    }
                    Option {
                        value: 10
                        text: qsTr("Help me get my Passport ($10)")
                    }  
                } 
                Button {
                    text: qsTr("Donate")
                    horizontalAlignment: HorizontalAlignment.Center
                    onClicked: {
                        if(donateDropDown.selectedIndex==0)
                            appUtil.launchBrowser("https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=YYQZCZR2MFA9A")
                        else if(donateDropDown.selectedIndex==1)
                            appUtil.launchBrowser("https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=WSYE2MJJ5KURA")
                        else if(donateDropDown.selectedIndex==2)
                            appUtil.launchBrowser("https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=6FU8UZBVC83TE")
                        else if(donateDropDown.selectedIndex==3)
                            appUtil.launchBrowser("https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=VGSSLV6A2F2GA")
                        else if(donateDropDown.selectedIndex==4)
                            appUtil.launchBrowser("https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=XGUL6X7FPFH62")
                    }
                }
                
            }
            Container {
                topPadding: ui.sdu(3.0)
                horizontalAlignment: HorizontalAlignment.Fill
                layout: StackLayout {}
                Label {
                    text: qsTr("Alternatively, you can buy my paid apps from BlackBerry World!")
                    multiline: true
                }
                Button {
                    text: qsTr("More apps by ShowStopper")
                    horizontalAlignment: HorizontalAlignment.Center
                    attachedObjects: [
                        Invocation {
                            id: invoke
                            query: InvokeQuery {
                                mimeType: "application/x-bb-appworld"
                                uri: "appworld://vendor/35407"
                            }
                        }
                    ]            
                    onClicked: {
                        invoke.trigger("bb.action.OPEN")
                    }   
                }
            }
        }
    }
}
