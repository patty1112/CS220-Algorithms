/*
 * trie.h
 *
 * Declaration of the trie class.
 * 
 * Author: <your name here>
 */

#ifndef _TRIE_H
#define _TRIE_H

#include <string>
#include <vector>


using namespace std;

class trie {
    friend class trieNode;
    private:
    struct trieNode {
        trieNode* children[26];
        bool isTerminal;
        trieNode() {
            for(int i = 0; i < 26; i++) {
                children[i] = nullptr;
            }
            isTerminal = false;
        }
        ~trieNode() {
            for(int i = 0; i < 26; i++) {
                delete children[i];
            }
        }
        trieNode* hasChild() {
            trieNode* curr = nullptr;
            for(int i = 0; i < 26; i++) {
                curr = this->children[i];
                if(curr != nullptr) {
                    return curr;
                }
            }
            return curr;
        }
    };
    void extendHelper(trieNode* &root, const string &prefix, vector<string> &result);
    trieNode* root;

    public:
    trie();
    ~trie();
    void insert(const string &s);
    bool contains(const string &s);
    bool is_prefix(const string &s);
    void extend(const string &prefix, vector<string> &result);
    
};

#endif
