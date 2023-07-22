#include "lineeditdelegate.h"

LineEditDelegate::LineEditDelegate(QObject *parent) : QItemDelegate(parent)
{

}

QWidget *LineEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    QLineEdit *editor = new QLineEdit(parent);
    editor->setStyleSheet(styleSheet);
    editor->setInputMask(inMask);
    return editor;
}

void LineEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    // Get the value via index of the Model
    QString value = index.model()->data(index, Qt::EditRole).toString();
    // Put the value into the SpinBox
    QLineEdit *lEdit = static_cast<QLineEdit*>(editor);
    lEdit->setText(value);
}

void LineEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lEdit = static_cast<QLineEdit*>(editor);
    QString value = lEdit->text();
    model->setData(index, value, Qt::EditRole);
}

void LineEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}
