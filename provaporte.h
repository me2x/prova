#ifndef PROVAPORTE_H
#define PROVAPORTE_H

#include <qt4/QtGui/QDialog>
#include "l4_data.h"
namespace Ui
{
class ProvaPorte;
}

class ProvaPorte : public QDialog
{
    Q_OBJECT
public:
    explicit ProvaPorte(QDialog* parent = 0);
    ~ProvaPorte();
    void exec();
    L4_Data* get_data();
    void set_data(L4_Data* data_in);
public slots:
    void accept();
    void reject();
    void add_table_line();
    void remove_table_line();
private:
    Ui::ProvaPorte* ui;
    L4_Data* data;
};

#endif // PROVAPORTE_H
