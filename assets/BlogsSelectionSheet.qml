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
    content: Page {
        titleBar: TitleBar {
            title: qsTr("Select blogs")
            dismissAction: ActionItem {
                title: qsTr("Cancel")
                onTriggered: {
                    iSheet.close()
                    cpUtil.clearFetchedUserBlogs()
                    cpUtil.activateBlog()
                    
                }
            } // ActionItem
            acceptAction: ActionItem {
                title: qsTr("Ok")
                onTriggered: {   
                	cpUtil.addSelectedBlogs()
                	cpUtil.activateBlog()
                	iSheet.close()
                }
            } // ActionItem
        }
        Container {
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Fill
            
            ListView {
                id: iList
                function toggleActiveInSelectedBlogs(pos) {
                    cpUtil.toggleActiveInSelectedBlogs(pos)
                }
                function toggleBlogSelection(pos) {
                    cpUtil.toggleBlogSelection(pos)
                }
                dataModel: cpUtil.selectBlogs
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill
                listItemComponents: [
                    ListItemComponent {
                        type: "item"
                        Container {
                            id: rootContainer
                            property bool isHighlighted: false
                            horizontalAlignment: HorizontalAlignment.Fill
                            verticalAlignment: VerticalAlignment.Fill
                            layout: DockLayout {
                            }
                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill
                                layout: StackLayout {
                                }
                                Container {
                                    leftPadding: ui.sdu(2)
                                    rightPadding: leftPadding
                                    topPadding: ui.sdu(1)
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    layout: DockLayout {
                                    }
	                                Container {
	                                    horizontalAlignment: HorizontalAlignment.Fill
	                                    verticalAlignment: VerticalAlignment.Fill
	                                    layout: StackLayout {
	                                    }
	                                    Label {
	                                        multiline: true
	                                        textStyle {
	                                            base: SystemDefaults.TextStyles.BodyText
	                                            fontSize: FontSize.Small
	                                            //                                    color: Color.create(0.1, 0.4, 0.8)
                                                fontWeight: ListItemData.blogIsActive?FontWeight.Bold:FontWeight.Normal
	                                        }
	                                        textFormat: TextFormat.Html
	                                        visible: text != ""
	                                        text: ListItemData.blogName
	                                    } // Label
	                                    Label {
	                                        textStyle {
	                                            base: SystemDefaults.TextStyles.NormalText
	                                            color: Color.create("#A8B1BA")
	                                            fontSize: FontSize.Small
	                                        }
	                                        visible: text != ""
	                                        text: ListItemData.blogUrl
	                                    } // Label
	                                }
	                                CheckBox {
                                    	id: selectedCheck
                                    	checked: ListItemData.blogMarked
                                    	horizontalAlignment: HorizontalAlignment.Right
                                    	verticalAlignment: VerticalAlignment.Center
                                    	onCheckedChanged: {
                                        	if(checked!=ListItemData.blogMarked)
                                                rootContainer.ListItem.view.toggleBlogSelection(ListItemData.index)
                                        } 
                                    }
	                            }
                                Divider {
                                }
                            }
                            Container {
                                id: highlight
                                background: Color.Gray
                                opacity: (rootContainer.isHighlighted) ? 0.5 : 0.0
                                horizontalAlignment: HorizontalAlignment.Fill
                                verticalAlignment: VerticalAlignment.Fill
                            }
                            
                            // Both the activation and selection of an item has the same visual appearance, we alter the opacity of the item.
                            function setHighlight(highlighted) {
                                rootContainer.isHighlighted = highlighted
                            }
                            
                            // Signal handler for ListItem activation
                            ListItem.onActivationChanged: {
                                setHighlight(ListItem.active);
                            }
                            
                            // Signal handler for ListItem selection
                            ListItem.onSelectionChanged: {
                                setHighlight(ListItem.selected);
                            }
                            
                            contextActions: [
                                ActionSet {
                                    id: cntxtMenu
                                    title: qsTr("Blog options")
                                    subtitle: ListItemData.blogName //"This is an action set."
                                    
                                    actions: [
                                        ActionItem {
                                            title: qsTr("Set active")
                                            enabled: ListItemData.blogMarked
                                            imageSource: "asset:///images/edit.png"
                                            onTriggered: {
                                                if(ListItemData.blogMarked && !ListItemData.blogIsActive)
                                                    rootContainer.ListItem.view.toggleActiveInSelecetdBlogs(ListItemData.index)
                                            }
                                        }
                                    ]
                                } // end of ActionSet
                            ] // end of contextActions list
                        }
                    }
                ]
                attachedObjects: [
                    ListScrollStateHandler {
                        id: scrollStateHandler
                        onAtEndChanged: {
                            if (scrollStateHandler.atEnd) {
                                //                            iList.loadMoreItems()
                            }
                        }
                    }
                ]
                onTriggered: {
                }
            }
        }
    }    
}
