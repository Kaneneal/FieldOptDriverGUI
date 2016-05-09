#include "optparametersdialog.h"
#include "ui_optparametersdialog.h"

OptParametersDialog::OptParametersDialog(QWidget *parent) :
    QDialog(parent),
    uiOptParameters(new Ui::OptParametersDialog){
    setupDialog();
}

OptParametersDialog::~OptParametersDialog(){
    delete uiOptParameters;
}

// JEG TROR IKKE JEG SENDER INFORMASJONEN RIKTIG TILBAKE TIL "EINAR" og PARAMETERS
// DEN ER VEL IKKE EN POINTER NÅ?  ELLER?!?!?
void OptParametersDialog::setOptParametersVariables(Utilities::Settings::Optimizer::Parameters parameters){
    parameters_ = parameters;
    uiOptParameters->paramMaxEvalSpinBox->setValue(parameters.max_evaluations);
    uiOptParameters->paramInitStepdoubleSpinBox->setValue(parameters.initial_step_length);
    uiOptParameters->paramMinStepdoubleSpinBox->setValue(parameters.minimum_step_length);
}

void OptParametersDialog::on_buttonBox_accepted(){
    qDebug() << "Clicked 'OK' in the Parameters dialog.";
    updateParametersToUtilities();
}

void OptParametersDialog::on_buttonBox_rejected(){
    qDebug() << "Clicked 'Cancel' in the Parameters dialog.";
    setOptParametersVariables(parameters_);
}

void OptParametersDialog::setupDialog(){
    uiOptParameters->setupUi(this);
    this->setWindowTitle("Optimizer - Parameters");
    setToolTips();
    initializeParametersObject();
}

void OptParametersDialog::setToolTips(){
    // tool tips for the spin boxes, and variables
    uiOptParameters->buttonBox->setToolTip("'OK' to accept (new) variables values. 'Cancel' to regret changes.");
    uiOptParameters->paramMaxEvalSpinBox->setToolTip("Type 'max evaluations' wanted.");
    uiOptParameters->paramInitStepdoubleSpinBox->setToolTip("Type the 'initial step length'.");
    uiOptParameters->paramMinStepdoubleSpinBox->setToolTip("Type the 'minimum step length'.");
}

void OptParametersDialog::initializeParametersObject(){
    parameters_.max_evaluations = 0;
    parameters_.initial_step_length = 0.0;
    parameters_.minimum_step_length = 0.0;
}

void OptParametersDialog::updateParametersToUtilities(){
    parameters_.max_evaluations = uiOptParameters->paramMaxEvalSpinBox->value();
    parameters_.initial_step_length = uiOptParameters->paramInitStepdoubleSpinBox->value();
    parameters_.minimum_step_length = uiOptParameters->paramMinStepdoubleSpinBox->value();
}

