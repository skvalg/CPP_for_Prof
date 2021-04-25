#include "poli_spreadsheet.h"
#include <sstream>

poli_spreadsheet::poli_spreadsheet()
{

}

PSpreadSheetCell::PSpreadSheetCell()
{

}

PSpreadSheetCell::~PSpreadSheetCell()
{

}

StringSpreadSheetCell::StringSpreadSheetCell():
    mValue("#NOVALUE")
{

}

void StringSpreadSheetCell::set(const std::string &inString)
{
    mValue=inString;
}

std::string StringSpreadSheetCell::getString()
{
    return mValue;
}

DoubleSpreadSheetCell::DoubleSpreadSheetCell():mValue(-1)
{

}

void DoubleSpreadSheetCell::set(const std::string &inString)
{
    mValue=stringToDouble(inString);
}

void DoubleSpreadSheetCell::set(double inDouble)
{
    mValue=inDouble;
}

std::string DoubleSpreadSheetCell::getString()
{
    return doubleToString(mValue);
}

std::string DoubleSpreadSheetCell::doubleToString(double inValue)
{
    std::ostringstream ostr;
    ostr<<inValue;
    return (ostr.str());
}

double DoubleSpreadSheetCell::stringToDouble(const std::string &inString)
{
    double temp;
    std::istringstream istr(inString);
    istr>>temp;
    if(istr.fail() || istr.eof()){
        return 0;
    }
    return temp;
}
