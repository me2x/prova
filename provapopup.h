#ifndef PROVAPOPUP_H
#define PROVAPOPUP_H

#include <qt4/QtGui/QWidget>
#include <QDialog>
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

   
private:
    Ui::ProvaPopup* ui;
};

#endif // PROVAPOPUP_H
