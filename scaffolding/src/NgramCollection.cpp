#include "../include/NgramCollection.hpp"
#include <iostream>
#include <utility>
#include <algorithm>

using std::vector;
using std::string;
using std::map;
using std::pair;
using std::list;
using std::sort;

bool sortbyval(const pair<string, int>  &p1, const pair<string, int> &p2);

/*main function to turn model into a string to be printed*/
string NgramCollection::toString(string ord) const{

  /*test for different cases and the case that input are not correct*/
  string tostring;
  if(ord.compare("a") == 0){
    tostring = toStringAlpha();
    
  }else if(ord.compare("r") == 0){
    tostring = toStringReverseAlpha();

  }else if(ord.compare("c")  == 0){
    tostring = toStringCount();

  }else if(ord.compare("g") == 0){
    
  }else{
    std::cerr << "Incorrect printing command, try again with \"a,\" \"r\" or \"c\". \n";
  }
  
  return tostring;
  
}

/*helper function to toString(), print in alphabetacal order*/
string NgramCollection::toStringAlpha() const{

  /*loops through the map for every single key/answer*/
  string totalout;
  for (auto iter1 = this->counts.begin();
       iter1 != this->counts.end();
       iter1++){
    string outbyline;

    string temp; 

    /*loops through all the keys for the model map*/
    for( unsigned i = 0; i < (iter1->first).size(); i++){
      temp += (iter1->first)[i] + " ";
    }
    for (auto iter2 = (iter1->second).begin();
	 iter2 != (iter1->second).end();
	 iter2++){
      /*updates the individual combinations with their apprearance*/
      outbyline += temp + (iter2->first) + " " + std::to_string(iter2->second) + "\n"; 
    }

    totalout += outbyline; 
  }
  return totalout; 
}


/*helper function to toString(), print in reverse alphabetacal order*/
string NgramCollection::toStringReverseAlpha() const{
  
  /*loops through the map for every single key/answer in reverse orders*/
  string totalout;
  for (auto iter1 = this->counts.rbegin();
       iter1 != this->counts.rend();
       iter1++){
    string outbyline;

    string temp; 
    /*loops through all the keys for the model map*/
    for( unsigned i = 0; i < (iter1->first).size(); i++){
      temp += (iter1->first)[i] + " ";
    }
    for (auto iter2 = (iter1->second).begin();
	 iter2 != (iter1->second).end();
	 iter2++){
      /*updates the individual combinations with their apprearance*/
      outbyline += temp + (iter2->first) + " " + std::to_string(iter2->second) + "\n";
      
    }

    totalout += outbyline;
  }

  return totalout;
  

  
}
/*helper function to toString(), print in order by count*/
string NgramCollection::toStringCount() const{
  string out;

  /*flattens the map out into a vector of pairs, 
   *with all the words as one string and count associated with it*/
  vector<pair<string,int> > v;
  for(auto iter = this->counts.begin();
      iter != this->counts.end();
      iter++){

    /*deals with the key part of the Ngram vector<string>*/
    string str;
    for(auto iterS = iter->first.begin();
	iterS != iter->first.end();
	iterS++){
      str += *iterS + " ";
    }

    /*deal with the inner map, adding word to string first then saving int for the vector*/
    for(auto iter2 = iter->second.begin();
	iter2 != iter->second.end();
	iter2++){
      string temp = iter2->first + " ";
      temp = str + temp;
      std::pair<string, int> p = {temp, iter2->second};
      v.push_back(p);
    }

  }
  
  /*sorts the vector now by count according to self generated sort algorithm*/
  std::sort(v.begin(), v.end(), sortbyval);
  
  for (auto iter = v.begin();
       iter != v.end();
       iter++){
      out += (iter->first) + std::to_string(iter->second) +"\n";
  }
  
  return out; 
}

/*helper function that increments map model whenever the same word sequence appears*/
void NgramCollection::increment(std::vector<std::string>::const_iterator begin,
				std::vector<std::string>::const_iterator end){


  /*pass in all N words, keys and answer included*/
  unsigned num = 0;
  vector<string> key;
  for(auto iter = begin; iter!= end; iter++){
    if(num == n-1){
      if(counts.count(key)){
	if(counts.at(key).count(*iter)){

	  /*if the sequence of words already exist, increment the count*/
	  counts.at(key).at(*iter)++;
	}else{
	  /*if the sequence(last word) didn't exist, update inner map*/
	  counts.at(key).insert(std::pair<string, unsigned>(*iter, 1u));
	}
	
      }else{
	/*if sequence didn't exist at all, update outer map*/
	counts[key] = {{*iter, 1u}};
      }
    }

    if(num < (this->n)-1){
      key.push_back(*iter);
      num++;
    }
    
  }
}


/*helper function that defines the order that                                             
 *the sort algorithm in printcorder() uses*/
bool sortbyval(const pair<string, int>  &p1, const pair<string, int> &p2){
  if(p1.second < p2.second){ //purely compares the frequencies of the wordpairs
    return 1;
  }else if(p1.second == p2.second){//if the frequency is equal, compare the words in alphabeta order
      if(p1.first < p2.first){
	return 1;
      }else{
	return 0;
      }
  }else{
    return 0;
  }
}


/*helper function to generate sentence according to model*/
string NgramCollection::pickWord(std::vector<std::string>::const_iterator begin,
				 std::vector<std::string>::const_iterator end) const{

  
  string chosen;
  int total = 0;
  vector<string> key;

  /*if for some reasons the model is empty, throw error*/
  if(getsize() == 0){
    std::cerr << "Have not read in file, try again. \n";
    exit(1);
  }
  
  for(auto iter = begin; iter != end; iter++){
    key.push_back(*iter);
  }

  map<string, unsigned > answer; 
  /*local copy of inner map that map to the outer key/word sequence*/
  for(auto iter = this->counts.begin(); iter!= this->counts.end(); iter++){
      if(counts.count(key)){
	answer = this->counts.at(key);
      }
  }

  /*collect all the possibility of ouputs following the sequence */
  for(auto iterm = answer.begin();
      iterm != answer.end();
      iterm++){
    total += iterm->second;
  }

  /*get random number for next word*/
  unsigned i = (unsigned)(rand() % total);
  unsigned cur = 0;
  for(auto iterm = answer.begin();
      iterm != answer.end();
      iterm++){

    /*get random next word by going in sequence and keeping wordcount*/
    cur += iterm->second;
    if(cur >= i){
      chosen = iterm->first;
      return chosen; 
    }

  }
  
  
  return chosen;
}
