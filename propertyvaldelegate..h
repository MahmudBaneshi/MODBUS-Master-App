#ifndef PUSHBUTTONDELEGATE_H
#define PUSHBUTTONDELEGATE_H

#include <QObject>
#include <QItemDelegate>
#include <QPushButton>
#include <QDebug>

class PropertyValDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit PropertyValDelegate(QObject *parent = nullptr);


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

public slots:
    void btnClickedSignal();

signals:
    void clickSignal(QString i);

private:
     QString value1;


};

#endif // PUSHBUTTONDELEGATE_H
