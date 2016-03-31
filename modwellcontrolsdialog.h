#ifndef MODWELLCONTROLSDIALOG_H
#define MODWELLCONTROLSDIALOG_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class ModWellControlsDialog;
}

class ModWellControlsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModWellControlsDialog(QWidget *parent = 0);
    ~ModWellControlsDialog();

private slots:
    void on_mWellControlModeComboBox_currentTextChanged(const QString &arg1);

    void on_wellControlButtonBox_accepted();

    void on_wellControlButtonBox_rejected();

private:
    Ui::ModWellControlsDialog *uiControls;
};

#endif // MODWELLCONTROLSDIALOG_H
