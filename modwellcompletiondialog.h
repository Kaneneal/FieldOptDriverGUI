#ifndef MODWELLCOMPLETIONDIALOG_H
#define MODWELLCOMPLETIONDIALOG_H

#include <QDialog>

namespace Ui {
class ModWellCompletionDialog;
}

class ModWellCompletionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModWellCompletionDialog(QWidget *parent = 0);
    ~ModWellCompletionDialog();

private:
    Ui::ModWellCompletionDialog *ui;
};

#endif // MODWELLCOMPLETIONDIALOG_H
