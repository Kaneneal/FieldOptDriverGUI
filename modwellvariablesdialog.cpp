#include "modwellvariablesdialog.h"
#include "ui_modwellvariablesdialog.h"

ModWellVariablesDialog::ModWellVariablesDialog(QWidget *parent) :
    QDialog(parent),
    uiVariables(new Ui::ModWellVariablesDialog){
    uiVariables->setupUi(this);

    this->setWindowTitle("Model – Well – Variables");
    uiVariables->mWellVariablesNameEdit->setPlaceholderText("Variable name");
    setToolTips();
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

void ModWellVariablesDialog::setToolTips(){
    uiVariables->buttonBox->setToolTip("'OK' to accept (new) well variables values. 'Cancel' to regret changes.");
    uiVariables->mWellVariablesNameEdit->setToolTip("Name of (current) variable");
    uiVariables->mWellVariableListWidget->setToolTip("List of variable(s) (items)");

    uiVariables->mWellVariablesAddButton->setToolTip("Add variable (item) to the list.");
    uiVariables->mWellVariablesRemoveButton->setToolTip("Remove selected variable (item) from the list.");
}
