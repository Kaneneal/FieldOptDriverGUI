#include "bashdialog.h"
#include "ui_bashdialog.h"

#include <QtCore>


BashDialog::BashDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BashDialog){

    setupBashDialog(); //!< Setup for the uiDialog and sets window title
    fixToolTips();

}

BashDialog::~BashDialog(){
    delete ui;
}

//when pressing button - add the text into the bashListWidget

//first check if not already in the list

void BashDialog::setupBashDialog(){
    ui->setupUi(this);
    this->setWindowTitle("BASH Commands");
    ui->bashCutomLineEdit->setPlaceholderText("Enter customized BASH command");

}

void BashDialog::updateBashDialog(){
    //laste inn fra THE list inn til tempList og disable alle elementer som også er i exampleList if tempList[i] == example[j], example[j].disable
}

void BashDialog::fixToolTips(){
    ui->addCustomItemBashListButton->setToolTip("Add custom bash command to the list");
    ui->addItemBashListButton->setToolTip("Add selected item to the bash command list");
    ui->removeItemBashListButton->setToolTip("Remove selected item from the list");
}

void BashDialog::on_buttonBox_accepted(){
    // update QList run through tempList and add to existing bashComList if not already existing
        qDebug() << "Clicked 'OK' in the Bash dialog.";
}

void BashDialog::on_buttonBox_rejected(){
    //tempList.clear - empty it
    qDebug() << "Clicked 'Cancel' in the Bash dialog.";

}

void BashDialog::on_addItemBashListButton_clicked(){
    //currentitem

    if (!(ui->bashExampleListWidget->selectedItems().size() > 0)){//if no selected items   -> return
        return;
    }

    QListWidgetItem *exampleItem = ui->bashExampleListWidget->currentItem();

    ui->bashListWidget->addItem(exampleItem->text());
    qDebug() << exampleItem;

    exampleItem->setHidden(true);
    exampleItem->setSelected(false);// must let unselect the item - now no selected item in list

   // ui->bashExampleListWidget;
    //ItemFlag *itemFlag = noItemFlags;
    //exampleItem->setFlags(itemFlag); //want to disable item from being selected as current item (from the example list)
}

void BashDialog::on_removeItemBashListButton_clicked(){
    if (!(ui->bashListWidget->selectedItems().size() > 0)){//if no selected items   -> return
        return;
    }

    QListWidgetItem *bashItem = ui->bashListWidget->currentItem();

    //test if not a member in examplelist --> nothing happens)
    //if exists in exampleList want to enable it again
    //enum Qt::ItemFlag NoItemFlags   and ItemIsEnabled - brukes?

    //foreløpig fungerer dette, skulle helst hatt gråsone og ikke gjemt det helt
    QList<QListWidgetItem *> exItems = ui->bashExampleListWidget->findItems(bashItem->text(),Qt::MatchExactly); //!< Checks if item came from the example list
    if (exItems.size() > 0){//!< If found item
        ui->bashExampleListWidget->setCurrentItem(exItems.at(0)); //!<Set the current item to the former
        ui->bashExampleListWidget->currentItem()->setHidden(false);
    }

    //then delete from the bashList
    delete bashItem;
}

void BashDialog::on_addCustomItemBashListButton_clicked(){
    QString customItem;
    customItem = ui->bashCutomLineEdit->text();
    if (customItem.isEmpty()){ //not adding empty item to the bashList
            return;
    }
    ui->bashListWidget->addItem(customItem);
    ui->bashCutomLineEdit->clear();
}

void BashDialog::updateBASHcommands(){
    //new QListWidgetItem(tr("Oak"), listWidget);

    //List = tempList
}
