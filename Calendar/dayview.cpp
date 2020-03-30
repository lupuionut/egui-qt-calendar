#include "dayview.h"

DayView::DayView(QDate date, QWidget *parent) : QDialog(parent)
{
    setMinimumSize(400, 350);

    m_eventsTable = new QTableWidget(this);
    m_tableHeader << "Time" << "Description" << "";

    m_eventsTable->setRowCount(0);
    m_eventsTable->setColumnCount(3);
    m_eventsTable->insertRow(3);

    m_eventsTable->setHorizontalHeaderLabels(m_tableHeader);
    m_eventsTable->verticalHeader()->setVisible(false);
    m_eventsTable->setShowGrid(false);

    m_eventsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_eventsTable->setSelectionMode(QAbstractItemView::NoSelection);

    m_eventsTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    m_eventsTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    m_eventsTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    m_addButton = new QPushButton(this);
    m_closeButton = new QPushButton(this);
    m_addButton->setText("Add new");
    m_closeButton->setText("Close");
    m_addButton->setToolTip("Add new event");
    m_closeButton->setToolTip("Close window");

    m_layout = new QVBoxLayout(this);
    m_buttonLayout = new QHBoxLayout;
    m_buttonLayout->addWidget(m_addButton);
    m_buttonLayout->addStretch();
    m_buttonLayout->addWidget(m_closeButton);
    m_buttonLayout->setSpacing(80);
    m_layout->addWidget(m_eventsTable);
    m_layout->addLayout(m_buttonLayout);
    setLayout(m_layout);

    m_date = date;
    setWindowTitle(m_date.toString("yyyy-MM-dd"));

    connect(m_closeButton, SIGNAL(clicked()), this, SLOT(slotCloseWindow()));
    connect(m_addButton, SIGNAL(clicked()), this, SLOT(slotAddEvent()));

    readEventsFromFile();
    updateEventsTable();
}

bool DayView::readEventsFromFile()
{
    QFile loadFile("events.json");

    if (!loadFile.open(QIODevice::ReadOnly))
    {
        qWarning("Failed to open file.");
        return false;
    }

    QByteArray eventsData = loadFile.readAll();
    loadFile.close();
    m_eventsJson = QJsonDocument(QJsonDocument::fromJson(eventsData)).object();

    return true;
}

void DayView::updateEventsTable()
{
    QJsonArray eventsArray = m_eventsJson[m_date.toString("dd.MM.yyyy")].toArray();
    m_eventsTable->clearContents();
    m_eventsTable->setRowCount(0);

    for (int i = 0; i < eventsArray.size(); i++)
    {
        QJsonObject singleEvent = eventsArray[i].toObject();
        m_eventsTable->insertRow(i);
        m_eventsTable->setItem(i, 0, new QTableWidgetItem(singleEvent["time"].toString()));
        m_eventsTable->setItem(i, 1, new QTableWidgetItem(singleEvent["description"].toString()));

        QWidget *rowButtons = new QWidget(m_eventsTable);
        QHBoxLayout *rowButtonLayout = new QHBoxLayout(rowButtons);

        QPushButton *editButton = new QPushButton(rowButtons);
        editButton->setText("Edit");
        editButton->setObjectName("editButton");
        QPushButton *deleteButton = new QPushButton(rowButtons);
        deleteButton->setText("Delete");
        deleteButton->setObjectName("deleteButton");
        connect(editButton, SIGNAL(clicked()), this, SLOT(slotEditEvent()));
        connect(deleteButton, SIGNAL(clicked()), this, SLOT(slotDeleteEvent()));

        rowButtonLayout->addStretch();
        rowButtonLayout->addWidget(editButton);
        rowButtonLayout->addWidget(deleteButton);
        rowButtonLayout->setAlignment(deleteButton, Qt::AlignRight);
        rowButtonLayout->setAlignment(editButton, Qt::AlignRight);
        rowButtonLayout->setContentsMargins(0, 0, 5, 0);
        m_eventsTable->setCellWidget(i, 2, rowButtons);
    }
    m_eventsTable->sortByColumn(0,Qt::AscendingOrder);

    for (int i = 0; i < m_eventsTable->rowCount(); i++)
    {
        m_eventsTable->cellWidget(i, 2)->findChild<QPushButton *>("editButton")->setProperty("id", i);
        m_eventsTable->cellWidget(i, 2)->findChild<QPushButton *>("deleteButton")->setProperty("id", i);
    }
}

bool DayView::writeEventsToFile()
{
    QFile saveFile("events.json");
    if (!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Failed to open file.");
        return false;
    }

    QJsonDocument saveDoc(m_eventsJson);
    saveFile.write(saveDoc.toJson());
    saveFile.close();

    return true;
}

void DayView::slotAddEvent()
{
    EventEdit *newEvent = new EventEdit(EventEdit::Add);
    QObject::connect(newEvent, SIGNAL(newEventSaved(QJsonObject)), this, SLOT(slotSaveEventToTable(QJsonObject)));
    newEvent->exec();
}

void DayView::slotSaveEventToTable(QJsonObject event)
{
    QJsonArray currentDayEvents = m_eventsJson[m_date.toString("dd.MM.yyyy")].toArray();
    currentDayEvents.append(event);
    m_eventsJson[m_date.toString("dd.MM.yyyy")] = currentDayEvents;

    updateEventsTable();
    writeEventsToFile();
}

void DayView::slotDeleteEvent()
{
    QPushButton *buttonSender = qobject_cast<QPushButton*>(sender());
    QJsonArray currentDayEvents = m_eventsJson[m_date.toString("dd.MM.yyyy")].toArray();

    for (QJsonArray::iterator it = currentDayEvents.begin(); it != currentDayEvents.end(); ++it)
    {
        QJsonObject event = it->toObject();
        if (event["time"] == m_eventsTable->item(buttonSender->property("id").toInt(), 0)->text() &&
                event["description"] == m_eventsTable->item(buttonSender->property("id").toInt(), 1)->text())
        {
            currentDayEvents.erase(it);
            break;
        }
    }

    if (currentDayEvents.isEmpty())
        m_eventsJson.remove(m_date.toString("dd.MM.yyyy"));
    else
        m_eventsJson[m_date.toString("dd.MM.yyyy")] = currentDayEvents;

    updateEventsTable();
    writeEventsToFile();
}

void DayView::slotEditEvent()
{
    QPushButton *buttonSender = qobject_cast<QPushButton*>(sender());

    EventEdit *newEvent = new EventEdit(EventEdit::Edit, buttonSender->property("id").toInt(), m_eventsTable->item(buttonSender->property("id").toInt(), 0)->text(), m_eventsTable->item(buttonSender->property("id").toInt(), 1)->text());
    QObject::connect(newEvent, SIGNAL(editedEventSaved(QJsonObject, int)), this, SLOT(slotEditEventInTable(QJsonObject, int)));
    newEvent->exec();
}

void DayView::slotEditEventInTable(QJsonObject event, int rowToEdit)
{
    QJsonArray currentDayEvents = m_eventsJson[m_date.toString("dd.MM.yyyy")].toArray();
    for (QJsonArray::iterator it = currentDayEvents.begin(); it != currentDayEvents.end(); ++it)
    {
        QJsonObject iteratorEvent = it->toObject();
        if (iteratorEvent["time"] == m_eventsTable->item(rowToEdit, 0)->text() &&
                iteratorEvent["description"] == m_eventsTable->item(rowToEdit, 1)->text())
        {
            currentDayEvents.erase(it);
            currentDayEvents.append(event);
            break;
        }
    }

    m_eventsJson[m_date.toString("dd.MM.yyyy")] = currentDayEvents;

    updateEventsTable();
    writeEventsToFile();
}

void DayView::slotCloseWindow()
{
    emit windowClosed();
    close();
}
