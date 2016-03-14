#ifndef PROVA_SCENA_H
#define PROVA_SCENA_H

#include <qt4/QtGui/QGraphicsScene>
#include <QGraphicsView>
namespace Ui
{
class prova_scena;
}

class prova_scena : public QGraphicsScene
{
    Q_OBJECT

private:
    Ui::prova_scena* ui;
public:
    explicit prova_scena(QGraphicsScene* parent = 0);
    ~prova_scena();
};

#endif // PROVA_SCENA_H
