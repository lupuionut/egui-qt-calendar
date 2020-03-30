#ifndef EVENTEDIT_H
#define EVENTEDIT_H

#include <QDialog>
#include <QJsonObject>
#include <QRegExpValidator>

namespace Ui {
class EventEdit;
}

class EventEdit : public QDialog
{
    Q_OBJECT

public:
    // Add mode allows user to add brand new event; Edit mode allows to set new values for existing events
    enum EditMode
    {
        Add, Edit
    };

    explicit EventEdit(EditMode editMode, int rowToEdit = 0, QString time = "", QString description = "", QWidget *parent = nullptr);
    ~EventEdit();

private:
    Ui::EventEdit *ui;
    QJsonObject m_event;
    int m_rowToEdit;
    EditMode m_editMode;

private slots:
    void slotSaveEvent(); // saves event to m_event

signals:
    void newEventSaved(QJsonObject event); // informs that new event has been created
    void editedEventSaved(QJsonObject event, int rowToEdit); // informs that event has been edited

};

#endif // EVENTEDIT_H
