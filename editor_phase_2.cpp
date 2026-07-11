#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

void fileExists(const string &filename){
    fstream f(filename,ios::in);
    if(!f){
        ofstream create(filename); //ofstream is used to create a file/add to a file
    }
}

void dispFile(const string &filename){
    ifstream file(filename); //ifstream is used to open a file in read mode, fails if the file is empty 
    if(!file){
        cout<<"Could not open file"<<endl;
        return;
    }
    string line;
    bool isThere=false;
    int linenum=1;
    cout<<"\n\n----------File contents -----------"<<endl;
    while(getline(file,line)){
        cout<<linenum++<<": "<<line<<endl;
        isThere = true;
    }
    if(isThere==false){
        cout<<"File is empty"<<endl;
    }
    cout<<"-------------------------------------\n\n"<<endl;
    file.close();
}
vector<string> ReadMultipleInput(){
    //Creates a function to read inputs and append into a vector, exit from vector if /end is used
    vector<string> lines;
    cout<<"\n\nEnter text. Type /end on a new line to finish"<<endl;
    string line;
    while(true){
        if(!getline(cin,line)){
            break;
        }
        if(line=="/end"){
            break;
        }
        lines.push_back(line);
    }
    return lines;
}
void appendToFile(const string &filename){
    ofstream file(filename, ios::app); //opens a output stream file in append only mode
    if(!file){
        cout<<"Error: cannot open file for editing"<<endl;
        return;
    }
    vector<string> lines = ReadMultipleInput();
    for(const auto &l:lines){ //append each datatype(auto in this case is String) to the vector
        file<<l<<endl;
    }
    cout<<"Appended "<<lines.size()<<" line(s) to text file";
}

void overwriteFile(const string &filename){
    //asks user if they want to overwrite, if yes then clears the whole file and asks user to append again
    cout<<"Are you sure you want to overwrite the file? Y/N"<<endl;
    string ans;
    getline(cin, ans);
    if(ans!="y" && ans!="Y"){
        cout<<"Overwrite aborted\n";
        return;
    }
    ofstream file(filename,ios::trunc); // trunc stands for truncate, clears the existing file
    if(!file){
        cout<<"Error: cannot open file\n";
        return;
    }
    vector<string> lines = ReadMultipleInput();
    for(const auto &l:lines){
        file<<l<<endl;
    }
    cout<<"File overwritten with "<<lines.size()<<" lines(s)\n";
}

void deleteLine(const string &filename){
    ifstream file(filename);
    if(!file){
        cout<<"Error: could not open file"<<endl;
        return;

    }
    vector<string> lines;
    string line;
    while(getline(file,line)){
        lines.push_back(line);
    }
    file.close();

    if(lines.empty()){
        cout<<"File is empty"<<endl;
        return;
    }

    cout<<"Enter the line number you wish to delete: 1-"<<lines.size()<<"\n";
    int x;
    cin>>x;

    if(x<1 || x>(int)lines.size()){
        cout<<"Invalid numbers";
        cin.ignore(numeric_limits<streamsize>::max(),'\n'); //clears buffer
        return;
    }
    ofstream out(filename,ios::trunc);
    for(int i=0;i<(int)lines.size();i++){
        if(i+1 != x){
            out<<lines[i]<<endl;
        }
    }
    out.close();
    cout<<"Line "<<x<<" deleted successfully";
}
int main(){
    string filename;
    cout<<"Enter the file name you wish to use: \n";
    cin>>filename;
    if(filename.empty()){
        cout<<"No filename provided. Exiting program\n";
        return 0;
    }
    fileExists(filename);
    while(true){
        cout<<"\n -------Text Editor Menu-------\n";
        cout<<"1: Display file contents\n";
        cout<<"2: Append text into a file\n";
        cout<<"3: Overwrite exising file completely\n";
        cout<<"4: Delete line\n";
        cout<<"5: Exit program\n";
        cout<<"Choose option between 1-5: \n";
        
        int x;
        //cin>>x;
        if(!(cin>>x)){
            cout<<"Invalid input. Please enter a number between 1 and 4\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); //ignore everything until the newline character \n
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(),'\n'); 

        switch(x){
            case 1:
                dispFile(filename);
                break;
            case 2:
                appendToFile(filename);
                break;
            case 3:
                overwriteFile(filename);
                break;
            case 4:
                deleteLine(filename);
                break;
            case 5:
                cout<<"Exiting program\n";
                return 0;
            default:
                cout<<"Invalid choice. Choose between 1-4\n";
        }
    }
}
