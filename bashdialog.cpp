#include "bashdialog.h"
#include "ui_bashdialog.h"



BashDialog::BashDialog(QWidget *parent) :
    QDialog(parent),
    uiBash(new Ui::BashDialog){

    setupBashDialog(); //!< Setup for the uiDialog and sets window title
}

BashDialog::~BashDialog(){
    delete uiBash;
}

//NEED TO CHECK IF THIS WAY REALLY SETS THE UTILITES COMMANDS?!? OR NEED TO USE A SETTER
//first check if not already in the list

void BashDialog::setupBashDialog(){
    uiBash->setupUi(this);
    this->setWindowTitle("Simualtor - BASH Commands");
    uiBash->bashCustomLineEdit->setPlaceholderText("Enter customized BASH command");
    //simulator_ = new Utilities::Settings::Simulator( ); er ikke riktig, men lurer på om må noe liknende?
    setToolTips();
}

// HAVE TO CHANGE NAME!
void BashDialog::setBashCommandsImport(Utilities::Settings::Simulator *simulator){
    simulator_ = simulator;
    QList<QListWidgetItem *> existing_items;
    uiBash->bashListWidget->clear();
        for (int i = 0; i < simulator->commands()->size(); i++) {
        existing_items = uiBash->bashExampleListWidget->findItems(simulator->commands()->at(i),Qt::MatchExactly);
        if (existing_items.size() != 0){
            //use element 0 cause it is known to be only one match
            uiBash->bashExampleListWidget->setCurrentItem(existing_items.at(0));
            addItem();

            selected_example_items_.append(existing_items.at(0)); //used when example_items is canceled
        }
        else {
            QListWidgetItem *command_item = new QListWidgetItem();
            command_item->setText(simulator->commands()->at(i));
            uiBash->bashListWidget->addItem(command_item);
        }
    }
    uiBash->bashShellTypeComboBox->setCurrentText(simulator->script_name());
}

void BashDialog::setToolTips(){
    uiBash->addCustomItemBashListButton->setToolTip("Add custom bash command to the list");
    uiBash->addItemBashListButton->setToolTip("Add selected item to the bash command list");
    uiBash->removeItemBashListButton->setToolTip("Remove selected item from the list");
    uiBash->buttonBox->setToolTip("Click 'OK' to accept the new changes. Click 'Cancel' to reject the new changes.");
}

void BashDialog::on_buttonBox_accepted(){
    qDebug() << "Clicked 'OK' in the Bash dialog.";
    //check if output directory and json fill in, default valgt, if not give message have to fill in.. (KJØR METODE)
    updateSimulatorBashToUtilities();
}

void BashDialog::on_buttonBox_rejected(){
    qDebug() << "Clicked 'Cancel' in the Bash dialog.";
    //check if output directory and json fill in, default valgt, if not give message have to fill in.. (KJØR METODE)
    resetExampleItems();
    setBashCommandsImport(simulator_); //this worked in parameters (men,hvis ikke importert, skjer da?)
}

void BashDialog::updateSimulatorBashToUtilities(){
    QStringList *temp_list = new QStringList();
//MOST TEST IF LIST IS BIGGER THAN 0, CONSTAINS SOMETHING?? OR DO I????
    for (int i = 0; i < uiBash->bashListWidget->count(); i++) {
            temp_list->append( uiBash->bashListWidget->item(i)->text());
        }
    simulator_->set_script_name(uiBash->bashShellTypeComboBox->currentText());
    simulator_->set_commands(temp_list);
}

void BashDialog::resetExampleItems(){
    for (int i = 0; i < selected_example_items_.size(); i++) {
        //select the item in bashWidgetList
        uiBash->bashListWidget->setCurrentItem( selected_example_items_.at(i));
        removeItem(); //put back into example list
    }
}

void BashDialog::on_addItemBashListButton_clicked(){
    addItem();
}

void BashDialog::on_removeItemBashListButton_clicked(){
   removeItem();
}

void BashDialog::on_addCustomItemBashListButton_clicked(){
    addCustomItem();
}

void BashDialog::addItem(){
    //adds current item (selected)
    if ( uiBash->bashExampleListWidget->selectedItems().size() == 0 ){//if no selected items   -> return
        return;
    }

    QListWidgetItem *exampleItem = uiBash->bashExampleListWidget->currentItem();

    uiBash->bashListWidget->addItem(exampleItem->text());
    qDebug() << exampleItem;

    exampleItem->setHidden(true);
    exampleItem->setSelected(false);// must let unselect the item - now no selected item in list

    //uiBash->bashExampleListWidget;
    //ItemFlag *itemFlag = noItemFlags;
    //exampleItem->setFlags(itemFlag); //want to disable item from being selected as current item (from the example list)
}


//NEED TO DO SOME TESTING: CANNOT ADD ALREADY EXISTING ITEM! AND IF EXIST IN EXAMPLE LIST, TAKE IT FROM THERE.
void BashDialog::addCustomItem(){
    QString custom_item;
    custom_item = uiBash->bashCustomLineEdit->text();
    if (custom_item.isEmpty()){ //not adding empty item to the bashList
            return;
    }
    uiBash->bashListWidget->addItem(custom_item);
    uiBash->bashCustomLineEdit->clear();
}

void BashDialog::removeItem(){
    //removes current item (selected)
    if ( uiBash->bashListWidget->selectedItems().size() == 0){//if no selected items   -> return
        return;
    }

    QListWidgetItem *bash_item = uiBash->bashListWidget->currentItem();
    QList<QListWidgetItem *> exItems = uiBash->bashExampleListWidget->findItems(bash_item->text(),Qt::MatchExactly); //!< Checks if item came from the example list
    if (exItems.size() > 0){//!< If found item
        uiBash->bashExampleListWidget->setCurrentItem(exItems.at(0)); //!<Set the current item to the former
        uiBash->bashExampleListWidget->currentItem()->setHidden(false); //not deleted, only hidden (to get it back)
    }
    //then delete from the bashList
    delete bash_item;
}

