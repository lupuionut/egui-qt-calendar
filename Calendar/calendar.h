#ifndef CALENDAR_H
#define CALENDAR_H

#include "dayview.h"
#include "calendarwidget.h"

#include <QMainWindow>

class Calendar : public QMainWindow
{
    Q_OBJECT

public:
    explicit Calendar(QWidget *parent = nullptr);

private:
    CalendarWidget *m_calendarWidget;
};
#endif // CALENDAR_H
