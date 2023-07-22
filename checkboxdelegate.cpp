#include "checkboxdelegate.h"

CheckBoxDelegate::CheckBoxDelegate(QObject *parent) : QItemDelegate(parent)
{

}

QWidget *CheckBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    QCheckBox *editor = new QCheckBox(parent);
    editor->setStyleSheet("QCheckBox::indicator { border:3px solid #CA3E47; width: 10px; height: 10px;}"
                          "QCheckBox::indicator:checked { background-color: #CA3E47; }");
    return editor;

}

void CheckBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    // Get the value via index of the Model
    QString value = index.model()->data(index, Qt::EditRole).toString();

    // Put the value into the SpinBox
    QCheckBox *checkbox = static_cast<QCheckBox*>(editor);
    if(value == "1"){
        checkbox->setChecked(true);
    }
    else{
        checkbox->setChecked(false);
    }

}

void CheckBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QCheckBox *checkbox = static_cast<QCheckBox*>(editor);
    QString value = "0";
    if(checkbox->isChecked()){
        value = "1";
    }
    model->setData(index, value, Qt::EditRole);

}

void CheckBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);

}
