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

#ifndef CPPAGE_H
#define CPPAGE_H

#include "abstractCPObject.h"

/** A cutepress page item. */
class CPPage: public AbstractCPObject {
    Q_OBJECT

    Q_PROPERTY(QString description READ description NOTIFY descriptionChanged)
    Q_PROPERTY(QString descriptionHtml READ descriptionHtml NOTIFY descriptionChanged)
    Q_PROPERTY(QString descriptionSnippet READ descriptionSnippet NOTIFY descriptionChanged)
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(QString link READ link NOTIFY linkChanged)
    Q_PROPERTY(QString permaLink READ permaLink NOTIFY permaLinkChanged)
    Q_PROPERTY(QString userId READ userId NOTIFY userIdChanged)
    Q_PROPERTY(QString mtExcerpt READ mtExcerpt NOTIFY mtExcerptChanged)
    Q_PROPERTY(QString mtTextMore READ mtTextMore NOTIFY mtTextMoreChanged)
    Q_PROPERTY(QString mtAllowComments READ mtAllowComments NOTIFY mtAllowCommentsChanged)
    Q_PROPERTY(QString mtAllowPings READ mtAllowPings NOTIFY mtAllowPingsChanged)
    Q_PROPERTY(QString wpSlug READ wpSlug NOTIFY wpSlugChanged)
    Q_PROPERTY(QString wpPassword READ wpPassword NOTIFY wpPasswordChanged)
    Q_PROPERTY(QString wpAuthorId READ wpAuthorId NOTIFY wpAuthorIdChanged)
    Q_PROPERTY(QString wpAuthorDisplayName READ wpAuthorDisplayName NOTIFY wpAuthorDisplayNameChanged)
    Q_PROPERTY(QString wpPageParentTitle READ wpPageParentTitle NOTIFY wpPageParentTitleChanged)
    Q_PROPERTY(QString wpPageTemplate READ wpPageTemplate NOTIFY wpPageTemplateChanged)
    Q_PROPERTY(QString pageParentId READ pageParentId NOTIFY pageParentIdChanged)
    Q_PROPERTY(QString wpPageOrder READ wpPageOrder NOTIFY wpPageOrderChanged)

    Q_PROPERTY(QString cpId READ cpId WRITE setCpId NOTIFY cpIdChanged)
    Q_PROPERTY(QString status READ status NOTIFY statusChanged)
    Q_PROPERTY(QString displayStatus READ displayStatus NOTIFY displayStatusChanged)
    Q_PROPERTY(QString localId READ localId NOTIFY localIdChanged)
    Q_PROPERTY(bool dirty READ dirty NOTIFY dirtyChanged)
    Q_PROPERTY(bool deleted READ deleted NOTIFY deletedChanged)
    Q_PROPERTY(bool error READ error NOTIFY errorChanged)
    Q_PROPERTY(QDateTime dateCreated READ dateCreated NOTIFY dateCreatedChanged)
    Q_PROPERTY(QString displayDate READ displayDate NOTIFY dateCreatedChanged)
    Q_PROPERTY(QString pageDate READ pageDate NOTIFY dateCreatedChanged)
    Q_PROPERTY(QString pageTime READ pageTime NOTIFY dateCreatedChanged)

    Q_PROPERTY(int infoState READ infoState NOTIFY infoStateChanged)
    Q_PROPERTY(QString infoStatus READ infoStatus NOTIFY infoStatusChanged)

public:
    /** Default constructor. */
   CPPage(QObject *parent = 0);

    /** Destructor. */
    ~CPPage();

    RoleItemModel *commentsModel;

    Q_INVOKABLE void clear();

    QString description() {return iDescription;}
    QString descriptionHtml();
    QString descriptionSnippet() { return getHtmlTextSnippet(iDescription); }
    QString title() {return iTitle;}
    QString link() {return iLink;}
    QString permaLink() {return iPermaLink;}
    QString userId() {return iUserId;}
    QString mtExcerpt() {return iMtExcerpt;}
    QString mtTextMore() {return iMtTextMore;}
    QString mtAllowComments() {return iMtAllowComments;}
    QString mtAllowPings() {return iMtAllowPings;}
    QString wpSlug() {return iWpSlug;}
    QString wpPassword() {return iWpPassword;}
    QString wpAuthorId() {return iWpAuthorId;}
    QString wpAuthorDisplayName() {return iWpAuthorDisplayName;}
    QString wpPageParentTitle() {return iWpPageParentTitle;}
    QString wpPageTemplate() {return iWpPageTemplate;}
    QString pageParentId() {return iPageParentId;}
    QString wpPageOrder() {return iWpPageOrder;}

    QString cpId() {return _cpId;}
    QString status() {return iStatus;}
    QString localId() {return iLocalId;}
    bool dirty() {return iDirty;}
    bool deleted() {return iDeleted;}
    bool error() {return iError;}
    QDateTime dateCreated() {return iDateCreated;}
    QString displayDate() {return iDateCreated.toString("ddd, dd-MMM-yyyy hh:mm AP");}
    QString pageDate() {return iDateCreated.toString("yyyy/M/d");}
    QString pageTime() {return iDateCreated.toString("h:m:s");}
    QString displayStatus();

    int infoState() { return _infoState; }
    QString infoStatus() { return _infoStatus; }

    void setDescription(const QString description) {iDescription = description; emit descriptionChanged();}
    void setTitle(const QString title) {iTitle = title; emit titleChanged();}
    void setLink(const QString link) {iLink = link; emit linkChanged();}
    void setPermaLink(const QString permaLink) {iPermaLink = permaLink; emit permaLinkChanged();}
    void setUserId(const QString userId) {iUserId = userId; emit userIdChanged();}
    void setMtExcerpt(const QString mtExcerpt) {iMtExcerpt = mtExcerpt; emit mtExcerptChanged();}
    void setMtTextMore(const QString mtTextMore) {iMtTextMore = mtTextMore; emit mtTextMoreChanged();}
    void setMtAllowComments(const QString mtAllowComments) {iMtAllowComments = mtAllowComments; emit mtAllowCommentsChanged();}
    void setMtAllowPings(const QString mtAllowPings) {iMtAllowPings = mtAllowPings; emit mtAllowPingsChanged();}
    void setWpSlug(const QString wpSlug) {iWpSlug = wpSlug; emit wpSlugChanged();}
    void setWpPassword(const QString wpPassword) {iWpPassword = wpPassword; emit wpPasswordChanged();}
    void setWpAuthor(const QString wpAuthor) {iWpAuthor = wpAuthor; emit wpAuthorChanged();}
    void setWpAuthorId(const QString wpAuthorId) {iWpAuthorId = wpAuthorId; emit wpAuthorIdChanged();}
    void setWpAuthorDisplayName(const QString wpAuthorDisplayName) {iWpAuthorDisplayName = wpAuthorDisplayName; emit wpAuthorDisplayNameChanged();}
    void setWpPageParentTitle(const QString wpPageParentTitle) {iWpPageParentTitle = wpPageParentTitle; emit wpPageParentTitleChanged();}
    void setWpPageTemplate(const QString wpPageTemplate) {iWpPageTemplate = wpPageTemplate; emit wpPageTemplateChanged();}
    void setPageParentId(const QString pageParentId) {iPageParentId = pageParentId; emit pageParentIdChanged();}
    void setWpPageOrder(const QString wpPageOrder) {iWpPageOrder = wpPageOrder; emit wpPageOrderChanged();}

    void setCpId(const QString cpId) {
        if(_cpId!=cpId) {
            _cpId = cpId;
            emit cpIdChanged();
        }
    }
    void setStatus(const QString status) {iStatus = status; emit statusChanged(); emit displayStatusChanged();}
    void setLocalId(const QString localId) {iLocalId = localId; emit localIdChanged();}
    void setDirty(const bool dirty) {iDirty = dirty; emit dirtyChanged();}
    void setDeleted(const bool deleted) {iDeleted = deleted; emit deletedChanged();}
    void setError(const bool error) {iError = error; emit errorChanged();}
    void setDateCreated(const QDateTime dateCreated) {iDateCreated = dateCreated; emit dateCreatedChanged();}

    void setInfoState(const int infoState) { _infoState = infoState; emit infoStateChanged(); }
    void setInfoStatus(const QString infoStatus) { _infoStatus = infoStatus; emit infoStatusChanged(); }

public slots:
    void setInfo(RoleItemModel* model, const int index);
    void setInfo(const QVariantMap info);
    void fetchInfo();
    void requestError(const int,const int,const QString);
    void requestFinished(const int, const QVariant &result);
    void taskStarted(const int op);
    void taskFinished(const int op);
    void taskFailed(const int op, const QString msg);

signals:
    void descriptionChanged();
    void titleChanged();
    void linkChanged();
    void permaLinkChanged();
    void userIdChanged();
    void mtExcerptChanged();
    void mtTextMoreChanged();
    void mtAllowCommentsChanged();
    void mtAllowPingsChanged();
    void wpSlugChanged();
    void wpPasswordChanged();
    void wpAuthorChanged();
    void wpAuthorIdChanged();
    void wpAuthorDisplayNameChanged();
    void wpPageParentTitleChanged();
    void wpPageTemplateChanged();
    void pageParentIdChanged();
    void wpPageOrderChanged();

    void cpIdChanged();
    void statusChanged();
    void localIdChanged();
    void dirtyChanged();
    void deletedChanged();
    void errorChanged();
    void dateCreatedChanged();

    void displayStatusChanged();

    void infoStateChanged();
    void infoStatusChanged();

    void pageRefreshed(QVariantMap newPage);


public:
    QString iDescription;
    QString iTitle;
    QString iLink;
    QString iPermaLink;
    QString iUserId;
    QString iMtExcerpt;
    QString iMtTextMore;
    QString iMtAllowComments;
    QString iMtAllowPings;
    QString iWpSlug;
    QString iWpPassword;
    QString iWpAuthorId;
    QString iWpAuthor;
    QString iWpAuthorDisplayName;
    QString iWpPageParentTitle;
    QString iWpPageTemplate;
    QString iPageParentId;
    QString iWpPageOrder;

    QString _cpId;
    QString iStatus;
    QString iLocalId;
    bool iDirty;
    bool iDeleted;
    bool iError;
    QDateTime iDateCreated;

    int _infoState;
    QString _infoStatus;
};
#endif // CPPAGE_H
