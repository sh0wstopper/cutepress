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

#include "abstractcpobject.h"
#include <QDebug>

AbstractCPObject::AbstractCPObject(QObject *parent)
        :QObject(parent)
{

    blogRoleNames[BlogEntry::NameRole] = "blogName";
    blogRoleNames[BlogEntry::IsAdminRole] = "blogIsAdmin";
    blogRoleNames[BlogEntry::IdRole] = "blogId";
    blogRoleNames[BlogEntry::UrlRole] = "blogUrl";
    blogRoleNames[BlogEntry::XmlRpcUrlRole] = "blogXmlRpcUrl";
    blogRoleNames[BlogEntry::HtUsernameRole] = "blogHtaccessUsername";
    blogRoleNames[BlogEntry::HtPasswordRole] = "blogHtaccessPassword";
    blogRoleNames[BlogEntry::UsernameRole] = "blogUsername";
    blogRoleNames[BlogEntry::PasswordRole] = "blogPassword";
    blogRoleNames[BlogEntry::NumberOfPostsRole] = "blogNumberOfPosts";
    blogRoleNames[BlogEntry::IsWordpressRole] = "blogIsWordpress";
    blogRoleNames[BlogEntry::PagesCountRole] = "blogPagesCount";
    blogRoleNames[BlogEntry::PostsCountRole] = "blogPostsCount";
    blogRoleNames[BlogEntry::CommentsCountRole] = "blogCommentsCount";
    blogRoleNames[BlogEntry::MarkedRole] = "blogMarked";
    blogRoleNames[BlogEntry::IsActiveRole] = "blogIsActive";
    blogRoleNames[BlogEntry::SanitizedUrlRole] = "blogSanitizedUrl";

    pageRoleNames[PageEntry::IdRole] = "pageId";
    pageRoleNames[PageEntry::TitleRole] = "pageTitle";
    pageRoleNames[PageEntry::LocalIdRole] = "pageLocalId";
    pageRoleNames[PageEntry::DescRole] = "pageDescription";
    pageRoleNames[PageEntry::ContentSnippetRole] = "pageContentSnippet";
    pageRoleNames[PageEntry::ExcerptRole] = "pageExcerpt";
    pageRoleNames[PageEntry::SlugRole] = "pageSlug";
    pageRoleNames[PageEntry::LinkRole] = "pageLink";
    pageRoleNames[PageEntry::PermaLinkRole] = "pagePermalink";
    pageRoleNames[PageEntry::WpAuthorRole] = "pageWpAuthor";
    pageRoleNames[PageEntry::WpAuthorDisplayNameRole] = "pageWpAuthorDisplayName";
    pageRoleNames[PageEntry::WpPageParentTitleRole] = "pageParentTitle";
    pageRoleNames[PageEntry::WpPageParentIdRole] = "pageParentId";
    pageRoleNames[PageEntry::WpPageParentOrderRole] = "pageParentOrder";
    pageRoleNames[PageEntry::StatusRole] = "pagePublishStatus";
    pageRoleNames[PageEntry::PasswordRole] = "pagePassword";
    pageRoleNames[PageEntry::DateCreatedRole] = "pageDateCreated";
    pageRoleNames[PageEntry::DisplayDateRole] = "pageDisplayDate";
    pageRoleNames[PageEntry::PageTimeRole] = "pageTime";
    pageRoleNames[PageEntry::PageDateRole] = "pageDate";
    pageRoleNames[PageEntry::CommentsOpenRole] = "pageCommentsOpen";
    pageRoleNames[PageEntry::CommentsCountRole] = "pageCommentsCount";
    pageRoleNames[PageEntry::PingsOpenRole] = "pagePingsOpen";
    pageRoleNames[PageEntry::TemplateRole] = "pageTemplate";
    pageRoleNames[PageEntry::MarkedRole] = "pageMarked";

    postRoleNames[PostEntry::IdRole] = "postId";
    postRoleNames[PostEntry::TitleRole] = "postTitle";
    postRoleNames[PostEntry::LocalIdRole] = "postLocalId";
    postRoleNames[PostEntry::DescRole] = "postDescription";
    postRoleNames[PostEntry::ContentSnippetRole] = "postContentSnippet";
    postRoleNames[PostEntry::ExcerptRole] = "postExcerpt";
    postRoleNames[PostEntry::SlugRole] = "postSlug";
    postRoleNames[PostEntry::LinkRole] = "postLink";
    postRoleNames[PostEntry::PermaLinkRole] = "postPermalink";
    postRoleNames[PostEntry::WpAuthorDisplayNameRole] = "postWpAuthorDisplayName";
    postRoleNames[PostEntry::CategoriesRole] = "postCategories";
    postRoleNames[PostEntry::TagsRole] = "postTags";
    postRoleNames[PostEntry::CommentsCountRole] = "postCommentsCount";
    postRoleNames[PostEntry::StatusRole] = "postPublishStatus";
    postRoleNames[PostEntry::DisplayStatusRole] = "postDisplayStatus";
    postRoleNames[PostEntry::StickyRole] = "postSticky";
    postRoleNames[PostEntry::PasswordRole] = "postPassword";
    postRoleNames[PostEntry::DateCreatedRole] = "postDateCreated";
    postRoleNames[PostEntry::DisplayDateRole] = "postDisplayDate";
    postRoleNames[PostEntry::PostTimeRole] = "postTime";
    postRoleNames[PostEntry::PostDateRole] = "postDate";
    postRoleNames[PostEntry::ModifiedRole] = "postModified";
    postRoleNames[PostEntry::DisplayModifiedRole] = "postDisplayModified";
    postRoleNames[PostEntry::CommentsOpenRole] = "postCommentsOpen";
    postRoleNames[PostEntry::PingsOpenRole] = "postPingsOpen";
    postRoleNames[PostEntry::CommentsCountRole] = "postCommentsCount";
    postRoleNames[PostEntry::MarkedRole] = "postMarked";

    commentRoleNames[CommentEntry::IdRole] = "commentId";
    commentRoleNames[CommentEntry::LocalIdRole] = "commentLocalId";
    commentRoleNames[CommentEntry::LinkRole] = "commentLink";
    commentRoleNames[CommentEntry::UserIdRole] = "commentUserId";
    commentRoleNames[CommentEntry::ContentRole] = "commentContent";
    commentRoleNames[CommentEntry::ContentPreviewRole] = "commentPreview";
    commentRoleNames[CommentEntry::PostIdRole] = "commentPostId";
    commentRoleNames[CommentEntry::PostTitleRole] = "commentPostTitle";
    commentRoleNames[CommentEntry::AuthorRole] = "commentAuthorName";
    commentRoleNames[CommentEntry::AuthorUrlRole] = "commentAuthorUrl";
    commentRoleNames[CommentEntry::AuthorEmailRole] = "commentAuthorEmail";
    commentRoleNames[CommentEntry::AuthorIpRole] = "commentAuthorIp";
    commentRoleNames[CommentEntry::StatusRole] = "commentStatus";
    commentRoleNames[CommentEntry::GravatarUrlRole] = "commentAuthorAvatarUrl";
    commentRoleNames[CommentEntry::DateCreatedRole] = "commentDate";
    commentRoleNames[CommentEntry::OrderRole] = "commentOrder";
    commentRoleNames[CommentEntry::MarkedRole] = "commentMarked";

    categoryRoleNames[CategoryEntry::IdRole] = "categoryId";
    categoryRoleNames[CategoryEntry::ParentIdRole] = "categoryParentId";
    categoryRoleNames[CategoryEntry::DescriptionRole] = "categoryDescription";
    categoryRoleNames[CategoryEntry::CategoryNameRole] = "categoryName";
    categoryRoleNames[CategoryEntry::HtmlUrlRole] = "categoryHtmlUrl";
    categoryRoleNames[CategoryEntry::RssUrlRole] = "categoryRssUrl";
    categoryRoleNames[CategoryEntry::MarkedRole] = "categoryMarked";

    mediaRoleNames[MediaEntry::TitleRole] = "mediaTitle";
    mediaRoleNames[MediaEntry::DescriptionRole] = "mediaDescription";
    mediaRoleNames[MediaEntry::CaptionRole] = "mediaCaption";
    mediaRoleNames[MediaEntry::LinkRole] = "mediaLink";
    mediaRoleNames[MediaEntry::ThumbnailRole] = "mediaThumbnail";
    mediaRoleNames[MediaEntry::MetaDataRole] = "mediaMetadata";
    mediaRoleNames[MediaEntry::ParentRole] = "mediaParentId";
    mediaRoleNames[MediaEntry::FileTypeRole] = "mediaFileType";
    mediaRoleNames[MediaEntry::DateCreatedRole] = "mediaDateCreated";
    mediaRoleNames[MediaEntry::DisplayDateRole] = "mediaDisplayDate";
    mediaRoleNames[MediaEntry::ImageWidthRole] = "mediaImageWidth";
    mediaRoleNames[MediaEntry::ImageHeightRole] = "mediaImageHeight";

    tagRoleNames[TagEntry::IdRole] = "tagId";
    tagRoleNames[TagEntry::NameRole] = "tagName";
    tagRoleNames[TagEntry::SlugRole] = "tagSlug";
    tagRoleNames[TagEntry::MarkedRole] = "tagMarked";
    tagRoleNames[TagEntry::HtmlUrlRole] = "tagHtmlUrl";
    tagRoleNames[TagEntry::RssUrlRole] = "tagRssUrl";
    tagRoleNames[TagEntry::CountRole] = "tagCount";
}

AbstractCPObject::~AbstractCPObject()
{

}

void AbstractCPObject::appendPages(RoleItemModel *model, const QVariantList pages)
{
	foreach(QVariant i, pages) {
		QVariantMap page = i.toMap();
		QVariantMap it;
	    it[pageRoleNames[PageEntry::IdRole]] = page["page_id"].toString();
	    it[pageRoleNames[PageEntry::TitleRole]] = page["title"].toString();
	    it[pageRoleNames[PageEntry::LocalIdRole]] = page["page_id"].toString();
	    QString desc;
	    if (!page["text_more"].toString().isEmpty()) {
	        // post is split into two parts
	        desc = page["description"].toString()
	            +   "\n <!--more--> \n"
	            +   page["text_more"].toString();
	    } else
	        desc = page["description"].toString();
	    it[pageRoleNames[PageEntry::DescRole]] = desc;
	    it[pageRoleNames[PageEntry::ContentSnippetRole]] = getHtmlTextSnippet(desc);
		it[pageRoleNames[PageEntry::ExcerptRole]] = page["excerpt"].toString();
		it[pageRoleNames[PageEntry::SlugRole]] = page["wp_slug"].toString();
	    it[pageRoleNames[PageEntry::LinkRole]] = page["link"].toString();
	    it[pageRoleNames[PageEntry::PermaLinkRole]] = page["permaLink"].toString();
	    it[pageRoleNames[PageEntry::WpAuthorRole]] = page["wp_author_id"].toString();
	    it[pageRoleNames[PageEntry::WpAuthorDisplayNameRole]] = page["wp_author_display_name"].toString();
	    it[pageRoleNames[PageEntry::WpPageParentTitleRole]] = page["wp_parent_title"].toString();
	    it[pageRoleNames[PageEntry::WpPageParentIdRole]] = page["wp_parent_id"].toString();
	    it[pageRoleNames[PageEntry::WpPageParentOrderRole]] = page["wp_parent_order"].toInt();
	    it[pageRoleNames[PageEntry::StatusRole]] = page["page_status"].toString();
	    it[pageRoleNames[PageEntry::PasswordRole]] = page["wp_password"].toString();
    	QDateTime d = QDateTime::fromString(page["date_created_gmt"].toString(), "yyyyMMddThh:mm:ss");
//	    	if(d>QDateTime::currentDateTimeUtc())
//		    	it[postRoleNames[PostEntry::StatusRole]] = "future";
		d.setTimeSpec(Qt::UTC);
		d = d.toLocalTime();
	    it[pageRoleNames[PageEntry::DateCreatedRole]] = d;
		it[pageRoleNames[PageEntry::DisplayDateRole]] = d.toString("ddd hh:mm AP MMM dd, yyyy");
	    it[pageRoleNames[PageEntry::PageTimeRole]] = QDateTime::fromString(page["dateCreated"].toString(), Qt::ISODate).time();
	    it[pageRoleNames[PageEntry::PageDateRole]] = QDateTime::fromString(page["dateCreated"].toString(), Qt::ISODate).date();
	    it[pageRoleNames[PageEntry::CommentsOpenRole]] = page["mt_allow_comments"].toString();
	    it[pageRoleNames[PageEntry::PingsOpenRole]] = page["mt_allow_pings"].toString();
	    it[pageRoleNames[PageEntry::CommentsCountRole]] = 0;
	    it[pageRoleNames[PageEntry::MarkedRole]] = false;
	    model->addEntry(it);
		//qDebug()<<"AbstractCPObject---Page"<<page["page_id"].toString()<<page["title"].toString()<<page["wp_author_display_name"].toString()<<d;
	}
}

int AbstractCPObject::updatePage(RoleItemModel *model, const QVariantMap page)
{
    QVariantMap it;
    it[pageRoleNames[PageEntry::IdRole]] = page["page_id"].toString();
    it[pageRoleNames[PageEntry::TitleRole]] = page["title"].toString();
    it[pageRoleNames[PageEntry::LocalIdRole]] = page["page_id"].toString();
    it[pageRoleNames[PageEntry::DescRole]] = page["description"].toString();
    QString desc;
    if (!page["text_more"].toString().isEmpty()) {
        // post is split into two parts
        desc = page["description"].toString()
            +   "\n <!--more--> \n"
            +   page["text_more"].toString();
    } else
        desc = page["description"].toString();
    it[pageRoleNames[PageEntry::DescRole]] = desc;
    it[pageRoleNames[PageEntry::ContentSnippetRole]] = getHtmlTextSnippet(desc);
    it[pageRoleNames[PageEntry::ExcerptRole]] = page["excerpt"].toString();
    it[pageRoleNames[PageEntry::SlugRole]] = page["wp_slug"].toString();
    it[pageRoleNames[PageEntry::LinkRole]] = page["link"].toString();
    it[pageRoleNames[PageEntry::PermaLinkRole]] = page["permaLink"].toString();
    it[pageRoleNames[PageEntry::WpAuthorRole]] = page["wp_author_id"].toString();
    it[pageRoleNames[PageEntry::WpAuthorDisplayNameRole]] = page["wp_author_display_name"].toString();
    it[pageRoleNames[PageEntry::WpPageParentTitleRole]] = page["wp_parent_title"].toString();
    it[pageRoleNames[PageEntry::WpPageParentIdRole]] = page["wp_parent_id"].toString();
    it[pageRoleNames[PageEntry::WpPageParentOrderRole]] = page["wp_parent_order"].toInt();
    it[pageRoleNames[PageEntry::StatusRole]] = page["page_status"].toString();
    it[pageRoleNames[PageEntry::PasswordRole]] = page["wp_password"].toString();
    QDateTime d = QDateTime::fromString(page["date_created_gmt"].toString(), "yyyyMMddThh:mm:ss");
//          if(d>QDateTime::currentDateTimeUtc())
//              it[postRoleNames[PostEntry::StatusRole]] = "future";
    d.setTimeSpec(Qt::UTC);
    d = d.toLocalTime();
    it[pageRoleNames[PageEntry::DateCreatedRole]] = d;
    it[pageRoleNames[PageEntry::DisplayDateRole]] = d.toString("ddd hh:mm AP MMM dd, yyyy");
    it[pageRoleNames[PageEntry::PageTimeRole]] = QDateTime::fromString(page["dateCreated"].toString(), Qt::ISODate).time();
    it[pageRoleNames[PageEntry::PageDateRole]] = QDateTime::fromString(page["dateCreated"].toString(), Qt::ISODate).date();
    it[pageRoleNames[PageEntry::CommentsOpenRole]] = page["mt_allow_comments"].toString();
    it[pageRoleNames[PageEntry::PingsOpenRole]] = page["mt_allow_pings"].toString();
    it[pageRoleNames[PageEntry::CommentsCountRole]] = 0;
    it[pageRoleNames[PageEntry::MarkedRole]] = false;
    for(int i=0;i<model->size();i++) {
        if(model->value(i).toMap().value(pageRoleNames[PageEntry::IdRole]).toString()==page["page_id"].toString()) {
            model->replace(i, it);
            //qDebug()<<"AbstractCPObject---UpdatePage"<<page["page_id"].toString()<<page["title"].toString()<<page["wp_author_display_name"].toString()<<d;
            return i;
        }
    }
    model->insertEntry(0, it);
    return -1;
}

void AbstractCPObject::appendPosts(RoleItemModel *model, const QVariantList posts)
{
    foreach(QVariant i, posts) {
        QVariantMap post = i.toMap();
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
        model->addEntry(it);
        //qDebug()<<"AbstractCPObject---Post"<<post["postid"].toString()<<model->size()<<post["post_status"].toString()<<post["mt_allow_pings"].toString();
    }
}

int AbstractCPObject::updatePost(RoleItemModel *model, const QVariantMap post)
{
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
    for(int i=0;i<model->size();i++) {
        if(model->value(i).toMap().value(postRoleNames[PostEntry::IdRole]).toString()==post["postid"].toString()) {
            model->replace(i, it);
            //qDebug()<<"AbstractCPObject---UpdatePost"<<post["postid"].toString()<<post["title"].toString()<<post["mt_allow_pings"].toString();
            return i;
        }
    }
    model->insertEntry(0, it);
    return -1;
}

void AbstractCPObject::appendComments(RoleItemModel *model, const QVariantList comments)
{
    foreach(QVariant i, comments) {
        QVariantMap comment = i.toMap();
        QVariantMap it;
        it[commentRoleNames[CommentEntry::IdRole]] = comment["comment_id"].toString();
        it[commentRoleNames[CommentEntry::LocalIdRole]] = comment["comment_id"].toString()+"."+comment["post_id"].toString();
        it[commentRoleNames[CommentEntry::LinkRole]] = comment["link"].toString();
        it[commentRoleNames[CommentEntry::UserIdRole]] = comment["user_id"].toString();
        it[commentRoleNames[CommentEntry::ContentRole]] = comment["content"].toString();
        it[commentRoleNames[CommentEntry::ContentPreviewRole]] = comment["content"].toString().left(200);
        it[commentRoleNames[CommentEntry::PostIdRole]] = comment["post_id"].toString();
        it[commentRoleNames[CommentEntry::PostTitleRole]] = comment["post_title"];
        it[commentRoleNames[CommentEntry::AuthorRole]] = comment["author"].toString();
        it[commentRoleNames[CommentEntry::AuthorUrlRole]] = comment["author_url"];
        it[commentRoleNames[CommentEntry::AuthorEmailRole]] = comment["author_email"];
        it[commentRoleNames[CommentEntry::AuthorIpRole]] = comment["author_ip"];
        it[commentRoleNames[CommentEntry::StatusRole]] = comment["status"];
        it[commentRoleNames[CommentEntry::GravatarUrlRole]] = "http://www.gravatar.com/avatar/"+
                QString(QCryptographicHash::hash(comment["author_email"].toString().toUtf8(),
                                                 QCryptographicHash::Md5 ).toHex())+
                "?s=100&d=mm";
        QDateTime d = QDateTime::fromString(comment["date_created_gmt"].toString(), "yyyyMMddThh:mm:ss");
        d.setTimeSpec(Qt::UTC);
        d = d.toLocalTime();
        it[commentRoleNames[CommentEntry::DateCreatedRole]] = d.toString("ddd hh:mm AP MMM dd, yyyy");
        it[commentRoleNames[CommentEntry::OrderRole]] = 0;
        it[commentRoleNames[CommentEntry::MarkedRole]] = false;
        model->addEntry(it);
        //qDebug()<<"AbstractCPObject---Comment"<<comment["comment_id"].toString()<<comment["post_id"].toString()<<comment["link"].toString();
    }
}

int AbstractCPObject::updateComment(RoleItemModel *model, const QVariantMap comment)
{
    QVariantMap it;
    it[commentRoleNames[CommentEntry::IdRole]] = comment["comment_id"].toString();
    it[commentRoleNames[CommentEntry::LocalIdRole]] = comment["comment_id"].toString()+"."+comment["post_id"].toString();
    it[commentRoleNames[CommentEntry::LinkRole]] = comment["link"].toString();
    it[commentRoleNames[CommentEntry::UserIdRole]] = comment["user_id"].toString();
    it[commentRoleNames[CommentEntry::ContentRole]] = comment["content"].toString();
    it[commentRoleNames[CommentEntry::ContentPreviewRole]] = comment["content"].toString().left(200);
    it[commentRoleNames[CommentEntry::PostIdRole]] = comment["post_id"].toString();
    it[commentRoleNames[CommentEntry::PostTitleRole]] = comment["post_title"];
    it[commentRoleNames[CommentEntry::AuthorRole]] = comment["author"].toString();
    it[commentRoleNames[CommentEntry::AuthorUrlRole]] = comment["author_url"];
    it[commentRoleNames[CommentEntry::AuthorEmailRole]] = comment["author_email"];
    it[commentRoleNames[CommentEntry::AuthorIpRole]] = comment["author_ip"];
    it[commentRoleNames[CommentEntry::StatusRole]] = comment["status"];
    it[commentRoleNames[CommentEntry::GravatarUrlRole]] = "http://www.gravatar.com/avatar/"+
            QString(QCryptographicHash::hash(comment["author_email"].toString().toUtf8(),
                                             QCryptographicHash::Md5 ).toHex())+
            "?s=100&d=mm";
    QDateTime d = QDateTime::fromString(comment["date_created_gmt"].toString(), "yyyyMMddThh:mm:ss");
    d.setTimeSpec(Qt::UTC);
    d = d.toLocalTime();
    it[commentRoleNames[CommentEntry::DateCreatedRole]] = d.toString("ddd hh:mm AP MMM dd, yyyy");
    it[commentRoleNames[CommentEntry::OrderRole]] = 0;
    it[commentRoleNames[CommentEntry::MarkedRole]] = false;
    for(int i=0;i<model->size();i++) {
        if(model->value(i).toMap().value(commentRoleNames[CommentEntry::IdRole]).toString()==comment["comment_id"].toString()) {
            model->replace(i, it);
            return i;
        }
    }
    model->insertEntry(0, it);
    return -1;
}

void AbstractCPObject::appendMediaItems(RoleItemModel *model, const QVariantList mediaItems)
{
	foreach(QVariant i, mediaItems) {
		QVariantMap mediaItem = i.toMap();
		QVariantMap it;
	    it[mediaRoleNames[MediaEntry::TitleRole]] = mediaItem["title"].toString();
	    it[mediaRoleNames[MediaEntry::DescriptionRole]] = mediaItem["description"].toString();
	    it[mediaRoleNames[MediaEntry::CaptionRole]] = mediaItem["caption"].toString();
	    it[mediaRoleNames[MediaEntry::LinkRole]] = mediaItem["link"].toString();
	    if(mediaItem["thumbnail"].toString().endsWith(".jpg")||mediaItem["thumbnail"].toString().endsWith(".png"))
	    	it[mediaRoleNames[MediaEntry::ThumbnailRole]] = mediaItem["thumbnail"].toString()+"?w=150";
	    else
	    	it[mediaRoleNames[MediaEntry::ThumbnailRole]] = mediaItem["thumbnail"].toString();
	    it[mediaRoleNames[MediaEntry::MetaDataRole]] = mediaItem["metadata"].toString();
	    it[mediaRoleNames[MediaEntry::ParentRole]] = mediaItem["id"].toString();
	    it[mediaRoleNames[MediaEntry::FileTypeRole]] = mediaItem["link"].toString().split(".").last().toLower();
	    QDateTime d = QDateTime::fromString(mediaItem["date_created_gmt"].toString(), "yyyyMMddThh:mm:ss");
        d.setTimeSpec(Qt::UTC);
        d = d.toLocalTime();
	    it[mediaRoleNames[MediaEntry::DateCreatedRole]] = d;
        it[mediaRoleNames[MediaEntry::DisplayDateRole]] = d.toString("MMM dd, yyyy");
	    it[mediaRoleNames[MediaEntry::ImageWidthRole]] = 0;
	    it[mediaRoleNames[MediaEntry::ImageHeightRole]] = 0;
	    model->addEntry(it);
		//qDebug()<<"AbstractCPObject---MediaItem"<<model->size()<<mediaItem["title"].toString()
		//        <<it[mediaRoleNames[MediaEntry::FileTypeRole]].toString();
	}
}

int AbstractCPObject::updateMediaItem(RoleItemModel *model, const QVariantMap mediaItem)
{
    QVariantMap it;
    it[mediaRoleNames[MediaEntry::TitleRole]] = mediaItem["title"].toString();
    it[mediaRoleNames[MediaEntry::DescriptionRole]] = mediaItem["description"].toString();
    it[mediaRoleNames[MediaEntry::CaptionRole]] = mediaItem["caption"].toString();
    it[mediaRoleNames[MediaEntry::LinkRole]] = mediaItem["link"].toString();
    if(mediaItem["thumbnail"].toString().endsWith(".jpg")||mediaItem["thumbnail"].toString().endsWith(".png"))
        it[mediaRoleNames[MediaEntry::ThumbnailRole]] = mediaItem["thumbnail"].toString()+"?w=150";
    else
        it[mediaRoleNames[MediaEntry::ThumbnailRole]] = mediaItem["thumbnail"].toString();
    it[mediaRoleNames[MediaEntry::MetaDataRole]] = mediaItem["metadata"].toString();
    it[mediaRoleNames[MediaEntry::ParentRole]] = mediaItem["id"].toString();
    it[mediaRoleNames[MediaEntry::FileTypeRole]] = mediaItem["link"].toString().split(".").last().toLower();
    QDateTime d = QDateTime::fromString(mediaItem["date_created_gmt"].toString(), "yyyyMMddThh:mm:ss");
    d.setTimeSpec(Qt::UTC);
    d = d.toLocalTime();
    it[mediaRoleNames[MediaEntry::DateCreatedRole]] = d;
    it[mediaRoleNames[MediaEntry::DisplayDateRole]] = d.toString("MMM dd, yyyy");
    it[mediaRoleNames[MediaEntry::ImageWidthRole]] = 0;
    it[mediaRoleNames[MediaEntry::ImageHeightRole]] = 0;
    for(int i=0;i<model->size();i++) {
        if(model->value(i).toMap().value(mediaRoleNames[MediaEntry::LinkRole]).toString()==mediaItem["link"].toString()) {
            model->replace(i, it);
            return i;
        }
    }
    model->insertEntry(0, it);
    return -1;
}

void AbstractCPObject::appendCategories(RoleItemModel *model, const QVariantList categories)
{
	foreach(QVariant i, categories) {
		QVariantMap category = i.toMap();
		QVariantMap it;
		it[categoryRoleNames[CategoryEntry::IdRole]] = category["categoryId"].toString();
		it[categoryRoleNames[CategoryEntry::DescriptionRole]] = category["categoryDescription"].toString();
		it[categoryRoleNames[CategoryEntry::CategoryNameRole]] = category["categoryName"].toString();
		it[categoryRoleNames[CategoryEntry::ParentIdRole]] = category["parentId"].toString();
		it[categoryRoleNames[CategoryEntry::HtmlUrlRole]] = category["html_url"].toString();
		it[categoryRoleNames[CategoryEntry::RssUrlRole]] = category["rss_url"].toString();
		it[categoryRoleNames[CategoryEntry::MarkedRole]] = false;
		model->addEntry(it);
		//qDebug()<<"AbstractCPObject---Category"<<category["categoryName"].toString();
	}
}

void AbstractCPObject::appendTags(RoleItemModel *model, const QVariantList tags)
{
	foreach(QVariant i, tags) {
		QVariantMap tag = i.toMap();
		QVariantMap it;
	    it[tagRoleNames[TagEntry::IdRole]] = tag["tag_id"].toString();
	    it[tagRoleNames[TagEntry::NameRole]] = tag["name"].toString();
	    it[tagRoleNames[TagEntry::SlugRole]] = tag["slug"].toString();
	    it[tagRoleNames[TagEntry::MarkedRole]] = false;
	    it[tagRoleNames[TagEntry::HtmlUrlRole]] = tag["html_url"].toString();
	    it[tagRoleNames[TagEntry::RssUrlRole]] = tag["rss_url"].toString();
	    it[tagRoleNames[TagEntry::CountRole]] = tag["count"].toString();
	    model->addEntry(it);
		//qDebug()<<"AbstractCPObject---Tag"<<tag["tag_id"].toString()<<tag["name"].toString();
	}
}

void AbstractCPObject::deletePostInModel(RoleItemModel *model, const QString postId)
{
	if(!model || !model->list.contains(postId)) return;
	for(int i=0;i<model->size();i++) {
		if(model->value(i).toMap().value(postRoleNames[PostEntry::IdRole]).toString()==postId) {
			model->removeAt(i);
			return;
		}
	}
}

void AbstractCPObject::deletePageInModel(RoleItemModel *model, const QString pageId)
{
	if(!model || !model->list.contains(pageId)) return;
	for(int i=0;i<model->size();i++) {
		if(model->value(i).toMap().value(pageRoleNames[PageEntry::IdRole]).toString()==pageId) {
			model->removeAt(i);
			return;
		}
	}
}

void AbstractCPObject::deleteCategoryInModel(RoleItemModel *model, const QString categoryId)
{
	if(!model || !model->list.contains(categoryId)) return;
	for(int i=0;i<model->size();i++) {
		if(model->value(i).toMap().value(categoryRoleNames[CategoryEntry::IdRole]).toString()==categoryId) {
			model->removeAt(i);
			return;
		}
	}
}

QString AbstractCPObject::getHtmlTextSnippet(const QString txt)
{
	QString s = txt;
	return s.remove(QRegExp("<[^>]*>")).trimmed();
}

QString AbstractCPObject::localFilePath(QString link)
{
    if(link.startsWith("file://")) {
        return QUrl(link).path();
    } else
        return link;
}
