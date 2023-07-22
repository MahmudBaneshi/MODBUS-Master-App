#include "comboboxdelegate.h"

ComboBoxDelegate::ComboBoxDelegate(QObject *parent) : QItemDelegate(parent)
{

}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    QComboBox *editor = new QComboBox(parent);
    if(whichItems == 5){
        for(int i = 0; i < Funcs.size(); i++){
            editor->addItem(Funcs.at(i));
        }
    }
    else if(whichItems == 15){
        for(int i = 0; i < costumItems.size(); i++){
            editor->addItem(costumItems.at(i));
        }
    }
    else if(whichItems == 14){
        for(int i = 0; i < dataType.size(); i++){
            editor->addItem(dataType.at(i));
        }
    }
    else if(whichItems == 13){
        for(int i = 0; i < InfNumber103.size(); i++){
            editor->addItem(InfNumber103.at(i));
        }
    }
    else if(whichItems == 12){
        for(int i = 0; i < Inputs.size(); i++){
            editor->addItem(Inputs.at(i));
        }
    }
    else if(whichItems == 7){
        for(int i = 0; i < baudRate.size(); i++){
            editor->addItem(baudRate.at(i));
        }
    }
    else if(whichItems == 6){
        for(int i = 0; i < rmsFft.size(); i++){
            editor->addItem(rmsFft.at(i));
        }
    }
    else if(whichItems == 8){
        for(int i = 0; i < parity.size(); i++){
            editor->addItem(parity.at(i));
        }
    }
    else if(whichItems == 9){
        for(int i = 0; i < group1or2.size(); i++){
            editor->addItem(group1or2.at(i));
        }
    }
    else if(whichItems == 6){
        for(int i = 0; i < rmsFft.size(); i++){
            editor->addItem(rmsFft.at(i));
        }
    }
    else if(whichItems == 10){
        for(int i = 0; i < ampere.size(); i++){
            editor->addItem(ampere.at(i));
        }
    }
    else if(whichItems == 11){
        for(int i = 0; i < volt.size(); i++){
            editor->addItem(volt.at(i));
        }
    }
    else if(whichItems == 4){
        for(int i = 0; i < inExt.size(); i++){
            editor->addItem(inExt.at(i));
        }
    }
    else if(whichItems == 3){
        for(int i = 0; i < activeInactive.size(); i++){
            editor->addItem(activeInactive.at(i));
        }
    }
    else if(whichItems == 2){
        for(int i = 0; i < Relays.size(); i++){
            editor->addItem(Relays.at(i));
        }
    }
    else if(whichItems == 1){
        for(int i = 0; i < LEDs.size(); i++){
            editor->addItem(LEDs.at(i));
        }
    }
    else {
        editor->addItem("DMT");
        editor->addItem("STI");
        editor->addItem("SI");
        editor->addItem("VI");
        editor->addItem("EI");
        editor->addItem("LTI");
        editor->addItem("IMI");
        editor->addItem("IVI");
        editor->addItem("IEI");
    }
    editor->setStyleSheet(styleSheet);
    return editor;

}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    // Get the value via index of the Model
    QString value = index.model()->data(index, Qt::EditRole).toString();
    // Put the value into the SpinBox
    QComboBox *combobox = static_cast<QComboBox*>(editor);
    combobox->setCurrentText(value);
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *combobox = static_cast<QComboBox*>(editor);
    QString value = combobox->currentText();
    model->setData(index, value, Qt::EditRole);

}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}
