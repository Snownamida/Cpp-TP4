#include "document.h"
#include <iostream>


std::ostream &operator<<(std::ostream &os, Documents &documents) {

  for (auto &document : documents) {
    std::cout << document.first << " " << document.second.getHit() << std::endl;
    for (auto &referer : document.second.getReferers()) {
      std::cout << "\t" << referer.first << " " << referer.second << std::endl;
    }
  }
  return os;
}