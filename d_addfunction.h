#ifndef D_ADDFUNCTION_H
#define D_ADDFUNCTION_H

#include <QDialog>
#include"funsql.h"
namespace Ui {
class d_addfunction;
}

class d_addfunction : public QDialog
{
    Q_OBJECT

public:
    explicit d_addfunction(QWidget *parent = nullptr);
    ~d_addfunction();
    void setType(bool isAdd,FunctionInfo info={});

private slots:
    void on_add_save_clicked();

    void on_add_cancel_clicked();

private:
    Ui::d_addfunction *ui;
    bool m_isAdd;
    FunctionInfo m_info;
};

#endif // D_ADDFUNCTION_H
