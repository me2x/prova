#ifndef provaGui_H
#define provaGui_H

#include "scene.h"
#include <QtGui/QMainWindow>
#include <QGraphicsView>

class provaGui : public QMainWindow
{
    Q_OBJECT
private:
  scene*       m_scene;               // scene representing the simulated landscape
public:
    provaGui();
    virtual ~provaGui();
    
    public slots:
  void showMessage( QString );        // show message on status bar
};

#endif // provaGui_H
