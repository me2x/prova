#ifndef PROVA_WIDGET_2_H
#define PROVA_WIDGET_2_H

#include <qt4/QtGui/QWidget>
#include "movablebutton.h"


namespace Ui
{
class prova_widget_2;
}

class prova_widget_2 : public QWidget
{
    Q_OBJECT
public:
    explicit prova_widget_2(QWidget* parent = 0);
    ~prova_widget_2();

    
protected:
    virtual void mousePressEvent(QMouseEvent* );
    virtual void mouseReleaseEvent(QMouseEvent* );
    virtual void mouseDoubleClickEvent(QMouseEvent* );
    virtual void mouseMoveEvent(QMouseEvent* );

private:
    Ui::prova_widget_2* ui;
    bool is_drawing;
    std::list<MovableButton*> layer_1_buttons;
};

#endif // PROVA_WIDGET_2_H
