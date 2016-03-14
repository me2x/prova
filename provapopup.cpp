#include "provapopup.h"
#include "ui_provapopup.h"

ProvaPopup::ProvaPopup(QDialog* parent): QDialog(parent), ui(new Ui::ProvaPopup)
{
    ui->setupUi(this);
//    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(Layer_1_press_event()));
    
}

ProvaPopup::~ProvaPopup(){
    delete ui;
}

void ProvaPopup::exec()
{
    QDialog::exec();
}
