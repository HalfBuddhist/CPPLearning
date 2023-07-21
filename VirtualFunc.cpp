//
// Created by Qingwei on 16/6/14.
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

class Book {
protected:
    string title;
    string author;
public:
    Book(string t, string a) {
        title = t;
        author = a;
    }

    virtual void display() const = 0;
};

class MyBook : public Book {
protected:
    int price;
public:
    MyBook(string t, string a, int p) : Book(t, a), price(p) { };

    void display() const {
        cout << "Title: " << this->title << endl;
        cout << "Author: " << this->author << endl;
        cout << "Price: " << this->price << endl;
    }
};


int TestVirtualFunc() {
    string title, author;
    int price;
    getline(cin, title);
    getline(cin, author);
    cin >> price;
    MyBook novel(title, author, price);
//    Book *a = new MyBook(title, author, price);
//    a->display();
//    Book *a = &novel;
//    Book a(title, author);
    novel.display();
    return 0;
}
