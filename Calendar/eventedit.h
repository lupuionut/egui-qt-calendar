#ifndef EVENTEDIT_H
#define EVENTEDIT_H

#include <QDialog>

namespace Ui {
class EventEdit;
}

class EventEdit : public QDialog
{
    Q_OBJECT

public:
    explicit EventEdit(QWidget *parent = nullptr);
    ~EventEdit();

private:
    Ui::EventEdit *ui;
};

#endif // EVENTEDIT_H
