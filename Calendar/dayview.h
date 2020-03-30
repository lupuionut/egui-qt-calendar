#ifndef DAYVIEW_H
#define DAYVIEW_H

#include "eventedit.h"

#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QDate>

class DayView : public QDialog
{
    Q_OBJECT

public:
    explicit DayView(QDate date, QWidget *parent = nullptr);

private:
    QTableWidget *m_eventsTable;
    QStringList m_tableHeader;

    QPushButton *m_addButton;
    QPushButton *m_closeButton;

    QVBoxLayout *m_layout;
    QHBoxLayout *m_buttonLayout;

    QDate m_date;
    QJsonObject m_eventsJson;

    bool readEventsFromFile(); // saves events from JSON to m_eventsJson
    void updateEventsTable(); // applies changes made to events in selected day (day edited in current dialog)
    bool writeEventsToFile(); // saves events from m_eventsJson to JSON file

signals:
    void windowClosed(); // informs main widget (calendar) that dialog has been closed

private slots:
    void slotAddEvent(); // opens dialog for adding new event
    void slotSaveEventToTable(QJsonObject event); // saves new event in table
    void slotDeleteEvent(); // deletes event
    void slotEditEvent(); // opens dialog for editing existing event
    void slotEditEventInTable(QJsonObject event, int rowToEdit); // saves edited event in table
    void slotCloseWindow(); // calls writeEventsToFile() and emits windowClosed()
};


#endif // DAYVIEW_H
