#include "mytext.h"

MyText::MyText(QWidget* parent):QPlainTextEdit(parent)
{

}
MyText::MyText(QWidget* parent,QString name):QPlainTextEdit(parent){
    this->name=name;
}
