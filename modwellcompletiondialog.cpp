#include "modwellcompletiondialog.h"
#include "ui_modwellcompletiondialog.h"

ModWellCompletionDialog::ModWellCompletionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModWellCompletionDialog)
{
    ui->setupUi(this);
}

ModWellCompletionDialog::~ModWellCompletionDialog()
{
    delete ui;
}
