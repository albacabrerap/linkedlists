//
// Created by Ary on 4/09/2026.
//


#include <stack>


class MyQueue {
    std::stack<int> front;
    std::stack<int> back;

    void transfer(){
        if(front.empty()){
            while(!back.empty()){
                front.push(back.top());
                back.pop();
            }
        }
    }

public:
    MyQueue() {}



    void push(int x) {
        back.push(x);
    }

    int pop() {
        transfer();
        int val = front.top();
        front.pop();
        return val;
    }

    int peek() {
        transfer();
        return front.top();
    }

    bool empty() {
        return (front.empty() && back.empty());
    }
};