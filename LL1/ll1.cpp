#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <string>

using namespace std;

struct Rule
{
    char left;
    string right;
    Rule(char _left, string _right);
};

Rule::Rule(char _left, string _right)
{
    left = _left;
    right = _right;
}



int main() {
    vector<Rule> rules = {
        Rule('S',"aS"),
        Rule('S',"bAc"),
        Rule('A',"bAc"),
        Rule('A',"d")
    };

    char t[] = {'a','b','c','d'};
    char nt[] = {'S','A'};

    // Create a map of maps to represent the table
    map<char, map<char, string>> table;
    
    for (size_t i = 0; i < sizeof(t); i++)
    {
        for (size_t j = 0; j < sizeof(t); j++)
        {
            if(i==j){
                table[t[i]][t[j]] = "pop";
            }else{
                table[t[i]][t[j]] = "error";
            }
        }
    }
    
    for (size_t i = 0; i < sizeof(nt); i++)
    {
        for (size_t j = 0; j < sizeof(t); j++)
        {

            int index = -1;
            //find index of rule
            for (int ri = 0; ri < rules.size(); ri++)
            {
                if(rules[ri].right[0] == t[j] && rules[ri].left == nt[i]){
                    index = ri;
                    break;
                }
            }
            
            if(index != -1){
                    table[nt[i]][t[j]] = "("+rules[index].right+","+to_string(index+1)+")";
            }else{
                table[nt[i]][t[j]] = "error";
            }
            
        }
        
    }
    
    // Kell még a # sor és a # oszlop

    // Iterate through the rows and columns of the table
    for (const auto& row : table) {
        for (const auto& col : row.second) {
            // Access the element of the table using the row and column names
            std::cout << "table[" << row.first << "][" << col.first << "] = " << col.second << std::endl;
        }
    }
    
    
    return 0;
}