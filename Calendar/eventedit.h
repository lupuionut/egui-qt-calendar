#ifndef EVENTEDIT_H
#define EVENTEDIT_H

#include <QDialog>
#include <QJsonObject>
#include <QDate>

namespace Ui {
class EventEdit;
}

class EventEdit : public QDialog
{
    Q_OBJECT

public:
    explicit EventEdit(QDate, QWidget *parent = nullptr);
    ~EventEdit();

private:
    Ui::EventEdit *ui;
    QDate m_date;
    QJsonObject m_event;

private slots:
    void slotSaveEvent();

signals:
    void eventSaved(QJsonObject m_event);

};

#endif // EVENTEDIT_H
