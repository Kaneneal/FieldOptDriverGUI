#ifndef MODWELLVARIABLESDIALOG_H
#define MODWELLVARIABLESDIALOG_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class ModWellVariablesDialog;
}

class ModWellVariablesDialog : public QDialog{
    Q_OBJECT

public:
    explicit ModWellVariablesDialog(QWidget *parent = 0);
    ~ModWellVariablesDialog();

private slots:
    //Signal methods
    void on_buttonBox_accepted(); //!< Click 'Ok' on Variables dialog.
    void on_buttonBox_rejected(); //!< Click 'Cancel' on Variables dialog.

private:
    Ui::ModWellVariablesDialog *uiVariables;
};

#endif // MODWELLVARIABLESDIALOG_H
