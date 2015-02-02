#include "Stripper.hpp"

ostream& operator<<(ostream& output, const Stripper& stripper){

  output<<"Meant to remove the '"<<stripper.getObjectNameToRemove()<<"' key from file '"<<stripper.getFileNameToStrip()<<"'";
  return output;
  
}

Stripper::Stripper(const TFile& fileToStrip, string objectNameToRemove):fileToStrip(&fileToStrip),objectNameToRemove(objectNameToRemove){

}

void Stripper::strip(){
 
  TIter keyIterator= fileToStrip->GetListOfKeys()->begin(); //iterator over the contents of the fileToStrip
  while(keyIterator != fileToStrip->GetListOfKeys()->end()){ //returns the pointer and increment it, when the pointer is not allocated it returns zero so the loop ends
    
    if((*keyIterator)->GetName() != objectNameToRemove) strippedObjects[(*keyIterator)->GetName()] = dynamic_cast<TKey*>(*keyIterator)->ReadObj();//this is silly to cast a TObject to a TKey to eventually return a TObject with the ReadObj method, but heh, this is ROOT !
    ++keyIterator;

  }

}

void Stripper::save(const string& newFileName){

  TFile outputFile(newFileName.c_str(), "recreate");
  for(auto it = strippedObjects.begin(); it != strippedObjects.end(); ++it) (*it).second->Write((*it).first);

}

void Stripper::setFileToStrip(const TFile& fileToStrip){
  
  this->fileToStrip = &fileToStrip;

}

void Stripper::setObjectNameToRemove(const string& objectNameToRemove){
  
  this->objectNameToRemove = objectNameToRemove;

}

const char* Stripper::getFileNameToStrip() const{
  
  return fileToStrip->GetName();

}

const string& Stripper::getObjectNameToRemove() const{
  
  return objectNameToRemove;

}



