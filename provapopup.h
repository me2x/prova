#ifndef PROVAPOPUP_H
#define PROVAPOPUP_H

#include <qt4/QtGui/QWidget>
#include <QDialog>
#include "l4_data.h"
namespace Ui
{
class ProvaPopup;
}

class ProvaPopup : public QDialog
{
    Q_OBJECT
public:
    explicit ProvaPopup(QDialog* parent = 0);
    ~ProvaPopup();
    void exec();
    L4_Data* get_data();
    void set_data(L4_Data* data_in);
public slots:
    void accept();
    void reject();
private:
    Ui::ProvaPopup* ui;
    L4_Data data;
};

#endif // PROVAPOPUP_H
