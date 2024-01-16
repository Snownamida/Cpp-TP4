#include <cstring>
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

  bool flagGenerateDot = false, flagExcludeImageCSSJS = false,
       flagSetTimeInterval = false;

  string TimeInterval, dotFileName;
  for (int i = 1; i < argc - 1; ++i) {
    if (!strcmp(argv[i], "-g")) {
      flagGenerateDot = 1;
      dotFileName = argv[i + 1];
      ++i;
    } else if (!strcmp(argv[i], "-e")) {
      flagExcludeImageCSSJS = 1;
    } else if (!strcmp(argv[i], "-t")) {
      flagSetTimeInterval = 1;
      TimeInterval = argv[i + 1];
      ++i;
    } else
      throw "invalid option";
  }

  logs.addLogsFromFile(argv[argc - 1], BASE_URL, flagExcludeImageCSSJS,
                       flagSetTimeInterval, TimeInterval);

  // cout << logs;

  Documents documents;
  for (auto &log : logs.get()) {
    documents[log.requestUrl].addReferer(log.referer);
  }

  // cout << documents;

  // documents.printMostHitedDocuments(MAX_SHOW);

  documents.generateDot();

  return 0;
}