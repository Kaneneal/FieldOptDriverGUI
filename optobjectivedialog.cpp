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


void OptObjectiveDialog::on_buttonBox_accepted(){
    qDebug() << "Clicked 'OK' in the Objective dialog.";
}

void OptObjectiveDialog::on_buttonBox_rejected(){
    qDebug() << "Clicked 'Cancel' in the Objective dialog.";
}


void OptObjectiveDialog::on_optObjectiveIsWellPropCheckBox_toggled(bool checked){
    if (checked){ //!< If it is a well property, enable to specify
        uiOptObjective->optObjectiveWellLabel->setEnabled(true);
        uiOptObjective->optObjectiveWellComboBox->setEnabled(true);
    }
    //mener man kan putte checked istedenfor true/false
    else{
        uiOptObjective->optObjectiveWellLabel->setEnabled(false);
        uiOptObjective->optObjectiveWellComboBox->setEnabled(false);
    }
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

void OptObjectiveDialog::setOptObjectiveWellVariables(bool is_well_prop, const QString &well_name){
   // Have a double check here with testing if is_well_prop is true, then set well_name...
    if (is_well_prop == true){
        uiOptObjective->optObjectiveIsWellPropCheckBox->setChecked(is_well_prop);
        uiOptObjective->optObjectiveWellComboBox->addItem(well_name);
        //OBS!!! remember to empty the combobox when opening another json file? donno if I can open another program/ it will replace data from the previous json, also add to combobox when adding wells in model.
    }
}

void  OptObjectiveDialog::setOptObjectiveIsWellPropCheckBox(bool is_well_prop){
    uiOptObjective->optObjectiveIsWellPropCheckBox->setChecked(is_well_prop);
}

void OptObjectiveDialog::setOptObjectiveWeightedSumComponents(double coefficient, const QString &property, int time_step){ // use if only one element in the list? or use as a private method
    uiOptObjective->optObjCoeffisientdSpinBox->setValue(coefficient);
    uiOptObjective->optObjTimeStepSpinBox->setValue(time_step);

    if(QString::compare(property, "CumulativeOilProduction") == 0){
        uiOptObjective->optObjPropertyComboBox->setCurrentText("Cumulative Oil Production");
    }

    if(QString::compare(property, "CumulativeWellWaterProduction") == 0){
        uiOptObjective->optObjPropertyComboBox->setCurrentText("Cumulative Well Water Production");
    }
}

void OptObjectiveDialog::setOptObjectiveWeightedSumComponents(const QList<Utilities::Settings::Optimizer::Objective::WeightedSumComponent> weighted_sum_list){

    for (int i=0; i < weighted_sum_list.length(); i++){
        // Får to nye objective dialogs opp uten informasjon, og man kan bytte fra dem.
        // OptObjectiveDialog *moreObjectives = new OptObjectiveDialog();, create list of dialogs? use that list, and uiOptObjective-> for hver iterasjon?
        // moreObjectives->show();
        // moreObjectives->activateWindow();

        OptObjectiveDialog::setOptObjectiveWeightedSumComponents( weighted_sum_list.value(i).coefficient, weighted_sum_list.value(i).property, weighted_sum_list.value(i).time_step);

        if (weighted_sum_list.value(i).is_well_prop){
           setOptObjectiveWellVariables( weighted_sum_list.value(i).is_well_prop,  weighted_sum_list.value(i).well );
        }
        else{
            setOptObjectiveIsWellPropCheckBox( weighted_sum_list.value(i).is_well_prop );
        }
    }
}


