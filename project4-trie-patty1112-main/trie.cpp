/*
 * trie.cpp
 *
 * Method definitions for the trie class.
 *
 * Author: Patrick Maes
 */

#include "trie.h"
#include <iostream>
trie::trie() {
    root = new trieNode();
}
trie::~trie() {
    
}
void trie::extendHelper(trieNode* &current, const string &prefix, vector<string> &result) {
    if(current == nullptr) {
        return;
    }
    if(current->isTerminal) {
        result.push_back(prefix);
    }
    for(size_t i = 0; i < 26; i++) {
        extendHelper(current->children[i], prefix + char(i+'a'), result);
    }
}

void trie::insert(const string &s) {
    trieNode* currLocation = root;
    for(size_t i = 0; i < s.size(); i ++) {
        char currentChar = s[i];
        int index = currentChar - 'a';
        if(currLocation->children[index] != nullptr) {
            currLocation = currLocation->children[index];
            if(i == s.size() - 1) {
                currLocation->isTerminal = true;
            }
            continue;
        } else {
            for(size_t j = i; j < s.size(); j++) {
                currentChar = s[j];
                int index = currentChar - 'a';
                currLocation->children[index] = new trieNode;
                currLocation = currLocation->children[index];
                if(j == s.size() - 1) {
                    currLocation->isTerminal = true;
                    return;
                }
            }
            return;
        }
    }
}

bool trie::contains(const string &s) {
    trieNode* currLocation = this->root;
    for(size_t i = 0; i < s.size(); i++) {
        char currentChar = s[i];
        int index = currentChar - 'a';
        if(currLocation->children[index] == nullptr) {
            return false;
        }
        currLocation = currLocation->children[index];
        if(i == (s.size() - 1) && currLocation->isTerminal) {
            return true;
        }
    }
    return false;
}

bool trie::is_prefix(const string &s) {
    trieNode* currLocation = root;
    for(size_t i = 0; i < s.size(); i++) {
        char currentChar = s[i];
        int index = currentChar - 'a';
        if(currLocation->children[index] == nullptr) {
            return false;
        }
        currLocation = currLocation->children[index];
    }
    if(currLocation->isTerminal) {
        return true;
    } else {
        while(currLocation->hasChild() != nullptr) {
            currLocation = currLocation->hasChild();
            if(currLocation->isTerminal) {
                return true;
            }
        }
        return false;
    }
}

void trie::extend(const string &prefix, vector<string> &result) {
    trieNode* currLocation = this->root;
    for(size_t i = 0; i < prefix.size(); i++) {
        char currentChar = prefix[i];
        int index = currentChar - 'a';
        if(currLocation->children[index] == nullptr) {
            return;
        }
        currLocation = currLocation->children[index];
    }
    extendHelper(currLocation, prefix, result);
}
