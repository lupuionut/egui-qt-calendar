#include "dayview.h"

DayView::DayView(QWidget *parent) : QDialog(parent)
{
    m_eventsTable = new QTableWidget(this);
    m_tableHeader << "Time" << "Description";

    m_eventsTable->setRowCount(3); // dummy rows
    m_eventsTable->setColumnCount(2);

    m_eventsTable->setHorizontalHeaderLabels(m_tableHeader);
    m_eventsTable->verticalHeader()->setVisible(false);
    m_eventsTable->setWindowTitle("*selected date*"); // placeholder title

    m_eventsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_eventsTable->setSelectionMode(QAbstractItemView::NoSelection);

    m_eventsTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    m_eventsTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    m_addButton = new QPushButton(this);
    m_saveButton = new QPushButton(this);
    m_addButton->setText("Add");
    m_saveButton->setText("Save");
    m_addButton->setToolTip("Add new event");
    m_saveButton->setToolTip("Save events");

    m_layout = new QVBoxLayout(this);
    m_buttonLayout = new QHBoxLayout(this);
    m_buttonLayout->addWidget(m_addButton);
    m_buttonLayout->addWidget(m_saveButton);
    m_layout->addWidget(m_eventsTable);
    m_layout->addLayout(m_buttonLayout);
    setLayout(m_layout);
}
