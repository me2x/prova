#include "prova_widget.h"
#include "ui_prova_widget.h"
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/math/constants/constants.hpp>
#include <QTimer>
#include "portselect.h"
prova_widget::prova_widget(QWidget* parent): QWidget(parent), ui(new Ui::prova_widget)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(Layer_1_press_event()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(Layer_2_press_event()));
    scene = new QGraphicsScene(this);
    scene->setObjectName("scene");
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setObjectName("graphicview");
    scene->setParent(ui->graphicsView);
    is_drawing = false;
    starting_object = 0;
    
    
    
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(redraw_line()));
    timer->start(100);
}
prova_widget::~prova_widget(){
    delete ui;
}
void prova_widget::Layer_1_press_event()
{
    popup.reset(new ProvaPopup());
      
    connect(popup.get(),SIGNAL(accepted()),this,SLOT(create_L1_obj()));
    connect(popup.get(),SIGNAL(rejected()),this,SLOT(no_data()));
    
    popup->exec();
    popup->activateWindow();
  
    std::cout<<"layer 1 press event triggered"<<std::endl;
}
void prova_widget::Layer_2_press_event()
{
porte.reset(new ProvaPorte());
      
    connect(porte.get(),SIGNAL(accepted()),this,SLOT(create_L2_obj()));
    connect(porte.get(),SIGNAL(rejected()),this,SLOT(no_data()));
    
    porte->exec();
    porte->activateWindow();
  
    std::cout<<"layer 1 press event triggered"<<std::endl;
}

void prova_widget::no_data()
{
    std::cout <<"no data provided in the popup"<<std::endl;
}


void prova_widget::create_L1_obj()
{
//dato che non fa la new, quando faccio reset di popup elimina il precedente e quindi segfaulta.
//risolvere con smartptr, nel momento in cui si perfeziona il tutto. ora puoi sbattertene le palle :D
//e procedere domattina con l'elimina
    
     L4_Data* data = popup->get_data();
     std::cout<<data->name<<std::endl;
     ProvaRiquadro *temp= new ProvaRiquadro();
     temp->setLayer(0);
     scene->addItem(temp);
     connect(temp,SIGNAL(riquadroCliccatoSx()),this,SLOT(component_clicked()));
     connect(temp,SIGNAL(riquadroMosso()),this,SLOT(break_line_drawing()));
     connect(temp,SIGNAL(riquadroCliccatoDx()),this,SLOT(break_line_drawing()));
     connect(temp,SIGNAL(riquadroDoubleClick()),this,SLOT(update_L1_object()));
     connect(scene,SIGNAL(selectionChanged()),temp,SLOT(provaselected()));
     temp->text->setPlainText(QString::fromStdString(data->name));
     graphical_to_data.insert(std::make_pair(temp,data));
     std::cout<<scene->parent()->objectName().toStdString()<<std::endl;
     
     std::cout<<ui->graphicsView->parentWidget()->objectName().toStdString()<<std::endl;
     
     std::cout<<ui->scrollAreaWidgetContents->parentWidget()->objectName().toStdString()<<std::endl;
     //temp->show();
     //temp->setText(QString::fromStdString(boost::lexical_cast<std::string>(temp)));
     
 //connect(temp, SIGNAL(clicked(bool)), this, SLOT(component_clicked()));
  //std::cout<<"before: "<< ui->scrollAreaWidgetContents->size().width()<<std::endl;
  //std::cout<<ui->scrollAreaWidgetContents->size().height()<<std::endl;
 // scene->addWidget(temp);
 // ui->scrollAreaWidgetContents->adjustSize();
  
 // std::cout<<"after:" <<ui->scrollAreaWidgetContents->size().width()<<std::endl;
  //std::cout<<ui->scrollAreaWidgetContents->size().height()<<std::endl;
  //update();
  
}
void prova_widget::create_L2_obj() //NTS sono praticamente uguali se non fosse per l'updateL2. e il fatto che usa un qdialog diverso. se anche update L2 resta simile prova a pensare funzione univoca.
{

     L4_Data* data = porte->get_data();
     std::cout<<data->name<<std::endl;
     ProvaRiquadro *temp= new ProvaRiquadro();
     temp->setLayer(1);
     scene->addItem(temp);
     connect(temp,SIGNAL(riquadroCliccatoSx()),this,SLOT(component_clicked()));
     connect(temp,SIGNAL(riquadroMosso()),this,SLOT(break_line_drawing()));
     connect(temp,SIGNAL(riquadroCliccatoDx()),this,SLOT(break_line_drawing()));
     connect(temp,SIGNAL(riquadroDoubleClick()),this,SLOT(update_L2_object()));
     connect(scene,SIGNAL(selectionChanged()),temp,SLOT(provaselected()));
     temp->text->setPlainText(QString::fromStdString(data->name));
     graphical_to_data.insert(std::make_pair(temp,data));
     std::cout<<scene->parent()->objectName().toStdString()<<std::endl;
     
     std::cout<<ui->graphicsView->parentWidget()->objectName().toStdString()<<std::endl;
     
     std::cout<<ui->scrollAreaWidgetContents->parentWidget()->objectName().toStdString()<<std::endl;
}

void prova_widget::component_clicked()
{
        std::cout<<"component_clicked"<<std::endl;
        QPoint p1 = QCursor::pos();
        QPoint p2 = ui->graphicsView->mapFromGlobal(p1);
        QPointF p = ui->graphicsView->mapToScene(p2);
        QGraphicsItem* item_tmp =  scene->itemAt(p.x()-3, p.y()-3); //NON HO ANCORA CAPITO XK SI PERDA 3px nella conversione. 
        //che poi la domanda fondamentale è sono 3 qua e x altrove? xk in tal caso il fix non  funziona...
        // QPoint p = ui->frame_6->mapFromGlobal(QCursor::pos());
        std::cout<<"item catched"<<std::endl;
        std::cout<<"item catched"<<item_tmp->type() <<std::endl;
        std::cout<<"item catched"<<std::endl;
        QPen blackpen = QPen(Qt::black);
        
        while (item_tmp->type() != ProvaRiquadro::ProvaRiquadro_type) //qtextgraphicitem
        {
            std::cout<<"item is text"<<std::endl;
            QList<QGraphicsItem*> items;
            QPointF point = QPointF(p.x()-3, p.y()-3);
            items = scene->items(point, Qt::IntersectsItemShape,Qt::AscendingOrder,QTransform());
            std::cout<<items.size()<<std::endl;
            item_tmp = items.at(items.size()-2);
        }
        ProvaRiquadro* item = qgraphicsitem_cast<ProvaRiquadro*>(item_tmp);
        std::cout<<"item is: "<<item<<std::endl;
        std::cout<<"item is: "<<item->text->toPlainText().toStdString()<<std::endl;
        if (item != nullptr && item != 0)
        {
            if(is_drawing)
            {
                is_drawing = false;
                scene->removeItem(curr_line_item);
                if(item->starting_lines.count(starting_object)==0)
                {
                    std::cout<<"test: precall di portselect"<<std::endl;
                    arrival_object = item;
                    std::cout<<"arrival set"<<std::endl;
//                    delete ps;
                    ps.reset(new PortSelect());
                    std::cout<<"reset done"<<std::endl;
                    ps->set_data(graphical_to_data.at(starting_object),graphical_to_data.at(arrival_object));
                    std::cout<<"data set set"<<std::endl;
                    connect(ps.get(),SIGNAL(accepted()),this,SLOT(finalize_line()));
                    connect(ps.get(),SIGNAL(rejected()),this,SLOT(break_line_drawing()));
                    std::cout<<"connection set"<<std::endl;
                    ps->exec();
                    ps->activateWindow();
                    
                   std::cout<<"test: postcall di portselect"<<std::endl;
                   
                    }
                    
                    
                    std::cerr<<"selecteditemscleardone"<<scene->selectedItems().size()<<std::endl;
            }
            else
            {
                is_drawing = true;
                starting_object = item;
                QPoint p1 = QCursor::pos();
                QPoint p2 = ui->graphicsView->mapFromGlobal(p1);
                QPointF p = ui->graphicsView->mapToScene(p2);
                QLineF newline(item->x()+item->boundingRect().center().x(),item->y()+item->boundingRect().bottom(),p.x()-3, p.y()-3);
                curr_line_item = scene->addLine(newline,blackpen);
              }
        }
        else 
            std::cout << " other type, value is: " << item_tmp->type()<<std::endl;

}


//funzione update: if(is_drawing) drawline arrive_point to qcursor::pos.
//piu che drawline, updateline
void prova_widget::redraw_line()
{
    if (!is_drawing) return;
   // std::cout<<"inside redraw line" <<std::endl;
    
        QPen blackpen = QPen(Qt::black);
        //std::cout << "curr line != 0" <<std::endl;
        QPoint p1 = QCursor::pos();
        QPoint p2 = ui->graphicsView->mapFromGlobal(p1);
        QPointF p = ui->graphicsView->mapToScene(p2);
        scene->removeItem(curr_line_item);
        
        QLineF newline(starting_object->x()+starting_object->boundingRect().center().x(),starting_object->y()+starting_object->boundingRect().bottom(),p.x()-3, p.y()-3);
        curr_line_item =  scene->addLine(newline,blackpen);
       
        //curr_line = &newline;
    
}

void prova_widget::break_line_drawing(){
    if (!is_drawing) return;
    
    scene->removeItem(curr_line_item);
    starting_object->setSelected(false);
    std::cerr<<"selecteditems size: "<<scene->selectedItems().size()<<std::endl;
    starting_object = 0;
    is_drawing = false;
}

void prova_widget::mousePressEvent(QMouseEvent* e)
{
    std::cout << "widget mouse press catched" << std::endl;
    //QWidget::mousePressEvent(e);
    if (e->button() == Qt::RightButton)
        break_line_drawing();
    else
    {
        QPoint globpos = e->globalPos();
        QPoint p2 = ui->graphicsView->mapFromGlobal(globpos);
        QPointF p3 = ui->graphicsView->mapToScene(p2);
        QRectF rect = QRectF(p3.x()-25,p3.y()-25,50,50);
        QList<QGraphicsItem*> list =  scene->items(rect);
        std::cout<<"list size is: "<<list.size()<<std::endl;
        for (QList<QGraphicsItem*>::iterator it = list.begin(); it != list.end();++it)
        {
            std::cout<< "type is:" << (*it)->type()<<std::endl;
        }
    }
}
void prova_widget::update_L1_object()
{ 
        if (is_drawing)
        {
            scene->removeItem(curr_line_item);
            //starting_object = 0;
            is_drawing = false;
            
            popup.reset(new ProvaPopup());
            
            connect(popup.get(),SIGNAL(accepted()),this,SLOT(update_object()));
            connect(popup.get(),SIGNAL(rejected()),this,SLOT(no_data()));
            popup->set_data(graphical_to_data.at(starting_object));
            popup->exec();
            popup->activateWindow();
            //starting_object->text->setPlainText("modded");
            
        }
        else
        {
            std::cout<< "starting object not retrieved"<<std::endl;
        }
                

    
}

void prova_widget::update_L2_object()
{ 
        if (is_drawing)
        {
            scene->removeItem(curr_line_item);
            //starting_object = 0;
            is_drawing = false;
            
            porte.reset(new ProvaPorte());
            
            connect(porte.get(),SIGNAL(accepted()),this,SLOT(update_object2()));
            connect(porte.get(),SIGNAL(rejected()),this,SLOT(no_data()));
            porte->set_data(graphical_to_data.at(starting_object));
            porte->exec();
            porte->activateWindow();
            //starting_object->text->setPlainText("modded");
            
        }
        else
        {
            std::cout<< "starting object not retrieved"<<std::endl;
        }
                

    
}

void prova_widget::update_object(){

    std::cout <<"entra in update"<<std::endl;
    L4_Data* data = popup->get_data();
    std::cout <<"data retrieved"<<std::endl;
    starting_object->text->setPlainText(QString::fromStdString(data->name));
    std::cout<<"update finished"<<std::endl;
}
void prova_widget::update_object2(){

    std::cout <<"entra in update"<<std::endl;
    L4_Data* data = porte->get_data();
    std::cout <<"data retrieved"<<std::endl;
    starting_object->text->setPlainText(QString::fromStdString(data->name));
    std::cout<<"update finished"<<std::endl;
}

void prova_widget::finalize_line(){
     std::pair<int,int> ports = ps->get_ports();
     Arrow* a =new Arrow(starting_object,arrival_object,ports.first,ports.second);
     arrows.push_back(a); 
     starting_object->setSelected(false);
     arrival_object->setArrowTarget();
     starting_object = 0;
     arrival_object->setSelected(false);
     arrival_object = 0;
}