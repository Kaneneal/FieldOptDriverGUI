#include "mwelldialog.h"
#include "ui_mwelldialog.h"


MWellDialog::MWellDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MWellDialog){
    setupMWellDialog();
    setupMWellControlDialog();
    setupMWellCompletionsDialog();
    setupMWellVariablesDialog();


}

MWellDialog::~MWellDialog(){
    delete ui;
}



void MWellDialog::setupMWellDialog(){
     ui->setupUi(this);
     this->setWindowTitle("Model - Well");
}

void MWellDialog::setupMWellControlDialog(){
    uiControl = new Ui::MWellControlDialog;
    mWellControlDialog = new QDialog();
    uiControl->setupUi(mWellControlDialog);
    mWellControlDialog->setWindowTitle("Model - Well - Controls");
}

void MWellDialog::setupMWellCompletionsDialog(){
    uiCompletions = new Ui::MWellCompletionsDialog;
    mWellCompletionsDialog = new QDialog();
    uiCompletions->setupUi(mWellCompletionsDialog);
    mWellCompletionsDialog->setWindowTitle("Model - Well - Completions");
}

void MWellDialog::setupMWellVariablesDialog(){
    uiVariables = new Ui::MWellVariablesDialog;
    mWellVariablesDialog = new QDialog();
    uiVariables->setupUi(mWellVariablesDialog);
    mWellVariablesDialog->setWindowTitle("Model - Well - Variables");
}

//------------- Model Well -----------------------------------------------------------------------------|


void MWellDialog::on_mWellSetControlsButton_clicked(){
    mWellControlDialog->setModal(true);
    mWellControlDialog->exec();
}

void MWellDialog::on_mWellSpecVariablesCheckBox_clicked(){
    if (ui->mWellSpecVariablesCheckBox->isChecked()){
        ui->mWellSetVariablesButton->setEnabled(true);
    }
    else{
        ui->mWellSetVariablesButton->setEnabled(false);
    }
}

//------------- END Model Well --------------------------------------------------------------------------|



//------------- Well Controls---------------------------------------------------------------------------|

void MWellDialog::on_mWellControlModeComboBox_currentTextChanged(const QString &controlMode){
    if (controlMode=="Rate"){
        uiControl->mWellControlRateLabel->setEnabled(true);
        uiControl->mWellControlRateSpinBox->setEnabled(true);
        uiControl->mWellControlBHPLabel->setEnabled(false);
        uiControl->mWellControlBHPSpinBox->setEnabled(false);
    }
    if (controlMode == "BHP"){

        uiControl->mWellControlBHPLabel->setEnabled(true);
        uiControl->mWellControlBHPSpinBox->setEnabled(true);
        uiControl->mWellControlRateLabel->setEnabled(false);
        uiControl->mWellControlRateSpinBox->setEnabled(false);
    }
}


void MWellDialog::on_mWellControlButtonBox_accepted(){
 // Update and accept parameters
}

void MWellDialog::on_mWellControlButtonBox_rejected(){ //!< what happens when press "Cancel" in "Controls"
    //Reset all parameters
}


//-------------END Well Controls------------------------------------------------------------------------|



void MWellDialog::on_mWellSetCompletionsButton_clicked(){
    mWellCompletionsDialog->setModal(true);
    mWellCompletionsDialog->exec();
}


void MWellDialog::on_mWellSetVariablesButton_clicked(){
    mWellVariablesDialog->setModal(true);
    mWellVariablesDialog->exec();
}


void MWellDialog::on_mWellDefinitionTypeComboBox_currentTextChanged(const QString &defType){
    if (defType=="Well Blocks"){
        ui->mWellBlocksArraysLabel->setEnabled(true);
        //ui->mWellBOX->setEnabled(true);
        ui->mWellSplinePointsArraysLabel->setEnabled(false);
        //ui->mWellBOX->setEnabled(false);
    }
    if (defType == "Well Spline"){

        ui->mWellSplinePointsArraysLabel->setEnabled(true);
        //ui->mWellBOX->setEnabled(true);
        ui->mWellBlocksArraysLabel->setEnabled(false);
       // ui->mWellBOX->setEnabled(false);
    }
}
