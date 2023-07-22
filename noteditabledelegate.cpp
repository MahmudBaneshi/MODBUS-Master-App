#include "noteditabledelegate.h"

NotEditableDelegate::NotEditableDelegate(QObject *parent) : QItemDelegate(parent)
{

}


bool NotEditableDelegate::editorEvent(QEvent*, QAbstractItemModel* , const QStyleOptionViewItem & , const QModelIndex &)
{
    return false;
}

QWidget* NotEditableDelegate::createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const
{
    return NULL;
}
