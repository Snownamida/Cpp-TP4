#ifndef LOGS_H
#define LOGS_H

#include <ostream>
#include <string>
#include <vector>

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

class Logs {
public:
  void addLogsFromFile(const char *const filename, const std::string &BASE_URL,
                       bool flagExcludeImageCSSJS, bool flagSetTimeInterval,
                       std::string timeInterval);
  friend std::ostream &operator<<(std::ostream &os, const Logs &logs);
  std::vector<Log> get() const { return _logs; }

protected:
  std::vector<Log> _logs;
};

std::ostream &operator<<(std::ostream &os, const Log &log);

#endif // LOGS_H