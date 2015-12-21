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

#ifndef CPUTIL_H
#define CPUTIL_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtXml/QDomNode>
#include <QtXml/QXmlStreamWriter>
#include <QCryptographicHash>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QFileInfo>
#include <QDebug>
#include "common.h"
#include "roleitemmodel.h"
#include "cpaction.h"
#include "abstractcpobject.h"

class CPUtil: public AbstractCPObject {
    Q_OBJECT
    Q_PROPERTY(QString debugText READ debugText NOTIFY debugTextChanged)
    Q_PROPERTY(RoleItemModel* selectBlogs READ selectBlogs NOTIFY selectBlogsChanged)
    Q_PROPERTY(RoleItemModel* blogs READ blogs NOTIFY blogsChanged)
    Q_PROPERTY(int blogAdditionState READ blogAdditionState NOTIFY blogAdditionStateChanged)
    Q_PROPERTY(QString blogAdditionStatus READ blogAdditionStatus NOTIFY blogAdditionStatusChanged)
    Q_PROPERTY(RoleItemModel* posts READ posts NOTIFY postsChanged)
    Q_PROPERTY(int postsState READ postsState NOTIFY postsStateChanged)
    Q_PROPERTY(QString postsStatus READ postsStatus NOTIFY postsStatusChanged)
    Q_PROPERTY(int postEditionState READ postEditionState NOTIFY postEditionStateChanged)
    Q_PROPERTY(QString postEditionStatus READ postEditionStatus NOTIFY postEditionStatusChanged)
    Q_PROPERTY(RoleItemModel* pages READ pages NOTIFY pagesChanged)
    Q_PROPERTY(int pagesState READ pagesState NOTIFY pagesStateChanged)
    Q_PROPERTY(QString pagesStatus READ pagesStatus NOTIFY pagesStatusChanged)
    Q_PROPERTY(int pageEditionState READ pageEditionState NOTIFY pageEditionStateChanged)
    Q_PROPERTY(QString pageEditionStatus READ pageEditionStatus NOTIFY pageEditionStatusChanged)
    Q_PROPERTY(RoleItemModel* comments READ comments NOTIFY commentsChanged)
    Q_PROPERTY(int commentsState READ commentsState NOTIFY commentsStateChanged)
    Q_PROPERTY(QString commentsStatus READ commentsStatus NOTIFY commentsStatusChanged)
    Q_PROPERTY(RoleItemModel* mediaItems READ mediaItems NOTIFY mediaItemsChanged)
    Q_PROPERTY(int mediaItemsState READ mediaItemsState NOTIFY mediaItemsStateChanged)
    Q_PROPERTY(QString mediaItemsStatus READ mediaItemsStatus NOTIFY mediaItemsStatusChanged)
    Q_PROPERTY(RoleItemModel* categories READ categories NOTIFY categoriesChanged)
    Q_PROPERTY(int categoriesState READ categoriesState NOTIFY categoriesStateChanged)
    Q_PROPERTY(QString categoriesStatus READ categoriesStatus NOTIFY categoriesStatusChanged)
    Q_PROPERTY(int categoryEditionState READ categoryEditionState NOTIFY categoryEditionStateChanged)
    Q_PROPERTY(QString categoryEditionStatus READ categoryEditionStatus NOTIFY categoryEditionStatusChanged)
    Q_PROPERTY(RoleItemModel* tags READ tags NOTIFY tagsChanged)
    Q_PROPERTY(int tagsState READ tagsState NOTIFY tagsStateChanged)
    Q_PROPERTY(QString tagsStatus READ tagsStatus NOTIFY tagsStatusChanged)
    Q_PROPERTY(int mediaUploadState READ mediaUploadState NOTIFY mediaUploadStateChanged)
    Q_PROPERTY(QString mediaUploadStatus READ mediaUploadStatus NOTIFY mediaUploadStatusChanged)
    Q_PROPERTY(int editorImageUploadState READ editorImageUploadState NOTIFY editorImageUploadStateChanged)
    Q_PROPERTY(QString editorImageUploadStatus READ editorImageUploadStatus NOTIFY editorImageUploadStatusChanged)
    Q_PROPERTY(QString editorUploadImageUrl READ editorUploadImageUrl NOTIFY editorUploadImageUrlChanged)
    Q_PROPERTY(QString editorUploadedImageUrl READ editorUploadedImageUrl NOTIFY editorUploadedImageUrlChanged)
    Q_PROPERTY(QStringList editorUploadImages READ editorUploadImages NOTIFY editorUploadImagesChanged)
    Q_PROPERTY(QString editorType READ editorType WRITE setEditorType NOTIFY editorTypeChanged)

    Q_PROPERTY(QString lastCreatedPageId READ lastCreatedPageId NOTIFY lastCreatedPageIdChanged)
    Q_PROPERTY(QString lastDeletedPageId READ lastDeletedPageId NOTIFY lastDeletedPageIdChanged)
    Q_PROPERTY(QString lastCreatedPostId READ lastCreatedPostId NOTIFY lastCreatedPostIdChanged)
    Q_PROPERTY(QString lastDeletedPostId READ lastDeletedPostId NOTIFY lastDeletedPostIdChanged)
    Q_PROPERTY(QString lastDeletedCommentId READ lastDeletedCommentId NOTIFY lastDeletedCommentIdChanged)
    Q_PROPERTY(QString lastCreatedCategoryId READ lastCreatedCategoryId NOTIFY lastCreatedCategoryIdChanged)
    Q_PROPERTY(QString lastDeletedCategoryId READ lastDeletedCategoryId NOTIFY lastDeletedCategoryIdChanged)
    Q_PROPERTY(QString lastApprovedCommentId READ lastApprovedCommentId NOTIFY lastApprovedCommentIdChanged)
    Q_PROPERTY(QString lastUnapprovedCommentId READ lastUnapprovedCommentId NOTIFY lastUnapprovedCommentIdChanged)
    Q_PROPERTY(QString lastSpammedCommentId READ lastSpammedCommentId NOTIFY lastSpammedCommentIdChanged)
    Q_PROPERTY(QString lastCreatedMediaId READ lastCreatedMediaId NOTIFY lastCreatedMediaIdChanged)


public:
    CPUtil(QObject *parent = 0);

    ~CPUtil();

    void clear();
    void clearBlogData();

    QString debugText() { return _debugText; }
    RoleItemModel* blogs() { return _blogsModel; }
    RoleItemModel* selectBlogs() { return _selectBlogsModel; }
    RoleItemModel* posts() { return _postsModel; }
    RoleItemModel* pages() { return _pagesModel; }
    RoleItemModel* comments() { return _commentsModel; }
    RoleItemModel* mediaItems() { return _mediaItemsModel; }
    RoleItemModel* tags() { return _tagsModel; }
    RoleItemModel* categories() { return _categoriesModel; }
    int blogAdditionState() { return _blogAdditionState; }
    QString blogAdditionStatus() { return _blogAdditionStatus; }
    int postsState() { return _postsState; }
    QString postsStatus() { return _postsStatus; }
    int postEditionState() { return _postEditionState; }
    QString postEditionStatus() { return _postEditionStatus; }
    int pagesState() { return _pagesState; }
    QString pagesStatus() { return _pagesStatus; }
    int pageEditionState() { return _pageEditionState; }
    QString pageEditionStatus() { return _pageEditionStatus; }
    int commentsState() { return _commentsState; }
    QString commentsStatus() { return _commentsStatus; }
    int mediaItemsState() { return _mediaItemsState; }
    QString mediaItemsStatus() { return _mediaItemsStatus; }
    int categoriesState() { return _categoriesState; }
    QString categoriesStatus() { return _categoriesStatus; }
    int categoryEditionState() { return _categoryEditionState; }
    QString categoryEditionStatus() { return _categoryEditionStatus; }
    int tagsState() { return _tagsState; }
    QString tagsStatus() { return _tagsStatus; }
    int mediaUploadState() { return _mediaUploadState; }
    QString mediaUploadStatus() { return _mediaUploadStatus; }
    int editorImageUploadState() { return _editorImageUploadState; }
    QString editorImageUploadStatus() { return _editorImageUploadStatus; }
    QString editorUploadImageUrl() { return _editorUploadImageUrl; }
    QString editorUploadedImageUrl() { return _editorUploadedImageUrl; }
    QStringList editorUploadImages() { return _editorUploadImages; }
    QString editorType() { return _editorType; }

    QString lastCreatedPageId() { return _lastCreatedPageId; }
    QString lastDeletedPageId() { return _lastDeletedPageId; }
    QString lastCreatedPostId() { return _lastCreatedPostId; }
    QString lastDeletedPostId() { return _lastDeletedPostId; }
    QString lastDeletedCommentId() { return _lastDeletedCommentId; }
    QString lastCreatedCategoryId() { return _lastCreatedCategoryId; }
    QString lastDeletedCategoryId() { return _lastDeletedCategoryId; }
    QString lastApprovedCommentId() { return _lastApprovedCommentId; }
    QString lastUnapprovedCommentId() { return _lastUnapprovedCommentId; }
    QString lastSpammedCommentId() { return _lastSpammedCommentId; }
    QString lastCreatedMediaId() { return _lastCreatedMediaId; }

    void setDebugText(const QString debugText) { _debugText = debugText; emit debugTextChanged(); }
    void setBlogAdditionState(const int blogAdditionState) { _blogAdditionState = blogAdditionState; emit blogAdditionStateChanged(); }
    void setBlogAdditionStatus(const QString blogAdditionStatus) { _blogAdditionStatus = blogAdditionStatus; emit blogAdditionStatusChanged(); }
    void setPostsState(const int postsState) { _postsState = postsState; emit postsStateChanged(); }
    void setPostsStatus(const QString postsStatus) { _postsStatus = postsStatus; emit postsStatusChanged(); }
    void setPostEditionState(const int postEditionState) { _postEditionState = postEditionState; emit postEditionStateChanged(); }
	void setPostEditionStatus(const QString postEditionStatus) { _postEditionStatus = postEditionStatus; emit postEditionStatusChanged(); }
	void setPagesState(const int pagesState) { _pagesState = pagesState; emit pagesStateChanged(); }
    void setPagesStatus(const QString pagesStatus) { _pagesStatus = pagesStatus; emit pagesStatusChanged(); }
    void setPageEditionState(const int pageEditionState) { _pageEditionState = pageEditionState; emit pageEditionStateChanged(); }
	void setPageEditionStatus(const QString pageEditionStatus) { _pageEditionStatus = pageEditionStatus; emit pageEditionStatusChanged(); }
	void setCommentsState(const int commentsState) { _commentsState = commentsState; emit commentsStateChanged(); }
    void setCommentsStatus(const QString commentsStatus) { _commentsStatus = commentsStatus; emit commentsStatusChanged(); }
    void setMediaItemsState(const int mediaItemsState) { _mediaItemsState = mediaItemsState; emit mediaItemsStateChanged(); }
    void setMediaItemsStatus(const QString mediaItemsStatus) { _mediaItemsStatus = mediaItemsStatus; emit mediaItemsStatusChanged(); }
    void setCategoriesState(const int categoriesState) { _categoriesState = categoriesState; emit categoriesStateChanged(); }
    void setCategoriesStatus(const QString categoriesStatus) { _categoriesStatus = categoriesStatus; emit categoriesStatusChanged(); }
    void setCategoryEditionState(const int categoryEditionState) { _categoryEditionState = categoryEditionState; emit categoryEditionStateChanged(); }
	void setCategoryEditionStatus(const QString categoryEditionStatus) { _categoryEditionStatus = categoryEditionStatus; emit categoryEditionStatusChanged(); }
	void setTagsState(const int tagsState) { _tagsState = tagsState; emit tagsStateChanged(); }
    void setTagsStatus(const QString tagsStatus) { _tagsStatus = tagsStatus; emit tagsStatusChanged(); }
    void setMediaUploadState(const int mediaUploadState) { _mediaUploadState = mediaUploadState; emit mediaUploadStateChanged(); }
	void setMediaUploadStatus(const QString mediaUploadStatus) { _mediaUploadStatus = mediaUploadStatus; emit mediaUploadStatusChanged(); }
	void setEditorImageUploadState(const int editorImageUploadState) { _editorImageUploadState = editorImageUploadState; emit editorImageUploadStateChanged(); }
    void setEditorImageUploadStatus(const QString editorImageUploadStatus) { _editorImageUploadStatus = editorImageUploadStatus; emit editorImageUploadStatusChanged(); }
    void setEditorUploadImageUrl(const QString editorUploadImageUrl) { _editorUploadImageUrl = editorUploadImageUrl; emit editorUploadImageUrlChanged(); }
    void setEditorUploadedImageUrl(const QString editorUploadedImageUrl) { _editorUploadedImageUrl = editorUploadedImageUrl; emit editorUploadedImageUrlChanged(); }
    void setEditorType(const QString editorType) { _editorType = editorType; emit editorTypeChanged(); }

    void setLastCreatedPageId(const QString lastCreatedPageId) { _lastCreatedPageId = lastCreatedPageId; emit lastCreatedPageIdChanged(); }
    void setLastDeletedPageId(const QString lastDeletedPageId) { _lastDeletedPageId = lastDeletedPageId; emit lastDeletedPageIdChanged(); }
    void setLastCreatedPostId(const QString lastCreatedPostId) { _lastCreatedPostId = lastCreatedPostId; emit lastCreatedPostIdChanged(); }
    void setLastDeletedPostId(const QString lastDeletedPostId) { _lastDeletedPostId = lastDeletedPostId; emit lastDeletedPostIdChanged(); }
    void setLastDeletedCommentId(const QString lastDeletedCommentId) { _lastDeletedCommentId = lastDeletedCommentId; emit lastDeletedCommentIdChanged(); }
    void setLastCreatedCategoryId(const QString lastCreatedCategoryId) { _lastCreatedCategoryId = lastCreatedCategoryId; emit lastCreatedCategoryIdChanged(); }
    void setLastDeletedCategoryId(const QString lastDeletedCategoryId) { _lastDeletedCategoryId = lastDeletedCategoryId; emit lastDeletedCategoryIdChanged(); }
    void setLastApprovedCommentId(const QString lastApprovedCommentId) { _lastApprovedCommentId = lastApprovedCommentId; emit lastApprovedCommentIdChanged(); }
	void setLastUnapprovedCommentId(const QString lastUnapprovedCommentId) { _lastUnapprovedCommentId = lastUnapprovedCommentId; emit lastUnapprovedCommentIdChanged(); }
	void setLastSpammedCommentId(const QString lastSpammedCommentId) { _lastSpammedCommentId = lastSpammedCommentId; emit lastSpammedCommentIdChanged(); }
	void setLastCreatedMediaId(const QString lastCreatedMediaId) { _lastCreatedMediaId = lastCreatedMediaId; emit lastCreatedMediaIdChanged(); }

public slots:
    void getBlogs();
    void fetchRecentPosts();
    void fetchPost(const QString postId);
    void fetchPostCommentsCount(const QString postId);
    void fetchPages();
    void fetchPage(const QString pageId);
    void fetchComments();
    void fetchComment(const QString commentId);
    void fetchMediaItems();
    void fetchMediaItem(const QString mediaId);
    void fetchTags();
    void fetchCategories();
    void toggleBlogSelection(const int pos);
    void toggleActiveInSelectedBlogs(const int pos);
    void clearFetchedUserBlogs();
    void addSelectedBlogs();
    void activateBlog(int idx = -1);
    void changeActiveBlog(const int pos);
    void changeActiveBlog(const QString blogUrl);
    void createNewPost(QString dateCreated = "",
                       QString title = "",
                       QString description = "",
                       QString excerpt = "",
                       QString slug = "",
                       QString status = "",
                       QString password = "",
                       QString categories = "",
                       QString tags = "",
                       bool commentsOpen = true,
                       bool pingsOpen = true,
                       bool sticky = false);
    void editPost(const QString postId,
                       QString dateCreated = "",
                       QString title = "",
                       QString description = "",
                       QString excerpt = "",
                       QString slug = "",
                       QString status = "",
                       QString password = "",
                       QString categories = "",
                       QString tags = "",
                       bool commentsOpen = true,
                       bool pingsOpen = true,
                       bool sticky = false);
    void deletePost(const QString postId);
    void deleteLocalPost(const QString postId);
    void saveLocalDraftPost(const QString id = "",
                       QString dateCreated = "",
                       QString title = "",
                       QString description = "",
                       QString excerpt = "",
                       QString slug = "",
                       QString status = "",
                       QString password = "",
                       QString categories = "",
                       QString tags = "",
                       bool commentsOpen = true,
                       bool pingsOpen = true,
                       bool sticky = false);
    void markCategoriesInModel(const QString categoriesString);
    void markCategoryInModel(const int idx);
    void unmarkCategoryInModel(const int idx);
    QString getMarkedCategoriesFromModel();
    void createNewPage(QString dateCreated = "",
                       QString title = "",
                       QString description = "",
                       QString excerpt = "",
                       QString slug = "",
                       QString status = "",
                       QString password = "",
                       bool commentsOpen = true,
                       bool pingsOpen = true,
                       int pageParentId=-1,
                       int pageOrder=-1);
    void editPage(QString pageId,
                  QString dateCreated = "",
                  QString title = "",
                  QString description = "",
                       QString excerpt = "",
                       QString slug = "",
                       QString status = "",
                       QString password = "",
                       bool commentsOpen = true,
                       bool pingsOpen = true,
                       int pageParentId=-1,
                       int pageOrder=-1);
    void deletePage(const QString pageId);
    void deleteLocalPage(const QString pageId);
    void saveLocalDraftPage(const QString id = "",
                            QString dateCreated = "",
                            QString title = "",
                            QString description = "",
                            QString excerpt = "",
                            QString slug = "",
                            QString status = "",
                            QString password = "",
                            bool commentsOpen = true,
                            bool pingsOpen = true,
                            int pageParentId=-1,
                            int pageOrder=-1);
    void approveComment(const QString commentId);
    void unapproveComment(const QString commentId);
    void spamComment(const QString commentId);
    void deleteComment(const QString commentId);
    void createNewCategory(const QString name, const QString slug="", const int parentId=0, const QString description="");
    void deleteCategory(const QString categoryId);
    void uploadFile(const QString filename, QString name, const bool overwrite = false);
    void uploadEditorImage(const QString filename, QString name = "", const bool overwrite = false);
    void removeAllBlogs();
    void removeBlog(const int iIndex);
    void removeBlog(const QString blogUrl);
    void appendEditorUploadImage(const QString image);
    void removeEditorUploadImage(const QString image);
    void clearEditorUploadImages();
    QString getEditorUploadImage() { return _editorUploadImages.first(); }
    int editorUploadImagesCount() { return _editorUploadImages.count(); }
    void clearEditorData();
    void prepareUploadListForSavedItem(const QString content);
    void clearPostEditionData();
    void clearPageEditionData();
    void updatePostInfoFromPostPage(const QString, const QVariantMap);
    void updatePageInfoFromPagePage(const QString, const QVariantMap);
    void fetchCommentCountForAllPosts();

private slots:
	void requestFinished(const int, const QVariant &result);
	void requestError(const int,const int,const QString);
	void taskStarted(const int);
	void taskFinished(const int);
	void taskFailed(const int, const int, const QString);

signals:
	void debugTextChanged();
	void blogsChanged();
	void selectBlogsChanged();
	void postsChanged();
	void pagesChanged();
	void commentsChanged();
	void mediaItemsChanged();
	void tagsChanged();
	void categoriesChanged();
	void blogAdditionStateChanged();
	void blogAdditionStatusChanged();
	void postsStateChanged();
	void postsStatusChanged();
	void postEditionStateChanged();
	void postEditionStatusChanged();
	void pagesStateChanged();
	void pagesStatusChanged();
	void pageEditionStateChanged();
	void pageEditionStatusChanged();
	void commentsStateChanged();
	void commentsStatusChanged();
	void mediaItemsStateChanged();
	void mediaItemsStatusChanged();
	void categoriesStateChanged();
	void categoriesStatusChanged();
	void categoryEditionStateChanged();
	void categoryEditionStatusChanged();
	void tagsStateChanged();
	void tagsStatusChanged();
	void mediaUploadStateChanged();
	void mediaUploadStatusChanged();
    void editorImageUploadStateChanged();
    void editorImageUploadStatusChanged();
    void editorUploadImageUrlChanged();
    void editorUploadedImageUrlChanged();
    void editorUploadImagesChanged();
    void editorTypeChanged();

    void lastCreatedPageIdChanged();
    void lastDeletedPageIdChanged();
    void lastCreatedPostIdChanged();
    void lastDeletedPostIdChanged();
	void lastDeletedCommentIdChanged();
    void lastCreatedCategoryIdChanged();
	void lastDeletedCategoryIdChanged();
	void lastApprovedCommentIdChanged();
	void lastUnapprovedCommentIdChanged();
	void lastSpammedCommentIdChanged();
    void lastCreatedMediaIdChanged();

private:
	void updateBlogsDB();
	void readBlogsFromDB();
    void deleteBlogTablesInDB(const QString sanitizedBlogUrl);
    void createBlogPagesTable();
    void updateBlogPagesDB();
    void insertInBlogPagesDB(QVariantMap);
    void updateInBlogPagesDB(QString, QVariantMap);
    void deleteInBlogPagesDB(QString);
    void readBlogPagesFromDB();
    void createBlogPostsTable();
    void updateBlogPostsDB();
    void insertInBlogPostsDB(QVariantMap);
    void updateInBlogPostsDB(QString, QVariantMap);
    void deleteInBlogPostsDB(QString);
    void readBlogPostsFromDB();
    void createBlogCommentsTable();
    void updateBlogCommentsDB();
    void insertInBlogCommentsDB(QVariantMap);
    void updateInBlogCommentsDB(QString, QVariantMap);
    void deleteInBlogCommentsDB(QString);
    void readBlogCommentsFromDB();
    void createBlogMediaTable();
    void updateBlogMediaDB();
    void insertInBlogMediaDB(QVariantMap);
    void updateInBlogMediaDB(QString, QVariantMap);
    void readBlogMediaFromDB();
    void createBlogCategoriesTable();
    void updateBlogCategoriesDB();
    void insertInBlogCategoriesDB(QVariantMap);
    void deleteInBlogCategoriesDB(QString);
    void readBlogCategoriesFromDB();
    void createBlogTagsTable();
    void updateBlogTagsDB();
    void readBlogTagsFromDB();
    void customClearPagesModel();
    void customClearPostsModel();
    void abortAllRunningRequests();
	QString sanitizedBlogUrl(const QString);
	QString integerValueForBoolean(const bool value);
    QNetworkAccessManager *manager;
    QString _debugText;
    RoleItemModel* _blogsModel;
    RoleItemModel* _selectBlogsModel;
    RoleItemModel* _postsModel;
    RoleItemModel* _pagesModel;
    RoleItemModel* _commentsModel;
    RoleItemModel* _mediaItemsModel;
    RoleItemModel* _categoriesModel;
    RoleItemModel* _tagsModel;

    int _blogAdditionState;
    QString _blogAdditionStatus;
    int _postsState;
    QString _postsStatus;
    int _postEditionState;
    QString _postEditionStatus;
    int _pagesState;
    QString _pagesStatus;
    int _pageEditionState;
    QString _pageEditionStatus;
    int _commentsState;
    QString _commentsStatus;
    int _mediaItemsState;
    QString _mediaItemsStatus;
    int _categoriesState;
    QString _categoriesStatus;
    int _categoryEditionState;
    QString _categoryEditionStatus;
    int _tagsState;
    QString _tagsStatus;
    int _mediaUploadState;
    QString _mediaUploadStatus;
    int _editorImageUploadState;
    QString _editorImageUploadStatus;
    QString _editorUploadImageUrl;
    QString _editorUploadedImageUrl;
    QStringList _editorUploadImages;
    QString _editorType;

    QString _lastCreatedPageId;
    QString _lastDeletedPageId;
    QString _lastCreatedPostId;
    QString _lastDeletedPostId;
    QString _lastDeletedCommentId;
    QString _lastCreatedCategoryId;
    QString _lastDeletedCategoryId;
    QString _lastApprovedCommentId;
    QString _lastUnapprovedCommentId;
    QString _lastSpammedCommentId;
    QString _lastCreatedMediaId;

    QSqlDatabase db;
};

#endif // CPUTIL_H
