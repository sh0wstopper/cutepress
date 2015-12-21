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

#include "apputil.h"
#include <QDebug>

AppUtil::AppUtil(QObject *parent)
        :QObject(parent)
{
}

AppUtil::~AppUtil()
{

}

QString AppUtil::normalizeText(QString myChat)
{
    QString result = myChat;
    result = result.replace("<br>", "\n");
    QString str = result;
    while(str.contains("<strong>")) {
        QString abc, cba;
        abc = str;
        abc = cba = abc.mid(abc.indexOf("<strong>"),abc.indexOf("</strong>")-abc.indexOf("<strong>")+9);
        cba = cba.remove("</strong>").remove("<strong>");
        str.replace(abc,cba);
    }
    while(str.contains("<b>")) {
        QString abc, cba;
        abc = str;
        abc = cba = abc.mid(abc.indexOf("<b>"),abc.indexOf("</b>")-abc.indexOf("<b>")+4);
        cba = cba.remove("</b>").remove("<b>");
        str.replace(abc,cba);
    }
    result = str;
    return result;
}

void AppUtil::launchBrowser(QString url)
{
	navigator_invoke(url.toStdString().c_str(), NULL);
}

QString AppUtil::removeImgFromString(const QString txt)
{
	QString result = txt;
	while(result.contains(QRegExp("<img[^>]*>"))) result.replace(QRegExp("<img[^>]*>"), "");
	return result;
}

QVariant AppUtil::fixHTML(const QString txt)
{
	QString result = txt;
	result.replace("<br>", "<br/>");
	result.replace("&", "&amp;");
	result.replace("'", "&#39;");
	result.replace("<", "&#60;");
	result.replace(">", "&#62;");
	result.replace("\"", "&#34;");
	return result;
}

void AppUtil::copyTextToClipboard(const QString txt)
{
	clipboard.clear();
	clipboard.insert("text/plain", txt.toAscii());
}

void AppUtil::likeItemInModel(RoleItemModel *model, const QString id)
{
    if(!model || id.isEmpty())
        return;
    QVariantMap item;
    for(int i=0;i<model->rowCount();i++) {
    	item = model->value(i).toMap();
    }
}

void AppUtil::unlikeItemInModel(RoleItemModel *model, const QString id)
{
    if(!model || id.isEmpty())
        return;
    QVariantMap item;
    for(int i=0;i<model->rowCount();i++) {
    	item = model->value(i).toMap();
    }
}

bool AppUtil::deleteItemInModel(RoleItemModel *model, const QString id)
{
    if(!model || id.isEmpty())
        return false;
    qDebug()<<"AppUtil---Deleting items in model";
    QVariantMap item;
    for(int i=0;i<model->rowCount();i++) {
    	item = model->value(i).toMap();
    }
    return false;
}

bool AppUtil::deletePostInModel(RoleItemModel *model, const QString id)
{
    if(!model || id.isEmpty() || !model->list.contains(id))
        return false;
    qDebug()<<"AppUtil---Deleting post in model";
    QVariantMap item;
    for(int i=0;i<model->rowCount();i++) {
    	item = model->value(i).toMap();
    	if(item["postId"].toString()==id) {
    		model->removeEntry(i);
    		return true;
    	}
    }
    return false;
}

bool AppUtil::approveCommentInModel(RoleItemModel *model, const QString id)
{
    if(!model || id.isEmpty() || !model->list.contains(id))
        return false;
    qDebug()<<"AppUtil---Approving comment in model";
    QVariantMap item;
    for(int i=0;i<model->rowCount();i++) {
    	item = model->value(i).toMap();
    	if(item["commentId"].toString()==id) {
    		item["commentStatus"]="approve";
    		model->replace(i, item);
    		return true;
    	}
    }
    return false;
}

bool AppUtil::unapproveCommentInModel(RoleItemModel *model, const QString id)
{
    if(!model || id.isEmpty() || !model->list.contains(id))
        return false;
    qDebug()<<"AppUtil---Unapproving comment in model";
    QVariantMap item;
    for(int i=0;i<model->rowCount();i++) {
    	item = model->value(i).toMap();
    	if(item["commentId"].toString()==id) {
    		item["commentStatus"]="hold";
    		model->replace(i, item);
    		return true;
    	}
    }
    return false;
}

bool AppUtil::spamCommentInModel(RoleItemModel *model, const QString id)
{
    if(!model || id.isEmpty() || !model->list.contains(id))
        return false;
    qDebug()<<"AppUtil---Spamming comment in model";
    QVariantMap item;
    for(int i=0;i<model->rowCount();i++) {
    	item = model->value(i).toMap();
    	if(item["commentId"].toString()==id) {
    		item["commentStatus"]="spam";
    		model->replace(i, item);
    		return true;
    	}
    }
    return false;
}

bool AppUtil::deleteCommentInModel(RoleItemModel *model, const QString id)
{
    if(!model || id.isEmpty() || !model->list.contains(id))
        return false;
    qDebug()<<"AppUtil---Deleting comment in model";
    QVariantMap item;
    for(int i=0;i<model->rowCount();i++) {
    	item = model->value(i).toMap();
    	if(item["commentId"].toString()==id) {
    		model->removeEntry(i);
    		return true;
    	}
    }
    return false;
}

bool AppUtil::modelContainsItem(RoleItemModel *model, const QString id)
{
    if(!model || id.isEmpty())
        return false;
    return model->list.contains(id);
}

int AppUtil::itemPositionInModel(RoleItemModel *model, const QString id)
{
	return 0;
}
QVariant AppUtil::getItemData(RoleItemModel *model, const int index, const QByteArray key)
{
    if(model && model->rowsCount()>index) {
    	return model->value(index).toMap().value(key);
    } else
        return "";
}
QString AppUtil::getFileExtension(const QString filename)
{
	return filename.split(".").last().toLower();
}

void AppUtil::changeValueInModelWithItemId(RoleItemModel* model, const QString id, const QString key, const QVariant value)
{
}

void AppUtil::changeValueInModel(RoleItemModel* model, const int idx, const QString key, const QVariant value)
{
    if(!model || idx>=model->size())
        return;
    QVariantMap item = model->value(idx).toMap();
    item[key] = value;
    model->replace(idx, item);
    qDebug()<<"AppUtil---ChangeValue-Index"<<idx<<key<<value<<model->value(idx).toMap().value(key);
}

QString AppUtil::tagsFromList(const QStringList tags)
{
	return tags.join(", ");
}

QString AppUtil::categoriesFromList(const QStringList categories)
{
	return categories.join(", ");
}

QString AppUtil::getWPUrl(const QString txt)
{
	QString iTxt = txt.toLower();
	QUrl url = QUrl(iTxt);
	if(iTxt.contains("http://") && url.isValid())
		return iTxt;
	if(iTxt.contains(".wordpress.com") || iTxt.contains("."))
		return "http://"+iTxt;
	return "http://"+iTxt+".wordpress.com";
}

bool AppUtil::isImageFile(const QString file) {
    return file.endsWith(".jpg", Qt::CaseInsensitive)||
            file.endsWith(".jpeg", Qt::CaseInsensitive)||
            file.endsWith(".png", Qt::CaseInsensitive)||
            file.endsWith(".bmp", Qt::CaseInsensitive);
}
