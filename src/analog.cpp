#include "documents.h"
#include "logs.h"
#include <cstring>
#include <string>

using std::string;

const string BASE_URL = "http://intranet-if.insa-lyon.fr";
const unsigned int MAX_SHOW = 10;

void setOptions(int argc, const char *const argv[], bool &flagGenerateDot,
                bool &flagExcludeImageCSSJS, bool &flagSetTimeInterval,
                string &timeInterval, string &dotFileName) {
  for (int i = 1; i < argc - 1; ++i) {
    if (!strcmp(argv[i], "-g")) {
      flagGenerateDot = true;
      ++i;
      if (i >= argc)
        throw "Please input dot file name";
      dotFileName = argv[i];
    } else if (!strcmp(argv[i], "-e")) {
      flagExcludeImageCSSJS = 1;
    } else if (!strcmp(argv[i], "-t")) {
      flagSetTimeInterval = 1;
      ++i;
      if (i >= argc)
        throw "Please input time";
      timeInterval = argv[i];
    } else
      throw "invalid option";
  }
}

int main(int argc, char *argv[]) {

  Logs logs;

  bool flagGenerateDot = false, flagExcludeImageCSSJS = false,
       flagSetTimeInterval = false;
  string timeInterval, dotFileName;
  
  setOptions(argc, argv, flagGenerateDot, flagExcludeImageCSSJS,
             flagSetTimeInterval, timeInterval, dotFileName);

  logs.addLogsFromFile(argv[argc - 1], BASE_URL, flagExcludeImageCSSJS,
                       flagSetTimeInterval, timeInterval);

  Documents documents;
  for (auto &log : logs.get()) {
    documents[log.requestUrl].addReferer(log.referer);
  }

  documents.printMostHitedDocuments(MAX_SHOW);
  if (flagGenerateDot)
    documents.generateDot(dotFileName);

  return 0;
}