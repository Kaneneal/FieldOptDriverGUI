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

    void setOptObjectiveType( Utilities::Settings::Optimizer::ObjectiveType obj_type );
    void setOptObjectiveWellVariables(bool is_well_prop, const QString &well_name );//!< For when is_well_prop == true, then set well_name.
    void setOptObjectiveIsWellPropCheckBox( bool is_well_prop ); //!< Simple method, sets check box is_well_prop, not depending on weather it is true or false.
    void setOptObjectiveWeightedSumComponents(double coefficient, const QString &property, int time_step );// use if only one element in the list? or use as a private method
    void setOptObjectiveWeightedSumComponents(const QList<Utilities::Settings::Optimizer::Objective::WeightedSumComponent> weighted_sum_list);

private slots:

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_optObjTypeComboBox_currentTextChanged(const QString &arg1);

    void on_optObjectiveIsWellPropCheckBox_toggled(bool checked);

private:
    Ui::OptObjectiveDialog *uiOptObjective;
};

#endif // OPTOBJECTIVEDIALOG_H
