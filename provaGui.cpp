#include "provaGui.h"
#include "scene.h"
#include "test.h"
#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>
#include <QStatusBar>
#include "prova_widget.h"
provaGui::provaGui()
{
    QLabel* label = new QLabel( this );
    label->setText( "Hello World!" );
    setCentralWidget( label );
    QAction* action = new QAction(this);
    action->setText( "Quit" );
    connect(action, SIGNAL(triggered()), SLOT(close()) );
    menuBar()->addMenu( "File" )->addAction( action );
    
      // create scene and central widget view of scene
  /*m_scene               = new scene();
  QGraphicsView*   view = new QGraphicsView( m_scene );
  view->setAlignment( Qt::AlignLeft | Qt::AlignTop );
  view->setFrameStyle( 0 );
  setCentralWidget( view );
  */
  
  
  
  
  prova_widget* m_scene = new prova_widget(); 
  //QWidget*   view = new QWidget( m_scene );
  /*QGraphicsView*   view = new QGraphicsView( m_scene );
  view->setAlignment( Qt::AlignLeft | Qt::AlignTop );
  view->setFrameStyle( 0 );
  */setCentralWidget( m_scene );
  
   // connect message signal from scene to showMessage slot
  //connect( m_scene, SIGNAL(message(QString)), this, SLOT(showMessage(QString)) );
}

provaGui::~provaGui()
{}

/************************************ showMessage ************************************/

void provaGui::showMessage ( QString msg)
{
  // display message on main window status bar
  statusBar()->showMessage( msg );
}

#include "provaGui.moc"
