#include <algorithm>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::string;

const string BASE_URL = "http://intranet-if.insa-lyon.fr";
const unsigned int MAX_SHOW = 10;

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
  std::map<string, unsigned int> getReferers() const { return _referers; }
  void addReferer(string url) {
    _hit++;
    _referers[url]++;
  }

protected:
  unsigned int _hit = 0;
  std::map<string, unsigned int> _referers;
};

std::ostream &operator<<(std::ostream &os, const Log &log) {
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
  return os;
}

std::ostream &operator<<(std::ostream &os,
                         std::map<string, document> &documents) {

  for (auto &document : documents) {
    cout << document.first << " " << document.second.getHit() << endl;
    for (auto &referer : document.second.getReferers()) {
      cout << "\t" << referer.first << " " << referer.second << endl;
    }
  }
  return os;
}

void addLogsFromFile(std::vector<Log> &logs, const char *const filename, bool optionE, bool optionT, string heure) {
  std::ifstream fin(filename);

  if (!fin.is_open()) {
    throw "File open failed";
  }

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

    // Heure Filter
    string requestHeure;
    size_t found = log.time.find(':');
    requestHeure.assign(log.time, found + 1, 2);

    if (optionT && requestHeure != heure) continue;

    // Format Filter
    string requestFormat = "";
    found = log.requestUrl.find('.');
    if (found != string::npos) 
        requestFormat.assign(log.requestUrl, found + 1, log.requestUrl.length() - found);
    
    if (optionE && (requestFormat == "jpg" || requestFormat == "css" || requestFormat == "js")) continue;
    

    logs.push_back(log);
  }
  fin.close();
}

int main(int argc, char *argv[]) {

  std::vector<Log> logs;

  bool optionG = 0, optionE = 0, optionT = 0;
  string unString, dotFile, heure;
  for (int i = 1; i < argc - 1; ++i) {
      unString = argv[i];
      if (unString == "-g") {
          optionG = 1;
          dotFile = argv[i + 1];
      }
      else if (unString == "-e") {
          optionE = 1;
      }
      else if (unString == "-t") {
          optionT = 1;
          heure = argv[i + 1];
      }
  }
  addLogsFromFile(logs, argv[argc-1], optionE, optionT, heure);

  // for (auto &log : logs) {
  //   cout << log;
  // }

  std::map<string, document> documents;
  for (auto &log : logs) {
    documents[log.requestUrl].addReferer(log.referer);
  }

  // cout << documents;
  std::vector<std::pair<string, document>> documentsSorted(documents.begin(),
  documents.end());

  std::sort(documentsSorted.begin(), documentsSorted.end(),
    [](const std::pair<string, document>& a,
       const std::pair<string, document>& b) {
          return a.second.getHit() > b.second.getHit();
    });

  unsigned int count = 0;
  for (auto& document : documentsSorted) {
        cout << document.first << " " << document.second.getHit() << endl;
        ++count;
        if (count >= MAX_SHOW)
            break;
          // for (auto &referer : document.second.getReferers()) {
          //   cout << "\t" << referer.first << " " << referer.second << endl;
          // }
  }
  
 
  
  return 0;
}