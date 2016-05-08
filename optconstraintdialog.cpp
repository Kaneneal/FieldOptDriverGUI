#include "optconstraintdialog.h"
#include "ui_optconstraintdialog.h"

OptConstraintDialog::OptConstraintDialog(QWidget *parent) :
    QDialog(parent),
    uiOptConstraint(new Ui::OptConstraintDialog){
    setupDialog();

}

OptConstraintDialog::~OptConstraintDialog(){
    delete uiOptConstraint;
}


void OptConstraintDialog::on_buttonBox_accepted(){
    qDebug() << "Clicked 'OK' in the Constraint dialog.";
    //UPDATE - ALL INFORMATION HAS NEW STATE
}

void OptConstraintDialog::on_buttonBox_rejected(){
    qDebug() << "Clicked 'Cancel' in the Constraint dialog.";
    //RESET ALL INFORMATION TO FORMER STATE
}

void OptConstraintDialog::setupDialog(){
    uiOptConstraint->setupUi(this);
    this->setWindowTitle("Optimizer - Constraints");
    setToolTips();

    connect(uiOptConstraint->optConstraintListWidget,SIGNAL(currentTextChanged(QString)), uiOptConstraint->optConItemSelectedLabel,SLOT(setText(QString)));
   //connect(uiOptConstraint->optConstraintListWidget,SIGNAL(currentTextChanged(QString)), uiOptConstraint->optConChangeNameEdit, SLOT(setText(QString)));
    initializeConPropertiesDialog();
}

void OptConstraintDialog::setToolTips(){
    uiOptConstraint->optConWellNameComboBox->setToolTip("Name of well");
    uiOptConstraint->optConstraintListWidget->setToolTip("List of current well's constraints");

    //MORE
}

void OptConstraintDialog::setConItemInformation(int currItem){
    switch (local_constraints_list_->at(currItem).type) {
    case Utilities::Settings::Optimizer::ConstraintType::BHP: //OR Rate.. then
        //  max, min
        uiOptConstraint->optConTypeComboBox->setCurrentText("BHP");
        uiOptConstraint->optConMaxdSpinBox->setValue(local_constraints_list_->at(currItem).max);
        uiOptConstraint->optConMindSpinBox->setValue(local_constraints_list_->at(currItem).min);
        break;

    case Utilities::Settings::Optimizer::ConstraintType::Rate:
        //  max, min
        uiOptConstraint->optConTypeComboBox->setCurrentText("Rate");
        uiOptConstraint->optConMaxdSpinBox->setValue(local_constraints_list_->at(currItem).max);
        uiOptConstraint->optConMindSpinBox->setValue(local_constraints_list_->at(currItem).min);
        break;

    case Utilities::Settings::Optimizer::ConstraintType::SplinePoints:
        uiOptConstraint->optConTypeComboBox->setCurrentText("Well Spline Points");
        setOptConSplinePointsType(currItem);
        break;

    default:
        qDebug() << "default case in setConItemInformation ";
        break;
    }
}



void OptConstraintDialog::setOptConSplinePointsType(int currItem){
        //think I can remove the comments here: ->
        //uiOptConstraint ->optConSplinePointsTypeLabel->setEnabled(true);
        //name is added to a list, then there should be an action, when that element is selected show the belonging information.
       // uiOptConstraint->optConSplinePointsTypeComboBox->setEnabled(true);

        switch (local_constraints_list_->at(currItem).spline_points_type) {

        case Utilities::Settings::Optimizer::ConstraintWellSplinePointsType::MaxMin :
            uiOptConstraint->optConSplinePointsTypeComboBox->setCurrentText("MaxMin");
        //    uiOptConstraint->optConSplinePointsLimitsLabel->setEnabled(true); skal ikke behøve å ha den her
            //Fix Limits... realCoordinate .x, .y, .z  ... for (int i = 0;.. create method?
           /* for (int j = 0; j < total; j++) {
                local_constraints_list_.at(i).spline_points_limits.at(j).max.x;
                local_constraints_list_.at(i).spline_points_limits.at(j).max.y;
                local_constraints_list_.at(i).spline_points_limits.at(j).max.z;
                local_constraints_list_.at(i).spline_points_limits.at(j).min.x;
                local_constraints_list_.at(i).spline_points_limits.at(j).min.y;
                local_constraints_list_.at(i).spline_points_limits.at(j).min.z;
            }*/
            break;

        case Utilities::Settings::Optimizer::ConstraintWellSplinePointsType::Function:
            uiOptConstraint->optConSplinePointsTypeComboBox->setCurrentText("Function");
            uiOptConstraint->optConSplinePointsFunctionEdit->setText(local_constraints_list_->at(currItem).well_spline_points_function);
            break;

        default:
            break;
        }

}

//showdialogsmethod som brukes i mainwindow.cpp når constraints-knappen blir trykket. kjører for(int i=0;...){ ->show(), activateWindow()

void OptConstraintDialog::setOptConstraintsVariables(QList<Utilities::Settings::Optimizer::Constraint> *constraints){ //skal constraints ha peker?
    //dele opp i flere metoder....
    setOptLocalConstraintsList(constraints);

    //Mulig dette kan bli én metode: initializeList(QList<Utilities::....> *constraints)
    int i = 0;
    QStringList well_list; //kan få den fra "offisiell" liste fra models, eller gå igjennom
    while(i < local_constraints_list_->size()){

        if (!well_list.contains(local_constraints_list_->at(i).well)){
             well_list.append(constraints->at(i).well);
        }

       i++;
    }
    uiOptConstraint->optConWellNameComboBox->addItems(well_list);
} //end method

// ta inn en liste? og/eller ta inn type etc. for så å kjøre if og kjøre metoder inni ettersom hva det blir sconst QString &well_name );//!< For when is_well_prop == true, then set well_name.

void OptConstraintDialog::on_optConAddButton_clicked(){
// add element with the belonging information
   //there has to be text in the wellcombobox....
    //if(uiOptConstraint->optConWellNameComboBox->size() > 0 ){//&& there is text in the edit-field which is not existing (if exist, then selected has to be the one with the same name) )
       // uiOptConstraint->optConstraintListWidget->addItem(textInLineEdit);
    //}
    //HVA hvis man legger personlig legger til et navn, så importerer? Kommer ikke det elementetmed? Jo, men kan ikke legge til med knappen...
    QList<QListWidgetItem *> existing_items = uiOptConstraint->optConstraintListWidget->findItems(uiOptConstraint->optConChangeNameEdit->text(),Qt::MatchExactly);
    if ((existing_items.size() == 0) && (uiOptConstraint->optConWellNameComboBox->count() > 0 )){ //no similar items in list, and it need to exist well names in combo box
        QListWidgetItem *new_item = new QListWidgetItem(uiOptConstraint->optConChangeNameEdit->text(), uiOptConstraint->optConstraintListWidget);
        uiOptConstraint->optConstraintListWidget->setCurrentItem(new_item);

        //Utilities::Settings::Optimizer::Constraint new_constraint;
       // new_constraint.name = uiOptConstraint->optConstraintListWidget->currentItem()->text();
        //local_constraints_list_->append( uiOptConstraint->optConstraintListWidget->currentItem());

        //need to create a constraint object, this object need to be updated with information, when clicking update
    }


}

void OptConstraintDialog::on_optConRemoveButton_clicked(){
    //remove element from the (also constraint_list... fix soon
    if(uiOptConstraint->optConstraintListWidget->item(0) != NULL){
        delete uiOptConstraint->optConstraintListWidget->currentItem();
        initializeConPropertiesDialog();
    }
}

void OptConstraintDialog::on_optConWellNameComboBox_currentTextChanged(const QString &well_name){
    //KJØR DENNE METODEN -> ( i mainwindow må det sendes med constraints/lista, den må så settes som en lokal liste i denne dialogen.
    uiOptConstraint->optConstraintListWidget->clear();
    QStringList constraint_name_list;
   // constraint_name_list.clear(); skal være unødvendig

    QString current_well;
    QString current_name;
    int i = 0;
    while(i < local_constraints_list_->size()){
        current_well = local_constraints_list_->at(i).well;
        current_name = local_constraints_list_->at(i).name;
        // current_name is added to constraint_name_list if it correspond to current well, and isn't already in list
        if (QString::compare(well_name, current_well) == 0 && !constraint_name_list.contains(current_name)){
             constraint_name_list.append(current_name);
        }
       i++;
    }

    if (!constraint_name_list.isEmpty()){
        uiOptConstraint->optConstraintListWidget->addItems(constraint_name_list);
        uiOptConstraint->optConstraintListWidget->setCurrentItem(uiOptConstraint->optConstraintListWidget->item(0)); // always a selected item in the list
    }
}


void OptConstraintDialog::setOptLocalConstraintsList(const QList<Utilities::Settings::Optimizer::Constraint> *local_constraints_list){
    local_constraints_list_ = local_constraints_list;
}

void OptConstraintDialog::on_optConstraintListWidget_currentTextChanged(const QString &currentText){
    // uiOptConstraint->optConstraintListWidget->setCurrentItem(0); it happens when connect()
    //every property shall change with the information belonging to the right item
    //So the signal reacts to changing text ->
    uiOptConstraint->optConTypeComboBox->setCurrentText("");
    //legge inn test om widgetList ikke er tom

    uiOptConstraint->optConTypeLabel->setEnabled(true);
    uiOptConstraint->optConTypeComboBox->setEnabled(true);
    //Show information corresponding to constraints item.
    for (int i = 0; i < local_constraints_list_->length(); i++) {
        if(QString::compare(currentText,local_constraints_list_->at(i).name) == 0 ){
            setConItemInformation(i);
            // break the for loop?? How to do that?;
           // continue;
            //return; //tror jeg skal fungere
        }
    }
}

void OptConstraintDialog::on_optConstraintListWidget_itemSelectionChanged(){ // need this in addition to changeText

    uiOptConstraint->optConTypeComboBox->setCurrentText("");
    //legge inn test om widgetList ikke er tom
    uiOptConstraint->optConTypeLabel->setEnabled(true);
    uiOptConstraint->optConTypeComboBox->setEnabled(true);

    for (int i = 0; i < local_constraints_list_->length(); i++) {
        if(QString::compare(uiOptConstraint->optConstraintListWidget->currentItem()->text(),local_constraints_list_->at(i).name) == 0 ){
            setConItemInformation(i);
            // break the for loop?? when finding the right item number. How to do that?;
           // continue;
        }
    }
}

void OptConstraintDialog::on_optConTypeComboBox_currentTextChanged(const QString &con_type){
    //what to enable and disable ui elements, depending on the text in the combobox (constraint type)
    enableDisableUiElementsConTypeComboBox(con_type);
}

void OptConstraintDialog::on_optConSplinePointsTypeComboBox_currentTextChanged(const QString &spline_type){
    enableDisableUiElementsSplinePointTypeComboBox(spline_type);
}


void OptConstraintDialog::enableDisableUiElementsConTypeComboBox(const QString &constraint_type){
    //what to enable and disable ui elements, depending on the constraint type (text in the combobox)
    bool enabler_spline = false;
    bool enabler_BHP_Rate = false;

    if (constraint_type.isEmpty()){
        uiOptConstraint->optConSplinePointsTypeComboBox->setCurrentText("");
        uiOptConstraint->optConSplinePointsLimitsLabel->setEnabled(false);
        uiOptConstraint->optConSplinePointsFunctionLabel->setEnabled(false);
        uiOptConstraint->optConSplinePointsFunctionEdit->setEnabled(false);
    }

    if ( QString::compare(constraint_type,"Well Spline Points") == 0 ) {
        enabler_spline = true;
        enabler_BHP_Rate = false;
    }

    if ( (QString::compare(constraint_type, "BHP") == 0) || (QString::compare(constraint_type, "Rate")==0)){
        enabler_BHP_Rate = true;
        enabler_spline = false;
        uiOptConstraint->optConSplinePointsLimitsLabel->setEnabled(false);
        uiOptConstraint->optConSplinePointsFunctionLabel->setEnabled(false);
        uiOptConstraint->optConSplinePointsFunctionEdit->setEnabled(false);
    }

    //Enables or disables these GUI elements(labels, spinboxes etc.) depending on the user choices
    uiOptConstraint->optConMaxLabel->setEnabled(enabler_BHP_Rate);
    uiOptConstraint->optConMaxdSpinBox->setEnabled(enabler_BHP_Rate);
    uiOptConstraint->optConMinLabel->setEnabled(enabler_BHP_Rate);
    uiOptConstraint->optConMindSpinBox->setEnabled(enabler_BHP_Rate);

    uiOptConstraint->optConSplinePointsTypeLabel->setEnabled(enabler_spline);
    uiOptConstraint->optConSplinePointsTypeComboBox->setEnabled(enabler_spline);
}

void OptConstraintDialog::enableDisableUiElementsSplinePointTypeComboBox(const QString &spline_type){
    bool enabler_maxmin = false;
    bool enabler_function = false;

    if ( QString::compare(spline_type,"MaxMin") == 0 ) {
        enabler_maxmin = true;
        enabler_function = false;
    }

    if ( QString::compare(spline_type, "Function") == 0){
        enabler_function = true;
        enabler_maxmin = false;
    }

    uiOptConstraint->optConSplinePointsLimitsLabel->setEnabled(enabler_maxmin);
    uiOptConstraint->optConSplinePointsFunctionLabel->setEnabled(enabler_function);
    uiOptConstraint->optConSplinePointsFunctionEdit->setEnabled(enabler_function);
}

void OptConstraintDialog::initializeConPropertiesDialog(){
    uiOptConstraint->optConItemSelectedLabel->setText("<No selected item>");
    uiOptConstraint->optConTypeComboBox->setCurrentText("");
    uiOptConstraint->optConSplinePointsTypeComboBox->setCurrentText("");

    //do the first check of enabling/disabling
    //alternative: create a fourth item in the combo box, which is the initial text and all the elements beneath is false initilially!!!
    uiOptConstraint->optConTypeLabel->setEnabled(false);
    uiOptConstraint->optConTypeComboBox->setEnabled(false);
    uiOptConstraint->optConMaxLabel->setEnabled(false);
    uiOptConstraint->optConMaxdSpinBox->setEnabled(false);
    uiOptConstraint->optConMinLabel->setEnabled(false);
    uiOptConstraint->optConMindSpinBox->setEnabled(false);
    uiOptConstraint->optConSplinePointsTypeLabel->setEnabled(false);
    uiOptConstraint->optConSplinePointsTypeComboBox->setEnabled(false);
    uiOptConstraint->optConSplinePointsLimitsLabel->setEnabled(false);
    uiOptConstraint->optConSplinePointsFunctionLabel->setEnabled(false);
    uiOptConstraint->optConSplinePointsFunctionEdit->setEnabled(false);
}




