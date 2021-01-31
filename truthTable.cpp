#include <iostream>
#include <vector>
#include <math.h>
#include <stack>
#include <string.h>
#include <string>
using namespace std; 


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

 int evaluateEachCombo(vector<int> &combination, vector<string> &expression){
      stack<string> st;
      
      int index = 0;
      for(int i = 0; i < expression.size(); i++){
          vector<string> eval;
          // ( p and q ) 
          if(expression.at(i) != "(" && expression.at(i) != "or" && expression.at(i) != "and" && expression.at(i) != ")" && expression.at(i) != "not"){
              if(st.top() == "not"){
                  if(combination[index] == 0){
                        combination[index] = 1;
                  }
                  else{
                      combination[index] = 0;
                  }
                  st.pop();
              }
              st.push(to_string(combination[index++]));
          }
          else if(expression.at(i) != ")"){
              st.push(expression.at(i));
          }
          else{
              while(st.top() != "("){
                  if(st.size() == 1 && st.top() != "("){
                      return -1;
                  }
                  eval.push_back(st.top());
                  st.pop();
                 
              }
              st.pop();
              if(eval.size() < 3){
                  return -1;
              }
              if(eval[1] == "or"){
                  bool num = stoi(eval[0]) || stoi(eval[2]);
                  if(num){
                      st.push("1");
                  }
                  else{
                     st.push("0");
                  }
              }
              else if(eval[1] == "and"){
                   bool num = stoi(eval[0]) && stoi(eval[2]);
                  if(num){
                      st.push("1");
                  }
                  else{
                     st.push("0");
                  }
              }
          }
          
      }
      if(st.size() > 1){
          return -1;
      }
      return stoi(st.top());
 }


 void evaluateExpressions(vector<vector<int>> &matrix, vector<string> &expression){
     for(int i = 0; i < matrix.size(); i++){
        int boolOutput = evaluateEachCombo(matrix[i], expression);
        if(boolOutput == -1){
            throw std::invalid_argument("");
        }
        matrix[i].push_back(boolOutput);
     }
 }

 

int main(){
   int number = 0;
   string expression = "";
   cout << "Number of Variables? ";
   cin >> number;
   cout << endl;
   cout << "Expression? ";
   cin.ignore();
   getline(cin, expression);
   string oneExpression = "";
   vector<string> varExp;
   // input: ( p and q )
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
    int count = 0;
     for(int i = 0; i < varExp.size(); i++){
       if(varExp[i] != "(" && varExp[i] != "or" && varExp[i] != "and" && varExp[i] != ")" && varExp[i] != "not"){
              count++;
       }
   }
   if(count != number){
       cout << "Number of variables does not match with input." << endl;
       return 0;
   }
   vector<vector<int>> matrix = outputConditions(number);
   try{
     evaluateExpressions(matrix, varExp);
   }
   catch(invalid_argument& e){ 
       cout << "Input not entered right." << endl;
       return 0;
   }
  
   
   for(int i = 0; i < varExp.size(); i++){
       if(varExp[i] != "(" && varExp[i] != "or" && varExp[i] != "and" && varExp[i] != ")" && varExp[i] != "not"){
              cout << varExp[i] << "| ";
       }
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



