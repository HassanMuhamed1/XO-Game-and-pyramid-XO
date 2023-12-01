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
