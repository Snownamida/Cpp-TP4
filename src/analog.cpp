#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

using std::string, std::cout, std::endl;

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
    cout << "============================" << endl;
    cout << log.IP << endl;
    cout << log.username << endl;
    cout << log.authenticatedUser << endl;
    cout << log.time << endl;
    cout << log.timeZone << endl;
    cout << log.request << endl;
    cout << log.code << endl;
    cout << log.size << endl;
    cout << log.referer << endl;
    cout << log.UA << endl;
    cout << "============================" << endl;
  }
}