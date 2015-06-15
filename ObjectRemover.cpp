#include <boost/filesystem.hpp>
#include "Stripper.hpp"

void ObjectRemover(const std::string& fileNameToClean, const std::string& objectNameToRemove, std::string newFileNameSuffix = "_stripped"){

  TFile fileToClean(fileNameToClean.c_str());
  Stripper stripper(fileToClean, objectNameToRemove);//create the Stripper object with the file to clean and the item to look for
  std::cout<<stripper<<std::endl;
  stripper.strip();
  stripper.save((fileNameToClean+newFileNameSuffix).c_str());//create a new filename with an extra extension
  
  std::cout<<"Saved the stripped file as '"<<fileNameToClean+newFileNameSuffix<<"'"<<std::endl;
  
}

int main (int argc, char* argv[]){
  
  if(argc > 2){
    
    std::string fileNameToClean = argv[1];
    std::string objectNameToRemove = argv[2];
    
    if(boost::filesystem::is_regular_file(fileNameToClean)){
      
      if(fileNameToClean.find(".root") != std::string::npos){
    
	if (argc == 3) ObjectRemover(fileNameToClean, objectNameToRemove);
	else if(argc == 4) ObjectRemover(fileNameToClean, objectNameToRemove, std::string(argv[3]));
	
      }
      else std::cout<<"Error: '"<<fileNameToClean<<"' is not a ROOT file "<<std::endl;
    
    }
    else std::cout<<"Error: '"<<fileNameToClean<<"' does not exist "<<std::endl;
  
  }
  else std::cout<<"Error: you must provide a ROOT file to clean and the object's name to remove from the file"<<std::endl;
  return 0;
  
}
