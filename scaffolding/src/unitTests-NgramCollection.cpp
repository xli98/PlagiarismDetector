/*
 * Unit test cases for NgramCollection class.
 *
 * TODO: some test cases have been provided, but you will need
 * to write your own for the remaining functions
 *
 * While you should definitely add lots more code, try not to remove
 * or modify any of the test cases we've provided
 */

#include "../include/catch.hpp" // simple unit-testing framework
#include "../include/NgramCollection.hpp" // header declaring the functions we want to test

#include <iostream>
#include <string>
#include <vector>
#include <list>

using std::string;
using std::vector;
using std::list;

/* test getN, should be pretty easy
 */
TEST_CASE("getN", "[getN]") {
  NgramCollection g3(3);
  NgramCollection g4(4);
  REQUIRE(g3.getN() == 3);
  REQUIRE(g4.getN() == 4);
}


/*these test cases tests whether I can read in files*/
TEST_CASE("empty model", "getsize"){
  NgramCollection g3(3);
  NgramCollection g4(4);
  REQUIRE(g3.getsize() == 0);
  REQUIRE(g4.getsize() == 0);
}

/* test toString on an empty collection
 */
TEST_CASE("toString when empty", "[toString]") {
  NgramCollection g3(3);
  REQUIRE(g3.toString() == "");
  REQUIRE(g3.toString("a") == "");
  REQUIRE(g3.toString("r") == "");
  REQUIRE(g3.toString("c") == "");

  NgramCollection g4(4);
  REQUIRE(g4.toString() == "");
  REQUIRE(g4.toString("a") == "");
  REQUIRE(g4.toString("r") == "");
  REQUIRE(g4.toString("c") == "");

}

/* test both toString and increment (since toString is the easiest way
 * of checking whether increment worked).  You may want extra
 * test-cases for each of the two separately.
 */
TEST_CASE("toString after increment", "[toString],[increment]") {
  NgramCollection g3(3);

  vector<string> v;
  v.push_back("Four");
  v.push_back("score");
  v.push_back("and");
  v.push_back("seven");
  
  g3.increment(v.begin(), v.end()-1);
  REQUIRE(g3.toString() == "Four score and 1\n");

  g3.increment(v.begin()+1, v.end());
  REQUIRE(g3.toString() == "Four score and 1\nscore and seven 1\n");

  g3.increment(v.begin(), v.end()-1);
  REQUIRE(g3.toString() == "Four score and 2\nscore and seven 1\n");  

  g3.increment(v.begin()+1, v.end());
  g3.increment(v.begin()+1, v.end());
  REQUIRE(g3.toString() == "Four score and 2\nscore and seven 3\n");
}

TEST_CASE("toString after increment of length2", "[toString],[increment]") {
  NgramCollection g2(2);

  vector<string> v;
  v.push_back("Four");
  v.push_back("score");
  v.push_back("and");
  v.push_back("seven");

  g2.increment(v.begin(), v.end()-2);
  REQUIRE(g2.toString() == "Four score 1\n");

  g2.increment(v.begin()+1, v.end()-1);
  REQUIRE(g2.toString() == "Four score 1\nscore and 1\n");

  g2.increment(v.begin()+2, v.end());
  REQUIRE(g2.toString() == "Four score 1\nand seven 1\nscore and 1\n");

  g2.increment(v.begin()+1, v.end()-1);
  g2.increment(v.begin()+1, v.end()-1);
  REQUIRE(g2.toString() == "Four score 1\nand seven 1\nscore and 3\n");

}

TEST_CASE("toString in order", "[toString], [toString a, c, r]"){
  NgramCollection g2(2);

  vector<string> v;
  v.push_back("Four");
  v.push_back("score");
  v.push_back("and");
  v.push_back("seven");

  g2.increment(v.begin(), v.end()-2);
  g2.increment(v.begin()+1, v.end()-1);
  g2.increment(v.begin()+2, v.end());
  g2.increment(v.begin()+1, v.end()-1);
  g2.increment(v.begin()+1, v.end()-1);

  REQUIRE(g2.toString() == "Four score 1\nand seven 1\nscore and 3\n");
  REQUIRE(g2.toString("a") == "Four score 1\nand seven 1\nscore and 3\n");
  REQUIRE(g2.toString("r") == "score and 3\nand seven 1\nFour score 1\n");


  g2.increment(v.begin(), v.end()-2);
  g2.increment(v.begin(), v.end()-2);
  g2.increment(v.begin(), v.end()-2);
  REQUIRE(g2.toString("c") =="and seven 1\nscore and 3\nFour score 4\n");
}


/* test pickWord when there's only one possible next word,
 * N=3
 */
TEST_CASE("pickWord three-grams when only one valid choice", "[pickWord]") {
  NgramCollection g3(3);
  vector<string> text;
  text.push_back("I");
  text.push_back("have");
  text.push_back("a");
  text.push_back("dream");
  text.push_back("that");
  text.push_back("one");
  text.push_back("day");
  
  g3.increment(text.begin(), text.end()-4); //adds "I, have, a"
  g3.increment(text.begin()+1, text.end()-3); //adds "have, a, dream"
  g3.increment(text.begin()+2, text.end()-2); //adds "a, dream, that"
  g3.increment(text.begin()+3, text.end()-1); //adds "dream, that, one"
  g3.increment(text.begin(), text.end()-4); //adds "I, have, a" AGAIN
  
  vector<string> wordsToFollow;
  wordsToFollow.push_back("I");
  wordsToFollow.push_back("have");
  wordsToFollow.push_back("a");

  vector<string>::iterator begin_list = wordsToFollow.begin();
  vector<string>::iterator end_list = begin_list;  //now points to "I"
  end_list = std::next(end_list);
  end_list = std::next(end_list);  //now points to "a"
  REQUIRE(g3.pickWord(begin_list, end_list) == "a");

  begin_list++; //now points to "have"
  end_list = std::next(end_list); //now points to "dream"
  REQUIRE(g3.pickWord(begin_list, end_list) == "dream");

}


/* test pickWord when there's only one possible next word,
 * N=4
 */
TEST_CASE("pickWord four-grams when only one valid choice", "[pickWord]") {

  NgramCollection g4(4);

  vector<string> text;
  text.push_back("I");
  text.push_back("have");
  text.push_back("a");
  text.push_back("dream");
  text.push_back("that");
  text.push_back("one");
  text.push_back("day");
  
  g4.increment(text.begin(), text.end()-3); //adds "I, have, a, dream"
  g4.increment(text.begin()+1, text.end()-2); //adds "have, a, dream, that"
  g4.increment(text.begin()+2, text.end()-1); //adds "a, dream, that one"
  g4.increment(text.begin()+3, text.end()); //adds "dream, that, one, day"
  g4.increment(text.begin(), text.end()-3); //adds "I, have, a, dream" AGAIN
  
  vector<string> wordsToFollow;
  wordsToFollow.push_back("I");
  wordsToFollow.push_back("have");
  wordsToFollow.push_back("a");
  wordsToFollow.push_back("dream");
  wordsToFollow.push_back("that");
  wordsToFollow.push_back("one");
	       

  vector<string>::iterator begin_list = wordsToFollow.begin();
  vector<string>::iterator end_list = begin_list;  //now points to "I"
  end_list = std::next(end_list);
  end_list = std::next(end_list);
  end_list = std::next(end_list);  //now points to "dream"
  REQUIRE(g4.pickWord(begin_list, end_list) == "dream");

  begin_list++; //now points to "have"
  end_list = std::next(end_list); //now points to "that"
  REQUIRE(g4.pickWord(begin_list, end_list) == "that");

}


/* test pickWord with more than one choice, be sure
 * we're getting them with the right likelihood
 */
TEST_CASE("pickWord with some options", "[pickWord]") {

  //First set up g3 to contain:
  //  "believe, you, can" with a count of 1
  //  "believe, you, will" with a count of 3
  NgramCollection g3(3);
  vector<string> text;
  text.push_back("believe");
  text.push_back("you");
  text.push_back("can");  
  g3.increment(text.begin(), text.end());

  text[2] = "will";
  g3.increment(text.begin(), text.end());
  g3.increment(text.begin(), text.end());
  g3.increment(text.begin(), text.end());


  //Use pickWord to generate numerous words to follow "believe, you"
  //and count up how many times "can" and "will" occur
  vector<string> wordsToFollow;
  wordsToFollow.push_back("believe");
  wordsToFollow.push_back("you");
  vector<string>::iterator begin_list = wordsToFollow.begin();
  vector<string>::iterator end_list = wordsToFollow.end();

  unsigned int numTrials = 10000;
  unsigned int can = 0;
  unsigned int will = 0;
  for (unsigned int i = 0; i < numTrials; i++) {
    string result = g3.pickWord(begin_list, end_list);
    if (result == "can") {
      can++;
    }
    else if (result == "will") {
      will++;
    }
  }

  // Uncomment to see what's going on if you're having trouble passing this test
  
  std::cout << "model: " << g3.toString() << "\n";
  std::cout << "can = " << can << ", will = " << will << "\n";
  

  REQUIRE((will / (double) numTrials) == Approx(0.5).epsilon(0.03));
  REQUIRE((can / (double) numTrials) == Approx(0.5).epsilon(0.03));

}
