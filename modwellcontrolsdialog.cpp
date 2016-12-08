#include "modwellcontrolsdialog.h"
#include "ui_modwellcontrolsdialog.h"

#include <QDebug>

ModWellControlsDialog::ModWellControlsDialog(QWidget *parent) :
    QDialog(parent),
    uiControls(new Ui::ModWellControlsDialog){
    setupDialog();
}

ModWellControlsDialog::~ModWellControlsDialog(){
    delete uiControls;
}

void ModWellControlsDialog::setModWellControlsVariables(QList<Utilities::Settings::Model::Well> wells){
    //skal også ta inn selected items number, så controls.at(numb).
    if(wells.at(0).controls.at(0).state == Utilities::Settings::Model::WellOpen){
        uiControls->mWellControlStateOpen->setChecked(true);
        uiControls->mWellControlStateShut->setChecked(false);
        qDebug() << "SetModWellControlsVariables kjørt og status state var open.";
    }

    switch (wells.at(0).controls.at(0).state) {
    case Utilities::Settings::Model::WellOpen:
        uiControls->mWellControlStateOpen->setChecked(true);
      //  uiControls->mWellControlStateShut->setChecked(false);
        break;
    case Utilities::Settings::Model::WellShut:
        uiControls->mWellControlStateShut->setChecked(true);
        break;
    default:
        break;
    }

    switch (wells.at(0).controls.at(0).control_mode) {
    case Utilities::Settings::Model::ControlMode::BHPControl:
        uiControls->mWellControlModeComboBox->setCurrentText("BHP");
        break;
    case Utilities::Settings::Model::ControlMode::RateControl:
        uiControls->mWellControlModeComboBox->setCurrentText("Rate");
        break;
    default:
        break;
    }

}



void ModWellControlsDialog::setupDialog(){
    uiControls->setupUi(this);
    this->setWindowTitle("Model – Well – Controls");
    setToolTips();
}

void ModWellControlsDialog::setToolTips(){
    uiControls->wellControlButtonBox->setToolTip("'OK' to accept (new) control values. 'Cancel' to regret changes.");
    uiControls->mWellControlModeComboBox->setToolTip("The well's control mode");
    uiControls->mWellControlBHPSpinBox->setToolTip("Bottom Hole Pressure");
    uiControls->mWellControlRateSpinBox->setToolTip("Rate");

}

void ModWellControlsDialog::setTimeSteps(QStringList time_steps){
    // eventuelt gjøre om, ta inn QList<int> og deretter fikse her?!?
    uiControls->mWellControlTimeStepComboBox->insertItems(0, time_steps);
    uiControls->mWellControlTimeStepComboBox->setCurrentIndex(0);

    //remember to clear this combobox when.
    //COnnect these two combobox and control times in mainwindow???
}

void ModWellControlsDialog::on_mWellControlModeComboBox_currentTextChanged(const QString &control_mode){
    //uiControl->mWellControlModeComboBox->currentText()
    if (QString::compare(control_mode, "Rate") == 0){
        uiControls->mWellControlRateLabel->setEnabled(true);
        uiControls->mWellControlRateSpinBox->setEnabled(true);
        uiControls->mWellControlBHPLabel->setEnabled(false);
        uiControls->mWellControlBHPSpinBox->setEnabled(false);
    }
    if (QString::compare(control_mode, "BHP") == 0){

        uiControls->mWellControlBHPLabel->setEnabled(true);
        uiControls->mWellControlBHPSpinBox->setEnabled(true);
        uiControls->mWellControlRateLabel->setEnabled(false);
        uiControls->mWellControlRateSpinBox->setEnabled(false);
    }
}

void ModWellControlsDialog::on_wellControlButtonBox_accepted(){
    // Update and accept parameters to temp fields
    qDebug() << "Clicked 'OK' in the Controls dialog (accepted)";
    // Send newest variables values to settings object.
}

void ModWellControlsDialog::on_wellControlButtonBox_rejected(){
    //Reset all parameters to the temp saved value

    qDebug() << "Clicked 'Cancel' in the Controls dialog (rejected)";
    //Reset to previous state.
}


