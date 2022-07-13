#include "calendar.h"

Calendar::Calendar(QWidget *parent) : QMainWindow(parent)
{
    m_calendarWidget = new CalendarWidget(this);
    m_calendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    m_calendarWidget->setHorizontalHeaderFormat(QCalendarWidget::ShortDayNames);
    m_calendarWidget->setFirstDayOfWeek(Qt::Monday);
    m_calendarWidget->setGridVisible(true);
    m_calendarWidget->setMinimumDate(QDate(1970, 1, 1));
    m_calendarWidget->setMaximumDate(QDate(9999, 12, 31));
    m_calendarWidget->setSelectedDate(QDate::currentDate());

    resize(600, 400);

    connect(m_calendarWidget, SIGNAL(activated(QDate)), this, SLOT(slotOpenDayView(QDate)));

    setCentralWidget(m_calendarWidget);
}

void Calendar::slotOpenDayView(QDate date)
{
    DayView *day = new DayView(date);
    connect(day, SIGNAL(windowClosed()), m_calendarWidget, SLOT(slotUpdateVectorOfDates()));
    day->exec();
}
