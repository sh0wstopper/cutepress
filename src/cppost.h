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

#ifndef CPPOST_H_
#define CPPOST_H_

#include "common.h"
#include "abstractcpobject.h"

/** Abstract CutePress Post. */
class CPPost: public AbstractCPObject {
    Q_OBJECT

    Q_PROPERTY(QString debugText READ debugText NOTIFY debugTextChanged)
	Q_PROPERTY(QString cpId READ cpId WRITE setCpId NOTIFY cpIdChanged)
    Q_PROPERTY(QString authorId READ authorId NOTIFY authorIdChanged)
    Q_PROPERTY(QString authorDisplayName READ authorDisplayName NOTIFY authorDisplayNameChanged)
    Q_PROPERTY(QDateTime dateCreated READ dateCreated NOTIFY dateCreatedChanged)
    Q_PROPERTY(QString displayDate READ displayDate NOTIFY dateCreatedChanged)
    Q_PROPERTY(QString modified READ modified NOTIFY modifiedChanged)
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(QString url READ url NOTIFY urlChanged)
    Q_PROPERTY(QString description READ description NOTIFY descriptionChanged)
    Q_PROPERTY(QString descriptionForHtml READ descriptionForHtml NOTIFY descriptionChanged)
    Q_PROPERTY(QString descriptionSnippet READ descriptionSnippet NOTIFY descriptionChanged)
    Q_PROPERTY(QString excerpt READ excerpt NOTIFY excerptChanged)
    Q_PROPERTY(QString slug READ slug NOTIFY slugChanged)
    Q_PROPERTY(QString status READ status NOTIFY statusChanged)
    Q_PROPERTY(QString displayStatus READ displayStatus NOTIFY statusChanged)
    Q_PROPERTY(QString password READ password NOTIFY passwordChanged)
	Q_PROPERTY(bool commentsOpen READ commentsOpen NOTIFY commentsOpenChanged)
	Q_PROPERTY(bool pingsOpen READ pingsOpen NOTIFY pingsOpenChanged)
	Q_PROPERTY(int commentsCount READ commentsCount NOTIFY commentsCountChanged)
    Q_PROPERTY(QStringList tags READ tags NOTIFY tagsChanged)
    Q_PROPERTY(QString tagsAsString READ tagsAsString NOTIFY tagsChanged)
    Q_PROPERTY(QStringList categories READ categories NOTIFY categoriesChanged)
    Q_PROPERTY(QString categoriesAsString READ categoriesAsString NOTIFY categoriesChanged)
    Q_PROPERTY(int infoState READ infoState NOTIFY infoStateChanged)
    Q_PROPERTY(QString infoStatus READ infoStatus NOTIFY infoStatusChanged)

    Q_PROPERTY(RoleItemModel* comments READ comments NOTIFY commentsChanged)
    Q_PROPERTY(int commentsState READ commentsState NOTIFY commentsStateChanged)
    Q_PROPERTY(QString commentsStatus READ commentsStatus NOTIFY commentsStatusChanged)
    Q_PROPERTY(int addCommentState READ addCommentState NOTIFY addCommentStateChanged)
    Q_PROPERTY(QString addCommentStatus READ addCommentStatus NOTIFY addCommentStatusChanged)
    Q_PROPERTY(QString newCommentId READ newCommentId NOTIFY newCommentIdChanged)
public:
    /** Default constructor. */
    CPPost(QObject *parent = 0);

    /** Destructor. */
    ~CPPost();

    QString debugText() { return _debugText; }
	QString cpId() { return _cpId; }
	QString authorId() { return _authorId; }
	QString authorDisplayName() { return _authorDisplayName; }
    QDateTime dateCreated() { return _dateCreated; }
	QString displayDate() { return _dateCreated.toString("ddd hh:mm AP MMM dd, yyyy"); }
	QString modified() { return _modified.toString("ddd hh:mm AP MMM dd, yyyy"); }
    QString title() { return _title; }
    QString url() { return _url; }
    QString description() { return _description; }
    QString descriptionForHtml() {
		QString contentForHtml = _description;
		contentForHtml = contentForHtml.remove("width=").remove("height=");
		return contentForHtml.replace("\n", "<br/>");
	}
    QString descriptionSnippet() { return getHtmlTextSnippet(_description); }
    QString excerpt() { return _excerpt; }
    QString slug() { return _slug; }
    QString status() { return _status; }
    QString displayStatus() {
    	if(_dateCreated>QDateTime::currentDateTime())
    		return "future";
    	else
    		return _status;
    }
    QString password() { return _password; }
    bool commentsOpen() { return _commentsOpen; }
    bool pingsOpen() { return _pingsOpen; }
    int commentsCount() { return _commentsCount; }
    QString tagsAsString();
    QString categoriesAsString();
    QStringList tags() { return _tags; }
    QStringList categories() { return _categories; }

    int infoState() { return _infoState; }
    QString infoStatus() { return _infoStatus; }

    RoleItemModel* comments() { return _commentsModel; }
    int commentsState() { return _commentsState; }
    QString commentsStatus() { return _commentsStatus; }
    int addCommentState() { return _addCommentState; }
    QString addCommentStatus() { return _addCommentStatus; }
    QString newCommentId() { return _newCommentId; }


    void setDebugText(const QString debugText) { _debugText = debugText; emit debugTextChanged(); }
    void setCpId(const QString cpId) {
		if(_cpId!=cpId) {
			_cpId = cpId;
			emit cpIdChanged();
		}
	}
	void setAuthorId(const QString authorId) { _authorId = authorId; emit authorIdChanged(); }
	void setAuthorDisplayName(const QString authorDisplayName) { _authorDisplayName = authorDisplayName; emit authorDisplayNameChanged(); }
	void setDateCreated(const QDateTime dateCreated) { _dateCreated = dateCreated; emit dateCreatedChanged(); }
	void setModified(const QDateTime modified) { _modified = modified; emit modifiedChanged(); }
	void setTitle(const QString title) { _title = title; emit titleChanged(); }
	void setUrl(const QString url) { _url = url; emit urlChanged(); }
	void setDescription(const QString description) { _description = description; emit descriptionChanged(); }
	void setExcerpt(const QString excerpt) { _excerpt = excerpt; emit excerptChanged(); }
	void setSlug(const QString slug) { _slug = slug; emit slugChanged(); }
	void setStatus(const QString status) { _status = status; emit statusChanged(); }
	void setPassword(const QString password) { _password = password; emit passwordChanged(); }
	void setCommentsOpen(const bool commentsOpen) { _commentsOpen = commentsOpen; emit commentsOpenChanged(); }
	void setPingsOpen(const bool pingsOpen) { _pingsOpen = pingsOpen; emit pingsOpenChanged(); }
	void setCommentsCount(const int commentsCount) { _commentsCount = commentsCount; emit commentsCountChanged(); }
    void setInfoState(const int infoState) { _infoState = infoState; emit infoStateChanged(); }
    void setInfoStatus(const QString infoStatus) { _infoStatus = infoStatus; emit infoStatusChanged(); }

    void setCommentsState(const int commentsState) { _commentsState = commentsState; emit commentsStateChanged(); }
    void setCommentsStatus(const QString commentsStatus) { _commentsStatus = commentsStatus; emit commentsStatusChanged(); }
    void setAddCommentState(const int addCommentState) { _addCommentState = addCommentState; emit addCommentStateChanged(); }
    void setAddCommentStatus(const QString addCommentStatus) { _addCommentStatus = addCommentStatus; emit addCommentStatusChanged(); }
    void setNewCommentId(const QString newCommentId) { _newCommentId = newCommentId; emit newCommentIdChanged(); }

public slots:
	void clear();
	void setInfo(RoleItemModel* model, const int index);
	void setInfo(const QVariantMap info);
	void fetchInfo();
	void fetchComments();
	void addComment(const QString body,
	        const QString parentId = QString());
    void requestError(const int,const int,const QString);
    void requestFinished(const int, const QVariant &result);
    void taskStarted(const int op);
    void taskFinished(const int op);
    void taskFailed(const int op, const QString msg);

signals:
    void debugTextChanged();
	void cpIdChanged();
	void localIdChanged();
    void descriptionChanged();
    void titleChanged();
    void urlChanged();
    void excerptChanged();
    void slugChanged();
    void statusChanged();
    void commentsOpenChanged();
    void pingsOpenChanged();
    void commentsCountChanged();
    void authorIdChanged();
    void authorDisplayNameChanged();
    void passwordChanged();
    void tagsChanged();
    void categoriesChanged();
    void dateCreatedChanged();
    void modifiedChanged();

    void infoStateChanged();
    void infoStatusChanged();

    void commentsChanged();
    void commentsStateChanged();
    void commentsStatusChanged();
    void addCommentStateChanged();
    void addCommentStatusChanged();
    void newCommentIdChanged();

    void postRefreshed(QVariantMap newPost);

protected:
	QString _cpId;
	QString _localId;
	QString _description;
    QString _title;
    QString _url;
    QString _excerpt;
    QString _slug;
    QString _status;
    bool _commentsOpen;
    bool _pingsOpen;
    int _commentsCount;
	QString _authorId;
	QString _authorDisplayName;
    QString _password;
    QStringList _tags;
    QStringList _categories;
    QDateTime _dateCreated;
	QDateTime _modified;

    int _infoState;
    QString _infoStatus;

    RoleItemModel *_commentsModel;
    int _commentsState;
    QString _commentsStatus;
    int _addCommentState;
    QString _addCommentStatus;
    QString _newCommentId;

    QString _debugText;
};
#endif /* CPPOST_H_ */
