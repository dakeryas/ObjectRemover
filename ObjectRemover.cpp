#include <boost/filesystem.hpp>
#include "Stripper.hpp"

void ObjectRemover(const string& fileNameToClean, const string& objectNameToRemove, const string newFileNameSuffix = "_stripped"){

  TFile fileToClean(fileNameToClean.c_str());
  Stripper stripper(fileToClean, objectNameToRemove);//create the Stripper object with the file to clean and the item to look for
  cout<<stripper<<endl;
  stripper.strip();
  stripper.save((fileNameToClean+newFileNameSuffix).c_str());//create a new filename with an extra extension
  
  cout<<"Saved the stripped file as '"<<fileNameToClean+newFileNameSuffix<<"'"<<endl;
  
}

int main (int argc, char* argv[]){
  
  if(argc > 2){
    
    string fileNameToClean = argv[1];
    string objectNameToRemove = argv[2];
    
    if(boost::filesystem::is_regular_file(fileNameToClean)){
      
      if(fileNameToClean.find(".root") != string::npos){
    
	if (argc == 3) ObjectRemover(fileNameToClean, objectNameToRemove);
	else if(argc == 4) ObjectRemover(fileNameToClean, objectNameToRemove, string(argv[3]));
	
      }
      else cout<<"Error: '"<<fileNameToClean<<"' is not a ROOT file "<<endl;
    
    }
    else cout<<"Error: '"<<fileNameToClean<<"' does not exist "<<endl;
  
  }
  else cout<<"Error: you must provide a ROOT file to clean and the object's name to remove from the file"<<endl;
  return 0;
  
}
