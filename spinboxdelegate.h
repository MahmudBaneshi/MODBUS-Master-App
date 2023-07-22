#ifndef SPINBOXDELEGATE_H
#define SPINBOXDELEGATE_H

#include <QObject>
#include <QItemDelegate>
#include <QSpinBox>

class SpinBoxDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit SpinBoxDelegate(QObject *parent = nullptr);
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
    int Max_R = 5;
    int Min_R = 0;
    double Step_R = 0.1;

signals:

};

#endif // SPINBOXDELEGATE_H
