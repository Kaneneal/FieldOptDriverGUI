#ifndef OPTPARAMETERSDIALOG_H
#define OPTPARAMETERSDIALOG_H

#include <QDialog>
#include <QDebug>

#include "Utilities/settings/optimizer.h"


namespace Ui {
class OptParametersDialog;
}

/*!
 * \brief The OptParametersDialog class contains Optimizer's Parameters.
 *  It handles how the three variables is set based on user actions.
 * \param max evalutions, initial step length, minimum step length
 */
class OptParametersDialog : public QDialog{
    Q_OBJECT

public:
    explicit OptParametersDialog(QWidget *parent = 0);
    ~OptParametersDialog();

 //   void setOptParametersVariables(int max_evaluations,double initial_step_length,double minimum_step_length); //!< receiving the parameters variables, then setting them in the gui
    void setOptParametersVariables( Utilities::Settings::Optimizer::Parameters parameters);

private slots:
    //Signal methods
    void on_buttonBox_accepted(); //!< Click 'OK', send data to Settings object.
    void on_buttonBox_rejected(); //!< Click 'Cancel', reset GUI-data to previous state.

    void setToolTips(); //!< Set tool tip for everything in the parameters dialog.
    void updateParametersToUtilities(); //!< Set/show-in-GUI parameters variables.

private:
    Ui::OptParametersDialog *uiOptParameters;
    Utilities::Settings::Optimizer::Parameters parameters_;
};

#endif // OPTPARAMETERSDIALOG_H
