#ifndef SEARCHDIA_H
#define SEARCHDIA_H

#include <QDialog>
#include<QDebug>
#include<QString>
namespace Ui {
class SearchDia;
}

class SearchDia : public QDialog
{
    Q_OBJECT

signals:
    void sendData(QString data);

public:


    QString initStr;

    explicit SearchDia(QWidget *parent = nullptr);
    ~SearchDia();

   void setInitStr();
public slots:
    void pressBtnS();




private slots:
    void on_pushButton_clicked();

private:
    Ui::SearchDia *ui;
    //QDialog *sDia;
};

#endif // SEARCHDIA_H
