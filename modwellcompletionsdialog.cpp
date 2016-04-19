#include "modwellcompletionsdialog.h"
#include "ui_modwellcompletionsdialog.h"

#include <QDebug>

ModWellCompletionsDialog::ModWellCompletionsDialog(QWidget *parent) :
    QDialog(parent),
    uiCompletions(new Ui::ModWellCompletionsDialog){
    uiCompletions->setupUi(this);
    this->setWindowTitle("Model - Well - Completions");
}

ModWellCompletionsDialog::~ModWellCompletionsDialog(){
    delete uiCompletions;
}

void ModWellCompletionsDialog::on_modWellCompletionButtonBox_accepted(){
    //send the chosen variables, save them... overwrite old ones or create new (research about this)
    qDebug() << "Clicked 'OK' in the Well Completions dialog.";

    //new_completions_list_ = temp_completions_list_;
}


void ModWellCompletionsDialog::on_modWellCompletionButtonBox_rejected(){
    //De forrige verdiene skal fortsatt gjelde. Når lagres dem?
    //Sjekk hva feltene er/midlertidige verdier,
    // så endre disse tre variablene i dialogen til disse verdiene
    qDebug() << "Clicked 'Cancel' in the Well Completions dialog.";

}

void ModWellCompletionsDialog::on_modWellCompAddButton_clicked(){
    //NEW item in completionListWidget, men i tillegg legges til i temp_completion_list som en completion type
    //dataen til denne blir satt, when pushing button "Update list item" eller noe sånt
    //compl_number = compl_number +1;
}


void ModWellCompletionsDialog::on_modWellCompRemoveButton_clicked(){
    //REMOVE item from completionListWidget (selected) og i temp_completion_list
    //compl_number = compl_number -1;
}
