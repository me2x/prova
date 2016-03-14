#include "scene.h"

/*************************************************************************************/
/******************** Scene representing the simulated landscape *********************/
/*************************************************************************************/

/************************************ constuctor *************************************/

scene::scene() : QGraphicsScene()
{
}
void  scene::mousePressEvent( QGraphicsSceneMouseEvent* event )
{
  // only interested if left mouse button pressed
  if ( event->button() != Qt::LeftButton ) return;

  // emit informative message
  qreal  x = event->scenePos().x();
  qreal  y = event->scenePos().y();
  emit message( QString("Clicked at %1,%2").arg(x).arg(y) );
}

#include "scene.moc"
