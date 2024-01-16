#ifndef LOGS_H
#define LOGS_H

#include <string>

struct Log {
  std::string IP;
  std::string username;
  std::string authenticatedUser;
  std::string time;
  std::string timeZone;
  std::string requestMethod;
  std::string requestUrl;
  std::string requestProtocol;
  unsigned short code;
  unsigned int size;
  std::string referer;
  std::string UA;
};

void addLogsFromFile(std::vector<Log> &logs, const char *const filename,
                     const std::string &BASE_URL);

std::ostream &operator<<(std::ostream &os, const Log &log);

#endif // LOGS_H