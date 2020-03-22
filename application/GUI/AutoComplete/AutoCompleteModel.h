/**
  * D-LAN - A decentralized LAN file sharing software.
  * Copyright (C) 2010-2012 Greg Burri <greg.burri@gmail.com>
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */
  
#pragma once

#include <QAbstractTableModel>
#include <QString>

#include <Common/Hash.h>

namespace GUI
{
   class AutoCompleteModel : public QAbstractTableModel
   {
   public:
      AutoCompleteModel();
      ~AutoCompleteModel();

      void setValues(const QList<QPair<Common::Hash, QString>>& values);

      Common::Hash getHash(const QModelIndex& index) const;

      /*QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
      QModelIndex parent(const QModelIndex& child) const;*/
      int rowCount(const QModelIndex& parent = QModelIndex()) const override;
      int columnCount(const QModelIndex& parent = QModelIndex()) const override;
      QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

   private:
      QList<QPair<Common::Hash, QString>> values;
   };
}
