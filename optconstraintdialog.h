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

    void setOptConstraintsVariables( QList<Utilities::Settings::Optimizer::Constraint> *constraints ); //!< For when is_well_prop == true, then set well_name. Use in mainwindow to import JSON and show in GUI.
    void setOptLocalConstraintsList(const QList<Utilities::Settings::Optimizer::Constraint> *local_constraints_list); //!< Set a local constraint list. Constraints is much used in the whole object, need local one available in reach.


private slots:
    //Signal methods (reacts to user action).
    void on_buttonBox_accepted(); //NOT FINISHED//!< Click 'OK', send data to Settings object.
    void on_buttonBox_rejected(); //NOT FINISHED //!< Click 'Cancel', reset GUI-data to previous state.
    void on_optConAddButton_clicked(); //!< Add constraint item (user action 'add').
    void on_optConRemoveButton_clicked(); //!< Remove selected/current item (user action 'remove').
    void on_optConWellNameComboBox_currentTextChanged(const QString &well_name); //!< Add/show constraint list based on well name/user action. Taken from local_constraints_list.
    void on_optConstraintListWidget_currentTextChanged(const QString &currentText); //!< Run setConItemInformation(int currItem).
    void on_optConstraintListWidget_itemSelectionChanged(); //!< //!< Run setConItemInformation(int currItem). In addition to currentTextChanged, in case.
    void on_optConTypeComboBox_currentTextChanged(const QString &con_type); //!< Run enableDisableUiElementsConTypeComboBox(QString con_type). User action.
    void on_optConSplinePointsTypeComboBox_currentTextChanged(const QString &spline_type); //!< Run enableDisableUiElementsSplinePointTypeComboBox(QString spline_type). User action.

    void setupDialog(); //!< Setup ui, and set window title.
    void setToolTips(); //!< Set tool tip for elements in constraint dialog
    void setConItemInformation(int currItem); //!< Show information in GUI corresponding to constraints item. Used in on_optConstraintListWidget_currentTextChanged() and on_optConstraintListWidget_itemSelectionChanged().
    void setOptConSplinePointsType(int currItem ); //!< Set/show spline point type in GUI based on info from current item. Used in setConItemInformation.
    void initializeConPropertiesDialog(); //!< Set the GUI dialog and elements in an initial state.
    void enableDisableUiElementsConTypeComboBox( const QString  &constraint_type); //!< Enable/disable ui elements based on contraint type. Run in signal method.
    void enableDisableUiElementsSplinePointTypeComboBox(const QString &spline_type); //!< Enable/disable ui elements based on spline type. Run in signal method.

private:
    Ui::OptConstraintDialog *uiOptConstraint;
    QList<Utilities::Settings::Optimizer::Constraint> const *local_constraints_list_ ; // skal også kunne endres på, const?
    QList<Utilities::Settings::Optimizer::Constraint> const *temp_constraints_list_; //skal endre på denne, skal den da være const??

};

#endif // OPTCONSTRAINTDIALOG_H
