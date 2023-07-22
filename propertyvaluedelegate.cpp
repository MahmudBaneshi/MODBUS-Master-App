#include "propertyvaluedelegate.h"

PropertyValueDelegate::PropertyValueDelegate(QObject *parent) : QItemDelegate(parent)
{

}
QWidget *PropertyValueDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const
{
    /*  Get Type  */
    QString val = index.model()->data(index.sibling(index.row(), index.column() - 2), Qt::EditRole).toString();
    /*  Get Range  */
    QString valR = index.model()->data(index.sibling(index.row(), index.column() - 1), Qt::EditRole).toString();

    QStringList val_1 = valR.split('-');
    if(val_1.size() == 1){
        val_1.append("1");
    }
    if(val_1.size() == 0){
        val_1.append("0");
        val_1.append("1");
    }
    if(val == "Bool"){
        QCheckBox *editor = new QCheckBox(parent);
        editor->setStyleSheet("QCheckBox::indicator { border:3px solid #CA3E47; width: 10px; height: 10px;}"
                              "QCheckBox::indicator:checked { background-color: #CA3E47; }");
        return editor;
    }
    else if(val == "Enum"){
        QComboBox *editor = new QComboBox(parent);
        for(int i = val_1.at(0).toInt(); i < val_1.at(1).toInt() + 1; i++){
            editor->addItem(QString::number(i));
        }
        editor->setStyleSheet(styleSheet);
        return editor;
    }
    else {
        QSpinBox *editor = new QSpinBox(parent);
        editor->setMinimum(val_1.at(0).toInt());
        editor->setMaximum(val_1.at(1).toInt());
        editor->setStyleSheet(styleSheet);
        return editor;
    }

}

void PropertyValueDelegate::setEditorData(QWidget* editor, const QModelIndex &index) const
{
    // Get the value via index of the Model
    QString value = index.model()->data(index, Qt::EditRole).toString();

    /*  Get Type  */
    QString val = index.model()->data(index.sibling(index.row(), index.column() - 2), Qt::EditRole).toString();

    if(val == "Bool"){
        QCheckBox *checkbox = static_cast<QCheckBox*>(editor);
        if(value == "1"){
            checkbox->setChecked(true);
        }
        else{
            checkbox->setChecked(false);
        }
    }
    else if(val == "Enum"){
        QComboBox *combobox = static_cast<QComboBox*>(editor);
        combobox->setCurrentText(value);
    }
    else {
        QSpinBox *spinbox = static_cast<QSpinBox*>(editor);
        spinbox->setValue(value.toInt());
    }
}


void PropertyValueDelegate::setModelData(QWidget* editor, QAbstractItemModel *model , const QModelIndex &index) const
{
    /*  Get Type  */
    QString val = index.model()->data(index.sibling(index.row(), index.column() - 2), Qt::EditRole).toString();
    QString value = "0";
    if(val == "Bool"){
        QCheckBox *checkbox = static_cast<QCheckBox*>(editor);
        if(checkbox->isChecked()){
            value = "1";
        }
    }
    else if(val == "Enum"){
        QComboBox *combobox = static_cast<QComboBox*>(editor);
        value = combobox->currentText();
    }
    else {
        QSpinBox *spinbox = static_cast<QSpinBox*>(editor);
        spinbox->interpretText();
        value = QString::number(spinbox->value());
    }

    model->setData(index, value, Qt::EditRole);
}

void PropertyValueDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}

