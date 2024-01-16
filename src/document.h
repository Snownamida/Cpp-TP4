#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <map>
#include <string>

class Document {
public:
  unsigned int getHit() const { return _hit; }
  std::map<std::string, unsigned int> getReferers() const { return _referers; }
  void addReferer(std::string url);

protected:
  unsigned int _hit = 0;
  std::map<std::string, unsigned int> _referers;
};

#endif // DOCUMENT_H