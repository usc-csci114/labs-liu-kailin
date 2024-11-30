#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main(int argc, char* argv[])
{
    cout << "PART 1A : NUMBER ORDERS" << endl;
    
    vector<int> numbers;
    int entry;
    int size = 0;
    
    cout << "Enter integers separated by spaces or lines" << endl
    cout << "Press ctrl-d to end)" << endl;
    
    while (cin >> entry){
        numbers.push_back(entry);
        size++;
    }
    
    cout << "Vector in entry order" << endl;
    for (size_t i =0; i < size; i++){
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    cout << "Vector in reverse order (using stack)" << endl;
    stack<int> reverse;
    for (size_t i =0; i < size; i++){
        reverse.push(numbers[i]);
    }
    while(reverse.empty() == FALSE){
        cout << reverse.top() << " ";
        reverse.pop();
    }
    cout << endl;
    
    
    
    
    return 0;
}
