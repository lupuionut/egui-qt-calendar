#include "eventedit.h"
#include "ui_eventedit.h"

EventEdit::EventEdit(EditMode editMode, int rowToEdit, QString time, QString description, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EventEdit)
{
    ui->setupUi(this);

    m_rowToEdit = rowToEdit;
    m_editMode = editMode;

    // validator which accepts only time in HH:MM format
    QValidator *timeValidator = new QRegExpValidator(QRegExp("^([0-1 ][0-9 ]|[2 ][0-3 ]):([0-5 ][0-9 ])$"));
    ui->m_timeEdit->setValidator(timeValidator);

    if (editMode == Add)
        this->setWindowTitle("Add event");
    else
    {
        ui->m_timeEdit->setText(time);
        ui->m_descriptionEdit->setText(description);
    }

    // connecting buttons
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

    if (m_editMode == Add)
        emit newEventSaved(m_event);
    else
        emit editedEventSaved(m_event, m_rowToEdit);
    close();
}
