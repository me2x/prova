#ifndef PORTSELECT_H
#define PORTSELECT_H

#include <qt4/QtGui/QDialog>
#include "l4_data.h"
#include <QRadioButton>
namespace Ui
{
class PortSelect;
}

class PortSelect : public QDialog
{
    Q_OBJECT
public:        
    explicit PortSelect(QDialog* parent = 0);
    ~PortSelect();
    void exec();
    void set_data(L4_Data* from, L4_Data* to);
    std::pair<int,int> get_ports();
public slots:
    void accept();
    void reject();
private:
    Ui::PortSelect* ui;
    L4_Data* source;
    L4_Data* target;
    int from, to;
    QButtonGroup* bg;
    QButtonGroup* bg2;
    std::list<QRadioButton*> buttons;
};

#endif // PORTSELECT_H
