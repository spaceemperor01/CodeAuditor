#ifndef DANGERFUN_MANAGE_H
#define DANGERFUN_MANAGE_H

#include <QWidget>
#include"funsql.h"
#include<d_addfunction.h>
namespace Ui {
class dangerfun_manage;
}

class dangerfun_manage : public QWidget
{
    Q_OBJECT

public:
    explicit dangerfun_manage(QWidget *parent = nullptr);
    ~dangerfun_manage();

private slots:
    void on_B_add_clicked();

    void on_B_search_clicked();

    void on_B_edit_clicked();

    void on_B_delete_clicked();

    void on_B_refresh_clicked();

    void on_B_clear_clicked();

private:
    Ui::dangerfun_manage *ui;
    d_addfunction m_addFunction;
    funSql *m_ptrriskSql;
};

#endif // DANGERFUN_MANAGE_H
