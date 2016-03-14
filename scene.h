#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
/*************************************************************************************/
/******************** Scene representing the simulated landscape *********************/
/*************************************************************************************/

class scene : public QGraphicsScene
{ 
    Q_OBJECT

signals:
  void  message( QString );                                  // info text message signal

protected:
  void  mousePressEvent( QGraphicsSceneMouseEvent* );        // receive mouse press events
public:
  scene();                                      // constructor
};

#endif  // SCENE_H
