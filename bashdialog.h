#ifndef BASHDIALOG_H
#define BASHDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QtCore>
#include <QListWidget>

#include "Utilities/settings/simulator.h"


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

    void setBashCommandsImport(Utilities::Settings::Simulator *simulator ); //!< set/show the imported bash commands in the bash dialog

private slots:

    //Signal methods (reacts to user action).
    void on_buttonBox_accepted();  //!< Clicked 'OK' in bash dialog. Runs updateSimulatorBashToUtilities(): Sends/updates bash to the settings object.
    void on_buttonBox_rejected();  //!< Clicked 'Cancel'in bash dialog.
    void on_addItemBashListButton_clicked();  //!< Runs addItem().
    void on_removeItemBashListButton_clicked();  //!< Runs removeItem().
    void on_addCustomItemBashListButton_clicked();  //!< Runs addCustomItem.


    void setupBashDialog(); //!< Setup, and set window title for bash dialog. Run setToolTips().
    void setToolTips();  //!< Set all tool tips for elements in the bash dialog.
    void addItem(); //!< Add selected/current item. Used in on_addItemBashListButton_clicked().
    void removeItem(); //!< Remove selected/current item. Used in on_removeItemBashListButton_clicked().
    void addCustomItem(); //!< Add custom created item. Used in button signal (on_addCustomItemBashListButton_clicked()).
    void updateSimulatorBashToUtilities(); //!< Sends/updates bash to the settings object.
    void resetExampleItems(); //!< Resets info to previous state. Used to put example items back in that list if clicks 'Cancel' after choosing them.

private:
    Ui::BashDialog *uiBash;
    Utilities::Settings::Simulator *simulator_;
    QList <QListWidgetItem*> selected_example_items_;//!< list for example items that is added in the bash widget list


};

#endif // BASHDIALOG_H
