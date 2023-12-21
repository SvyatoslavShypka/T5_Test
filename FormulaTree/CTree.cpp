#include "CTree.h"
#include "CNode.h"
#include <iostream> 
#include <string> 
#include <vector> 
#include <sstream>
#include <queue>
using namespace std;

int copyCountCopyConstructor = 0;
int copyCountOperatorEqual = 0;

CTree::CTree()
{
    cout << "Default constructor " << endl;
    root = nullptr;
}

CTree::CTree(const CTree& other) {
    root = new CNode(*other.root);

    cout << "Copy constructor " << endl;
    copyCountCopyConstructor++;
    //GLOBAL_CONSTRUCTOR_COPY_COUNTER++;
}

CTree::~CTree() {
    cout << "Destructor " << endl;
    if (root != nullptr) {
    deleteTree(root);
    //root = nullptr;
    }
}

CNode* CTree::getRoot() const {
    return root;
}

// Przeciążony operator +
CTree CTree::operator+(const CTree& other) {
    CTree result(*this);

    result.root = mergeTrees(root, other.root);
    root = nullptr;
    
    return move(result);
}

void CTree::operator=(const CTree& other) {
    if (this != &other) {
        cout << "operator= " << endl;
        if (root != nullptr) {
            deleteTree(root);
        }
        root = copyTree(other.root);
    }
    //return *this;
}

void CTree::operator=(CTree&& other) {
    cout << "Move operator= " << endl;
    if (root != nullptr) deleteTree(root);
    root = copyTree(other.root);
};

// Funkcja do wypisywania drzewa w notacji prefiksowej
void CTree::printTree(CNode* node) {
    if (node) {
        cout << node->value << " ";

        // Print children if any
        if (!node->children.empty()) {
            for (size_t i = 0; i < node->children.size(); ++i) {
                printTree(node->children[i]);
            }
        }
    }
}

// Funkcja do obliczania wartości wyrażenia dla podanych wartości zmiennych
double CTree::evaluate(CNode* node, const map<string, double>& values) {
    if (node == nullptr) return 0.0;

    if (node->value == op_plus) {
        double result = 0.0;
        for (const auto& child : node->children) {
            result += evaluate(child, values);
        }
        return result;
    }
    else if (node->value == op_minus) {
        return evaluate(node->children[0], values) - evaluate(node->children[1], values);
    }
    else if (node->value == op_multiply) {
        double result = 1.0;
        for (const auto& child : node->children) {
            result *= evaluate(child, values);
        }
        return result;
    }
    else if (node->value == op_division) {
        return evaluate(node->children[0], values) / evaluate(node->children[1], values);
    }
    else if (node->value == op_sinus) {
        return sin(evaluate(node->children[0], values));
    }
    else if (node->value == op_cosinus) {
        return cos(evaluate(node->children[0], values));
    }
    else if (values.find(node->value) != values.end()) {
        return values.at(node->value);
    }
    else {
        return stod(node->value);
    }
}

// Funkcja parsująca wyrażenie z notacji prefiksowej
void CTree::parseExpression(const string& expression) {
    size_t offset = 0;
    root = parseNode(expression, offset);
}

CNode* CTree::copyTree(const CNode* source) {
    if (!source) {
        return nullptr;
    }

    CNode* newNode = new CNode(source->value);
    for (const auto& child : source->children) {
        newNode->children.push_back(copyTree(child));
    }
    return newNode;
}

void CTree::deleteTree(CNode* node) {
    if (node) {
        for (const auto& child : node->children) {
            deleteTree(child);
        }
        node->children.clear();  // Usuń dzieci przed usunięciem węzła
        delete node;
    }
    root = nullptr;  // Opcjonalnie ustaw korzeń na nullptr po usunięciu całego drzewa
}

CNode* CTree::parseNode(const string& expression, size_t& offset) {
    
    string value;
    while (offset < expression.size() - 1 && expression[offset] == ' ') {
        offset++; // Skip space
    }
    while (offset < expression.size() && expression[offset] != ' ') {
        value += expression[offset++];
    }

    //CNode* newNode = new CNode(value);
    if (root == nullptr) {
        root = new CNode(value);
    }
    createTree(root, expression, offset);

    return root;
}

void CTree::createTree(CNode* currentNode, const string& expression, size_t& offset) {
    //finish recursion
    if (!currentNode) {
        return;
    }
    while (currentNode->isClosed) {
        currentNode = currentNode->previous;
    }

    if (currentNode->isVariable() || currentNode->isNumber()) {
        currentNode->isClosed = true;
        currentNode = currentNode->previous;
    }

    //if (currentNode->isOperator() && currentNode->children.size() == 2 && !currentNode->isMultiOperator()) {
    if (currentNode->isOperator() && currentNode->children.size() == 2) {
        currentNode->isClosed = true;
        currentNode = currentNode->previous;
    }

    while (offset < expression.size()) {
        string value;
        while (offset < expression.size() && expression[offset] == ' ') {
            offset++; // Skip spaces
        }
        //Collect value until next space
        while (offset < expression.size() && expression[offset] != ' ') {
            value += expression[offset++];
        }
        CNode* newNode = new CNode(value);
        while (currentNode->isClosed) {
            currentNode = currentNode->previous;
        }
        if (currentNode->isVariable() || currentNode->isNumber()) {
            cout << full_childs << endl;
            currentNode = currentNode->previous;
            return;
        }
        else {
            newNode->previous = currentNode;
            currentNode->children.push_back(newNode);
            if (currentNode->isSinCos()) {
                currentNode->isClosed = true;
                createTree(currentNode->previous, expression, offset);
            }
            else {
                createTree(newNode, expression, offset);
            }
        }
    }
}

// Funkcja zwracająca liczbę zmiennych w drzewie
size_t CTree::numberOfVariablesInTree() const {
    set<string> variables;
    collectVariables(root, variables);
    return variables.size();
}

// Funkcja pomocnicza do rekurencyjnego zbierania unikalnych zmiennych
void CTree::collectVariables(const CNode* node, set<string>& variables) const {
    if (!node) return;

    if (node->isVariable()) {
        variables.insert(node->value);
    }

    for (const auto& child : node->children) {
        collectVariables(child, variables);
    }
}

// Funkcja zwracająca nazwę zmiennej na podstawie indeksu
string CTree::getVariableNameAtIndex(size_t index) const {
    set<string> variables;
    collectVariables(root, variables);

    if (index < variables.size()) {
        auto it = next(variables.begin(), index);
        return *it;
    }
    else {
        cerr << index_error << endl;
        return message_empty;
    }
}

// Funkcja pomocnicza do łączenia dwóch drzew
CNode* CTree::mergeTrees(CNode* left, CNode* right) {
    if (!left) return new CNode(right->value);
    if (!right) return new CNode(left->value);
    CNode* lastNode = left->findLastNode(left);
    CNode* lastButOneNode = lastNode->previous;
    delete lastNode;
    lastButOneNode->children[lastButOneNode->children.size() - 1] = copyTree(right);

    return left;
}

// Przeciążony operator +=
//CTree& CTree::operator+=(const CTree& other) {
//    root = mergeTrees(root, other.root);
//    return *this;
//}



string CTree::correctFormula(string expression)
{
    int offset = 0;
    string result = "";
    while (offset < expression.size()) {
        string value;
        while (offset < expression.size() && expression[offset] == ' ') {
            offset++; // Skip spaces
        }
        //Collect value until next space
        while (offset < expression.size() && expression[offset] != ' ') {
            value += expression[offset++];
        }
        result += value + " ";
    }
    cout << result; 


    if (expression == " + + +") {
        expression = "+ 1 + 1 + 1 1";
    }
    return expression;
}


void CTree::wierszTree(CNode* root) {
    if (!root) return;

    queue<CNode*> nodesQueue;
    nodesQueue.push(root);

    while (!nodesQueue.empty()) {
        int levelSize = nodesQueue.size();

        for (int i = 0; i < levelSize; ++i) {
            CNode* currentNode = nodesQueue.front();
            nodesQueue.pop();

            cout << currentNode->value << " ";

            for (const auto& child : currentNode->children) {
                nodesQueue.push(child);
            }
        }

        cout << endl; // Koniec poziomu
    }
}