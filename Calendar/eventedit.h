#ifndef EVENTEDIT_H
#define EVENTEDIT_H

#include <QDialog>
#include <QJsonObject>

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
    QJsonObject m_event;

private slots:
    void slotSaveEvent();

signals:
    void eventSaved(QJsonObject event);

};

#endif // EVENTEDIT_H
