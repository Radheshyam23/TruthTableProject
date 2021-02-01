#include <iostream>
#include <vector>
#include <math.h>
#include <stack>
#include <string.h>
#include <string>
#include <unordered_map>
using namespace std;


bool isValid(vector<string> &expression){           //checks whether brackets are properly placed
   vector<string> brackets;
   for(int i = 0; i < expression.size(); i++){
       if(expression[i] == ")" || expression[i] == "("){
           brackets.push_back(expression[i]);
       }
   }
   stack<string> check;
   for(int i = 0; i < brackets.size(); i++){
       if(check.size() > 0 && brackets[i] == ")"){
           if(check.top() != "("){
               return false;
           }
           else{
               check.pop();
           }
       }
       else{
           if(check.size() == 0 && brackets[i] == ")"){
               return false;
           }
           check.push(brackets[i]);
       }
   }
   if(check.size() >= 1){
       return false;
   }
   return true;

}


vector<int> convertToBinary(int number, int size){
    vector<int> binary;
    while(number != 0){
        int temp = number % 2;
        binary.insert(binary.begin() + 0, temp);
        number = number / 2;
    }
    while(binary.size() != size){
        binary.insert(binary.begin() + 0, 0);
    }
    return binary;
}


 vector<vector<int>> outputConditions(int number){
   vector<vector<int>> matrixVar;
   for(int i = 0; i < pow(2, number); i++){
        matrixVar.push_back(convertToBinary(i, number));
   }
   return matrixVar;

 }

bool CalcXOR(string a, string b)
{
    if((stoi(a)==0 && stoi(b)==1) || (stoi(a)==1 && stoi(b)==0))
        return true;
    else
        return false;
}

 int evaluateEachCombo(unordered_map<string, int> map, vector<string> &expression){
      stack<string> st;
      for(int i = 0; i < expression.size(); i++){
          vector<string> eval;

          if(map.find(expression[i]) != map.end()){
                if(st.size() > 0 && st.top() == "not"){
                    st.pop();
                    if(map[expression[i]] == 0){
                        st.push("1");
                    }
                    else{
                        st.push("0");
                    }
                }
                else{
                   st.push(to_string(map[expression[i]]));
                }
           }
          else if(expression.at(i) != ")"){
              if(st.size() > 0 && expression[i] == "not" && st.top() == "not"){
                  st.pop();
              }
              else{
                  st.push(expression.at(i));
              }
            }
          else{
              while(st.top() != "("){
                  eval.push_back(st.top());
                  st.pop();
                }
              st.pop();
              if(eval[1] == "or"){
                  bool num = stoi(eval[0]) || stoi(eval[2]);
                  if(st.size() > 0 && st.top() == "not"){
                      st.pop();
                       if(num){
                        st.push("0");
                       }
                       else{
                        st.push("1");
                       }
                  }
                  else{
                    if(num){
                        st.push("1");
                    }
                    else{
                        st.push("0");
                    }
                  }
              }
              else if(eval[1] == "and"){
                  bool num = stoi(eval[0]) && stoi(eval[2]);
                   if(st.size() > 0 && st.top() == "not"){
                      st.pop();
                       if(num){
                        st.push("0");
                       }
                       else{
                        st.push("1");
                       }
                   }
                   else{
                    if(num){
                        st.push("1");
                    }
                    else{
                        st.push("0");
                    }
                }

            }

            else if(eval[1] == "xor")
            {
                bool num = CalcXOR(eval[0],eval[2]);

                if(st.size() > 0 && st.top() == "not")
                {
                    st.pop();
                    if(num)
                        st.push("0");

                    else
                        st.push("1");
                }
                else
                {
                    if(num)
                        st.push("1");

                    else
                        st.push("0");
                }
            }
        }
      }
    return stoi(st.top());
}


 void evaluateExpressions(vector<vector<int>> &matrix, vector<string> &expression, vector<string> variables){
     unordered_map<string, int> map;
     for(int i = 0; i < matrix.size(); i++){
         for(int k = 0; k < variables.size(); k++){
            map[variables[k]] = matrix[i][k];
         }
        matrix[i].push_back(evaluateEachCombo(map, expression));
     }
 }



int main(){
   int number = 0;
   string expression = "";
   cout << "Number of Unique Variables? ";
   cin >> number;
   cout << endl;
   cout << "Expression? ";
   cin.ignore();
   getline(cin, expression);
   string oneExpression = "";
   vector<string> varExp;
   vector<string> variables;

   for(int i = 0; i < expression.length(); i++){
        if(expression.at(i) != ' '){
            oneExpression += expression.at(i);
        }
        else{
            varExp.push_back(oneExpression);
            oneExpression = "";
        }

    }
    varExp.push_back(oneExpression);
    unordered_map<string, int> map;

     for(int i = 0; i < varExp.size(); i++){
       if(varExp[i] != "(" && varExp[i] != "or" && varExp[i] != "and" && varExp[i] != ")" && varExp[i] != "not" && varExp[i]!= "xor")
        {
              if(map.find(varExp[i]) == map.end()){
                   map[varExp[i]] = 1;
                   variables.push_back(varExp[i]);
              }
              else{
                  map[varExp[i]]++;
              }
       }
   }

   if(map.size() != number){
       cout << "Number of variables does not match with input." << endl;
       return 0;
   }
   if(!isValid(varExp)){
       cout << "Input not right." << endl;
       return 0;
   }
   vector<vector<int>> matrix = outputConditions(number);
    try{
     evaluateExpressions(matrix, varExp, variables);
    }
   catch(invalid_argument& e){
       cout << "Input not entered right." << endl;
       return 0;
   }


   for(int i = 0; i < variables.size(); i++){
       cout << variables[i] << "| ";
   }
   cout << "O| " << endl;
   for(int i = 0; i < matrix.size(); i++){
       for(int j = 0; j < matrix[i].size(); j++){
           cout << matrix[i][j] <<  "| ";
       }
        cout << endl;
    }

   return 0;

}
