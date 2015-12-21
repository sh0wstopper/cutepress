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

#include "cppost.h"

CPPost::CPPost(QObject *parent)
        :AbstractCPObject(parent)
{
	_commentsModel = new RoleItemModel(commentRoleNames, this);
	clear();
}

CPPost::~CPPost()
{

}

void CPPost::clear()
{
    setDebugText("");
	setCpId("");
	setAuthorId("");
	setAuthorDisplayName("");
	setDateCreated(QDateTime());
	setModified(QDateTime());
	setTitle("");
	setUrl("");
	setDescription("");
	setExcerpt("");
	setSlug("");
	setStatus("");
	setPassword("");
	setCommentsOpen(false);
	setPingsOpen(false);
	setCommentsCount(0);
	_categories.clear();
	emit categoriesChanged();
	_tags.clear();
	emit tagsChanged();

	setInfoState(ProgressState::None);
	setInfoStatus("");

	_commentsModel->clearModel();
	setCommentsState(ProgressState::None);
	setCommentsStatus("");
	setAddCommentState(ProgressState::None);
	setAddCommentStatus("");
	setNewCommentId("");
}

void CPPost::setInfo(RoleItemModel* model, const int index)
{
	setInfo(model->value(index).toMap());
}

void CPPost::setInfo(const QVariantMap info)
{
	setAuthorId(info[postRoleNames[PostEntry::WpAuthorRole]].toString());
	setAuthorDisplayName(info[postRoleNames[PostEntry::WpAuthorDisplayNameRole]].toString());
	setDateCreated(info[postRoleNames[PostEntry::DateCreatedRole]].toDateTime());
	setModified(info[postRoleNames[PostEntry::ModifiedRole]].toDateTime());
	setTitle(info[postRoleNames[PostEntry::TitleRole]].toString());
	setUrl(info[postRoleNames[PostEntry::LinkRole]].toString());
	setDescription(info[postRoleNames[PostEntry::DescRole]].toString());
	setExcerpt(info[postRoleNames[PostEntry::ExcerptRole]].toString());
	setSlug(info[postRoleNames[PostEntry::SlugRole]].toString());
	setStatus(info[postRoleNames[PostEntry::StatusRole]].toString());
	setPassword(info[postRoleNames[PostEntry::PasswordRole]].toString());
	setCommentsOpen(info[postRoleNames[PostEntry::CommentsOpenRole]].toInt());
	setPingsOpen(info[postRoleNames[PostEntry::PingsOpenRole]].toInt());
	setCommentsCount(info[postRoleNames[PostEntry::CommentsCountRole]].toInt());
	_categories=info[postRoleNames[PostEntry::CategoriesRole]].toStringList();
	emit categoriesChanged();
	_tags = info[postRoleNames[PostEntry::TagsRole]].toStringList();
	emit tagsChanged();
	setCpId(info[postRoleNames[PostEntry::IdRole]].toString());
}

void CPPost::fetchInfo()
{
    QMultiMap<QString, QVariant> params;
    params.insert("postid", _cpId);
    QStringList order;
    order<<"postid"<<"username"<<"password"<<"blog_id";
    CPAction::CPOperation op = CPAction::GetPost;
    CPAction *request = new CPAction(op, this);
    request->exec("POST", params, order);
    if(requests.contains(op) && requests[op]) {
        requests[op]->abortRequest();
        requests[op]->deleteLater();
    }
    if(request) {
        requests[op] = request;
        taskStarted(op);
        connect(request,SIGNAL(error(int,int,QString)),
                this,SLOT(requestError(int,int,QString)));
        connect(request,SIGNAL(finished(int,QVariant)),
                this,SLOT(requestFinished(int,QVariant)));
    }
}

void CPPost::fetchComments()
{
    qDebug()<<"CPPost---Fetching post comments...";
    QMultiMap<QString, QVariant> params;
    QVariantMap content;
    content["post_id"] = _cpId;
    content["number"] = 40;
    params.insert("content", content);
    QStringList order;
    order<<"blog_id"<<"username"<<"password"<<"content";
    CPAction::CPOperation op = CPAction::GetPostComments;
    CPAction *request = new CPAction(op, this);
    request->exec("POST", params, order);
    if(requests.contains(op) && requests[op]) {
        requests[op]->abortRequest();
        requests[op]->deleteLater();
    }
    if(request) {
        requests[op] = request;
        taskStarted(op);
        connect(request,SIGNAL(error(int,int,QString)),
                this,SLOT(requestError(int,int,QString)));
        connect(request,SIGNAL(finished(int,QVariant)),
                this,SLOT(requestFinished(int,QVariant)));
    }
}

void CPPost::addComment(const QString body, const QString parentId)
{
    qDebug()<<"CPPost---Adding new post comment...";
    QMultiMap<QString, QVariant> params;
    QVariantMap comment;
    comment["content"] = body;
    if(!parentId.isEmpty())
        comment["comment_parent"] = parentId.toInt();
    else
        comment["comment_parent"] = 0;
    params.insert("post_id", _cpId);
    params.insert("comment", comment);
    QStringList order;
    order<<"blog_id"<<"username"<<"password"<<"post_id"<<"comment";
    CPAction::CPOperation op = CPAction::NewComment;
    CPAction *request = new CPAction(op, this);
    request->exec("POST", params, order);
    if(request) {
        requests[op] = request;
        taskStarted(op);
        connect(request,SIGNAL(error(int,int,QString)),
                this,SLOT(requestError(int,int,QString)));
        connect(request,SIGNAL(finished(int,QVariant)),
                this,SLOT(requestFinished(int,QVariant)));
    }
}

void CPPost::requestFinished(const int operation, const QVariant &result)
{
    if(result.isNull() || !result.isValid()) {
        taskFailed(operation, tr("Unknown response"));
        requests[operation]->deleteLater();
        requests.remove(operation);
        return;
    }
    CPAction *reply = qobject_cast<CPAction *>(sender());
    switch(operation) {
        case CPAction::GetPost:
        {
        	QVariantMap post = result.toList().first().toMap();
        	QVariantMap it;
            it[postRoleNames[PostEntry::IdRole]] = post["postid"].toString();
            it[postRoleNames[PostEntry::TitleRole]] = post["title"].toString();
            it[postRoleNames[PostEntry::LocalIdRole]] = post["postid"].toString();
            QString desc;
            if (!post["mt_text_more"].toString().isEmpty()) {
                // post is split into two parts
                desc = post["description"].toString()
                    +   "\n <!--more--> \n"
                    +   post["mt_text_more"].toString();
            } else
                desc = post["description"].toString();
            it[postRoleNames[PostEntry::DescRole]] = desc;
            it[postRoleNames[PostEntry::ContentSnippetRole]] = getHtmlTextSnippet(desc);
            it[postRoleNames[PostEntry::ExcerptRole]] = post["mt_excerpt"].toString();
            it[postRoleNames[PostEntry::SlugRole]] = post["wp_slug"].toString();
            it[postRoleNames[PostEntry::LinkRole]] = post["link"].toString();
            it[postRoleNames[PostEntry::PermaLinkRole]] = post["permaLink"].toString();
            it[postRoleNames[PostEntry::WpAuthorRole]] = post["wp_author_id"].toString();
            it[postRoleNames[PostEntry::WpAuthorDisplayNameRole]] = post["wp_author_display_name"].toString();
            it[postRoleNames[PostEntry::StatusRole]] = post["post_status"].toString();
            it[postRoleNames[PostEntry::PasswordRole]] = post["wp_password"].toString();
            QDateTime d = QDateTime::fromString(post["date_created_gmt"].toString(), "yyyyMMddThh:mm:ss");
            it[postRoleNames[PostEntry::DisplayStatusRole]] = post["post_status"].toString();
            it[postRoleNames[PostEntry::StickyRole]] = post["sticky"].toBool();
            it[postRoleNames[PostEntry::CategoriesRole]] = post["categories"].toStringList();
            it[postRoleNames[PostEntry::TagsRole]] = post["mt_keywords"].toString().split(", ");
            if(d>QDateTime::currentDateTimeUtc())
                it[postRoleNames[PostEntry::DisplayStatusRole]] = "future";
            d.setTimeSpec(Qt::UTC);
            d = d.toLocalTime();
            it[postRoleNames[PostEntry::DateCreatedRole]] = d;
            it[postRoleNames[PostEntry::DisplayDateRole]] = d.toString("ddd hh:mm AP MMM dd, yyyy");
            d = QDateTime::fromString(post["date_modified"].toString(), "yyyyMMddThh:mm:ss");
    //          d.setTimeSpec(Qt::UTC);
    //          d = d.toLocalTime();
            it[postRoleNames[PostEntry::ModifiedRole]] = d;
            it[postRoleNames[PostEntry::DisplayModifiedRole]] = d.toString("ddd hh:mm AP MMM dd, yyyy");
            it[postRoleNames[PostEntry::PostTimeRole]] = d.time();
            it[postRoleNames[PostEntry::PostDateRole]] = d.date();
            it[postRoleNames[PostEntry::CommentsOpenRole]] = post["mt_allow_comments"].toString();
            it[postRoleNames[PostEntry::PingsOpenRole]] = post["mt_allow_pings"].toString();
            it[postRoleNames[PostEntry::CommentsCountRole]] = 0;
            it[postRoleNames[PostEntry::MarkedRole]] = false;
            setInfo(it);
            emit postRefreshed(post);
        } break;
        case CPAction::GetPostComments:
        {
            QVariantList comments = result.toList().first().toList();
            _commentsModel->clearModel();
            appendComments(_commentsModel, comments);
        	qDebug()<<"CPPost---Comments"<<comments.count();
        } break;
        case CPAction::NewComment:
        {
            QString commentId = result.toList().first().toString();
            if(!commentId.isEmpty()) {
                setNewCommentId(commentId);
                taskFinished(operation);
                reply->deleteLater();
                requests.remove(operation);
                fetchComments();
                return;
            }
        } break;
    }
    taskFinished(operation);
    reply->deleteLater();
    requests.remove(operation);
}

void CPPost::requestError(const int operation,const int code,const QString msg)
{
    CPAction *reply = qobject_cast<CPAction *>(sender());
    qDebug()<<"CPPost---Error"<<operation<<code<<msg;
    taskFailed(operation, msg);
    reply->deleteLater();
    requests.remove(operation);
}

void CPPost::taskStarted(const int op)
{
	if(op==CPAction::GetPost) {
		setInfoState(ProgressState::Processing);
		setInfoStatus(tr("Fetching post info..."));
	} else if(op==CPAction::GetPostComments) {
		setCommentsState(ProgressState::Processing);
		setCommentsStatus(tr("Fetching post comments..."));
	} else if(op==CPAction::NewComment) {
		setAddCommentState(ProgressState::Processing);
		setAddCommentStatus(tr("Fetching post comments..."));
	}
}

void CPPost::taskFinished(const int op)
{
	if(op==CPAction::GetPost) {
		setInfoState(ProgressState::Success);
		setInfoStatus(tr("Fetched post info!"));
	} else if(op==CPAction::GetPostComments) {
		setCommentsState(ProgressState::Success);
		setCommentsStatus(tr("Fetched post comments!"));
	} else if(op==CPAction::NewComment) {
		setAddCommentState(ProgressState::Success);
		setAddCommentStatus(tr("Fetched post comments!"));
	}
}

void CPPost::taskFailed(const int op, const QString msg)
{
	if(op==CPAction::GetPost) {
		setInfoState(ProgressState::Error);
		setInfoStatus(msg);
	} else if(op==CPAction::GetPostComments) {
		setCommentsState(ProgressState::Error);
		setCommentsStatus(msg);
	} else if(op==CPAction::NewComment) {
		setAddCommentState(ProgressState::Error);
		setAddCommentStatus(msg);
	}
}

QString CPPost::categoriesAsString()
{
	return _categories.join(", ");
}

QString CPPost::tagsAsString()
{
	return _tags.join(", ");
}
