#ifndef STRIPPER_H
#define STRIPPER_H

#include <string>
#include <iostream>
#include <map>
#include <TFile.h>
#include <TObject.h>
#include <TKey.h>
#include <TIterator.h>

using namespace std;

class Stripper{

  const TFile* fileToStrip;
  map<const char*, TObject*> strippedObjects;
  string objectNameToRemove;
  
public:  
  Stripper(const TFile& fileToStrip, string objectNameToRemove);
  void strip();//actually stip down the vector of objects 
  void save(const string& newFileName);//save the file to another name
  void setFileToStrip(const TFile& fileToStrip);
  void setObjectNameToRemove(const string& objectNameToRemove);
  const char* getFileNameToStrip() const;
  const string& getObjectNameToRemove() const;
  
};

ostream& operator<<(ostream& output, const Stripper& stripper);

#endif