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

    void setOptLocalConstraintsList(const QList<Utilities::Settings::Optimizer::Constraint> *local_constraints_list); //!< constraints is much used in the whole object, need local one in use


private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void setOptConSplinePointsType(int currItem );

    void on_optConAddButton_clicked();

    void on_optConRemoveButton_clicked();

    void on_optConWellNameComboBox_currentTextChanged(const QString &well_name);

    void on_optConstraintListWidget_currentTextChanged(const QString &currentText);

    void on_optConTypeComboBox_currentTextChanged(const QString &con_type);

    void initializeConPropertiesDialog();

    void on_optConSplinePointsTypeComboBox_currentTextChanged(const QString &spline_type);

    void setConstraintToolTips();

    void setConItemInformation(int currItem);

    void on_optConstraintListWidget_itemSelectionChanged();

    void enableDisableUiElementsConTypeComboBox( const QString  &constraint_type);

    void enableDisableUiElementsSplinePointTypeComboBox(const QString &spline_type);

private:
    Ui::OptConstraintDialog *uiOptConstraint;
    QList<Utilities::Settings::Optimizer::Constraint> const *local_constraints_list_ ; // skal også kunne endres på, const?
    QList<Utilities::Settings::Optimizer::Constraint> const *temp_constraints_list_; //skal endre på denne, skal den da være const??

};

#endif // OPTCONSTRAINTDIALOG_H
