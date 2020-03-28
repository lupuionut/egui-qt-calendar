#include "eventedit.h"
#include "ui_eventedit.h"

EventEdit::EventEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EventEdit)
{
    ui->setupUi(this);

    connect(ui->m_cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->m_saveButton, SIGNAL(clicked()), this, SLOT(slotSaveEvent()));
}

EventEdit::~EventEdit()
{
    delete ui;
}

void EventEdit::slotSaveEvent()
{
    m_event["time"] = ui->m_timeEdit->text();
    m_event["description"] = ui->m_descriptionEdit->text();

    emit eventSaved(m_event);
    close();
}
