//
// Created by Qingwei on 16/6/13.
//

#include <iostream>
#include <vector>

using namespace std;


class Person {
protected:
    string firstName;
    string lastName;
    int id;
public:
    Person(string firstName, string lastName, int identification) {
        this->firstName = firstName;
        this->lastName = lastName;
        this->id = identification;
    }

    void printPerson() {
        cout << "Name: " << lastName << ", " << firstName << "\nID: " << id << "\n";
    }

};

class Student : public Person {
private:
    vector<int> testScores;
public:
    // Write your constructor
    Student(string firstName, string lastName, int id, vector<int> scores) : Person(firstName, lastName, id),
                                                                             testScores(scores) { }

    // Write char calculate()
    char calculate() {
        int sum(0);
        for (vector<int>::iterator it = testScores.begin(); it < testScores.end(); it++) {
            sum += *it;
        }

        double avg(testScores.size() ? sum * 1.0 / testScores.size() : 0);

        if (avg >= 90) return 'O';
        else if (avg >= 80) return 'E';
        else if (avg >= 70) return 'A';
        else if (avg >= 55) return 'P';
        else if (avg >= 40) return 'D';
        else return 'T';
    }
};

int TestInheritance() {
    string firstName;
    string lastName;
    int id;
    int numScores;
    cin >> firstName >> lastName >> id >> numScores;
    vector<int> scores;
    for (int i = 0; i < numScores; i++) {
        int tmpScore;
        cin >> tmpScore;
        scores.push_back(tmpScore);
    }
    Student *s = new Student(firstName, lastName, id, scores);
    s->printPerson();
    cout << "Grade: " << s->calculate() << "\n";
    return 0;
}