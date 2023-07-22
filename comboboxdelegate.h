#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QObject>
#include <QItemDelegate>
#include <QComboBox>

class ComboBoxDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit ComboBoxDelegate(QObject *parent = nullptr);

    /* Create Editor when we construct MyDelegate */
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const;

    /* Then, we set the Editor */
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    /* When we modify data, this model reflect the change */
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    /* Give the SpinBox the info on size and location */
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const;
    const QStringList InfNumber103 = { "None", "160", "161", "162", "163", "164", "165" ,"166", "167",
                                       "168", "169", "170", "171", "172", "173"}; /* whichitems = 13 160-239 */
    QStringList costumItems; /* whichitems = 15 160-239 */
    int whichItems = 0;
    QString styleSheet = "color: rgb(255, 255, 255);"
                         "font: 12pt 'Ubuntu Mono';";

signals:

private:
    const QStringList LEDs = { "None", "LED1", "LED2", "LED3", "LED4", "LED5", "LED6"};  /* whichitems = 1 */
    const QStringList Relays = { "None", "BO1", "BO2", "BO3", "BO4", "BO5", "BO6"}; /* whichitems = 2 */
    const QStringList activeInactive = { " ", "L", "U"}; /* whichitems = 3 */
    const QStringList inExt = {"Internal", "External"}; /* whichitems = 4 */
    const QStringList Funcs = { " ", "I>", "I>>", "I>>>", "IE>", "IE>>", "IE>>>"}; /* whichitems = 5 */
    const QStringList rmsFft = { "RMS", "FFT"}; /* whichitems = 6 */
    const QStringList parity = { "None", "Even", "Odd"}; /* whichitems = 7 */
    const QStringList baudRate = { "9600", "19200"}; /* whichitems = 8 */
    const QStringList group1or2 = { "GROUP1", "GROUP2"}; /* whichitems = 9 */
    const QStringList ampere = { "1A", "5A"}; /* whichitems = 10 */
    const QStringList volt = { "1000v", "500v"}; /* whichitems = 11 */
    const QStringList Inputs = { "None", "BI1", "BI2", "BI3", "BI4", "BI5", "BI6"}; /* whichitems = 12 */
    const QStringList dataType = { "Bool", "Enum", "UINT16"}; /* whichitems = 14 */

};

#endif // COMBOBOXDELEGATE_H
