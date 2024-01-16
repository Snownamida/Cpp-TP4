#include "document.h"

void Document::addReferer(std::string url) {
  _hit++;
  _referers[url]++;
}
