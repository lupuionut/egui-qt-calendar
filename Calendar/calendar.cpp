#include "calendar.h"

Calendar::Calendar(QWidget *parent) : QMainWindow(parent)
{
    m_calendarWidget = new CalendarWidget(this);
    m_calendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    m_calendarWidget->setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
    m_calendarWidget->setFirstDayOfWeek(Qt::Sunday);
    m_calendarWidget->setGridVisible(true);
    m_calendarWidget->setMinimumDate(QDate(1970, 1, 1));
    m_calendarWidget->setMaximumDate(QDate(9999, 12, 31));

    resize(600, 400);

    setCentralWidget(m_calendarWidget);
}
