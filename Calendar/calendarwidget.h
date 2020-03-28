#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QCalendarWidget>

class CalendarWidget : public QCalendarWidget
{
    Q_OBJECT
public:
    explicit CalendarWidget(QWidget *parent = nullptr);
protected:
    void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const override;
};

#endif // CALENDARWIDGET_H
