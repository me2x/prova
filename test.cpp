#include "test.h"
#include "ui_test.h"
#include <iostream>
test::test(QWidget* parent) : QWidget(parent),ui(new Ui::test)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(mousePressEvent()));
}
test::~test(){
    delete ui;
}
void  test::mousePressEvent()
{
    emit message( QString("Clicked"));
    std::cout<<"clicked" <<std::endl;
    return;
}