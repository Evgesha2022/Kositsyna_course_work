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
 * @brief ��������� ����.
 *  @details ������������ ��� ����� �������� ��������� ������ � ���� ������ ������ � ���������� �������� ����
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
 * @brief ��������� �������
 * ������������ ��� ����� �������� ��������� ������
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
 * @brief ��������� ������ ���.
 * ������������ ��� ����� �������� ��������� ������ � ������ ���  ������������.
 * @details  �������� id �������, �������� ������� ���, ����� ������ ������ ���. ����� ��� ����������� �������� ���� Time.
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
 * @brief ����� ���������� ����������� �� ������� �����.
 *  @details������ ������������ ���� Time.������������ ��� ���������� ����, �� ������� ������� ������� �������� ����� ���������� � ������������ after_time.
 * @param rhs ����� � �������� ����������
 * @param lhs ������� ����������
 * @return ����� �����
 */
Time sum(Time rhs, Time lhs);
/**
 * @brief ��������� ������� ������ ��������.
 * ������������ ��� ����� �������� ��������� ������ � ������� ������ ������������ ��������� �������������.�������� id �������� �� ������ ������ ��� � �����, ������ ������� ����� ������� ��� ��������.
 */
struct  Times_Day_for_tablet
{
    Times_Day_for_tablet(int time_id_use, Time after_time) :_time_id_use(time_id_use), _after_time(after_time) {};
    int _time_id_use;
    Time _after_time;

};
/**
 * @brief ��������� ��������.
 * @details������������ ��� ����� �������� ��������� ������ � ����������� ��������� �������������.�������� id ��������, �������� ��������, ���� ������ ������ � ������ ������.
 * @details ��� �������� �����-�� �� �������� ���������� ����������������� id � ������������ � �� ��������� � �������. ���� ������ ������ ����������� �������� ���� Date.
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
 * @brief ����� ���������� ����������� � ���� ���������� ����.
 * @details ������������ ��� ���������� ��������� ���� ������ ��������.
 * @param rhs ���� � ������� ����������
 * @param lhs ���������� ����
 * @return ��������� ���� ������
 */
Date find_final_date(Date rhs, int lhs);
/**
 * @brief ��������� User
 * @details ������������ ��� ����� �������� ��������� ������ � ������������. �������� ���, �������, ����� ��� � ������ ��������.
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
/** @brief ������� ��������� ������ � ������� ����� ������� ���� ������� ��������.
     @param val_user ������ ������������ � �������.
     @param val_tablet ������ �������� � ������� �������� ����� ������������
     @param change  ��� json ����� �� ��� ���� ��������
      @returns ������ � ������� �� ���������
*/

std::string puttabletafter_time(int& val_user, int& val_tablet, int& val_time, const char* change);

/** @brief  ������� ��������� ����� � ������� Tablet
       @param val_user ������ ������������ � ������
       @param val_tablet ������ �������� � ������� �������� ����� ������������
       @param  what ��� ����� ��������
       @param change  ��� json ����� � ������� ��� ���������
      @returns ������ � ������� �� ���������
*/
std::string puttabletwhat(int& val_user, int& val_tablet, std::string& what, const char* change);

/** @brief  ������� ��������� ���� begin_time � �������  Daily_regime
       @param val_user ������ ������������ � �������
       @param val_time ������ ������� � ������� �������� ����� ������������
        @param change  ��� json ����� � ������� ��� ���������
      @returns ������ � ������� �� ���������
*/
std::string putdaily_regimebt(int& val_user, int& val_time, const char* change);

/** @brief ������� ��������� ����� � ������� User1
       @param val_user ������ ������������ � �������
       @param what ��� ����� ��������
       @param change  ��� json ����� � ������� ��� ���������
      @returns ������ � ������� �� ���������
*/
std::string putuserwhat(int& val_user, std::string& what, const char* change);
void puttablet(std::string& fn, std::string& ln, std::string& tab, std::string& tabch);

/** @brief �������  ������ ������������ ����� � ������� User1
       @param fn first_name ������������
       @param ln last_name ������������
       @param what ��� ����� ��������
      @returns ������ � ������� ������ � ������� JSON
*/
void getuserwhat(std::string& fn, std::string& ln, std::string& what);

/** @brief �������  ������ ������������ ����� ���� �������� Tablet � ������������
       @param fn first_name ������������
       @param ln last_name ������������
       @param what ��� ����� ��������
      @returns ������ � ������� ������ � ������� JSON
*/
void getusertabletswhat(std::string& fn, std::string& ln, std::string& what);

/** @brief �������  ������ ������������ ����� ������a Tablet � ������������
       @param fn first_name ������������
       @param ln last_name ������������
       @param what ��� ����� ��������
      @returns ������ � ������� ������ � ������� JSON
*/
void getusertabletwhat(std::string& fn, std::string& ln, std::string& tab, std::string what);

/** @brief �������  ���������� ������ ������������
       @param json_user  ��� json �����, ��� ������ ������������ �������� ����� ��������
      @returns ������ � ������� ������ � ������� JSON
*/
std::string postuser(const char* json_user);

/** @brief �������  ���������� ����� �������� � ������������
* @param val_user ������ ������������ � �������
    @param json_tablet  ��� json �����, ��� ������ �������� ������������
    @returns ������ � ������� �� ����������
*/
std::string posttablet(int& val_user, const char* json_tablet);
/** @brief �������  ���������� ����� �������� � ������������
* @param val_user ������ ������������ � �������
* @param val_tablet ������ �������� � ������� �������� ����� ������������
    @param time_for_tablet  ��� json �����, ��� ������ �������� ������������
    @returns ������ � ������� �� ����������
*/
std::string post_time_for_tablet(int& val_user, int& val_tablet, const char* time_for_tablet);

/** @brief �������� ������������
      @param val_user ������ ������������ � �������
        @returns ������ � ������� �� �������� ������������
*/
std::string deleteuser(int& val_user);
/** @brief �������� �������� �  ������������
      @param val_user ������ ������������ � �������
        @param val_tablet ������ �������� � ������� �������� ����� ������������
          @returns ������ � ������� �� �������� �������� ������������
*/
std::string deletetablet(int& val_user, int& val_tablet);

std::string deletetime_for_tablet(int& val_user, int& val_tablet, int& val_time_use);

std::string deletetime_of_day(int& val_user, int& val_time);

rapidjson::Document getFile(const char* pathjson);


/** @brief ����� ��� ������ ���� Document � std::vector<User1>.
      @param doc Document ���� ���������� ����� �������� json �����
*/
void fromJSON1(const rapidjson::Document& doc);

/** @brief ����� ��� ������ ������ �� std::vector<User1> � ��� Document ��� ������ json �����.
      @returns Document ��� ����������� ���������� � json ����
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
/** @brief ����� ��� ������ ������������ �� ������� � ����� 
      @returns ���������� ��� ������ � ������� �������������
*/
int find_user(std::string fn, std::string ln);

int find_tablet(int val_user, std::string tablet);
int find_time_tablet(int val_user, int val_tablet, int time);


std::string  post_time_of_day(int & val_user, const char* time_of_day);

bool check_time_id(int& val_user, int& timeid);

bool check_tablet_id(int& val_user, int& tablet_id);

bool check_user_id(int& val_user);

#endif