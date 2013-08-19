#include "../stack/stack.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

bool isdigit(char c){
  return (c -'0' > 0 && c -'0' < 9);
}
void oneOperatorEval(stack<char>& operatr, stack<int> & operands){
  char operatorc = operatr.pop();
  int l = operands.pop();
  int r = operands.pop();
  if(operatorc == '+'){
	operands.push(l + r);
  }
  if(operatorc == '-'){
	operands.push(l - r);
  }
  if(operatorc == '*'){
	operands.push(l * r);
  }	  
  if(operatorc == '/'){
	operands.push(l / r);
  }
}
int main(){
  string s = "(5+2) + ( 5 * 6 )";
  int i =0;
  stack<char> operatr;
  stack<int> operands;
  while(i < s.size()){
	if( s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/'){
	  operatr.push(s[i]);
	  i++;
	}else if (s[i] == ')'){ // do the pop of operand here and do one eval
	  oneOperatorEval(operatr,operands);
	  ++i;
	}else if(isdigit(s[i])){ //digit
	  string ls;
	  ls = ls + s[i];
	  int opr = 0;
	  while(isdigit(s[++i]) && s[i] < s.size()){
		ls = ls + s[i];
	  }
	  stringstream ss(ls);
	  ss >> opr;
	  operands.push(opr);
	}else{ // ignore any other character 
	  i++;
	}
  } /* while ends here */
  while(operatr.size() != 0){ /* now keep poping up the leftover operator to get the multiple set of exp evaluated */
	  oneOperatorEval(operatr,operands);
  }
  cout << "result is " << operands.pop() << endl;
	
}
