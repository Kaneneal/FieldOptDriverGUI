#ifndef MODWELLCONTROLSDIALOG_H
#define MODWELLCONTROLSDIALOG_H

#include <QDialog>
#include <QDebug>

#include "Utilities/settings/model.h"

namespace Ui {
class ModWellControlsDialog;
}

class ModWellControlsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModWellControlsDialog(QWidget *parent = 0);
    ~ModWellControlsDialog();
    //another input: number of the selected item
    void setModWellControlsVariables(QList<Utilities::Settings::Model::Well> wells);

    void setTimeSteps(QStringList time_steps);
private slots:

    //Signal methods (reacts to user action).
    void on_mWellControlModeComboBox_currentTextChanged(const QString &control_mode); //!< Enables/disables based on control mode.
    void on_wellControlButtonBox_accepted(); //Click 'Ok'. Send info to settings objects.
    void on_wellControlButtonBox_rejected(); //Click 'Cancel'. Set to previous state. No changes stored.

    void setupDialog();//!< Setup dialog, and set window title. Run setToolTips().
    void setToolTips(); //!< Set tool tips for dialog elements.
private:
    Ui::ModWellControlsDialog *uiControls;
};

#endif // MODWELLCONTROLSDIALOG_H
