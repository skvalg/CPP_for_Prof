#include <iostream>
#include "spreadsheet.h"

using namespace std;

int main()
{
    //пример использования указателя на метод
    SpreadSheetCell myCell;
    myCell.set(2.66);
    typedef double (SpreadSheetCell :: *PtrtoGet) () const;
    PtrtoGet methodPtr=&SpreadSheetCell::getValue;
    cout<<(myCell.*methodPtr)()<<endl;
    return 0;
}
