#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;

struct Log {
  string IP;
  string username;
  string authenticatedUser;
  string time;
  string timeZone;
  string request;
  char code[4];
  unsigned int size;
  string referer;
  string UA;
};

class document {
public:
  unsigned int getHit() const { return _hit; }
  string getUrl() const { return _url; }
  void addReferer(string url) {
    _hit++;
    if (referers.find(url) == referers.end())
      referers[url] = 0;
    else
      referers[url]++;
  }

protected:
  string _url;
  unsigned int _hit = 0;
  std::map<string, unsigned int> referers;
};

std::ostream &operator<<(std::ostream &os, const Log &log) {
  os << "============================" << endl;
  os << log.IP << endl;
  os << log.username << endl;
  os << log.authenticatedUser << endl;
  os << log.time << endl;
  os << log.timeZone << endl;
  os << log.request << endl;
  os << log.code << endl;
  os << log.size << endl;
  os << log.referer << endl;
  os << log.UA << endl;
  os << "============================" << endl;
  return os;
}

int main(int argc, char *argv[]) {

  std::ifstream fin(argv[1]);

  if (!fin.is_open()) {
    cout << "File open failed" << endl;
    return -1;
  }

  std::vector<Log> logs;

  while (!fin.eof()) {
    Log log;
    string tmp;

    fin >> std::quoted(log.IP);
    if (log.IP.empty())
      break;

    fin >> std::quoted(log.username);
    fin >> std::quoted(log.authenticatedUser);

    fin >> std::quoted(log.time);
    log.time.erase(0, 1);

    fin >> std::quoted(log.timeZone);
    log.timeZone.pop_back();

    fin >> std::quoted(log.request);

    fin >> std::quoted(tmp);
    std::strcpy(log.code, tmp.c_str());

    fin >> std::quoted(tmp);
    if (tmp == "-")
      tmp = "0";
    log.size = std::stoi(tmp);

    fin >> std::quoted(log.referer);
    fin >> std::quoted(log.UA);

    logs.push_back(log);
  }

  for (auto &log : logs) {
    cout << log;
  }
}