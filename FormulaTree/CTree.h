#pragma once

#include <iostream>
#include <map>
#include <set>
using namespace std;

class CNode;

class CTree {
    static int i_copyCount;
private:
    CNode* root;

    CNode* parseNode(const string& expression, size_t& offset);

public:
    CNode* copyTree(const CNode* source);
    void deleteTree(CNode* node);
    CTree();
    CTree(const CTree& c_tree) {
        //cout << "Copy constructor " << ++i_copyCount << endl;
        cout << "Copy constructor " << endl;
    };

    CTree(const CTree&& c_tree) {
        //cout << "Move constructor " << ++i_copyCount << endl;
        cout << "Move constructor " << endl;
    };

    ~CTree();

    CNode* getRoot() const;

    CTree& operator=(const CTree& other);
    CTree operator=(CTree&& other) {
        //cout << "Move operator= " << ++i_copyCount << endl;
        cout << "Move operator= " << endl;
        root = other.root;
        
        other.root = NULL;
        return(*this);
    };
    CTree& operator+=(const CTree& other);

    void createTree(CNode* currentNode, const string& expression, size_t& offset);
    void printTree(CNode* node);
    double evaluate(CNode* node, const map<string, double>& values);
    void parseExpression(const string& expression);


    size_t numberOfVariablesInTree() const;
    void collectVariables(const CNode* node, set<string>& variables) const;
    string getVariableNameAtIndex(size_t index) const;
    string correctFormula(string expression);
    void wierszTree(CNode* root);
    CNode* mergeTrees(CNode* left, CNode* right);
};
