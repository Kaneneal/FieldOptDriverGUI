#include "modwellvariablesdialog.h"
#include "ui_modwellvariablesdialog.h"

ModWellVariablesDialog::ModWellVariablesDialog(QWidget *parent) :
    QDialog(parent),
    uiVariables(new Ui::ModWellVariablesDialog){
    uiVariables->setupUi(this);

    this->setWindowTitle("Model - Well - Variables");

}

ModWellVariablesDialog::~ModWellVariablesDialog(){
    delete uiVariables;
}

void ModWellVariablesDialog::on_buttonBox_accepted(){
    qDebug() << "Clicked 'OK' in the Model Well Variables dialog (accepted)";
    // Send new updated info to settings object.
}

void ModWellVariablesDialog::on_buttonBox_rejected(){
    qDebug() << "Clicked 'Cancel' in the Model Well Variables dialog(rejected)";
    // Reset GUI to previous state.
}
