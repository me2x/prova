#include "prova_widget.h"
#include "ui_prova_widget.h"
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <QTimer>
prova_widget::prova_widget(QWidget* parent): QWidget(parent), ui(new Ui::prova_widget)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(Layer_1_press_event()));
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
    popup = new ProvaPopup();
    popup->exec();
    popup->activateWindow();
    
    
    
    std::cout<<"layer 1 press event triggered"<<std::endl;
     ProvaRiquadro *temp= new ProvaRiquadro();
     scene->addItem(temp);
     connect(temp,SIGNAL(riquadroCliccatoSx()),this,SLOT(component_clicked()));
     connect(temp,SIGNAL(riquadroMosso()),this,SLOT(break_line_drawing()));
     connect(temp,SIGNAL(riquadroCliccatoDx()),this,SLOT(break_line_drawing()));
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

void prova_widget::component_clicked()
{
    std::cout<<"component_clicked"<<std::endl;
    QPoint p1 = QCursor::pos();
    QPoint p2 = ui->graphicsView->mapFromGlobal(p1);
    QPointF p = ui->graphicsView->mapToScene(p2);
    ProvaRiquadro* item =  (ProvaRiquadro*) scene->itemAt(p.x()-3, p.y()-3); //NON HO ANCORA CAPITO XK SI PERDA 3px nella conversione. 
    //che poi la domanda fondamentale è sono 3 qua e x altrove? xk in tal caso il fix non  funziona...
       // QPoint p = ui->frame_6->mapFromGlobal(QCursor::pos());
    QPen blackpen = QPen(Qt::black);
    if (item->type() == QGraphicsItem::UserType)
    {
        if(is_drawing)
        {
            is_drawing = false;
            scene->removeItem(curr_line_item);
            QPointF* starting_point = new QPointF(starting_object->x()+starting_object->boundingRect().center().x(),
                                                 starting_object->y()+starting_object->boundingRect().bottom());
            QPointF* arrival_point = new QPointF (item->x()+item->boundingRect().center().x(),
                                                 item->y()+item->boundingRect().bottom());
            QLineF newline(*starting_point,*arrival_point);
            curr_line_item = scene->addLine(newline,blackpen);
            starting_object->arriving_lines.insert(std::make_pair(item,curr_line_item));
            item->starting_lines.insert(std::make_pair(starting_object,curr_line_item));
            
            
            
            starting_object = 0;
            item = 0;
        }
        else
        {
            
            //start
            //std::cout<<"crash test: else init"<<std::endl;
            
            is_drawing = true;
           // std::cout<<"crash test: set true"<<std::endl;
            starting_object = item;
           // std::cout<<"crash test: set start point"<<std::endl;
            QPoint p1 = QCursor::pos();
            QPoint p2 = ui->graphicsView->mapFromGlobal(p1);
            QPointF p = ui->graphicsView->mapToScene(p2);
         //   std::cout<<"crash test: get p"<<p.x()<<std::endl;
         //   std::cout<<"crash test: item is"<< item->objectName().toStdString()<<std::endl; //crasha se riprende la linea
            QLineF newline(item->x()+item->boundingRect().center().x(),item->y()+item->boundingRect().bottom(),p.x()-3, p.y()-3);
         //   std::cout<<"crash test: draw line"<<std::endl;
            curr_line_item = scene->addLine(newline,blackpen);
         //   std::cout<<"crash test: drawn line"<<std::endl;
           
         //   std::cout<<"crash test: else exit"<<std::endl;
        }
    }
    else
        std::cout << " other type, value is: " << item->type()<<std::endl;
}


//funzione update: if(is_drawing) drawline arrive_point to qcursor::pos.
//piu che drawline, updateline
void prova_widget::redraw_line()
{
    if (!is_drawing) return;
   // std::cout<<"inside redraw line" <<std::endl;
    
        QPen blackpen = QPen(Qt::black);
        std::cout << "curr line != 0" <<std::endl;
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
    starting_object = 0;
    is_drawing = false;
}

void prova_widget::mousePressEvent(QMouseEvent* e)
{
    std::cout << "widget mouse press catched" << std::endl;
    //QWidget::mousePressEvent(e);
    if (e->button() == Qt::RightButton)
        break_line_drawing();
}

