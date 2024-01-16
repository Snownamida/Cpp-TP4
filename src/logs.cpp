#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "logs.h"

std::ostream &operator<<(std::ostream &os, const Log &log) {
  os << log.IP << std::endl;
  os << log.username << std::endl;
  os << log.authenticatedUser << std::endl;
  os << log.time << std::endl;
  os << log.timeZone << std::endl;
  os << log.requestMethod << std::endl;
  os << log.requestUrl << std::endl;
  os << log.requestProtocol << std::endl;
  os << log.code << std::endl;
  os << log.size << std::endl;
  os << log.referer << std::endl;
  os << log.UA << std::endl;
  return os;
}

void Logs::addLogsFromFile(const char *const filename,
                           const std::string &BASE_URL, bool optionE, bool optionT, std::string heure) {
  std::ifstream fin(filename);

  if (!fin.is_open()) {
    throw "File open failed";
  }

  while (!fin.eof()) {
    Log log;
    std::string tmp;
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
    std::string requestHeure;
    size_t found = log.time.find(':');
    requestHeure.assign(log.time, found + 1, 2);
    if (optionT && requestHeure != heure) continue;

    // Format Filter
    std::string requestFormat;
    found = log.requestUrl.find('.');
    requestFormat.assign(log.requestUrl, found + 1, log.requestUrl.length() - found);
    if (optionE && (requestFormat == "jpg" || requestFormat == "jpg" || requestFormat == "js")) continue;

    _logs.push_back(log);
  }

    

  fin.close();
}

std::ostream &operator<<(std::ostream &os, const Logs &logs) {
  for (auto &log : logs._logs) {
    os << log;
  }
  return os;
}