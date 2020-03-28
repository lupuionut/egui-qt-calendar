#include "eventedit.h"
#include "ui_eventedit.h"

EventEdit::EventEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EventEdit)
{
    ui->setupUi(this);
}

EventEdit::~EventEdit()
{
    delete ui;
}
