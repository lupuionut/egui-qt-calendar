#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QCalendarWidget>
#include <QVector>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QFile>
#include <QPainter>

class CalendarWidget : public QCalendarWidget
{
    Q_OBJECT
public:
    explicit CalendarWidget(QWidget *parent = nullptr);

protected:
    // overrided method which paints only days with events
    void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const override;

private:
    QVector<QDate> m_datesWithEvents;
    QJsonObject m_events;

    bool readEventsFromJson(); // reads events from JSON file and saves them in m_events

private slots:
    void slotUpdateVectorOfDates(); // saves dates with events in m_datesWithEvents
};

#endif // CALENDARWIDGET_H
