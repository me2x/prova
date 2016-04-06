#include "provaporte.h"
#include "ui_provaporte.h"
#include <QComboBox>
#include <QSpinBox>
#include "port.h"
#include <iostream>

ProvaPorte::ProvaPorte(QDialog* parent): QDialog(parent), ui(new Ui::ProvaPorte)
{
    ui->setupUi(this);
    connect(ui->add,SIGNAL(clicked()),this,SLOT(add_table_line()));
    connect(ui->remove,SIGNAL(clicked()),this,SLOT(remove_table_line()));
    connect(ui->ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(reject()));
    data = new L4_Data();
    data->name = "";
}


void ProvaPorte::add_table_line()
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    QComboBox* settingA = new QComboBox();
    settingA->addItem("100");
    settingA->addItem("200");
    ui->tableWidget->setCellWidget ( ui->tableWidget->rowCount()-1, 1, settingA );
    
    QComboBox* settingB = new QComboBox();
    settingB->addItem("True");
    settingB->addItem("False");
    ui->tableWidget->setCellWidget ( ui->tableWidget->rowCount()-1, 3, settingB );
    
    QSpinBox* spin = new QSpinBox();
    ui->tableWidget->setCellWidget ( ui->tableWidget->rowCount()-1, 0, spin );
    
    QSpinBox* spin2 = new QSpinBox();
    ui->tableWidget->setCellWidget ( ui->tableWidget->rowCount()-1, 2, spin2 );
   
    /* getter
     QComboBox *myCB = qobject_cast<QComboBox*>(ui->tableWidget_4->cellWidget(0,0));
     InputComboData << myCB->currentText();
     
     */
}
void ProvaPorte::remove_table_line()
{
    ui->tableWidget->removeRow(ui->tableWidget->rowCount()-1);
}


void ProvaPorte::accept()
{
    data->ports.clear();
     for (int i = 0; i< ui->tableWidget->rowCount();i++)
    {
        Port* port = new Port();
        QSpinBox *id = qobject_cast<QSpinBox*>(ui->tableWidget->cellWidget(i,0));
        //TODO check != 0
        port->id = id->value();
        QComboBox *priority = qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(i,1));
        port->priority = priority->currentText().toInt();
        
        QSpinBox *ass_id = qobject_cast<QSpinBox*>(ui->tableWidget->cellWidget(i,2));
        port->associate_id = ass_id->value();
        QComboBox *isMaster = qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(i,3));
        port->is_master = isMaster->currentText()=="True"?true:false;
        
        data->ports.push_back(port);
    }
    QString text = ui->lineEdit_2->text();
    data->name = text.toStdString();
    //TODO controllo name non sia gia in uso
    if (data->name != ""){
        std::cout <<"name accepted"<<std::endl;
        QDialog::accept();
    }
    else 
    {
        std::cout <<"name refused"<<std::endl;
        QDialog::reject();
        
    }
   
}
ProvaPorte::~ProvaPorte(){
    delete ui;
}

void ProvaPorte::reject()
{
    std::cout <<"refuse button"<<std::endl;
    QDialog::reject();
}

void ProvaPorte::exec()
{
    QDialog::exec();
}
L4_Data* ProvaPorte::get_data()
{
return data;
}
void ProvaPorte::set_data(L4_Data* data_in)
{
    data = data_in;
    ui->lineEdit_2->setText(QString::fromStdString(data->name));
    for (std::list<Port*>::iterator it = data->ports.begin();it != data->ports.end();++it)
    {
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    QComboBox* settingA = new QComboBox();
    settingA->addItem("100");
    settingA->addItem("200");
    settingA->setCurrentIndex((*it)->priority == 100 ? 0 : 1);
    ui->tableWidget->setCellWidget ( ui->tableWidget->rowCount()-1, 1, settingA );
    
    QComboBox* settingB = new QComboBox();
    settingB->addItem("True");
    settingB->addItem("False");
    settingB->setCurrentIndex((*it)->is_master == true ? 0 : 1);
    ui->tableWidget->setCellWidget ( ui->tableWidget->rowCount()-1, 3, settingB );
    
    QSpinBox* spin = new QSpinBox();
    spin->setValue((*it)->id);
    ui->tableWidget->setCellWidget ( ui->tableWidget->rowCount()-1, 0, spin );
    
    QSpinBox* spin2 = new QSpinBox();
    spin2->setValue((*it)->associate_id);
    ui->tableWidget->setCellWidget ( ui->tableWidget->rowCount()-1, 2, spin2 );
   
    }
}