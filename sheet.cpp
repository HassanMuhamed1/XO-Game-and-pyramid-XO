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
/*
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>  // For sleep function

using namespace std;

const int rows = 20;
const int cols = 50;

// Function to initialize the grid with random initial state
void initializeGrid(vector<vector<int>>& grid) {
    srand(time(nullptr));
    for (int i = 0; i < rows; ++i) {
        vector<int> row;
        for (int j = 0; j < cols; ++j) {
            row.push_back(rand() % 2);
        }
        grid.push_back(row);
    }
}

// Function to display the current state of the grid
void displayGrid(const vector<vector<int>>& grid) {
    for (const auto& row : grid) {
        for (int cell : row) {
            cout << (cell == 1 ? "." : "*") << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

// Function to get the number of live neighbors for a given cell
int countLiveNeighbors(const vector<vector<int>>& grid, int i, int j) {
    int count = 0;
    for (int x = max(0, i - 1); x < min(rows, i + 2); ++x) {
        for (int y = max(0, j - 1); y < min(cols, j + 2); ++y) {
            if (!(x == i && y == j)) {
                count += grid[x][y];
            }
        }
    }
    return count;
}

// Function to update the grid based on the rules of the Game of Life
void updateGrid(vector<vector<int>>& grid) {
    vector<vector<int>> newGrid = grid;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int liveNeighbors = countLiveNeighbors(grid, i, j);

            if (grid[i][j] == 1) {
                if (liveNeighbors < 2 || liveNeighbors > 3) {
                    newGrid[i][j] = 0;
                }
            } else {
                if (liveNeighbors == 3) {
                    newGrid[i][j] = 1;
                }
            }
        }
    }

    grid = newGrid;
}

int main() {
    vector<vector<int>> grid;

    initializeGrid(grid);

    for (int generation = 1; generation <= 50; ++generation) {
        cout << "Generation " << generation << ":" << endl;
        displayGrid(grid);
        sleep(1);  // Optional: add a delay for better visualization
        updateGrid(grid);
    }

    return 0;
}
*/
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
