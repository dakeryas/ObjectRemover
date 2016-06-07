#include "boost/filesystem.hpp"
#include "boost/program_options.hpp"
#include "Stripper.hpp"

namespace bpo = boost::program_options;

void ObjectRemover(const std::string& fileNameToClean, const std::string& objectNameToRemove, std::string newFileNameSuffix){

  TFile fileToClean(fileNameToClean.c_str());
  Stripper stripper(fileToClean, objectNameToRemove);//create the Stripper object with the file to clean and the item to look for
  std::cout<<stripper<<std::endl;
  stripper.strip();
  stripper.save((fileNameToClean+newFileNameSuffix).c_str());//create a new filename with an extra extension
  
  std::cout<<"Saved the stripped file as '"<<fileNameToClean+newFileNameSuffix<<"'"<<std::endl;
  
}

int main (int argc, char* argv[]){
  
  std::string fileNameToClean;
  std::string objectNameToRemove;
  std::string newFileNameSuffix;
  
  bpo::options_description optionDescription("Object Remover usage");
  optionDescription.add_options()
  ("help,h", "Display this help message")
  ("target,t", bpo::value<std::string>(&fileNameToClean)->required(), "File to clean")
  ("remove,r", bpo::value<std::string>(&objectNameToRemove)->required(), "Object name to remove")
  ("extension,e", bpo::value<std::string>(&newFileNameSuffix)->default_value("_stripped") ,"New extension for the output file");

  bpo::positional_options_description positionalOptions;//to use arguments without "--"
  positionalOptions.add("target", -1);
  
  bpo::variables_map arguments;
  try{
    
    bpo::store(bpo::command_line_parser(argc, argv).options(optionDescription).positional(positionalOptions).run(), arguments);
    
    if(arguments.count("help") || argc == 1){
      
      std::cout<<optionDescription<<std::endl;
      return 0;
      
    }
      
    bpo::notify(arguments);//the arguments are ready to be used
    
  }
  catch(bpo::error& e){
    
    std::cout<<e.what()<<std::endl;
    return 1;
    
  }

  if(boost::filesystem::is_regular_file(fileNameToClean)){
    
    if(fileNameToClean.find(".root") != std::string::npos) ObjectRemover(fileNameToClean, objectNameToRemove, newFileNameSuffix);
    else std::cout<<"Error: '"<<fileNameToClean<<"' is not a ROOT file "<<std::endl;
  
  }
  else std::cout<<"Error: '"<<fileNameToClean<<"' does not exist "<<std::endl;

  return 0;
  
}
