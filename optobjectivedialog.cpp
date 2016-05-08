#include "optobjectivedialog.h"
#include "ui_optobjectivedialog.h"

OptObjectiveDialog::OptObjectiveDialog(QWidget *parent) :
    QDialog(parent),
    uiOptObjective(new Ui::OptObjectiveDialog){
    setupDialog();
}

OptObjectiveDialog::~OptObjectiveDialog(){
    delete uiOptObjective;
}

void OptObjectiveDialog::setupDialog(){
    uiOptObjective->setupUi(this);
    this->setWindowTitle("Optimizer - Objective");
}


void OptObjectiveDialog::on_buttonBox_accepted(){
    qDebug() << "Clicked 'OK' in the Objective dialog.";
    //UPDATE - ALL INFORMATION HAS NEW STATE

    //updateObjectiveToUtilities(); directly set the variables...
}

void OptObjectiveDialog::on_buttonBox_rejected(){
    qDebug() << "Clicked 'Cancel' in the Objective dialog.";
    //RESET ALL INFORMATION TO FORMER STATE (use/load new_component_list)


}

void OptObjectiveDialog::on_optObjectiveIsFieldPropCheckBox_toggled(bool checked){
    //If it is a Field property, disable Well label and combobox
    uiOptObjective->optObjectiveWellLabel->setEnabled(!checked);
    uiOptObjective->optObjectiveWellComboBox->setEnabled(!checked);

}


QList<Utilities::Settings::Optimizer::Objective::WeightedSumComponent> *OptObjectiveDialog::new_weighted_sum_list() const{
    return new_weighted_sum_list_;
}

void OptObjectiveDialog::setNewWeightedSumList(QList<Utilities::Settings::Optimizer::Objective::WeightedSumComponent> *new_weighted_sum_list){
    new_weighted_sum_list_ = new_weighted_sum_list;
}


void OptObjectiveDialog::on_optObjTypeComboBox_currentTextChanged(const QString &obj_type){
    bool enabler = true;
    bool isWellPropEnabler = false;
    if (QString::compare(obj_type,"Weighted Sum") == 0) {
        enabler = true;
        
        if (uiOptObjective->optObjectiveIsFieldPropCheckBox->isChecked()){ //the isWellProp need to stay disabled until this checkbox is checked.
            isWellPropEnabler = false;
        }
        else{
            isWellPropEnabler = true;
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
    uiOptObjective->optObjectiveIsFieldPropCheckBox->setEnabled(enabler);

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
        uiOptObjective->optObjectiveIsFieldPropCheckBox->setChecked(false);
        uiOptObjective->optObjectiveWellComboBox->addItem(well_name);
        //OBS!!! remember to empty the combobox when opening another json file? donno if I can open another program/ it will replace data from the previous json, also add to combobox when adding wells in model.
    }
}

void  OptObjectiveDialog::setOptObjectiveIsFieldPropCheckBox(bool is_well_prop){
    //changed the code from having well check box to Field check box, but still has is_well_prop as input, since settings_->...->weighted_sum_list.value(i).is_well_prop has it
    uiOptObjective->optObjectiveIsFieldPropCheckBox->setChecked(!is_well_prop);
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
        comp_number = i + 1;
        uiOptObjective->optObjWeightedSumListWidget->addItem(QStringLiteral("Component %1").arg(comp_number));
        //passe på slik at informasjonen vises når man trykker på de forskjellige elementene.
        setOptObjectiveWeightedSumComponents( weighted_sum_list.value(i).coefficient, weighted_sum_list.value(i).property, weighted_sum_list.value(i).time_step);

        if (weighted_sum_list.value(i).is_well_prop){
           setOptObjectiveWellVariables( weighted_sum_list.value(i).is_well_prop,  weighted_sum_list.value(i).well );
        }
        else{
            setOptObjectiveIsFieldPropCheckBox( weighted_sum_list.value(i).is_well_prop );
        }
    }
}


void OptObjectiveDialog::on_optObjAddComponentButton_clicked(){
    //need to do something about temp_component_list
    comp_number = comp_number + 1;
    addComponent();

}


void OptObjectiveDialog::on_optObjRemoveComponentButton_clicked(){
    //remove element from the (also constraint_list... fix soon
    if(uiOptObjective->optObjWeightedSumListWidget->item(0) != NULL){
        delete uiOptObjective->optObjWeightedSumListWidget->currentItem();
       // initializeConPropertiesDialog();
        comp_number = comp_number - 1;
    }
    else{
        comp_number = 0;
    }
}

void OptObjectiveDialog::on_optObjWeightedSumListWidget_currentTextChanged(const QString &current_comp){
    //check for the current name, then update component information
    updateComponentInformation(current_comp);

    //use currentRowChanged instead of THIS METHOD??? currentItemChanged(&item);
}


void OptObjectiveDialog::updateComponentInformation(const QString current_comp){// tar inn int i stedet?
    // comp_numb
    //currentItem   what row, at? ItemAt()?
    //show current information from the current_comp-number
   // setOptObjectiveWeightedSumComponents();
    //temp_weighted_sum_list should be updated
}

void OptObjectiveDialog::addComponent(){
    // QListWidgetItem *new_item = new QListWidgetItem(QStringLiteral("Component %1").arg(comp_number), uiOptObjective->optObjWeightedSumListWidget);

        QListWidgetItem *new_item = new QListWidgetItem(QStringLiteral("Component %1").arg(comp_number));
        uiOptObjective->optObjWeightedSumListWidget->addItem(new_item);
        uiOptObjective->optObjWeightedSumListWidget->setCurrentItem(new_item);

      //  Utilities::Settings::Optimizer::Objective::WeightedSumComponent new_weighted_component;

      //  temp_weighted_sum_list_->append(new_weighted_component);

        //need to create a weighted sum component, this object need to be updated with information, when clicking update
}

//alternativ BRUK, siden den har currentRow.. som jeg bruker litt her...
void OptObjectiveDialog::on_optObjWeightedSumListWidget_currentRowChanged(int currentRow){

}



