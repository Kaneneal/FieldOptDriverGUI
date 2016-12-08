#include "mwelldialog.h"
#include "ui_mwelldialog.h"


MWellDialog::MWellDialog(QWidget *parent) :
    QDialog(parent),
    uiModWell(new Ui::MWellDialog){
    setupMWellDialogs();
}

MWellDialog::~MWellDialog(){
    delete uiModWell;
}

/* Closing a dialog, are you sure?
void MyDialog::reject()
{
    QMessageBox::StandardButton resBtn = QMessageBox::Yes;
    if (changes) {
        resBtn = QMessageBox::question( this, APP_NAME,
                                        tr("Are you sure?\n"),
                                        QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                        QMessageBox::Yes);
    }
    if (resBtn == QMessageBox::Yes) {
        QDialog::reject();
    }
*/

void MWellDialog::setupMWellDialogs(){
    //MWellDialog
     uiModWell->setupUi(this);
     this->setWindowTitle("Model – Well");
     setToolTips();
     uiModWell->mWellNameEdit->setPlaceholderText("Well name");
     initializeMWellDialogElements();
     mWellControlsDialog = new ModWellControlsDialog();
     mWellCompletionsDialog = new ModWellCompletionsDialog();
     mWellVariablesDialog = new ModWellVariablesDialog();
}

void MWellDialog::setToolTips(){
    uiModWell->buttonBox->setToolTip("'OK' to accept (new) wells and values. 'Cancel' to regret changes.");
    uiModWell->mWellNameEdit->setToolTip("Name of (current) well.");
    uiModWell->mWellListWidget->setToolTip("List of well(s).");
    uiModWell->mWellAddButton->setToolTip("Add well (item) to the list.");
    uiModWell->mWellRemoveButton->setToolTip("Remove selected well (item) from the list.");

    uiModWell->mWellBlockXBox->setToolTip("Well block i-value.");
    uiModWell->mWellBlockYBox->setToolTip("Well block j-value.");
    uiModWell->mWellBlockZBox->setToolTip("Well block k-value.");

    uiModWell->mWellSplineXBox->setToolTip("Well spline i-value.");
    uiModWell->mWellSplineYBox->setToolTip("Well spline j-value.");
    uiModWell->mWellSplineZBox->setToolTip("Well spline k-value.");
}

void MWellDialog::initializeMWellDialogElements(){
    uiModWell->mWellSplineXBox->setHidden(true);
    uiModWell->mWellSplineYBox->setHidden(true);
    uiModWell->mWellSplineZBox->setHidden(true);
    uiModWell->mWellSplineLabel->setHidden(true);

    uiModWell->mWellBlockXBox->setHidden(false);
    uiModWell->mWellBlockYBox->setHidden(false);
    uiModWell->mWellBlockZBox->setHidden(false);
    uiModWell->mWellBlocksLabel->setHidden(false);

}

void MWellDialog::addWellBlock(){
    //QSpinBox QDoubleSpinBox;
    QTableWidgetItem *item_x;
    QTableWidgetItem *item_y;
    QTableWidgetItem *item_z;

    // xyz-values should be added to the table-widget.
    if (isDefinitionTypeWellBlock()){
        item_x = new QTableWidgetItem( uiModWell->mWellBlockXBox->text() );
        item_y = new QTableWidgetItem( uiModWell->mWellBlockYBox->text() );
        item_z = new QTableWidgetItem( uiModWell->mWellBlockZBox->text() );
    }else{
        item_x = new QTableWidgetItem( uiModWell->mWellSplineXBox->text() );
        item_y = new QTableWidgetItem( uiModWell->mWellSplineYBox->text() );
        item_z = new QTableWidgetItem( uiModWell->mWellSplineZBox->text() );

    }

   int totRows = uiModWell->mWellBlocksTableWidget->rowCount();

    for (int row = 0; row <= totRows-1; row++) {
        //if well block already exist, give message to user, return and doesn't add the new well block
        //THIS TEST DO NOOOOT DIFFER BETWEEN 0,0,0 and 0.00 0.00 0.00 (But should not be problem. will not mix block and spline in the table.
        if ( (QString::compare(item_x->text(),uiModWell->mWellBlocksTableWidget->item(row,0)->text()) == 0 )
             && ( QString::compare(item_y->text(),uiModWell->mWellBlocksTableWidget->item(row,1)->text()) == 0)
             && ( QString::compare(item_z->text(),uiModWell->mWellBlocksTableWidget->item(row,2)->text()) == 0) ){
           QMessageBox::information(this,"Well block already exist" , "This well block already exist. You cannot add well blocks that are already in the table.", QMessageBox::Ok, 0);
            return;
        }
    }

    //Add block (Will only happen if none of the above goes through (no block like this)).
    uiModWell->mWellBlocksTableWidget->insertRow(totRows);
    uiModWell->mWellBlocksTableWidget->setItem(totRows,0, item_x);
    uiModWell->mWellBlocksTableWidget->setItem(totRows,1, item_y);
    uiModWell->mWellBlocksTableWidget->setItem(totRows,2, item_z);

    //CLEAR SPIN BOXES? SET TO 0,0,0?

    //also add to completions, so they can choose these well blocks.
}

bool MWellDialog::isDefinitionTypeWellBlock(){
    if (QString::compare(uiModWell->mWellDefinitionTypeComboBox->currentText(),"Well Blocks") == 0) {
        return true;
    }
    else{
        return false;
    }
}

void MWellDialog::setMWellsVariables(QList<Utilities::Settings::Model::Well> wells){
    wells_ = wells;
    //Split up in functions
    //For now, using the element at position 0.
    uiModWell->mWellNameEdit->setText(wells.at(0).name);
    switch (wells.at(0).type) {
    case Utilities::Settings::Model::WellType::Producer:
        uiModWell->mWellTypeComboBox->setCurrentText("Producer");
        break;
    case Utilities::Settings::Model::WellType::Injector:
        uiModWell->mWellTypeComboBox->setCurrentText("Injector");
        break;
    default:
        break;
    }

    switch (wells.at(0).definition_type) {
    case Utilities::Settings::Model::WellDefinitionType::WellBlocks:
        uiModWell->mWellDefinitionTypeComboBox->setCurrentText("Well Blocks");
        for (int pos = 0; pos < wells.at(0).well_blocks.size(); pos++) {
            uiModWell->mWellBlockXBox->setValue(wells.at(0).well_blocks.at(pos).position.i);
            uiModWell->mWellBlockYBox->setValue(wells.at(0).well_blocks.at(pos).position.j);
            uiModWell->mWellBlockZBox->setValue(wells.at(0).well_blocks.at(pos).position.k);
            addWellBlock();
        }
        break;
    case Utilities::Settings::Model::WellDefinitionType::WellSpline:
        uiModWell->mWellDefinitionTypeComboBox->setCurrentText("Well Spline");
        for (int pos = 0; pos < wells.at(0).spline_points.size(); pos++) {
            uiModWell->mWellSplineXBox->setValue(wells.at(0).spline_points.at(pos).x);
            uiModWell->mWellSplineYBox->setValue(wells.at(0).spline_points.at(pos).y);
            uiModWell->mWellSplineZBox->setValue(wells.at(0).spline_points.at(pos).z);
            addWellBlock();
        }
        break;
    default:
        break;
    }
    uiModWell->mWellBlockXBox->setValue(0);
    uiModWell->mWellBlockYBox->setValue(0);
    uiModWell->mWellBlockZBox->setValue(0);
    uiModWell->mWellSplineXBox->setValue(0.0);
    uiModWell->mWellSplineYBox->setValue(0.0);
    uiModWell->mWellSplineZBox->setValue(0.0);

    switch (wells.at(0).prefered_phase) {
    case Utilities::Settings::Model::PreferedPhase::Oil:
        uiModWell->mWellPrefPhaseComboBox->setCurrentText("Oil");
        break;
    case Utilities::Settings::Model::PreferedPhase::Water:
        uiModWell->mWellPrefPhaseComboBox->setCurrentText("Water");
        break;
    case Utilities::Settings::Model::PreferedPhase::Gas:
        uiModWell->mWellPrefPhaseComboBox->setCurrentText("Gas");
        break;
    case Utilities::Settings::Model::PreferedPhase::Liquid:
        uiModWell->mWellPrefPhaseComboBox->setCurrentText("Liquid");
        break;
    default:
        break;
    }
    // QStringLiteral("Component %1").arg(comp_number)
    uiModWell->mWellHeelXSpinBox->setValue(wells.at(0).heel.i);
    uiModWell->mWellHeelYSpinBox->setValue(wells.at(0).heel.j);
    uiModWell->mWellHeelZSpinBox->setValue(wells.at(0).heel.k);
    uiModWell->mWellBoreRadiusdSpinBox->setValue(wells.at(0).wellbore_radius);

    switch (wells.at(0).direction) {
    case Utilities::Settings::Model::Direction::X:
        uiModWell->mWellDirectionComboBox->setCurrentText("X");
        break;
    case Utilities::Settings::Model::Direction::Y:
        uiModWell->mWellDirectionComboBox->setCurrentText("Y");
        break;
    case Utilities::Settings::Model::Direction::Z:
        uiModWell->mWellDirectionComboBox->setCurrentText("Z");
        break;
    default:
        break;
    }

    if (wells.at(0).variables.size() > 0){
        uiModWell->mWellSpecVariablesCheckBox->setChecked(true);
    }else{
        uiModWell->mWellSpecVariablesCheckBox->setChecked(false);
    }
}

void MWellDialog::on_mWellSetControlsButton_clicked(){
    mWellControlsDialog->setModal(true);
    mWellControlsDialog->exec();
    //if not using modal way -  ->show(); and then ->activateWindow();
    mWellControlsDialog->setModWellControlsVariables(wells_);
}

void MWellDialog::on_mWellSetCompletionsButton_clicked(){
    mWellCompletionsDialog->setModal(true);
    mWellCompletionsDialog->exec();
}

void MWellDialog::on_mWellSpecVariablesCheckBox_toggled(bool checked){
    uiModWell->mWellSetVariablesButton->setEnabled(checked);
}


void MWellDialog::on_mWellSetVariablesButton_clicked(){
    mWellVariablesDialog->setModal(true);
    mWellVariablesDialog->exec();
}


void MWellDialog::on_mWellDefinitionTypeComboBox_currentTextChanged(const QString &def_type){
    bool xyzbox_enabler = true;
    bool xyz_spline_enabler = false;
    if (QString::compare(def_type,"Well Blocks") == 0) {
        xyzbox_enabler = false;
        xyz_spline_enabler = true;
    }
    if (QString::compare( def_type,"Well Spline") == 0 ){
        xyzbox_enabler = true;
        xyz_spline_enabler = false;
    }
    uiModWell->mWellSplineXBox->setHidden(xyz_spline_enabler);
    uiModWell->mWellSplineYBox->setHidden(xyz_spline_enabler);
    uiModWell->mWellSplineZBox->setHidden(xyz_spline_enabler);
    uiModWell->mWellSplineLabel->setHidden(xyz_spline_enabler);

    uiModWell->mWellBlockXBox->setHidden(xyzbox_enabler);
    uiModWell->mWellBlockYBox->setHidden(xyzbox_enabler);
    uiModWell->mWellBlockZBox->setHidden(xyzbox_enabler);
    uiModWell->mWellBlocksLabel->setHidden(xyzbox_enabler);

    //INFORM: IF YOU CHANGE DEFINITION TYPE - the well block table resets:
    while (uiModWell->mWellBlocksTableWidget->rowCount() > 0 ){
        uiModWell->mWellBlocksTableWidget->removeRow(0);
    }
}
void MWellDialog::on_mWellAddBlockButton_clicked(){
    // xyz-values should be added to the table-widget.
    addWellBlock();
}

void MWellDialog::on_buttonBox_accepted(){
    qDebug() << "Clicked 'OK' in the (add) Well dialog.";
    //send new variables to settings object
    //check tablewidget for well blocks.
    //update
}

void MWellDialog::on_buttonBox_rejected(){
    qDebug() << "Clicked 'Cancel' in the (add) Well dialog.";
    //fix to previuos state
    setMWellsVariables(wells_); //cannot use this without initializing all the values I use in this method. OR System crashes!
}

