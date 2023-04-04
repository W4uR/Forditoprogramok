#include <iostream>
#include <stack>
#include <vector>
#include <string>

using namespace std;




int main(){

    string bemenet= "";
    string kimenet="";

    std::cout << "\nKerem adja meg a bemenetet: \n";

    getline(cin, bemenet);
    int length = bemenet.length();
    for (int i=0; i < length; ++i) {
    
        if (isdigit(bemenet[i])) {
            while (isdigit(bemenet[i])) {
                ++i;
            }
            kimenet += "<szam> ";
        }
        if (isalpha(bemenet[i])) {
            while (isalpha(bemenet[i]) || isdigit(bemenet[i])) {
                ++i;
            }
            kimenet += "<azonosito> ";
        }
        if (bemenet[i]==':' && bemenet[i+1] == '=') {
            i=i+2;
            kimenet += "<:= token> ";
        }
        if (bemenet[i] == '{') {
            for (int j=i; j < length; ++j) {
                if (bemenet[j] == '}') {
                    i = j;
                    kimenet += "<{}komment> ";
                    break;
                }
            }
        }
        if (bemenet[i] == '(' && bemenet[i+1]=='*') {
            for (int j = i+2; j < length; ++j) {
                if (bemenet[j] == '*' && bemenet[j+1]==')') {
                    i = j+1;
                    kimenet += "<(**)komment> ";
                    break;
                }
            }
            }
        if (bemenet[i] == '<' && bemenet[i + 1] == '>') {
            kimenet += "<<> token> ";
        }
        if (bemenet[i] == '<' && bemenet[i + 1] == '=') {
            kimenet += "<<= token>> ";
        }
        if (bemenet[i] == '>' && bemenet[i + 1] == '=') {
            kimenet += "<>= token> ";
        }
        if (bemenet[i] == '$') {
            kimenet += "<eof>";
            break; 
        }
    }
    cout << kimenet <<endl;
    return 0;
}