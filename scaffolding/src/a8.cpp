#include "LanguageModel.hpp"
#include <iostream>
#include <string>
using std::string; 

int main(int argc, char* argv[]){
  /*if has too few command-line inputs, return error*/
  if(argc < 4 || argc >5){
    std::cerr << "Incorrct number of command line arguments supplied. \n";
    return 1;
  }

  /*stores the comman-line variables for future use*/
  string files = argv[1];
  int ngram = atoi(argv[2]);
  string ord = argv[3];
  
  int output = 0;

  /*create instance of Ngram to call function with*/
  LanguageModel model(ngram);

  /*if there are the g command, get the number of files to generate*/
  if(argc == 5){
    output = atoi(argv[4]);
  }

  /*read text file into a model*/
  model.readinfile(files);

  /*call functions on given commands*/
  if(ord.compare("g") == 0){
    if(output == 0){
      std::cerr << "Does not have the number of time to generate line based on model. \n";
    }
    for(int i = 0; i < output; i++){
      model.generate();
    }
  }else{
    string tostring = model.getCollection().toString(ord);
    std::cout << tostring;
  }
  return 0;
  
}
