#include <iostream>
#include <vector>
#include <string>
#include <map>
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



int main() {
    vector<Rule> rules = {
        Rule('S',{"T+S","T"}),
        Rule('T',{"a","b"}),
    };
    string terminalis = "ab+";
    string alfa = "";
    string beta = "S";

    char state = 'q';
    int pointer = 0;

    string input = "b+a";
    char start = 'S';

    int max = 0;
    while (++max < 50 && state != 't')
    {
        cout<<"("<<state<<" | "<<pointer+1<<" | "<<alfa<<" | " << beta<<")"<<endl;
        //Kiterjesztes
        bool kit = false;
        if(state == 'q'){
            for (size_t i = 0; i < rules.size(); i++)
            {
                if(rules.at(i).left == beta[0]){
                    alfa.push_back(beta[0]);
                    alfa.push_back('0');
                    beta = beta.substr(1);
                    beta.insert(0,rules.at(i).right[0]);; //Első alternativa
                    kit = true;
                    break;
                }
            }
            if(kit == true) continue;
        //Sikeres input illesztes
            if(beta[0] == input[pointer]){
                pointer++;
                alfa.push_back(beta[0]);
                beta = beta.substr(1);
            }else{
        //sikertelen input illesztes
                state = 'b';

            }
        

        //Sikeres elemzes
            if(pointer == input.length() && beta.empty()){
                cout<<"Sikeres elemzés, része a nyelvnek."<<endl;
                for (size_t i = 0; i < alfa.length(); i++)
                {
                    if(terminalis.find(alfa[i])==string::npos)//-Nem terminalis
                        cout<<alfa[i];
                }
                
                return 0;
            }
        }else if(state == 'b'){        //backtrack az inputban

            if(terminalis.find(alfa.back())!=string::npos){ //-Terminalis
                pointer--;
                beta.insert(0,1,alfa.back());
                alfa = alfa.substr(0,alfa.length()-1);
            }else{        //backtrack a kiterjesztesben

                for (size_t i = 0; i < rules.size(); i++)
                {
                    if(rules.at(i).left == *(alfa.end()-2)){//[alfa.length()-2]){
                        int j = alfa.back()-'0';
                        if(++j<rules.at(i).right.size()){
                            alfa = alfa.substr(0,alfa.length()-2);
                            alfa.push_back(rules.at(i).left);
                            alfa.push_back(j+48);
                            beta = beta.substr(rules.at(i).right[j-1].length());
                            beta.insert(0,rules.at(i).right[j]);
                            state = 'q';
                            //------I Sikeres backtrack
                        }else if(rules.at(i).left == start && pointer == 0){
                            //------II
                            cout<<"Nem része a nyelvnek"<<endl;
                            return 0;
                        }else{//----III
                            //levagott resz hossza
                            
                            int l = rules.at(i).right[*(alfa.end()-1)-48].length();
                            beta = beta.substr(l);
                            beta.insert(0,1,rules.at(i).left);

                            alfa = alfa.substr(0,alfa.length()-2);
                        }
                    }
                }


            }


        }


    }

    return 0;
}
