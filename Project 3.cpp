#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "SlangTree.h"
#include "SlangMap.h"
#include <chrono>
using namespace std;
using namespace std::chrono;

int main()
{

    //variables that we will pull from excel
    string word, def, line, uv, dv, trash;
    vector<string> words, defs;
    vector<float> uvs, dvs;

    int upVote, downVote, com;

    //Initializations of the two data structures: tree and map.

    SlangTree slangTree;
    SlangTree::TreeNode* tree = NULL;

    SlangMap slangMap;

    ifstream inFS;
    inFS.open("Urban Dictionary.csv");

    getline(inFS, trash);

    auto startVector = high_resolution_clock::now();

    int n = 1;
    /*================READING CSV FILE AND INPUTTING DATA INTO DATA STRUCTURES================*/
    while (!inFS.eof() && inFS.good() && n < 128410)
    {
        //line will contain the entire line...be sure to cut up into word, upvote, downvote, and definition
        getline(inFS, line);

        //get word
        com = line.find(',');
        word = line.substr(0, com);

        //get upvote
        line = line.substr(com + 1, line.size() - (word.size() + 1));
        com = line.find(',');
        uv = line.substr(0, com);

        //get downvote
        line = line.substr(com + 1, line.size() - (uv.size() + 1));
        com = line.find(',');
        dv = line.substr(0, com);

        //get defitinition
        def = line.substr(com + 1, line.size() - (dv.size() + 1));
        //def = def.substr(0, def.size() - 9);                          

        //add variable to respective vector
        words.push_back(word);
        defs.push_back(def);
        uvs.push_back(stof(uv));
        dvs.push_back(stof(dv));
        n++;
    }
     
    //important to close file!!
    inFS.close();

    auto stopVector = high_resolution_clock::now();
    auto durationVector = duration_cast<seconds>(stopVector - startVector);
    cout << "Time taken to read csv and input into vectors: " << durationVector.count() << " seconds" << endl;

    auto startTreeInsert = high_resolution_clock::now();
    for (int i = 0; i < words.size(); i++) {
        tree = slangTree.insertSlang(tree, words[i], defs[i], uvs[i], dvs[i]);
    }
    auto stopTreeInsert = high_resolution_clock::now();
    auto durationTreeInsert = duration_cast<seconds>(stopTreeInsert - startTreeInsert);
    cout << "Time taken to input vectors into Binary Search Tree: " << durationTreeInsert.count() << " seconds" << endl;

    auto startMapInsert = high_resolution_clock::now();
    for (int j = 0; j < words.size(); j++) {
        //cout << words[j] << endl;
        slangMap.insertSlang(words[j], defs[j], uvs[j], dvs[j]);
    }
    auto stopMapInsert = high_resolution_clock::now();
    auto durationMapInsert = duration_cast<seconds>(stopMapInsert - startMapInsert);
    cout << "Time taken to input vectors into Hash Map: " << durationMapInsert.count() << " seconds" << endl;
    cout << endl;

    /*================GETTING USER INPUT AND RUNNING RESPECTIVE FUNCTIONS================*/

    cout << "WELCOME TO THE GEN Z DICTIONARY" << endl;
    cout << "===============================" << endl;
    cout << "Please select an option from the menu below:" << endl;
    cout << "1. Look up the definition of a word" << endl;
    cout << "2. Show the popularity of a word" << endl;
    cout << "3. Display the top trending words" << endl;
    cout << "4. Quit" << endl;
    cout << "===============================" << endl;
    bool end = false;
    string option;

    //keep prompting user until they choose menu option 4
    while (!end)
    {
        cout << "Please choose from the menu: ";
        cin >> option;
        if (option == "1" || option == "2" || option == "3" || option == "4")
        {
            if (option == "1")    //user wishes to look up the definition of a word
            {
                cout << endl << "Please type the word you would like to look the definition for: ";
                string word;
                bool res = false;
                string def = "";
                cin.ignore();
                getline(cin, word);

                //Binary Search Tree
                auto startTreeDef = high_resolution_clock::now();
                slangTree.findDef(tree, word, res, def);
                auto stopTreeDef = high_resolution_clock::now();
                auto durationTreeDef = duration_cast<nanoseconds>(stopTreeDef - startTreeDef);

                cout << endl << "According to the Binary Search Tree:" << endl;
                if (res) {
                    cout << "The definition of " << word << " is: " << def << endl;
                    
                } else {
                    cout << "That word isn't even on the list! Never ever say it..." << endl;
                }
                cout << "Time taken to find the definition of the word: " << durationTreeDef.count() << " nanoseconds" << endl;

                //Hash Map
                auto startMapDef = high_resolution_clock::now();
                def = slangMap.findDef(word);
                auto stopMapDef = high_resolution_clock::now();
                auto durationMapDef = duration_cast<nanoseconds>(stopMapDef - startMapDef);

                cout << endl << "According to the Hash Map:" << endl;
                if (def != "-1") {
                    cout << "The definition of " << word << " is: " << def << endl;

                }
                else {
                    cout << "That word isn't even on the list! Never ever say it..." << endl;
                }
                cout << "Time taken to find the definition of the word: " << durationMapDef.count() << " nanoseconds" << endl;
                cout << endl;

            }
            if (option == "2")    //user wishes to know the popularity of a certain word
            {
                //ranking of coolness
                cout << "..................................." << endl;
                cout << "| Cool Factor | What it Means     |" << endl;
                cout << "..................................." << endl;
                cout << "| 20+         | Super Duper Cool! |" << endl;
                cout << "-----------------------------------" << endl;
                cout << "| 15-19       | Quite Cool.       |" << endl;
                cout << "-----------------------------------" << endl;
                cout << "| 8-14        | Kind of Cool...   |" << endl;
                cout << "-----------------------------------" << endl;
                cout << "| 0-8         | Not Cool at All!  |" << endl;
                cout << "..................................." << endl;
                cout << endl << "Please type the word you would like to know the popularity of: ";
                
                string word;
                bool res = false;
                float ratio = 0.0;
                cin.ignore();
                getline(cin, word);

                auto startTreeRatio = high_resolution_clock::now();
                slangTree.findRatio(tree, word, res, ratio);
                auto stopTreeRatio = high_resolution_clock::now();
                auto durationTreeRatio = duration_cast<nanoseconds>(stopTreeRatio - startTreeRatio);

                cout << endl << "According to the Binary Search Tree: ";
                if (res) {
                    cout << "The popularity of " << word << " is: " << ratio << endl;
                } else {
                    cout << "That word isn't even on the list! Never ever say it..." << endl;
                }
                cout << "Time taken to find the popularity of the word: " << durationTreeRatio.count() << " nanoseconds" << endl;

                auto startMapRatio = high_resolution_clock::now();
                ratio = slangMap.findRatio(word);
                auto stopMapRatio = high_resolution_clock::now();
                auto durationMapRatio = duration_cast<nanoseconds>(stopMapRatio - startMapRatio);

                cout << endl << "According to the Hash Map: ";
                if (ratio != -1) {
                    cout << "The popularity of " << word << " is: " << ratio << endl;
                }
                else {
                    cout << "That word isn't even on the list! Never ever say it..." << endl;
                }
                cout << "Time taken to find the popularity of the word: " << durationMapRatio.count() << " nanoseconds" << endl;
                cout << endl;

            }
            if (option == "3")
            {
                cout << endl << "The most popular words (coolness factor above 40.0): " << endl;
                
                vector<string> trendingWordsTree;
                vector<string> trendingWordsMap;
                bool res = false;
                float ratio = 0.0;

                auto startTreeTrend = high_resolution_clock::now();
                slangTree.findTrending(tree, trendingWordsTree);
                cout << endl << "According to the Binary Search Tree:" << endl;
                for (int i = 0; i < trendingWordsTree.size(); i++) {
                    cout << trendingWordsTree[i] << " (";
                    slangTree.findRatio(tree, trendingWordsTree[i], res, ratio);
                    cout << ratio << ")" << endl;
                }
                auto stopTreeTrend = high_resolution_clock::now();
                auto durationTreeTrend = duration_cast<nanoseconds>(stopTreeTrend - startTreeTrend);
                cout << "Time taken to find the trending words: " << durationTreeTrend.count() << " nanoseconds" << endl;

                auto startMapTrend = high_resolution_clock::now();
                slangMap.findTrending(trendingWordsMap);
                cout << endl << "According to the Hash Map:" << endl;
                for (int i = 0; i < trendingWordsMap.size(); i++) {
                    cout << trendingWordsMap[i] << " (";
                    cout << slangMap.findRatio(trendingWordsMap[i]) << ")" << endl;
                }
                auto stopMapTrend = high_resolution_clock::now();
                auto durationMapTrend = duration_cast<nanoseconds>(stopMapTrend - startMapTrend);
                cout << "Time taken to find the trending words: " << durationMapTrend.count() << " nanoseconds" << endl;
                cout << endl;

            }
            if (option == "4")
            {
                cout << endl << "Thank you for using the Gen Z Dictionary" << endl;
                end = true;
            }
            //at the end of doing what the user requested, ask what they would like to do next.
            //they can choose from the menu again
        }
        else
        {
            cout << endl << "Error: Please enter a valid integer for a menu option" << endl;
            cout << endl;
        }
        cout << "===============================" << endl;
    }
    return 0;
}

