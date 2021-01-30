#include <iostream>
#include <vector>
#include <math.h>
#include <stack>
#include <string.h>
#include <string>
using namespace std; 


vector<int> convertToBinary(int number, int size){
    vector<int> binary;
    vector<int> binary2;
    while(number != 0){
        int temp = number % 2;
        binary.push_back(temp);
        number = number / 2;
    }
    for(int i = binary.size() - 1; i >= 0; i--){
        binary2.push_back(binary[i]);
    }
    int index = binary2.size();
    while(index != size){
        binary2.insert(binary2.begin() + 0, 0);
        index++;
    }
    return binary2;
}


 vector<vector<int>> outputConditions(int number){
   vector<vector<int>> matrixVar;
   for(int i = 0; i < pow(2, number); i++){
          vector<int> binary = convertToBinary(i, number);
          matrixVar.push_back(binary);
   }
   return matrixVar;

 }

 int evaluateEachCombo(vector<int> combination, vector<string> expression){
      stack<string> st;
      
      int index = 0;
      for(int i = 0; i < expression.size(); i++){
          vector<string> eval;
          // ( p and q )
          if(expression.at(i) != "(" || expression.at(i) != "or" || expression.at(i) != "and" || expression.at(i) != ")"){
              st.push(to_string(combination[index++]));
          }
          else if(expression.at(i) != ")"){
              st.push(expression.at(i));
          }
          else{
              while(st.top() != "("){
                  eval.push_back(st.top());
                  st.pop();
              }
              st.pop();
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
      return stoi(st.top());
 }


 void evaluateExpressions(vector<vector<int>> &matrix, int number, vector<string> expression){
     for(int i = 0; i < matrix.size(); i++){
        int boolOutput = evaluateEachCombo(matrix[i], expression);
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
   vector<vector<int>> matrix = outputConditions(number);
   evaluateExpressions(matrix, number, varExp);
   for(int i = 0; i < matrix.size(); i++){
       for(int j = 0; j < matrix[i].size(); j++){
           cout << matrix[i][j] <<  " ";
       }
       cout << endl;
   }

   return 0;

}



