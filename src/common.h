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

#ifndef COMMON_H
#define COMMON_H

#include <QObject>

/**
 * @struct ProgressEntry
 * Structure for defining roles for recentle uploaded model
 */
struct ProgressState {

    enum ProgressRoles {
        None,
        Success,
        Processing,
        Error
    };
};

/**
 * @struct BlogEntry
 * Structure for defining roles for blogs model
 */
struct BlogEntry {

    enum BlogRoles {
        UrlRole = Qt::UserRole + 1,
        IdRole,
        NameRole,
        XmlRpcUrlRole,
        HtUsernameRole,
        HtPasswordRole,
        UsernameRole,
        PasswordRole,
        IsAdminRole,
        IsWordpressRole,
        PagesCountRole,
        PostsCountRole,
        NumberOfPostsRole,
        CommentsCountRole,
        MarkedRole,
        IsActiveRole,
        SanitizedUrlRole
    };
};

/**
 * @struct MediaDirEntry
 * Structure for defining roles for directory model
 */
struct MediaDirEntry {

    enum MediaDirRoles {
        PathRole = Qt::UserRole + 1
    };
};


/**
 * @struct PageEntry
 * Structure for defining roles for pages model
 */
struct PageEntry {

    enum PagesRoles {
    	IdRole = Qt::UserRole + 1,
        TitleRole,
        LocalIdRole,
        DescRole,
        ContentSnippetRole,
        ExcerptRole,
        SlugRole,
        LinkRole,
        PermaLinkRole,
        WpPageParentTitleRole,
        WpPageParentIdRole,
        WpPageParentOrderRole,
        WpAuthorDisplayNameRole,
        WpAuthorRole,
        StatusRole,
        PasswordRole,
        DateCreatedRole,
        DisplayDateRole,
        PageTimeRole,
        PageDateRole,
        MarkedRole,
        CommentsOpenRole,
        CommentsCountRole,
        PingsOpenRole,
        TemplateRole,
        SortDateRole
    };
};

/**
 * @struct PostEntry
 * Structure for defining roles for posts model
 */
struct PostEntry {

    enum PostsRoles {
    	IdRole = Qt::UserRole + 1,
        TitleRole,
        LocalIdRole,
        DescRole,
        ContentSnippetRole,
        ExcerptRole,
        SlugRole,
        LinkRole,
        PermaLinkRole,
        WpAuthorDisplayNameRole,
        WpAuthorRole,
        CategoriesRole,
        TagsRole,
        StatusRole,
        DisplayStatusRole,
        StickyRole,
        PasswordRole,
        DateCreatedRole,
        DisplayDateRole,
        PostTimeRole,
        PostDateRole,
        DisplayModifiedRole,
        ModifiedRole,
        MarkedRole,
        CommentsOpenRole,
        PingsOpenRole,
        CommentsCountRole,
        SortDateRole
    };
};

/**
 * @struct PostStatus
 * Structure for defining roles for post status
 */
struct PostStatus {

    enum PostsRoles {
        Orphan = Qt::UserRole + 1,
        Published,
        Private,
        Pending,
        Future,
        Draft,
        LocalDraft,
        Busy,
        Trash
    };
};

/**
 * @struct CommentsEntry
 * Structure for defining roles for comments model
 */
struct CommentEntry {

    enum CommentRoles {
        IdRole = Qt::UserRole + 1,
        LocalIdRole,
        LinkRole,
        UserIdRole,
        ContentRole,
        ContentPreviewRole,
        PostIdRole,
        PostTitleRole,
        AuthorRole,
        AuthorUrlRole,
        AuthorEmailRole,
        AuthorIpRole,
        StatusRole,
        GravatarUrlRole,
        DateCreatedRole,
        MarkedRole,
        ParentIdRole,
        GrandParentIdRole,
        OrderRole,
        SortDateRole
    };
};

/**
 * @struct CategoryEntry
 * Structure for defining roles for categories model
 */
struct CategoryEntry {

    enum CategoryRoles {
        IdRole = Qt::UserRole + 1,
        ParentIdRole,
        DescriptionRole,
        CategoryNameRole,
        HtmlUrlRole,
        RssUrlRole,
        MarkedRole
    };
};

/**
 * @struct TagEntry
 * Structure for defining roles for tags model
 */
struct TagEntry {

    enum TagRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        CountRole,
        SlugRole,
        HtmlUrlRole,
        RssUrlRole,
        DataTagVersionNumberRole,
        MarkedRole
    };
};

/**
 * @struct MediaEntry
 * Structure for defining roles for media items model
 */
struct MediaEntry {

    enum MediaRoles {
    	LinkRole = Qt::UserRole + 1,
        ParentRole,
        DescriptionRole,
        ThumbnailRole,
        CaptionRole,
        TitleRole,
        MetaDataRole,
        FileTypeRole,
        DateCreatedRole,
        DisplayDateRole,
        ImageWidthRole,
        ImageHeightRole,
        SortDateRole
    };
};

/**
 * @struct LocalMediaEntry
 * Structure for defining roles for local media items model
 */
struct LocalMediaEntry {

    enum LocalMediaRoles {
        FileNameRole = Qt::UserRole + 1,
        FilePathRole,
        FileSizeRole,
        FileThumbRole,
        FileTypeRole
    };
};

/**
 * @struct StatsEntry
 * Structure for defining roles for stats views model
 */
struct StatsEntry {

    enum StatsRoles {
        DateRole = Qt::UserRole + 1,
        ViewsRole
    };
};

/**
 * @struct StatsReferrerEntry
 * Structure for defining roles for stats refrrer model
 */
struct StatsReferrerEntry {

    enum StatsReferrerRoles {
        DateRole = Qt::UserRole + 1,
        ReferrerRole,
        ReferrerPreviewRole
    };
};

/**
 * @struct StatsSearchTermsEntry
 * Structure for defining roles for stats refrrer model
 */
struct StatsSearchTermsEntry {

    enum StatsSearchTermsRoles {
        DateRole = Qt::UserRole + 1,
        SearchTermsRole,
        SearchTermsPreviewRole
    };
};

/**
 * @struct CommentOrder
 * Structure for defining order of a comment
 */
struct CommentOrder {

    enum CommentOrderRoles {
        PrimaryOrder = 0,
        SecondaryOrder,
        TertiaryOrder
    };
};

#endif // COMMON_H
