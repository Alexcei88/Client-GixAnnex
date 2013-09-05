#include "iparsingcommandout.h"

//----------------------------------------------------------------------------------------/
IParsingCommandOut::IParsingCommandOut(){}
//----------------------------------------------------------------------------------------/
IParsingCommandOut::~IParsingCommandOut(){};
//----------------------------------------------------------------------------------------/
void IParsingCommandOut::GetNewDataStdOut()
{
    std::cout<<"New data"<<std::endl;
    //QString newData(TShell::GetInstance()->readStandartOutput());

}
//----------------------------------------------------------------------------------------/

