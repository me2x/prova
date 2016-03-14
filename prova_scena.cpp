#include "prova_scena.h"
#include "ui_prova_scena.h"

prova_scena::prova_scena(QGraphicsScene* parent): QGraphicsScene(parent), ui(new Ui::prova_scena)
{
    //ui->setupUi(this);
}
prova_scena::~prova_scena(){
    delete ui;
}