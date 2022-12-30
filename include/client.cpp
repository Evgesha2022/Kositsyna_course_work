#include<client.h>
#include<fstream>
#include<string>
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include <rapidjson/ostreamwrapper.h>
#include "rapidjson/encodings.h"
using namespace rapidjson;
int counter = 0;

int clientpart(std::string s)
{
    setlocale(LC_ALL, "Rus");
    std::vector<std::string> requests;
    std::string ok = "200 OK - ";
    std::string badr = "400 Bad Request - ";
    std::string notfound = "404 Not found - ";
    const char delim = '/';
    std::cout << s << std::endl;
        tokenize(s, delim, requests);
        int i = 0;
            if (requests[i] == "get")
            {
                if (requests[i + 1] == "users")//get/users
                {
                    std::cout << ok;
                    getuserswhat();//получение списка users
                }
                else if (requests[i + 1] == "user")
                {
                    if (requests[i + 4] == "tablet")
                    {
                        getusertabletwhat(requests[i + 2], requests[i + 3], requests[i + 5], requests[i + 6]);
                        //get/user/Ivan/Ivanov/tablet/Vitamin_C/period_day
                        //get/user/Ivan/Ivanov/tablet/Vitamin_C/time_of_day
                    }
                    else if (requests[i + 4] == "tablets") {
                        std::cout << ok;
                        getusertabletswhat(requests[i + 2], requests[i + 3], requests[i + 5]);
                        //get/user/Ivan/Ivanov/tablets/period_times
                        //get/user/Ivan/Ivanov/tablets/period_days
                        //get/user/Ivan/Ivanov/tablets/name
                    }
                    else
                    {
                        getuserwhat(requests[i + 2], requests[i + 3], requests[i + 4]);
                        //get/user/Ivan/Ivanov/daily_regime
                    }
                }
                else std::cout << badr << "“акой команды нет" << std::endl;
            }
            
            else if (requests[i] == "delete")
            {
            if (requests[i + 1] == "user")
            {
                int val_user = find_user(requests[i + 2], requests[i + 3]);
                if (val_user == -1) { std::cout << notfound << "User не найден" << std::endl; return 0; }
                std::string ans = deleteuser(val_user);//delete/user/Ivan/Ivanov
                std::cout << ok<< ans << std::endl;
                std::cin.clear();
            }
            else if (requests[i + 1] == "tablet")
            {
                int val_user = find_user(requests[i + 2], requests[i + 3]);
                if (val_user == -1) { std::cout << notfound<< "User не найден" << std::endl; return 0; }
                int val_tablet = find_tablet(val_user, requests[i + 4]);
                if (val_tablet == -1) { std::cout << notfound<< "Tablet не найден" << std::endl; return 0; }
                std::string ans =deletetablet(val_user, val_tablet);//delete/tablet/Ivan/Ivanov/Vitamin_C
                std::cout << ok<< ans << std::endl;
                std::cin.clear();

            }
            else if (requests[i + 1] == "time_for_tablet")//delete/time_for_tablet/Ivan/Ivanov/Vitamin_C/2
            {
                int val_user = find_user(requests[i + 2], requests[i + 3]);
                if (val_user == -1) { std::cout << notfound << "User не найден" << std::endl; return 0;
                }
                int val_tablet = find_tablet(val_user, requests[i + 4]);
                if (val_tablet == -1) { std::cout << notfound <<"Tablet не найден" << std::endl; return 0;
                }
                int val_time = stoi(requests[i + 5]);
                int val_time_use = find_time_tablet(val_user, val_tablet, val_time);
                if (val_time_use == -1) { std::cout << notfound << "ƒанное time не используетс€ в этих таблетках найден" << std::endl; return 0;
                }
                std::string ans = deletetime_for_tablet(val_user, val_tablet, val_time_use);
                std::cout << ok<< ans << std::endl;
                std::cin.clear();
            }
            else if (requests[i + 1] == "time_of_day")//delete/time_of_day/Ivan/Ivanov/2
            {
                int val_user = find_user(requests[i + 2], requests[i + 3]);
                if (val_user == -1) { std::cout << notfound<< "User не найден" << std::endl; return 0;
                }
                int val_time = find_time(val_user, stoi(requests[i + 4]));
                if (val_time == -1) { std::cout << notfound <<"Time не найден" << std::endl; return 0;
                }
                std::string ans = deletetime_of_day(val_user, val_time);
                std::cout << ok<<ans<< std::endl;
                std::cin.clear();

            }
            else std::cout << badr<< "“акой команды нет" << std::endl;
            }
            else if (requests[i] == "end")
            {
                return 0;
            }
            else std::cout << badr<< "“акой команды нет" << std::endl;
            requests.clear();
            i = 0;
        }
    



int clientpart1(std::string s, const char* s1)
{
    setlocale(LC_ALL, "Rus");
    std::vector<std::string> requests;
    const char delim = '/';
    tokenize(s, delim, requests);
    int i = 0;
    std::string ok = "200 OK - ";
    std::string creat = "201 Created - ";
    std::string badr = "400 Bad Request - ";
    std::string notfound = "404 Not found - ";
    std::cout << s << std::endl;
    if (requests[i] == "put")
    {
        if (requests[i + 1] == "tablet")
        {
            if (requests[i + 5] == "after_time")//put/tablet/Ivan/Ivanov/Vitamin_C/after_time/1
            {
                int val_user = find_user(requests[i + 2], requests[i + 3]);
                int val_tablet = find_tablet(val_user, requests[i + 4]);
                int val_time = stoi(requests[i + 6]);
                const char* change = s1;
                int val_time_use = find_time_tablet(val_user, val_tablet, val_time);
                std::cout << ok<< puttabletafter_time(val_user, val_tablet, val_time_use, change) << std::endl;
            }
            else
            {
                int val_user = find_user(requests[i + 2], requests[i + 3]);//put/tablet/Ivan/Ivanov/Vitamin_C/what
                if (val_user == -1) { std::cout << notfound<< "User не найден" << std::endl; return 0; }
                int val_tablet = find_tablet(val_user, requests[i + 4]);
                if (val_tablet == -1) {
                    std::cout << notfound<<  "Tablet не найден" << std::endl; return 0;
                }
                const char* change = s1;
                std::string what = requests[i + 5];
                std::cout << ok<< puttabletwhat(val_user, val_tablet, what, change);
            }
        }
        else if (requests[i + 1] == "daily_regime")//put/daily_regime/Ivan/Ivanov/2
        {
            int val_user = find_user(requests[i + 2], requests[i + 3]);
            if (val_user == -1) {
                std::cout << notfound<< "User не найден" << std::endl; return 0;
            }
            int val_time = find_time(val_user, stoi(requests[i + 4]));
            if (val_time == -1) {
                std::cout << notfound<<"Time не найден" << std::endl; return 0;
            }

            const char* change = s1;
            std::cout << ok<< putdaily_regimebt(val_user, val_time, change) << std::endl;
        }
        else if (requests[i + 1] == "user") //put/user/Ivan/Ivanov/first_name
        {
            int val_user = find_user(requests[i + 2], requests[i + 3]);
            if (val_user == -1) { std::cout << notfound<< "User не найден" << std::endl; return 0; }
            const char* change = s1;
            std::string what = requests[i + 4];
            std::cout << ok<< putuserwhat(val_user, what, change) << std::endl;
        }
        else  std::cout << badr<<"“акой команды нет" << std::endl;
    }
    else if (requests[i] == "post")
    {
        if (requests[i + 1] == "user")
        {
            const char* json_user = s1;
            std::string ans = postuser(json_user);// post/user
            std::cout << creat << ans << std::endl;
            std::cin.clear();
        }
        else if (requests[i + 1] == "tablet")
        {
            int val_user = find_user(requests[i + 2], requests[i + 3]);
            if (val_user == -1) { std::cout << notfound<< "User не найден" << std::endl; return 0; }
            const char* json_tablet = s1;

            std::string ans = posttablet(val_user, json_tablet);//post/tablet/Ivan/Ivanov
            std::cout << creat << ans << std::endl;
            std::cin.clear();

        }
        else if (requests[i + 1] == "time_for_tablet")
        {
            int val_user = find_user(requests[i + 2], requests[i + 3]);
            if (val_user == -1) { std::cout << notfound<< "User не найден" << std::endl; return 0; }
            int val_tablet = find_tablet(val_user, requests[i + 4]);
            if (val_tablet == -1) { std::cout << notfound<< "Tablet не найден" << std::endl; return 0; }
            const char* time_for_tablet = s1;

            std::string ans = post_time_for_tablet(val_user, val_tablet, time_for_tablet);
            std::cout << creat << ans << std::endl;
            std::cin.clear();

        }
        else if (requests[i + 1] == "time_of_day")
        {
            int val_user = find_user(requests[i + 2], requests[i + 3]);
            if (val_user == -1) { std::cout << notfound<<"User не найден" << std::endl; return 0; }
            const char* time_of_day = s1;
            std::string ans = post_time_of_day(val_user, time_of_day);
            std::cout << creat <<ans << std::endl;
            std::cin.clear();

        }
        else std::cout << badr<<"“акой команды нет" << std::endl;
    }
    else std::cout << badr<<"“акой команды нет" << std::endl;
    requests.clear();
    std::cin.clear();
    i = 0;
}

void printConsole(rapidjson::Document& doc)
{
    setlocale(LC_ALL, "Rus");
    rapidjson::StringBuffer buffer;
    buffer.Clear();
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    std::cout << buffer.GetString() << std::endl;
}

void SaveFile(rapidjson::Document& doc, std::string what)
{
    std::string s = std::to_string(counter);
    std::ofstream ofs( s+"." + what + ".json");
    OStreamWrapper osw(ofs);
    Writer<OStreamWrapper> writer(osw);
    doc.Accept(writer);
    counter++;
}

void SaveFileBase(rapidjson::Document& doc)
{
    std::string s = std::to_string(counter);
    std::ofstream ofs(s+"."+"output.json");
    OStreamWrapper osw(ofs);
    Writer<OStreamWrapper> writer(osw);
    doc.Accept(writer);
    counter++;
}

void tokenize(std::string& str, const char delim, std::vector<std::string>& out)
{
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}
void tokenize(std::string& str, const char delim, std::vector<int>& out)
{
    size_t start;
    size_t end = 0;
    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        out.push_back((stoi(str.substr(start, end - start))));
    }
}
