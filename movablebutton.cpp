#include "movablebutton.h"
#include <iostream>

void MovableButton::mouseMoveEvent( QMouseEvent *event )
{
        if( event->buttons() & Qt::LeftButton )
        {
            being_moved=true;
    std::cout << event->globalPos().x() << "parent x: "<<parentWidget()->whatsThis().toStdString()<<std::endl;
    std::cout << parentWidget()->mapToGlobal(parentWidget()->rect().topLeft()).x() << std::endl;
    if(event->globalPos().y()-parentWidget()->mapToGlobal(parentWidget()->rect().topLeft()).y() <= (parentWidget()->size().height()-this->height()) &&
        event->globalPos().y()-parentWidget()->mapToGlobal(parentWidget()->rect().topLeft()).y() >= 0 && 
        event->globalPos().x()-parentWidget()->mapToGlobal(parentWidget()->rect().topLeft()).x() >= 0)
    {
    move( event->globalPos().x()-parentWidget()->mapToGlobal(parentWidget()->rect().topLeft()).x(),
                      event->globalPos().y()-parentWidget()->mapToGlobal(parentWidget()->rect().topLeft()).y());
    std::cout << "IF VALUES: "<<event->globalPos().y()-parentWidget()->mapToGlobal(parentWidget()->rect().topLeft()).y() <<std::endl;
    std::cout << (parentWidget()->size().height()-this->height()) <<std::endl;
    }
     //porta oltre e smette di muovere. e quindi non aggiorna la minwidth. bottone sembra sparire invece è solo out of scope.      
        }
        
        
        //rifare e invece che tenere come termine di paragone curr width settare ext button.
        
}
void MovableButton::mousePressEvent(QMouseEvent* e)
{
    QAbstractButton::mousePressEvent(e);
}
void MovableButton::mouseReleaseEvent(QMouseEvent* event)
{
    if (!being_moved)
    {
        QAbstractButton::mouseReleaseEvent(event);
    }
    else
    {
        being_moved = false;
  std::cout<<"before: "<< parentWidget()->size().width()<<std::endl;
  std::cout<<parentWidget()->size().height()<<std::endl;
  std::cout<<"aaaa: "<< event->globalPos().x()-parentWidget()->mapToGlobal(parentWidget()->rect().topLeft()).x()<<std::endl;
  std::cout<<event->globalPos().y()-parentWidget()->mapToGlobal(parentWidget()->rect().topLeft()).y()<<std::endl;
  
  //parentWidget()->adjustSize();
  parentWidget()->setMinimumWidth(std::max(event->globalPos().x()-parentWidget()->mapToGlobal(parentWidget()->rect().topLeft()).x()+this->width(), parentWidget()->size().width()));
  std::cout<<"after:" <<parentWidget()->size().width()<<std::endl;
  std::cout<<parentWidget()->size().height()<<std::endl;
    }
}



#include "movablebutton.moc"
