#ifndef DOCUMENTS_H
#define DOCUMENTS_H

#include "document.h"
#include <algorithm>
#include <map>
#include <string>
#include <vector>

struct Documents {
  std::map<std::string, Document> _documents;

  Document &operator[](std::string url) { return _documents[url]; }

  std::vector<std::pair<std::string, Document>>
  getSortedDucumentsByHit(unsigned int maxShow) const;
  void printMostHitedDocuments(const unsigned int maxShow) const;
  void generateDot() const;
};

  std::ostream &operator<<(std::ostream &os, Documents &documents);

#endif // DOCUMENTS_H