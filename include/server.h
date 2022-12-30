#ifndef json_07092022
#define json_07092022
#pragma once
#include<iostream>
#include<string>
#include <cstdio>
#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
#include <string>
#include <vector>
#include<client.h>
using namespace rapidjson;
/**
 * @brief Структура даты.
 *  @details Используется для более удобного изменения данных о дате начала приема и вычисления конечной даты
 */
struct Date
{
    Date() {};
    Date(int day, int month, int year)
        : _day(day), _month(month), _year(year) {};
    int _day;
    int _month;
    int _year;
};

/**
 * @brief Структура времени
 * Используется для более удобного изменения данных
 */
struct Time
{
    Time() {};
    Time(int hour, int min, int sec)
        : _hour(hour), _min(min), _sec(sec) {};

    int _hour = 0;
    int _min = 0;
    int _sec = 0;

};

/**
 * @brief Структура Режима дня.
 * Используется для более удобного изменения данных о режиме дня  пользователя.
 * @details  Содержит id времени, название времени дня, время начала режима дня. Режим дня представлен объектом типа Time.
 */
struct Daily_regime
{
    Daily_regime(int time_id, std::string time_of_day, Time begin_time)
        : _time_id1(time_id), _time_of_day(time_of_day), _begin_time(begin_time) {};
    int _time_id1;
    std::string _time_of_day;
    Time _begin_time;
};

/**
 * @brief Метод выполнящий прибавление ко времени минут.
 *  @detailsМинуты представлены тоже Time.Используется для вычисления того, во сколько следует принять таблетку после указанного с прибавлением after_time.
 * @param rhs время к которому прибавляем
 * @param lhs сколько прибавляем
 * @return новое время
 */
Time sum(Time rhs, Time lhs);
/**
 * @brief Структура Времени приема таблеток.
 * Используется для более удобного изменения данных о времени приема определенных таблеткок пользователем.Содержит id таблеток из списка режима дня и время, спустя которое нужно принять эту таблетку.
 */
struct  Times_Day_for_tablet
{
    Times_Day_for_tablet(int time_id_use, Time after_time) :_time_id_use(time_id_use), _after_time(after_time) {};
    int _time_id_use;
    Time _after_time;

};
/**
 * @brief Структура Таблеток.
 * @detailsИспользуется для более удобного изменения данных о принимаемых таблетках пользователем.Содержит id таблеток, название таблеток, дату начала приема и период приема.
 * @details При удаление какой-то из таблеток происходит перераспределение id в соответствии с их хранением в векторе. Дата начала приема представлен объектом типа Date.
 */
struct Tablets
{
    Tablets(int  tablet_id, std::string name, Date start_date, int period_days, std::vector<Times_Day_for_tablet> time_of_day)
        :_tablet_id(tablet_id), _name(name), _start_date(start_date), _period_days(period_days), _time_of_day(time_of_day) {};

    int _tablet_id;
    std::string _name;
    Date _start_date;
    int _period_days;
    Date _finish_date;
    std::vector<Times_Day_for_tablet> _time_of_day;
};

/**
 * @brief Метод выполнящий прибавление к дате количество дней.
 * @details Используется для вычисления финальной даты приема таблеток.
 * @param rhs дата к которой прибавляем
 * @param lhs количество дней
 * @return финальная дата приема
 */
Date find_final_date(Date rhs, int lhs);
/**
 * @brief Структура User
 * @details Используется для более удобного изменения данных о пользователе. Содержит имя, фамилию, режим дня и список таблеток.
 */
struct User1
{
    User1() = default;
    User1(int userid,
        std::string first_name,
        std::string last_name, std::vector<Daily_regime> times, std::vector<Tablets> tablets)
        :_userid(userid), _first_name(first_name), _last_name(last_name), _times(times), _tablets(tablets) {};
    int  _userid;
    std::vector<Tablets> _tablets;
    std::vector<Daily_regime> _times;
    std::string _first_name;
    std::string _last_name;
};
/** @brief Функция изменения данных о времени через сколько надо принять таблетку.
     @param val_user индекс пользователя в векторе.
     @param val_tablet индекс таблеток в векторе таблеток этого пользователя
     @param change  имя json файла на что надо изменить
      @returns Строку с ответом об изменении
*/

std::string puttabletafter_time(int& val_user, int& val_tablet, int& val_time, const char* change);

/** @brief  Функция изменения полей в объекте Tablet
       @param val_user индекс пользователя в вектор
       @param val_tablet индекс таблеток в векторе таблеток этого пользователя
       @param  what что нужно изменить
       @param change  имя json файла с данными для изменения
      @returns Строку с ответом об изменении
*/
std::string puttabletwhat(int& val_user, int& val_tablet, std::string& what, const char* change);

/** @brief  Функция изменения поля begin_time в объекте  Daily_regime
       @param val_user индекс пользователя в векторе
       @param val_time индекс времени в векторе таблеток этого пользователя
        @param change  имя json файла с данными для изменения
      @returns Строку с ответом об изменении
*/
std::string putdaily_regimebt(int& val_user, int& val_time, const char* change);

/** @brief Функция изменения полей в объекте User1
       @param val_user индекс пользователя в векторе
       @param what что нужно изменить
       @param change  имя json файла с данными для изменения
      @returns Строку с ответом об изменении
*/
std::string putuserwhat(int& val_user, std::string& what, const char* change);
void puttablet(std::string& fn, std::string& ln, std::string& tab, std::string& tabch);

/** @brief Функция  выдачи определенных полей в объекте User1
       @param fn first_name пользователя
       @param ln last_name пользователя
       @param what что нужно изменить
      @returns Строку с ответом данных в формате JSON
*/
void getuserwhat(std::string& fn, std::string& ln, std::string& what);

/** @brief Функция  выдачи определенных полей всех объектов Tablet у пользователя
       @param fn first_name пользователя
       @param ln last_name пользователя
       @param what что нужно изменить
      @returns Строку с ответом данных в формате JSON
*/
void getusertabletswhat(std::string& fn, std::string& ln, std::string& what);

/** @brief Функция  выдачи определенных полей объектa Tablet у пользователя
       @param fn first_name пользователя
       @param ln last_name пользователя
       @param what что нужно изменить
      @returns Строку с ответом данных в формате JSON
*/
void getusertabletwhat(std::string& fn, std::string& ln, std::string& tab, std::string what);

/** @brief Функция  добавления нового пользователя
       @param json_user  имя json файла, где данные пользователя которого нужно добавить
      @returns Строку с ответом данных в формате JSON
*/
std::string postuser(const char* json_user);

/** @brief Функция  добавления новых таблеток к пользователя
* @param val_user индекс пользователя в векторе
    @param json_tablet  имя json файла, где данные таблеток пользователя
    @returns Строку с ответом об измененияъ
*/
std::string posttablet(int& val_user, const char* json_tablet);
/** @brief Функция  добавления новых таблеток к пользователя
* @param val_user индекс пользователя в векторе
* @param val_tablet индекс таблеток в векторе таблеток этого пользователя
    @param time_for_tablet  имя json файла, где данные таблеток пользователя
    @returns Строку с ответом об измененияъ
*/
std::string post_time_for_tablet(int& val_user, int& val_tablet, const char* time_for_tablet);

/** @brief Удаление пользователя
      @param val_user индекс пользователя в векторе
        @returns Строку с ответом об удалении пользователя
*/
std::string deleteuser(int& val_user);
/** @brief Удаление таблеток у  пользователя
      @param val_user индекс пользователя в векторе
        @param val_tablet индекс таблеток в векторе таблеток этого пользователя
          @returns Строку с ответом об удалении таблеток пользователя
*/
std::string deletetablet(int& val_user, int& val_tablet);

std::string deletetime_for_tablet(int& val_user, int& val_tablet, int& val_time_use);

std::string deletetime_of_day(int& val_user, int& val_time);

rapidjson::Document getFile(const char* pathjson);


/** @brief Метод для записи типа Document в std::vector<User1>.
      @param doc Document файл полученный после парсинга json файла
*/
void fromJSON1(const rapidjson::Document& doc);

/** @brief Метод для записи данных из std::vector<User1> в тип Document для выдачи json файла.
      @returns Document для дальнейшего сохранения в json файл
*/
rapidjson::Document toJSON1();

void downloadData();

void getuserswhat();

rapidjson::Document   getuserswhatJSON();

rapidjson::Document  getuserwhattoJSON(int user_id, std::string what);


int find_time(int user_id, int time_id);



std::string  returnstrtime(Time time);

std::string realtime(int time_id, int user_id, int tablet_id, int vec_time_tablet);


std::string  returnstrdate(Date date);
/** @brief Метод для поиска пользователя по фамилии и имени 
      @returns Возвращает его индекс в векторе пользователей
*/
int find_user(std::string fn, std::string ln);

int find_tablet(int val_user, std::string tablet);
int find_time_tablet(int val_user, int val_tablet, int time);


std::string  post_time_of_day(int & val_user, const char* time_of_day);

bool check_time_id(int& val_user, int& timeid);

bool check_tablet_id(int& val_user, int& tablet_id);

bool check_user_id(int& val_user);

#endif