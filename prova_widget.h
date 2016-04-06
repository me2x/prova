#ifndef PROVA_WIDGET_H
#define PROVA_WIDGET_H

#include <qt4/QtGui/QWidget>
#include <qpushbutton.h>
#include "provariquadro.h"
#include <QtGui>
#include <QtCore>
#include "provapopup.h"
#include "provaporte.h"
#include "l4_data.h"
#include "portselect.h"
#include <memory>
namespace Ui
{
class prova_widget;
}

class prova_widget : public QWidget
{
    Q_OBJECT
public slots:
    void Layer_1_press_event();
    void Layer_2_press_event();
    void component_clicked();
    void redraw_line();
    void break_line_drawing();
    void mousePressEvent(QMouseEvent * e);
    void create_L1_obj();
    void create_L2_obj();
    void no_data();
    void update_L1_object();
    void update_L2_object();
    void update_object();
    void update_object2();
    void finalize_line();
private:
   // std::list<ProvaRiquadro*> layer_1_buttons;
    ProvaRiquadro* starting_object; 
    ProvaRiquadro* arrival_object;
    QGraphicsLineItem* curr_line_item;
    Ui::prova_widget *ui;
    bool is_drawing;
    QGraphicsScene *scene;
    QTimer* timer;
    std::shared_ptr<ProvaPopup> popup;
    std::shared_ptr<ProvaPorte> porte;
    std::shared_ptr<PortSelect> ps;
    //PortSelect* ps;
    bool doubleclick;
    std::list<Arrow*> arrows;
    std::map<ProvaRiquadro*, L4_Data*> graphical_to_data;
public:
    explicit prova_widget(QWidget* parent = 0);
    ~prova_widget();


};

#endif // PROVA_WIDGET_H
