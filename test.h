#ifndef TEST_H
#define TEST_H

#include <qt4/QtGui/qwidget.h>
#include <QWidget>

namespace Ui
{
class test;
}

class test : public QWidget
{
    Q_OBJECT
signals:
  void  message( QString );                                  // info text message signal

public slots:
  void  mousePressEvent();        // receive mouse press events
private:
    Ui::test* ui;
public:
    explicit test(QWidget* parent = 0);
    ~test();
};

#endif // TEST_H
  