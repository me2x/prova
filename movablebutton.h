#ifndef MOVABLEBUTTON_H
#define MOVABLEBUTTON_H

#include <qt4/QtGui/QPushButton>
#include <QMouseEvent>
class MovableButton : public QPushButton
{
    Q_OBJECT
public:
MovableButton(QWidget *aaa) : QPushButton(aaa){}

protected:
    virtual void mouseMoveEvent(QMouseEvent* e);
    virtual void mousePressEvent ( QMouseEvent * e );
    virtual void mouseReleaseEvent ( QMouseEvent * e );
private:
    bool being_moved = false;
};

#endif // MOVABLEBUTTON_H
