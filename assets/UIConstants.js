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

var UploadState = {
    None : 0,
    InQueue : 1,
    Uploading : 2,
    UploadError : 3,
    Uploaded : 4,
    Aborted: 5
};

var ProgressState = {
    None : 0,
    Success : 1,
    Processing : 2,
    Error : 3
};
var PhotoVisibility = {
    Private : 0,
    Friends : 1,
    Family : 2,
    FriendsAndFamily : 3,
    Public : 4
};

var MAX_POSTS = 450