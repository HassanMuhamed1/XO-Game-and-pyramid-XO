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

    bool contains(T element) {
        auto it = find(s.begin(), s.end(), element);
        return (it != s.end());
    }

    int Count(T element) {
        return count(s.begin(), s.end(), element);
    }

    T* ToArray() const {
        T* array = new T[s.size()];
        std::copy(s.begin(), s.end(), array);
        return array;
    }
    bool operator == (Set & s1);
    bool operator != (Set & s1);

    ~Set() {
        delete[] ToArray();
    }
};

template<class T>
bool Set<T>::operator!=(Set &s1) {
    if(s1.Size() != s.size()){
        return true ;
    }
    else {
        return false ;
    }
}

template<class T>
bool Set<T>::operator ==(Set &s1) {
    if(s1.Size() == s.size()){
        return true;
    }
    else{
        return false;
    }

}

int main() {
    Set<string> s1 , s2;
    s1.Push("Hassan");
    s1.Push("Muhammed");
    s1.Push("Hassan");
    s1.Push("Muhammed");
    s1.Push("Sona");
    cout << "Size of s : " << s1.Size() << endl;
    cout << "Is 3 in s1? " << s1.contains("Hassan") << endl;
    cout << "Count of 1 in s1: " << s1.Count("Muhammed") << endl;
    cout << "Count of 1 in s1: " << s1.Count("Hassan") << endl;
    cout<< "number 3 is deleted "<<endl;
    s1.Remove("Hassan");
    cout<<s1.contains("Hassan");
    if(s1 == s1){
        cout<<"s1 equal to s2"<<endl;
    }else if(s1 != s1){
        cout<<"s1 not equal to s2"<<endl;
    }
    return 0;
}
