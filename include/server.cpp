#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include <rapidjson/rapidjson.h>
#include "rapidjson/stringbuffer.h"
#include <iostream>
#include <string>
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include <rapidjson/ostreamwrapper.h>
#include<fstream>
#include<string>
#include<server.h>
using namespace rapidjson;

rapidjson::Document getFile(const char* pathjson)
{
    char* ostype = getenv("OSTYPE");
    if (ostype == NULL)
    {
        ostype = getenv("windir");
        if (ostype != NULL)
        {
            FILE* fp = fopen(pathjson, "rb");
            char readBuffer[65536];
            FileReadStream is(fp, readBuffer, sizeof(readBuffer));
            Document d;
            d.ParseStream(is);
            fclose(fp);
            return d;
        }
        else
        {
            FILE* fp = fopen(pathjson, "r");
            char readBuffer[65536];
            FileReadStream is(fp, readBuffer, sizeof(readBuffer));
            Document d;
            d.ParseStream(is);
            fclose(fp);
            return d;
        }
    }
}

//rapidjson::Document getFile(const char* pathjson)
//{
//    FILE* fp = fopen(pathjson, "rb"); // non-Windows use "r"
//    char readBuffer[65536];
//    FileReadStream is(fp, readBuffer, sizeof(readBuffer));
//    Document d;
//    d.ParseStream(is);
//    fclose(fp);
//    return d;
//}


std::vector<User1> users;
void getusertabletfinish_date( std::string& fn, std::string& ln, std::string& tab)
{
    for (int i = 0; i < users.size(); i++)
    {
        std::cout << users[i]._first_name << ' ' << users[i]._last_name << '\n';
    }
}

rapidjson::Document  getusertabletwhattoJSON(int user_id, int tablet_id, std::string what)
{
    rapidjson::Document jsonDoc;
    jsonDoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();
    rapidjson::Value koorsArray(rapidjson::kArrayType);
    rapidjson::Value objKoord;

    int koord2 = tablet_id;
    if (what == "period_day")
    {
        objKoord.SetObject();
        Value val(users[user_id]._tablets[koord2]._name.c_str(), jsonDoc.GetAllocator());
        objKoord.AddMember("name", val, allocator);
        std::string start_date = returnstrdate(users[user_id]._tablets[koord2]._start_date);
        Value val1(start_date.c_str(), jsonDoc.GetAllocator());
        objKoord.AddMember("start_date", val1, allocator);
        int period_days = users[user_id]._tablets[koord2]._period_days;
        objKoord.AddMember("period_days", period_days, allocator);
        Date final_date_D = find_final_date(users[user_id]._tablets[koord2]._start_date, period_days);
        std::string final_date = returnstrdate(final_date_D);
        Value val2(final_date.c_str(), jsonDoc.GetAllocator());
        objKoord.AddMember("final_date", val2, allocator);
        jsonDoc.AddMember("tablet", objKoord, allocator);
        return jsonDoc;
    }
    else if (what == "time_of_day")
    {
        objKoord.SetObject();
        Value val(users[user_id]._tablets[koord2]._name.c_str(), jsonDoc.GetAllocator());
        objKoord.AddMember("name", val, allocator);
        rapidjson::Value koorsArray3(rapidjson::kArrayType);
        for (int koord3 = 0; koord3 < users[user_id]._tablets[koord2]._time_of_day.size(); koord3++)
        {
            rapidjson::Value objKoord3;
            objKoord3.SetObject();
            int time_id_use = users[user_id]._tablets[koord2]._time_of_day[koord3]._time_id_use;
            int val2 = find_time(user_id, time_id_use);
            Value val(users[user_id]._times[val2]._time_of_day.c_str(), jsonDoc.GetAllocator());
            objKoord3.AddMember("time_of_day", val, allocator);
            std::string time = realtime(time_id_use, user_id, koord2, koord3);
            Value val1(time.c_str(), jsonDoc.GetAllocator());
            objKoord3.AddMember("time", val1, allocator);
            koorsArray3.PushBack(objKoord3, allocator);
        }
        objKoord.AddMember("regime",koorsArray3, allocator);
        jsonDoc.SetObject();
        jsonDoc.AddMember("tablet", objKoord, allocator);
        return jsonDoc;

    }
}

rapidjson::Document  getusertabletsperiodstoJSON( int user_id, std::string what)
{
    rapidjson::Document jsonDoc;
    jsonDoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();
    rapidjson::Value koorsArray(rapidjson::kArrayType);
    rapidjson::Value objKoord;
    if (what == "period_times")
    {
        for (int koord2 = 0; koord2 < users[user_id]._tablets.size(); koord2++)
        {
            objKoord.SetObject();
            Value val(users[user_id]._tablets[koord2]._name.c_str(), jsonDoc.GetAllocator());
            objKoord.AddMember("name", val, allocator);
           rapidjson::Value koorsArray1(rapidjson::kArrayType);
            rapidjson::Value objKoord2;
            for (int koord1 = 0; koord1 < users[user_id]._tablets[koord2]._time_of_day.size(); koord1++)
            { 
                objKoord2.SetObject();
                int time_id = users[user_id]._tablets[koord2]._time_of_day[koord1]._time_id_use;
                /*Value key("time_id", jsonDoc.GetAllocator());
                objKoord2.AddMember("time_id", time_id, allocator);*/
                int val2 = find_time(user_id, time_id);
                if (val2 == -1) break;
                Value val(users[user_id]._times[val2]._time_of_day.c_str(), jsonDoc.GetAllocator());
                objKoord2.AddMember("time_of_day", val, allocator); 
                std::string time = realtime(time_id, user_id, koord2, koord1);
                Value val1(time.c_str(), jsonDoc.GetAllocator());
                objKoord2.AddMember("time", val1, allocator);
                koorsArray1.PushBack(objKoord2, allocator);
            }
            objKoord.AddMember("periods", koorsArray1, allocator);
            koorsArray.PushBack(objKoord, allocator);
        }
        jsonDoc.AddMember("period_times", koorsArray, allocator);
        return jsonDoc;
    }
    else if (what == "period_days") 
    {

        for (int koord2 = 0; koord2 < users[user_id]._tablets.size(); koord2++)
        {
            objKoord.SetObject();
            Value val(users[user_id]._tablets[koord2]._name.c_str(), jsonDoc.GetAllocator());
            objKoord.AddMember("name", val, allocator);
            std::string start_date = returnstrdate(users[user_id]._tablets[koord2]._start_date);
            Value val1(start_date.c_str(), jsonDoc.GetAllocator());
            objKoord.AddMember("start_date", val1, allocator);
            int period_days = users[user_id]._tablets[koord2]._period_days;
            objKoord.AddMember("period_days", period_days, allocator);
            Date final_date_D = find_final_date(users[user_id]._tablets[koord2]._start_date, period_days);
            std::string final_date = returnstrdate(final_date_D);
            Value val2(final_date.c_str(), jsonDoc.GetAllocator());
            objKoord.AddMember("final_date", val2, allocator);
            koorsArray.PushBack(objKoord, allocator);
        }
        jsonDoc.AddMember("period_days", koorsArray, allocator);
        return jsonDoc;
    }
    else if (what == "name")
    {
        for (int koord2 = 0; koord2 < users[user_id]._tablets.size(); koord2++)
        {
            objKoord.SetObject();
            int tablet_id = users[user_id]._tablets[koord2]._tablet_id;
            objKoord.AddMember("tablet_id", tablet_id, allocator);
            Value val(users[user_id]._tablets[koord2]._name.c_str(), jsonDoc.GetAllocator());
            objKoord.AddMember("name", val, allocator);
            koorsArray.PushBack(objKoord, allocator);
            jsonDoc.SetObject();
        }
    jsonDoc.AddMember("tablets_name", koorsArray, allocator);
    return jsonDoc;
        
    }
    
}

int find_time(int user_id, int time_id)
{
    for (int i = 0; i < users[user_id]._times.size(); i++)
    {
        if (time_id == users[user_id]._times[i]._time_id1)
        {
            return i;
        }
    }
    return -1;
}

std::string realtime(int time_id, int user_id, int tablet_id, int vec_time_tablet)
{
    int val = find_time(user_id, time_id);//ищем данные о времени в массиве daily_regime 
    Time real_time = sum(users[user_id]._times[val]._begin_time, users[user_id]._tablets[tablet_id]._time_of_day[vec_time_tablet]._after_time);
    std::string realtime = returnstrtime(real_time);
    return realtime;
}

void getusertabletswhat( std::string& fn, std::string& ln, std::string& what)
{
    std::string s = "getusertablets" + what;
    rapidjson::Document getabletsperiods;
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]._first_name == fn && users[i]._last_name == ln)
        {
            getabletsperiods = getusertabletsperiodstoJSON(i , what);
            SaveFile(getabletsperiods, s);
            printConsole(getabletsperiods);
        }
    }
}

void getusertabletwhat(std::string& fn, std::string& ln, std::string& tab, std::string what)
{
    rapidjson::Document getabletwhat;
    std::string s = "getusertablet" + what;
    int i = find_user(fn, ln);
    if (i == -1) { std::cout << "404 Not found - "<<"User не найден" << std::endl; return; }
    int j = find_tablet(i, tab);
    if (j == -1) { std::cout << "404 Not found - " << "Tablet не найден" << std::endl; return ; }
    std::cout << "200 OK - ";
                    getabletwhat = getusertabletwhattoJSON(i, j, what);
                    SaveFile(getabletwhat, s);
                    printConsole(getabletwhat);
}

void getuserswhat()
{
    std::string s = "getusers";
    Document val = getuserswhatJSON();
    SaveFile(val, s);
    printConsole(val);

}

rapidjson::Document   getuserswhatJSON()
{
    rapidjson::Document jsonDoc;
    jsonDoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();
    rapidjson::Value koorsArray(rapidjson::kArrayType);
    rapidjson::Value objKoord;
     for (int koord2 = 0; koord2 < users.size(); koord2++)
        {
            objKoord.SetObject();
            Value val(users[koord2]._first_name.c_str(), jsonDoc.GetAllocator());
            objKoord.AddMember("first_name", val, allocator);
            Value val1(users[koord2]._last_name.c_str(), jsonDoc.GetAllocator());
            objKoord.AddMember("last_name", val1, allocator);
            koorsArray.PushBack(objKoord, allocator);
        }
    jsonDoc.SetObject();
    jsonDoc.AddMember("users", koorsArray, allocator);
    return jsonDoc;
}

void getuserwhat( std::string& fn, std::string& ln, std::string& what)
{
    bool flag = false;
    std::string s = "getuser" + what;
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]._first_name == fn && users[i]._last_name == ln)
        {
            std::cout << "200 OK - ";
            Document user = getuserwhattoJSON(i, what);
            SaveFile(user, s);
            printConsole(user);
            flag = true;
        }
    }
    if (flag == false) std::cout << "404 Not found - " << "Данный пользователь не найден";
}

rapidjson::Document  getuserwhattoJSON(int user_id, std::string what)
{
    rapidjson::Document jsonDoc;
    jsonDoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();
    rapidjson::Value koorsArray(rapidjson::kArrayType);
    rapidjson::Value objKoord;
    if (what == "daily_regime")
    {
        for (int koord1 = 0; koord1 < users[user_id]._times.size(); koord1++)
        {
            objKoord.SetObject();
            int time_id = users[user_id]._times[koord1]._time_id1;
            Value key("time_id", jsonDoc.GetAllocator());
            objKoord.AddMember("time_id", time_id, allocator);
            Value val(users[user_id]._times[koord1]._time_of_day.c_str(), jsonDoc.GetAllocator());
            objKoord.AddMember("time_of_day", val, allocator);
            std::string time = returnstrtime(users[user_id]._times[koord1]._begin_time);
            Value val1(time.c_str(), jsonDoc.GetAllocator());
            objKoord.AddMember("begin_time", val1, allocator);
            koorsArray.PushBack(objKoord, allocator);
        }
        jsonDoc.SetObject();
        jsonDoc.AddMember("daily_regime", koorsArray, allocator);
        return jsonDoc;
    }
}

void puttablet( std::string& fn, std::string& ln, std::string& tab, std::string& tabch) {
    bool flag = false;
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]._first_name == fn && users[i]._last_name == ln)
        {
            for (int j = 0; j < users[i]._tablets.size(); j++)
            {
                if (users[i]._tablets[j]._name == tab)
                {
                    std::cout << users[i]._tablets[j]._name << " был измене на " << tabch << '\n';
                    users[i]._tablets[j]._name = tabch;
                    break;
                }
            }
            flag = true;
            break;
        }
    }
    if (flag == false) std::cout << "404 Not found - " << "Данный пользователь не найден";
}

void downloadData()
{
    const char* path = "output.json";
    Document d = getFile(path);
    assert(d.IsObject());
    assert(d.HasMember("users"));
    User1 val2;
    fromJSON1(d);
}

rapidjson::Document toJSON1()
{
    rapidjson::Document jsonDoc;
    //jsonDoc.SetArray();
    jsonDoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();
    rapidjson::Value koorsArray(rapidjson::kArrayType);
    rapidjson::Value objKoord3;
    rapidjson::Value objKoord1;
    rapidjson::Value objKoord;
    //rapidjson::Value objKoord3;
    rapidjson::Value objKoord2;
    for (int koord = 0; koord < users.size(); koord++) {
        objKoord.SetObject();
        int user = users[koord]._userid;
        Value key("userid", jsonDoc.GetAllocator());
        objKoord.AddMember("userid", user, allocator);
        Value val(users[koord]._first_name.c_str(), jsonDoc.GetAllocator());
        objKoord.AddMember("first_name", val, allocator);
        Value val1(users[koord]._last_name.c_str(), jsonDoc.GetAllocator());
        objKoord.AddMember("last_name", val1, allocator);
        rapidjson::Value koors1Array(rapidjson::kArrayType);//могут быть проблемы с очисткой массива
        rapidjson::Value koors2Array(rapidjson::kArrayType);
        for (int koord1 = 0; koord1 < users[koord]._times.size(); koord1++)
        {
            objKoord2.SetObject();
            int time_id = users[koord]._times[koord1]._time_id1;
            Value key("time_id", jsonDoc.GetAllocator());
            objKoord2.AddMember("time_id", time_id, allocator);
            Value val(users[koord]._times[koord1]._time_of_day.c_str(), jsonDoc.GetAllocator());
            objKoord2.AddMember("time_of_day", val, allocator);
            std::string time = returnstrtime(users[koord]._times[koord1]._begin_time);
            Value val1(time.c_str(), jsonDoc.GetAllocator());
            objKoord2.AddMember("begin_time", val1, allocator);
            koors1Array.PushBack(objKoord2, allocator);
        }
        for (int koord2 = 0; koord2 < users[koord]._tablets.size(); koord2++) {

            rapidjson::Value koors3Array(rapidjson::kArrayType);
            objKoord1.SetObject();
            int tablet_id = users[koord]._tablets[koord2]._tablet_id;
            Value key("tablet_id", jsonDoc.GetAllocator());
            objKoord1.AddMember("tablet_id", tablet_id, allocator);
            Value val(users[koord]._tablets[koord2]._name.c_str(), jsonDoc.GetAllocator());
            objKoord1.AddMember("name", val, allocator);
            std::string start_date = returnstrdate(users[koord]._tablets[koord2]._start_date);
            Value val1(start_date.c_str(), jsonDoc.GetAllocator());
            objKoord1.AddMember("start_date", val1, allocator);
            int period_days = users[koord]._tablets[koord2]._period_days;
            Value key1("period_days", jsonDoc.GetAllocator());
            objKoord1.AddMember("period_days", tablet_id, allocator);
            for (int koord3 = 0; koord3 < users[koord]._tablets[koord2]._time_of_day.size(); koord3++)
            {
                objKoord3.SetObject();
                int time_id_use = users[koord]._tablets[koord2]._time_of_day[koord3]._time_id_use;
                Value key("time_id", jsonDoc.GetAllocator());
                objKoord3.AddMember("time_id", time_id_use, allocator);
                std::string time = returnstrtime(users[koord]._tablets[koord2]._time_of_day[koord3]._after_time);
                Value val3(time.c_str(), jsonDoc.GetAllocator());
                objKoord3.AddMember("after_time", val3, allocator);
                koors3Array.PushBack(objKoord3, allocator);
                // objKoord3.Clear();
            }
            objKoord1.AddMember("time_of_day", koors3Array, allocator);
            koors2Array.PushBack(objKoord1, allocator);
            //koors3Array.Clear();
        }
        objKoord.AddMember("daily_regime", koors1Array, allocator);
        objKoord.AddMember("tablets", koors2Array, allocator);
        koorsArray.PushBack(objKoord, allocator);
    }
    jsonDoc.SetObject();
    jsonDoc.AddMember("users", koorsArray, allocator);
    return jsonDoc;
}

void fromJSON1(const rapidjson::Document& doc) {
    if (!doc.IsObject())
        throw std::runtime_error("document should be an object");

    static const char* members[] = { "userid", "first_name", "last_name","times"
    };
    if (!doc.HasMember("users"))
        throw std::runtime_error("missing fields");
    assert(doc.IsObject());
    int userid, timeid, tablet_id, period_days, time_id_use;
    std::string first_name,  time_of_day;
    std::string last_name, name, start_date, after_time;
    std::vector<Daily_regime> times;
    std::vector<Tablets> tablets;
    std::vector<Times_Day_for_tablet> tdft;
    const char delim = ':';
    const char delim1 = '/';
    std::vector<int> time;
    std::vector<int> date;
    for (SizeType i = 0;  i < doc["users"].Size(); i++)
    {
        userid = doc["users"][i]["userid"].GetInt();
        first_name = doc["users"][i]["first_name"].GetString();
        last_name = doc["users"][i]["last_name"].GetString();
        for (SizeType j = 0; j < doc["users"][i]["daily_regime"].Size(); j++)
        {
            timeid = doc["users"][i]["daily_regime"][j]["time_id"].GetInt();
            time_of_day = doc["users"][i]["daily_regime"][j]["time_of_day"].GetString();
            std::string begin_time_str = doc["users"][i]["daily_regime"][j]["begin_time"].GetString();
            tokenize(begin_time_str, delim, time);
            Time begin_time (time[0], time[1], time[2]);
            Daily_regime result1(timeid, time_of_day, begin_time);
            times.push_back(result1);
            time.clear();
        }
        for (SizeType k = 0; k < doc["users"][i]["tablets"].Size(); k++)
        {
            tablet_id = doc["users"][i]["tablets"][k]["tablet_id"].GetInt();
            name = doc["users"][i]["tablets"][k]["name"].GetString();
            start_date = doc["users"][i]["tablets"][k]["start_date"].GetString();
            tokenize(start_date, delim1, date);
            Date start_date(date[0], date[1], date[2]);
            date.clear();
            period_days = doc["users"][i]["tablets"][k]["period_days"].GetInt();
            for (SizeType l = 0; l < doc["users"][i]["tablets"][k]["time_of_day"].Size(); l++)
            {
                time_id_use = doc["users"][i]["tablets"][k]["time_of_day"][l]["time_id"].GetInt();
                std::string aftertime = doc["users"][i]["tablets"][k]["time_of_day"][l]["after_time"].GetString();
                tokenize(aftertime, delim, time);
                Time after_time(time[0], time[1], time[2]);
                Times_Day_for_tablet result3(time_id_use, after_time);
                tdft.push_back(result3);
                time.clear();
            }
            Tablets result2(tablet_id, name, start_date, period_days, tdft);
            tablets.push_back(result2);
            tdft.clear();
        }
        User1 result(userid, first_name, last_name, times, tablets);
        users.push_back(result);
        tablets.clear();
        times.clear();
    };
}

std::string  returnstrtime(Time time)
{
    std::string sep = ":";
    std::string hour,min, sec;
    if (time._hour - 10 < 0)
    {
        hour = '0' + std::to_string(time._hour);
    }
    else hour =  std::to_string(time._hour);
    if (time._min - 10 < 0)
    {
        min = '0' + std::to_string(time._min);
    }
    else min = std::to_string(time._min);
    if (time._sec - 10 < 0)
    {
        sec = '0' + std::to_string(time._sec);
    }
    else sec = std::to_string(time._sec);
    std::string strtime = hour + sep + min + sep + sec;
    return strtime;
}

Time  sum(Time rhs, Time lhs)
{
    Time ans;
    ans._hour = (rhs._hour + lhs._hour) % 24;
    ans._min = (rhs._min+ lhs._min) % 60;
    int val = (rhs._min + lhs._min) - 60;
    while (val >= 60)
    {
        ans._hour++;
        val = val - 60;
    }
    ans._sec = (rhs._sec + rhs._sec) % 60;
    int val1 = (rhs._sec + lhs._sec) - 60;
    while (val1 >= 60)
    {
        ans._min++;
        val = val - 60;
    }
    return ans;
}

std::string  returnstrdate(Date date)
{
    std::string sep = "/";
    std::string day, month, year;
    if (date._day - 10 < 0)
    {
        day = '0' + std::to_string(date._day);
    }
    else  day =  std::to_string(date._day);
    if (date._month - 10 < 0)
    {
        month = '0' + std::to_string(date._month);
    }
    else  month =  std::to_string(date._month);
    if (date._year - 10 < 0)
    {
        year = '0' + std::to_string(date._year);
    }
    else year =  std::to_string(date._year);
    std::string strtime = day+ sep + month + sep + year;
    return strtime;
}

Date find_final_date(Date rhs, int days)
{
    Date final_date;
    final_date._year = rhs._year;
    final_date._month = rhs._month;
    final_date._day = rhs._day;
    switch (rhs._month)
    {
    case 1:case 3:case 5:case 7:case 8:case 10:case 12:
    {
        final_date._day += days;
        if (final_date._day <= 31) break;
        else
        {
            final_date._day -= 31;
            if (rhs._month = 12)
            {
                final_date._year += 1;
            }
            final_date._month += 1;
        }
    }; break;
    case 4:case 6:case 9:case 11:
    {
        final_date._day += days;
        if (final_date._day <= 30) break;
        else
        {
            final_date._day -= 30;
            final_date._month += 1;
        }
    }; break;
    case 2: if (final_date._year % 4 == 0 && final_date._year % 100 != 0)
    {
        final_date._day += days;
        if (final_date._day <= 29) break;
        else
        {
            final_date._day -= 29;
            final_date._month += 1;
        }
    }
          else
    {
        final_date._day += days;
        if (final_date._day <= 28) break;
        else
        {
            final_date._day -= 28;
            final_date._month += 1;
        }
    }; break;
    }
    return final_date;
}

int find_user(std::string fn, std::string ln)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]._first_name == fn && users[i]._last_name == ln)
        {
            return i;
        }
    }
    return -1;
}

int find_tablet(int val_user, std::string tab)
{
    for (int j = 0; j < users[val_user]._tablets.size(); j++)
    {
        if (users[val_user]._tablets[j]._name == tab)
        {
            return j;
        }
    }
    return -1;
}
int find_time_tablet(int val_user, int val_tablet, int time)
{
    for ( int  i=0; i< users[val_user]._tablets[val_tablet]._time_of_day.size(); i++)
    {
        if (users[val_user]._tablets[val_tablet]._time_of_day[i]._time_id_use == time)
        {
            return i;
        }
    }
    return -1;
}
std::string postuser(const char * json_user)
{
    Document d_json_user= getFile(json_user);
    assert(d_json_user.IsObject());
    if (!d_json_user.IsObject())
        throw std::runtime_error("document should be an object");
    static const char* members[] = { "userid", "first_name", "last_name","times"
    };
    assert(d_json_user.IsObject());
    int userid, timeid, tablet_id, period_days, time_id_use;
    std::string first_name, time_of_day;
    std::string last_name, name, start_date, after_time;
    std::vector<Daily_regime> times;
    std::vector<Tablets> tablets;
    std::vector<Times_Day_for_tablet> tdft;
    const char delim = ':';
    const char delim1 = '/';
    std::vector<int> time;
    std::vector<int> date;
        userid = d_json_user["userid"].GetInt();
        int val_user_id = userid - 1;
        if (!check_user_id(userid)) return "Уже есть пользователь с таким user_id";
        first_name = d_json_user["first_name"].GetString();
        last_name = d_json_user["last_name"].GetString();
        for (SizeType j = 0; j < d_json_user["daily_regime"].Size(); j++)
        {
            timeid = d_json_user["daily_regime"][j]["time_id"].GetInt();
            time_of_day = d_json_user["daily_regime"][j]["time_of_day"].GetString();
            std::string begin_time_str = d_json_user["daily_regime"][j]["begin_time"].GetString();
            tokenize(begin_time_str, delim, time);
            Time begin_time(time[0], time[1], time[2]);
            Daily_regime result1(timeid, time_of_day, begin_time);
            times.push_back(result1);
            time.clear();
        }
        for (SizeType k = 0; k < d_json_user["tablets"].Size(); k++)
        {
            tablet_id = d_json_user["tablets"][k]["tablet_id"].GetInt();
            name = d_json_user["tablets"][k]["name"].GetString();
            start_date = d_json_user["tablets"][k]["start_date"].GetString();
            tokenize(start_date, delim1, date);
            Date start_date(date[0], date[1], date[2]);
            date.clear();
            period_days = d_json_user["tablets"][k]["period_days"].GetInt();
            for (SizeType l = 0; l < d_json_user["tablets"][k]["time_of_day"].Size(); l++)
            {
                time_id_use = d_json_user["tablets"][k]["time_of_day"][l]["time_id"].GetInt();
                std::string aftertime = d_json_user["tablets"][k]["time_of_day"][l]["after_time"].GetString();
                tokenize(aftertime, delim, time);
                Time after_time(time[0], time[1], time[2]);
                Times_Day_for_tablet result3(time_id_use, after_time);
                tdft.push_back(result3);
                time.clear();
            }
            Tablets result2(tablet_id, name, start_date, period_days, tdft);
            tablets.push_back(result2);
            tdft.clear();
        }
        User1 result(userid, first_name, last_name, times, tablets);
        users.push_back(result);
        tablets.clear();
        times.clear();
        Document val = toJSON1();
        SaveFileBase(val);
        return "в файл добавлен новый user";
}


std::string posttablet(int& val_user, const char* json_tablet)
{
    Document d_json_tablet = getFile(json_tablet);
    if (!d_json_tablet.IsObject())
        throw std::runtime_error("document should be an object");
    assert(d_json_tablet.IsObject());
    int tablet_id, period_days, time_id_use;
    std::string time_of_day;
    std::string name, start_date_1, after_time;
    const char delim = ':';
    const char delim1 = '/';
    std::vector<int> time;
    std::vector<int> date;
    tablet_id = d_json_tablet["tablet_id"].GetInt();
    if (!check_tablet_id(val_user, tablet_id)) return "Уже есть пользователь с таким tablet_id";
    name = d_json_tablet["name"].GetString();
    start_date_1 = d_json_tablet["start_date"].GetString();
    tokenize(start_date_1, delim1, date);
    Date start_date(date[0], date[1], date[2]);
    date.clear();
    period_days = d_json_tablet["period_days"].GetInt();
    std::vector<Times_Day_for_tablet> tdft;
    for (SizeType l = 0; l < d_json_tablet["time_of_day"].Size(); l++)
    {
        time_id_use = d_json_tablet["time_of_day"][l]["time_id"].GetInt();
        std::string aftertime = d_json_tablet["time_of_day"][l]["after_time"].GetString();
        tokenize(aftertime, delim, time);
        Time after_time(time[0], time[1], time[2]);
        Times_Day_for_tablet result3(time_id_use, after_time);
        tdft.push_back(result3);
        time.clear();
    }
    Tablets result2(tablet_id, name, start_date, period_days, tdft);
    users[val_user]._tablets.push_back(result2);
    SaveFileBase(toJSON1());
    return "в файл добавлен новый tablet";
    tdft.clear();
}
std::string post_time_for_tablet(int& val_user, int& val_tablet, const char* time_for_tablet)
{
    Document d_time_for_tablet = getFile(time_for_tablet);
    if (!d_time_for_tablet.IsObject())
        throw std::runtime_error("document should be an object");
    assert(d_time_for_tablet.IsObject());
    int tablet_id, period_days, time_id_use;
    std::string time_of_day;
    std::string name, start_date_1, after_time_1;
    const char delim = ':';
    const char delim1 = '/';
    std::vector<int> time;
    std::vector<int> date;
    time_id_use = d_time_for_tablet["time_id"].GetInt();
    std::string aftertime_1 = d_time_for_tablet["after_time"].GetString();
    tokenize(aftertime_1, delim, time);
    Time after_time(time[0], time[1], time[2]);
    Times_Day_for_tablet result3(time_id_use, after_time);
    time.clear();
    users[val_user]._tablets[val_tablet]._time_of_day.push_back(result3);
    Document val = toJSON1();
    SaveFileBase(val);
    return "в файл добавлен новый time к таблетке " + users[val_user]._tablets[val_tablet]._name;
}
std::string post_time_of_day(int& val_user, const char* time_of_day_1)
{
    Document d_time_of_day = getFile(time_of_day_1);
    if (!d_time_of_day.IsObject())
        throw std::runtime_error("document should be an object");
    assert(d_time_of_day.IsObject());
    int timeid;
    std::string time_of_day;
    const char delim = ':';
    const char delim1 = '/';
    std::vector<int> time;
    std::vector<int> date;
    timeid = d_time_of_day["time_id"].GetInt();
    if (!check_time_id(val_user, timeid)) return "Уже есть пользователь с таким time_id";
    time_of_day = d_time_of_day["time_of_day"].GetString();
    std::string begin_time_str = d_time_of_day["begin_time"].GetString();
    tokenize(begin_time_str, delim, time);
    Time begin_time(time[0], time[1], time[2]);
    Daily_regime result1(timeid, time_of_day, begin_time);
    users[val_user]._times.push_back(result1);
    Document val = toJSON1();
    SaveFileBase(val);
    return "в файл добавлено новое событие к user " + users[val_user]._userid;
    time.clear();
}

bool check_time_id(int& val_user, int& timeid)
{
    for (Daily_regime & i : users[val_user]._times)
    {
        if (i._time_id1 == timeid) return false;
    }
    return true;
}

bool check_tablet_id(int& val_user, int& tablet_id)
{
    for (Tablets& i : users[val_user]._tablets)
    {
        if (i._tablet_id == tablet_id) return false;
    }
    return true;
}

bool check_user_id(int& val_user)
{
    for (User1& i : users)
    {
        if (i._userid== val_user) return false;
    }
    return true;
}

std::string puttabletafter_time(int& val_user, int& val_tablet, int& val_time, const char* change)
{
    Document d_change_aft = getFile(change);
    if (!d_change_aft.IsObject())
        throw std::runtime_error("document should be an object");
    assert(d_change_aft.IsObject());
    std::string aftertime_1 = d_change_aft["after_time"].GetString();
    const char delim = ':';
    std::vector<int> time;
    tokenize(aftertime_1, delim, time);
    Time after_time(time[0], time[1], time[2]);
    time.clear();
    users[val_user]._tablets[val_tablet]._time_of_day[val_time]._after_time = after_time;
    Document val = toJSON1();
    SaveFileBase(val);
    std::string  ans = " Произошло изменение after_time в user " + val_user ;
    return ans;
}

std::string puttabletwhat(int& val_user, int& val_tablet, std::string& what, const char* change)
{
    Document d_change = getFile(change);
    if (!d_change.IsObject())
        throw std::runtime_error("document should be an object");
    assert(d_change.IsObject());
    if (what == "name")
    {
        std::string name = d_change["name"].GetString();
        users[val_user]._tablets[val_tablet]._name= name;
    }
    else if (what == "start_date")
    {
        std::string start_date_1 = d_change["start_date"].GetString();
        const char delim1 = '/';
        std::vector<int> date;
        tokenize(start_date_1, delim1, date);
        Date start_date(date[0], date[1], date[2]);
        date.clear();
        users[val_user]._tablets[val_tablet]._start_date = start_date;
    }
    else if (what == "period_days")
    {
        int period_days = d_change["period_days"].GetInt();
        users[val_user]._tablets[val_tablet]._period_days = period_days;
    }
    else return " 400 Bad Request - Данной команды не существует";
    Document val = toJSON1();
    SaveFileBase(val);
    std::string  ans = "Произошло изменение "+what+" в user " + std::to_string(val_user+1);
    return ans;
}

std::string putdaily_regimebt(int& val_user, int& val_time, const char* change)
{
    Document d_change = getFile(change);
    if (!d_change.IsObject())
        throw std::runtime_error("document should be an object");
    std::vector<int> time;
    std::string begin_time_str = d_change["begin_time"].GetString();
    const char delim = ':';
    tokenize(begin_time_str, delim, time);
    Time begin_time(time[0], time[1], time[2]);
    time.clear();
    users[val_user]._times[val_time]._begin_time = begin_time;
    Document val = toJSON1();
    SaveFileBase(val);
    std::string  ans = "Произошло изменение begin_time в user " + std::to_string(val_user + 1);
    return ans;
}

std::string putuserwhat(int& val_user, std::string& what, const char* change)
{
    Document d_change = getFile(change);
    if (!d_change.IsObject())
        throw std::runtime_error("document should be an object");
    assert(d_change.IsObject());
    if (what == "first_name")
    {
        std::string first_name = d_change["first_name"].GetString();
        users[val_user]._first_name = first_name;
    }
    else if (what == "last_name")
    {
        std::string last_name = d_change["last_name"].GetString();
        users[val_user]._first_name = last_name;
    }
    else return "400 Bad Request - Такой команды нет";
    SaveFileBase(toJSON1());
    std::string  ans = "Произошло изменение " + what + " в user " + std::to_string(val_user + 1);
    return ans;
}

std::string deleteuser(int& val_user)
{
    if (val_user < (users.size() - 1))
    {
        users.erase(users.begin() + val_user);
        std::vector<User1>(users).swap(users);
        for (int i = 0; i < users.size(); i++)
        {
            users[i]._userid = i + 1;
        }
        SaveFileBase(toJSON1());
        std::string  ans = "Произошло удаление user ";
        return ans;
    }
    else
    {
        users.erase(users.begin() + val_user);
        std::vector<User1>(users).swap(users);
        SaveFileBase(toJSON1());
        std::string  ans = "Произошло удаление user ";
        return ans;
    }
    
}

std::string deletetablet(int& val_user, int& val_tablet)
{
    if (val_tablet < (users[val_user]._tablets.size() - 1))
    {
        users[val_user]._tablets.erase(users[val_user]._tablets.begin() + val_tablet);
        std::vector<Tablets>(users[val_user]._tablets).swap(users[val_user]._tablets);
        for (int i = 0; i < users[val_user]._tablets.size(); i++)
        {
            users[val_user]._tablets[i]._tablet_id = i + 1;
        }
        SaveFileBase(toJSON1());
        std::string  ans = "Произошло удаление tablet  в user" + std::to_string(val_user + 1);
        return ans;
    }
    else
    {
        users[val_user]._tablets.erase(users[val_user]._tablets.begin() + val_tablet);
        std::vector<Tablets>(users[val_user]._tablets).swap(users[val_user]._tablets);
        SaveFileBase(toJSON1());
        std::string  ans = "Произошло удаление tablet  в user" + std::to_string(val_user+1);
        return ans;
    }
}

std::string deletetime_for_tablet(int& val_user, int& val_tablet, int& val_time_use)
{
    users[val_user]._tablets[val_tablet]._time_of_day.erase(users[val_user]._tablets[val_tablet]._time_of_day.begin() + val_time_use);
    std::vector<Times_Day_for_tablet>(users[val_user]._tablets[val_tablet]._time_of_day).swap(users[val_user]._tablets[val_tablet]._time_of_day);
    SaveFileBase(toJSON1());
   std::string  ans = "Произошло удаление tablet  в user" + std::to_string(val_user + 1);
    return ans;
}

std::string deletetime_of_day(int& val_user, int& val_time)
{
    if(val_time < (users[val_user]._times.size() - 1))
    {
        users[val_user]._times.erase(users[val_user]._times.begin() + val_time);
        std::vector<Daily_regime>(users[val_user]._times).swap(users[val_user]._times);
        for (int i = 0; i < users[val_user]._times.size(); i++)
        {
            users[val_user]._times[i]._time_id1 = i + 1;
        }
        SaveFileBase(toJSON1());
        std::string  ans = "Произошло удаление tablet  в user" + std::to_string(val_user + 1);
        return ans;
    }
    else
    {
        users[val_user]._times.erase(users[val_user]._times.begin() + val_time);
        std::vector<Daily_regime>(users[val_user]._times).swap(users[val_user]._times);
    SaveFileBase(toJSON1());
    std::string  ans = "Произошло удаление tablet  в user" + std::to_string(val_user + 1);
    return ans;
    }
}
