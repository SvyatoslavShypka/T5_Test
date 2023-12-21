#pragma once


#include <iostream>
#include <map>
#include <set>
#include "CNode.h"
using namespace std;

class CNode;

class CTree {

private:
    CNode* root = nullptr;

    CNode* parseNode(const string& expression, size_t& offset);

public:

    static int copyCountCopyConstructor;
    static int copyCountOperatorEqual;
    
    CNode* copyTree(const CNode* source);
    void deleteTree(CNode* node);
    CTree();
    CTree(const CTree& other);
        
    ~CTree();

    CNode* getRoot() const;

    void operator=(const CTree& other);
    //void operator=(CTree&& other);
    CTree operator+(const CTree& other);

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

