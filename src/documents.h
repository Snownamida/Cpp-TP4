#ifndef DOCUMENTS_H
#define DOCUMENTS_H

#include "document.h"
#include <algorithm>
#include <map>
#include <string>
#include <vector>

struct Documents : std::map<std::string, Document> {

  std::vector<std::pair<std::string, Document>>
  getSortedDucumentsByHitNumber(unsigned int maxShow) const;
  void printMostHitedDocuments(const unsigned int maxShow) const;
  void generateDot(const std::string &dotFileName) const;
};

std::ostream &operator<<(std::ostream &os, Documents &documents);

#endif // DOCUMENTS_H