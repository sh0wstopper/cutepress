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

#include "cpaction.h"

CPAction::CPAction(int action, QObject *parent)
                    : QObject(parent),
                      iAction(action)
{

}

CPAction::~CPAction()
{
}

void CPAction::exec(const QString &httpMethod, const QMultiMap<QString, QVariant> &params, const QStringList order, const bool isMultiPart)
{
    qDebug()<<"CPAction---Making request"<<iAction<<order;
    QByteArray xml;
    prepareRequestData(&xml, params, order);
    QNetworkReply *reply = 0;
    iError = QNetworkReply::NoError;
    iErrorString = "";
    QUrl iUrl = QUrl(CPEngine::instance().blogRPCUrl());
    if(iUrl.isEmpty())
    	iUrl = QUrl(prepareRPCUrl(CPEngine::instance().blogUrl()));
    reply = CPEngine::instance().request(httpMethod, iUrl, xml, isMultiPart);
    if (reply) {
    	xmlData = xml;
        iRequest = reply;
        buffer.clear();
        connect(reply, SIGNAL(readyRead()), this, SLOT(readData()));
        connect(reply, SIGNAL(finished()), this, SLOT(requestFinished()));
        connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),
                this,SLOT(requestError(QNetworkReply::NetworkError)));
    }
}

void CPAction::abortRequest()
{
    if(iRequest!=NULL && iRequest->isRunning()) {
        iRequest->abort();
        iError = iRequest->error();
        iErrorString = iRequest->errorString();
        iRequest->deleteLater();
    }
}

void CPAction::readData()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply) return;
    buffer.append(reply->readAll());
}

void CPAction::requestFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply) return;
    if(reply->error()==QNetworkReply::NoError) {
        if(iAction==CPAction::GetUserBlogs && !reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toString().isEmpty()) {
            qDebug()<<"CPAction---Redirected";
            CPEngine::instance().setBlogRPCUrl(reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toString());
            reply->deleteLater();
            exec("POST", QMultiMap<QString, QVariant>());
            return;
        }
        qDebug()<<"CPAction---Request finished!"<<reply->url();
        iError = QNetworkReply::NoError;
        iErrorString = "";
        QVariant parsed = parse(buffer);
        dataParsed(parsed);
    }
    reply->deleteLater();
}

void CPAction::requestError(QNetworkReply::NetworkError error)
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    qDebug()<<"CPAction---Error"<<error;
    iError = iRequest->error();
    iErrorString = iRequest->errorString();
    emit this->error(iAction, error, reply->errorString());
    reply->deleteLater();
}

QVariant CPAction::parse(const QByteArray data)
{
	if(data.isEmpty()) return QVariant();


    QVariantMap result;
    QDomDocument d;
    if(d.setContent(data) && !d.isNull()) {
        QDomNode n = d.firstChild();
        n = n.nextSibling();
        if(n.nodeName()=="methodResponse") {
        	n = n.firstChild();
        	if(n.nodeName()=="params") {
        		return readParams(n);
        	} else if(n.nodeName()=="fault")
				return readFault(n);
        }
    }
    return QVariant();
}

QVariant CPAction::readParams(const QDomNode params)
{
	QDomNode node = params;
	if(node.hasChildNodes()) {
		node = node.firstChild();
		QVariantList list;
		while(!node.isNull()) {
			if(node.nodeName()=="param")
				list.append(readParam(node));
			node = node.nextSibling();
		}
		return list;
	}
	return QVariant();
}

QVariant CPAction::readParam(const QDomNode param)
{
	if(param.hasChildNodes() && param.firstChild().nodeName()=="value") {
		return readValue(param.firstChild());
	}
	return QVariant();
}

QVariant CPAction::readValue(const QDomNode val)
{
	if(val.hasChildNodes()) {
		QDomNode node = val.firstChild();
		if(node.nodeName()=="array") {

			return readArray(node);
		} else if(node.nodeName()=="struct") {
			return readStruct(node);
		} else {
			return node.toElement().text();
		}
	}
	return QVariant();
}

QVariantList CPAction::readArray(const QDomNode array)
{
	if(array.hasChildNodes()) {
		QDomNode node = array.firstChild();
		if(node.nodeName()=="data") {
			node = node.firstChild();
			QVariantList list;
			while(!node.isNull()) {
				QVariant val;
				if(node.nodeName()=="value")
					val = readValue(node);
				else if(node.nodeName()=="param")
					val = readParam(node);
				else if(node.nodeName()=="struct")
					val = readStruct(node);

				if(!val.isNull()) list.append(val);
				node = node.nextSibling();
			}
			return list;
		}
	}
	return QVariantList();
}

QVariantMap CPAction::readStruct(const QDomNode strct)
{
	if(strct.hasChildNodes()) {
		QDomNode node = strct.firstChild();
		QVariantMap map;
		while(!node.isNull()) {
			if(node.nodeName()=="member") {
				QPair<QString, QVariant> pair = readMember(node);
				map.insert(pair.first, pair.second);
			}
			node = node.nextSibling();
		}
		return map;
	}
	return QVariantMap();
}

QPair<QString, QVariant> CPAction::readMember(const QDomNode member)
{
	if(member.hasChildNodes()) {
		QDomNode node = member.firstChild();
		QPair<QString, QVariant> pair;
		while(!node.isNull()) {
			if(node.nodeName()=="name")
				pair.first = node.toElement().text();
			else if(node.nodeName()=="value")
				pair.second = readValue(node);
			node = node.nextSibling();
		}
		return pair;
	}
	return QPair<QString, QVariant>();
}

QVariant CPAction::readFault(const QDomNode fault)
{
	qDebug()<<"CPAction---Parse ReadFault!";
	if(fault.hasChildNodes()) {
		QDomNode node = fault.firstChild();
		if(node.nodeName()=="value")
			return readValue(node);
	}
	return QVariant();
}

void CPAction::dataParsed(const QVariant &parsed)
{
    qDebug()<<"CPAction---Parse"<<parsed;
    if(!parsed.isNull()) {
    	if(parsed.type()==QVariant::Map) {
    		qDebug()<<"CPAction---Parse Read Fault"<<parsed.toMap();
    		QVariantMap map = parsed.toMap();
    		int errId = 101;
    		QString errStr = "Fault!";
    		if(map.contains("faultCode") && !map.value("faultCode").toString().isEmpty())
    		    errId = map.value("faultCode").toInt();
            if(map.contains("faultString") && !map.value("faultString").toString().isEmpty())
                errStr = map.value("faultString").toString();
    		emit error(iAction, errId, errStr);
    	} else {
    		emit finished(iAction, parsed);
    	}
    } else {
		qDebug()<<"CPAction---ParsingError";
        emit error(iAction, -1, tr("Empty Response! Check if XML-RPC method enabled in WordPress blog settings."));
    }
}

void CPAction::prepareRequestData(QByteArray *xml, const QMultiMap<QString, QVariant> &params, QStringList order)
{
	QXmlStreamWriter sw(xml);
	sw.setAutoFormatting(true);
	sw.writeStartDocument();

	sw.writeStartElement("methodCall");
	sw.writeTextElement("methodName", methodName());

	QMultiMap<QString, QVariant> allParams;
	if(!params.contains("blog_id")) {
		if(!CPEngine::instance().blogId().isEmpty() && iAction!=GetUserBlogs && iAction!=DeletePost) {
			allParams.insert("blog_id", CPEngine::instance().blogId());
		}
	}
	if(!params.contains("username"))
		allParams.insert("username", CPEngine::instance().blogUsername());
	if(!params.contains("password"))
		allParams.insert("password",CPEngine::instance().blogPassword());

	if(order.isEmpty()) {
		if(!CPEngine::instance().blogId().isEmpty() && iAction!=GetUserBlogs)
			order.append("blog_id");
		if(!CPEngine::instance().blogUsername().isEmpty())
			order.append("username");
		if(!CPEngine::instance().blogPassword().isEmpty())
			order.append("password");
		order.append(params.keys());
	}
	allParams = allParams+params;
	sw.writeStartElement("params");
	foreach(QString key, order) {
		sw.writeStartElement("param");
		sw.writeCharacters(key);
		writeValue(&sw, allParams.value(key));
		sw.writeEndElement();
	}
	sw.writeEndElement();

	sw.writeEndDocument();
}

QByteArray CPAction::methodName()
{
	switch(iAction) {
	case GetUserBlogs:
		return "wp.getUsersBlogs";
	case GetPosts:
		return "metaWeblog.getRecentPosts";
    case GetPost:
        return "metaWeblog.getPost";
	case GetPages:
		return "wp.getPages";
    case GetPage:
        return "wp.getPage";
	case GetComments:
		return "wp.getComments";
    case GetComment:
        return "wp.getComment";
    case GetPostComments:
        return "wp.getComments";
    case GetPostCommentsCount:
        return "wp.getCommentCount";
	case GetCommentStatusList:
		return "wp.getCommentStatusList";
	case GetMediaLibrary:
		return "wp.getMediaLibrary";
    case GetMediaItem:
        return "wp.getMediaItem";
	case GetCategories:
		return "wp.getCategories";
	case NewCategory:
		return "wp.newCategory";
	case DeleteCategory:
		return "wp.deleteCategory";
	case GetTags:
		return "wp.getTags";
	case NewPost:
		return "metaWeblog.newPost";
    case EditPost:
        return "metaWeblog.editPost";
	case DeletePost:
		return "metaWeblog.deletePost";
	case NewPage:
		return "wp.newPage";
    case EditPage:
        return "wp.editPage";
	case DeletePage:
		return "wp.deletePage";
    case NewComment:
        return "wp.newComment";
	case ApproveComment:
		return "wp.editComment";
	case UnapproveComment:
		return "wp.editComment";
	case SpamComment:
		return "wp.editComment";
	case EditComment:
		return "wp.editComment";
	case DeleteComment:
		return "wp.deleteComment";
	case UploadFile:
		return "wp.uploadFile";
    case UploadEditorImage:
        return "wp.uploadFile";
	default:
		return "";
	}
}

QString CPAction::prepareRPCUrl(const QString url)
{
	if(url.endsWith("/"))
		return url+"xmlrpc.php";
	else
		return url+"/xmlrpc.php";
}

void CPAction::writeStruct(QXmlStreamWriter *sw, QVariantMap strct)
{
	sw->writeStartElement("struct");
	QStringList keys = strct.keys();
	foreach(QString key, keys) {
		writeMember(sw,key,strct.value(key));
	}
	sw->writeEndElement();
}

void CPAction::writeMember(QXmlStreamWriter *sw, QString key, QVariant value)
{
	sw->writeStartElement("member");
	sw->writeTextElement("name", key);
	writeValue(sw, value);
	sw->writeEndElement();
}

void CPAction::writeArray(QXmlStreamWriter *sw, QVariantList list)
{
	sw->writeStartElement("array");
	sw->writeStartElement("data");
	foreach(QVariant value, list)
		writeValue(sw, value);
	sw->writeEndElement();
	sw->writeEndElement();
}

void CPAction::writeValue(QXmlStreamWriter *sw, QVariant value)
{
	sw->writeStartElement("value");
	if(value.type()==QVariant::String)
		sw->writeTextElement("string", value.toString());
	if(value.type()==QVariant::ByteArray) {
		if(iAction==UploadFile ||iAction==UploadEditorImage) {
			sw->writeStartElement("base64");
			sw->writeCharacters("");
			sw->device()->write(value.toByteArray().toBase64());
			sw->writeEndElement();
		}
	} else if(value.type()==QVariant::Bool)
		sw->writeTextElement("boolean", value.toBool()?"1":"0");
	else if(value.type()==QVariant::Int)
		sw->writeTextElement("int", value.toString());
	else if(value.type()==QVariant::List)
		writeArray(sw, value.toList());
    else if(value.type()==QVariant::StringList)
        writeArray(sw, value.toList());
	else if(value.type()==QVariant::Map)
		writeStruct(sw, value.toMap());
	else if(value.type()==QVariant::DateTime)
		sw->writeTextElement("dateTime.iso8601", value.toDateTime().toString("yyyyMMddThh:mm:ss"));
	sw->writeEndElement();
}
