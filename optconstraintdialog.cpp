#include "optconstraintdialog.h"
#include "ui_optconstraintdialog.h"

OptConstraintDialog::OptConstraintDialog(QWidget *parent) :
    QDialog(parent),
    uiOptConstraint(new Ui::OptConstraintDialog){
    uiOptConstraint->setupUi(this);
    this->setWindowTitle("Optimizer - Constraints");

    // Add additional feature so that
    // we can manually modify the data in ListView
    // It may be triggered by hitting any key or double-click etc.
    uiOptConstraint->optConstraintListWidget->setEditTriggers(QAbstractItemView::AnyKeyPressed |
                                                              QAbstractItemView::DoubleClicked);

    connect(uiOptConstraint->optConstraintListWidget,SIGNAL(currentTextChanged(QString)),uiOptConstraint->optConItemSelectedLabel,SLOT(setText(QString)));
}

OptConstraintDialog::~OptConstraintDialog(){
    delete uiOptConstraint;
}


void OptConstraintDialog::on_buttonBox_accepted(){
    qDebug() << "Clicked 'OK' in the Constraint dialog.";
}

void OptConstraintDialog::on_buttonBox_rejected(){
    qDebug() << "Clicked 'Cancel' in the Constraint dialog.";

}
void OptConstraintDialog::setOptConSplinePointsType(QList<Utilities::Settings::Optimizer::Constraint> *spline_constraints){

    for (int i = 0; i < spline_constraints->length(); i++) {
        // constraints.at(i);
        uiOptConstraint ->optConSplinePointsTypeLabel->setEnabled(true);
        //name is added to a list, then there should be an action, when that element is selected show the belonging information.
        uiOptConstraint->optConSplinePointsTypeComboBox->setEnabled(true);


        switch (spline_constraints->at(i).spline_points_type) {
        case Utilities::Settings::Optimizer::ConstraintWellSplinePointsType::MaxMin :
            uiOptConstraint->optConSplinePointsTypeComboBox->setCurrentText("MaxMin");
            uiOptConstraint->optConSplinePointsLimitsLabel->setEnabled(true);
            //Fix Limits... realCoordinate .x, .y, .z  ... for (int i = 0;.. create method?
           /* for (int j = 0; j < total; j++) {
                constraints.at(i).spline_points_limits.at(j).max.x;
                constraints.at(i).spline_points_limits.at(j).max.y;
                constraints.at(i).spline_points_limits.at(j).max.z;
                constraints.at(i).spline_points_limits.at(j).min.x;
                constraints.at(i).spline_points_limits.at(j).min.y;
                constraints.at(i).spline_points_limits.at(j).min.z;
            }*/

            uiOptConstraint->optConSplinePointsFunctionLabel->setEnabled(false);
            uiOptConstraint->optConSplinePointsFunctionEdit->setEnabled(false);
            break;
        case Utilities::Settings::Optimizer::ConstraintWellSplinePointsType::Function:
            uiOptConstraint->optConSplinePointsTypeComboBox->setCurrentText("Function");

            uiOptConstraint->optConSplinePointsFunctionLabel->setEnabled(true);
            uiOptConstraint->optConSplinePointsFunctionEdit->setEnabled(true);
            uiOptConstraint->optConSplinePointsFunctionEdit->setText(spline_constraints->at(i).well_spline_points_function);
            uiOptConstraint->optConSplinePointsLimitsLabel->setEnabled(false);

            break;
        default:
            break;
        }
        //Disabling the useless elements
        uiOptConstraint->optConMaxLabel->setEnabled(false);
        uiOptConstraint->optConMaxdSpinBox->setEnabled(false);
        uiOptConstraint->optConMinLabel->setEnabled(false);
        uiOptConstraint->optConMindSpinBox->setEnabled(false);

    }// end for
}

//showdialogsmethod som brukes i mainwindow.cpp når constraints-knappen blir trykket. kjører for(int i=0;...){ ->show(), activateWindow()

void OptConstraintDialog::setOptConstraintsVariables(QList<Utilities::Settings::Optimizer::Constraint> *constraints ){ //skal constraints ha peker?
    //dele opp i flere metoder....
    //bool enabler;

    //Mulig dette kan bli én metode: initializeList(QList<Utilities::....> *constraints)
    int i = 0;
    QStringList well_list; //kan få den fra "offisiell" liste fra models, eller gå igjennom
    while(i < constraints->size()){

        if (!well_list.contains(constraints->at(i).well)){
             well_list.append(constraints->at(i).well);
        }

       i++;
    }
    uiOptConstraint->optConWellNameComboBox->addItems(well_list);


       // uiOptConstraint->optConstraintListWidget->addItems(StringList); //when currentText() bla bla osv.

    for (int i = 0; i < constraints->length(); i++) {

                switch (constraints->at(i).type) {
            case Utilities::Settings::Optimizer::ConstraintType::BHP: //OR Rate.. then
                //  max, min
                uiOptConstraint->optConTypeComboBox->setCurrentText("BHP");
                uiOptConstraint->optConMaxLabel->setEnabled(true);
                uiOptConstraint->optConMaxdSpinBox->setEnabled(true);
                uiOptConstraint->optConMaxdSpinBox->setValue(constraints->at(i).max);

                uiOptConstraint->optConMinLabel->setEnabled(true);
                uiOptConstraint->optConMindSpinBox->setEnabled(true);
                uiOptConstraint->optConMindSpinBox->setValue(constraints->at(i).min);

                uiOptConstraint->optConSplinePointsTypeLabel->setEnabled(false);
                uiOptConstraint->optConSplinePointsTypeComboBox->setEnabled(false);
                uiOptConstraint->optConSplinePointsLimitsLabel->setEnabled(false);
                uiOptConstraint->optConSplinePointsFunctionLabel->setEnabled(false);
                uiOptConstraint->optConSplinePointsFunctionEdit->setEnabled(false);
                break;
            case Utilities::Settings::Optimizer::ConstraintType::Rate:
                //  max, min
                uiOptConstraint->optConTypeComboBox->setCurrentText("Rate");
                uiOptConstraint->optConMaxLabel->setEnabled(true);
                uiOptConstraint->optConMaxdSpinBox->setEnabled(true);
                uiOptConstraint->optConMaxdSpinBox->setValue(constraints->at(i).max);

                uiOptConstraint->optConMinLabel->setEnabled(true);
                uiOptConstraint->optConMindSpinBox->setEnabled(true);
                uiOptConstraint->optConMindSpinBox->setValue(constraints->at(i).min);

                //Disabling the useless elements
                uiOptConstraint->optConSplinePointsTypeLabel->setEnabled(false);
                uiOptConstraint->optConSplinePointsTypeComboBox->setEnabled(false);
                uiOptConstraint->optConSplinePointsLimitsLabel->setEnabled(false);
                uiOptConstraint->optConSplinePointsFunctionLabel->setEnabled(false);
                uiOptConstraint->optConSplinePointsFunctionEdit->setEnabled(false);

                break;
            case Utilities::Settings::Optimizer::ConstraintType::SplinePoints:
                setOptConSplinePointsType(constraints);

                break;
            default:

                break;
        }

    }

}

// ta inn en liste? og/eller ta inn type etc. for så å kjøre if og kjøre metoder inni ettersom hva det blir sconst QString &well_name );//!< For when is_well_prop == true, then set well_name.

void OptConstraintDialog::on_optConAddButton_clicked(){
// add element with the belonging information
}

void OptConstraintDialog::on_optConRemoveButton_clicked(){
    //remove element from the
}

/*    // Add additional feature so that
    // we can manually modify the data in ListView
    // It may be triggered by hitting any key or double-click etc.
    ui->listView->
            setEditTriggers(QAbstractItemView::AnyKeyPressed |
                            QAbstractItemView::DoubleClicked);
}*/

void OptConstraintDialog::on_optConWellNameComboBox_currentTextChanged(const QString &well_name){

    //KJØR DENNE METODEN -> ( i mainwindow må det sendes med constraints/lista, den må så settes som en lokal liste i denne dialogen.
    uiOptConstraint->optConstraintListWidget->clear();
    QStringList constraint_name_list;
   // constraint_name_list.clear(); skal være unødvendig

    //setCurrentElement til listWidgetItem(0) (noe sånt) (dette skal aktivere action "on_optConstraintListWidget_activated??) noe sånt
    QString current_well;
    QString current_name;
    int i = 0;
    while(i < local_constraints_list_->size()){
        current_well = local_constraints_list_->at(i).well;
        current_name = local_constraints_list_->at(i).name;
        if (QString::compare(well_name, current_well) == 0 && !constraint_name_list.contains(current_name)){
             constraint_name_list.append(current_name);
        }
       i++;
    }

    if (!constraint_name_list.isEmpty()){
        uiOptConstraint->optConstraintListWidget->addItems(constraint_name_list);
        uiOptConstraint->optConstraintListWidget->setCurrentItem(uiOptConstraint->optConstraintListWidget->item(0)); // always is a selected item
    }


}
void OptConstraintDialog::setLocalConstraintsList(const QList<Utilities::Settings::Optimizer::Constraint> *local_constraints_list){
    local_constraints_list_ = local_constraints_list;
}


void OptConstraintDialog::on_optConstraintListWidget_currentTextChanged(const QString &currentText){
   // uiOptConstraint->optConstraintListWidget->setCurrentItem(0);
    //every property shall change with the information belonging to the right item


}
