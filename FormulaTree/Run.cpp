#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <sstream>
#include <set>
#include "CNode.h"
#include "CTree.h"
#include "CMySmartPointer.h"

using namespace std;

// Funkcja do wczytywania wartości z stringstream
void readValues(stringstream& ss, vector<double>& values) {
    double value;
    while (ss >> value) {

        values.push_back(value);
    }
}

int main() {
    
    int* x = new int;

    *x = 5;

    int* y = new int;
    *y = 6;
    CMySmartPointer<int> firstSP(x);
    CMySmartPointer<int> secondSP(y);
    firstSP = secondSP;

    CTree tree;

    while (true) {
        cout << message_enter;
        string command;
        getline(cin, command);

        stringstream ss(command);
        string cmd;
        ss >> cmd;

        if (cmd == command_comp) {
            // Obsługa polecenia "comp"
            // Odczytaj wartości i przypisz do odpowiednich zmiennych w drzewie

            vector<double> values;
            readValues(ss, values);

            // Sprawdź, czy liczba wartości jest zgodna z ilością zmiennych w drzewie
            if (values.size() != tree.numberOfVariablesInTree()) {
                cout << message_err << endl;
            }
            else {
                // Stworzenie mapy zmiennych i ich wartości
                map<string, double> variableValues;
                for (size_t i = 0; i < values.size(); ++i) {
                    variableValues[tree.getVariableNameAtIndex(i)] = values[i];
                }

                // Wywołanie funkcji evaluate na korzeniu drzewa
                double result = tree.evaluate(
                    tree.getRoot(), variableValues);

                // Wyświetlenie wyniku
                cout << message_result << result << endl;
            }
        } //TODO make print easy: repeat the formula
        else if (cmd == message_print) {
            // Obsługa polecenia "print"
            cout << message_tree;
            if (!tree.getRoot()) {
                cout << message_no_tree << endl;
            }
            else {
                tree.printTree(tree.getRoot());
                cout << endl;
            }
        }
        else if (cmd == message_vars) {
            // Obsługa polecenia "vars"
            set<string> variables;
            tree.collectVariables(tree.getRoot(), variables);
            cout << message_variables;
            for (const auto& variable : variables) {
                cout << variable << message_space;
            }
            cout << endl;
        }
        else if (cmd == command_enter) {
            string formula;
            getline(ss, formula);

            formula = tree.correctFormula(formula);

            tree.parseExpression(formula);
            cout << message_parsed << endl;
        } 
        else if (cmd == command_del) {
            tree.deleteTree(tree.getRoot());
            cout << message_deleted_tree << endl;
        }
        else if (cmd == command_join) {
            CTree newTree;
            string formula;
            getline(ss, formula);
            newTree.parseExpression(formula);
            //tree += newTree;
            tree = tree + newTree;
            cout << message_merged_tree << endl;
        }
        else if (cmd == command_exit) {
            cout << command_exit << endl;
            //tree.deleteTree(tree.getRoot());
            /*CTree result(tree);

            result.root = mergeTrees(root, other.root);
            root = nullptr;*/
            return 0;
        }
        else if (cmd == message_levels) {
            tree.wierszTree(tree.getRoot());
        }
    }
    return 0;
}
