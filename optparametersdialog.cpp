#include "optparametersdialog.h"
#include "ui_optparametersdialog.h"

OptParametersDialog::OptParametersDialog(QWidget *parent) :
    QDialog(parent),
    uiOptParameters(new Ui::OptParametersDialog){
    uiOptParameters->setupUi(this);
    this->setWindowTitle("Optimizer - Parameters");
}

OptParametersDialog::~OptParametersDialog(){
    delete uiOptParameters;
}

void OptParametersDialog::setOptParametersVariables(int max_evaluations, double initial_step_length, double minimum_step_length){
    uiOptParameters->paramMaxEvalSpinBox->setValue(max_evaluations);
    uiOptParameters->paramInitStepdoubleSpinBox->setValue(initial_step_length);
    uiOptParameters->paramMinStepdoubleSpinBox->setValue(minimum_step_length);
}

void OptParametersDialog::on_buttonBox_accepted(){
    qDebug() << "Clicked 'OK' in the Parameters dialog.";
}

void OptParametersDialog::on_buttonBox_rejected(){
    qDebug() << "Clicked 'Cancel' in the Parameters dialog.";
}
