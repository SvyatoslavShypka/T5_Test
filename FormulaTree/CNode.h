#pragma once

#include <string>
#include <vector>
using namespace std;

class CNode {
public:
    string value;
    vector<CNode*> children;
    CNode* previous;
    bool isClosed;

    CNode(string val);
    CNode(const CNode& other);

    CNode* operator+(CNode* other);
    bool isVariable() const;
    bool isNumber() const;
    bool isOperator() const;
    bool isSinCos() const;
    CNode* findLastNode(CNode* node) const;
};

const string index_error = "Error: Index out of range.";
const string full_childs = "incorrect input! There are already two childs";
const string message_enter = "Enter command: ";
const string command_comp = "comp";
const string command_enter = "enter";
const string command_del = "del";
const string command_join = "join";
const string command_exit = "exit";
const string message_err = "Error: Incorrect number of values provided for computation.";
const string message_result = "Result: ";
const string message_print = "print";
const string message_tree = "Tree: ";
const string message_no_tree = "Tree doesn't exist";
const string message_vars = "vars";
const string message_variables = "Variables: ";
const string message_parsed = "Expression entered and parsed.";
const string message_deleted_tree = "Tree was deleted";
const string message_merged_tree = "Tree was merged";
const string message_levels = "levels";
const string op_plus = "+";
const string op_minus = "-";
const string op_multiply = "*";
const string op_division = "/";
const string op_sinus = "sin";
const string op_cosinus = "cos";
const string message_space = " ";
const string message_empty = "";