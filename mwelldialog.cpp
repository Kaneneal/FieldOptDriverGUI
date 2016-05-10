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
     this->setWindowTitle("Model - Well");
     setToolTips();
     initializeMWellDialogElements();
     mWellControlsDialog = new ModWellControlsDialog();
     mWellCompletionsDialog = new ModWellCompletionsDialog();
     mWellVariablesDialog = new ModWellVariablesDialog();
}

void MWellDialog::setToolTips(){
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

void MWellDialog::on_mWellSetControlsButton_clicked(){
    mWellControlsDialog->setModal(true);
    mWellControlsDialog->exec();
    //if not using modal way -  ->show(); and then ->activateWindow();
}

void MWellDialog::on_mWellSetCompletionsButton_clicked(){
    mWellCompletionsDialog->setModal(true);
    mWellCompletionsDialog->exec();
}


void MWellDialog::on_mWellSpecVariablesCheckBox_clicked(){
    if (uiModWell->mWellSpecVariablesCheckBox->isChecked()){
        uiModWell->mWellSetVariablesButton->setEnabled(true);
    }
    else{
        uiModWell->mWellSetVariablesButton->setEnabled(false);
    }
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
}

void MWellDialog::on_buttonBox_rejected(){
    qDebug() << "Clicked 'Cancel' in the (add) Well dialog.";
    //fix to previuos state
}
