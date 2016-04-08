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

void OptParametersDialog::setOptParametersVariables(Utilities::Settings::Optimizer::Parameters parameters){
    uiOptParameters->paramMaxEvalSpinBox->setValue(parameters.max_evaluations);
    uiOptParameters->paramInitStepdoubleSpinBox->setValue(parameters.initial_step_length);
    uiOptParameters->paramMinStepdoubleSpinBox->setValue(parameters.minimum_step_length);
}

void OptParametersDialog::on_buttonBox_accepted(){
    qDebug() << "Clicked 'OK' in the Parameters dialog.";
}

void OptParametersDialog::on_buttonBox_rejected(){
    qDebug() << "Clicked 'Cancel' in the Parameters dialog.";
}
