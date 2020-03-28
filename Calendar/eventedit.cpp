#include "eventedit.h"
#include "ui_eventedit.h"

EventEdit::EventEdit(QDate *date, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EventEdit)
{
    ui->setupUi(this);
    m_date = new QDate(*date);

    connect(ui->m_cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->m_saveButton, SIGNAL(clicked()), this, SLOT(slotSaveEvent()));
}

EventEdit::~EventEdit()
{
    delete ui;
}

void EventEdit::slotSaveEvent()
{
    m_event = new QJsonObject();
    m_event->operator[]("time") = ui->m_timeEdit->text();
    m_event->operator[]("description") = ui->m_descriptionEdit->text();
    m_event->operator[]("date") = m_date->toString("dd.MM.yyyy");

    emit eventSaved(m_event);
    close();
}
