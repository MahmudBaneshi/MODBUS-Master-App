#ifndef NOTEDITABLEDELEGATE_H
#define NOTEDITABLEDELEGATE_H

#include <QObject>
#include <QItemDelegate>


class NotEditableDelegate : public QItemDelegate
{
public:
    explicit NotEditableDelegate(QObject *parent = nullptr);


protected:
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
    QWidget* createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const;

};

#endif // NOTEDITABLEDELEGATE_H
