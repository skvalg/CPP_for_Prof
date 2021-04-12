#ifndef SPREADSHEET_H
#define SPREADSHEET_H
#include <string>
class SpreadSheetApplication;
class SpreadSheetCell{
public:
    SpreadSheetCell();
    SpreadSheetCell(double initialValue);
    explicit SpreadSheetCell(const std::string& initialValue);
    SpreadSheetCell(const SpreadSheetCell& src); //конструктор копирования

    SpreadSheetCell& operator=(const SpreadSheetCell& rhs);

     double getValue()const;
     std::string getString()const;

    void set(double inValue);
    void set(const std::string &inString);

    //Функции преобразования данных имеют интересный способ этого преобразования
    static std::string doubleToString(double inValue);
    static double stringToDouble(const std::string & inString);

    friend bool checkSpreadsheetCell(const SpreadSheetCell &cell);

    //перергрузка операторов, для обеспечения комутативности
    //функция не должна быть связана ни с каким объектом
    //поэтому ее делаем глобальной и дружественной к нашему классу,
    // чтобы она имела доступ к внутренним членам нашего класса
    friend const SpreadSheetCell operator+(const SpreadSheetCell &lhs, const SpreadSheetCell &rhs);
    friend const SpreadSheetCell operator-(const SpreadSheetCell &lhs, const SpreadSheetCell &rhs);
    friend const SpreadSheetCell operator*(const SpreadSheetCell &lhs, const SpreadSheetCell &rhs);
    friend const SpreadSheetCell operator/(const SpreadSheetCell &lhs, const SpreadSheetCell &rhs);
    //перегрузка допполнительных операторов
    SpreadSheetCell& operator+=(const SpreadSheetCell &rhs);
    SpreadSheetCell& operator-=(const SpreadSheetCell &rhs);
    SpreadSheetCell& operator*=(const SpreadSheetCell &rhs);
    SpreadSheetCell& operator/=(const SpreadSheetCell &rhs);
    //перегрузка операторов сравнения
    friend bool operator ==(const SpreadSheetCell &lhs, const SpreadSheetCell &rhs);
    friend bool operator <(const SpreadSheetCell &lhs, const SpreadSheetCell &rhs);
    friend bool operator >(const SpreadSheetCell &lhs, const SpreadSheetCell &rhs);
    friend bool operator !=(const SpreadSheetCell &lhs, const SpreadSheetCell &rhs);
    friend bool operator <=(const SpreadSheetCell &lhs, const SpreadSheetCell &rhs);
    friend bool operator >=(const SpreadSheetCell &lhs, const SpreadSheetCell &rhs);
protected:
    double mValue;
    std::string mString;

    mutable int mNumAccesses;//Член класса котороый может быть изменени из конст методов
};
class SpreadSheet
{
public:
    SpreadSheet(const SpreadSheetApplication &theApp,
                int inWidth=kMaxWidth, int inHeight=kMaxHeight
                );

    // конструктор копии
    SpreadSheet(const SpreadSheet & src);
    //Оператор присваивания
    SpreadSheet& operator=(const SpreadSheet &rhs);
    //Конструктор копии и оператор присваивания можно запретить для исопльзования
    //просто объявив их под модификатором private, при этом реализовывать их не обязательно

    //Деструктор
    ~SpreadSheet();

    void setCellAt(int x, int y,
                   const SpreadSheetCell &cell);
    SpreadSheetCell getCellAt(int x, int y);
    int getId();
public:
    static const int kMaxHeight = 100;
    static const int kMaxWidth = 100;
protected:
    bool inRange(int val, int upper);
    int mWidth, mHeight;
    int mId;
    //так как память выделяется динамически требуется реализовать для класса свой конструктор копирования и оператор присваивания
    //потому что может возникнуть путанница с указателями
    SpreadSheetCell **mCells;

    //Метод для переноса данных
    void copyFrom(const SpreadSheet &src);

    const SpreadSheetApplication & mTheApp;
    static int sCounter;
};


#endif // SPREADSHEET_H
