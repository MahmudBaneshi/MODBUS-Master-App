#ifndef LINEEDITDELEGATE_H
#define LINEEDITDELEGATE_H


#include <QObject>
#include <QItemDelegate>
#include <QLineEdit>

class LineEditDelegate : public QItemDelegate
{
public:
    LineEditDelegate(QObject *parent = nullptr);
    /* Create Editor when we construct MyDelegate */
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const;

    /* Then, we set the Editor */
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    /* When we modify data, this model reflect the change */
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    /* Give the SpinBox the info on size and location */
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const;
    int whichItems = 0;
    QString styleSheet = "color: rgb(255, 255, 255);"
                         "font: 12pt 'Ubuntu Mono';";
    QString inMask;
};

#endif // LINEEDITDELEGATE_H
