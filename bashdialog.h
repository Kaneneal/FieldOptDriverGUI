#ifndef BASHDIALOG_H
#define BASHDIALOG_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class BashDialog;
}

/*!
 * \brief The BashDialog class
 *
 */
class BashDialog : public QDialog {
    Q_OBJECT

public:
    explicit BashDialog(QWidget *parent = 0);
    ~BashDialog();

    void setBashCommandsImport(const QString &script_name, QStringList *commands); //!< set/show the imported bash commands in the bash dialog

    QStringList *getNewCommandsList() const;

private slots:

    void setupBashDialog(); //!<

    void fixToolTips();  //!<

    void updateBASHcommands(QStringList *temp_commands_list);  //!< use for accepting or rejecting new commands list.

    void on_buttonBox_accepted();  //!<

    void on_buttonBox_rejected();  //!<

    void on_addItemBashListButton_clicked();  //!<

    void on_removeItemBashListButton_clicked();  //!<

    void on_addCustomItemBashListButton_clicked();  //!<

    void setNewCommandsList( QStringList *commands); //!<

    void addCustomItem();

    void removeItem();

    void addItem();


private:
    Ui::BashDialog *uiBash; //!<
    Qt::ItemFlag *itemFlag; //!<
    QStringList *new_commands_list_; //!< The new commands list with updated information
    QStringList *temp_commands_list_; //!< For saving changes during user changes. If rejecting(Cancel) this will be cleared.

    //temp_list changes during user changes
    //if changes commands, then click ok, new_commands_list = temp_list, click cancel, new_commands_list is still identical to commands.
    //if click save after use of program, new_commands_list is the "new" commands_

};

#endif // BASHDIALOG_H
