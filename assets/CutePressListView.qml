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

ListView {    
    function scrollToTop() {
        iList.scrollToItem([0], ScrollAnimation.None);
    }

    function openLink(iUrl) {
        appUtil.launchBrowser(iUrl);
    }
    function copyToClipboard(iText) {
        appUtil.copyTextToClipboard(iText);
    }
    
    function openBlogEditorSheet(blogIsWordPress,
                                blogUrl,
                                blogUsername,
                                blogPassword,
                                blogHtUsername,
                                blogHtPassword) {       
        mainWindow.openBlogEditorSheet(blogIsWordPress,
                                 blogUrl,
                                 blogUsername,
                                 blogPassword,
                                 blogHtUsername,
                                 blogHtPassword);
    }
    function openEditPostEditor(iCurrentItem) {
        mainWindow.openEditPostEditor(iCurrentItem)
    }
    function openEditPageEditor(iCurrentItem) {
        mainWindow.openEditPageEditor(iCurrentItem)
    }
    function deletePost(iPost) {
        cpUtil.deletePost(iPost)
    }
    function deleteLocalPost(iPost) {
        cpUtil.deleteLocalPost(iPost)
    }
    function deletePage(iPage) {
        cpUtil.deletePage(iPage)
    }
    function deleteComment(iComment) {
        mainWindow.openDialog(qsTr("Delete comment"), 
        qsTr("Delete selected comment?"), "comment-delete",
        iComment, "")
    }
    function deleteCategory(iCategory) {
        cpUtil.deleteCategory(iCategory)
    }
    function approveComment(iComment) {
        cpUtil.approveComment(iComment)
    }
    function unapproveComment(iComment) {
        cpUtil.unapproveComment(iComment)
    }
    function spamComment(iComment) {
        mainWindow.openDialog(qsTr("Spam comment"), 
            qsTr("Spam selected comment?"), "comment-spam",
            iComment, "")
    }
    function editComment(iComment, iStatus, iContent) {
        cpUtil.editComment(iComment, iStatus, iContent)
    }
    function openDialog(iTitle, iBody, iItemType, iItemId, iLaterAction) {
        mainWindow.openDialog(iTitle, iBody, iItemType, iItemId, iLaterAction)
    }
}