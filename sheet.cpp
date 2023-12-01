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
