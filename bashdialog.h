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


private slots:

    void setupBashDialog(); //!<

    void fixToolTips();  //!<

    void updateBashDialog();  //!<

    void updateBASHcommands();  //!<

    void on_buttonBox_accepted();  //!<

    void on_buttonBox_rejected();  //!<

    void on_addItemBashListButton_clicked();  //!<

    void on_removeItemBashListButton_clicked();  //!<

    void on_addCustomItemBashListButton_clicked();  //!<


private:
    Ui::BashDialog *ui; //!<
    Qt::ItemFlag *itemFlag; //!<
};

#endif // BASHDIALOG_H
