#ifndef CHECKBOXDELEGATE_H
#define CHECKBOXDELEGATE_H

#include <QObject>
#include <QItemDelegate>
#include <QCheckBox>

class CheckBoxDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit CheckBoxDelegate(QObject *parent = nullptr);
    /* Create Editor when we construct MyDelegate */
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const;

    /* Then, we set the Editor */
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    /* When we modify data, this model reflect the change */
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    /* Give the SpinBox the info on size and location */
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const;

signals:

};

#endif // CHECKBOXDELEGATE_H
