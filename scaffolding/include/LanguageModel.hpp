#ifndef _CS120_LANGUAGEMODEL_HPP
#define _CS120_LANGUAGEMODEL_HPP
#include <vector>
#include <list>
#include <map>
#include <string>
#include <cstdlib> // for srand
#include <ctime> // for time() (for srand)
#include "NgramCollection.hpp"

class LanguageModel {

public:

  LanguageModel(unsigned n): model(n){}
  
  /*reads input sentence and makes a map of Ngrams*/
  void makemodel(std::string filename);
  void readinfile(std::string str);
  NgramCollection getCollection() const { return model; }
  void generate();

  
  /*some generate function*/
  
private:

  NgramCollection model;
  unsigned n; 

};

#endif
