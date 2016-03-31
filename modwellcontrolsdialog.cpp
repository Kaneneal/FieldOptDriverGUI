#include "modwellcontrolsdialog.h"
#include "ui_modwellcontrolsdialog.h"

#include <QDebug>

ModWellControlsDialog::ModWellControlsDialog(QWidget *parent) :
    QDialog(parent),
    uiControls(new Ui::ModWellControlsDialog){
    uiControls->setupUi(this);
    this->setWindowTitle("Model - Well - Controls");
}

ModWellControlsDialog::~ModWellControlsDialog(){
    delete uiControls;
}

void ModWellControlsDialog::on_mWellControlModeComboBox_currentTextChanged(const QString &controlMode){
    //uiControl->mWellControlModeComboBox->currentText()
    if (QString::compare(controlMode, "Rate") == 0){
        uiControls->mWellControlRateLabel->setEnabled(true);
        uiControls->mWellControlRateSpinBox->setEnabled(true);
        uiControls->mWellControlBHPLabel->setEnabled(false);
        uiControls->mWellControlBHPSpinBox->setEnabled(false);
    }
    if (QString::compare(controlMode, "BHP") == 0){

        uiControls->mWellControlBHPLabel->setEnabled(true);
        uiControls->mWellControlBHPSpinBox->setEnabled(true);
        uiControls->mWellControlRateLabel->setEnabled(false);
        uiControls->mWellControlRateSpinBox->setEnabled(false);
    }
}

void ModWellControlsDialog::on_wellControlButtonBox_accepted(){
    // Update and accept parameters to temp fields
    qDebug() << "Clicked 'OK' in the Controls dialog (accepted)";
}

void ModWellControlsDialog::on_wellControlButtonBox_rejected(){
    //Reset all parameters to the temp saved value

    qDebug() << "Clicked 'Cancel' in the Controls dialog (rejected)";
}
