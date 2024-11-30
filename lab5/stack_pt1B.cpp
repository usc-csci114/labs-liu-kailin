#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// helper function to find matching opening bracket
char findMatch(char c){
    if (c == ')') {
        return '(';
    }
    else if (c == ']') {
        return '[';
    }
    else if (c == '}') {
        return '{';
    }
    else if (c == '>') {
        return '<';
    }
}

// main
int main()
{
    cout << "PART 1B : MATCHING DELIMITERS" << endl;
    
    string entry;
    
    cout << "Enter a string containing only (), {}, [], <> and whitespace" << endl
    cout << "EXAMPLE: ({<>[()}]) " << endl;
    
    getline(cin, entry);
    
    stack<char> brackets;
    
    for(size_t i=0; i< entry.length(); i++){ // step through entry
        char current = entry[i];
        
        if (current == ' '){ // skip whitespace
            continue;
        }
        
        // compare if opening or closing brackets
        // opening bracket
        if(current == '(' || current == '{' || current == '[' || current == '<') {
            brackets.push(current); // push onto stack
        }
        // closing bracket
        else if (current == ')' || current == '}' || current == ']' || current == '>') {
            
            if (brackets.empty()){ // special case where there is an error in the sequence
                cout << "Error. Found '" << current << "' at position " << i;
                cout << ", expecting any open." << endl;
                return 1;
            }
            
            char top_item = brackets.top(); // store top item of stack
            
            if (top_item != findMatch(current)){ // compare top item with current
                cout << "Error. Found '" << current << "' at position " << i;
                cout << ", expecting " << findMatch(current) << endl;
                return 1;
            }
            
            brackets.pop(); // pop top so next can be analyzed
        }
    }
    
    // if reach end of entry and stack isn't empty, there is a mismatch
    if (!brackets.empty()){
        cout << "Error. Unmatched open parens/brackets." << endl;
        return 1;
    }
    
    cout << "The entry sequence matches" << endl;
    
    return 0;
}
