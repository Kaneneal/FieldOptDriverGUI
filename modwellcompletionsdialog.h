#ifndef MODWELLCOMPLETIONSDIALOG_H
#define MODWELLCOMPLETIONSDIALOG_H

#include <QDialog>
#include <QDebug>

#include "Utilities/settings/model.h"

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
    //Signal methods (reacts to user action).
    void on_modWellCompletionButtonBox_accepted(); //!< Click 'Ok'. Send information to the settings object.
    void on_modWellCompletionButtonBox_rejected(); //!< Click 'Cancel'. Set info in the dialog to previous state.
    void on_modWellCompAddButton_clicked(); //!< Add a completion to the list.
    void on_modWellCompRemoveButton_clicked(); //!< Remove selected/current (item)completion from the list.

    void setToolTips(); //!< Set tool tips for dialog elements.

private:
    Ui::ModWellCompletionsDialog *uiCompletions;
};

#endif // MODWELLCOMPLETIONSDIALOG_H
