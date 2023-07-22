#ifndef REMOVEDEVWIN_H
#define REMOVEDEVWIN_H

#include <QDialog>

namespace Ui {
class RemoveDevWin;
}

class RemoveDevWin : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveDevWin(QWidget *parent = nullptr);
    ~RemoveDevWin();

private:
    Ui::RemoveDevWin *ui;
};

#endif // REMOVEDEVWIN_H
