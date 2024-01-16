#include "documents.h"
#include <iostream>

std::vector<std::pair<std::string, Document>>
Documents::getSortedDucumentsByHit(unsigned int maxShow) const {
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

std::ostream &operator<<(std::ostream &os, Documents &documents) {

  for (auto &document : documents._documents) {
    std::cout << document.first << " " << document.second.getHit() << std::endl;
    for (auto &referer : document.second.getReferers()) {
      std::cout << "\t" << referer.first << " " << referer.second << std::endl;
    }
  }
  return os;
}
