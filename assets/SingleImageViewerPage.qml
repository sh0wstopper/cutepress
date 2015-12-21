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

import bb.cascades 1.3
import com.cutepress.webimageview 1.0
import "UIConstants.js" as UI

Page {
    id: page
    property variant photo
    property alias imageUrl: bigImg.url
    property alias titleText: titleLabel.text
    property alias descriptionText: descriptionLabel.text
    property alias linkText: linkLabel.text
    property alias dateText: dateLabel.text
    actions: [
        InvokeActionItem {
            title: qsTr("Share")
            imageSource: "asset:///images/share.png"
            ActionBar.placement: ActionBarPlacement.InOverflow
            query {
                mimeType: "text/plain"
                invokeActionId: "bb.action.SHARE"
            }
            onTriggered: {
                data = titleText + " "+imageUrl;
            }
        },
        ActionItem {
            title: qsTr("Copy link")
            imageSource: "asset:///images/copy_link.png"
            onTriggered: {
                appUtil.copyTextToClipboard(imageUrl);
            }
            ActionBar.placement: ActionBarPlacement.InOverflow
        },
        ActionItem {
            title: qsTr("Open in browser")
            imageSource: "asset:///images/open_link.png"
            onTriggered: {
                appUtil.launchBrowser(imageUrl);
            }
            ActionBar.placement: ActionBarPlacement.InOverflow
        }
    ]
    titleBar: TitleBar {
        title: qsTr("Image")
    }
    ScrollView {
        id: scrollView
        horizontalAlignment: HorizontalAlignment.Fill
        scrollViewProperties {
            scrollMode: ScrollMode.Vertical
        }

        content: Container {
            layout: StackLayout {
            }
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Fill
            WebImageView {
                id: bigImg
                horizontalAlignment: HorizontalAlignment.Center
                scalingMethod: ScalingMethod.AspectFit
            }
            Divider {
            }

            Container {
                topPadding: ui.sdu(2)
                bottomPadding: topPadding
                leftPadding: ui.sdu(2)
                rightPadding: leftPadding
                horizontalAlignment: HorizontalAlignment.Fill
                layout: StackLayout {
                }
                Label {
                    id: titleLabel
                    multiline: true
                    horizontalAlignment: HorizontalAlignment.Fill
                    textStyle {
                        base: SystemDefaults.TextStyles.NormalText
                        fontWeight: FontWeight.Bold
                    }
                    visible: text != ""
                }
                Label {
                    id: descriptionLabel
                    multiline: true
                    visible: text != ""
                    textFormat: TextFormat.Html
                    textStyle {
                        base: SystemDefaults.TextStyles.NormalText
                    }
                }
                Label {
                    id: linkLabel
                    visible: text != ""
                    textFormat: TextFormat.Html
                    textStyle {
                        base: SystemDefaults.TextStyles.NormalText
                        fontWeight: FontWeight.W300
                        color: Color.DarkGray
                    }
                    multiline: true
                }
                Label {
                    id: dateLabel
                    visible: text != ""
                    textStyle.color: Color.Gray
                    textStyle.fontSize: FontSize.XSmall
                    textFormat: TextFormat.Html
                }
            }
        }
    }
}
