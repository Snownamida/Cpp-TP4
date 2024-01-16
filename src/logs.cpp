#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "logs.h"

const std::string TICKET_ETUDIANT_URL =
    "/SiteWebIF/Intranet-etudiant.php?ticket=";
const std::string TICKET_PERSONNEL_URL =
    "/SiteWebIF/Intranet-personnel.php?ticket=";
const std::string GOOGLE_FR_URL = "http://www.google.fr/";
const std::string GOOGLE_COM_URL = "http://www.google.fr/";
const std::string FAVICON_URL = "/cas/themes/insa/media/favicon.ico";

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
    if (!log.referer.compare(0, GOOGLE_FR_URL.length(), GOOGLE_FR_URL))
      log.referer = GOOGLE_FR_URL + '*';
    if (!log.referer.compare(0, GOOGLE_COM_URL.length(), GOOGLE_COM_URL))
      log.referer = GOOGLE_COM_URL + '*';
    if (!log.requestUrl.compare(0, TICKET_ETUDIANT_URL.length(),
                                TICKET_ETUDIANT_URL))
      log.requestUrl = TICKET_ETUDIANT_URL + "*";
    if (!log.requestUrl.compare(0, TICKET_PERSONNEL_URL.length(),
                                TICKET_PERSONNEL_URL))
      log.requestUrl = TICKET_PERSONNEL_URL + "*";
    // if (!log.requestUrl.compare(0, FAVICON_URL.length(), FAVICON_URL))
    //   log.requestUrl = FAVICON_URL;

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
    if (optionE &&
        (extension == "jpg" || extension == "png" || extension == "gif" ||
         extension == "ico" || extension == "css" || extension == "js"))
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