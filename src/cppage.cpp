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

#include "cppage.h"

CPPage::CPPage(QObject* parent)
		:AbstractCPObject(parent)
{
    this->clear();
    connect(this,SIGNAL(statusChanged()),SIGNAL(displayStatusChanged()));
    connect(this,SIGNAL(cpIdChanged()),SIGNAL(displayStatusChanged()));
    connect(this,SIGNAL(localIdChanged()),SIGNAL(displayStatusChanged()));
    connect(this,SIGNAL(dirtyChanged()),SIGNAL(displayStatusChanged()));
    connect(this,SIGNAL(dateCreatedChanged()),SIGNAL(displayStatusChanged()));
}

CPPage::~CPPage()
{
}

void CPPage::clear()
{
    setCpId("");
    setDescription("");
    setTitle("");
    setLink("");
    setPermaLink("");
    setUserId("");
    setMtExcerpt("");
    setMtTextMore("");
    setMtAllowComments("");
    setMtAllowPings("");
    setWpSlug("");
    setWpPassword("");
    setWpAuthor("");
    setWpAuthorId("");
    setWpAuthorDisplayName("");
    setWpPageParentTitle("");
    setWpPageTemplate("");
    setPageParentId("");
    setWpPageOrder("");
    setCpId("");
    setStatus("");
    setLocalId(0);
    setDirty(false);
    setDeleted(false);
    setError(false);
    setDateCreated(QDateTime());
}

QString CPPage::displayStatus()
{
//    QString status;
//    if(iStatus=="publish"){
//        status = tr("Published");
//    }
//    else if(iStatus=="private")
//        status = tr("Private");
//    else if(iStatus=="pending")
//        status = tr("Pending review");
//    else if(iStatus=="future")
//        status = tr("Scheduled in future");
//    else if(iStatus=="draft")
//        status = tr("Draft");
//    else if(iStatus=="trash")
//        status = tr("Trashed");
//    if(iItemId.isNull())
//        status = tr("Local Draft");
//    if(iLocalId==0)
//        status = tr("Orphaned");
//    if(iDirty)
//        status = tr("Busy");
    return iStatus;
}

QString CPPage::descriptionHtml()
{
	QString contentForHtml = iDescription;
	contentForHtml = contentForHtml.remove("width=").remove("height=");
	return contentForHtml.replace("\n", "<br/>");
}

void CPPage::setInfo(RoleItemModel* model, const int index)
{
	setInfo(model->value(index).toMap());
}

void CPPage::setInfo(const QVariantMap info)
{
	setDescription(info[pageRoleNames[PageEntry::DescRole]].toString());
	setTitle(info[pageRoleNames[PageEntry::TitleRole]].toString());
	setLink(info[pageRoleNames[PageEntry::LinkRole]].toString());
	setPermaLink(info[pageRoleNames[PageEntry::PermaLinkRole]].toString());
	setMtExcerpt(info[pageRoleNames[PageEntry::ExcerptRole]].toString());
	setMtAllowComments(info[pageRoleNames[PageEntry::CommentsOpenRole]].toString());
	setMtAllowPings(info[pageRoleNames[PageEntry::PingsOpenRole]].toString());
	setWpSlug(info[pageRoleNames[PageEntry::SlugRole]].toString());
	setWpPassword(info[pageRoleNames[PageEntry::PasswordRole]].toString());
	setWpAuthor(info[pageRoleNames[PageEntry::WpAuthorRole]].toString());
	setWpAuthorId(info[pageRoleNames[PageEntry::WpAuthorRole]].toString());
	setWpAuthorDisplayName(info[pageRoleNames[PageEntry::WpAuthorDisplayNameRole]].toString());
	setWpPageParentTitle(info[pageRoleNames[PageEntry::WpPageParentTitleRole]].toString());
	setWpPageTemplate(info[pageRoleNames[PageEntry::TemplateRole]].toString());
	setPageParentId(info[pageRoleNames[PageEntry::WpPageParentIdRole]].toString());

	setStatus(info[pageRoleNames[PageEntry::StatusRole]].toString());
	setLocalId(info[pageRoleNames[PageEntry::IdRole]].toString());
	setDateCreated(info[pageRoleNames[PageEntry::DateCreatedRole]].toDateTime());

	setCpId(info[pageRoleNames[PageEntry::IdRole]].toString());
}

void CPPage::fetchInfo()
{
    QMultiMap<QString, QVariant> params;
    CPAction::CPOperation op = CPAction::GetPage;
    QStringList order;
    order<<"blog_id"<<"page_id"<<"username"<<"password";
    CPAction *request = new CPAction(op, this);
    params.insert("page_id", _cpId);
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

void CPPage::requestFinished(const int operation, const QVariant &result)
{
//    if(result.isNull() || !result.isValid()) {
//        taskFailed(operation, tr("Unknown response"));
//        requests[operation]->deleteLater();
//        requests.remove(operation);
//        return;
//    }
    CPAction *reply = qobject_cast<CPAction *>(sender());
    switch(operation) {
        case CPAction::GetPage:
        {
            QVariantMap page = result.toList().first().toMap();
            QVariantMap it;
            it[pageRoleNames[PageEntry::IdRole]] = page["page_id"].toString();
            it[pageRoleNames[PageEntry::TitleRole]] = page["title"].toString();
            it[pageRoleNames[PageEntry::LocalIdRole]] = page["page_id"].toString();
            QString desc;
            if (!page["text_more"].toString().isEmpty()) {
                // page is split into two parts
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
            setInfo(it);
            emit pageRefreshed(page);
        } break;
    }
    taskFinished(operation);
    reply->deleteLater();
    requests.remove(operation);
}

void CPPage::requestError(const int operation,const int code,const QString msg)
{
    CPAction *reply = qobject_cast<CPAction *>(sender());
    qDebug()<<"CPPage---Error"<<operation<<code<<msg;
    taskFailed(operation, msg);
    reply->deleteLater();
    requests.remove(operation);
}

void CPPage::taskStarted(const int op)
{
    if(op==CPAction::GetPage) {
        setInfoState(ProgressState::Processing);
        setInfoStatus(tr("Fetching page info..."));
    }
}

void CPPage::taskFinished(const int op)
{
    if(op==CPAction::GetPage) {
        setInfoState(ProgressState::Success);
        setInfoStatus(tr("Fetched page info!"));
    }
}

void CPPage::taskFailed(const int op, const QString msg)
{
    if(op==CPAction::GetPage) {
        setInfoState(ProgressState::Error);
        setInfoStatus(msg);
    }
}
