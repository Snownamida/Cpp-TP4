#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "logs.h"

std::ostream &operator<<(std::ostream &os, const Log &log) {
  os << "IP                : " << log.IP << std::endl;
  os << "username          : " << log.username << std::endl;
  os << "authenticatedUser : " << log.authenticatedUser << std::endl;
  os << "time              : " << log.time << std::endl;
  os << "timeZone          : " << log.timeZone << std::endl;
  os << "requestMethod     : " << log.requestMethod << std::endl;
  os << "requestUrl        : " << log.requestUrl << std::endl;
  os << "requestProtocol   : " << log.requestProtocol << std::endl;
  os << "code              : " << log.code << std::endl;
  os << "size              : " << log.size << std::endl;
  os << "referer           : " << log.referer << std::endl;
  os << "UA                : " << log.UA << std::endl;
  return os;
}

void Logs::addLogsFromFile(const char *const filename,
                           const std::string &BASE_URL, bool optionE,
                           bool optionT, std::string heure) {
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
    if (optionT && requestHeure != heure)
      continue;

    // Format Filter
    std::string extension;
    found = log.requestUrl.find_last_of('.');
    extension.assign(log.requestUrl, found + 1,
                         log.requestUrl.length() - found);
    if (optionE && (extension == "jpg" || extension == "png" ||
                    extension == "gif" || extension == "ico" ||
                    extension == "css" || extension == "js"))
      continue;

    _logs.push_back(log);
  }

  fin.close();
}

std::ostream &operator<<(std::ostream &os, const Logs &logs) {
  for (auto &log : logs._logs) {
    os << "-------------------------" << std::endl;
    os << log;
    os << "-------------------------" << std::endl;
  }
  return os;
}