/*利用栈实现四则运算表达式求值
by zoe*/

#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <string>
#include <stack>
#include <map>
#include <iostream>

using namespace std;

//先讲输入的中缀表达式转换成后缀表达式
string change(string infix){
  string postfix;//后缀表达式
  stack<char> mark;//符号栈

  map<char,int> priority;
  priority['+']=0;
  priority['-']=0;
  priority['*']=1;
  priority['/']=1;

  int current=0;
  for(int i=0;i<infix.size();i++){
    current=infix[i];
    switch (current) {
      case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '.':
         postfix.push_back(current);//是数字的话直接输入到后缀表达式的字符串里
         break;
      case '+': case '-': case '*': case '/':
      while(!mark.empty()){
        char tempTop=mark.top();
        if(current!='('&&priority[current]<=priority[tempTop]){
          postfix.push_back(tempTop);
          mark.pop();
          if(mark.empty()) break;
          tempTop=mark.top();
        }
      }
      mark.push(current);
      break;

      case ')':
      postfix.push_back('#');
      while(mark.top()!='('){
        postfix.push_back(mark.top());
        mark.pop();
      }
      mark.top();
      break;

      case '(':
      if(infix[i-1] >= '0' && infix[i-1] <= '9'){
         postfix.push_back('#');
         mark.push('*');
      }
      mark.push(current);
      break;

      default:
      break;
    }
  }
  if(infix[infix.size()-1] != ')')
        postfix.push_back('#');//中缀表达式最后一个是数字需要加上#。
    while(!mark.empty())//如果栈非空，全部出栈并写入输出字符串
    {
        postfix.push_back(mark.top());
        mark.pop();
    }

  return postfix;
}


//再对后缀表达式利用栈进行求值
float caculate(string postfix){
  stack<float> TempResult;
  float TempNum;
  string StrNum;
  float currNum;

  for(string::const_iterator i=postfix.begin();i!=postfix.end();i++){
    switch (*i) {
      case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '.':
      StrNum.push_back(*i);
      break;

      case '+':
      TempNum=TempResult.top();
      TempResult.pop();
      TempNum+=TempResult.top();
      TempResult.pop();
      TempResult.push(TempNum);
      break;

      case '-':
      TempNum=TempResult.top();
      TempResult.pop();
      TempNum=TempResult.top()-TempNum;
      TempResult.pop();
      TempResult.push(TempNum);
      break;

      case '*':
      TempNum=TempResult.top();
      TempResult.pop();
      TempNum*=TempResult.top();
      TempResult.pop();
      TempResult.push(TempNum);
      break;

      case '/':
      TempNum=TempResult.top();
      TempResult.pop();
      TempNum=TempResult.top()/TempNum;
      TempResult.pop();
      TempResult.push(TempNum);
      break;

      case '#':
      currNum = atof(StrNum.c_str());//in c++11, use currNum = std::stof(strNUm);
      StrNum.clear();
      TempResult.push(currNum);
      break;
    }
  }
  return TempResult.top();
}


float expressionCalculate(std::string s)
{
    return caculate(change(s));
}

int main(){
  string test1="2*(3+5)-1+4/2";
  float result=expressionCalculate(test1);
  printf("%f\n",result );
  return 0;
}
