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
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ModWellVariablesDialog *uiVariables;
};

#endif // MODWELLVARIABLESDIALOG_H
