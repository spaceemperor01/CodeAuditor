#include "dangerinfo.h"

dangerInfo::dangerInfo()
{

}
dangerInfo::dangerInfo(int line,QString filename,dangerFun *danger){
    this->line=line;
    this->filename=filename;
    this->danger=danger;
}
