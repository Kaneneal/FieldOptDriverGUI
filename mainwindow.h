#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>                   //ingen feil om kommentere bort
//#include <QtDeclarative/QDeclarativeView>

#include <QDialog>
//#include <QtGui> //Tror kanskje denne inneholder flere av disse under - sjekke ut!ingen feil om kommenterer bort

#include <QTabBar>           // To get access to the tabWidgets bar
#include <QFileDialog>       // To get access to the file dialog for directories - browse...
#include <QMessageBox>
#include <QDebug>

#include <QApplication> // to be able to exit, close program
#include <QCloseEvent> //to be able to manipulate the reject/x, close on the main window

#include "Utilities/settings/settings.h"

//Dialog headers
#include "bashdialog.h"
#include "mwelldialog.h"
#include "optparametersdialog.h"
#include "optconstraintdialog.h"
#include "optobjectivedialog.h"

#include "ui_aboutdialog.h"


namespace Ui {
class MainWindow;
}

/*!
 * \brief The MainWindow class
 *
 * Every dialog should be connected and handled here.
 * /todo Import information from json into the GUI, through settings_
*/
class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //GÅ OVER NAVNA!

    // Constructor methods (run in constructor)
    void setupMainWindow(); //!< Sets the ui, window title, and initial tab
    void setToolTips(); //!< Set tool tip for everything directly in mainwindow
    void setupPlaceholderTexts(); //!< Set up the placeholder texts for line edits
    void setupDialogs(); //!< Creates all (new) dialogs, ran in the constructor
    void setupAboutDialog(); //!<  Set up the "About FieldOpt" dialog (don't need this if does it as the others)


    // REACTIVE METHODS, TRIGGERED BY USER
    void on_tabWidget_currentChanged(int index); //!< When changing tabs, the title in the window change name to the current tab

    //Global
    void on_globalNameEdit_textChanged(const QString &name); //!< The Settings object's name is set when user changes it.
    void on_globalPathEdit_textChanged(const QString &output_directory); //!< The Settings object's output directory is set when user changes it.
    void on_globalBrowseButton_clicked(); //!< Browse dialog opens, can choose output directory
    void on_globalBookkeepCheckBox_toggled(bool checked); //!< Enables/disables bookeeper tolerance
    void on_globalBookkeepTolerancedSpinBox_valueChanged(double bookkeep_tolerance); //!< The Settings object's bookeeper tolerance is set when user changes it.

    //Model
    void on_modelTypeComboBox_currentTextChanged(const QString &model_type); //!< The Settings object's (Model) reservoir grid source type is set when user changes it.
    void on_modelPathEdit_textChanged(const QString &model_grid_path); //!< The Settings object's (Model) reservoir grid path is set when user changes it.
    void on_modelBrowseButton_clicked(); //!< Browse dialog opens, can choose grid source file (.GRID or .EGRID)
    void on_modelSetWellVariablesButton_clicked(); //!< Activates model-well dialog
    void on_modelAddControlTimeButton_clicked();  //!<
    void on_modelRemoveControlTimeButton_clicked(); //!<

    //Simulator
    void on_simTypeComboBox_currentTextChanged(const QString &sim_type); //!<  The Settings object's Simulator type is set when user changes it.
    void on_simPathEdit_textChanged(const QString &driver_path); //!<  The Settings object's (Simulator) driver path is set when user changes it.
    void on_simBrowseButton_clicked(); //!< Browse dialog opens, can choose driver file (.DATA)
    void on_simChooseBashComButton_clicked();//!< Activates simulator-bash dialog

    //Optimizer
    void on_optTypeComboBox_currentTextChanged(const QString &opt_type); //!< Sets the Settings object's optimizer type
    void on_optTypeEditButton_clicked(); //!< Connected to opt type combobox, optimizer tab
    void on_optModeComboBox_currentTextChanged(const QString &opt_mode); //!< Sets the Settings object's optimizer mode
    void on_optSetParametersButton_clicked(); //!< Activates optimizer-parmeters dialog
    void on_optSetObjectiveButton_clicked(); //!< Activates optimizer-objective dialog
    void on_optSetConstraintsButton_clicked(); //!< Activates optimizer-constraint dialog

    void closeEvent (QCloseEvent *event); //!< Use for closing/exiting the program. Ask question.

    // Action, menu bar triggered
    void on_actionOpen_JSON_file_triggered(); //!< Opens filedialog, and then imports JSON file
    void on_actionSave_triggered(); //!< Push save THEN
    void on_actionAbout_triggered(); //!< Opens About dialog
    void on_actionExit_triggered(); //!< Opens QMessagebox:Question. User get to exit the program

    // Help methods
    //endre navn?
    void fixIconOnButton(); //!< Places all the icons onto the buttons
    //endre navn senere
    void connectAllStuff(); //!< Connects the elements in the ui
    void saveJSONfile(); //need seperated methods as well? one for create JSON file? One for update?
    void importJSONfile(); //!< Gather and runs all the set/show-in-GUI functions
    void setGlobalVariables(); //!< Set/show-in-GUI global variables
    void setModelVariables(); //!< Set/show-in-GUI model variables
    void setSimulatorVariables(); //!< Set/show-in-GUI Simulator variables
    void setOptimizerVariables(); //!< Set/show-in-GUI Optimizer variables
    void updateModelControlTimesToUtilities(); //!< Set/show-in-GUI model control times



private:
    Ui::MainWindow *ui;
    QFileDialog *browseFileDialog; //!< File dialog used to find the file path - output place, vgdriver path
    QApplication *app;             //!< Application - need for f.ex. closing the application

    Utilities::Settings::Settings *settings_; //!<

    BashDialog *bashDialog; //!<
    MWellDialog *mWellDialog; //!<
    OptParametersDialog *optParametersDialog; //!<
    OptConstraintDialog *optConstraintDialog; //!<
    OptObjectiveDialog *optObjectiveDialog; //!<
    Ui::AboutDialog *uiAbout; // Since it doesn't have its own .cpp file
    QDialog *aboutDialog; //!<

  //  QDeclarativeView fieldOptLogo;

};

#endif // MAINWINDOW_H
