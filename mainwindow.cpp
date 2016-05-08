// Karoline Louise Rykkelid, Fall 2015

//Included header files:
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    setupMainWindow();
    setupDialogs();
    setToolTips();
    setupPlaceholderTexts();
    fixIconOnButton();
    connectAllStuff();
}


MainWindow::~MainWindow(){
    delete ui;
    //delete bashDialog; //Have to delete it, since bashDialog is set up modelless (can move back and forth between windows/dialogs), no need to cause do not create ui's here
    //delete mWellDialog; //trenger ikke å fjerne på denne måten
}

void MainWindow::setupMainWindow(){
    ui->setupUi(this);
    this->setWindowTitle("FieldOpt - "+ ui->tabWidget->tabText(0)); //FieldOpt - global

    ui->tabWidget->setCurrentIndex(0); // Sets the initial tab to be the global tab
    ui->optTypeLine->setText(ui->optTypeComboBox->currentText());

    // SKAL ENDRES TIL Å LAGES OG GJELDE AKKURAT DET SOM BLIR TASTET INN.
    settings_ = new Utilities::Settings::Settings("/home/karolinr/Documents/GitHub/FieldOpt/FieldOpt/GTest/Utilities/driver/driver.json", "/home/karolinr");

}

void MainWindow::setupDialogs(){
    bashDialog = new BashDialog();
    mWellDialog = new MWellDialog();
    optParametersDialog = new OptParametersDialog();
    optConstraintDialog = new OptConstraintDialog();
    optObjectiveDialog = new OptObjectiveDialog();
    setupAboutDialog(); // Set up the "About FieldOpt" dialog

}

void MainWindow::setupAboutDialog(){
    aboutDialog = new QDialog;
    uiAbout = new Ui::AboutDialog;
    uiAbout->setupUi(aboutDialog);
    aboutDialog->setWindowTitle("About FieldOpt");
}


//----------Design GUI methods ---------------------------------------------------------------------------|
void MainWindow::setToolTips(){
    //Global - tool tip
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

    ui->modelControlTimesListWidget->setToolTip("List of Control times");
    ui->modelAddControlTimeButton->setToolTip("Add control time (item) to the list");
    ui->modelRemoveControlTimeButton->setToolTip("Remove selected (item) control time");
    ui->modelControlTimesSpinBox->setToolTip("Control time (Integer)");


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
    //Global
    ui->globalNameEdit->setPlaceholderText("Enter name to be used when generating output file names");
    ui->globalPathEdit->setPlaceholderText("Path to the output files ");
    //Model
    ui->modelPathEdit->setPlaceholderText("Path to the grid file (.GRID or .EGRID)");
    //Simulator
    ui->simPathEdit->setPlaceholderText("Path to the driver file (.DATA)");
}

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

    //Global - Bookkeeper checbox, label and enabler
    connect( ui->globalBookkeepCheckBox, SIGNAL(toggled(bool)), ui->globalBookkeepTolLabel, SLOT(setEnabled(bool) ));
    connect( ui->globalBookkeepCheckBox, SIGNAL(toggled(bool)), ui->globalBookkeepTolerancedSpinBox, SLOT(setEnabled(bool)) );
}

void MainWindow::fixIconOnButton(){
    QPixmap pixmap(":/Images/pensil");
    QIcon EditIcon(pixmap);
    ui->globalOutputPathEditButton->setIcon(EditIcon);
    ui->globalOutputPathEditButton->setIconSize(QSize(27,27));
    ui->globalOutputPathEditButton->setFixedSize(QSize(27,27));

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
    //Something here. Sender dem til JSONfila

    //if something - everything correctly done
    QMessageBox::information(this, "Save", "You have now saved (and/or updated) the JSON file.", QMessageBox::Ok, 0 );
}


void MainWindow::importJSONfile(){
    setGlobalVariables();
    setModelVariables();
    setSimulatorVariables();
    setOptimizerVariables();
}


//------------- Global actions ------------------------------------------------------------------------------------------------------|

void MainWindow::on_globalBrowseButton_clicked(){

    //Have this here so it jumps to right tab if we use the edit button shortcut
    ui->tabWidget->setCurrentIndex(0); //!< Sets the current tab to "global" tab
    ui->globalPathEdit->setFocus(); //!< The global path is set to current focus

    QString temp_output_directory = browseFileDialog->getExistingDirectory(this, tr("Choose Directory"),"/home",
                                                                        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
   // browseFileDialog->setFocus();
    if(!temp_output_directory.isNull()){ //!< if you chose a path with the file dialog, the line edit is changed. If not, nothing happens
        ui->globalPathEdit->setText(temp_output_directory); //!< Sets the text in the lineEdit field to be the choosen path to the directory
        settings_->simulator()->set_output_directory(temp_output_directory);
        settings_->set_output_directory(temp_output_directory);
    }
}

void MainWindow::on_globalBookkeepCheckBox_toggled(bool checked){
    if (!checked){
        ui->globalBookkeepTolerancedSpinBox->setValue(0.0);
    }
}

void MainWindow::on_globalNameEdit_textChanged(const QString &name){
   settings_->set_name(name);
}

void MainWindow::on_globalPathEdit_textChanged(const QString &output_directory){
    settings_->set_output_directory(output_directory);
    //settings_->simulator()->set_output_directory(output_directory);
    //KANSKJE sette direkte fra (evt. sette begge?)
}

void MainWindow::on_globalBookkeepTolerancedSpinBox_valueChanged(double bookkeep_tolerance){
 settings_->set_bookkeeper_tolerance(bookkeep_tolerance);
}

//--------END global actions---------------------------------------------------------------------------------------------------------|


//------------- Model actions -------------------------------------------------------------------------------------------------------|

void MainWindow::on_modelBrowseButton_clicked(){
    QString tempGridPath = browseFileDialog->getOpenFileName(this, tr("Choose grid file (.GRID or .EGRID)"), "/home", tr("Grid files (*.GRID *.EGRID)"));

    if(!tempGridPath.isNull()){  //if choosing a path with the file dialog, the line edit is changed. If not, nothing happens
        ui->modelPathEdit->setText(tempGridPath);
    }
}

void MainWindow::on_modelSetWellVariablesButton_clicked(){
    mWellDialog->show();
    mWellDialog->raise();
    mWellDialog->activateWindow();
}

void MainWindow::on_modelTypeComboBox_currentTextChanged(const QString &model_grid_type){

    if (QString::compare(model_grid_type, "ECLIPSE" ) == 0 ){
        settings_->model()->set_reservoir_grid_source_type(Utilities::Settings::Model::ReservoirGridSourceType::ECLIPSE);
    }
}

void MainWindow::on_modelPathEdit_textChanged(const QString &model_grid_path){
    settings_->model()->set_reservoir_grid_path(model_grid_path);
}

void MainWindow::on_modelAddControlTimeButton_clicked(){
    QString string_box_value = QStringLiteral("%1").arg(ui->modelControlTimesSpinBox->value());
    QList<QListWidgetItem *> existing_items = ui->modelControlTimesListWidget->findItems(string_box_value,Qt::MatchExactly);

    if(existing_items.size() == 0){
        ui->modelControlTimesListWidget->addItem(string_box_value);
        //update control times list to Utilities
         updateModelControlTimesToUtilities();
    }
    //How to sort by integer values.. can change List Widget from String to Int?
    ui->modelControlTimesListWidget->sortItems(Qt::SortOrder::AscendingOrder);

}

void MainWindow::on_modelRemoveControlTimeButton_clicked(){
    delete ui->modelControlTimesListWidget->currentItem();
    //update control times list to Utilities
    updateModelControlTimesToUtilities();
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

void MainWindow::on_simChooseBashComButton_clicked(){
    //WANT? be able to click both windows when bash command is open, or not??
    // må bare lages én gang pr mainWindow, men åpnes og lukkes. Dataen spares på og skal være den samme helt til man lukker programmet.
    // BashDialog bashDialog;
    // bashDialog.setModal(true);
    // bashDialog.exec();
     bashDialog->show();
     bashDialog->raise();
     bashDialog->activateWindow();
}

void MainWindow::on_simTypeComboBox_currentTextChanged(const QString &sim_type){
    //sending updates to Utilites/setting variables
    if (QString::compare(sim_type, "ECLIPSE" ) == 0 ){
        settings_->simulator()->set_type(Utilities::Settings::Simulator::SimulatorType::ECLIPSE);
    }
    else if( QString::compare(sim_type, "ADGPRS" ) == 0 ){
        settings_->simulator()->set_type(Utilities::Settings::Simulator::SimulatorType::ADGPRS);
    }
}

void MainWindow::on_simPathEdit_textChanged(const QString &driver_path){
    settings_->set_driver_path(driver_path);
   //settings_->simulator()->set_driver_file_path(driver_path);
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


void MainWindow::on_optTypeComboBox_currentTextChanged(const QString &opt_type){
    if( QString::compare(opt_type, "Compass" ) == 0 ){
        settings_->optimizer()->set_optimizer_type(Utilities::Settings::Optimizer::OptimizerType::Compass);
    }
}

void MainWindow::on_optModeComboBox_currentTextChanged(const QString &opt_mode){
    if( QString::compare(opt_mode, "Maximize" ) == 0 ){
        settings_->optimizer()->set_optimizer_mode(Utilities::Settings::Optimizer::OptimizerMode::Maximize);
    }
    else if( QString::compare(opt_mode, "Minimize" ) == 0 ){
        settings_->optimizer()->set_optimizer_mode(Utilities::Settings::Optimizer::OptimizerMode::Minimize);
    }
}


//-------------END optimizer actions-------------------------------------------------------------------------------------------------|




//------------- MENU actions --------------------------------------------------------------------------------------------------------|

//Import/open JSON file
void MainWindow::on_actionOpen_JSON_file_triggered(){

    if(ui->globalPathEdit->text().size() == 0){
       QMessageBox::information(this, "Missing output path", "Please fill out the path to the output directory and/or browse, in the Global tab before opening the JSON file.", QMessageBox::Ok, 0);
        return;
    }
    // browseFileDialog.setLabelText (QFileDialog::Accept, "Import" );//!< Sets the button text to "Import" in the file dialog må kjøres egen .exec for å kjøre denne spesielle
      QString tempPreJSONPath = browseFileDialog->getOpenFileName(this, tr("Choose JSON file to import"), "/home", tr("JSON (*.json)"));

      if(!tempPreJSONPath.isEmpty()){ // if you choose a path with the file dialog, the line edit is changed. If not, nothing happens
        ui->jsonPathLine->setText(tempPreJSONPath);
        ui->jsonPathLine->setEnabled(true);
        ui->jsonPathLabel->setEnabled(true);

        // Need to disable json line stuff, when no text there (deleted or regret choosing a json file), when you create a new json file here, the json position will be the same as output path?
        // settings_ = new Utilities::Settings::Settings(ui->jsonPathLine->text(), ui->globalPathEdit->text()); // Skal endre og uncommente senere
       importJSONfile();
      }
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

//--------------HELP-METHODS --------------------------------------------------------------------------------------------------------------|

void MainWindow::updateModelControlTimesToUtilities(){
    QList<int> control_list;
    int int_value;
    control_list.clear(); //since using append, need to clear?

    for (int i = 0; i < ui->modelControlTimesListWidget->count(); ++i) {
        //konverte QString to int.
        int_value = ui->modelControlTimesListWidget->item(i)->text().toInt();
        control_list.append(int_value);
    }

//sort?? evt. konvertere og sortere i den andre metoden
   // control_list.sort;
// slik at sortert før den kommer hit...
    settings_->model()->set_control_times(control_list);
}
//--------------HELP-METHODS --------------------------------------------------------------------------------------------------------------|


//------Set/show-in-GUI methods -----------------------------------------------------------------------------------------------------------|

void MainWindow::setGlobalVariables(){
    ui->globalNameEdit->setText(settings_->name());
    ui->globalPathEdit->setText(settings_->output_directory());
    //default use a setter instead of... settings_->bookkeeper_tolerance()= 0.0;
    //check if bookkeeper_tolerance is set, if not default = 0.0

    // det har å gjøre med bookkeeperen som holder oversikt over hvilke sett med variable som har blitt evaluert,
    // sånn at man ikke evaluerer samme to ganger. Hvis tolerance er større enn 0 vil man også droppe å evaluere
    // variable som er nære de som allerede har blitt evaluert (hvis tolerance er 5 vil et sett med variable som
    //er "lengde" 5 unna et allerede evaulert sett bli droppe

    //if() checkbox == true, setCheckboxEnabled setbookkeeperTol
    if (settings_->bookkeeper_tolerance() != 0.0 ){
        ui->globalBookkeepCheckBox->setChecked(true);
        ui->globalBookkeepTolerancedSpinBox->setValue(settings_->bookkeeper_tolerance());
    }
    else{
        ui->globalBookkeepTolerancedSpinBox->setValue(0.0);
    }
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

    //kan ha getter her?? på reservoir path
    ui->modelPathEdit->setText(settings_->model()->reservoir().path);

    //control times - from int to QString
    QList<int> int_control_times_list = settings_->model()->control_times();
    QStringList string_control_list;
    for (int i = 0; i < int_control_times_list.size() ; ++i) {
        string_control_list.append(QStringLiteral("%1").arg(int_control_times_list.at(i)));
    }
    ui->modelControlTimesListWidget->clear();
    ui->modelControlTimesListWidget->addItems(string_control_list);
}

void MainWindow::setSimulatorVariables(){
    switch (settings_->simulator()->type()) {
    case Utilities::Settings::Simulator::SimulatorType::ECLIPSE:
        // set ui string value
        ui->simTypeComboBox->setCurrentText("ECLIPSE");
        break;
    case Utilities::Settings::Simulator::SimulatorType::ADGPRS:
        ui->simTypeComboBox->setCurrentText("ADGPRS");
        break;
    default:
        //Initial type (ECLIPSE?) There is testing in the simulator.cpp already, that takes care of non-existing types
        break;
    }
    ui->simPathEdit->setText(settings_->simulator()->driver_file_path());
    bashDialog->setBashCommandsImport(settings_->simulator());
}

void MainWindow::setOptimizerVariables(){
    switch (settings_->optimizer()->type()) {
    case ::Utilities::Settings::Optimizer::OptimizerType::Compass:
        // set ui string value
        ui->optTypeComboBox->setCurrentText("Compass");
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

    //checking if the weighted sum component list isn't empty
    //IS CHECKED IN EINAR'S CODE, DO I NEED TO CHECK IT HERE???
    if (settings_->optimizer()->objective().weighted_sum.size() > 0){
        qDebug() << "Objective-lista inneholder noe.";
        optObjectiveDialog->setOptObjectiveWeightedSumComponents(settings_->optimizer()->objective().weighted_sum);
        // getter her? på weigted sum
    }
    //checking if the constraint list isn't empty
    if (settings_->optimizer()->constraints()->size() > 0){
        optConstraintDialog->setOptConstraintsVariables(settings_->optimizer()->constraints());
    }
}



//------ END Set/show-in-GUI methods ------------------------------------------------------------------------------------------------------|


