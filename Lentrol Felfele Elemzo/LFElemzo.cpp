#include <iostream>
#include <string>
#include <vector>

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



int main(){
    
    vector<Rule> rules = {
        Rule('S',"S+T"),
        Rule('S',"T"),
        Rule('T',"a"),
        Rule('T',"b")
    };
    char state = 'q';
    int pointer = 0;
    string alfa = "";
    string beta = "";

    string input = "a+b+c";
    char start = 'S';

    cout<<"Start"<<endl;

    while (state != 't')
    {
        //redukalas
        cout<<state<<" | "<<pointer+1<<" | "<<alfa<<" | "<<beta<<endl;

        if(state == 'q'){
            
            bool redukalt = false;
            for (int j = 0; j < rules.size(); j++) ///// OUT OF RANGE
            {
                int l = rules.at(j).right.length();
                if(l<= alfa.length() && rules.at(j).right.compare(alfa.substr(alfa.length()-l))==0){
                    alfa = alfa.substr(0,alfa.length()-l) + rules.at(j).left;
                    beta = to_string(j) + beta;
                    redukalt = true;
                    break;
                }

            }
            if (redukalt)
            {
                continue;
            }
            
            

            //leptetes
            if (pointer < input.length())
            {
                alfa.push_back(input[pointer]);
                beta.insert(0,"s");
                pointer++;
                continue;
            }
            
            //sikeres befejezes
            if (pointer == input.length())
            {
                if(alfa.length() == 1 && alfa[0] == start){
                    state = 't';
                    break;
                }else{         //backtrack
                    state = 'b';
                }
            }
        }else if(state == 'b'){

            bool success =  false;
            if (pointer < input.length()) 
            {
                int k = beta[0]-'0';
                string jobb = rules[k].right;
                
                //------------------------------------------ //I
                k++;
                while (k<rules.size())
                {
                    if(rules[k].right.compare(jobb)){
                        beta = beta.substr(1);
                        beta.insert(0,to_string(k));

                        alfa = alfa.substr(0,alfa.length()-1);
                        alfa.push_back(rules[k].left);
                        success = true;
                        break;
                    }

                    k++;
                }
                if (!success) //II
                {
                    int j = beta[0]-'0';
                    beta = beta.substr(1);
                    beta.insert(0,"s");
                    alfa = alfa.substr(0,alfa.length()-1);
                    
                    string jobb = rules[j].right;
                    for (size_t i = 0; i < jobb.length(); i++)
                    {
                        alfa.push_back(jobb[i]);
                    }
                    alfa.push_back(input[pointer]);
                    pointer++;
                    success = true;
                }
            }else if (pointer == input.length()) //III
            {
                if (isdigit(beta[0]))
                {
                    int index = beta[0]-'0';
                    if(alfa.empty() == false && rules.at(index).left == alfa[alfa.length()-1]){

                        alfa = alfa.substr(0,alfa.length()-1);
                        alfa.append(rules.at(index).right);
                        success = true;
                    }
                }
                
            }
            
            // IV
            if(success == false){
                if (pointer < input.length() && pointer > 0 && input[pointer] == alfa[alfa.length()-1] && beta[0]=='s')
                {
                    pointer--;
                    alfa = alfa.substr(0,alfa.length()-1);
                    beta = beta.substr(1);
                }else{ //V
                    cout<< "Nem resze a nyelvnek"<<endl;
                    return 0;
                }
                
            }
        
        }
    }
    cout<< "Siker" <<endl;
    for (int i = 0; i < beta.length(); i++) {
        if (beta[i] != 's')
        {
            cout<< ++beta[i];
        }
        
    }
    
    cout<<endl;
        

    return 0; 
}