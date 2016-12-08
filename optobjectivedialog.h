#ifndef OPTOBJECTIVEDIALOG_H
#define OPTOBJECTIVEDIALOG_H

#include <QDialog>
#include <QtCore>
#include <QDebug>

#include "Utilities/settings/optimizer.h"

namespace Ui {
class OptObjectiveDialog;
}

class OptObjectiveDialog : public QDialog{
    Q_OBJECT

public:
    explicit OptObjectiveDialog(QWidget *parent = 0);
    ~OptObjectiveDialog();

    void setOptObjectiveType( Utilities::Settings::Optimizer::ObjectiveType obj_type ); //!< Set objective type in GUI
    void setOptObjectiveWellVariables(bool is_well_prop, const QString &well_name );//!< For when is_well_prop == true, then set well_name.
    void setOptObjectiveIsFieldPropCheckBox( bool is_well_prop ); //!< Set check box "Is it a Field property?" based on weighted_sum_list.is_well_prop
    void setOptObjectiveWeightedSumComponents(const QList<Utilities::Settings::Optimizer::Objective::WeightedSumComponent> weighted_sum_list); //!< Set/show weighted sum components in GUI

    QList<Utilities::Settings::Optimizer::Objective::WeightedSumComponent> *new_weighted_sum_list() const; //!< Get the temporary weighted sum list which contains new changes.
    void setNewWeightedSumList(QList<Utilities::Settings::Optimizer::Objective::WeightedSumComponent> *new_weighted_sum_list); //!< Set the temporary weighted sum list

private slots:

    // Signal methods (reacts to user action).
    void on_buttonBox_accepted(); //!< Click 'OK' in dialog, then
    void on_buttonBox_rejected(); //!< Click 'Cancel' in dialog, then
    void on_optObjTypeComboBox_currentTextChanged(const QString &obj_type);//!< Enable/disable ui elements based on objective type (user actions).
    void on_optObjAddComponentButton_clicked(); //!< Add component when button is clicked.
    void on_optObjRemoveComponentButton_clicked(); //!< Remove selected/current component when remove button is clicked.
    void on_optObjWeightedSumListWidget_currentTextChanged(const QString &current_comp); //!< Updates information depending on which component is selected by user.
    void on_optObjWeightedSumListWidget_currentRowChanged(int currentRow); //Currently not in use, need the int currentRow?
    void on_optObjectiveIsFieldPropCheckBox_toggled(bool checked); //!< Handle enable/disable well combo box depending on user action.


    void setupDialog(); //!< Setup ui, and sets window title
    void setToolTips();//!< Set tool tip for elements in objective dialog
    void setOptObjectiveWeightedSumComponents(double coefficient, const QString &property, int time_step );//!< Set coeffisient, property, time step values in GUI. Used in the public setWeigthedSumComponent.
    void updateComponentInformation(const QString current_comp); // Have to use for updating component information while user changes data. To set current comp information
    void addComponent(); //!< Help method run in the add component on clicked


private:
    Ui::OptObjectiveDialog *uiOptObjective;
    //const? no?
    QList<Utilities::Settings::Optimizer::Objective::WeightedSumComponent> *new_weighted_sum_list_; //!< Needed to temporary store weighted sum list changes on elements that may be "permanent" changes sent to Settings object
    int comp_number = 0; //!< Since the components don't have names or anything unique about them, we need to give them names. Component + comp_number.
};

#endif // OPTOBJECTIVEDIALOG_H
