// Data parsing functions from MP Schedule 

#include "utils.h"
#include <sstream>
#include <fenv.h>
#include <signal.h>
#include <vector>

std::string file_to_string(const std::string& filename){
  std::ifstream text(filename);

  std::stringstream strStream;
  if (text.is_open()) {
    strStream << text.rdbuf();
  }
  return strStream.str();
}

std::string TrimRight(const std::string & str) {
    std::string tmp = str;
    return tmp.erase(tmp.find_last_not_of(" ") + 1);
}

std::string TrimLeft(const std::string & str) {
    std::string tmp = str;
    return tmp.erase(0, tmp.find_first_not_of(" "));
}

// Method to remove quotation marks from data
std::string TrimQuotations(const std::string & str) {
    std::string tmp = str;
    return tmp.erase(0, tmp.find_first_not_of("\"")).erase(tmp.find_last_not_of("\"") + 1);
}

std::string Trim(const std::string & str) {
    std::string tmp = str;
    return TrimLeft(TrimRight(str));
}

int SplitString(const std::string & str1, char sep, std::vector<std::string> &fields) {
    std::string str = str1;
    std::string::size_type pos;
    while((pos=str.find(sep)) != std::string::npos) {
        fields.push_back(str.substr(0,pos));
        str.erase(0,pos+1);  
    }
    fields.push_back(str);
    return fields.size();
}

bool comp(pair<string, double>& a, pair<string, double>& b) {
    return a.second > b.second;
}

vector<pair<string, double>> sortmap(map<string, double>& M) {
    vector<pair<string, double>> A;
    for (auto& it: M) {
        A.push_back(it);
    }
    sort(A.begin(), A.end(), comp);
    return A;
}