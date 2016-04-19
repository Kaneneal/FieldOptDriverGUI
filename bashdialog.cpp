#include "bashdialog.h"
#include "ui_bashdialog.h"

#include <QtCore>


BashDialog::BashDialog(QWidget *parent) :
    QDialog(parent),
    uiBash(new Ui::BashDialog){

    setupBashDialog(); //!< Setup for the uiDialog and sets window title
    fixToolTips();

}

BashDialog::~BashDialog(){
    delete uiBash;
}


//when pressing button - add the text into the bashListWidget

//first check if not already in the list

void BashDialog::setupBashDialog(){
    uiBash->setupUi(this);
    this->setWindowTitle("BASH Commands");
    uiBash->bashCustomLineEdit->setPlaceholderText("Enter customized BASH command");
    new_commands_list_ = new QStringList();
    temp_commands_list_ = new QStringList();

}
void BashDialog::setNewCommandsList(QStringList *commands){
    new_commands_list_ = commands;
}


void BashDialog::setBashCommandsImport(const QString &script_name, QStringList *commands){
    //laste inn fra THE list inn til tempList og disable alle elementer som også er i exampleList if tempList[i] == example[j], example[j].disable
    setNewCommandsList(commands);
    //test if already in the examplelist, kjør addItem??(lage ny metode..), endre litt på den, fordi den velger bare the selected one...

    uiBash->bashListWidget->addItems(*commands);
//QList<QListWidgetItem *> exItems = uiBash->bashExampleListWidget->findItems(bashItem->text(),Qt::MatchExactly);


    uiBash->bashShellTypeComboBox->setCurrentText(script_name);
}

void BashDialog::fixToolTips(){
    uiBash->addCustomItemBashListButton->setToolTip("Add custom bash command to the list");
    uiBash->addItemBashListButton->setToolTip("Add selected item to the bash command list");
    uiBash->removeItemBashListButton->setToolTip("Remove selected item from the list");
    uiBash->buttonBox->setToolTip("Click 'OK' to accept the new changes. Click 'Cancel' to reject the new changes.");
}

void BashDialog::on_buttonBox_accepted(){
    // update QList run through tempList and add to existing bashComList if not already existing
        qDebug() << "Clicked 'OK' in the Bash dialog.";
        updateBASHcommands(temp_commands_list_); //In mainwindow, can now use getNewCommandsList, and set the commands to that list.
}

void BashDialog::on_buttonBox_rejected(){
    //tempList.clear - empty it
    qDebug() << "Clicked 'Cancel' in the Bash dialog.";
    temp_commands_list_->clear();
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
    //currentitem

    if (!(uiBash->bashExampleListWidget->selectedItems().size() > 0)){//if no selected items   -> return
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
    if (!(uiBash->bashListWidget->selectedItems().size() > 0)){//if no selected items   -> return
        return;
    }

    QListWidgetItem *bashItem = uiBash->bashListWidget->currentItem();

    //test if not a member in examplelist --> nothing happens)
    //if exists in exampleList want to enable it again
    //enum Qt::ItemFlag NoItemFlags   and ItemIsEnabled - brukes?

    //foreløpig fungerer dette, skulle helst hatt gråsone og ikke gjemt det helt
    QList<QListWidgetItem *> exItems = uiBash->bashExampleListWidget->findItems(bashItem->text(),Qt::MatchExactly); //!< Checks if item came from the example list
    if (exItems.size() > 0){//!< If found item
        uiBash->bashExampleListWidget->setCurrentItem(exItems.at(0)); //!<Set the current item to the former
        uiBash->bashExampleListWidget->currentItem()->setHidden(false);
    }

    //then delete from the bashList
    delete bashItem;
}

QStringList *BashDialog::getNewCommandsList() const {
    return new_commands_list_;
}


void BashDialog::updateBASHcommands(QStringList *temp_commands_list){
    //new QListWidgetItem(tr("Oak"), listWidget);
    new_commands_list_ = temp_commands_list;
}
