#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
#include <string>
#include "rapidjson/filereadstream.h" 
#include "rapidjson/encodedstream.h" 
#include <rapidjson/ostreamwrapper.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include<vector>
#include<server.h>
void printConsole(rapidjson::Document& doc);

void SaveFile(rapidjson::Document& doc, std::string what);
void SaveFileBase(rapidjson::Document& doc);

void tokenize(std::string& str, const char delim, std::vector<std::string>& out);
void tokenize(std::string& str, const char delim, std::vector<int>& out);
int clientpart(std::string s);

int clientpart1(std::string s, const char* s1);
std::string readfile(std::string name_file);