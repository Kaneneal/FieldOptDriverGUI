#ifndef MWELLDIALOG_H
#define MWELLDIALOG_H

#include <QDialog>
#include "ui_mwellcontroldialog.h"
#include "ui_mwellcompletionsdialog.h"
#include "ui_mwellvariablesdialog.h"

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

    void on_mWellControlButtonBox_accepted(); //!<

    void on_mWellControlButtonBox_rejected(); //!<

    void on_mWellControlModeComboBox_currentTextChanged(const QString &arg1); //!<

    void setupMWellDialog(); //!< ui->setupUI(QDialog) for Well

    void setupMWellControlDialog(); //!< ui->setupUI(QDialog) for Controls

    void setupMWellCompletionsDialog(); //!< ui->setupUI(QDialog) for Completions

    void setupMWellVariablesDialog(); //!< ui->setupUI(QDialog) for Variables

    void on_mWellSetControlsButton_clicked();

    void on_mWellSpecVariablesCheckBox_clicked();

    void on_mWellDefinitionTypeComboBox_currentTextChanged(const QString &arg1);

    void on_mWellSetCompletionsButton_clicked();

    void on_mWellSetVariablesButton_clicked();

private:
    Ui::MWellDialog *ui;

    Ui::MWellControlDialog *uiControl;
    QDialog *mWellControlDialog;

    Ui::MWellCompletionsDialog *uiCompletions;
    QDialog *mWellCompletionsDialog;

    Ui::MWellVariablesDialog *uiVariables;
    QDialog *mWellVariablesDialog;

};

#endif // MWELLDIALOG_H
