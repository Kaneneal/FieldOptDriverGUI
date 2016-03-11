#include "optdialog.h"
#include "ui_optparametersdialog.h"
#include "ui_optobjetivedialog.h"
#include "ui_optconstraintsdialog.h"

OptDialog::OptDialog(QWidget *parent) :
    QDialog(parent)
     {//, ui(new Ui::optDialog)
    setupOptParametersDialog();
    setupOptObjectiveDialog();
    setupOptConstraintsDialog();
}

OptDialog::~OptDialog(){
    //if they are deleted here, then they won't remember after open, close.. maybe delete in mainwindow...
    delete uiParameters;
    delete uiObjective;
    delete uiConstraints;
}

void OptDialog::setupOptParametersDialog(){
    uiParameters = new Ui::OptParametersDialog;
    optParametersDialog = new QDialog();
    uiParameters->setupUi(optParametersDialog);
    optParametersDialog->setWindowTitle("Optimizer - Parameter");
}

void OptDialog::setupOptObjectiveDialog(){
    uiObjective = new Ui::OptObjectiveDialog;
    optObjectiveDialog = new QDialog();
    uiObjective->setupUi(optObjectiveDialog);
    optObjectiveDialog->setWindowTitle("Optimizer - Objective");
}

void OptDialog::setupOptConstraintsDialog(){
    uiConstraints = new Ui::OptConstraintsDialog;
    optConstraintsDialog = new QDialog();
    uiConstraints->setupUi(optConstraintsDialog);
    optConstraintsDialog->setWindowTitle("Optimizer - Constraints");
}
QDialog *OptDialog::getOptParametersDialog() const{
    return optParametersDialog;
}
QDialog *OptDialog::getOptObjectiveDialog() const{
    return optObjectiveDialog;
}
QDialog *OptDialog::getOptConstraintsDialog() const{
    return optConstraintsDialog;
}


void OptDialog::on_optObjectiveIsWellPropCheckBox_clicked(){//does not work...
    if (uiObjective->optObjectiveIsWellPropCheckBox->isChecked()){ //!< If it is a well property, enable to specify
        uiObjective->optObjectiveWellLabel->setEnabled(true);
        uiObjective->optObjectiveWellEdit->setEnabled(true);
        uiObjective->optObjectiveWellComboBox->setEnabled(true);

    }
    else{
        uiObjective->optObjectiveWellLabel->setEnabled(false);
        uiObjective->optObjectiveWellEdit->setEnabled(false);
        uiObjective->optObjectiveWellComboBox->setEnabled(false);
    }
}

void OptDialog::on_buttonBox_accepted()
{

}
