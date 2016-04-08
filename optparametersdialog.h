#ifndef OPTPARAMETERSDIALOG_H
#define OPTPARAMETERSDIALOG_H

#include <QDialog>
#include <QDebug>

#include "Utilities/settings/optimizer.h"


namespace Ui {
class OptParametersDialog;
}

class OptParametersDialog : public QDialog{
    Q_OBJECT

public:
    explicit OptParametersDialog(QWidget *parent = 0);
    ~OptParametersDialog();

 //   void setOptParametersVariables(int max_evaluations,double initial_step_length,double minimum_step_length); //!< receiving the parameters variables, then setting them in the gui
    void setOptParametersVariables( Utilities::Settings::Optimizer::Parameters parameters);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::OptParametersDialog *uiOptParameters;
};

#endif // OPTPARAMETERSDIALOG_H
