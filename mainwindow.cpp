// Karoline Louise Rykkelid, Fall 2015

//Included header files:
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_aboutdialog.h"


#include <QtGui> //Tror kanskje denne inneholder flere av disse under - sjekke ut!

#include <QTabBar>                          // To get access to the tabWidgets bar
#include <QFileDialog>                      // To get access to the file dialog for directories - browse...
#include <QMessageBox>
#include <QDebug>

#include <QApplication> // to be able to exit, close program
#include <QCloseEvent> //to be able to manipulate the reject/x, close on the main window


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){

    setupMainWindow(); //!< Sets the ui, window title, and initial tab
    setupDialogs();
    setToolTips(); //!< Sets up the tool tips
    setupPlaceholderTexts();//!< Sets up the placeholder texts for line edits

    fixIconOnButton(); //!< Places all the icons onto the buttons
    connectAllStuff(); //!< Connects the elements in the ui

}


MainWindow::~MainWindow(){
    delete ui;
    //delete bashDialog; //Have to delete it, since bashDialog is set up modelless (can move back and forth between windows/dialogs), no need to cause do not create ui's here
   // delete mWellDialog; //trenger ikke å fjerne på denne måten
}

void MainWindow::setupMainWindow(){
    ui->setupUi(this);
    this->setWindowTitle("FieldOpt - "+ ui->tabWidget->tabText(0)); //FieldOpt - global

    ui->tabWidget->setCurrentIndex(0); //!< Sets the initial tab to be the global tab
    ui->optTypeLine->setText(ui->optTypeComboBox->currentText());

    settings_ = new Utilities::Settings::Settings("/home/karolinr/Documents/GitHub/FieldOpt/FieldOpt/GTest/Utilities/driver/driver.json", "/home/karolinr");

}

void MainWindow::setupDialogs(){
    bashDialog = new BashDialog();
    mWellDialog = new MWellDialog();
    optParametersDialog = new OptParametersDialog();
    optConstraintDialog = new OptConstraintDialog();
    optObjectiveDialog = new OptObjectiveDialog();
    setupAboutDialog(); //!< Set ups the "About FieldOpt" dialog

}

void MainWindow::setupAboutDialog(){
    aboutDialog = new QDialog;
    uiAbout = new Ui::AboutDialog;
    uiAbout->setupUi(aboutDialog);
    aboutDialog->setWindowTitle("About FieldOpt");
}


//----------Design GUI methods ---------------------------------------------------------------------------|
/*!
 * \brief MainWindow::setToolTips
 * Setting all the tool tips for everything in mainwindow
 */
void MainWindow::setToolTips(){
    //global - tool tip
    ui->globalNameEdit->setToolTip("Used to generate output file name(s)");
    ui->globalPathEdit->setToolTip("Path - Location for the output files");
    ui->globalBrowseButton->setToolTip("Browse - Find your path");

    ui->globalOutputPathLine->setToolTip("Path to the output files");
    ui->globalOutputPathEditButton->setToolTip("Edit path");

    //Model - tool tip
    ui->modelPathEdit->setToolTip("Path - Location for the grid file");
    ui->modelBrowseButton->setToolTip("Browse - Find the path to the grid file (.GRID or .EGRID)");

    ui->modelGridPathLine->setToolTip("Path to the model grid file");
    ui->modelGridPathEditButton->setToolTip("Edit path");

    //Simulator tool tip
    ui->simPathEdit->setToolTip("Path - Location for the driver file");
    ui->simBrowseButton->setToolTip("Browse - Find the path to the driver file (.DATA)");

    ui->simDriverPathLine->setToolTip("Path to the driver file");
    ui->simDriverPathEditButton->setToolTip("Edit path");

    //Optimizer tool tip
    ui->optTypeLine->setToolTip(" The opt algorithm type");
    ui->optTypeEditButton->setToolTip("Set/change type");

    //Tabs - tool tip
    ui->tabWidget->setTabToolTip(0,"global - Set name of the generated output files, the path, and choose debugging mode or not"); //!< For "global tab"// Switch to global settings
    ui->tabWidget->setTabToolTip(1,"Set model settings, variables and parameters for reservoir and wells"); //!< For "model tab" // Switch to model
    ui->tabWidget->setTabToolTip(2,"Set simulator type, how to execute the sim., and define the driver path."); //!< For "simulator tab" //Switch to simulator
    ui->tabWidget->setTabToolTip(3,"Set optimizer type, settings, and parameters"); //!< For "optimizer tab" // Switch to optimizer

    //JSON path - tool tip
    ui->jsonPathLine->setToolTip("Path to the JSON file");
    ui->jsonPathEditButton->setToolTip("Edit path");
}

void MainWindow::setupPlaceholderTexts(){
    //global
    ui->globalNameEdit->setPlaceholderText("Enter name to be used when generating output file names");
    ui->globalPathEdit->setPlaceholderText("Path to the output files ");
    //Model
    ui->modelPathEdit->setPlaceholderText("Path to the grid file (.GRID or .EGRID)");
    //Simulator
    ui->simPathEdit->setPlaceholderText("Path to the driver file (.DATA)");
}

/*!
 * \brief MainWindow::on_tabWidget_currentChanged
 * When changing tabs, the title in the window change name to the current
 *
 * \param index
 */
void MainWindow::on_tabWidget_currentChanged(int index){

    this->setWindowTitle("FieldOpt - "+ ui->tabWidget->tabText(index));
}

void MainWindow::connectAllStuff(){
    // HOW to check if the path exsists? not be able to change by typing?
    connect( ui->globalPathEdit, SIGNAL(textChanged(QString)), ui->globalOutputPathLine, SLOT(setText(QString)) );
    connect( ui->simPathEdit, SIGNAL(textChanged(QString)), ui->simDriverPathLine, SLOT(setText(QString)) );
    connect( ui->modelPathEdit, SIGNAL(textChanged(QString)), ui->modelGridPathLine, SLOT(setText(QString)) );
    connect( ui->optTypeComboBox, SIGNAL(currentTextChanged(QString)), ui->optTypeLine, SLOT(setText(QString)) );

    //Connect edit-buttons to browse buttons
    connect( ui->globalOutputPathEditButton, SIGNAL(clicked(bool)), ui->globalBrowseButton, SLOT(click()));
    connect( ui->modelGridPathEditButton, SIGNAL(clicked(bool)), ui->modelBrowseButton, SLOT(click()));
    connect( ui->simDriverPathEditButton, SIGNAL(clicked(bool)), ui->simBrowseButton, SLOT(click()));
    connect( ui->jsonPathEditButton, SIGNAL(clicked(bool)), ui->actionOpen_JSON_file, SLOT(trigger()));

}

void MainWindow::fixIconOnButton(){
    //kan sikkert arrangere dette annerledes, men forløpig slik
    QPixmap pixmap(":/Images/pensil");
    QIcon EditIcon(pixmap);
    ui->globalOutputPathEditButton->setIcon(EditIcon);
    ui->globalOutputPathEditButton->setIconSize(QSize(27,27));//pixmap.rect().size());
   // ui->globalOutputPathEditButton->setFixedSize(QSize(27,27)); Satt i GUI - sette her også?

    ui->modelGridPathEditButton->setIcon(EditIcon);
    ui->modelGridPathEditButton->setIconSize(QSize(25,25));

    ui->simDriverPathEditButton->setIcon(EditIcon);
    ui->simDriverPathEditButton->setIconSize(QSize(25,25));//pixmap.rect().size());

    ui->optTypeEditButton->setIcon(EditIcon);
    ui->optTypeEditButton->setIconSize(QSize(25,25));

    ui->jsonPathEditButton->setIcon(EditIcon);
    ui->jsonPathEditButton->setIconSize(QSize(25,25));
}


//---------- END Design GUI methods ----------------------------------------------------------------------|

void MainWindow::saveJSONfile(){
    updateAllParameters();

    //Something here. Sender dem til JSONfila

    //if something - everything correctly done
    QMessageBox::information(this, "Save", "You have now saved (and/or updated) the JSON file.", QMessageBox::Ok, 0 );
}

void MainWindow::updateAllParameters(){ // Fra GUI ut til Settings

    //sets the global parameters
//    global.set_name(ui->globalNameEdit->text());
//    global.set_output_directory(ui->globalPathEdit->text());
//    global.set_verbosity(ui->globalRadioButtonY->isChecked()); //!< verbose = true if yes is checked

// FIX METHODS FOR THESE SETTERS!!!!!!!!!!!!!!
    //sets the model parameters

    //sets the simulator parameters
    //simulator.set_type( ui->simTypeComboBox->currentText() ); //Put a check for SimulatorType = ECLIPSE. already method for this?
//    switch (settings->simulator()->type()) {
//    case ::Utilities::Settings::Simulator::SimulatorType::ECLIPSE:
//        // set ui string value
//        break;
//    default:
//        break;
//    }

//    if (QString::compare(ui->simTypeComboBox->currentText(), "ECLIPSE") == 0) {
//        // set object enum value
//    }
  //simulator.setCommands(ui->simCommandsList);
//    simulator.set_driver_file_path( (ui->simPathEdit->text()) );


    //sets the optimizer parameters including all subclasses
//    optimizer.setType(ui->optTypeComboBox->currentText());

   // optimizer.Parameter.initialStepLength;
   // optimizer.Parameter.maxEvaluations;
   // optimizer.Parameter.minimumStepLength;

   // optimizer.Objective. ;

//    qDebug() << "Global name: " + global.get_name();

//    qDebug() << "Global dir: " + global.output_directory();

//    qDebug() << "Global verbose: " + QString::number(global.verbose());

//    qDebug() << "Sim type: " + simulator.get_type();

//    qDebug() << "Sim path: " + simulator.get_driver_file_path();

//    qDebug() << "Opt type: " + optimizer.type();

}

void MainWindow::importJSONfile(){
    setGlobalVariables();
    setModelVariables();
    setSimulatorVariables();
    setOptimizerVariables();
}

//------------- global actions ------------------------------------------------------------------------------------------------------|

void MainWindow::on_globalBrowseButton_clicked(){ //fix own instance of file dialog?
    // Browse file dialog mode
    //browseFileDialog.setFileMode(QFileDialog::Directory); // show files and directories when open file dialog
    //ABOUT DIRECTORY TYPE
    /* About the (QFileDialog::Directory)
     * The name of a directory. Both files and directories are displayed.
     * However, the native Windows file dialog does not support displaying
     *  files in the directory chooser.
     */
    //browseFileDialog.setOption(QFileDialog::ShowDirsOnly);  //want to show directories only
    //browseFileDialog.setLabelText (QFileDialog::Accept, "Choose" ); // DONT WORK, YET
   // browseFileDialog.exec(); . want to be able to fix it!

    //Have this here if we use the edit button shortcut
    ui->tabWidget->setCurrentIndex(0); //!< Sets the current tab to "global" tab
    ui->globalPathEdit->setFocus(); //!< The global path is set to current focus

    QString tempOutputDirectory = browseFileDialog->getExistingDirectory(this, tr("Choose Directory"),"/home",
                                                                        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
   // browseFileDialog->setFocus();
    if(!tempOutputDirectory.isNull()){ //!< if you chose a path with the file dialog, the line edit is changed. If not, nothing happens
        ui->globalPathEdit->setText(tempOutputDirectory); //!< Sets the text in the lineEdit field to be the choosen path to the directory
    }
}

//END global actions-----------------------------------------------------------------------------------------------------------------|


//------------- Model actions -------------------------------------------------------------------------------------------------------|
void MainWindow::on_modelBrowseButton_clicked(){
    QString tempGridPath = browseFileDialog->getOpenFileName(this, tr("Choose grid file (.GRID or .EGRID)"), "/home", tr("Grid files (*.GRID *.EGRID)"));

    if(!tempGridPath.isNull()){  //!< if you chose a path with the file dialog, the line edit is changed. If not, nothing happens
        ui->modelPathEdit->setText(tempGridPath);
    }
}

void MainWindow::on_modelSetWellVariablesButton_clicked(){
    mWellDialog->show();
    mWellDialog->raise();
    mWellDialog->activateWindow();
}


//-------------END Model actions-----------------------------------------------------------------------------------------------------|


//------------- Simulator actions ---------------------------------------------------------------------------------------------------|

void MainWindow::on_simBrowseButton_clicked(){
   // browseFileDialog.setLabelText (QFileDialog::Accept, "Choose" );//!< Sets the button text to "Choose" in the file dialog -DONT WORK

    //Put here in case the edit button is clicked, the focus changes
    ui->tabWidget->setCurrentIndex(2); //!< Sets the current tab to "simulator" tab
    ui->simPathEdit->setFocus(); //!< The driver path is set to current focus

    QString tempDriverPath = browseFileDialog->getOpenFileName(this, tr("Choose Driver file (.DATA)"), "/home", tr("Driver file (*.DATA)"));


    if(!tempDriverPath.isNull()){  //!< if you chose a path with the file dialog, the line edit is changed. If not, nothing happens
        ui->simPathEdit->setText(tempDriverPath);
    }
}

void MainWindow::on_simChooseCommButton_clicked(){
   //WANT? be able to click both windows when bash command is open, or not??
   // må bare lages én gang pr mainWindow, men åpnes og lukkes. Dataen spares på og skal være den samme helt til man lukker programmet.
   // BashDialog bashDialog;
   // bashDialog.setModal(true);
   // bashDialog.exec();
    bashDialog->show();
    bashDialog->raise();
    bashDialog->activateWindow();

}

//-------------END simulator actions-------------------------------------------------------------------------------------------------|


//------------- Optimizer actions ---------------------------------------------------------------------------------------------------|

void MainWindow::on_optTypeEditButton_clicked(){
    ui->tabWidget->setCurrentIndex(3); //!< Sets the current tab to "be the "optimizer" tab
    ui->optTypeComboBox->activated(ui->optTypeComboBox->currentText());
    ui->optTypeComboBox->setFocus();
}

void MainWindow::on_optSetParametersButton_clicked(){
    //optParametersDialog->setModal(true);
    //optParametersDialog->exec();
    optParametersDialog->show();
    optParametersDialog->activateWindow();
}

void MainWindow::on_optSetObjectiveButton_clicked(){
    // Bruker dette så må man lukke objective dialog, men kanskje man vil sammenlikne?
    // optObjectiveDialog->setModal(true);
    // optObjectiveDialog->exec();
    optObjectiveDialog->show();
    optObjectiveDialog->activateWindow();

    //hvordan fikser dette... når klikker så må det lages en ny dialog? eller kan den allerede være laget
    // og deretter sette modellen = true...
}

void MainWindow::on_optSetConstraintsButton_clicked(){
    // optConstraintDialog->setModal(true);
    // optConstraintDialog->exec();
    optConstraintDialog->show();
    optConstraintDialog->activateWindow();
}

//-------------END optimizer actions-------------------------------------------------------------------------------------------------|




//------------- MENU actions -------------------------------------------------------------------------------------------------------------|
void MainWindow::on_actionNew_JSON_file_opens_a_new_window_triggered(){
        //MainWindow newWindow = ui(new Ui::MainWindow);
        //ui->setupUi(newWindow);
        //newWindow->setWindowTitle("FieldOpt - "+ ui->tabWidget->tabText(0))
        //opprett instanse av denne mainwindow - mer komplisert enn jeg tenkte , tror jeg... siden d ikke eksisterer kode til det nye vinduet - variablene som skal settes
}

//Import/open JSON file
void MainWindow::on_actionOpen_JSON_file_triggered(){

    if(ui->globalPathEdit->text().size()==0){
       QMessageBox::information(this, "Missing output path", "Please fill out the path to the output directory and/or browse, in the Global tab before opening the JSON file.", QMessageBox::Ok, 0);
        return;
    }

    // browseFileDialog.setLabelText (QFileDialog::Accept, "Import" );//!< Sets the button text to "Import" in the file dialog må kjøres egen .exec for å kjøre denne spesielle
      QString tempPreJSONPath = browseFileDialog->getOpenFileName(this, tr("Choose JSON file to import"), "/home", tr("JSON (*.json)"));

      if(!tempPreJSONPath.isEmpty()){       //!< if you chose a path with the file dialog, the line edit is changed. If not, nothing happens
        ui->jsonPathLine->setText(tempPreJSONPath);
        ui->jsonPathLine->setEnabled(true);
        ui->jsonPathLabel->setEnabled(true);
      }
       // Need to disable json line stuff, when no text there (deleted or regret choosing a json file), when you create a new json file here, the json position will be the same as output path?

    //  settings_ = new Utilities::Settings::Settings(ui->jsonPathLine->text(), ui->globalPathEdit->text()); // Skal endre og uncommente senere

      importJSONfile();
}


void MainWindow::on_actionSave_triggered(){
    //saves all changes into the .JSON file.
    //run a method (create and/or update .JSON file)
    saveJSONfile();
}

// EXIT the program
void MainWindow::on_actionExit_triggered(){
    //if no changes - all saved
    //if not all changes are saved, ask to save the last changes??!?

QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Close this program?", "Are you sure you want to quit?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
        app->quit();
        //delete all ui's: solution: it does it with app->quit()
    }
 else {
     qDebug() << "Yes was *not* clicked";
  }

}

//About FieldOpt
void MainWindow::on_actionAbout_triggered(){
   //aboutDialog->show();
   //aboutDialog->raise();
   //aboutDialog->activateWindow();
   aboutDialog->setModal(true);
   aboutDialog->exec();
}


void MainWindow::closeEvent (QCloseEvent *event){
    //check if saved... if not, ask if you want to save. then ->

    QMessageBox::StandardButton replyBtn;
    replyBtn= QMessageBox::question( this, "FieldOpt", tr("Are you sure you want to quit?\n"), QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);
    if (replyBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
        //delete all ui's
        //extra ? app->close()?
       app->closeAllWindows();
    }
}

//------------- END MENU actions ----------------------------------------------------------------------------------------------------------|


//------Set/show-in-GUI methods -----------------------------------------------------------------------------------------------------------|

void MainWindow::setGlobalVariables(){
    ui->globalNameEdit->setText(settings_->name());
    ui->globalPathEdit->setText(settings_->output_directory());
    //default use a setter instead of... settings_->bookkeeper_tolerance()= 0.0;
    //check if bookkeeper_tolerance is set, if not default = 0.0
}

void MainWindow::setModelVariables(){
    switch (settings_->model()->reservoir().type) { //more types?
    case ::Utilities::Settings::Model::ReservoirGridSourceType::ECLIPSE:
        // set ui string value
        ui->modelTypeComboBox->setCurrentText("ECLIPSE");
        //test if the combo box contains the chosen reservoir grid source type, if not, addItem to the list (and make it currentItem) (for to run through the list)
        break;
    default:
        //Initial type ECLIPSE?
        break;
    }

    ui->modelPathEdit->setText(settings_->model()->reservoir().path);
}

void MainWindow::setSimulatorVariables(){
    switch (settings_->simulator()->type()) { //more types?
    case ::Utilities::Settings::Simulator::SimulatorType::ECLIPSE:
        // set ui string value
        ui->simTypeComboBox->setCurrentText("ECLIPSE");
        //test if the combo box contains the chosen simulator type, if not, addItem to the list (and make it currentItem) (for to run through the list)
        break;
    default:
        //Initial type (ECLIPSE?)
        break;
    }
    ui->simPathEdit->setText(settings_->simulator()->driver_file_path());

}

void MainWindow::setOptimizerVariables(){
    switch (settings_->optimizer()->type()) {
    case ::Utilities::Settings::Optimizer::OptimizerType::Compass:
        // set ui string value
        ui->optTypeComboBox->setCurrentText("Compass");
        //test if the combo box contains the chosen optimizer type, if not, addItem to the list (and make it currentItem) (for to run through the list)
        break;
    default:
        //initial type (Compass?)
        break;
    }
    switch (settings_->optimizer()->mode()){
    case ::Utilities::Settings::Optimizer::OptimizerMode::Maximize:
        ui->optModeComboBox->setCurrentText("Maximize");
        break;
    case ::Utilities::Settings::Optimizer::OptimizerMode::Minimize:
        ui->optModeComboBox->setCurrentText("Minimize");
        break;
    default:
       // ui->optModeComboBox->setCurrentText("Maximize");
        break;
    }

    optParametersDialog->setOptParametersVariables(settings_->optimizer()->parameters());
    optObjectiveDialog->setOptObjectiveType(settings_->optimizer()->objective().type);

    if (settings_->optimizer()->objective().weighted_sum.size() == 1){
        qDebug() << "Det er bare ett element i objective-lista";

        if( settings_->optimizer()->objective().weighted_sum.value(0).is_well_prop){
             optObjectiveDialog->setOptObjectiveWellVariables(settings_->optimizer()->objective().weighted_sum.value(0).is_well_prop, settings_->optimizer()->objective().weighted_sum.value(0).well);
        }
         else{
             optObjectiveDialog->setOptObjectiveIsWellPropCheckBox(settings_->optimizer()->objective().weighted_sum.value(0).is_well_prop);
         }
        //    optObjectiveDialog->setOptObjectiveWeightedSumComponents(settings_--->coeffisient, settings_---> property,settings_---> timeStep);
    }
    else {
        qDebug() << "Objective-lista er større enn én. Mer enn ett element";
    }
        optObjectiveDialog->setOptObjectiveWeightedSumComponents(settings_->optimizer()->objective().weighted_sum);
    // if only one element in Qlist<WeightesSumComponent> then go for this:  (under) or else set(QList<>);
    //    optObjectiveDialog->setOptObjectiveWeightedSumComponents(Coeffisient,Property Cumulative,TimeStep);

    // Utilities::Settings::Optimizer::Objective temp_objective_ = settings_->optimizer()->objective(); does not seem to work? wanted to shorten things

    //
        optConstraintDialog->setLocalConstraintsList(settings_->optimizer()->constraints());
        optConstraintDialog->setOptConstraintsVariables(settings_->optimizer()->constraints()); // trenger ingen argumenter her?????

}

//------ END Set/show-in-GUI methods ------------------------------------------------------------------------------------------------------|
