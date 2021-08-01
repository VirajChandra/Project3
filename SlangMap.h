#include <string>
#include <vector>
#include <iostream>

using namespace std;

class SlangMap { //main map class
public:
	struct Word { //struct of word which stores all the data read from the csv file
		string wStr;
		string def;
		float upVote;
		float downVote;
		Word() : wStr(""), def(""), upVote(0.0), downVote(0.0) {}
		Word(string w, string d, float uv, float dv) : wStr(w), def(d), upVote(uv), downVote(dv) {}
	};

	vector<Word*>* dictionary; //vector of struct type which will further store the words as a linked list
	SlangMap(); 

	void insertSlang(string word, string Def, float UV, float DV); 
	int hashFunc(string w); 
	string findDef(string w); //
	float findRatio(string w);
	void findTrending(vector<string>& trendingWords);

};

SlangMap::SlangMap() { //constructor
	dictionary = new vector<Word*>[28];
}

int SlangMap::hashFunc(string w) { //hash function to find suitable index
	int temp = int(w.at(0));
	if (temp >= 65 && temp <= 90) //if uppercase, set accordingly
		return temp - 64;
	else if (temp >= 97 && temp <= 122) //if lowercase, set accordingly
		return temp - 96;
	else
		return 27; //if char other than letters, store in a separate index
}

void SlangMap::insertSlang(string word, string Def, float UV, float DV) { //fucntion to insert data in the dictionary
	int i = hashFunc(word); //call the hash function

	Word* temp = new Word(word, Def, UV, DV); //create a new struct and set the values

	dictionary[i].push_back(temp); //push the word struct at appropriate index
}

string SlangMap::findDef(string w) { //Search the definition of a word
	int j = hashFunc(w);

	for (auto itr : dictionary[j]) { //for each loop to iterate 
		if (itr->wStr == w) {
			return itr->def;
		}
	}

	return "-1";
}

float SlangMap::findRatio(string w) { //returns the ratio 
	int j = hashFunc(w);

	for (auto itr : dictionary[j]) { //loop to iterate at a particular index
		if (itr->wStr == w) {
			return (itr->upVote / itr->downVote);
		}
	}

	return -1;
}

void SlangMap::findTrending(vector<string>& trendingWordsMap) { //FInd the top words as per the votes
	for (int i = 0; i < 27; i++) { //iterates through the indices
		for (auto itr : dictionary[i]) { //iterates through the words at a given index
			if ((itr->upVote / itr->downVote) > 40.0) {
				trendingWordsMap.push_back(itr->wStr);
			}
		}
	}
}



