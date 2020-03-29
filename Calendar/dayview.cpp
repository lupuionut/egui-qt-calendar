#include "dayview.h"

DayView::DayView(QWidget *parent) : QDialog(parent)
{
    m_eventsTable = new QTableWidget(this);
    m_tableHeader << "Time" << "Description";

    m_eventsTable->setRowCount(0);
    m_eventsTable->setColumnCount(2);
    m_eventsTable->insertRow(3);

    m_eventsTable->setHorizontalHeaderLabels(m_tableHeader);
    m_eventsTable->verticalHeader()->setVisible(false);

    m_eventsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_eventsTable->setSelectionMode(QAbstractItemView::NoSelection);

    m_eventsTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    m_eventsTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    m_addButton = new QPushButton(this);
    m_closeButton = new QPushButton(this);
    m_addButton->setText("Add new");
    m_closeButton->setText("Close");
    m_addButton->setToolTip("Add new event");
    m_closeButton->setToolTip("Close window");

    m_layout = new QVBoxLayout(this);
    m_buttonLayout = new QHBoxLayout(this);
    m_buttonLayout->addWidget(m_addButton);
    m_buttonLayout->addStretch();
    m_buttonLayout->addWidget(m_closeButton);
    m_buttonLayout->setSpacing(80);
    m_layout->addWidget(m_eventsTable);
    m_layout->addLayout(m_buttonLayout);
    setLayout(m_layout);

    m_date = QDate(1999, 11, 20);
    setWindowTitle(m_date.toString("yyyy-MM-dd"));

    connect(m_closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(m_addButton, SIGNAL(clicked()), this, SLOT(slotAddEvent()));
    connect(m_closeButton, SIGNAL(clicked()), this, SLOT(slotUpdateFile()));

    readEventsFromFile();
    m_eventsTable->sortByColumn(0,Qt::AscendingOrder);
}

bool DayView::readEventsFromFile()
{
    QFile loadFile("../Calendar/events.json");

    if (!loadFile.open(QIODevice::ReadOnly))
    {
        qWarning("Failed to open file.");
        return false;
    }

    QByteArray eventsData = loadFile.readAll();
    loadFile.close();
    eventsJson = QJsonDocument(QJsonDocument::fromJson(eventsData)).object();
    QJsonArray eventsArray = eventsJson[m_date.toString("dd.MM.yyyy")].toArray();

    for (int i = 0; i < eventsArray.size(); i++)
    {
        QJsonObject singleEvent = eventsArray[i].toObject();
        int rowCount = m_eventsTable->rowCount();
        m_eventsTable->insertRow(rowCount);
        m_eventsTable->setItem(rowCount, 0, new QTableWidgetItem(singleEvent["time"].toString()));
        m_eventsTable->setItem(rowCount, 1, new QTableWidgetItem(singleEvent["description"].toString()));

        QWidget *rowButtons = new QWidget(m_eventsTable);
        QHBoxLayout *rowButtonLayout = new QHBoxLayout(rowButtons);
        QPushButton *editButton = new QPushButton(rowButtons);
        editButton->setText("Edit");
        QPushButton *deleteButton = new QPushButton(rowButtons);
        deleteButton->setText("Delete");
        rowButtonLayout->addStretch();
        rowButtonLayout->addWidget(editButton);
        rowButtonLayout->addWidget(deleteButton);
        rowButtonLayout->setAlignment(deleteButton, Qt::AlignRight);
        rowButtonLayout->setAlignment(editButton, Qt::AlignRight);
        rowButtonLayout->setSpacing(1);
        rowButtonLayout->setContentsMargins(100, 0, 5, 0);
        m_eventsTable->setCellWidget(rowCount, 1, rowButtons);
    }

    return true;
}

void DayView::slotAddEvent()
{
    EventEdit *newEvent = new EventEdit();
    QObject::connect(newEvent, SIGNAL(eventSaved(QJsonObject)), this, SLOT(slotAddEventToTable(QJsonObject)));
    newEvent->exec();
}

void DayView::slotAddEventToTable(QJsonObject event)
{
    int rowCount = m_eventsTable->rowCount();
    m_eventsTable->insertRow(rowCount);
    m_eventsTable->setItem(rowCount, 0, new QTableWidgetItem(event["time"].toString()));
    m_eventsTable->setItem(rowCount, 1, new QTableWidgetItem(event["description"].toString()));
    m_eventsTable->sortByColumn(0,Qt::AscendingOrder);
}

void DayView::slotUpdateFile()
{
    int rowCount = m_eventsTable->rowCount();
    QJsonArray updatedEvents;

    for (int i = 0; i < rowCount; i++)
    {
        QJsonObject event;
        event["time"] = m_eventsTable->item(i, 0)->text();
        event["description"] = m_eventsTable->item(i, 1)->text();
        updatedEvents.append(event);
    }

    eventsJson[m_date.toString("dd.MM.yyyy")] = updatedEvents;

    QFile saveFile("../Calendar/events.json");
    if (!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Failed to open file.");
        return;
    }

    QJsonDocument saveDoc(eventsJson);
    saveFile.write(saveDoc.toJson());
    saveFile.close();
}
