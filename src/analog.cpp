#include <algorithm>
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "logs.h"

using std::cout;
using std::endl;
using std::string;

const string BASE_URL = "http://intranet-if.insa-lyon.fr";
const unsigned int MAX_SHOW = 10;

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

int main(int argc, char *argv[]) {

  std::vector<Log> logs;

  addLogsFromFile(logs, argv[1], BASE_URL);

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
            [](const std::pair<string, document> &a,
               const std::pair<string, document> &b) {
              return a.second.getHit() > b.second.getHit();
            });

  unsigned int count = 0;
  for (auto &document : documentsSorted) {
    cout << document.first << " " << document.second.getHit() << endl;
    ++count;
    if (count >= MAX_SHOW)
      break;
    // for (auto &referer : document.second.getReferers()) {
    //   cout << "\t" << referer.first << " " << referer.second << endl;
    // }
  }
}