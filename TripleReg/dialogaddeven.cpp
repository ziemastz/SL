#include "dialogaddeven.h"
#include "ui_dialogaddeven.h"

DialogAddEven::DialogAddEven(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddEven)
{
    ui->setupUi(this);
}

DialogAddEven::~DialogAddEven()
{
    delete ui;
}

void DialogAddEven::on_cancel_pushButton_clicked()
{
    close();
}


void DialogAddEven::on_add_pushButton_clicked()
{
    TripleRegLogbookModel logbook;
    logbook.id =0;
    logbook.type = ui->type_comboBox->currentText();
    logbook.description = ui->desciption_plainTextEdit->toPlainText();
    logbook.root = "Logbook";
    logbook.element = "-";
    logbook.userId = Settings::loggedUserId();
    DatabaseStarlingLab db;
    if(!db.insert(&logbook)) {
        QMessageBox::warning(this,tr("Database"),tr("Inserting error from database!\nPlease contact the administrator."));
        return;
    }
    accept();
}

