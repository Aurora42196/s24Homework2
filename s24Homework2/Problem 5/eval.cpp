//
//  eval.cpp
//  s24Homework2
//
//  Created by Cameron Maiden on 4/30/24.
//

#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

///////////////////////////////////////////////////////////////////////////
//  Function declarations
///////////////////////////////////////////////////////////////////////////

int evaluate(string infix, string& postfix, bool& result);
// Evaluates a boolean expression
//   If infix is a syntactically valid infix boolean expression,
//   then set postfix to the postfix form of that expression, set
//   result to the value of the expression and return zero.  If
//   infix is not a syntactically valid expression, return 1; in
//   that case, postfix may or may not be changed, but result must
//   be unchanged.

bool checkPrecedence(const char& ch, const char& top);
// returns true only if the precedence of ch <= precedence of stack top
// and returns false otherwise (i.e. precedence of ch was greater than top, invalid ch was passed in)

bool validInfix(const char& prev, const char& curr);
// helper function to check if the infix expression is syntactically valid by checking
// whether the current char is a valid char to succeed the previous char

bool postfixEval(string& pf);
// helper function to evaluate the postfix function


///////////////////////////////////////////////////////////////////////////
//  Function implementations
///////////////////////////////////////////////////////////////////////////
/// Operator precedence convention:
///  Binary boolean infix operators     Associativity
///  1. parentheses => ()                    right to left
///  2. ! => not                                    right to left
///  2. & => and                                  left to right
///  3. | => inclusive or                       left to right
///  4. operands => T, F                     left to right
///
/// Here are some examples of valid expressions:
/// T                          evaluates to true
/// (F)                        evaluates to false
/// T&(F)                      evaluates to false
/// T & !F                     evaluates to true
/// !(F|T)                     evaluates to false
/// !F|T                       evaluates to true
/// T|F&F                      evaluates to true
/// T&!(F|T&T|F)|!!!(F&T&F)    evaluates to true
///
int evaluate(string infix, string& postfix, bool& result)
{
    if (infix.empty()) // check if the string passed in is empty
        return 1;
    
    postfix = "";
    stack<char> opStack; //Initialize the operator stack to empty
    
    // assign the first and last valid characters of the infix expression in the case that there's space at the beginning or the end of the string
    char start = '\0';
    char end = '\0';
    for (unsigned long i = 0; i < infix.size(); i++)
    {
        if (infix.at(i) == ' ')
            continue;
        else
            start = infix.at(i);
            break;
    }
    for (unsigned long i = infix.size()-1; i > 0; i--)
    {
        if (infix.at(i) == ' ')
            continue;
        else
            end = infix.at(i);
            break;
    }
    
    switch (start) // Check the beginning of the string for valid starting character
    {
        case 'T':
        case 'F':
        case '!':
        case '(':
            break;
            
        default: // Infix expression cannot start with anything other than above cases
            cerr << "infix expression cannot begin with " << infix.at(0) << endl;
            return 1;
            break;
    }
    
    switch (end) // Check the end of the string for valid starting character
    {
        case 'T':
        case 'F':
        case ')':
            break;
            
        default: // Infix expression cannot start with anything other than above cases
            cerr << "infix expression cannot end with " << infix.at(infix.size()-1) << endl;
            return 1;
            break;
    }

    
    char prev; // keeps track of the last significant char before iterating through the next char in the string
    for(int k = 0; k != infix.size(); k++)
    {
        char ch = infix.at(k);
        switch (ch)
        {
            case 'T':
            case 'F':
                if (!validInfix(prev, infix.at(k)))
                    return 1;
                prev = ch;
                
                postfix += ch;
                break;
            case '(':
            case '!':
                if (!validInfix(prev, infix.at(k)))
                    return 1;
                prev = ch;
                
                opStack.push(ch);
                break;
            case ')':
                if (!validInfix(prev, infix.at(k)))
                    return 1;
                prev = ch;
                
                while(opStack.top() != '(')
                {
                    if (opStack.empty())
                        return 1;
                    postfix += opStack.top();
                    opStack.pop();
                }
                opStack.pop();
                break;
            case '&':
            case '|':
                if (!validInfix(prev, infix.at(k)))
                    return 1;
                prev = ch;
                // checkPrecedence(ch,opStack.top()) validates if the precedence of ch <= precedence of stack top
                while (!opStack.empty() && opStack.top() != '(' && checkPrecedence(ch,opStack.top()) == true)
                {
                    postfix += opStack.top();
                    opStack.pop();
                }
                opStack.push(ch);
                break;
                
            case ' ':
                continue; // we ignore any blank space in the expression
                
            default: ///syntactically invalid infix string (any char passed in that is not one of the cases above)
                return 1;
                break;
        }
    }
    while(!opStack.empty())
    {
        postfix += opStack.top();
        opStack.pop();
    }
    
    // By this point, postfix should be a syntactically valid postfix string,
    // meaning newInfix should be syntactically valid before this function is ever called
    // if newInfix is not valid, then result should remain unchanged
    result = postfixEval(postfix);
    
//    cerr << "Made it to end of evaluate function somehow" << endl;
    return 0;
}

bool checkPrecedence(const char& ch, const char& top)
{
    switch (ch) // Used to check if precedence of ch <= the precedence of stack.top()
    {
        case '!':
            if(top == '!')
                return true;
            else 
                return false;
            break;
            
        case '&':
            if(top == '!' || top == '&')
                return true;
            else
                return false;
            
        case '|':
            if (top == '!' || top == '&' || top == '|')
                return true;
            else
                return false;
            
        case 'T':
        case 'F':
            if(top == '!' || top == '&' || top == '|' || top == 'T' || top == 'F')
                return true;
            else
                return false;
        default: // value for ch is not any of the values above
            cerr << "invalid char: cannot check precedence" << endl;
            return false;
            break;
    }
}

bool validInfix(const char& prev, const char& curr)
{
    switch (prev) 
    {
        case 'T':
        case 'F':
            switch (curr) 
            {
                case '&':
                case '|':
                case '(':
                case ')':
                    return true;
                    
                default:
                    cerr << "invalid char after T or F" << endl;
                    return false;
            }
            
        case '&':
        case '|':
        case '!':
        case '(':
            switch (curr)
            {
                case 'T':
                case 'F':
                case '!':
                case '(':
                    return true;
                    
                default:
                    cerr << "invalid char after " << prev << endl;
                    return false;
            }
            
        case ')':
            switch (curr)
            {
                case '&':
                case ')':
                    return true;
                    
                default:
                    cerr << "invalid char after )" << endl;
                    return false;
            }
        case '\0': // this means that curr is the first valid char in the expression
            return true;
            
        default:
            cerr << "invalid char passed in for prev" << endl;
            return false;
    }
}


bool postfixEval(string& pf)
{
    stack<char> pfStack;
    for(int i = 0; i < pf.size(); i++)
    {
        char ch = pf.at(i);
        switch (ch) 
        {
            case 'T':
            case 'F':
                pfStack.push(ch);
                break;
                
            case '!': 
            {
                char operand = pfStack.top();
                pfStack.pop();
                if (operand == 'T')
                    pfStack.push('F');
                if (operand == 'F')
                    pfStack.push('T');
                break;
            }
            case '&': // ch is a binary operator
            case '|':
            {
                char operand2 = pfStack.top();
                pfStack.pop();
                char operand1 = pfStack.top();
                pfStack.pop();
                
                if (ch == '&')
                {
                    if (operand1 == operand2)
                        pfStack.push(operand1);
                    else if(operand1 == 'F')
                        pfStack.push(operand1);
                    else
                        pfStack.push(operand2);
                }
                
                if(ch == '|')
                {
                    if (operand1 == operand2)
                        pfStack.push(operand1);
                    else if(operand1 == 'T')
                        pfStack.push(operand1);
                    else
                        pfStack.push(operand2);
                }
                
                break;
            }
                
            default:
                cerr << "invalid char passed into pf" << endl;
                exit(1);
                
        }
    }
    
    if (pfStack.top() == 'T')
        return true;
    else
        return false;
}


///////////////////////////////////////////////////////////////////////////
//  main function (COMMENT THE FUNCTION OUT BEFORE TURNING IT IN!!!!!!)
///////////////////////////////////////////////////////////////////////////

int main()
{
    string pf;
    bool answer;
    assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
    assert(evaluate("   T| F   ", pf, answer) == 0  &&  pf == "TF|"  &&  answer);
    assert(evaluate("T| F", pf, answer) == 0  &&  pf == "TF|"  &&  answer);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("T|", pf, answer) == 1);
    assert(evaluate("F F", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("()", pf, answer) == 1);
    assert(evaluate("()T", pf, answer) == 1);
    assert(evaluate("T(F|T)", pf, answer) == 1);
    assert(evaluate("T(&T)", pf, answer) == 1);
    assert(evaluate("(T&(F|F)", pf, answer) == 1);
    assert(evaluate("T+F", pf, answer) == 1);
    assert(evaluate("F  |  !F & (T&F) ", pf, answer) == 0
           &&  pf == "FF!TF&&|"  &&  !answer);
    assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
    assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
    cout << "Passed all tests" << endl;
}
