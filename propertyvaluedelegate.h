#ifndef PROPERTYVALUEDELEGATE_H
#define PROPERTYVALUEDELEGATE_H

#include <QObject>
#include <QItemDelegate>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QDebug>

class PropertyValueDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit PropertyValueDelegate(QObject *parent = nullptr);

    /* Create Editor when we construct MyDelegate */
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const;

    /* Then, we set the Editor */
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    /* When we modify data, this model reflect the change */
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    /* Give the SpinBox the info on size and location */
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const;

    QString styleSheet = "color: rgb(255, 255, 255);"
                         "font: 12pt 'Ubuntu Mono';";


private:
     QString value1;
};

#endif // PROPERTYVALUEDELEGATE_H
