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

#include "roleitemmodel.h"
#include <QDebug>


RoleItemModel::RoleItemModel(const QHash<int, QString> &roleNames, QObject *parent)
              :ArrayDataModel(parent)
{
    setRoleNames(roleNames);
    list.clear();
}

RoleItemModel::~RoleItemModel()
{

}

void RoleItemModel::addEntry(QVariantMap item)
{
    if(!list.contains(item[_roleNames.value(Qt::UserRole+1)])) {
    	item["index"] = size();
        list.append(item[_roleNames.value(Qt::UserRole+1)]);
    	this->append(item);
    }
}

void RoleItemModel::insertEntry(const int pos, QVariantMap item)
{
    if(!list.contains(item[_roleNames.value(Qt::UserRole+1)])) {
    	item["index"] = pos;
        list.insert(pos, item[_roleNames.value(Qt::UserRole+1)]);
    	this->insert(pos, item);
    }
}

void RoleItemModel::removeEntry(int row)
{
    if(row<rowsCount()) {
        if(!list.isEmpty())
            list.removeOne(this->value(row).toMap().value(_roleNames.value(Qt::UserRole+1)));
        removeAt(row);
    }
}

void RoleItemModel::clearModel()
{
    list.clear();
    clear();
}
