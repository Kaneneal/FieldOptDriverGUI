#include "optconstraintdialog.h"
#include "ui_optconstraintdialog.h"

OptConstraintDialog::OptConstraintDialog(QWidget *parent) :
    QDialog(parent),
    uiOptConstraint(new Ui::OptConstraintDialog){
    uiOptConstraint->setupUi(this);
    this->setWindowTitle("Optimizer - Constraints");
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
