#ifndef DOCUMENTS_H
#define DOCUMENTS_H

#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include "document.h"

struct Documents {
  std::map<std::string, Document> _documents;

  Document &operator[](std::string url) { return _documents[url]; }

  std::vector<std::pair<std::string, Document>>
  getSortedDucumentsByHit(unsigned int maxShow) {
    std::vector<std::pair<std::string, Document>> documentsSorted(
        _documents.begin(), _documents.end());

    std::sort(documentsSorted.begin(), documentsSorted.end(),
              [](const std::pair<std::string, Document> &a,
                 const std::pair<std::string, Document> &b) {
                return a.second.getHit() > b.second.getHit();
              });

    if (documentsSorted.size() > maxShow)
      documentsSorted.resize(maxShow);

    return documentsSorted;
  }
};

std::ostream &operator<<(std::ostream &os, Documents &documents);

#endif // DOCUMENTS_H