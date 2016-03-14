#include "prova_widget_2.h"
#include "ui_prova_widget_2.h"
#include <iostream>

prova_widget_2::prova_widget_2(QWidget* parent): QWidget(parent), ui(new Ui::prova_widget_2)
{
    ui->setupUi(this);
//    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(Layer_1_press_event()));
    
}

prova_widget_2::~prova_widget_2(){
    delete ui;
}
void prova_widget_2::mousePressEvent(QMouseEvent* e)
{
    std::cout<<"mousepressevent"<<childAt(e->pos())->whatsThis().toStdString()<<std::endl;
}

void prova_widget_2::mouseReleaseEvent(QMouseEvent* )
{
    std::cout<<"mousereleeaseevent"<<std::endl;
}

void prova_widget_2::mouseDoubleClickEvent(QMouseEvent* )
{
    std::cout<<"mousedoubleclickevent"<<std::endl;
}

void prova_widget_2::mouseMoveEvent(QMouseEvent* )
{
    std::cout<<"mousemoveevent"<<std::endl;
}
