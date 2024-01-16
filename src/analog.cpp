#include <iostream>
#include <ostream>
#include <string>
#include <utility>

#include "document.h"
#include "documents.h"
#include "logs.h"

using std::cout;
using std::endl;
using std::string;

const string BASE_URL = "http://intranet-if.insa-lyon.fr";
const unsigned int MAX_SHOW = 10;

int main(int argc, char *argv[]) {

  Logs logs;

  logs.addLogsFromFile(argv[1], BASE_URL);

  // cout << logs;

  Documents documents;
  for (auto &log : logs.get()) {
    documents[log.requestUrl].addReferer(log.referer);
  }

  // cout << documents;

  for (auto &document : documents.getSortedDucumentsByHit(MAX_SHOW)) {
    cout << document.first << " " << document.second.getHit() << endl;
    // for (auto &referer : document.second.getReferers()) {
    //   cout << "\t" << referer.first << " " << referer.second << endl;
    // }
  }
  
 
  
  return 0;
}