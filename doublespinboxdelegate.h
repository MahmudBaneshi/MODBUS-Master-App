#ifndef DOUBLESPINBOXDELEGATE_H
#define DOUBLESPINBOXDELEGATE_H

#include <QObject>
#include <QItemDelegate>
#include <QDoubleSpinBox>

class DoubleSpinBoxDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit DoubleSpinBoxDelegate(QObject *parent = nullptr);

    /* Create Editor when we construct MyDelegate */
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const;

    /* Then, we set the Editor */
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    /* When we modify data, this model reflect the change */
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    /* Give the SpinBox the info on size and location */
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const;

    int Max_R = 5;
    int Min_R = 0;
    double Step_R = 0.1;
    QString styleSheet = "color: rgb(255, 255, 255);"
                         "font: 12pt 'Ubuntu Mono';";

signals:

};

#endif // DOUBLESPINBOXDELEGATE_H
