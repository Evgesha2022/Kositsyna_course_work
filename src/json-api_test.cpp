#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
#include <string>
#include <client.h>
#include<server.h>
#include "rapidjson/filereadstream.h" 
#include "rapidjson/encodedstream.h" 
#include <rapidjson/ostreamwrapper.h>
#include <cstdio>
#include <fstream>
#include <iostream>

using namespace rapidjson;
int main() {
   setlocale(LC_ALL, "Rus");
   downloadData();
   clientpart("get/user/Ivan/Ivanov/tablet/Vitamin_C/period_day");
   std::cout << std::endl;
   clientpart("delete/user/Ivan/Ivanov");
   std::cout << std::endl;
   clientpart("get/users");
   std::cout << std::endl;
   clientpart1("post/user", "postuser.json");
   std::cout << std::endl;
   clientpart("get/user/Ivan/Ivanov/tablet/Vitamin_E/period_day");
   std::cout << std::endl;
   clientpart1("post/time_of_day/Ivan/Ivanov", "posttime_of_day.json");
   std::cout << std::endl;
   clientpart("get/user/Ivan/Ivanov/daily_regime");
   std::cout << std::endl;
   clientpart("get/user/Ivan/Ivanov/tablets/period_days");
   std::cout << std::endl;
   clientpart1("put/tablet/Ivan/Ivanov/Vitamin_D/start_date", "puttabletstartdate.json");
   std::cout << std::endl;
   clientpart("get/user/Ivan/Ivanov/tablets/period_days");
   std::cout<<std::endl;
   clientpart("get/user/Ivan/Ivanov/tablet/Vitamin_C/time_of_day");
   std::cout << std::endl;
   clientpart1("put/tablet/Ivan/Ivanov/Vitamin_C/after_time/1", "puttabletafter_time.json");
   std::cout << std::endl;
   clientpart("get/user/Ivan/Ivanov/tablets/period_times");
   std::cout << std::endl;
   clientpart("delete/time_for_tablet/Ivan/Ivanov/Vitamin_C/1");
   std::cout << std::endl;
   clientpart("get/user/Ivan/Ivanov/tablet/Vitamin_C/time_of_day");
   std::cout << std::endl;
   clientpart1("post/time_for_tablet/Ivan/Ivanov/Vitamin_C", "posttime_for_tablet.json");
   std::cout << std::endl;
   clientpart("get/user/Ivan/Ivanov/tablet/Vitamin_C/time_of_day");
   std::cout << std::endl;
   clientpart("get/smt/time_of_day");
   std::cout << std::endl;
   system("pause");
   return 0;
}