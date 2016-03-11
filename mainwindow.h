#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>                   //evt.
#include <QApplication>
#include <QFileDialog>
//#include <QtDeclarative/QDeclarativeView>
//#include "settings/settings.h"
#include <QDialog>

#include "Utilities/settings/settings.h"

//bash dialog headers
#include "bashdialog.h"
#include "mwelldialog.h"
#include "optdialog.h"

#include "ui_aboutdialog.h"

//namespace Utilities {
//namespace Settings {
//class Settings;
//class Optimizer;
//class Simulator;
//class Model;
//}
//}


namespace Ui {
class MainWindow;
}

/*!
 * \brief The MainWindow class
 *
 * Every dialog should be connected and handled here.
 * /todo Connect every dialog
 * /todo Import information from json into the GUI, through settings_
*/
class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //må nok endre litt navn her

    void setupMainWindow();

    /*!
     * \brief on_tabWidget_currentChanged kommtar om funksjon
     * \param index og parameter
     */
    void on_tabWidget_currentChanged(int index); //!<

    void on_globalBrowseButton_clicked(); //!< Browse dialog opens, can choose output directory

    void on_modelBrowseButton_clicked(); //!< Browse dialog opens, can choose grid file (.GRID or .EGRID)

    void on_simBrowseButton_clicked(); //!< Browse dialog opens, can choose driver file (.DATA)

    void on_actionSave_triggered(); //!<

    void on_actionExit_triggered(); //!<

    void setToolTips(); //!<

    void setupPlaceholderTexts(); //!<

    void setupDialogs(); //!<

    void setupAboutDialog(); //!<

    void saveJSONfile(); //need seperated methods as well? one for create JSON file? One for update?

    void updateAllParameters(); //!< test function for setting all parameters after they have been change by the user

    void on_actionOpen_JSON_file_triggered(); //!<

    void on_optTypeEditButton_clicked(); //!<

    void fixIconOnButton(); //endre navn?

    void connectAllStuff(); //endre navn senere

    void on_simChooseCommButton_clicked(); //!<

    void on_actionNew_JSON_file_opens_a_new_window_triggered(); //!<

    void on_actionAbout_triggered(); //!<

    void on_modelSetWellVariablesButton_clicked(); //!<

    void on_optSetParametersButton_clicked(); //!<

    void on_optSetObjectiveButton_clicked(); //!<

    void on_optSetConstraintsButton_clicked(); //!<

private:
    Ui::MainWindow *ui; //!<
    QFileDialog *browseFileDialog; //!< file dialog used to find the file path - output place and driver path
    QApplication *app;             //!< application - need for f.ex. closing the application

    BashDialog *bashDialog; //!<
    Utilities::Settings::Settings *settings_; //!<

    Ui::AboutDialog *uiAbout; //!<
    QDialog *aboutDialog; //!<

    MWellDialog *mWellDialog; //!<

    OptDialog *optDialog; //!<

  //  QDeclarativeView fieldOptLogo;


};

#endif // MAINWINDOW_H
