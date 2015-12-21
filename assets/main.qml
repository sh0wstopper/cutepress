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
import com.cutepress.manager 1.0
import com.cutepress.cputil 1.0
import com.cutepress.settings 1.0
import com.cutepress.util 1.0
import "UIConstants.js" as UI


CutePressTabbedPane {
    id: mainWindow
    showTabsOnActionBar: true
	
    attachedObjects: [
        CPManager {
            id: cpManager
        },
        CPUtil {
            id: cpUtil
            onLastCreatedPageIdChanged: {
                if(lastCreatedPageId!="")
                    cpUtil.fetchPage(lastCreatedPageId)
            }
            onLastCreatedPostIdChanged: {
                if(lastCreatedPostId!="")
                    cpUtil.fetchPost(lastCreatedPostId)
            }
            onLastCreatedCategoryIdChanged: {
                if(lastCreatedCategoryId!="")
                    cpUtil.fetchCategories()
            }
            onLastCreatedMediaIdChanged: {
                console.log("Main.qml----Media Created", lastCreatedMediaId, editorUploadImagesCount())
                if(lastCreatedMediaId!="" && editorUploadImagesCount()<=1)
                    cpUtil.fetchMediaItem(lastCreatedMediaId)
            }
            onPostsStateChanged: {
                if(postsState==UI.ProgressState.Success) {
                    if(appSettings.readData("Is_Get_Post_Comment_Count")=="true")
                        fetchCommentCountForAllPosts()
                }
            }
        },
        AppSettings {
            id: appSettings
        },
        AppUtil {
            id: appUtil
        }
	]
//	Page {
//	    Container {
//	        //Todo: fill me with QML
//	        layout: StackLayout {
//	            
//	        }
//	        Label {
//	            // Localized text with the dynamic translation and locale updates support
//	            text: qsTr("Hello World") + Retranslate.onLocaleOrLanguageChanged
//	            textStyle.base: SystemDefaults.TextStyles.BigText
//	        }
//	        
//	        TextField {
//	            id: blogAddressInput
//	            text: "http://theshowstopper.in/"
//	        }
//	        
//	        TextField {
//	            id: blogUsernameInput
//	            text: "admin"
//	        }
//	        
//	        TextField {
//	            id: blogPasswordInput
//	            text: "kumar_22"    
//	            inputMode: TextFieldInputMode.Password        
//	        }
//	        Button {
//	            text: "Sign in"
//	            onClicked: {
//	                cpManager.blogUrl = blogAddressInput.text
//	                cpManager.blogUsername = blogUsernameInput.text
//	                cpManager.blogPassword = blogPasswordInput.text
//	                cpUtil.getBlogs()
//	            }
//            }
//            Button {
//                text: "New Blog"
//                onClicked: {
//                    var nSheet = newBlogSheetDefinition.createObject()
//                    nSheet.open()
//                }
//            }
//            Button {
//                text: "Sign in"
//                onClicked: {
//                    var nPage = debugPageDefinition.createObject()
//                    mainWindow.push(nPage)
//                }
//            }
//	    }
//	}
    
    Menu.definition: MenuDefinition {
        // Specify the actions that should be included in the menu
        actions: [
            ActionItem {
                title: qsTr("About")
                imageSource: "asset:///images/info.png"
                onTriggered: {
                    var npage = aboutPageDefinition.createObject();
                    mainWindow.push(npage);
                }
                attachedObjects: [
                    ComponentDefinition {
                        id: aboutPageDefinition
                        source: "AboutPage.qml"
                    }
                ]
            },
            ActionItem {
                title: qsTr("Help")
                imageSource: "asset:///images/help.png"
                onTriggered: {
                    var npage = helpPageDefinition.createObject();
                    mainWindow.push(npage);
                }
                attachedObjects: [
                    ComponentDefinition {
                        id: helpPageDefinition
                        source: "HelpPage.qml"
                    }
                ]
            },
            ActionItem {
                title: qsTr("Settings")
                imageSource: "asset:///images/settings.png"
                onTriggered: {
                    var nSheet = settingsSheetDefinition.createObject(mainWindow.top());
                    nSheet.open();
                }
                attachedObjects: [
                    ComponentDefinition {
                        id: settingsSheetDefinition
                        source: "SettingsPage.qml"
                    }
                ]
            },
            ActionItem {
                title: qsTr("Donate")
                imageSource: "asset:///images/donate.png"
                onTriggered: {
                    var nPage = donatePageDefinition.createObject();
                    mainWindow.push(nPage);
                }
                attachedObjects: [
                    ComponentDefinition {
                        id: donatePageDefinition
                        source: "DonatePage.qml"
                    }
                ]
            }//,
//		    ActionItem {
//		        title: qsTr("Open debug")
//		        onTriggered: {                
//		            mainWindow.openDebug()
//		        }
//		    }
	    ]
    }
	BlogListsTab {
    	id: mainTab
        title: qsTr("Blogs")
        imageSource: "asset:///images/blogs.png"
	}
    PagesTab {
        id: pagesTab
        enabled: cpUtil.blogs.size()>0
        title: qsTr("Pages")
        imageSource: "asset:///images/page.png"
    }
    PostsTab {
        id: postsTab
        enabled: cpUtil.blogs.size()>0
        title: qsTr("Posts")
        imageSource: "asset:///images/post.png"
    }
    CommentsTab {
        id: commentsTab
        enabled: cpUtil.blogs.size()>0
        title: qsTr("Comments")
        imageSource: "asset:///images/comment.png"
    }
    MediaTab {
        id: mediaTab
        enabled: cpUtil.blogs.size()>0
        title: qsTr("Media")
        imageSource: "asset:///images/image.png"
    }
    CategoriesTab {
        id: categoriesTab
        enabled: cpUtil.blogs.size()>0
        title: qsTr("Categories")
        imageSource: "asset:///images/categories.png"
    }
//    TagsTab {
//        id: tagsTab
//        title: qsTr("Tags")
//    }
    onCreationCompleted: {
        if(cpUtil.blogs.size()>0)
            mainWindow.activeTab  = postsTab
    }
}
