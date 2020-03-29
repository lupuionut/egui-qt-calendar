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
    enum EditMode
    {
        Add, Edit
    };

    explicit EventEdit(EditMode editMode, int rowToEdit = 0, QWidget *parent = nullptr);
    ~EventEdit();

private:
    Ui::EventEdit *ui;
    QJsonObject m_event;
    int m_rowToEdit;
    EditMode m_editMode;

private slots:
    void slotSaveEvent();

signals:
    void newEventSaved(QJsonObject event);
    void editedEventSaved(QJsonObject event, int rowToEdit);

};

#endif // EVENTEDIT_H
