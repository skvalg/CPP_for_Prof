#ifndef POLI_SPREADSHEET_H
#define POLI_SPREADSHEET_H
#include <string>
/**
\file
\brief Заголовочный файл с описанием классов для работы с электронными таблицами
\author Ovsyannikov NIkolay
\version 3.0
\date Апрель 2021 года

Данный файл содержит в себе определения основных
классов, используемых для реализации электронны таблиц
Тут релизуется иерархическая структура для полиморфного поведения
классов-ячеек электронной таблицы
*/

/**
 * @brief The PSpreadSheetCell class - базовый класс ячейки электронной таблицы
 */
class PSpreadSheetCell{
    public:
        PSpreadSheetCell();
        virtual ~PSpreadSheetCell();

        /**
         * \brief Виртуальный метод для инициализации ячейки таблицы. Переопределяется
         * в дочернем классе.
         * \param[in] На вход принимает экземпляр строки std::string
         */
        virtual void set(const std::string& inString)=0;
        /**
          * \brief Виртуальный метод для получения данных ячейки в виде std::string - строки.
          * Переопределяется в дочернем классе
          * \param[out] Возврашает строковое значение, которое содержит ячейка
          */
        virtual std::string getString()=0;

};

/**
 * @brief The StringSpreadSheetCell class - ячека таблицы для строкового представления данных
 */
class StringSpreadSheetCell:public PSpreadSheetCell{
    public:
        StringSpreadSheetCell();

        /**
         * @brief set - метод для инициализации данных ячейки
         * @param inString - аргумент, которым будет проинициализирована данная ячейка
         */
        virtual void set(const std::string &inString);

        /**
         * @brief getString - метод для получения строкового предсталвения ячейки
         * @return Возвращает строковое представление ячейки
         */
        virtual std::string getString();
    protected:
        /**
         * @brief mValue - поле для хранения данных ячейки
         */
        std::string mValue;

};

/**
 * @brief The DoubleSpreadSheetCell class - класс для реализация ячейки электронной таблицы хранящей тиб double
 */
class DoubleSpreadSheetCell:public PSpreadSheetCell{
    public:
        DoubleSpreadSheetCell();

    /**
     * @brief set - метод для инициализации данных ячейки
     * @param inString - аргумент, которым будет проинициализирована данная ячейка
     */
    virtual void set(const std::string &inString);
    /**
     * @brief set - перегруженный метод для инициализации данных ячейки
     * @param inDouble - аргумент, которым будет проинициализирована данная ячейка
     */
    virtual void set(double inDouble);

    /**
     * @brief getString - метод для получения строкового предсталвения ячейки
     * @return Возвращает строковое представление ячейки
     */
    virtual std::string getString();
protected:
     /**
     * @brief doubleToString - метод преобразования значения ячейки double к строковому представлению
     * @param inValue - double значение ячейки
     * @return результат представления inValue в тип std::string
     */
    static std::string doubleToString(double inValue);
    /**
     * @brief stringToDouble - метод перобразования строкового значения в тип double
     * @param inString - строка, которую требуется преобразовать
     * @return результат представления строки inString в тип double
     */
    static double stringToDouble(const std::string & inString);
    /**
     * @brief mValue - поле для хранения данных ячейки
     */
    double mValue;

};
class poli_spreadsheet
{
public:
    poli_spreadsheet();
};

#endif // POLI_SPREADSHEET_H
