#include "provapopup.h"
#include "ui_provapopup.h"
#include <iostream>
ProvaPopup::ProvaPopup(QDialog* parent): QDialog(parent), ui(new Ui::ProvaPopup)
{
    ui->setupUi(this);
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(reject()));
    data.name = "";
}

ProvaPopup::~ProvaPopup(){
    delete ui;
}

void ProvaPopup::exec()
{
    QDialog::exec();
}
L4_Data* ProvaPopup::get_data()
{
return &data;
}
void ProvaPopup::set_data(L4_Data* data_in)
{
    data = *data_in;
}
void ProvaPopup::accept()
{
    QString text = ui->lineEdit->text();
    data.name = text.toStdString();
    //TODO controllo name non sia gia in uso
    if (data.name != ""){
        std::cout <<"name accepted"<<std::endl;
        QDialog::accept();
    }
    else 
    {
        std::cout <<"name refused"<<std::endl;
        QDialog::reject();
        
    }
}
void ProvaPopup::reject()
{
    std::cout <<"refuse button"<<std::endl;
    QDialog::reject();
}
