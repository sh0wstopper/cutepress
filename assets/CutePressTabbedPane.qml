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
import com.cutepress.timer 1.0
import "UIConstants.js" as UI

TabbedPane {
    id: root
    function push(iPage) {
        activeTab.push(iPage)
    }
    function pop(iPage) {
        activeTab.pop(iPage)
    }
    function top() {
        return activeTab.top()
    }
    function count() {
        return activeTab.count()
    }
    function navigateToFirst() {
        activeTab.navigateToFirst()
    }
    function showInfoBanner(txt) {
        banner.body = txt;
        banner.show();
    }
    function destroySheet(iSheet) {
        sheetDestroyer.currentSheet = iSheet;
        sheetDestroyer.start();
    }
    
    function openBlogListForSelection() {
        var iSheet = blogsSelectionSheetDefinition.createObject(root)
        iSheet.open()
    }
    
    function openPost(post) {
        cpUtil.fetchPostCommentsCount(post.postId)
        var iPage = postPageDefinition.createObject()
        iPage.setPostInfo(post)
        root.push(iPage)
    }
    
    function openPage(pge) {
        var iPage = pagePageDefinition.createObject()
        iPage.setPageInfo(pge)
        root.push(iPage)
    }
    
    function openDebug() {
        var iPage = debugPageDefinition.createObject()
        root.push(iPage)
    }
    
    function openTagsPage() {
        var npage = tagsPageDefinition.createObject()
        mainWindow.push(npage)
    }
    
    function openNewPostEditor() {
        cpUtil.clearPostEditionData()
        var iSheet = postEditorSheetDefinition.createObject(root)
        iSheet.open()
    }
    
    function openNewPageEditor() {
        cpUtil.clearPageEditionData()
        var iSheet = pageEditorSheetDefinition.createObject(root)
        iSheet.open()
    }
    
    function openNewCategoryEditor() {
        var iSheet = categoryEditorSheetDefinition.createObject(root)
        iSheet.open()
    }
    
    function openNewMediaEditor() {
        var iSheet = mediaEditorSheetDefinition.createObject(root)
        iSheet.open()
    }
    
    function openImageViewer(imageUrl, name, description, iDate) {
        var iPage = singleImageViewerPageDefinition.createObject()
        iPage.imageUrl = imageUrl
        iPage.titleText = name
        iPage.descriptionText = description
        iPage.linkText = imageUrl
        iPage.dateText = iDate
        root.push(iPage)
    }
    
    function openEditPostEditor(iCurrentItem) {
        cpUtil.clearPostEditionData()
        var nSheet = postEditorSheetDefinition.createObject(root.top());
        nSheet.isEditing = true
        nSheet.titleText = iCurrentItem.postTitle
        nSheet.bodyText = iCurrentItem.postDescription
        console.log("Dabba", iCurrentItem.postDisplayStatus)
        if(iCurrentItem.postPublishStatus=="private")
            nSheet.statusIndex = 1
        else if(iCurrentItem.postPublishStatus=="draft")
            nSheet.statusIndex = 2
        else if(iCurrentItem.postPublishStatus=="pending")
            nSheet.statusIndex = 3
        else if(iCurrentItem.postPublishStatus=="localdraft") {
            nSheet.statusIndex = 4
            cpUtil.prepareUploadListForSavedItem(iCurrentItem.postDescription)
        } else 
            nSheet.statusIndex = 0
        nSheet.passwordText = iCurrentItem.postPassword
        nSheet.timeValue = iCurrentItem.postDateCreated
        nSheet.slugText = iCurrentItem.postSlug
        nSheet.excerptText = iCurrentItem.postExcerpt
        nSheet.tagsText = appUtil.tagsFromList(iCurrentItem.postTags)
        nSheet.categoriesText = appUtil.categoriesFromList(iCurrentItem.postCategories)
        nSheet.commentsOpenValue = iCurrentItem.postCommentsOpen
        nSheet.pingsOpenValue = iCurrentItem.postPingsOpen
        nSheet.postId = iCurrentItem.postId
        nSheet.postItem = iCurrentItem
        nSheet.open();
    }
    
    
    function openEditPostEditorUsingObject(iPost) {
        cpUtil.clearPostEditionData()
        var nSheet = postEditorSheetDefinition.createObject(root.top());
        nSheet.isEditing = true
        nSheet.titleText = iPost.title
        nSheet.bodyText = iPost.description
        if(iPost.status=="private")
            nSheet.statusIndex = 1
        else if(iPost.status=="draft")
            nSheet.statusIndex = 2
        else if(iPost.status=="pending")
            nSheet.statusIndex = 3
        else if(iPost.status=="localdraft") {
            nSheet.statusIndex = 4
            cpUtil.prepareUploadListForSavedItem(iPost.description)
        }
        else 
            nSheet.statusIndex = 0
        nSheet.passwordText = iPost.password
        nSheet.timeValue = iPost.dateCreated
        nSheet.slugText = iPost.slug
        nSheet.excerptText = iPost.excerpt
        nSheet.tagsText = iPost.tagsAsString
        nSheet.categoriesText = iPost.categoriesAsString
        nSheet.commentsOpenValue = iPost.commentsOpen
        nSheet.pingsOpenValue = iPost.pingsOpen
        nSheet.postId = iPost.cpId
        nSheet.postObject = iPost
        nSheet.caller = root.top()
        nSheet.open();
    }
    
    function openEditPageEditor(iCurrentItem) {
        cpUtil.clearPageEditionData()
        var nSheet = pageEditorSheetDefinition.createObject(root.top());
        nSheet.isEditing = true
        nSheet.titleText = iCurrentItem.pageTitle
        nSheet.bodyText = iCurrentItem.pageDescription
        console.log("Dabba",iCurrentItem.pagePublishStatus)
        if(iCurrentItem.pagePublishStatus=="private")
            nSheet.statusIndex = 1
        else if(iCurrentItem.pagePublishStatus=="draft")
            nSheet.statusIndex = 2
        else if(iCurrentItem.pagePublishStatus=="localdraft") {
            nSheet.statusIndex = 3
            cpUtil.prepareUploadListForSavedItem(iCurrentItem.pageDescription)
        } else 
            nSheet.statusIndex = 0
        nSheet.passwordText = iCurrentItem.pagePassword
        nSheet.timeValue = iCurrentItem.pageDateCreated
        nSheet.slugText = iCurrentItem.pageSlug
        nSheet.excerptText = iCurrentItem.pageExcerpt
        nSheet.commentsOpenValue = iCurrentItem.pageCommentsOpen
        nSheet.pingsOpenValue = iCurrentItem.pagePingsOpen
        nSheet.pageId = iCurrentItem.pageId
        nSheet.pageItem = iCurrentItem
        nSheet.open();
    }
    
    
    function openEditPageEditorUsingObject(iPage) {
        cpUtil.clearPageEditionData()
        var nSheet = pageEditorSheetDefinition.createObject(root.top());
        nSheet.isEditing = true
        nSheet.titleText = iPage.title
        nSheet.bodyText = iPage.description
        if(iPage.displayStatus=="private")
            nSheet.statusIndex = 1
        else if(iPage.displayStatus=="draft")
            nSheet.statusIndex = 2
        else if(iPage.displayStatus=="localdraft") {
            nSheet.statusIndex = 3
            cpUtil.prepareUploadListForSavedItem(iPage.description)
        } else 
            nSheet.statusIndex = 0
        nSheet.passwordText = iPage.wpPassword
        nSheet.timeValue = iPage.dateCreated
        nSheet.slugText = iPage.wpSlug
        nSheet.excerptText = iPage.mtExcerpt
        nSheet.commentsOpenValue = iPage.mtAllowComments
        nSheet.pingsOpenValue = iPage.mtAllowPings
        nSheet.pageId = iPage.cpId
        nSheet.pageObject = iPage
        nSheet.caller = root.top()
        nSheet.open();
    }
    
    function openImageSelector(caller, pos) {
        var iSheet = imageSelectionSheetDefinition.createObject(root)
        iSheet.caller = caller
        iSheet.insertPosition = pos
        iSheet.open()
    }
        
    function openDialog(iTitle, iBody, iItemType, iItemId, iLaterAction) {
        queryDialog.title = iTitle
        queryDialog.body = iBody
        queryDialog.itemId = iItemId
        queryDialog.itemType = iItemType
        queryDialog.laterAction = iLaterAction
        queryDialog.show()
    }
    
    function openNewBlogSheet() {       
        var nSheet = newBlogSheetDefinition.createObject(root.top())
        nSheet.open()
    }
    
    attachedObjects: [
        SystemToast {
            id: banner
            position: SystemUiPosition.TopCenter
        },
        Timer {
            id: sheetDestroyer
            property variant currentSheet: 0
            interval: 500
            singleShot: true
            onTimeout: {
                if(currentSheet==0) return;
                currentSheet.destroy();
                currentSheet = 0;
            }
        },
        ComponentDefinition {
            id: blogsSelectionSheetDefinition
            source: "BlogsSelectionSheet.qml"
        },
        ComponentDefinition {
            id: postPageDefinition
            source: "PostPage.qml"
        },
        ComponentDefinition {
            id: pagePageDefinition
            source: "PagePage.qml"
        },
        ComponentDefinition {
            id: debugPageDefinition
            source: "DebugPage.qml" 
        },
        ComponentDefinition {
            id: postEditorSheetDefinition
            source: "PostEditorSheet.qml" 
        },
        ComponentDefinition {
            id: pageEditorSheetDefinition
            source: "PageEditorSheet.qml" 
        },
        ComponentDefinition {
            id: categoryEditorSheetDefinition
            source: "CategoryEditorSheet.qml" 
        },
        ComponentDefinition {
            id: mediaEditorSheetDefinition
            source: "MediaEditorSheet.qml" 
        },
        ComponentDefinition {
            id: singleImageViewerPageDefinition
            source: "SingleImageViewerPage.qml" 
        },
        ComponentDefinition {
            id: imageSelectionSheetDefinition
            source: "ImageSelectionSheet.qml" 
        },
        ComponentDefinition {
            id: tagsPageDefinition
            source: "TagsPage.qml" 
        },
        ComponentDefinition {
            id: newBlogSheetDefinition
            source: "NewBlogSheet.qml" 
        },
        SystemDialog {
            id: queryDialog
            property string laterAction: ""
            property string itemType: ""
            property string itemId: ""
            title: qsTr("Delete post")
            body: qsTr("Do you really want to delete post?")// + postId
            onFinished: {
                if(queryDialog.result == SystemUiResult.ConfirmButtonSelection) {
                    console.log(itemType, itemId, laterAction)
                    if(queryDialog.itemType=="" || (queryDialog.itemType!="blogs-remove" && queryDialog.itemId=="")) return;
                    if(queryDialog.itemType=="blogs-remove") {
                        cpManager.clear()           
                        cpUtil.removeAllBlogs()
                    } else if(queryDialog.itemType=="blog-remove") {
                        cpUtil.removeBlog(queryDialog.itemId*1)
                    } else if(queryDialog.itemType=="page-delete") {
                        cpUtil.deletePage(queryDialog.itemId)
                    } else if(queryDialog.itemType=="post-delete") {
                        cpUtil.deletePost(queryDialog.itemId)                    
                    } else if(queryDialog.itemType=="category-delete") {
                        cpUtil.deleteCategory(queryDialog.itemId)                    
                    } else if(queryDialog.itemType=="comment-delete") {
                        cpUtil.deleteComment(queryDialog.itemId)                    
                    } else if(queryDialog.itemType=="comment-spam") {
                        cpUtil.spamComment(queryDialog.itemId)                    
                    }
                    if(queryDialog.laterAction=="pop")
                        mainWindow.pop()
                }
            }
        }
    ]
}
