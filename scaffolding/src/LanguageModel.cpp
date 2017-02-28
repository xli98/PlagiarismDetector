#include "../include/LanguageModel.hpp"
#include <iostream>
#include <fstream>
using std::fstream;
using std::ifstream;
using std::vector;
using std::string;
using std::map;
using std::pair;
using std::list;


void LanguageModel :: makemodel(string filename){
  /*if file doesn't open correctly, throw error*/
  ifstream infile;
  infile.open(filename);
  if (!infile.is_open()) {
    std::cerr << "File name provided does not exist!\n";
    exit(1);
  }

  
  vector<string > key;
  string word1;
  /*start filling in the map before first word*/
  for(unsigned i = 1; i < model.getN(); i++){
    string temp = "<START_" + std::to_string(i) + ">";
    key.push_back(temp);
  }


  /*treats the first word of file independently(deals with one word file)*/
  if(infile >> word1){
    key.push_back(word1);
  }else{
    std::cerr << "No input, try again. \n";
    exit(1);
  }
  
  vector<string>::const_iterator begin = key.begin();
  vector<string>::const_iterator end = key.end();
  model.increment(begin, end);//increment the map with wordcount or new answer

  /*keep incrementing map until reach the last word*/
  while(infile >> word1){
    key.erase(key.begin());
    key.push_back(word1);

    model.increment(begin, end);

  }

  /*deal with the different numbers of endings after the last word was read in*/
  for(unsigned i = 1; i < model.getN(); i++){
    key.erase(key.begin());
    
    string temp = "<END_" + std::to_string(i) + ">";

    key.push_back(temp);
    model.increment(begin, end);
    word1 = temp;
  }

  infile.close();
  
}


/*read the file containing inputnames one by one*/
void LanguageModel :: readinfile(string str){
  ifstream infile;
  infile.open(str);
  if (!infile.is_open()) {
    std::cerr << "Failed to open file!\n";
    exit(1);
  }

  /*while there are still input to read, treat the input*/
  string filename;
  while(infile >> filename){
    makemodel(filename);
  }
  
  infile.close();
}

/*function to generate new texts based on the model given*/
void LanguageModel :: generate(){

  /*the first starting key to get the first word*/
  vector<string > key;
  for(unsigned i = 1; i < model.getN(); i++){
    string temp = "<START_" + std::to_string(i) + ">";
    key.push_back(temp);
    std::cout << temp << " "; 
  }

  /*get the first word*/
  vector<string>::const_iterator begin = key.begin();
  vector<string>::const_iterator end = key.end();
  string temp = model.pickWord(begin, end);
  std::cout << temp << " ";


  
  string lastword = "<END_" + std::to_string(model.getN()-1) + ">";


  /*keep on getting next words until we read the <END_N>*/
  while(temp.compare(lastword) != 0){

    key.erase(key.begin());
    key.push_back(temp);
    
    temp = model.pickWord(begin, end);
    std::cout << temp << " ";
  }

  std::cout << "\n"; 
  
}
