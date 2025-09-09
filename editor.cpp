#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main(){
    string filename;
    cout<<"Enter the file name you wish to use: \n";
    cin>>filename;
    cin.ignore();
    fstream file(filename, ios::in | ios::out | ios::app);
    if(!file){
        file.open(filename,ios::out);
        file.close();
        file.open(filename,ios::in | ios::out | ios::app);
    }
    string line;
    cout<<"File "<<filename<<" Opened, Enter your text below, use '/end' if you want to stop writing"<<endl;
    while(true){
        getline(cin,line);
        if(line=="/end"){
            break;
        }
        file<<line<<endl;
    }
    file.close();
    cout<<"File has been saved and closed"<<endl;
    return 0;
}