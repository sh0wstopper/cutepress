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

CutePressListView {
    property string lastApprovedCommentId: cpUtil.lastApprovedCommentId
    onLastApprovedCommentIdChanged: {
        if(lastApprovedCommentId!="")
            appUtil.approveCommentInModel(dataModel, lastApprovedCommentId)
        updateModel()
    }
    property string lastUnapprovedCommentId: cpUtil.lastUnapprovedCommentId
    onLastUnapprovedCommentIdChanged: {
        if(lastUnapprovedCommentId!="")
            appUtil.unapproveCommentInModel(dataModel, lastUnapprovedCommentId)
        updateModel()
    }
    property string lastSpammedCommentId: cpUtil.lastSpammedCommentId
    onLastSpammedCommentIdChanged: {
        if(lastSpammedCommentId!="")
            appUtil.spamCommentInModel(dataModel, lastSpammedCommentId)
        updateModel()
    }
    
    property string lastDeletedCommentId: cpUtil.lastDeletedCommentId
    onLastDeletedCommentIdChanged: {
        if(lastDeletedCommentId!="")
            appUtil.deleteCommentInModel(dataModel, lastDeletedCommentId)
        updateModel()
    }
}