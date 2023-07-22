#include "pushbuttondelegate.h"

static QString btnName = "";

PushButtonDelegate::PushButtonDelegate(QObject *parent) : QItemDelegate(parent)
{

}

QWidget *PushButtonDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    QPushButton *editor = new QPushButton(parent);
    editor->setStyleSheet(styleSheet);
    return editor;

}

void PushButtonDelegate::setEditorData(QWidget* editor, const QModelIndex &index) const
{
    // Get the value via index of the Model
    QString value = index.model()->data(index, Qt::EditRole).toString();
    // Put the value into the SpinBox
    btnName = QString::number(index.row()) + "," + QString::number(index.column());
    QPushButton *btn = static_cast<QPushButton*>(editor);
    connect(btn, SIGNAL(clicked()), this , SLOT(btnClickedSignal()));
    btn->setText(value);
}


void PushButtonDelegate::setModelData(QWidget* editor, QAbstractItemModel *model , const QModelIndex &index) const
{
    QPushButton *btn = static_cast<QPushButton*>(editor);
    QString value = btn->text();
    model->setData(index, value, Qt::EditRole);
}

void PushButtonDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}

void PushButtonDelegate::btnClickedSignal()
{
    emit clickSignal(btnName);
}
