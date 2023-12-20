#include "CNode.h"

using namespace std;

CNode::CNode(string val)
{
    value = val;
    previous = nullptr;
    isClosed = false;
}

CNode* CNode::operator+(CNode* other) {
    CNode* newNode = new CNode(op_plus);
    newNode->children.push_back(this);
    newNode->children.push_back(other);
    return newNode;
}

bool CNode::isVariable() const {
    if (value.empty() || !isalpha(value[0]) || isSinCos()) {
        return false;
    }

    for (char ch : value) {
        if (!isalnum(ch)) {
            return false;
        }
    }
    return true;
}

bool CNode::isNumber() const {
    for (char ch : value) {
        if (!isdigit(ch)) {
            return false;
        }
    }
    return true;
}

bool CNode::isOperator() const {
    if (value == op_plus || value == op_minus || value == op_multiply || value == op_division) {
        return true;
    }
    return false;
}

bool CNode::isSinCos() const {
    if (value == op_sinus || value == op_cosinus) {
        return true;
    }
    return false;
}

CNode* CNode::findLastNode(CNode* node) const {
    if (node) {
        while (!node->children.empty()) {
            node = node->children[node->children.size() - 1];
        }
    }
    return node;
}