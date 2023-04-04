#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

struct Rule
{
    char left;
    vector<string> right;
    Rule(char _left, vector<string> _right);
};

Rule::Rule(char _left, vector<string> _right)
{
    left = _left;
    right = _right;
}

bool contains(vector<string> &vector, string value){
    if (std::count(vector.begin(), vector.end(), value)) {
        return true;
    }
    else {
        return false;
    }
}

// CYK algorithm function
bool cyk(string input, vector<Rule> rules) {
    int n = input.length();
    vector<vector<set<char>>> pyramid(n, vector<set<char>>(n)); //NxN-es mátrix

    // Legalsó sor
    for (int i = 0; i < n; i++) {
        for (auto r : rules) {
            if(contains(r.right,input)){
                pyramid[i][i].insert(r.left);
            }
        }
    }



    for (int len = 2; len <= n; len++) {                            // Szint
        for (int i = 0; i <= n - len; i++) {                        // Oszlop
            int j = i + len - 1;
            for (int k = i; k < j; k++) {
                for (auto r : rules) {
                    for (char a : pyramid[i][k]) {
                        for (char b : pyramid[k+1][j]) {
                            string prod = string(1,a) + string(1,b);
                            if (contains(r.right,prod)) {
                                pyramid[i][j].insert(r.left);
                            }
                        }
                    }
                }
            }
        }
    }

    // Kezdő szimbolum szerepel a csúcsban
    
    for (auto r : pyramid[0][n-1]) {
        if (r == 'S') {
            return true;
        }
    }
    return false;
}

int main() {

    vector<Rule> rules = {
        Rule('S',{"AB", "CD", "CB", "SS"}),
        Rule('A',{"BC", "a"}),
        Rule('B',{"SC", "b"}),
        Rule('C',{"DD", "b"}),
        Rule('D',{"BA"}),
    };



    vector<string> testStrings = {"aabbaba", "ab", "abba", "aabb"};
    for (auto s : testStrings) {
        if (cyk(s, rules)) {
            cout << s << " generálja." << endl;
        } else {
            cout << s << " NEM generálja" << endl;
        }
    }

    return 0;
}
