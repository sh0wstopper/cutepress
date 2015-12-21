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

#include "cputil.h"
#include <QDebug>
#include <QNetworkAccessManager>

CPUtil::CPUtil(QObject* parent)
    :AbstractCPObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data/cutepress.sqlite");
    if (!db.open()) {
        qDebug()<<tr("CPUtil---Unable to establish a database connection.");
    } else {
        if(!db.tables(QSql::AllTables).contains("blogs")) {
            qDebug()<<"CPUtil---Need to create table!";
            QSqlQuery query;
            qDebug()<<"CPUtil---Create blogs table"<<query.exec("CREATE TABLE blogs (blogUrl VARCHAR(255) primary key, "
                       "blogName VARCHAR(255), "
            		   "xmlRpcUrl VARCHAR(255), "
            		   "blogId VARCHAR(25), "
            		   "htUsername VARCHAR(60), "
            		   "htPassword VARCHAR(64), "
            		   "username VARCHAR(60), "
            		   "password VARCHAR(64), "
            		   "isAdmin boolean, "
            		   "isWordpress boolean, "
            		   "pagesCount integer, "
            		   "postsCount integer, "
            		   "numberOfPosts integer, "
            		   "commentsCount integer, "
            		   "isActive boolean,"
            		   "sanitizedUrl VARCHAR(255))");
            qDebug()<<"CPUtil---Tables"<<db.tables(QSql::AllTables);
        }
    }
	manager = new QNetworkAccessManager(this);

    _blogsModel = new RoleItemModel(blogRoleNames, this);
	emit blogsChanged();
    _selectBlogsModel = new RoleItemModel(blogRoleNames, this);
	emit selectBlogsChanged();
    _postsModel = new RoleItemModel(postRoleNames, this);
	emit postsChanged();
    _pagesModel = new RoleItemModel(pageRoleNames, this);
	emit pagesChanged();
    _commentsModel = new RoleItemModel(commentRoleNames, this);
	emit commentsChanged();
    _mediaItemsModel = new RoleItemModel(mediaRoleNames, this);
    emit mediaItemsChanged();
    _categoriesModel = new RoleItemModel(categoryRoleNames, this);
    emit categoriesChanged();
    _tagsModel = new RoleItemModel(tagRoleNames, this);
    emit tagsChanged();

    clear();
    readBlogsFromDB();
    activateBlog();
}

CPUtil::~CPUtil()
{

}

void CPUtil::clear()
{
	_blogsModel->clearModel();
	emit blogsChanged();
	_selectBlogsModel->clearModel();
	emit selectBlogsChanged();
	setBlogAdditionState(ProgressState::None);
	setBlogAdditionStatus("");
	clearBlogData();
}

void CPUtil::clearBlogData()
{
	_postsModel->clearModel();
	emit postsChanged();
	setPostsState(ProgressState::None);
	setPostsStatus("");
	setPostEditionState(ProgressState::None);
	setPostEditionStatus("");
	_pagesModel->clearModel();
	emit pagesChanged();
	setPagesState(ProgressState::None);
	setPagesStatus("");
	setPageEditionState(ProgressState::None);
	setPageEditionStatus("");
	_commentsModel->clearModel();
	emit commentsChanged();
	setCommentsState(ProgressState::None);
	setCommentsStatus("");
	_mediaItemsModel->clearModel();
	emit mediaItemsChanged();
	setMediaItemsState(ProgressState::None);
	setMediaItemsStatus("");
	_tagsModel->clearModel();
	emit tagsChanged();
	setTagsState(ProgressState::None);
	setTagsStatus("");
	_categoriesModel->clearModel();
	emit categoriesChanged();
	setCategoriesState(ProgressState::None);
	setCategoriesStatus("");
	setCategoryEditionState(ProgressState::None);
	setCategoryEditionStatus("");
	setMediaUploadState(ProgressState::None);
	setMediaUploadStatus("");
    setEditorImageUploadState(ProgressState::None);
    setEditorImageUploadStatus("");
    setEditorUploadImageUrl("");
    setEditorUploadedImageUrl("");

	setLastCreatedPageId("");
    setLastDeletedPageId("");
    setLastCreatedPostId("");
    setLastDeletedPostId("");
	setLastDeletedCommentId("");
	setLastCreatedCategoryId("");
    setLastDeletedCategoryId("");
	setLastApprovedCommentId("");
	setLastUnapprovedCommentId("");
	setLastSpammedCommentId("");
    setLastCreatedMediaId("");
}

void CPUtil::getBlogs()
{
	QMultiMap<QString, QVariant> params;
	CPAction::CPOperation op = CPAction::GetUserBlogs;
    CPAction *request = new CPAction(op, this);
    request->exec("POST", params);

    if(request) {
    	request->setProperty("username", CPEngine::instance().blogUsername());
    	request->setProperty("password", CPEngine::instance().blogPassword());
//    	request->setProperty("htUsername", CPEngine::instance().);
//    	request->setProperty("htPassword", CPEngine::instance().blogPassword());
        requests[op] = request;
        taskStarted(op);
        connect(request,SIGNAL(error(int,int,QString)),
                this,SLOT(requestError(int,int,QString)));
        connect(request,SIGNAL(finished(int,QVariant)),
                this,SLOT(requestFinished(int,QVariant)));
    }

}

void CPUtil::fetchRecentPosts()
{
	QMultiMap<QString, QVariant> params;
	CPAction::CPOperation op = CPAction::GetPosts;
    CPAction *request = new CPAction(op, this);
    params.insert("numberOfPosts", "50");
    request->exec("POST", params);
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

void CPUtil::fetchPost(const QString  postId)
{
    QMultiMap<QString, QVariant> params;
    params.insert("postid", postId);
    QStringList order;
    order<<"postid"<<"username"<<"password"<<"blog_id";
    CPAction::CPOperation op = CPAction::GetPost;
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

void CPUtil::fetchPostCommentsCount(const QString  postId)
{
    QMultiMap<QString, QVariant> params;
    params.insert("postid", postId);
    QStringList order;
    order<<"blog_id"<<"username"<<"password"<<"postid";
    CPAction::CPOperation op = CPAction::GetPostCommentsCount;
    CPAction *request = new CPAction(op, this);
    request->exec("POST", params, order);
    if(request) {
        request->setProperty("postId", postId);
        requests[op] = request;
        taskStarted(op);
        connect(request,SIGNAL(error(int,int,QString)),
                this,SLOT(requestError(int,int,QString)));
        connect(request,SIGNAL(finished(int,QVariant)),
                this,SLOT(requestFinished(int,QVariant)));
    }
}

void CPUtil::fetchPages()
{
	QMultiMap<QString, QVariant> params;
    params.insert("max_pages", "25");
	CPAction::CPOperation op = CPAction::GetPages;
    CPAction *request = new CPAction(op, this);
    request->exec("POST", params);
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

void CPUtil::fetchPage(const QString pageId)
{
    QMultiMap<QString, QVariant> params;
    CPAction::CPOperation op = CPAction::GetPage;
    QStringList order;
    order<<"blog_id"<<"page_id"<<"username"<<"password";
    CPAction *request = new CPAction(op, this);
    params.insert("page_id", pageId);
    request->exec("POST", params, order);
    if(request) {
        request->setProperty("pageId", pageId);
        requests[op] = request;
        taskStarted(op);
        connect(request,SIGNAL(error(int,int,QString)),
                this,SLOT(requestError(int,int,QString)));
        connect(request,SIGNAL(finished(int,QVariant)),
                this,SLOT(requestFinished(int,QVariant)));
    }
}

void CPUtil::fetchComments()
{
	QMultiMap<QString, QVariant> params;
	QVariantMap content;
	content["number"] = 40;
	params.insert("content", content);
	QStringList order;
	order<<"blog_id"<<"username"<<"password"<<"content";
	CPAction::CPOperation op = CPAction::GetComments;
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

void CPUtil::fetchComment(const QString commentId)
{
    QMultiMap<QString, QVariant> params;
    params.insert("comment_id", commentId);
    QStringList order;
    order<<"blog_id"<<"username"<<"password"<<"comment_id";
    CPAction::CPOperation op = CPAction::GetComment;
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

void CPUtil::fetchMediaItems()
{
	QMultiMap<QString, QVariant> params;
	CPAction::CPOperation op = CPAction::GetMediaLibrary;
    CPAction *request = new CPAction(op, this);
    request->exec("POST", params);
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

void CPUtil::fetchMediaItem(const QString mediaId)
{
    QMultiMap<QString, QVariant> params;
    params.insert("attachment_id", mediaId);
    QStringList order;
    order<<"blog_id"<<"username"<<"password"<<"attachment_id";
    CPAction::CPOperation op = CPAction::GetMediaItem;
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

void CPUtil::fetchCategories()
{
	QMultiMap<QString, QVariant> params;
	CPAction::CPOperation op = CPAction::GetCategories;
    CPAction *request = new CPAction(op, this);
    request->exec("POST", params);
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

void CPUtil::fetchTags()
{
	QMultiMap<QString, QVariant> params;
	CPAction::CPOperation op = CPAction::GetTags;
    CPAction *request = new CPAction(op, this);
    request->exec("POST", params);
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

void CPUtil::createNewPost(QString dateCreated,
                       QString title,
                       QString description,
                       QString excerpt,
                       QString slug,
                       QString status,
                       QString password,
                       QString categories,
                       QString tags,
                       bool commentsOpen,
                       bool pingsOpen,
                       bool sticky)
{

	QMultiMap<QString, QVariant> params;
	QVariantMap content;
	content["post_type"] = "post";
	content["title"] = title;
	content["description"] = description;
	QDateTime dt = QDateTime::fromString(dateCreated, Qt::ISODate);
	dt.addSecs(-60);
	content["date_created_gmt"] = dt;
	if(!categories.isEmpty()) {
		categories = categories.replace(", ", ",");
		categories = categories.replace(" ,", ",");
		content["categories"] = categories.split(",");
	}
	if(!tags.isEmpty()) {
		tags = tags.replace(", ", ",");
		tags = tags.replace(" ,", ",");
		content["mt_keywords"] = tags.split(",");
	}
	content["mt_excerpt"] = excerpt;
	content["wp_slug"] = slug;
	content["wp_password"] = password;
	content["post_status"] = status;
	content["publish"] = status!="draft";
	content["sticky"] = sticky;
	content["mt_allow_comments"] = commentsOpen?"open":"closed";
	content["mt_allow_pings"] = pingsOpen?"open":"closed";
	//qDebug()<<dt<<content;
	params.insert("content", content);
	CPAction::CPOperation op = CPAction::NewPost;
    CPAction *request = new CPAction(op, this);
    request->exec("POST", params);
    if(request) {
        requests[op] = request;
        taskStarted(op);
        connect(request,SIGNAL(error(int,int,QString)),
                this,SLOT(requestError(int,int,QString)));
        connect(request,SIGNAL(finished(int,QVariant)),
                this,SLOT(requestFinished(int,QVariant)));
    }
}

void CPUtil::editPost(const QString postId,
                QString dateCreated,
                       QString title,
                       QString description,
                       QString excerpt,
                       QString slug,
                       QString status,
                       QString password,
                       QString categories,
                       QString tags,
                       bool commentsOpen,
                       bool pingsOpen,
                       bool sticky)
{

    QMultiMap<QString, QVariant> params;
    QVariantMap content;
    content["post_type"] = "post";
    content["title"] = title;
    content["description"] = description;
    QDateTime dt = QDateTime::fromString(dateCreated, Qt::ISODate);
    content["date_created_gmt"] = dt;
    if(!categories.isEmpty()) {
        categories = categories.replace(", ", ",");
        categories = categories.replace(" ,", ",");
        content["categories"] = categories.split(",");
    }
    if(!tags.isEmpty()) {
        tags = tags.replace(", ", ",");
        tags = tags.replace(" ,", ",");
        content["mt_keywords"] = tags.split(",");
    }
    content["mt_excerpt"] = excerpt;
    content["wp_slug"] = slug;
    content["wp_password"] = password;
    content["post_status"] = status;
    content["sticky"] = sticky;
    content["mt_allow_comments"] = commentsOpen?"open":"closed";
    content["mt_allow_pings"] = pingsOpen?"open":"closed";
    //qDebug()<<dt<<content<<content["categories"];
    params.insert("postid", postId);
    params.insert("content", content);
    params.insert("publish", status!="draft");
    QStringList order;
    order<<"postid"<<"username"<<"password"<<"content"<<"publish";
    CPAction::CPOperation op = CPAction::EditPost;
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

void CPUtil::deletePost(const QString postId)
{
    for(int i=0;i<_postsModel->size();i++) {
        QVariantMap item = _postsModel->value(i).toMap();
        if(item[postRoleNames[PostEntry::IdRole]].toString()==postId) {
            if(item[postRoleNames[PostEntry::StatusRole]].toString()=="localdraft") {
                deleteLocalPost(postId);
                return;
            } else
                break;
        }
    }

	QMultiMap<QString, QVariant> params;
	params.insert("appkey", "123");
	params.insert("postid", postId);
	params.insert("publish", true);
	QStringList order;
	order<<"appkey"<<"postid"<<"username"<<"password"<<"publish";
	CPAction::CPOperation op = CPAction::DeletePost;
    CPAction *request = new CPAction(op, this);
    request->exec("POST", params, order);
    if(request) {
    	request->setProperty("postId", postId);
        requests[op] = request;
        taskStarted(op);
        connect(request,SIGNAL(error(int,int,QString)),
                this,SLOT(requestError(int,int,QString)));
        connect(request,SIGNAL(finished(int,QVariant)),
                this,SLOT(requestFinished(int,QVariant)));
    }
}

void CPUtil::createNewPage(QString dateCreated,
                       QString title,
                       QString description,
                       QString excerpt,
                       QString slug,
                       QString status,
                       QString password,
                       bool commentsOpen,
                       bool pingsOpen,
                       int pageParentId,
                       int pageOrder)
{

	QMultiMap<QString, QVariant> params;
	QVariantMap content;
	content["post_type"] = "page";
	content["title"] = title;
	content["description"] = description;
	QDateTime dt = QDateTime::fromString(dateCreated, Qt::ISODate);
	dt.addSecs(-60);
	content["date_created_gmt"] = dt;
	content["mt_excerpt"] = excerpt;
	content["wp_slug"] = slug;
	content["wp_password"] = password;
	content["publish"] = status!="draft";
	content["page_status"] = status;
	content["mt_allow_comments"] = commentsOpen?1:0;
	content["mt_allow_pings"] = pingsOpen?1:0;
	if(pageParentId!=-1)
		content["wp_page_parent_id"] = pageParentId;
	if(pageOrder!=-1)
		content["wp_page_order"] = pageOrder;
	//qDebug()<<dt<<content;
	params.insert("content", content);
	CPAction::CPOperation op = CPAction::NewPage;
    CPAction *request = new CPAction(op, this);
    request->exec("POST", params);
    if(request) {
        requests[op] = request;
        taskStarted(op);
        connect(request,SIGNAL(error(int,int,QString)),
                this,SLOT(requestError(int,int,QString)));
        connect(request,SIGNAL(finished(int,QVariant)),
                this,SLOT(requestFinished(int,QVariant)));
    }
}

void CPUtil::editPage(QString id,
                      QString dateCreated,
                       QString title,
                       QString description,
                       QString excerpt,
                       QString slug,
                       QString status,
                       QString password,
                       bool commentsOpen,
                       bool pingsOpen,
                       int pageParentId,
                       int pageOrder)
{
    /*qDebug()<<dateCreated
            <<title
            <<excerpt
            <<slug
            <<status
            <<password;*/
    QMultiMap<QString, QVariant> params;
    QVariantMap content;
    content["post_type"] = "page";
    content["title"] = title;
    content["description"] = description;
    QDateTime dt = QDateTime::fromString(dateCreated, Qt::ISODate);
    content["date_created_gmt"] = dt;
    content["mt_excerpt"] = excerpt;
    content["wp_slug"] = slug;
    content["wp_password"] = password;
    content["publish"] = status!="draft";
    content["page_status"] = status;
    content["mt_allow_comments"] = commentsOpen?1:0;
    content["mt_allow_pings"] = pingsOpen?1:0;
    if(pageParentId!=-1)
        content["wp_page_parent_id"] = pageParentId;
    if(pageOrder!=-1)
        content["wp_page_order"] = pageOrder;
    qDebug()<<dt<<content;
    params.insert("page_id", id);
    params.insert("content", content);
    QStringList order;
    order<<"blog_id"<<"page_id"<<"username"<<"password"<<"content";
    CPAction::CPOperation op = CPAction::EditPage;
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

void CPUtil::deletePage(const QString pageId)
{
    qDebug()<<"CPUtil---Delete page---"<<pageId;
    for(int i=0;i<_pagesModel->size();i++) {
        QVariantMap item = _pagesModel->value(i).toMap();
        if(item[pageRoleNames[PageEntry::IdRole]].toString()==pageId) {
            if(item[pageRoleNames[PageEntry::StatusRole]].toString()=="localdraft") {
                deleteLocalPage(pageId);
                return;
            } else
                break;
        }
    }
	QMultiMap<QString, QVariant> params;
	params.insert("page_id", pageId.toInt());
	CPAction::CPOperation op = CPAction::DeletePage;
    CPAction *request = new CPAction(op, this);
    request->exec("POST", params);
    if(request) {
    	request->setProperty("pageId", pageId);
        requests[op] = request;
        taskStarted(op);
        connect(request,SIGNAL(error(int,int,QString)),
                this,SLOT(requestError(int,int,QString)));
        connect(request,SIGNAL(finished(int,QVariant)),
                this,SLOT(requestFinished(int,QVariant)));
    }
}

void CPUtil::approveComment(const QString commentId)
{

	QMultiMap<QString, QVariant> params;
	QVariantMap comment;
	comment["status"] = "approve";
	params.insert("comment_id", commentId.toInt());
	params.insert("comment", comment);
	CPAction::CPOperation op = CPAction::ApproveComment;
    CPAction *request = new CPAction(op, this);
	QStringList order;
	order<<"blog_id"<<"username"<<"password"<<"comment_id"<<"comment";
    request->exec("POST", params, order);
    if(request) {
    	request->setProperty("commentId", commentId);
        requests[op] = request;
        taskStarted(op);
        connect(request,SIGNAL(error(int,int,QString)),
                this,SLOT(requestError(int,int,QString)));
        connect(request,SIGNAL(finished(int,QVariant)),
                this,SLOT(requestFinished(int,QVariant)));
    }
}

void CPUtil::unapproveComment(const QString commentId)
{

	QMultiMap<QString, QVariant> params;
	QVariantMap comment;
	comment["status"] = "hold";
	params.insert("comment_id", commentId.toInt());
	params.insert("comment", comment);
	CPAction::CPOperation op = CPAction::UnapproveComment;
    CPAction *request = new CPAction(op, this);
	QStringList order;
	order<<"blog_id"<<"username"<<"password"<<"comment_id"<<"comment";
    request->exec("POST", params, order);
    if(request) {
    	request->setProperty("commentId", commentId);
        requests[op] = request;
        taskStarted(op);
        connect(request,SIGNAL(error(int,int,QString)),
                this,SLOT(requestError(int,int,QString)));
        connect(request,SIGNAL(finished(int,QVariant)),
                this,SLOT(requestFinished(int,QVariant)));
    }
}

void CPUtil::spamComment(const QString commentId)
{

	QMultiMap<QString, QVariant> params;
	QVariantMap comment;
	comment["status"] = "spam";
	params.insert("comment_id", commentId.toInt());
	params.insert("comment", comment);
	CPAction::CPOperation op = CPAction::SpamComment;
    CPAction *request = new CPAction(op, this);
	QStringList order;
	order<<"blog_id"<<"username"<<"password"<<"comment_id"<<"comment";
    request->exec("POST", params, order);
    if(request) {
    	request->setProperty("commentId", commentId);
        requests[op] = request;
        taskStarted(op);
        connect(request,SIGNAL(error(int,int,QString)),
                this,SLOT(requestError(int,int,QString)));
        connect(request,SIGNAL(finished(int,QVariant)),
                this,SLOT(requestFinished(int,QVariant)));
    }
}

void CPUtil::deleteComment(const QString commentId)
{

	QMultiMap<QString, QVariant> params;
	params.insert("comment_id", commentId.toInt());
	CPAction::CPOperation op = CPAction::DeleteComment;
    CPAction *request = new CPAction(op, this);
    request->exec("POST", params);
    if(request) {
    	request->setProperty("commentId", commentId);
        requests[op] = request;
        taskStarted(op);
        connect(request,SIGNAL(error(int,int,QString)),
                this,SLOT(requestError(int,int,QString)));
        connect(request,SIGNAL(finished(int,QVariant)),
                this,SLOT(requestFinished(int,QVariant)));
    }
}

void CPUtil::createNewCategory(const QString name,
		const QString slug,
		const int parentId,
        const QString description)
{

	QMultiMap<QString, QVariant> params;
	QVariantMap content;
	content["name"] = name;
	if(!slug.isEmpty())
		content["slug"] = slug;
	if(parentId!=0)
		content["parent_id"] = parentId;
	if(!description.isEmpty())
		content["description"] = description;
	params.insert("content", content);
	QStringList order;
	order<<"blog_id"<<"username"<<"password"<<"content";
	CPAction::CPOperation op = CPAction::NewCategory;
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

void CPUtil::deleteCategory(const QString categoryId)
{

	QMultiMap<QString, QVariant> params;
	params.insert("category_id", categoryId.toInt());
	CPAction::CPOperation op = CPAction::DeleteCategory;
	QStringList order;
	order<<"blog_id"<<"username"<<"password"<<"category_id";
    CPAction *request = new CPAction(op, this);
    request->exec("POST", params, order);
    if(request) {
    	request->setProperty("categoryId", categoryId);
        taskStarted(op);
        connect(request,SIGNAL(error(int,int,QString)),
                this,SLOT(requestError(int,int,QString)));
        connect(request,SIGNAL(finished(int,QVariant)),
                this,SLOT(requestFinished(int,QVariant)));
    }
}

void CPUtil::uploadFile(const QString filename, QString name, const bool overwrite)
{
	QMultiMap<QString, QVariant> params;
	QFile file(localFilePath(filename));
	QVariantMap data;
	if(file.open(QIODevice::ReadOnly)) {
		QByteArray ba = file.readAll();
		data["bits"] = ba;
		QFileInfo info(localFilePath(filename));
		QString suffix = info.suffix().toLower();
		if(name.trimmed().isEmpty()) {
			name = info.fileName();
			data["name"] = name;
		} else {
			if(name.endsWith(suffix, Qt::CaseInsensitive))
				data["name"] = name;
			else
				data["name"] = name+"."+suffix;
			data["title"] = name;
		}
		if(suffix=="jpg"||suffix=="jpeg")
			data["type"] = "image/jpeg";
		else if(suffix=="png"||suffix=="bmp")
			data["type"] = "image/"+suffix;
		file.close();
	}
	data["overwrite"] = overwrite;
	params.insert("data", data);
	QStringList order;
	order<<"blog_id"<<"username"<<"password"<<"data";
	CPAction::CPOperation op = CPAction::UploadFile;
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

void CPUtil::uploadEditorImage(const QString filename, QString name, const bool overwrite)
{
    QMultiMap<QString, QVariant> params;
    QFile file(localFilePath(filename));
    QVariantMap data;
    if(file.open(QIODevice::ReadOnly)) {
        QByteArray ba = file.readAll();
        data["bits"] = ba;
        QFileInfo info(localFilePath(filename));
        QString suffix = info.suffix().toLower();
        if(name.trimmed().isEmpty()) {
            name = info.fileName();
            data["name"] = name;
        } else {
            if(name.endsWith(suffix, Qt::CaseInsensitive))
                data["name"] = name;
            else
                data["name"] = name+"."+suffix;
        }
        if(suffix=="jpg"||suffix=="jpeg")
            data["type"] = "image/jpeg";
        else if(suffix=="png"||suffix=="bmp")
            data["type"] = "image/"+suffix;
        file.close();
    } else {
        taskFailed(CPAction::UploadEditorImage, 404, tr("File 'filename' for upload not readble").arg(filename));
    }
    data["overwrite"] = overwrite;
    params.insert("data", data);
    QStringList order;
    order<<"blog_id"<<"username"<<"password"<<"data";
    CPAction::CPOperation op = CPAction::UploadEditorImage;
    CPAction *request = new CPAction(op, this);
    request->exec("POST", params, order);
    if(request) {
        setEditorUploadImageUrl(filename);
        requests[op] = request;
        taskStarted(op);
        connect(request,SIGNAL(error(int,int,QString)),
                this,SLOT(requestError(int,int,QString)));
        connect(request,SIGNAL(finished(int,QVariant)),
                this,SLOT(requestFinished(int,QVariant)));
    }
}

void CPUtil::requestFinished(const int operation, const QVariant &result)
{
    CPAction *reply = qobject_cast<CPAction *>(sender());
    if(operation==CPAction::GetUserBlogs) {
    	QVariantList blogs = result.toList().first().toList();
    	int idx = 0;
    	foreach(QVariant i, blogs) {
    		QVariantMap blog = i.toMap();
    		if(!_blogsModel->list.contains(blog["url"].toString())) {
                QVariantMap it;
                it[blogRoleNames[BlogEntry::NameRole]] = blog["blogName"].toString();
                it[blogRoleNames[BlogEntry::IsAdminRole]] = blog["isAdmin"].toBool();
                it[blogRoleNames[BlogEntry::IdRole]] = blog["blogid"].toString();
                it[blogRoleNames[BlogEntry::UrlRole]] = blog["url"].toString();
                QUrl rpcUrl = QUrl(blog["xmlrpc"].toString());
                it[blogRoleNames[BlogEntry::XmlRpcUrlRole]] = blog["xmlrpc"].toString();
                it[blogRoleNames[BlogEntry::HtUsernameRole]] = "";
                it[blogRoleNames[BlogEntry::HtPasswordRole]] = "";
                it[blogRoleNames[BlogEntry::UsernameRole]] = reply->property("username").toString();
                it[blogRoleNames[BlogEntry::PasswordRole]] = reply->property("password").toString();
                it[blogRoleNames[BlogEntry::NumberOfPostsRole]] = 0;
                it[blogRoleNames[BlogEntry::IsWordpressRole]] = rpcUrl.host().endsWith(".wordpress.com");
                it[blogRoleNames[BlogEntry::PagesCountRole]] = 0;
                it[blogRoleNames[BlogEntry::PostsCountRole]] = 0;
                it[blogRoleNames[BlogEntry::CommentsCountRole]] = 0;
                it[blogRoleNames[BlogEntry::MarkedRole]] = true;
                if(idx==0)
                    it[blogRoleNames[BlogEntry::IsActiveRole]] = true;
                else
                    it[blogRoleNames[BlogEntry::IsActiveRole]] = false;
                it[blogRoleNames[BlogEntry::SanitizedUrlRole]] = sanitizedBlogUrl(blog["url"].toString());
                _selectBlogsModel->addEntry(it);
                idx++;
    		}
    	}
    	emit selectBlogsChanged();
    } else if(operation==CPAction::GetPages) {
    	customClearPagesModel();
		QVariantList pages = result.toList().first().toList();
		appendPages(_pagesModel, pages);
		updateBlogPagesDB();
		emit pagesChanged();
    } else if(operation==CPAction::GetPage) {
        QVariantMap page = result.toList().first().toMap();
        int idx=updatePage(_pagesModel, page);
        if(idx==-1)
            insertInBlogPagesDB(_pagesModel->value(0).toMap());
        else
            updateInBlogPagesDB(reply->property("pageId").toString(),_pagesModel->value(idx).toMap());
        emit pagesChanged();
    } else if(operation==CPAction::GetPosts) {
        customClearPostsModel();
        QVariantList posts = result.toList().first().toList();
        appendPosts(_postsModel, posts);
        updateBlogPostsDB();
        emit postsChanged();
    } else if(operation==CPAction::GetPost) {
        QVariantMap post = result.toList().first().toMap();
        int idx=updatePost(_postsModel, post);
        if(idx==-1)
            insertInBlogPostsDB(_postsModel->value(0).toMap());
        else
            updateInBlogPostsDB(reply->property("postId").toString(),_postsModel->value(idx).toMap());
        emit postsChanged();
    } else if(operation==CPAction::GetComments) {
    	_commentsModel->clearModel();
		QVariantList comments = result.toList().first().toList();
		appendComments(_commentsModel, comments);
        updateBlogCommentsDB();
		emit commentsChanged();
    } else if(operation==CPAction::GetComment) {
        QVariantMap comment = result.toList().first().toMap();
        int idx=updateComment(_commentsModel, comment);
        if(idx==-1)
            insertInBlogCommentsDB(_commentsModel->value(0).toMap());
        else
            updateInBlogPagesDB(reply->property("commentId").toString(),_commentsModel->value(idx).toMap());
        emit commentsChanged();
    } else if(operation==CPAction::GetMediaLibrary) {
    	_mediaItemsModel->clearModel();
		QVariantList mediaItems = result.toList().first().toList();
		appendMediaItems(_mediaItemsModel, mediaItems);
		updateBlogMediaDB();
		emit mediaItemsChanged();
    } else if(operation==CPAction::GetMediaItem) {
        QVariantMap mediaItem = result.toList().first().toMap();
        int idx=updateMediaItem(_mediaItemsModel, mediaItem);
        if(idx==-1)
            insertInBlogMediaDB(_mediaItemsModel->value(0).toMap());
        else
            updateInBlogMediaDB(reply->property("link").toString(),_mediaItemsModel->value(idx).toMap());
        emit mediaItemsChanged();
    } else if(operation==CPAction::GetCategories) {
		QVariantList categories = result.toList().first().toList();
		appendCategories(_categoriesModel, categories);
        updateBlogCategoriesDB();
		emit commentsChanged();
    } else if(operation==CPAction::GetTags) {
    	_tagsModel->clearModel();
		QVariantList tags = result.toList().first().toList();
		appendTags(_tagsModel, tags);
        updateBlogTagsDB();
		emit tagsChanged();
    } else if(operation==CPAction::NewPage) {
        if(!result.toList().first().toString().isEmpty()) {
            setLastCreatedPageId(result.toList().first().toString());
        }
    } else if(operation==CPAction::DeletePage) {
        if(result.toList().first().toBool()) {
            setLastDeletedPageId(reply->property("pageId").toString());
            deletePageInModel(_pagesModel, _lastDeletedPageId);
            deleteInBlogPagesDB(_lastDeletedPageId);
        }
    } else if(operation==CPAction::NewPost) {
        if(!result.toList().first().toString().isEmpty()) {
            setLastCreatedPostId(result.toList().first().toString());
        }
    } else if(operation==CPAction::DeletePost) {
        if(result.toList().first().toBool()) {
            setLastDeletedPostId(reply->property("postId").toString());
            deletePostInModel(_postsModel, _lastDeletedPostId);
            deleteInBlogPostsDB(_lastDeletedPostId);
        }
    } else if(operation==CPAction::ApproveComment) {
        if(result.toList().first().toBool())
            setLastApprovedCommentId(reply->property("commentId").toString());
    } else if(operation==CPAction::UnapproveComment) {
        if(result.toList().first().toBool())
            setLastUnapprovedCommentId(reply->property("commentId").toString());
    } else if(operation==CPAction::SpamComment) {
        if(result.toList().first().toBool()) {
            setLastSpammedCommentId(reply->property("commentId").toString());
            deleteInBlogCommentsDB(_lastSpammedCommentId);
        }
    } else if(operation==CPAction::DeleteComment) {
    	if(result.toList().first().toBool()) {
    		setLastDeletedCommentId(reply->property("commentId").toString());
            deleteInBlogCommentsDB(_lastDeletedCommentId);
        }
    } else if(operation==CPAction::NewCategory) {
        if(!result.toList().first().toString().isEmpty()) {
            setLastCreatedCategoryId(result.toList().first().toMap().value("categoryid").toString());
        }
    } else if(operation==CPAction::DeleteCategory) {
    	if(result.toList().first().toBool()) {
    		setLastDeletedCategoryId(reply->property("categoryId").toString());
            deleteCategoryInModel(_categoriesModel, _lastDeletedCategoryId);
            deleteInBlogCategoriesDB(_lastDeletedCategoryId);
    	}
    } else if(operation==CPAction::UploadFile) {
        if(!result.toList().first().toMap().value("id").toString().isEmpty()) {
            setLastCreatedMediaId(result.toList().first().toMap().value("id").toString());
        }
    } else if(operation==CPAction::UploadEditorImage) {
        setEditorUploadedImageUrl(result.toList().first().toMap().value("url").toString());
        if(!result.toList().first().toMap().value("id").toString().isEmpty()) {
            setLastCreatedMediaId(result.toList().first().toMap().value("id").toString());
        }
    } else if(operation==CPAction::GetPostCommentsCount) {
        for(int i=0;i<_postsModel->size();i++) {
            if(_postsModel->value(i).toMap().value(postRoleNames[PostEntry::IdRole]).toString()==reply->property("postId").toString()) {
                QVariantMap item = _postsModel->value(i).toMap();
                item[postRoleNames[PostEntry::CommentsCountRole]] = result.toList().first().toMap().value("approved").toInt();
                _postsModel->replace(i, item);
                break;
            }
        }
        emit postsChanged();
    }
    taskFinished(operation);
    reply->deleteLater();
    requests.remove(operation);
}

void CPUtil::requestError(const int operation,const int code,const QString msg)
{
    CPAction *reply = qobject_cast<CPAction *>(sender());
    qDebug()<<"CpUtil---Error"<<operation<<code<<msg;
    taskFailed(operation, code, msg);
    reply->deleteLater();
    requests.remove(operation);
}

void CPUtil::taskStarted(const int op)
{
	if(op==CPAction::GetUserBlogs) {
		setBlogAdditionState(ProgressState::Processing);
		setBlogAdditionStatus(tr("Getting user blogs..."));
	} else if(op==CPAction::GetPosts) {
		setPostsState(ProgressState::Processing);
		setPostsStatus(tr("Getting blog posts..."));
    } else if(op==CPAction::GetPost) {
        setPostsState(ProgressState::Processing);
        setPostsStatus(tr("Getting blog post..."));
	} else if(op==CPAction::NewPost) {
		setPostEditionState(ProgressState::Processing);
		setPostEditionStatus(tr("Creating blog post..."));
    } else if(op==CPAction::EditPost) {
        setPostEditionState(ProgressState::Processing);
        setPostEditionStatus(tr("Editing blog post..."));
	} else if(op==CPAction::GetPages) {
		setPagesState(ProgressState::Processing);
		setPagesStatus(tr("Getting blog pages..."));
	} else if(op==CPAction::GetPage) {
        setPagesState(ProgressState::Processing);
        setPagesStatus(tr("Getting blog page..."));
    } else if(op==CPAction::NewPage) {
		setPageEditionState(ProgressState::Processing);
		setPageEditionStatus(tr("Creating page..."));
	} else if(op==CPAction::EditPage) {
        setPageEditionState(ProgressState::Processing);
        setPageEditionStatus(tr("Editing page..."));
    } else if(op==CPAction::GetComments) {
		setCommentsState(ProgressState::Processing);
		setCommentsStatus(tr("Getting blog comments..."));
    } else if(op==CPAction::GetComment) {
        setCommentsState(ProgressState::Processing);
        setCommentsStatus(tr("Getting blog comment..."));
	} else if(op==CPAction::GetMediaLibrary) {
		setMediaItemsState(ProgressState::Processing);
		setMediaItemsStatus(tr("Getting blog media items..."));
	} else if(op==CPAction::GetMediaItem) {
        setMediaItemsState(ProgressState::Processing);
        setMediaItemsStatus(tr("Getting blog media item..."));
    } else if(op==CPAction::GetCategories) {
		setCategoriesState(ProgressState::Processing);
		setCategoriesStatus(tr("Getting blog categories..."));
	} else if(op==CPAction::NewCategory) {
		setCategoryEditionState(ProgressState::Processing);
		setCategoryEditionStatus(tr("Creating new category..."));
	} else if(op==CPAction::GetTags) {
		setTagsState(ProgressState::Processing);
		setTagsStatus(tr("Getting blog tags..."));
	} else if(op==CPAction::UploadFile) {
		setMediaUploadState(ProgressState::Processing);
		setMediaUploadStatus(tr("Uploading media file..."));
	} else if(op==CPAction::UploadEditorImage) {
        setEditorImageUploadState(ProgressState::Processing);
        setEditorImageUploadStatus(tr("Uploading image..."));
        if(_editorType.toLower()=="post") {
            setPostEditionState(ProgressState::Processing);
            setPostEditionStatus(tr("Uploading image..."));
        } else if(_editorType.toLower()=="page") {
            setPageEditionState(ProgressState::Processing);
            setPageEditionStatus(tr("Uploading image..."));
        }
    }
}

void CPUtil::taskFinished(const int op)
{
	if(op==CPAction::GetUserBlogs) {
		setBlogAdditionState(ProgressState::Success);
		setBlogAdditionStatus(tr("Retrieved user blogs!"));
	} else if(op==CPAction::GetPosts) {
		setPostsState(ProgressState::Success);
		setPostsStatus(tr("Retrieved blog posts!"));
    } else if(op==CPAction::GetPost) {
        setPostsState(ProgressState::Success);
        setPostsStatus(tr("Retrieved blog post!"));
	} else if(op==CPAction::NewPost) {
		setPostEditionState(ProgressState::Success);
		setPostEditionStatus(tr("New post created!"));
    } else if(op==CPAction::EditPost) {
        setPostEditionState(ProgressState::Success);
        setPostEditionStatus(tr("Post edited!"));
	} else if(op==CPAction::GetPages) {
		setPagesState(ProgressState::Success);
		setPagesStatus(tr("Retrieved blog pages!"));
	} else if(op==CPAction::GetPage) {
        setPagesState(ProgressState::Success);
        setPagesStatus(tr("Retrieved blog page!"));
    } else if(op==CPAction::NewPage) {
		setPageEditionState(ProgressState::Success);
		setPageEditionStatus(tr("New page created!"));
	} else if(op==CPAction::EditPage) {
        setPageEditionState(ProgressState::Success);
        setPageEditionStatus(tr("Page edited!"));
    } else if(op==CPAction::GetComments) {
		setCommentsState(ProgressState::Success);
		setCommentsStatus(tr("Retrieved blog comments!"));
    } else if(op==CPAction::GetComment) {
        setCommentsState(ProgressState::Success);
        setCommentsStatus(tr("Retrieved blog comment!"));
	} else if(op==CPAction::GetMediaLibrary) {
		setMediaItemsState(ProgressState::Success);
		setMediaItemsStatus(tr("Retrieved blog media items!"));
	} else if(op==CPAction::GetMediaItem) {
        setMediaItemsState(ProgressState::Success);
        setMediaItemsStatus(tr("Retrieved blog media item!"));
    } else if(op==CPAction::GetCategories) {
		setCategoriesState(ProgressState::Success);
		setCategoriesStatus(tr("Retrieved blog categories!"));
	} else if(op==CPAction::NewCategory) {
		setCategoryEditionState(ProgressState::Success);
		setCategoryEditionStatus(tr("Created new category!"));
	} else if(op==CPAction::GetTags) {
		setTagsState(ProgressState::Success);
		setTagsStatus(tr("Retrieved blog tags!"));
	} else if(op==CPAction::UploadFile) {
		setMediaUploadState(ProgressState::Success);
		setMediaUploadStatus(tr("Uploaded media file!"));
	} else if(op==CPAction::UploadEditorImage) {
        setEditorImageUploadState(ProgressState::Success);
        setEditorImageUploadStatus(tr("Uploaded image!"));
//        if(_editorType.toLower()=="post" && _postEditionState==ProgressState::Processing) {
//            setPostEditionState(ProgressState::None);
//            setPostEditionStatus(tr("Uploaded image!"));
//        } else if(_editorType.toLower()=="page" && _pageEditionState==ProgressState::Processing) {
//            setPageEditionState(ProgressState::None);
//            setPageEditionStatus(tr("Uploaded image!"));
//        }
    }
}

void CPUtil::taskFailed(const int op, const int errCode, const QString error)
{
	if(op==CPAction::GetUserBlogs) {
		setBlogAdditionState(ProgressState::Error);
		setBlogAdditionStatus(tr("Unable to retrieve user blogs!\n %1: %2").arg(errCode).arg(error));
	} else if(op==CPAction::GetPosts) {
		setPostsState(ProgressState::Error);
		setPostsStatus(tr("Unable to retrieve blog posts!\n %1: %2").arg(errCode).arg(error));
	} else if(op==CPAction::GetPost) {
	    setPostsState(ProgressState::Error);
	    setPostsStatus(tr("Unable to retrieve blog post!\n %1: %2").arg(errCode).arg(error));
	} else if(op==CPAction::NewPost) {
		setPostEditionState(ProgressState::Error);
		setPostEditionStatus(tr("Unable to create new post!\n %1: %2").arg(errCode).arg(error));
    } else if(op==CPAction::EditPost) {
        setPostEditionState(ProgressState::Error);
        setPostEditionStatus(tr("Unable to edit post!\n %1: %2").arg(errCode).arg(error));
	} else if(op==CPAction::GetPages) {
		setPagesState(ProgressState::Error);
		setPagesStatus(tr("Unable to retrieve blog pages!\n %1: %2").arg(errCode).arg(error));
	} else if(op==CPAction::GetPage) {
        setPagesState(ProgressState::Error);
        setPagesStatus(tr("Unable to retrieve blog page!\n %1: %2").arg(errCode).arg(error));
    } else if(op==CPAction::NewPage) {
		setPageEditionState(ProgressState::Error);
		setPageEditionStatus(tr("Unable to create new page!\n %1: %2").arg(errCode).arg(error));
	} else if(op==CPAction::EditPage) {
        setPageEditionState(ProgressState::Error);
        setPageEditionStatus(tr("Unable to edit page!\n %1: %2").arg(errCode).arg(error));
    } else if(op==CPAction::GetComments) {
		setCommentsState(ProgressState::Error);
		setCommentsStatus(tr("Unable to retrieve blog comments!\n %1: %2").arg(errCode).arg(error));
    } else if(op==CPAction::GetComment) {
        setCommentsState(ProgressState::Error);
        setCommentsStatus(tr("Unable to retrieve blog comment!\n %1: %2").arg(errCode).arg(error));
	} else if(op==CPAction::GetMediaLibrary) {
		setMediaItemsState(ProgressState::Error);
		setMediaItemsStatus(tr("Unable to retrieve blog media items!\n %1: %2").arg(errCode).arg(error));
	} else if(op==CPAction::GetMediaItem) {
        setMediaItemsState(ProgressState::Error);
        setMediaItemsStatus(tr("Unable to retrieve blog media item!\n %1: %2").arg(errCode).arg(error));
    } else if(op==CPAction::GetCategories) {
		setCategoriesState(ProgressState::Error);
		setCategoriesStatus(tr("Unable to retrieve blog categories!\n %1: %2").arg(errCode).arg(error));
	} else if(op==CPAction::NewCategory) {
		setCategoryEditionState(ProgressState::Error);
		setCategoryEditionStatus(tr("Unable to retrieve blog categories!\n %1: %2").arg(errCode).arg(error));
	} else if(op==CPAction::GetTags) {
		setTagsState(ProgressState::Error);
		setTagsStatus(tr("Unable to retrieve blog tags!\n %1: %2").arg(errCode).arg(error));
	} else if(op==CPAction::UploadFile) {
		setMediaUploadState(ProgressState::Error);
		setMediaUploadStatus(tr("Unable to upload media file!\n %1: %2").arg(errCode).arg(error));
	} else if(op==CPAction::UploadEditorImage) {
        setEditorImageUploadState(ProgressState::Error);
        setEditorImageUploadStatus(tr("Unable to upload image!\n %1: %2").arg(errCode).arg(error));
        if(_editorType.toLower()=="post") {
            setPostEditionState(ProgressState::Error);
            setPostEditionStatus(tr("Unable to update post. Error uploading image!\n %1: %2").arg(errCode).arg(error));
        } else if(_editorType.toLower()=="page") {
            setPageEditionState(ProgressState::Error);
            setPageEditionStatus(tr("Unable to update page. Error uploading image!\n %1: %2").arg(errCode).arg(error));
        }
    }
}

void CPUtil::toggleBlogSelection(const int pos)
{
	QVariantMap item = _selectBlogsModel->value(pos).toMap();
	item[blogRoleNames[BlogEntry::MarkedRole]] = !item[blogRoleNames[BlogEntry::MarkedRole]].toBool();
	_selectBlogsModel->replace(pos, item);
	emit selectBlogsChanged();
}

void CPUtil::toggleActiveInSelectedBlogs(const int pos)
{
    QVariantMap item;
    for(int i=0;i<_selectBlogsModel->size();i++) {
        item = _selectBlogsModel->value(i).toMap();
        if(i!=pos) {
            if(item[blogRoleNames[BlogEntry::IsActiveRole]].toBool()) {
                item[blogRoleNames[BlogEntry::IsActiveRole]]=false;
                _selectBlogsModel->replace(i, item);
            }
        } else {
            item[blogRoleNames[BlogEntry::IsActiveRole]]=true;
            _selectBlogsModel->replace(i, item);
        }
    }
    emit selectBlogsChanged();
}

void CPUtil::clearFetchedUserBlogs()
{
    _selectBlogsModel->clear();
    emit selectBlogsChanged();
}

void CPUtil::addSelectedBlogs()
{
    qDebug()<<"CPUtil---Adding selected blogs!";
    for(int i=0;i<_blogsModel->size();i++) {
        QVariantMap item = _blogsModel->value(i).toMap();
        if(item[blogRoleNames[BlogEntry::IsActiveRole]].toBool()) {
            item[blogRoleNames[BlogEntry::IsActiveRole]]=false;
            _blogsModel->replace(i, item);
        }
    }
	for(int i=0;i<_selectBlogsModel->size();i++) {
		QVariantMap item = _selectBlogsModel->value(i).toMap();
		if(item[blogRoleNames[BlogEntry::MarkedRole]].toBool()) {
			item[blogRoleNames[BlogEntry::MarkedRole]] = false;
			_blogsModel->addEntry(item);
		}
	}
	emit blogsChanged();
	setBlogAdditionState(ProgressState::None);
    setBlogAdditionStatus("");
    _selectBlogsModel->clear();
}

void CPUtil::activateBlog(int idx)
{
	if(_blogsModel->size()==0) return;
	if(idx==-1) {
		for(int i=0;i<_blogsModel->size();i++) {
	    	QVariantMap item = _blogsModel->value(i).toMap();
			if(item[blogRoleNames[BlogEntry::IsActiveRole]].toBool()) {
				idx = i;
				break;
			}
		}
	}
	if(idx>=_blogsModel->size()) return;
	clearBlogData();
	QVariantMap item = _blogsModel->value(idx).toMap();
	if(CPEngine::instance().blogUrl() != item[blogRoleNames[BlogEntry::UrlRole]].toString() ||
		CPEngine::instance().blogUsername() != item[blogRoleNames[BlogEntry::UsernameRole]].toString() ||
		CPEngine::instance().blogPassword() != item[blogRoleNames[BlogEntry::PasswordRole]].toString()) {
			CPEngine::instance().setBlogUrl(item[blogRoleNames[BlogEntry::UrlRole]].toString());
			CPEngine::instance().setBlogUsername(item[blogRoleNames[BlogEntry::UsernameRole]].toString());
			CPEngine::instance().setBlogPassword(item[blogRoleNames[BlogEntry::PasswordRole]].toString());
			CPEngine::instance().setBlogRPCUrl(item[blogRoleNames[BlogEntry::XmlRpcUrlRole]].toString());
            CPEngine::instance().setBlogSanitizedUrl(item[blogRoleNames[BlogEntry::SanitizedUrlRole]].toString());
	}
	CPEngine::instance().setBlogId(item[blogRoleNames[BlogEntry::IdRole]].toString());
	if(requests.keys().size()>0)
	    abortAllRunningRequests();
	if(!db.tables(QSql::AllTables).contains(item[blogRoleNames[BlogEntry::SanitizedUrlRole]].toString()+"pages")) {
	        createBlogPagesTable();
	    } else
	        readBlogPagesFromDB();
    if(!db.tables(QSql::AllTables).contains(item[blogRoleNames[BlogEntry::SanitizedUrlRole]].toString()+"posts")) {
        createBlogPostsTable();
    } else
        readBlogPostsFromDB();
    if(!db.tables(QSql::AllTables).contains(item[blogRoleNames[BlogEntry::SanitizedUrlRole]].toString()+"comments")) {
        createBlogCommentsTable();
    } else
        readBlogCommentsFromDB();
    if(!db.tables(QSql::AllTables).contains(item[blogRoleNames[BlogEntry::SanitizedUrlRole]].toString()+"media")) {
        createBlogMediaTable();
    } else
        readBlogMediaFromDB();
    if(!db.tables(QSql::AllTables).contains(item[blogRoleNames[BlogEntry::SanitizedUrlRole]].toString()+"categories")) {
        createBlogCategoriesTable();
    } else
        readBlogCategoriesFromDB();
    if(!db.tables(QSql::AllTables).contains(item[blogRoleNames[BlogEntry::SanitizedUrlRole]].toString()+"tags")) {
        createBlogTagsTable();
    } else
        readBlogTagsFromDB();
//    if(CPEngine::instance().networkAccessManager()->networkAccessible()==QNetworkAccessManager::Accessible) {
        fetchRecentPosts();
        fetchPages();
        fetchComments();
        fetchMediaItems();
        fetchTags();
        fetchCategories();
//    }
    updateBlogsDB();
}

void CPUtil::changeActiveBlog(const int pos)
{
	if(pos>=_blogsModel->size()) return;
	activateBlog(pos);
	for(int i=0;i<_blogsModel->size();i++) {
		QVariantMap item = _blogsModel->value(i).toMap();
		if(i==pos)
			item[blogRoleNames[BlogEntry::IsActiveRole]] = true;
		else
			item[blogRoleNames[BlogEntry::IsActiveRole]] = false;
		_blogsModel->replace(i, item);
	}
    updateBlogsDB();
}

void CPUtil::changeActiveBlog(const QString blogUrl)
{
	for(int i=0;i<_blogsModel->size();i++) {
		QVariantMap item = _blogsModel->value(i).toMap();
		if(item[blogRoleNames[BlogEntry::UrlRole]].toString()==blogUrl) {
			changeActiveBlog(i);
			return;
		}
	}
}

void CPUtil::updateBlogsDB()
{
    QSqlQuery query;
    QString queryString;
    qDebug()<<"CPUtil---Delete-All"<<query.exec("DELETE FROM blogs;")<<query.executedQuery()<<query.lastError();
    query.clear();
    for(int i=0;i<_blogsModel->rowCount();i++) {
    	QVariantMap item = _blogsModel->value(i).toMap();
    	if(i==0) {
    		queryString = "INSERT INTO blogs VALUES ";
    	}
    	queryString += "('"+item[blogRoleNames[BlogEntry::UrlRole]].toString()+
                "', '"+
                item[blogRoleNames[BlogEntry::NameRole]].toString()+
                "', '"+
                item[blogRoleNames[BlogEntry::XmlRpcUrlRole]].toString()+
                "', '"+
                item[blogRoleNames[BlogEntry::IdRole]].toString()+
                "', '"+
                item[blogRoleNames[BlogEntry::HtUsernameRole]].toString()+
                "', '"+
                item[blogRoleNames[BlogEntry::HtPasswordRole]].toString()+
                "', '"+
                item[blogRoleNames[BlogEntry::UsernameRole]].toString()+
                "', '"+
                item[blogRoleNames[BlogEntry::PasswordRole]].toString()+
                "', "+
                integerValueForBoolean(item[blogRoleNames[BlogEntry::IsAdminRole]].toBool())+
                ", "+
                integerValueForBoolean(item[blogRoleNames[BlogEntry::IsWordpressRole]].toBool())+
                ", "+
                item[blogRoleNames[BlogEntry::PagesCountRole]].toString()+
                ", "+
                item[blogRoleNames[BlogEntry::PostsCountRole]].toString()+
                ", "+
                item[blogRoleNames[BlogEntry::NumberOfPostsRole]].toString()+
                ", "+
                item[blogRoleNames[BlogEntry::CommentsCountRole]].toString()+
                ", "+
                integerValueForBoolean(item[blogRoleNames[BlogEntry::IsActiveRole]].toBool())+
                ", '"+
                item[blogRoleNames[BlogEntry::SanitizedUrlRole]].toString()+
                "')";
    	if(i!=_blogsModel->rowCount()-1) {
    		queryString += ", ";
    	} else {
    		queryString += ";";
    	}
    }
    qDebug()<<"CPUtil---Insert-All"<<query.exec(queryString)<<query.lastError()<<query.executedQuery();
}

void CPUtil::readBlogsFromDB()
{
    QSqlQuery query;
    QString queryString;
    qDebug()<<"CPUtil---Read-All"<<query.exec("SELECT * FROM blogs;")<<query.executedQuery()<<query.lastError();
    while(query.next()) {
    	QVariantMap it;
	    it[blogRoleNames[BlogEntry::NameRole]] = query.value(1).toString();
	    it[blogRoleNames[BlogEntry::IsAdminRole]] = query.value(8).toBool();
	    it[blogRoleNames[BlogEntry::IdRole]] = query.value(3).toString();
	    it[blogRoleNames[BlogEntry::UrlRole]] = query.value(0).toString();
	    it[blogRoleNames[BlogEntry::XmlRpcUrlRole]] = query.value(2).toString();
		it[blogRoleNames[BlogEntry::HtUsernameRole]] = query.value(4).toString();
		it[blogRoleNames[BlogEntry::HtPasswordRole]] = query.value(5).toString();
	    it[blogRoleNames[BlogEntry::UsernameRole]] = query.value(6).toString();
	    it[blogRoleNames[BlogEntry::PasswordRole]] = query.value(7).toString();
	    it[blogRoleNames[BlogEntry::NumberOfPostsRole]] = query.value(12).toInt();
	    it[blogRoleNames[BlogEntry::IsWordpressRole]] = query.value(9).toBool();
	    it[blogRoleNames[BlogEntry::PagesCountRole]] = query.value(10).toInt();
	    it[blogRoleNames[BlogEntry::PostsCountRole]] = query.value(11).toInt();
	    it[blogRoleNames[BlogEntry::CommentsCountRole]] = query.value(13).toInt();
	    it[blogRoleNames[BlogEntry::IsActiveRole]] = query.value(14).toBool();
        it[blogRoleNames[BlogEntry::SanitizedUrlRole]] = query.value(15).toString();
	    _blogsModel->addEntry(it);
    }
}

QString CPUtil::integerValueForBoolean(const bool value)
{
	if(value)
		return "1";
	else
		return "0";
}

void CPUtil::removeAllBlogs()
{
    for(int i=0;i<_blogsModel->size();i++)
        deleteBlogTablesInDB(sanitizedBlogUrl(_blogsModel->value(i).toMap().value(blogRoleNames[BlogEntry::UrlRole]).toString()));
	clear();
    QSqlQuery query;
    qDebug()<<"CPUtil---removeAllBlogs"<<query.exec("DELETE FROM blogs")<<query.lastError();
}

void CPUtil::removeBlog(const int iIndex)
{
	QString blogUrl = _blogsModel->value(iIndex).toMap().value(blogRoleNames[BlogEntry::UrlRole]).toString();
	removeBlog(blogUrl);
}

void CPUtil::removeBlog(const QString blogUrl)
{
	bool isActiveBlog = false;
    for(int i=0;i<_blogsModel->rowCount();i++) {
    	QVariantMap item = _blogsModel->value(i).toMap();
    	if(item[blogRoleNames[BlogEntry::UrlRole]].toString()==blogUrl) {
    	    if(item[blogRoleNames[BlogEntry::IsActiveRole]].toBool())
    	        isActiveBlog = true;
    		_blogsModel->removeEntry(i);
    		break;
    	}
    }
    QSqlQuery query;
    qDebug()<<"CPUtil---removeBlog"<<blogUrl<<query.exec("DELETE FROM blogs WHERE blogUrl='"+blogUrl+"'")<<query.lastError();
    deleteBlogTablesInDB(sanitizedBlogUrl(blogUrl));
    if(isActiveBlog && _blogsModel->size()!=0)
    	changeActiveBlog(0);
}

void CPUtil::appendEditorUploadImage(const QString image)
{
    if(!_editorUploadImages.contains(image)) {
        _editorUploadImages.append(image);
        emit editorUploadImagesChanged();
    }
}

void CPUtil::removeEditorUploadImage(const QString image)
{
    _editorUploadImages.removeOne(image);
    emit editorUploadImagesChanged();
}

void CPUtil::clearEditorUploadImages()
{
    _editorUploadImages.clear();
    emit editorUploadImagesChanged();
}

void CPUtil::clearEditorData()
{
    setPostEditionState(ProgressState::None);
    setPostEditionStatus("");
    setPageEditionState(ProgressState::None);
    setPageEditionStatus("");
    setEditorImageUploadState(ProgressState::None);
    setEditorImageUploadStatus("");
    setEditorUploadImageUrl("");
    setEditorUploadedImageUrl("");
    _editorUploadImages.clear();
    emit editorUploadImagesChanged();
    setEditorType("");
}

QString CPUtil::sanitizedBlogUrl(const QString blogUrl)
{
    QString s = blogUrl;
    return s.remove(".").remove(":").remove("/");
}

void CPUtil::createBlogPagesTable() {
    QSqlQuery query;
    QString queryString = "CREATE TABLE "+CPEngine::instance().blogSanitizedUrl()+"pages (id VARCHAR(20) primary key, "
               "title TEXT, "
               "localid VARCHAR(20), "
               "content TEXT, "
               "excerpt TEXT, "
               "slug VARCHAR(100), "
               "link VARCHAR(255), "
               "permalink VARCHAR(255), "
               "parenttitle TEXT, "
               "parentid VARCHAR(20), "
               "parentorder INTEGER, "
               "authordisplayname VARCHAR(255), "
               "author VARCHAR(255), "
               "status VARCHAR(20), "
               "password VARCHAR(20), "
               "datecreated VARCHAR(64), "
               "commentsopen BOOLEAN, "
               "commentscount VARCHAR(20), "
               "pingsopen BOOLEAN, "
               "template VARCHAR(100), "
               "sortdate VARCHAR(64))";

    qDebug()<<"CPUtil---createBlogPagesTable"<<query.exec(queryString)<<query.lastError();
    qDebug()<<"CPUtil---Tables"<<db.tables(QSql::AllTables);
}

void CPUtil::updateBlogPagesDB() {

    QSqlQuery query;
    qDebug()<<"CPUtil---updateBlogPagesDB"<<query.exec("DELETE FROM "+CPEngine::instance().blogSanitizedUrl()+"pages;")<<query.executedQuery()<<query.lastError();
    query.clear();
    for(int i=0;i<_pagesModel->rowCount();i++) {
        insertInBlogPagesDB(_pagesModel->value(i).toMap());
    }
}

void CPUtil::deleteBlogTablesInDB(const QString sanitizedBlogUrl) {

    QSqlQuery query;
    qDebug()<<"CPUtil---Drop-Pages"<<query.exec("DROP TABLE "+sanitizedBlogUrl+"pages;")<<query.executedQuery()<<query.lastError();
    query.clear();
    qDebug()<<"CPUtil---Drop-Posts"<<query.exec("DROP TABLE "+sanitizedBlogUrl+"posts;")<<query.executedQuery()<<query.lastError();
    query.clear();
    qDebug()<<"CPUtil---Drop-Comments"<<query.exec("DROP TABLE "+sanitizedBlogUrl+"posts;")<<query.executedQuery()<<query.lastError();
    query.clear();
    qDebug()<<"CPUtil---Drop-Media"<<query.exec("DROP TABLE "+sanitizedBlogUrl+"media;")<<query.executedQuery()<<query.lastError();
    query.clear();
    qDebug()<<"CPUtil---Drop-Categories"<<query.exec("DROP TABLE "+sanitizedBlogUrl+"categories;")<<query.executedQuery()<<query.lastError();
    query.clear();
    qDebug()<<"CPUtil---Drop-Tags"<<query.exec("DROP TABLE "+sanitizedBlogUrl+"tags;")<<query.executedQuery()<<query.lastError();

}

void CPUtil::insertInBlogPagesDB(QVariantMap item) {

    QSqlQuery query;
    QString queryString;
    queryString = "INSERT INTO "+CPEngine::instance().blogSanitizedUrl()+"pages VALUES ";
    queryString += "('"+item[pageRoleNames[PageEntry::IdRole]].toString()+
            "', '"+
            item[pageRoleNames[PageEntry::TitleRole]].toString().replace("'","''")+
            "', '"+
            item[pageRoleNames[PageEntry::LocalIdRole]].toString()+
            "', '"+
            item[pageRoleNames[PageEntry::DescRole]].toString().replace("'","''")+
            "', '"+
            item[pageRoleNames[PageEntry::ExcerptRole]].toString().replace("'","''")+
            "', '"+
            item[pageRoleNames[PageEntry::SlugRole]].toString()+
            "', '"+
            item[pageRoleNames[PageEntry::LinkRole]].toString()+
            "', '"+
            item[pageRoleNames[PageEntry::PermaLinkRole]].toString()+
            "', '"+
            item[pageRoleNames[PageEntry::WpPageParentTitleRole]].toString().replace("'","''")+
            "', '"+
            item[pageRoleNames[PageEntry::WpPageParentIdRole]].toString()+
            "', "+
            item[pageRoleNames[PageEntry::WpPageParentOrderRole]].toString()+
            ", '"+
            item[pageRoleNames[PageEntry::WpAuthorDisplayNameRole]].toString()+
            "', '"+
            item[pageRoleNames[PageEntry::WpAuthorRole]].toString()+
            "', '"+
            item[pageRoleNames[PageEntry::StatusRole]].toString()+
            "', '"+
            item[pageRoleNames[PageEntry::PasswordRole]].toString().replace("'","''")+
            "', '"+
            item[pageRoleNames[PageEntry::DateCreatedRole]].toDateTime().toString(Qt::ISODate)+
            "', "+
            integerValueForBoolean(item[pageRoleNames[PageEntry::CommentsOpenRole]].toBool())+
            ", '"+
            item[pageRoleNames[PageEntry::CommentsCountRole]].toString()+
            "', "+
            integerValueForBoolean(item[pageRoleNames[PageEntry::PingsOpenRole]].toBool())+
            ", '"+
            item[pageRoleNames[PageEntry::TemplateRole]].toString()+
            "', '"+
            item[pageRoleNames[PageEntry::SortDateRole]].toString()+
            "');";
    qDebug()<<"CPUtil---insertInBlogPagesDB"<<query.exec(queryString)<<query.lastError();
}

void CPUtil::deleteInBlogPagesDB(QString pageId)
{
    QSqlQuery query;
    QString queryString = "DELETE FROM "+CPEngine::instance().blogSanitizedUrl()+
            "pages WHERE id='"+
            pageId+"';";
    qDebug()<<"CPUtil---deleteInBlogPagesDB"<<query.exec(queryString)<<query.lastError();
}

void CPUtil::updateInBlogPagesDB(QString pageId, QVariantMap item) {

    QSqlQuery query;
    QString queryString;
    queryString = "UPDATE "+CPEngine::instance().blogSanitizedUrl()+"pages SET ";
    queryString += "id='"+item[pageRoleNames[PageEntry::IdRole]].toString()+
            "', title='"+
            item[pageRoleNames[PageEntry::TitleRole]].toString().replace("'","''")+
            "', localid='"+
            item[pageRoleNames[PageEntry::LocalIdRole]].toString()+
            "', content='"+
            item[pageRoleNames[PageEntry::DescRole]].toString().replace("'","''")+
            "', excerpt='"+
            item[pageRoleNames[PageEntry::ExcerptRole]].toString().replace("'","''")+
            "', slug='"+
            item[pageRoleNames[PageEntry::SlugRole]].toString()+
            "', link='"+
            item[pageRoleNames[PageEntry::LinkRole]].toString()+
            "', permalink='"+
            item[pageRoleNames[PageEntry::PermaLinkRole]].toString()+
            "', parenttitle='"+
            item[pageRoleNames[PageEntry::WpPageParentTitleRole]].toString().replace("'","''")+
            "', parentid='"+
            item[pageRoleNames[PageEntry::WpPageParentIdRole]].toString()+
            "', parentorder="+
            item[pageRoleNames[PageEntry::WpPageParentOrderRole]].toString()+
            ", authordisplayname='"+
            item[pageRoleNames[PageEntry::WpAuthorDisplayNameRole]].toString()+
            "', author='"+
            item[pageRoleNames[PageEntry::WpAuthorRole]].toString()+
            "', status='"+
            item[pageRoleNames[PageEntry::StatusRole]].toString()+
            "', password='"+
            item[pageRoleNames[PageEntry::PasswordRole]].toString().replace("'","''")+
            "', datecreated='"+
            item[pageRoleNames[PageEntry::DateCreatedRole]].toDateTime().toString(Qt::ISODate)+
            "', commentsopen="+
            integerValueForBoolean(item[pageRoleNames[PageEntry::CommentsOpenRole]].toBool())+
            ", commentscount='"+
            item[pageRoleNames[PageEntry::CommentsCountRole]].toString()+
            "', pingsopen="+
            integerValueForBoolean(item[pageRoleNames[PageEntry::PingsOpenRole]].toBool())+
            ", template='"+
            item[pageRoleNames[PageEntry::TemplateRole]].toString()+
            "', sortdate='"+
            item[pageRoleNames[PageEntry::SortDateRole]].toString()+
            "' WHERE id='"+pageId+"';";
    qDebug()<<"CPUtil---updateInBlogPagesDB"<<query.exec(queryString)<<query.lastError();
}

void CPUtil::readBlogPagesFromDB() {
    QSqlQuery query;
    QString queryString;
    qDebug()<<"CPUtil---readBlogPagesFromDB"<<query.exec("SELECT * FROM "+CPEngine::instance().blogSanitizedUrl()+"pages;")<<query.executedQuery()<<query.lastError();
    while(query.next()) {
        QVariantMap it;
        it[pageRoleNames[PageEntry::IdRole]] = query.value(0).toString();
        it[pageRoleNames[PageEntry::TitleRole]] = query.value(1).toString();
        it[pageRoleNames[PageEntry::LocalIdRole]] = query.value(2).toString();
        it[pageRoleNames[PageEntry::DescRole]] = query.value(3).toString();
        it[pageRoleNames[PageEntry::ContentSnippetRole]] = getHtmlTextSnippet(query.value(3).toString());
        it[pageRoleNames[PageEntry::ExcerptRole]] = query.value(4).toString();
        it[pageRoleNames[PageEntry::SlugRole]] = query.value(5).toString();
        it[pageRoleNames[PageEntry::LinkRole]] = query.value(6).toString();
        it[pageRoleNames[PageEntry::PermaLinkRole]] = query.value(7).toString();
        it[pageRoleNames[PageEntry::WpPageParentTitleRole]] = query.value(8).toString();
        it[pageRoleNames[PageEntry::WpPageParentIdRole]] = query.value(9).toString();
        it[pageRoleNames[PageEntry::WpPageParentOrderRole]] = query.value(10).toString();
        it[pageRoleNames[PageEntry::WpAuthorDisplayNameRole]] = query.value(11).toString();
        it[pageRoleNames[PageEntry::WpAuthorRole]] = query.value(12).toString();
        it[pageRoleNames[PageEntry::StatusRole]] = query.value(13).toString();
        it[pageRoleNames[PageEntry::PasswordRole]] = query.value(14).toString();
        QDateTime d = QDateTime::fromString(query.value(15).toString(), Qt::ISODate);
        it[pageRoleNames[PageEntry::DateCreatedRole]] = d;
        it[pageRoleNames[PageEntry::DisplayDateRole]] = d.toString("ddd hh:mm AP MMM dd, yyyy");
        it[pageRoleNames[PageEntry::PageTimeRole]] = d.time();
        it[pageRoleNames[PageEntry::PageDateRole]] = d.date();
        it[pageRoleNames[PageEntry::CommentsOpenRole]] = query.value(16).toBool();
        it[pageRoleNames[PageEntry::PingsOpenRole]] = query.value(18).toInt();
        it[pageRoleNames[PageEntry::CommentsCountRole]] = query.value(17).toInt();
        it[pageRoleNames[PageEntry::MarkedRole]] = false;
        _pagesModel->addEntry(it);
    }
}

void CPUtil::createBlogPostsTable() {
    QSqlQuery query;
    QString queryString = "CREATE TABLE "+CPEngine::instance().blogSanitizedUrl()+"posts (id VARCHAR(20) primary key, "
               "title TEXT, "
               "localid VARCHAR(20), "
               "content TEXT, "
               "excerpt TEXT, "
               "slug VARCHAR(100), "
               "link VARCHAR(255), "
               "permalink VARCHAR(255), "
               "authordisplayname VARCHAR(255), "
               "author VARCHAR(255), "
               "categories TEXT, "
               "tags TEXT, "
               "status VARCHAR(20), "
               "sticky BOOLEAN, "
               "password VARCHAR(20), "
               "datecreated VARCHAR(64), "
               "modified VARCHAR(64), "
               "commentsopen BOOLEAN, "
               "commentscount VARCHAR(20), "
               "pingsopen BOOLEAN, "
               "sortdate VARCHAR(64))";

    qDebug()<<"CPUtil---createBlogPostsTable"<<query.exec(queryString)<<query.lastError();
    qDebug()<<"CPUtil---Tables"<<db.tables(QSql::AllTables);
}
void CPUtil::updateBlogPostsDB() {

    QSqlQuery query;
    qDebug()<<"CPUtil---updateBlogPostsDB"<<query.exec("DELETE FROM "+CPEngine::instance().blogSanitizedUrl()+"posts WHERE id NOT LIKE 'local%';")<<query.executedQuery()<<query.lastError();
    query.clear();
    for(int i=0;i<_postsModel->rowCount();i++) {
        insertInBlogPostsDB(_postsModel->value(i).toMap());
    }
}

void CPUtil::insertInBlogPostsDB(QVariantMap item) {

    QSqlQuery query;
    QString queryString;
    queryString = "INSERT INTO "+CPEngine::instance().blogSanitizedUrl()+"posts VALUES ";
    queryString += "('"+item[postRoleNames[PostEntry::IdRole]].toString()+
            "', '"+
            item[postRoleNames[PostEntry::TitleRole]].toString().replace("'","''")+
            "', '"+
            item[postRoleNames[PostEntry::LocalIdRole]].toString()+
            "', '"+
            item[postRoleNames[PostEntry::DescRole]].toString().replace("'","''")+
            "', '"+
            item[postRoleNames[PostEntry::ExcerptRole]].toString().replace("'","''")+
            "', '"+
            item[postRoleNames[PostEntry::SlugRole]].toString()+
            "', '"+
            item[postRoleNames[PostEntry::LinkRole]].toString()+
            "', '"+
            item[postRoleNames[PostEntry::PermaLinkRole]].toString()+
            "', '"+
            item[postRoleNames[PostEntry::WpAuthorDisplayNameRole]].toString()+
            "', '"+
            item[postRoleNames[PostEntry::WpAuthorRole]].toString()+
            "', '"+
            item[postRoleNames[PostEntry::CategoriesRole]].toStringList().join(";")+
            "', '"+
            item[postRoleNames[PostEntry::TagsRole]].toStringList().join(";")+
            "', '"+
            item[postRoleNames[PostEntry::StatusRole]].toString()+
            "', "+
            integerValueForBoolean(item[postRoleNames[PostEntry::StickyRole]].toBool())+
            ", '"+
            item[postRoleNames[PostEntry::PasswordRole]].toString().replace("'","''")+
            "', '"+
            item[postRoleNames[PostEntry::DateCreatedRole]].toDateTime().toString(Qt::ISODate)+
            "', '"+
            item[postRoleNames[PostEntry::ModifiedRole]].toDateTime().toString(Qt::ISODate)+
            "', "+
            integerValueForBoolean(item[postRoleNames[PostEntry::CommentsOpenRole]].toBool())+
            ", '"+
            item[postRoleNames[PostEntry::CommentsCountRole]].toString()+
            "', "+
            integerValueForBoolean(item[postRoleNames[PostEntry::PingsOpenRole]].toBool())+
            ", '"+
            item[postRoleNames[PostEntry::SortDateRole]].toString()+
            "');";
    qDebug()<<"CPUtil---insertInBlogPostsDB"<<query.exec(queryString)<<query.lastError();
}

void CPUtil::deleteInBlogPostsDB(QString postId)
{
    QSqlQuery query;
    QString queryString = "DELETE FROM "+CPEngine::instance().blogSanitizedUrl()+
            "posts WHERE id='"+
            postId+"';";
    qDebug()<<"CPUtil---deleteInBlogPostsDB"<<query.exec(queryString)<<query.lastError();
}

void CPUtil::updateInBlogPostsDB(QString postId, QVariantMap item) {

    QSqlQuery query;
    QString queryString;
    queryString = "UPDATE "+CPEngine::instance().blogSanitizedUrl()+"posts SET ";
    queryString += "id='"+item[postRoleNames[PostEntry::IdRole]].toString()+
            "', title='"+
            item[postRoleNames[PostEntry::TitleRole]].toString().replace("'","''")+
            "', localid='"+
            item[postRoleNames[PostEntry::LocalIdRole]].toString()+
            "', content='"+
            item[postRoleNames[PostEntry::DescRole]].toString().replace("'","''")+
            "', excerpt='"+
            item[postRoleNames[PostEntry::ExcerptRole]].toString().replace("'","''")+
            "', slug='"+
            item[postRoleNames[PostEntry::SlugRole]].toString()+
            "', link='"+
            item[postRoleNames[PostEntry::LinkRole]].toString()+
            "', permalink='"+
            item[postRoleNames[PostEntry::PermaLinkRole]].toString()+
            "', authordisplayname='"+
            item[postRoleNames[PostEntry::WpAuthorDisplayNameRole]].toString()+
            "', author='"+
            item[postRoleNames[PostEntry::WpAuthorRole]].toString()+
            "', categories='"+
            item[postRoleNames[PostEntry::CategoriesRole]].toStringList().join(";")+
            "', tags='"+
            item[postRoleNames[PostEntry::TagsRole]].toStringList().join(";")+
            "', status='"+
            item[postRoleNames[PostEntry::StatusRole]].toString()+
            "', sticky="+
            integerValueForBoolean(item[postRoleNames[PostEntry::StickyRole]].toBool())+
            ", password='"+
            item[postRoleNames[PostEntry::PasswordRole]].toString().replace("'","''")+
            "', datecreated='"+
            item[postRoleNames[PostEntry::DateCreatedRole]].toDateTime().toString(Qt::ISODate)+
            "', modified='"+
            item[postRoleNames[PostEntry::ModifiedRole]].toDateTime().toString(Qt::ISODate)+
            "', commentsopen="+
            integerValueForBoolean(item[postRoleNames[PostEntry::CommentsOpenRole]].toBool())+
            ", commentscount='"+
            item[postRoleNames[PostEntry::CommentsCountRole]].toString()+
            "', pingsopen="+
            integerValueForBoolean(item[postRoleNames[PostEntry::PingsOpenRole]].toBool())+
            ", sortdate='"+
            item[postRoleNames[PostEntry::SortDateRole]].toString()+
            "' WHERE id='"+postId+"';";
    qDebug()<<"CPUtil---updateInBlogPostsDB"<<postId<<query.exec(queryString)<<query.lastError();
}

void CPUtil::readBlogPostsFromDB() {
    QSqlQuery query;
    QString queryString;
    qDebug()<<"CPUtil---readBlogPostsFromDB"<<query.exec("SELECT * FROM "+CPEngine::instance().blogSanitizedUrl()+"posts;")<<query.executedQuery()<<query.lastError();
    while(query.next()) {
        QVariantMap it;
        it[postRoleNames[PostEntry::IdRole]] = query.value(0).toString();
        it[postRoleNames[PostEntry::TitleRole]] = query.value(1).toString();
        it[postRoleNames[PostEntry::LocalIdRole]] = query.value(2).toString();
        it[postRoleNames[PostEntry::DescRole]] = query.value(3).toString();
        it[postRoleNames[PostEntry::ContentSnippetRole]] = getHtmlTextSnippet(query.value(3).toString());
        it[postRoleNames[PostEntry::ExcerptRole]] = query.value(4).toString();
        it[postRoleNames[PostEntry::SlugRole]] = query.value(5).toString();
        it[postRoleNames[PostEntry::LinkRole]] = query.value(6).toString();
        it[postRoleNames[PostEntry::PermaLinkRole]] = query.value(7).toString();
        it[postRoleNames[PostEntry::WpAuthorDisplayNameRole]] = query.value(8).toString();
        it[postRoleNames[PostEntry::WpAuthorRole]] = query.value(9).toString();
        it[postRoleNames[PostEntry::CategoriesRole]] = query.value(10).toString().split(";");
        it[postRoleNames[PostEntry::TagsRole]] = query.value(11).toString().split(";");
        it[postRoleNames[PostEntry::StatusRole]] = query.value(12).toString();
        it[postRoleNames[PostEntry::DisplayStatusRole]] = query.value(12).toString();
        it[postRoleNames[PostEntry::StickyRole]] = query.value(13).toString();
        it[postRoleNames[PostEntry::PasswordRole]] = query.value(14).toString();
        QDateTime d = QDateTime::fromString(query.value(15).toString(), Qt::ISODate);
        if(d>QDateTime::currentDateTime())
            it[postRoleNames[PostEntry::DisplayStatusRole]] = "future";
        it[postRoleNames[PostEntry::DateCreatedRole]] = d;
        it[postRoleNames[PostEntry::DisplayDateRole]] = d.toString("ddd hh:mm AP MMM dd, yyyy");
        it[postRoleNames[PostEntry::PostTimeRole]] = d.time();
        it[postRoleNames[PostEntry::PostDateRole]] = d.date();
        d = QDateTime::fromString(query.value(16).toString(), Qt::ISODate);
        it[postRoleNames[PostEntry::ModifiedRole]] = d;
        it[postRoleNames[PostEntry::DisplayModifiedRole]] = d.toString("ddd hh:mm AP MMM dd, yyyy");
        it[postRoleNames[PostEntry::CommentsOpenRole]] = query.value(17).toBool();
        it[postRoleNames[PostEntry::CommentsCountRole]] = query.value(18).toInt();
        it[postRoleNames[PostEntry::PingsOpenRole]] = query.value(19).toInt();
        it[postRoleNames[PostEntry::MarkedRole]] = false;
        _postsModel->addEntry(it);
    }
}

void CPUtil::createBlogCommentsTable() {
    QSqlQuery query;
    QString queryString = "CREATE TABLE "+CPEngine::instance().blogSanitizedUrl()+"comments (id VARCHAR(25) primary key, "
               "localid VARCHAR(25), "
               "link VARCHAR(255), "
               "userid VARCHAR(25), "
               "content TEXT, "
               "contentpreview TEXT, "
               "postid VARCHAR(25), "
               "posttitle TEXT, "
               "author VARCHAR(255), "
               "authorurl VARCHAR(255), "
               "authoremail VARCHAR(255), "
               "authorip VARCHAR(64), "
               "status VARCHAR(100), "
               "gravatarurl VARCHAR(255), "
               "datecreated VARCHAR(64), "
               "parentid VARCHAR(25), "
               "grandparentid VARCHAR(25), "
               "corder INTEGER, "
               "sortdate VARCHAR(64))";

    qDebug()<<"CPUtil---createBlogCommentsTable"<<query.exec(queryString)<<query.lastError();
    qDebug()<<"CPUtil---Tables"<<db.tables(QSql::AllTables);
}
void CPUtil::updateBlogCommentsDB() {

    QSqlQuery query;
    QString queryString;
    qDebug()<<"CPUtil---updateBlogCommentsDB"<<query.exec("DELETE FROM "+CPEngine::instance().blogSanitizedUrl()+"comments;")<<query.executedQuery()<<query.lastError();
    for(int i=0;i<_commentsModel->rowCount();i++)
        insertInBlogCommentsDB(_commentsModel->value(i).toMap());
}

void CPUtil::insertInBlogCommentsDB(QVariantMap item) {

    QSqlQuery query;
    QString queryString;
    queryString = "INSERT INTO "+CPEngine::instance().blogSanitizedUrl()+"comments VALUES ";
    queryString += "('"+item[commentRoleNames[CommentEntry::IdRole]].toString()+
        "', '"+
        item[commentRoleNames[CommentEntry::LocalIdRole]].toString()+
        "', '"+
        item[commentRoleNames[CommentEntry::LinkRole]].toString()+
        "', '"+
        item[commentRoleNames[CommentEntry::UserIdRole]].toString()+
        "', '"+
        item[commentRoleNames[CommentEntry::ContentRole]].toString().replace("'","''")+
        "', '"+
        item[commentRoleNames[CommentEntry::ContentPreviewRole]].toString().replace("'","''")+
        "', '"+
        item[commentRoleNames[CommentEntry::PostIdRole]].toString()+
        "', '"+
        item[commentRoleNames[CommentEntry::PostTitleRole]].toString().replace("'","''")+
        "', '"+
        item[commentRoleNames[CommentEntry::AuthorRole]].toString()+
        "', '"+
        item[commentRoleNames[CommentEntry::AuthorUrlRole]].toString()+
        "', '"+
        item[commentRoleNames[CommentEntry::AuthorEmailRole]].toString()+
        "', '"+
        item[commentRoleNames[CommentEntry::AuthorIpRole]].toString()+
        "', '"+
        item[commentRoleNames[CommentEntry::StatusRole]].toString()+
        "', '"+
        item[commentRoleNames[CommentEntry::GravatarUrlRole]].toString()+
        "', '"+
        item[commentRoleNames[CommentEntry::DateCreatedRole]].toString()+
        "', '"+
        item[commentRoleNames[CommentEntry::ParentIdRole]].toString()+
        "', '"+
        item[commentRoleNames[CommentEntry::GrandParentIdRole]].toString()+
        "', "+
        item[commentRoleNames[CommentEntry::OrderRole]].toString()+
        ", '"+
        item[commentRoleNames[CommentEntry::SortDateRole]].toString()+
        "');";
    qDebug()<<"CPUtil---insertInBlogCommentsDB"<<query.exec(queryString)<<query.lastError();
}

void CPUtil::deleteInBlogCommentsDB(QString commentId)
{
    QSqlQuery query;
    QString queryString = "DELETE FROM "+CPEngine::instance().blogSanitizedUrl()+
            "comments WHERE id='"+
            commentId+"';";
    qDebug()<<"CPUtil---deleteInBlogCommentsDB"<<query.exec(queryString)<<query.lastError();
}

void CPUtil::updateInBlogCommentsDB(QString commentId,QVariantMap item)
{
    QSqlQuery query;
    QString queryString;
    queryString = "UPDATE "+CPEngine::instance().blogSanitizedUrl()+"comments SET ";
    queryString += "id='"+item[commentRoleNames[CommentEntry::IdRole]].toString()+
        "', localid='"+
        item[commentRoleNames[CommentEntry::LocalIdRole]].toString()+
        "', link='"+
        item[commentRoleNames[CommentEntry::LinkRole]].toString()+
        "', userid='"+
        item[commentRoleNames[CommentEntry::UserIdRole]].toString()+
        "', content'"+
        item[commentRoleNames[CommentEntry::ContentRole]].toString().replace("'","''")+
        "', contentpreview='"+
        item[commentRoleNames[CommentEntry::ContentPreviewRole]].toString().replace("'","''")+
        "', postid='"+
        item[commentRoleNames[CommentEntry::PostIdRole]].toString()+
        "', posttitle'"+
        item[commentRoleNames[CommentEntry::PostTitleRole]].toString().replace("'","''")+
        "', author='"+
        item[commentRoleNames[CommentEntry::AuthorRole]].toString()+
        "', authorurl'"+
        item[commentRoleNames[CommentEntry::AuthorUrlRole]].toString()+
        "', authoremail='"+
        item[commentRoleNames[CommentEntry::AuthorEmailRole]].toString()+
        "', authorip='"+
        item[commentRoleNames[CommentEntry::AuthorIpRole]].toString()+
        "', status='"+
        item[commentRoleNames[CommentEntry::StatusRole]].toString()+
        "', gravatarurl='"+
        item[commentRoleNames[CommentEntry::GravatarUrlRole]].toString()+
        "', datecreated='"+
        item[commentRoleNames[CommentEntry::DateCreatedRole]].toString()+
        "', parentid='"+
        item[commentRoleNames[CommentEntry::ParentIdRole]].toString()+
        "', grandparentid='"+
        item[commentRoleNames[CommentEntry::GrandParentIdRole]].toString()+
        "', order="+
        item[commentRoleNames[CommentEntry::OrderRole]].toString()+
        ", sortdate'"+
        item[commentRoleNames[CommentEntry::SortDateRole]].toString()+
        "');";
    qDebug()<<"CPUtil---updateInBlogCommentsDB"<<query.exec(queryString)<<query.lastError();
}

void CPUtil::readBlogCommentsFromDB() {
    QSqlQuery query;
    QString queryString;
    qDebug()<<"CPUtil---readBlogCommentsFromDB"<<query.exec("SELECT * FROM "+CPEngine::instance().blogSanitizedUrl()+"comments;")<<query.executedQuery()<<query.lastError();
    while(query.next()) {
        QVariantMap it;
        it[commentRoleNames[CommentEntry::IdRole]] = query.value(0).toString();
        it[commentRoleNames[CommentEntry::LocalIdRole]] = query.value(1).toString();
        it[commentRoleNames[CommentEntry::LinkRole]] = query.value(2).toString();
        it[commentRoleNames[CommentEntry::UserIdRole]] = query.value(3).toString();
        it[commentRoleNames[CommentEntry::ContentRole]] = query.value(4).toString();
        it[commentRoleNames[CommentEntry::ContentPreviewRole]] = query.value(5).toString();
        it[commentRoleNames[CommentEntry::PostIdRole]] = query.value(6).toString();
        it[commentRoleNames[CommentEntry::PostTitleRole]] = query.value(7).toString();
        it[commentRoleNames[CommentEntry::AuthorRole]] = query.value(8).toString();
        it[commentRoleNames[CommentEntry::AuthorUrlRole]] = query.value(9).toString();
        it[commentRoleNames[CommentEntry::AuthorEmailRole]] = query.value(10).toString();
        it[commentRoleNames[CommentEntry::AuthorIpRole]] = query.value(11).toString();
        it[commentRoleNames[CommentEntry::StatusRole]] = query.value(12).toString();
        it[commentRoleNames[CommentEntry::GravatarUrlRole]] = query.value(13).toString();
        it[commentRoleNames[CommentEntry::DateCreatedRole]] = query.value(14).toString();
        it[commentRoleNames[CommentEntry::MarkedRole]] = false;
        it[commentRoleNames[CommentEntry::ParentIdRole]] = query.value(15).toInt();
        it[commentRoleNames[CommentEntry::GrandParentIdRole]] = query.value(16).toInt();
        it[commentRoleNames[CommentEntry::OrderRole]] = query.value(17).toInt();
        it[commentRoleNames[CommentEntry::SortDateRole]] = query.value(18).toInt();
        _commentsModel->addEntry(it);
    }
}

void CPUtil::createBlogMediaTable() {
    QSqlQuery query;
    qDebug()<<"CPUtil---createBlogMediaTable"<<query.exec("CREATE TABLE "+CPEngine::instance().blogSanitizedUrl()+"media (link VARCHAR(255) primary key, "
               "parent VARCHAR(25), "
               "description TEXT, "
               "thumbnail VARCHAR(255), "
               "caption TEXT, "
               "title TEXT, "
               "metadata TEXT, "
               "filetype VARCHAR(60), "
               "datecreated VARCHAR(64), "
               "imagewidth INTEGER, "
               "imageheight INTEGER)");
    qDebug()<<"CPUtil---Tables"<<db.tables(QSql::AllTables);
}

void CPUtil::updateBlogMediaDB() {

    QSqlQuery query;
    QString queryString;
    qDebug()<<"CPUtil---updateBlogMediaDB"<<query.exec("DELETE FROM "+CPEngine::instance().blogSanitizedUrl()+"media;")<<query.executedQuery()<<query.lastError();
    query.clear();
    queryString = "INSERT INTO "+CPEngine::instance().blogSanitizedUrl()+"media VALUES ";
    for(int i=0;i<_mediaItemsModel->rowCount();i++) {
        QVariantMap item = _mediaItemsModel->value(i).toMap();
        queryString += "('"+item[mediaRoleNames[MediaEntry::LinkRole]].toString()+
                "', '"+
                item[mediaRoleNames[MediaEntry::ParentRole]].toString()+
                "', '"+
                item[mediaRoleNames[MediaEntry::DescriptionRole]].toString().replace("'","''")+
                "', '"+
                item[mediaRoleNames[MediaEntry::ThumbnailRole]].toString()+
                "', '"+
                item[mediaRoleNames[MediaEntry::CaptionRole]].toString().replace("'","''")+
                "', '"+
                item[mediaRoleNames[MediaEntry::TitleRole]].toString().replace("'","''")+
                "', '"+
                item[mediaRoleNames[MediaEntry::MetaDataRole]].toString()+
                "', '"+
                item[mediaRoleNames[MediaEntry::FileTypeRole]].toString()+
                "', '"+
                item[mediaRoleNames[MediaEntry::DateCreatedRole]].toDateTime().toString(Qt::ISODate)+
                "', "+
                item[mediaRoleNames[MediaEntry::ImageWidthRole]].toString()+
                ", "+
                item[mediaRoleNames[MediaEntry::ImageHeightRole]].toString()+
                ")";
        if(i!=_mediaItemsModel->rowCount()-1) {
            queryString += ", ";
        } else {
            queryString += ";";
        }
    }
    qDebug()<<"CPUtil---insertAllInBlogMediaDB"<<query.exec(queryString)<<query.lastError();
}

void CPUtil::insertInBlogMediaDB(QVariantMap item) {

    QSqlQuery query;
    QString queryString;
    queryString = "INSERT INTO "+CPEngine::instance().blogSanitizedUrl()+"media VALUES ";
    queryString += "('"+item[mediaRoleNames[MediaEntry::LinkRole]].toString()+
        "', '"+
        item[mediaRoleNames[MediaEntry::ParentRole]].toString()+
        "', '"+
        item[mediaRoleNames[MediaEntry::DescriptionRole]].toString().replace("'","''")+
        "', '"+
        item[mediaRoleNames[MediaEntry::ThumbnailRole]].toString()+
        "', '"+
        item[mediaRoleNames[MediaEntry::CaptionRole]].toString().replace("'","''")+
        "', '"+
        item[mediaRoleNames[MediaEntry::TitleRole]].toString().replace("'","''")+
        "', '"+
        item[mediaRoleNames[MediaEntry::MetaDataRole]].toString()+
        "', '"+
        item[mediaRoleNames[MediaEntry::FileTypeRole]].toString()+
        "', '"+
        item[mediaRoleNames[MediaEntry::DateCreatedRole]].toDateTime().toString(Qt::ISODate)+
        "', "+
        item[mediaRoleNames[MediaEntry::ImageWidthRole]].toString()+
        ", "+
        item[mediaRoleNames[MediaEntry::ImageHeightRole]].toString()+
        ");";
    qDebug()<<"CPUtil---insertInBlogMediaDB"<<query.exec(queryString)<<query.lastError();//<<item[mediaRoleNames[MediaEntry::DateCreatedRole]].toDateTime().toString();
}

void CPUtil::updateInBlogMediaDB(QString mediaLink, QVariantMap item)
{
    QSqlQuery query;
    QString queryString;
    queryString = "UPDATE "+CPEngine::instance().blogSanitizedUrl()+"media SET ";
    queryString += "link='"+item[mediaRoleNames[MediaEntry::LinkRole]].toString()+
        "', parent='"+
        item[mediaRoleNames[MediaEntry::ParentRole]].toString()+
        "', description='"+
        item[mediaRoleNames[MediaEntry::DescriptionRole]].toString().replace("'","''")+
        "', thumbnail='"+
        item[mediaRoleNames[MediaEntry::ThumbnailRole]].toString()+
        "', caption='"+
        item[mediaRoleNames[MediaEntry::CaptionRole]].toString().replace("'","''")+
        "', title='"+
        item[mediaRoleNames[MediaEntry::TitleRole]].toString().replace("'","''")+
        "', metadata='"+
        item[mediaRoleNames[MediaEntry::MetaDataRole]].toString()+
        "', filetype='"+
        item[mediaRoleNames[MediaEntry::FileTypeRole]].toString()+
        "', datecreated='"+
        item[mediaRoleNames[MediaEntry::DateCreatedRole]].toDateTime().toString(Qt::ISODate)+
        "', imagewidth="+
        item[mediaRoleNames[MediaEntry::ImageWidthRole]].toString()+
        ", imageheight="+
        item[mediaRoleNames[MediaEntry::ImageHeightRole]].toString()+
        ");";
    qDebug()<<"CPUtil---updateInBlogMediaDB"<<query.exec(queryString)<<query.lastError();
}

void CPUtil::readBlogMediaFromDB() {
    QSqlQuery query;
    QString queryString;
    qDebug()<<"CPUtil---readBlogMediaFromDB"<<query.exec("SELECT * FROM "+CPEngine::instance().blogSanitizedUrl()+"media;")<<query.executedQuery()<<query.lastError();
    while(query.next()) {
        QVariantMap it;
        it[mediaRoleNames[MediaEntry::LinkRole]] = query.value(0).toString();
        it[mediaRoleNames[MediaEntry::ParentRole]] = query.value(1).toString();
        it[mediaRoleNames[MediaEntry::DescriptionRole]] = query.value(2).toString();
        it[mediaRoleNames[MediaEntry::ThumbnailRole]] = query.value(3).toString();
        it[mediaRoleNames[MediaEntry::CaptionRole]] = query.value(4).toString();
        it[mediaRoleNames[MediaEntry::TitleRole]] = query.value(5).toString();
        it[mediaRoleNames[MediaEntry::MetaDataRole]] = query.value(6).toString();
        it[mediaRoleNames[MediaEntry::FileTypeRole]] = query.value(7).toString();
        it[mediaRoleNames[MediaEntry::DateCreatedRole]] = QDateTime::fromString(query.value(8).toString(), Qt::ISODate);
        it[mediaRoleNames[MediaEntry::DisplayDateRole]] = QDateTime::fromString(query.value(8).toString(), Qt::ISODate).toString("MMM dd, yyyy");
        it[mediaRoleNames[MediaEntry::ImageWidthRole]] = query.value(9).toInt();
        it[mediaRoleNames[MediaEntry::ImageHeightRole]] = query.value(10).toInt();
        _mediaItemsModel->addEntry(it);
    }
}

void CPUtil::createBlogCategoriesTable() {
    QSqlQuery query;
    qDebug()<<"CPUtil---createBlogCategoriesTable"<<query.exec("CREATE TABLE "+CPEngine::instance().blogSanitizedUrl()+"categories (id VARCHAR(25) primary key, "
               "parent VARCHAR(25), "
               "description TEXT, "
               "name VARCHAR(255), "
               "htmlurl VARCHAR(255), "
               "rssurl VARCHAR(255))")<<query.lastError();
    qDebug()<<"CPUtil---Tables"<<db.tables(QSql::AllTables);
}

void CPUtil::updateBlogCategoriesDB() {

    QSqlQuery query;
    QString queryString;
    qDebug()<<"CPUtil---updateBlogCategoriesDB"<<query.exec("DELETE FROM "+CPEngine::instance().blogSanitizedUrl()+"categories;")<<query.executedQuery()<<query.lastError();
    query.clear();
    queryString = "INSERT INTO "+CPEngine::instance().blogSanitizedUrl()+"categories VALUES ";
    for(int i=0;i<_categoriesModel->rowCount();i++) {
        QVariantMap item = _categoriesModel->value(i).toMap();
        queryString += "('"+item[categoryRoleNames[CategoryEntry::IdRole]].toString()+
                "', '"+
                item[categoryRoleNames[CategoryEntry::ParentIdRole]].toString()+
                "', '"+
                item[categoryRoleNames[CategoryEntry::DescriptionRole]].toString()+
                "', '"+
                item[categoryRoleNames[CategoryEntry::CategoryNameRole]].toString()+
                "', '"+
                item[categoryRoleNames[CategoryEntry::HtmlUrlRole]].toString()+
                "', '"+
                item[categoryRoleNames[CategoryEntry::RssUrlRole]].toString()+
                "')";
        if(i!=_categoriesModel->rowCount()-1) {
            queryString += ", ";
        } else {
            queryString += ";";
        }
    }
    qDebug()<<"CPUtil---insertAllInBlogCategoriesDB"<<query.exec(queryString)<<query.lastError();
}

void CPUtil::insertInBlogCategoriesDB(QVariantMap item) {

    QSqlQuery query;
    QString queryString = "INSERT INTO "+CPEngine::instance().blogSanitizedUrl()+"categories VALUES ";
    queryString += "('"+item[categoryRoleNames[CategoryEntry::IdRole]].toString()+
        "', '"+
        item[categoryRoleNames[CategoryEntry::ParentIdRole]].toString()+
        "', '"+
        item[categoryRoleNames[CategoryEntry::DescriptionRole]].toString()+
        "', '"+
        item[categoryRoleNames[CategoryEntry::CategoryNameRole]].toString()+
        "', '"+
        item[categoryRoleNames[CategoryEntry::HtmlUrlRole]].toString()+
        "', '"+
        item[categoryRoleNames[CategoryEntry::RssUrlRole]].toString()+
        "')";
    queryString += ";";
    qDebug()<<"CPUtil---insertInBlogCategoriesDB"<<query.exec(queryString)<<query.lastError();
}

void CPUtil::deleteInBlogCategoriesDB(QString categoryId)
{
    QSqlQuery query;
    QString queryString = "DELETE FROM "+CPEngine::instance().blogSanitizedUrl()+
            "categories WHERE id='"+
            categoryId+"';";
    qDebug()<<"CPUtil---deleteInBlogCategoriesDB"<<query.exec(queryString)<<query.lastError();
}

void CPUtil::readBlogCategoriesFromDB() {
    QSqlQuery query;
    QString queryString;
    qDebug()<<"CPUtil---readBlogCategoriesFromDB"<<query.exec("SELECT * FROM "+CPEngine::instance().blogSanitizedUrl()+"categories;")<<query.executedQuery()<<query.lastError();
    while(query.next()) {
        QVariantMap it;
        it[categoryRoleNames[CategoryEntry::IdRole]] = query.value(0).toString();
        it[categoryRoleNames[CategoryEntry::ParentIdRole]] = query.value(1).toString();
        it[categoryRoleNames[CategoryEntry::DescriptionRole]] = query.value(2).toString();
        it[categoryRoleNames[CategoryEntry::CategoryNameRole]] = query.value(3).toString();
        it[categoryRoleNames[CategoryEntry::HtmlUrlRole]] = query.value(4).toString();
        it[categoryRoleNames[CategoryEntry::RssUrlRole]] = query.value(5).toString();
        it[categoryRoleNames[CategoryEntry::MarkedRole]] = false;
        _categoriesModel->addEntry(it);
    }
}

void CPUtil::createBlogTagsTable() {
    QSqlQuery query;
    qDebug()<<"CPUtil---createBlogTagsTable"<<query.exec("CREATE TABLE "+CPEngine::instance().blogSanitizedUrl()+"tags (id VARCHAR(25) primary key, "
               "name VARCHAR(25), "
               "count INTEGER, "
               "slug VARCHAR(255), "
               "htmlurl VARCHAR(255), "
               "rssurl VARCHAR(255), "
               "datatagversion INTEGER)");
    qDebug()<<"CPUtil---Tables"<<db.tables(QSql::AllTables);
}
void CPUtil::updateBlogTagsDB() {
    QSqlQuery query;
    QString queryString;
    qDebug()<<"CPUtil---updateBlogTagsDB"<<query.exec("DELETE FROM "+CPEngine::instance().blogSanitizedUrl()+"tags;")<<query.executedQuery()<<query.lastError();
    query.clear();
    queryString = "INSERT INTO "+CPEngine::instance().blogSanitizedUrl()+"tags VALUES ";
    for(int i=0;i<_tagsModel->rowCount();i++) {
        QVariantMap item = _tagsModel->value(i).toMap();
        queryString += "('"+item[tagRoleNames[TagEntry::IdRole]].toString()+
                "', '"+
                item[tagRoleNames[TagEntry::NameRole]].toString()+
                "', "+
                item[tagRoleNames[TagEntry::CountRole]].toString()+
                ", '"+
                item[tagRoleNames[TagEntry::SlugRole]].toString()+
                "', '"+
                item[tagRoleNames[TagEntry::HtmlUrlRole]].toString()+
                "', '"+
                item[tagRoleNames[TagEntry::RssUrlRole]].toString()+
                "', 0)";
        if(i!=_tagsModel->rowCount()-1) {
            queryString += ", ";
        } else {
            queryString += ";";
        }
    }
    qDebug()<<"CPUtil---insetInBlogTagsDB"<<query.exec(queryString)<<query.lastError();
}
void CPUtil::readBlogTagsFromDB() {
    QSqlQuery query;
    QString queryString;
    qDebug()<<"CPUtil---readBlogTagsFromDB"<<query.exec("SELECT * FROM "+CPEngine::instance().blogSanitizedUrl()+"tags;")<<query.executedQuery()<<query.lastError();
    while(query.next()) {
        QVariantMap it;
        it[tagRoleNames[TagEntry::IdRole]] = query.value(0).toString();
        it[tagRoleNames[TagEntry::NameRole]] = query.value(1).toString();
        it[tagRoleNames[TagEntry::CountRole]] = query.value(2).toString();
        it[tagRoleNames[TagEntry::SlugRole]] = query.value(3).toString();
        it[tagRoleNames[TagEntry::HtmlUrlRole]] = query.value(4).toString();
        it[tagRoleNames[TagEntry::RssUrlRole]] = query.value(5).toString();
        it[tagRoleNames[TagEntry::DataTagVersionNumberRole]] = query.value(6).toString();
        it[tagRoleNames[TagEntry::MarkedRole]] = false;
        _tagsModel->addEntry(it);
    }
}

void CPUtil::saveLocalDraftPage(const QString id,
                                QString dateCreated,
                                QString title,
                                QString description,
                                QString excerpt,
                                QString slug,
                                QString status,
                                QString password,
                                bool commentsOpen,
                                bool pingsOpen,
                                int pageParentId,
                                int pageOrder) {
    if(status!="localdraft")
        return;
    qDebug()<<"CPUtil---saveLocalDraftPage"<<dateCreated;
    QDateTime d = QDateTime::fromString(dateCreated, Qt::ISODate);
    d.setTimeSpec(Qt::UTC);
    d = d.toLocalTime();
    QVariantMap it;
    it[pageRoleNames[PageEntry::IdRole]] = "localpage."+QString::number(d.toTime_t());
    it[pageRoleNames[PageEntry::TitleRole]] = title;
    it[pageRoleNames[PageEntry::LocalIdRole]] = "localpage."+QString::number(d.toTime_t());
    it[pageRoleNames[PageEntry::DescRole]] = description;
    it[pageRoleNames[PageEntry::ContentSnippetRole]] = getHtmlTextSnippet(description);
    it[pageRoleNames[PageEntry::ExcerptRole]] = excerpt;
    it[pageRoleNames[PageEntry::SlugRole]] = slug;
    it[pageRoleNames[PageEntry::LinkRole]] = "";
    it[pageRoleNames[PageEntry::PermaLinkRole]] = "";
    it[pageRoleNames[PageEntry::WpAuthorRole]] = CPEngine::instance().blogUsername();
    it[pageRoleNames[PageEntry::WpAuthorDisplayNameRole]] = CPEngine::instance().blogUsername();
    it[pageRoleNames[PageEntry::WpPageParentTitleRole]] = "";
    it[pageRoleNames[PageEntry::WpPageParentIdRole]] = "";
    it[pageRoleNames[PageEntry::WpPageParentOrderRole]] = 0;
    it[pageRoleNames[PageEntry::StatusRole]] = status;
    it[pageRoleNames[PageEntry::PasswordRole]] = password;
    it[pageRoleNames[PageEntry::DateCreatedRole]] = d;
    it[pageRoleNames[PageEntry::DisplayDateRole]] = d.toString("ddd hh:mm AP MMM dd, yyyy");
    it[pageRoleNames[PageEntry::PageTimeRole]] = d.time();
    it[pageRoleNames[PageEntry::PageDateRole]] = d.date();
    it[pageRoleNames[PageEntry::CommentsOpenRole]] = commentsOpen;
    it[pageRoleNames[PageEntry::PingsOpenRole]] = pingsOpen;
    it[pageRoleNames[PageEntry::CommentsCountRole]] = 0;
    it[pageRoleNames[PageEntry::MarkedRole]] = false;
    if(id.isEmpty()) {
        it[pageRoleNames[PageEntry::IdRole]] = "localpage."+QString::number(d.toTime_t());
        it[pageRoleNames[PageEntry::LocalIdRole]] = "localpage."+QString::number(d.toTime_t());
        _pagesModel->insertEntry(0, it);
        insertInBlogPagesDB(it);
    } else {
        it[pageRoleNames[PageEntry::IdRole]] = id;
        it[pageRoleNames[PageEntry::LocalIdRole]] = id;
        int pos=-1;
        for(int i=0;i<_pagesModel->size();i++) {
            if(_pagesModel->value(i).toMap().value(pageRoleNames[PageEntry::IdRole]).toString()==id) {
                pos = i;
                break;
            }
        }
        if(pos!=-1)
            _pagesModel->replace(pos, it);
        updateInBlogPagesDB(id, it);
    }
}

void CPUtil::customClearPagesModel()
{
    int count=_pagesModel->size();
    while(count>0) {
        for(int i=0;i<_pagesModel->size();i++) {
            if(!_pagesModel->value(i).toMap().value("pageId").toString().startsWith("local")) {
                _pagesModel->removeEntry(i);
                break;
            }
        }
        count--;
    }
}

void CPUtil::saveLocalDraftPost(const QString id,
                       QString dateCreated,
                       QString title,
                       QString description,
                       QString excerpt,
                       QString slug,
                       QString status,
                       QString password,
                       QString categories,
                       QString tags,
                       bool commentsOpen,
                       bool pingsOpen,
                       bool sticky) {
    if(status!="localdraft")
        return;
    qDebug()<<"CPUtil---saveLocalDraftPost"<<dateCreated;
    QDateTime d = QDateTime::fromString(dateCreated, Qt::ISODate);
    d.setTimeSpec(Qt::UTC);
    d = d.toLocalTime();
    QVariantMap it;
    it[postRoleNames[PostEntry::TitleRole]] = title;
    it[postRoleNames[PostEntry::DescRole]] = description;
    it[postRoleNames[PostEntry::ContentSnippetRole]] = getHtmlTextSnippet(description);
    it[postRoleNames[PostEntry::ExcerptRole]] = excerpt;
    it[postRoleNames[PostEntry::SlugRole]] = slug;
    it[postRoleNames[PostEntry::LinkRole]] = "";
    it[postRoleNames[PostEntry::PermaLinkRole]] = "";
    it[postRoleNames[PostEntry::WpAuthorRole]] = CPEngine::instance().blogUsername();
    it[postRoleNames[PostEntry::WpAuthorDisplayNameRole]] = CPEngine::instance().blogUsername();
    it[postRoleNames[PostEntry::CommentsCountRole]] = 0;
    it[postRoleNames[PostEntry::StatusRole]] = status;
    it[postRoleNames[PostEntry::DisplayStatusRole]] = status;
    it[postRoleNames[PostEntry::StickyRole]] = sticky;
    it[postRoleNames[PostEntry::PasswordRole]] = password;
    it[postRoleNames[PostEntry::CategoriesRole]] = categories.split(", ");
    it[postRoleNames[PostEntry::TagsRole]] = tags.split(", ");
    it[postRoleNames[PostEntry::DateCreatedRole]] = d;
    it[postRoleNames[PostEntry::DisplayDateRole]] = d.toString("ddd hh:mm AP MMM dd, yyyy");
    it[postRoleNames[PostEntry::ModifiedRole]] = d;
    it[postRoleNames[PostEntry::DisplayModifiedRole]] = d.toString("ddd hh:mm AP MMM dd, yyyy");
    it[postRoleNames[PostEntry::PostTimeRole]] = d.time();
    it[postRoleNames[PostEntry::PostDateRole]] = d.date();
    it[postRoleNames[PostEntry::CommentsOpenRole]] = commentsOpen;
    it[postRoleNames[PostEntry::PingsOpenRole]] = pingsOpen;
    it[postRoleNames[PostEntry::CommentsCountRole]] = 0;
    it[postRoleNames[PostEntry::MarkedRole]] = false;
    if(id.isEmpty()) {
        it[postRoleNames[PostEntry::IdRole]] = "localpost."+QString::number(d.toTime_t());
        it[postRoleNames[PostEntry::LocalIdRole]] = "localpost."+QString::number(d.toTime_t());
        _postsModel->insertEntry(0, it);
        insertInBlogPostsDB(it);
    } else {
        it[postRoleNames[PostEntry::IdRole]] = id;
        it[postRoleNames[PostEntry::LocalIdRole]] = id;
        int pos=-1;
        for(int i=0;i<_postsModel->size();i++) {
            if(_postsModel->value(i).toMap().value(postRoleNames[PostEntry::IdRole]).toString()==id) {
                pos = i;
                break;
            }
        }
        if(pos!=-1)
            _postsModel->replace(pos, it);
        updateInBlogPostsDB(id, it);
    }
}

void CPUtil::customClearPostsModel()
{
    int count=_postsModel->size();
    while(count>0) {
        for(int i=0;i<_postsModel->size();i++) {
            if(!_postsModel->value(i).toMap().value("postId").toString().startsWith("local")) {
                _postsModel->removeEntry(i);
                break;
            }
        }
        count--;
    }
}

void CPUtil::deleteLocalPage(const QString pageId)
{
    deletePageInModel(_pagesModel, pageId);
    QSqlQuery query;
    qDebug()<<"CPUtil---deleteLocalPage"<<query.exec("DELETE FROM "+CPEngine::instance().blogSanitizedUrl()+"posts WHERE id='"+pageId+"';")<<query.executedQuery()<<query.lastError();
}

void CPUtil::deleteLocalPost(const QString postId)
{
    deletePostInModel(_postsModel, postId);
    QSqlQuery query;
    qDebug()<<"CPUtil---deleteLocalPost"<<query.exec("DELETE FROM "+CPEngine::instance().blogSanitizedUrl()+"posts WHERE id='"+postId+"';")<<query.executedQuery()<<query.lastError();
}


void CPUtil::prepareUploadListForSavedItem(const QString content)
{
    QRegExp imgTagRegex("\\<img[^\\>]*src\\s*=\\s*\"([^\"]*)\"[^\\>]*\\>", Qt::CaseInsensitive);
    imgTagRegex.setMinimal(true);
    int offset = 0;
    while( (offset = imgTagRegex.indexIn(content, offset)) != -1){
        offset += imgTagRegex.matchedLength();
        QString url = imgTagRegex.cap(1);
        if(url.startsWith("file://") && !_editorUploadImages.contains(url))
            _editorUploadImages.append(url);
    }
    emit editorUploadImagesChanged();
}

void CPUtil::markCategoriesInModel(const QString categoriesString)
{
    QStringList categories = categoriesString.split(", ");
    for(int i=0;i<_categoriesModel->size();i++) {
        QVariantMap item = _categoriesModel->value(i).toMap();
        if(categories.contains(item[categoryRoleNames[CategoryEntry::CategoryNameRole]].toString())) {
            item[categoryRoleNames[CategoryEntry::MarkedRole]] = true;
        } else {
            item[categoryRoleNames[CategoryEntry::MarkedRole]] = false;
        }
        _categoriesModel->replace(i, item);
    }
    emit categoriesChanged();
}

void CPUtil::markCategoryInModel(const int idx)
{
    QVariantMap item = _categoriesModel->value(idx).toMap();
    item[categoryRoleNames[CategoryEntry::MarkedRole]] = true;
    _categoriesModel->replace(idx, item);
    emit categoriesChanged();
}

void CPUtil::unmarkCategoryInModel(const int idx)
{
    QVariantMap item = _categoriesModel->value(idx).toMap();
    item[categoryRoleNames[CategoryEntry::MarkedRole]] = false;
    _categoriesModel->replace(idx, item);
    emit categoriesChanged();
}

QString CPUtil::getMarkedCategoriesFromModel()
{
    QStringList categories;
    for(int i=0;i<_categoriesModel->size();i++) {
        QVariantMap item = _categoriesModel->value(i).toMap();
        if(item[categoryRoleNames[CategoryEntry::MarkedRole]].toBool()) {
            categories.append(item[categoryRoleNames[CategoryEntry::CategoryNameRole]].toString());
            item[categoryRoleNames[CategoryEntry::MarkedRole]] = false;
            _categoriesModel->replace(i, item);
        }
    }
    emit categoriesChanged();
    return categories.join(", ");
}

void CPUtil::clearPostEditionData()
{
    setPostEditionState(ProgressState::None);
    setPostEditionStatus("");
}

void CPUtil::clearPageEditionData()
{
    setPageEditionState(ProgressState::None);
    setPageEditionStatus("");
}

void CPUtil::updatePostInfoFromPostPage(const QString postId, const QVariantMap post)
{
    int idx=updatePost(_postsModel, post);
    if(idx==-1)
        insertInBlogPostsDB(_postsModel->value(0).toMap());
    else
        updateInBlogPostsDB(postId, _postsModel->value(idx).toMap());
    emit postsChanged();
}

void CPUtil::updatePageInfoFromPagePage(const QString pageId, const QVariantMap page)
{
    int idx=updatePage(_pagesModel, page);
    if(idx==-1)
        insertInBlogPagesDB(_pagesModel->value(0).toMap());
    else
        updateInBlogPagesDB(pageId, _pagesModel->value(idx).toMap());
    emit pagesChanged();
}

void CPUtil::fetchCommentCountForAllPosts()
{
    for(int i=0;i<_postsModel->size();i++) {
        QVariantMap item = _postsModel->value(i).toMap();
        if(item[postRoleNames[PostEntry::StatusRole]].toString()!="draft" ||
                item[postRoleNames[PostEntry::StatusRole]].toString()!="localdraft") {
            fetchPostCommentsCount(item[postRoleNames[PostEntry::IdRole]].toString());
        }
    }
}

void CPUtil::abortAllRunningRequests()
{
    QList<int> keys = requests.keys();
    foreach(int i, keys) {
        requests[i]->abortRequest();
        requests[i]->deleteLater();
        requests.remove(i);
    }
}
