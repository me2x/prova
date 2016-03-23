#ifndef PROVA_WIDGET_H
#define PROVA_WIDGET_H

#include <qt4/QtGui/QWidget>
#include <qpushbutton.h>
#include "provariquadro.h"
#include <QtGui>
#include <QtCore>
#include "provapopup.h"

namespace Ui
{
class prova_widget;
}

class prova_widget : public QWidget
{
    Q_OBJECT
public slots:
    void Layer_1_press_event();
    void component_clicked();
    void redraw_line();
    void break_line_drawing();
    void mousePressEvent(QMouseEvent * e);
    void create_L1_obj();
    void no_data();
    void update_L1_object();
    void update_object();
private:
   // std::list<ProvaRiquadro*> layer_1_buttons;
    ProvaRiquadro* starting_object; 
    QGraphicsLineItem* curr_line_item;
    Ui::prova_widget *ui;
    bool is_drawing;
    QGraphicsScene *scene;
    QTimer* timer;
    ProvaPopup* popup;
    bool doubleclick;
public:
    explicit prova_widget(QWidget* parent = 0);
    ~prova_widget();


};

#endif // PROVA_WIDGET_H
