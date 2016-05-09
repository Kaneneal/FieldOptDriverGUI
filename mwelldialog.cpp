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

     mWellControlsDialog = new ModWellControlsDialog();
     mWellCompletionsDialog = new ModWellCompletionsDialog();
     mWellVariablesDialog = new ModWellVariablesDialog();
}

void MWellDialog::addWellBlock(){
    // xyz-values should be added to the table-widget.
    uiModWell->mWellBlockXBox;
    uiModWell->mWellBlockYBox;
    uiModWell->mWellBlockZBox;
    uiModWell->mWellBlocksTableWidget;
}

//------------- Model Well -----------------------------------------------------------------------------|

void MWellDialog::on_mWellSetControlsButton_clicked(){
    mWellControlsDialog->setModal(true);
    mWellControlsDialog->exec();

    //if not modal way -  ->show(); and then ->activateWindow();
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
    if (QString::compare(def_type,"Well Blocks") == 0) {
        uiModWell->mWellBlocksArraysLabel->setEnabled(true);
        //uiModWell->mWellBOX->setEnabled(true);
        uiModWell->mWellSplinePointsArraysLabel->setEnabled(false);
        //uiModWell->mWellBOX->setEnabled(false);
    }
    if (QString::compare( def_type,"Well Spline") == 0 ){
        uiModWell->mWellSplinePointsArraysLabel->setEnabled(true);
        //uiModWell->mWellBOX->setEnabled(true);
        uiModWell->mWellBlocksArraysLabel->setEnabled(false);
       // uiModWell->mWellBOX->setEnabled(false);
    }
}
void MWellDialog::on_mWellAddBlockButton_clicked(){
    // xyz-values should be added to the table-widget.
    addWellBlock();
}

void MWellDialog::on_buttonBox_accepted(){
    qDebug() << "Clicked 'OK' in the (add) Well dialog.";
    //send new variables to settings object
}

void MWellDialog::on_buttonBox_rejected(){
    qDebug() << "Clicked 'Cancel' in the (add) Well dialog.";
    //fix to previuos state

}


//------------- END Model Well --------------------------------------------------------------------------|


