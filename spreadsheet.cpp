#include "spreadsheet.h"
#include <sstream>

bool checkSpreadsheetCell(const SpreadSheetCell &cell){
    return (SpreadSheetCell::stringToDouble(cell.mString)== cell.mValue);
}
SpreadSheetCell::SpreadSheetCell():mValue(0),mString(""),mNumAccesses(0)
{

}

SpreadSheetCell::SpreadSheetCell(const SpreadSheetCell &src):
    mValue(src.mValue),mString(src.mString),mNumAccesses(0)
{

}

SpreadSheetCell &SpreadSheetCell::operator=(const SpreadSheetCell &rhs)
{
    if(this==&rhs) return (*this);
    mValue=rhs.mValue;
    mString=rhs.mString;
    return (*this);
}

inline double SpreadSheetCell::getValue() const
{
    mNumAccesses++;
    return (mValue);
}


SpreadSheetCell::SpreadSheetCell(const std::string &initialValue):
    mValue(stringToDouble(initialValue)),mString(initialValue),mNumAccesses(0)
{

}

void SpreadSheetCell::set(const std::string &inString)
{
    mString=inString;
    mValue=stringToDouble(mString);
}

inline std::string SpreadSheetCell::getString() const
{
    mNumAccesses++;
    return (mString);
}

void SpreadSheetCell::set(double inValue)
{
    mValue=inValue;
    mString=doubleToString(mValue);
}

std::string SpreadSheetCell::doubleToString(double inValue)
{
    std::ostringstream ostr;
    ostr<<inValue;
    return (ostr.str());
}

double SpreadSheetCell::stringToDouble(const std::string &inString)
{
    double temp;
    std::istringstream istr(inString);
    istr>>temp;
    if(istr.fail() || istr.eof()){
        return 0;
    }
    return temp;
}

const SpreadSheetCell SpreadSheetCell::operator+(const SpreadSheetCell &cell) const
{
    SpreadSheetCell newCell;
    newCell.set(mValue+cell.mValue);
    return (newCell);
}
SpreadSheetCell SpreadSheet::getCellAt(int x, int y)
{
    SpreadSheetCell empty;
    if(!inRange(x,mWidth)||!inRange(y,mHeight)){
            return (empty);
    }
    return (mCells[x][y]);
}

int SpreadSheet::sCounter = 0;
SpreadSheet::SpreadSheet(const SpreadSheetApplication &theApp, int inWidth, int inHeight):
    mWidth(inWidth<kMaxWidth ? inWidth : kMaxWidth),mHeight(inHeight<kMaxHeight ? inHeight : kMaxHeight),
    mTheApp(theApp)
{
    mId=sCounter++;
    mCells = new SpreadSheetCell *[mWidth];
    for(int i=0;i<mWidth;++i){
        mCells[i]=new SpreadSheetCell[mHeight];
    }
}

SpreadSheet::SpreadSheet(const SpreadSheet &src):mTheApp(src.mTheApp)
{
    mId=sCounter++;
    copyFrom(src);
}

SpreadSheet::~SpreadSheet()
{
    for(int i=0;i<mWidth;++i){
        delete [] mCells[i];
    }
    delete [] mCells;
}

SpreadSheet &SpreadSheet::operator=(const SpreadSheet &rhs)
{

    if(this==&rhs)return (*this);

    //Чистим текущую выделенную область памяти
    for(int i=0;i<mWidth;++i){
        delete [] mCells[i];
    }
    delete [] mCells;

    //Копируем данные
    copyFrom(rhs);

    return (*this);
}

void SpreadSheet::setCellAt(int x, int y, const SpreadSheetCell &cell)
{
    if(!inRange(x,mWidth)||!inRange(y,mHeight)){
        return;
    }
    mCells[x][y]=cell;
}


bool SpreadSheet::inRange(int val, int upper)
{
    if(val>upper) return false;

    return true;
}

void SpreadSheet::copyFrom(const SpreadSheet &src)
{
    int i,j;

    mWidth=src.mWidth;
    mHeight=src.mHeight;

    // Выделяем память в соответствии с памятью копируемого объекта
    mCells = new SpreadSheetCell* [mWidth];
    for(i=0;i<mWidth;++i){
        mCells[i]=new SpreadSheetCell[mHeight];
    }
    //Заполняем данные
    for(i=0;i<mWidth;++i){
        for(j=0;j<mHeight;++j){
            mCells[i][j]=src.mCells[i][j];
        }
    }
}

