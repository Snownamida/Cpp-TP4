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

  bool optionG = 0, optionE = 0, optionT = 0;
  string unString, heure, dotFile;
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

  logs.addLogsFromFile(argv[argc-1], BASE_URL, optionE, optionT, heure);

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