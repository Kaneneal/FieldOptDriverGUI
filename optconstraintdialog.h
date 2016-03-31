#ifndef OPTCONSTRAINTDIALOG_H
#define OPTCONSTRAINTDIALOG_H

#include <QDialog>
#include <QDebug>
#include "Utilities/settings/optimizer.h"

namespace Ui {
class OptConstraintDialog;
}

class OptConstraintDialog : public QDialog{
    Q_OBJECT

public:
    explicit OptConstraintDialog(QWidget *parent = 0);
    ~OptConstraintDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::OptConstraintDialog *uiOptConstraint;
};

#endif // OPTCONSTRAINTDIALOG_H
