#ifndef STRIPPER_H
#define STRIPPER_H

#include <string>
#include <iostream>
#include <map>
#include <TFile.h>
#include <TObject.h>
#include <TKey.h>
#include <TIterator.h>

class Stripper{

  const TFile* fileToStrip;
  std::map<const char*, TObject*> strippedObjects;
  std::string objectNameToRemove;
  
public:  
  Stripper(const TFile& fileToStrip, const std::string& objectNameToRemove);
  void strip();//actually stip down the vector of objects 
  void save(const std::string& newFileName);//save the file to another name
  void setFileToStrip(const TFile& fileToStrip);
  void setObjectNameToRemove(const std::string& objectNameToRemove);
  const char* getFileNameToStrip() const;
  const std::string& getObjectNameToRemove() const;
  
};

std::ostream& operator<<(std::ostream& output, const Stripper& stripper);

#endif