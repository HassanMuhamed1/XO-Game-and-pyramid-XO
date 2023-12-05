// problem-1
#include <iostream>
#include <fstream>
using namespace std;

class LabelGenerator{
protected:
    string prefix;
    int initial;
public:
    LabelGenerator(string p , int i): prefix(p) , initial(i){}

    virtual string nextLabel(){
        return prefix + to_string(initial++);
    };
};

class FileLabelGenerator : public LabelGenerator{
protected:
    string Filename;
    ifstream Filestream;
public:
    FileLabelGenerator(string& prefix,int initial , string& file ) : LabelGenerator(prefix , initial) , Filename(file){
        Filestream.open(file);
    }
    ~FileLabelGenerator(){
        Filestream.close();
    }
    string nextLabel() override {
        string otherline;
        if (Filestream >> otherline) {
            return LabelGenerator::nextLabel() + " " + otherline;
        } else {
            return LabelGenerator::nextLabel();
        }
    };
};

int main(){
    LabelGenerator FigureNumbers("Figure" , 1);
    LabelGenerator Pointnumbers ("P" , 0);
    cout<<"Figrue numbers: ";
    for (int i = 0; i < 3; ++i) {
        cout<<FigureNumbers.nextLabel() <<", ";
    }
    cout<<"\n"<<"Point numbers: ";
    for (int i = 0; i < 5; ++i) {
        cout<< Pointnumbers.nextLabel()<<", ";
    }
    cout<<"\n" << "More figures: ";
    for (int i = 0; i < 3; ++i) {
        cout<<FigureNumbers.nextLabel()<<", ";
    }
    cout<<endl;
    //=====================================================
    /*FileLabelGenerator figureLabels("Figure" ,1 , "Label.txt");
    cout<<"Figure Labels: \n";
    for(int i=0 ; i<3 ; i++){
        cout<<figureLabels.nextLabel()<<endl;
    }*/
    return 0;
}
//===================================================================================================
// Probem 3
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <cctype>
using namespace std;
string Clean(string& word) {
    string cleanedWord;
    for (char c : word) {
        if (isalnum(c) || c == '-') {
            cleanedWord += tolower(c);
        }
    }
    return cleanedWord;
}


int main(){
    string filename;

    cout << "Enter the name of the text file: ";
    cin >> filename;

    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error opening the file." <<endl;
        return 1;
    }

    map<string, int> FrequencyTable;

    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string word;

        while (iss >> word) {
            string cleanedWord = Clean(word);
            if (!cleanedWord.empty()) {
                FrequencyTable[cleanedWord]++;
            }
        }
    }

    inputFile.close();

    cout << "Frequency Table:\n";
    for (const auto& pair : FrequencyTable) {
        cout << pair.first << ": " << pair.second << endl;
    }
    return 0;
}
//==============================================
// problem 4
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template<class T>
class Set {
private:
    vector<T> s;
public:
    void Push(T element) {
        if (count(s.begin(), s.end(), element) == 0) {
            s.push_back(element);
        }
       sort(s.begin(),s.end());
    }

    void Remove(T element) {
        auto it = find(s.begin(), s.end(), element);
        if (it != s.end()) {
            s.erase(it);
        }
    }

    int Size() {
        return s.size();
    }
    int print(){
        for (int i = 0; i < s.size(); ++i) {
            cout<<s[i];
        }
    }


    bool contains(T element) {
        auto it = find(s.begin(), s.end(), element);
        return (it != s.end());
    }

    T* ToArray() const {
        T* array = new T[s.size()];
        copy(s.begin(), s.end(), array);
        return array;
    }
    bool operator == (Set & s1);
    bool operator != (Set & s1);
    T operator [](int i);

    ~Set() {
        delete[] ToArray();
    }
};

template<class T>
T Set<T>::operator[](int i) {
    return s[i];
}

template<class T>
bool Set<T>::operator!=(Set &s1) {
    if (s.size() != s1.Size()) {
        return true;
    } else {
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] != s1[i]) {
                return true;
            }
        }
        return false;
    }
}

template<class T>
bool Set<T>::operator==(Set &s1) {
    if (s.size() == s1.Size()) {
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] != s1[i]) {
                return false;
            }
        }
        return true;
    } else {
        return false;  
    }
}



int main() {
    Set<int> s , s1;
    s.Push(1);
    s.Push(5);
    s.Push(3);
    s.Push(6);
    s.Push(7);
// 13567
// 13568
    s1.Push(1);
    s1.Push(5);
    s1.Push(3);
    s1.Push(6);
    s1.Push(8);
    if(s == s1){
        cout<<"is equal";
    }
    else if( s != s1){
        cout<<"is not equal";
    }
    return 0;
}
//===============================================================
// problem 6
#include <iostream>
#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;
class Universe {
private:
    static const int Rows = 30;
    static const int columns = 30;
public:
    int cell[Rows][columns]={0};
    void initialize();
    void reset();
    int count_neighbors(int row, int col);
    void next_neighbors();
    void display();
    void run(Universe& u);
    static const int directions[8][2];
};

void Universe::initialize() {
    for(int i =0 ; i < Rows ; i++){
        for (int j = 0; j < columns; ++j){
            cell[14][14] = 1;
            cell[15][15] = 1;
            cell[16][15] = 1;
            cell[16][14] = 1;
            cell[16][13] = 1;
        }
    }
}
void Universe::reset() {
    memset(cell, 0, sizeof(cell));
}
const int Universe::directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},            {0, 1},
        {1, -1}, {1, 0}, {1, 1}
};
int Universe::count_neighbors(int row, int col) {
    int count = 0;

    for (int d = 0; d < 8; ++d) {
        int newRow = row + directions[d][0];
        int newCol = col + directions[d][1];

        if (newRow >= 0 && newRow < Rows && newCol >= 0 && newCol < columns) {
            count += cell[newRow][newCol];
        }
    }

    return count;
}

void Universe::next_neighbors() {
    int nextCell[Rows][columns];

    for (int i = 0; i < Rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            int neighbors = count_neighbors(i, j);

            if (cell[i][j] == 1) {
                nextCell[i][j] = (neighbors < 2 || neighbors > 3) ? 0 : 1;
            } else {
                nextCell[i][j] = (neighbors == 3) ? 1 : 0;
            }
        }
    }
    memcpy(cell, nextCell, sizeof(cell));
}
void Universe::display() {
    for (int i = 0; i < Rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            cout << (cell[i][j] ? "X" : ".")<<" ";
        }
        cout <<endl;
    }

}
void Universe::run(Universe& u) {
    u.initialize();
    for (int i = 0; i < 2; ++i) {
        {
            display();
            next_neighbors();
            cout<<endl << "================================================"<<endl;
        }
    }
    u.reset();
}

int main() {
    Universe u;
    u.run(u);

    return 0;
}
