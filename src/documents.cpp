#include "documents.h"
#include <fstream>
#include <iostream>

std::vector<std::pair<std::string, Document>>
Documents::getSortedDucumentsByHitNumber(unsigned int maxShow) const {
  std::vector<std::pair<std::string, Document>> documentsSorted(begin(), end());

  std::sort(documentsSorted.begin(), documentsSorted.end(),
            [](const std::pair<std::string, Document> &a,
               const std::pair<std::string, Document> &b) {
              return a.second.getHit() > b.second.getHit();
            });

  if (documentsSorted.size() > maxShow)
    documentsSorted.resize(maxShow);

  return documentsSorted;
}

void Documents::printMostHitedDocuments(const unsigned int maxShow) const {
  for (auto &document : getSortedDucumentsByHitNumber(maxShow)) {
    std::cout << document.first << " (" << document.second.getHit() << " hits)"
              << std::endl;
    // for (auto &referer : document.second.getReferers()) {
    //   cout << "\t" << referer.first << " " << referer.second << endl;
    // }
  }
}

void Documents::generateDot(const std::string &dotFileName) const {

  std::ofstream fout(dotFileName);

  if (!fout.is_open()) {
    throw "Dot file open failed";
  }

  fout << "digraph {" << std::endl;
  for (auto &document : *this) {
    for (auto &referer : document.second.getReferers()) {
      fout << "\t\"" << referer.first << "\" -> \"" << document.first
           << "\" [label=\"" << referer.second << "\"];" << std::endl;
    }
  }
  fout << "}" << std::endl;
  fout.close();
}

std::ostream &operator<<(std::ostream &os, Documents &documents) {

  for (auto &document : documents) {
    std::cout << document.first << " (" << document.second.getHit() << " hits)"
              << std::endl;
    for (auto &referer : document.second.getReferers()) {
      std::cout << "\t" << referer.first << " (" << referer.second << " hits)"
                << std::endl;
    }
  }
  return os;
}
