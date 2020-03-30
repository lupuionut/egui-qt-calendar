#include "calendarwidget.h"

CalendarWidget::CalendarWidget(QWidget *parent) : QCalendarWidget(parent)
{
    slotUpdateVectorOfDates();
}

void CalendarWidget::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const
{
    if (m_datesWithEvents.contains(date))
    {
        painter->drawText(rect, Qt::AlignCenter, QString::number(date.day()));
        painter->fillRect(rect, QColor::fromRgb(79, 172, 247, 80));
    }
    else
        QCalendarWidget::paintCell(painter, rect, date);
}

bool CalendarWidget::readEventsFromJson()
{
    QFile loadFile("events.json");

    if (!loadFile.open(QIODevice::ReadOnly))
    {
        qWarning("Failed to open file.");
        return false;
    }

    QByteArray eventsData = loadFile.readAll();
    loadFile.close();
    m_events = QJsonDocument(QJsonDocument::fromJson(eventsData)).object();

    return true;
}

void CalendarWidget::slotUpdateVectorOfDates()
{
    readEventsFromJson();
    m_datesWithEvents.clear();

    foreach (QString key, m_events.keys())
    {
        if (m_events[key].isNull())
            continue;

        QDate date = QDate::fromString(key, "dd.MM.yyyy");
        m_datesWithEvents.append(date);
    }
}
