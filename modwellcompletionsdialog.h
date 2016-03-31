#ifndef MODWELLCOMPLETIONSDIALOG_H
#define MODWELLCOMPLETIONSDIALOG_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class ModWellCompletionsDialog;
}

class ModWellCompletionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModWellCompletionsDialog(QWidget *parent = 0);
    ~ModWellCompletionsDialog();

private slots:
    void on_modWellCompletionButtonBox_accepted();

    void on_modWellCompletionButtonBox_rejected();

private:
    Ui::ModWellCompletionsDialog *uiCompletions;
};

#endif // MODWELLCOMPLETIONSDIALOG_H
