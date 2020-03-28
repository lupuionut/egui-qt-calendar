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
    m_eventsTable->setWindowTitle("*selected date*"); // placeholder title

    m_eventsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_eventsTable->setSelectionMode(QAbstractItemView::NoSelection);

    m_eventsTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    m_eventsTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    m_addButton = new QPushButton(this);
    m_closeButton = new QPushButton(this);
    m_addButton->setText("Add");
    m_closeButton->setText("Close");
    m_addButton->setToolTip("Add new event");
    m_closeButton->setToolTip("Close window");

    m_layout = new QVBoxLayout(this);
    m_buttonLayout = new QHBoxLayout(this);
    m_buttonLayout->addWidget(m_addButton);
    m_buttonLayout->addWidget(m_closeButton);
    m_buttonLayout->setSpacing(80);
    m_layout->addWidget(m_eventsTable);
    m_layout->addLayout(m_buttonLayout);
    setLayout(m_layout);

    readEventsFromFile();
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
    QJsonObject eventsJson = QJsonDocument(QJsonDocument::fromJson(eventsData)).object();
    QJsonArray eventsArray = eventsJson["events"].toArray();

    for (int i = 0; i < eventsArray.size(); i++)
    {
        QJsonObject singleEvent = eventsArray[i].toObject();
        if (singleEvent["date"].toString() == "20.11.1999") // fixed placeholder date
        {
            int rowCount = m_eventsTable->rowCount();
            m_eventsTable->insertRow(rowCount);
            m_eventsTable->setItem(rowCount, 0, new QTableWidgetItem(singleEvent["time"].toString()));
            m_eventsTable->setItem(rowCount, 1, new QTableWidgetItem(singleEvent["description"].toString()));
        }
    }

    return true;
}
