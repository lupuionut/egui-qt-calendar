#ifndef DAYVIEW_H
#define DAYVIEW_H

#include <QDialog>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QBitArray>
#include <QDate>

class DayView : public QDialog
{
    Q_OBJECT
public:
    explicit DayView(QWidget *parent = nullptr);
private:
    QTableWidget *m_eventsTable;
    QStringList m_tableHeader;

    QPushButton *m_addButton;
    QPushButton *m_closeButton;

    QVBoxLayout *m_layout;
    QHBoxLayout *m_buttonLayout;

    QDate m_date;

    bool readEventsFromFile();
};


#endif // DAYVIEW_H
