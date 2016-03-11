#ifndef OPTDIALOG_H
#define OPTDIALOG_H

#include <QDialog>
#include "ui_optparametersdialog.h"
#include "ui_optconstraintsdialog.h"
#include "ui_optobjetivedialog.h"

namespace Ui {
class OptDialog;
}

/*!
 * \brief The OptDialog class
 *
 *
 */
class OptDialog : public QDialog{
    Q_OBJECT

public:
    explicit OptDialog(QWidget *parent = 0);
    ~OptDialog();

    void setupOptParametersDialog();

    void setupOptObjectiveDialog();

    void setupOptConstraintsDialog();

    QDialog *getOptParametersDialog() const;

    QDialog *getOptObjectiveDialog() const;

    QDialog *getOptConstraintsDialog() const;

private slots:
    void on_optObjectiveIsWellPropCheckBox_clicked(); //!<

    void on_buttonBox_accepted(); //!<

private:
    Ui::OptParametersDialog *uiParameters; //!<
    Ui::OptObjectiveDialog *uiObjective;   //!<
    Ui::OptConstraintsDialog *uiConstraints; //!<

    QDialog *optParametersDialog; //!<
    QDialog *optObjectiveDialog; //!<
    QDialog *optConstraintsDialog; //!<
};

#endif // OPTDIALOG_H
