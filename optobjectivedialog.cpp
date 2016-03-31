#include "optobjectivedialog.h"
#include "ui_optobjectivedialog.h"

OptObjectiveDialog::OptObjectiveDialog(QWidget *parent) :
    QDialog(parent),
    uiOptObjective(new Ui::OptObjectiveDialog){
    uiOptObjective->setupUi(this);
    this->setWindowTitle("Optimizer - Objective");
}

OptObjectiveDialog::~OptObjectiveDialog(){
    delete uiOptObjective;
}

void OptObjectiveDialog::on_optObjectiveIsWellPropCheckBox_clicked(){
    if (uiOptObjective->optObjectiveIsWellPropCheckBox->isChecked()){ //!< If it is a well property, enable to specify
        uiOptObjective->optObjectiveWellLabel->setEnabled(true);
        uiOptObjective->optObjectiveWellEdit->setEnabled(true);
        uiOptObjective->optObjectiveWellComboBox->setEnabled(true);
    }
    else{
        uiOptObjective->optObjectiveWellLabel->setEnabled(false);
        uiOptObjective->optObjectiveWellEdit->setEnabled(false);
        uiOptObjective->optObjectiveWellComboBox->setEnabled(false);
    }

}

void OptObjectiveDialog::on_buttonBox_accepted(){
    qDebug() << "Clicked 'OK' in the Objective dialog.";
}

void OptObjectiveDialog::on_buttonBox_rejected(){
    qDebug() << "Clicked 'Cancel' in the Objective dialog.";
}

void OptObjectiveDialog::on_optObjTypeComboBox_currentTextChanged(const QString &objType){
    bool enabler = true;
    bool isWellPropEnabler = true;
    if (QString::compare(objType,"Weighted Sum") == 0) {
        enabler = true;

        if (uiOptObjective->optObjectiveIsWellPropCheckBox->isChecked()){ //the isWellProp need to stay disabled until this checkbox is checked.
            isWellPropEnabler = true;
        }
        else{
            isWellPropEnabler = false;
        }
    }
    else{
        enabler = false;
        isWellPropEnabler = false;
    }
    //Enables or disables these GUI elements(labels, spinboxes etc.) depending on the user choices
    uiOptObjective->optObjWeightSumCompLabel->setEnabled(enabler);
    uiOptObjective->optObjTimeStepLabel->setEnabled(enabler);
    uiOptObjective->optObjTimeStepSpinBox->setEnabled(enabler);
    uiOptObjective->optObjPropertyLabel->setEnabled(enabler);
    uiOptObjective->optObjPropertyComboBox->setEnabled(enabler);
    uiOptObjective->optObjCoeffisientLabel->setEnabled(enabler);
    uiOptObjective->optObjCoeffisientdSpinBox->setEnabled(enabler);
    uiOptObjective->optObjectiveIsWellPropCheckBox->setEnabled(enabler);

    uiOptObjective->optObjectiveWellLabel->setEnabled(isWellPropEnabler);
    uiOptObjective->optObjectiveWellEdit->setEnabled(isWellPropEnabler);
    uiOptObjective->optObjectiveWellComboBox->setEnabled(isWellPropEnabler);
}

void OptObjectiveDialog::setOptObjectiveType(Utilities::Settings::Optimizer::ObjectiveType obj_type){
    switch (obj_type){
    case Utilities::Settings::Optimizer::ObjectiveType::WeightedSum:
        uiOptObjective->optObjTypeComboBox->setCurrentText("Weighted Sum");
        break;
    default:
        break;
    }
}

