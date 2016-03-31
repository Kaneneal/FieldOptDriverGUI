#ifndef MWELLDIALOG_H
#define MWELLDIALOG_H

#include <QDialog>
#include <QDebug>

#include "modwellcompletionsdialog.h"
#include "modwellcontrolsdialog.h"
#include "modwellvariablesdialog.h"

namespace Ui {
class MWellDialog;
}

/*!
 * \brief The MWellDialog class
 *
 *
 *
 */

class MWellDialog : public QDialog{
    Q_OBJECT

public:
    explicit MWellDialog(QWidget *parent = 0);
    ~MWellDialog();


private slots:

    void setupMWellDialogs(); //!< ui->setupUI(QDialog) for Well, ui->setupUI(QDialog) for Controls and Variables

    void on_mWellSetControlsButton_clicked();

    void on_mWellSpecVariablesCheckBox_clicked();

    void on_mWellDefinitionTypeComboBox_currentTextChanged(const QString &arg1);

    void on_mWellSetCompletionsButton_clicked();

    void on_mWellSetVariablesButton_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::MWellDialog *uiModWell;

   ModWellCompletionsDialog *mWellCompletionsDialog;
   ModWellControlsDialog *mWellControlsDialog;
   ModWellVariablesDialog *mWellVariablesDialog;

};

#endif // MWELLDIALOG_H
