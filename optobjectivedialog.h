#ifndef OPTOBJECTIVEDIALOG_H
#define OPTOBJECTIVEDIALOG_H

#include <QDialog>
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

  void setOptObjectiveType(Utilities::Settings::Optimizer::ObjectiveType obj_type);

private slots:
    void on_optObjectiveIsWellPropCheckBox_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_optObjTypeComboBox_currentTextChanged(const QString &arg1);

private:
    Ui::OptObjectiveDialog *uiOptObjective;
};

#endif // OPTOBJECTIVEDIALOG_H
