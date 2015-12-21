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

#include "WebImageView.h"
#include <bb/cascades/Image>

QNetworkAccessManager * WebImageView::mNetManager = new QNetworkAccessManager;
QNetworkDiskCache * WebImageView::mNetworkDiskCache = new QNetworkDiskCache();

WebImageView::WebImageView() {
	setImage(Image());
	setStatus(WebImageView::None);

	// Initialize network cache
	mNetworkDiskCache->setCacheDirectory(QDesktopServices::storageLocation(QDesktopServices::CacheLocation));


	// Set cache in manager
	mNetManager->setCache(mNetworkDiskCache);
}

const QUrl& WebImageView::url() const {
	return mUrl;
}

void WebImageView::setUrl(const QUrl& url) {
	if(url.isEmpty()) return;
	setStatus(WebImageView::Loading);
	mUrl = url;
	if(url.isLocalFile() || url.scheme()=="asset") {
		setImageSource(url);
		setStatus(WebImageView::Success);
		mLoading = 1.0;
		emit loadingChanged();
	} else {
		mLoading = 0;
		QNetworkReply * reply = mNetManager->get(QNetworkRequest(url));
		connect(reply,SIGNAL(finished()), this, SLOT(imageLoaded()));
		connect(reply,SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(imageError(QNetworkReply::NetworkError)));
		connect(reply,SIGNAL(downloadProgress ( qint64 , qint64  )), this, SLOT(dowloadProgressed(qint64,qint64)));
	}
	emit urlChanged();
}

double WebImageView::loading() const {
	return mLoading;
}

void WebImageView::imageLoaded() {
	QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());
	if(reply->url()!=mUrl) return;
	QString possibleRedirectUrl =
		         reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toString();
	if(!possibleRedirectUrl.isEmpty()) {
		reply->deleteLater();
		setUrl(possibleRedirectUrl);
		return;
	}
	setImage(Image(reply->readAll()));
	setStatus(WebImageView::Success);
	reply->deleteLater();
}

void WebImageView::imageError(QNetworkReply::NetworkError code)
{
	QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());
	if(code!=QNetworkReply::NoError) {
		setStatus(WebImageView::Error);
	}
	reply->deleteLater();
}

void WebImageView::dowloadProgressed(qint64 bytes,qint64 total)
{
	mLoading =  double(bytes)/double(total);
	emit loadingChanged();
}
