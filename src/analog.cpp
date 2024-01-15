#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Log {
  std::string IP;
  std::string username;
  std::string authenticatedUser;
  std::string time;
  std::string timeZone;
  std::string request;
  char code[4];
  unsigned int size;
  std::string referer;
  std::string UA;
};

int main(int argc, char *argv[]) {

  std::ifstream fin(argv[1]);

  if (!fin.is_open()) {
    std::cout << "File open failed" << std::endl;
    return -1;
  }

  std::vector<Log> logs;

  while (!fin.eof()) {
    Log log;
    std::string tmp;

    fin >> std::quoted(log.IP);
    if (log.IP.empty())
      break;

    fin >> std::quoted(log.username);
    fin >> std::quoted(log.authenticatedUser);
    fin >> std::quoted(log.time);
    fin >> std::quoted(log.timeZone);
    fin >> std::quoted(log.request);

    fin >> std::quoted(tmp);
    std::strcpy(log.code, tmp.c_str());

    fin >> std::quoted(tmp);
    log.size = std::stoi(tmp);

    fin >> std::quoted(log.referer);
    fin >> std::quoted(log.UA);

    logs.push_back(log);
  }

  for (auto &log : logs) {
    std::cout << "============================" << std::endl;
    std::cout << log.IP << std::endl;
    std::cout << log.username << std::endl;
    std::cout << log.authenticatedUser << std::endl;
    std::cout << log.time << std::endl;
    std::cout << log.timeZone << std::endl;
    std::cout << log.request << std::endl;
    std::cout << log.code << std::endl;
    std::cout << log.size << std::endl;
    std::cout << log.referer << std::endl;
    std::cout << log.UA << std::endl;
    std::cout << "============================" << std::endl;
  }
}