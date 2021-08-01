#pragma once
#include <string>
#include <iostream>;
#include <vector>
using namespace std;

class SlangTree { //The main SlangTree class
public:
    struct TreeNode { //The TreeNode subclass
        string word; //variable for the slang word
        string def; //variable for the slang definition
        float upVote; //variables for the amount of upvotes a slang word has
        float downVote; //variables for the amount of downvotes a slang word has
        TreeNode* left; //The left node of the tree
        TreeNode* right; //The right node of the tree
        TreeNode() : word(""), def(""), upVote(0.0), downVote(0.0), left(NULL), right(NULL) {} //the default constructor for a node in the tree
        TreeNode(string w, string d, float uv, float dv) : word(w), def(d), upVote(uv), downVote(dv), left(NULL), right(NULL) {} //the constructor of a new node in the tree

    };

    void findDef(TreeNode* root, string word, bool& res, string& def);
    void findRatio(TreeNode* root, string word, bool& res, float& ratio);

    TreeNode* insertSlang(TreeNode* root, string word, string def, float upVotes, float downVotes);

    void findTrending(TreeNode* root, vector<string>& trendingWords);
};

void SlangTree::findTrending(TreeNode* root, vector<string>& trendingWordsTree) { //finds all the words that have a higher ratio of upvotes than downvotes and puts them 
    if (root == NULL) {
        return;
    }
    else {
        if (root->upVote / root->downVote > 40.0) {
            trendingWordsTree.push_back(root->word);
        }
        findTrending(root->left, trendingWordsTree);
        findTrending(root->right, trendingWordsTree);
    }
}

SlangTree::TreeNode* SlangTree::insertSlang(TreeNode* root, string word, string def, float upVotes, float downVotes) { //inserts the word, definition, up-votes and down-votes into the tree and then balances the tree automatically using the rotate functions
    if (root == NULL) { //inserts a new node if the tree is currently empty
        return new TreeNode(word, def, upVotes, downVotes);
    }
    else { //inserts a node in the correct location that satisfies the BST constraints
        if (word < root->word) {
            root->left = insertSlang(root->left, word, def, upVotes, downVotes);
        }
        else if (word > root->word) {
            root->right = insertSlang(root->right, word, def, upVotes, downVotes);
        }
        else {
            return root;
        }
    }
    return root;
}

void SlangTree::findDef(TreeNode* root, string word, bool& res, string& def) { //this traverses through the loop for the matching word and then prints out the definition associated with the word

    if (root == NULL) {
        return;
    }
    else {
        if (root->word == word) { //if the word matches, it prints out the name and makes result variable true
            def = root->def;
            res = true;
        }
    }
    findDef(root->left, word, res, def); //searches the left subtree
    findDef(root->right, word, res, def); //searches the right subtree
}

void SlangTree::findRatio(TreeNode* root, string word, bool& res, float& ratio) { //this traverses through the loop for the matching word and then prints out the ratio of upvotes and downvotes associated with the word

    if (root == NULL) {
        return;
    }
    else {
        if (root->word == word) { //if the word matches, it prints out the name and makes result variable true
            ratio = (root->upVote) / (root->downVote);
            res = true;
        }
    }
    findRatio(root->left, word, res, ratio); //searches the left subtree
    findRatio(root->right, word, res, ratio); //searches the right subtree
}