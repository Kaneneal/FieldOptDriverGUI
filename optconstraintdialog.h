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

    void setOptConstraintsVariables( QList<Utilities::Settings::Optimizer::Constraint> *constraints ); // ta inn en liste? og/eller ta inn type etc. for så å kjøre if og kjøre metoder inni ettersom hva det blir sconst QString &well_name );//!< For when is_well_prop == true, then set well_name.

    void setLocalConstraintsList(const QList<Utilities::Settings::Optimizer::Constraint> *local_constraints_list); //!< constraints is much used in the whole object, need local one in use


private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void setOptConSplinePointsType( QList<Utilities::Settings::Optimizer::Constraint> *spline_constraints );

    void on_optConAddButton_clicked();

    void on_optConRemoveButton_clicked();

    void on_optConWellNameComboBox_currentTextChanged(const QString &well_name);

    void on_optConstraintListWidget_currentTextChanged(const QString &currentText);

private:
    Ui::OptConstraintDialog *uiOptConstraint;
    QList<Utilities::Settings::Optimizer::Constraint> const *local_constraints_list_ ;

};

#endif // OPTCONSTRAINTDIALOG_H
