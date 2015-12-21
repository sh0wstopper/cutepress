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

#ifndef ROLEITEMMODEL_H
#define ROLEITEMMODEL_H

#include <bb/cascades/ArrayDataModel>
#include <QObject>

/* Convenience class to allow easily exposing
   C++ data as a model for QML View.
*/
using namespace bb::cascades;

class RoleItemModel : public ArrayDataModel
{
	Q_OBJECT
public:
    /* roleNames is a map describing when role id (e.g. Qt::UserRole+1)
      is associated with what name on QML side (e.g. 'bookTitle')      */
    RoleItemModel(const QHash<int, QString> &roleNames = QHash<int, QString>(), QObject * parent = 0);
    ~RoleItemModel();
    Q_INVOKABLE QString itemType (const QVariantList &indexPath) {return "item";}
    QVariantList list;

public slots:
	void setRoleNames(const QHash<int, QString> &roleNames) { _roleNames = roleNames; }
	int rowCount() { return size(); }
	int rowsCount() { return size(); }

    void addEntry(QVariantMap item);
    void insertEntry(const int pos, QVariantMap item);
    void removeEntry(int row);
    void clearModel();
private:
    QHash<int, QString> _roleNames;
};

#endif // ROLEITEMMODEL_H
