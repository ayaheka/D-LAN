#include "TableLogItemDelegate.h"

#include <QPainter>

#include <Common/LogManager/IEntry.h>

#include <TableLogModel.h>

TableLogItemDelegate::TableLogItemDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

void TableLogItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
   const TableLogModel* model = static_cast<const TableLogModel*>(index.model());
   QStyleOptionViewItem newOption(option);

   switch (model->getSeverity(index.row()))
   {
   case LM::SV_END_USER :
      painter->fillRect(option.rect, QColor(222, 213, 235));
      break;
   case LM::SV_WARNING :
      painter->fillRect(option.rect, QColor(235, 199, 199));
      break;
   case LM::SV_ERROR :
      painter->fillRect(option.rect, QColor(200, 0, 0));
      newOption.palette.setColor(QPalette::Text, QColor(255, 255, 255));
      break;
   case LM::SV_FATAL_ERROR :
      painter->fillRect(option.rect, QColor(50, 0, 0));
      newOption.palette.setColor(QPalette::Text, QColor(255, 255, 0));
      break;
   }

   QItemDelegate::paint(painter, newOption, index);
}
