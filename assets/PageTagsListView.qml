import bb.cascades 1.3
import com.cutepress.webimageview 1.0

CutePressListView {
    id: iList
    signal flickedAtEnd()
    
    //    property string lastDeletedPostId: appBlog.lastDeletedPostId
    //    onLastDeletedPostIdChanged: {
    //        if(lastDeletedPostId!="")
    //        	appUtil.deletePostInModel(dataModel, lastDeletedPostId)
    //    }
    
    horizontalAlignment: HorizontalAlignment.Fill
    verticalAlignment: VerticalAlignment.Fill
    
    listItemComponents: [
        ListItemComponent {
            id: listComponent
            type: "item"
            Container {
                id: rootContainer
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill
                property bool isHighlighted
                
                layout: DockLayout {
                }
                //                Container {
                //                    background: {
                //                        if(ListItemData.postPublishStatus=="private")
                //                        	return Color.Green
                //                        else if(ListItemData.postPublishStatus=="pending")
                //                            return Color.create("#FF8C00")
                //                        else if(ListItemData.postPublishStatus=="draft")
                //                            return Color.Yellow
                //                        else if(ListItemData.postPublishStatus=="future")
                //                            return Color.DarkCyan
                //                        else if(ListItemData.postPublishStatus=="trash")
                //                            return Color.Red
                //                    }
                //                    minWidth: 10
                //                    maxWidth: minWidth
                //                    horizontalAlignment: HorizontalAlignment.Right
                //                    verticalAlignment: VerticalAlignment.Fill
                //                }
                Container {
                    horizontalAlignment: HorizontalAlignment.Fill
                    layout: StackLayout {}
                    Container {
                        horizontalAlignment: HorizontalAlignment.Fill
                        leftPadding: ui.sdu(2)
                        rightPadding: leftPadding
                        layout: StackLayout {}
                        Label {
                            text: ListItemData.tagName
                            textStyle.fontWeight: FontWeight.Bold
                            textFormat: TextFormat.Html
                            multiline: true
                        }
                        Label {
                            text: ListItemData.tagCount>1?qsTr("%1 posts | %2").arg(ListItemData.tagCount).arg(ListItemData.tagSlug):qsTr("%1 post | %2").arg(ListItemData.tagCount).arg(ListItemData.tagSlug)
                            textFormat: TextFormat.Html
                            textStyle.fontSize: FontSize.XSmall
                            textStyle.color: Color.Gray
                            textStyle.fontStyle: FontStyle.Italic
                            multiline: true
                        }
                    }
                    Divider {}
                }
                
                // A colored Container is used to highlight the item on selection.
                Container {
                    id: highlight
                    background: Color.Gray
                    opacity: rootContainer.isHighlighted? 0.8: 0.0
                    horizontalAlignment: HorizontalAlignment.Fill
                    verticalAlignment: VerticalAlignment.Fill
                }
                
                // Both the activation and selection of an item has the same visual appearance, we alter the opacity of the item.
                function setHighlight(highlighted) {
                    rootContainer.isHighlighted = highlighted
                }
                
                // Signal handler for ListItem activation
                ListItem.onActivationChanged: {
                    setHighlight(ListItem.active);
                }
                
                // Signal handler for ListItem selection
                ListItem.onSelectionChanged: {
                    setHighlight(ListItem.selected);
                }
                
                contextActions: [
                    ActionSet {
                        id: cntxtMenu
                        title: qsTr("Post options")
                        subtitle: ListItemData.postTitle //"This is an action set."
                        
                        actions: [
                            //                            ActionItem {
                            //                                title: qsTr("View details")
                            //                                imageSource: "asset:///images/details.png"
                            //                                onTriggered: {
                            //                                    rootContainer.ListItem.view.openPhotoDetails(rootContainer.ListItem.view.dataModel, rootContainer.ListItem.indexPath);
                            //                                }
                            //                            },
                            //                            ActionItem {
                            //                                title: ListItemData.photoFavorited?qsTr("Unfavorite"):qsTr("Favorite")
                            //                                enabled: rootContainer.ListItem.view.isUserAuthorized
                            //                                imageSource: ListItemData.photoFavorited?"asset:///images/unfavorite.png":"asset:///images/favorite.png"
                            //                                onTriggered: {
                            //                                    if(ListItemData.photoFavorited)
                            //                                        rootContainer.ListItem.view.unfavoritePhoto(ListItemData.photoId)
                            //                                    else
                            //                                        rootContainer.ListItem.view.favoritePhoto(ListItemData.photoId)
                            //                                }
                            //                            },
                            //                            ActionItem {
                            //                                title: ListItemData.photoVoted?qsTr("Liked"):qsTr("Like")
                            //                                imageSource: "asset:///images/like.png"
                            //                                enabled: rootContainer.ListItem.view.isUserAuthorized && !ListItemData.photoVoted
                            //                                onTriggered: {
                            //                                    rootContainer.ListItem.view.likePhoto(ListItemData.photoId)
                            //                                }
                            //                            },
                            //                            ActionItem {
                            //                                title: qsTr("View owner profile")
                            //                                imageSource: "asset:///images/user.png"
                            //                                onTriggered: {
                            //                                    rootContainer.ListItem.view.openPersonPage(ListItemData.photoUserId, ListItemData.photoUserUsername, ListItemData.photoUserFullname, ListItemData.photoUserUserpicUrl);
                            //                                }
                            //                            },
                            //                            ActionItem {
                            //                                title: {
                            //                                    if(ListItemData.postPublishStatus=="publish")
                            //                                    	return qsTr("Review")
                            //                                    else
                            //                                        return qsTr("Publish")
                            //                                }
                            //                                enabled: ListItemData.postBlogId==rootContainer.ListItem.view.appBlogId && (ListItemData.postPublishStatus=="publish")
                            //                                imageSource: "asset:///images/comment.png"
                            //                                onTriggered: {
                            //                                    rootContainer.ListItem.view.openPhotoCommentsWithDetails(ListItemData.photoId, ListItemData.photoName, ListItemData.photoDescription, ListItemData.photoThumbUrl);
                            //                                }
                            //                            },
//                            ActionItem {
//                                title: qsTr("Edit")
//                                enabled: rootContainer.ListItem.view.isUserAuthorized && ListItemData.postBlogId == rootContainer.ListItem.view.appBlogId
//                                imageSource: "asset:///images/edit.png"
//                                onTriggered: {
//                                    rootContainer.ListItem.view.openEditPostEditor(rootContainer.ListItem.view.dataModel.data(rootContainer.ListItem.indexPath));
//                                }
//                            },
                            InvokeActionItem {
                                title: qsTr("Share")
                                imageSource: "asset:///images/share.png"
                                query {
                                    mimeType: "text/plain"
                                    invokeActionId: "bb.action.SHARE"
                                }
                                onTriggered: {
                                    data = ListItemData.postTitle+" " + ListItemData.postShorUrl;
                                }
                            },
                            ActionItem {
                                title: qsTr("Copy link")
                                imageSource: "asset:///images/copy_link.png"
                                onTriggered: rootContainer.ListItem.view.copyToClipboard(ListItemData.postUrl)
                            },
                            ActionItem {
                                title: qsTr("Open in browser")
                                imageSource: "asset:///images/open_link.png"
                                onTriggered: rootContainer.ListItem.view.openLink(ListItemData.postUrl)
                            }//,
//                            ActionItem {
//                                title: qsTr("Delete")
//                                enabled: rootContainer.ListItem.view.isUserAuthorized && ListItemData.postBlogId == rootContainer.ListItem.view.appBlogId
//                                imageSource: "asset:///images/delete.png"
//                                onTriggered: {
//                                    rootContainer.ListItem.view.deletePost(ListItemData.postId)
//                                }
//                            }
                        ]
                    } // end of ActionSet
                ] // end of contextActions list
            }
        }
    ]
    onTriggered: {
        //        mainWindow.openPost(dataModel.data(indexPath))
    }
    attachedObjects: [
        ListScrollStateHandler {
            id: scrollStateHandler
            onAtEndChanged: {
                if (scrollStateHandler.atEnd) {
                    iList.flickedAtEnd();
                }
            }
        }
    ]
}