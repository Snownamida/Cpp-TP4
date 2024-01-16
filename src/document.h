#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <map>
#include <string>

class document {
public:
  unsigned int getHit() const { return _hit; }
  std::map<std::string, unsigned int> getReferers() const { return _referers; }
  void addReferer(std::string url) {
    _hit++;
    _referers[url]++;
  }

protected:
  unsigned int _hit = 0;
  std::map<std::string, unsigned int> _referers;
};

typedef std::map<std::string, document> Documents;

std::ostream &operator<<(std::ostream &os, Documents &documents);

#endif // DOCUMENT_H