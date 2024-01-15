#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;

const string BASE_URL = "http://intranet-if.insa-lyon.fr";

struct Log {
  string IP;
  string username;
  string authenticatedUser;
  string time;
  string timeZone;
  string requestMethod;
  string requestUrl;
  string requestProtocol;
  unsigned short code;
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
  os << log.requestMethod << endl;
  os << log.requestUrl << endl;
  os << log.requestProtocol << endl;
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
    std::istringstream tmpiss;

    fin >> log.IP;
    if (log.IP.empty())
      break;

    fin >> log.username >> log.authenticatedUser >> log.time >>
        std::quoted(log.timeZone);

    fin >> std::quoted(tmp);
    tmpiss = std::istringstream(tmp);
    tmpiss >> log.requestMethod >> log.requestUrl >> log.requestProtocol;

    fin >> log.code;

    fin >> tmp;
    if (tmp == "-")
      tmp = "0";
    log.size = std::stoi(tmp);

    fin >> std::quoted(log.referer);
    fin >> std::quoted(log.UA);

    log.time.erase(0, 1);
    log.timeZone.pop_back();
    if (!log.referer.compare(0, BASE_URL.length(), BASE_URL))
      log.referer.erase(0, BASE_URL.length());

    logs.push_back(log);
  }

  for (auto &log : logs) {
    cout << log;
  }
}