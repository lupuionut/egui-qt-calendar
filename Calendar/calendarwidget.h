#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QCalendarWidget>
#include <QVector>
#include <QJsonDocument>
#include <QJsonArray>
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
    void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const override;

private:
    QVector<QDate> m_datesWithEvents;
    QJsonObject m_events;

    bool readEventsFromJson();

private slots:
    void slotUpdateVectorOfDates();
};

#endif // CALENDARWIDGET_H
