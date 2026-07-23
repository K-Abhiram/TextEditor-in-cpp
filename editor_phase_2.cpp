#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <sstream>
using namespace std;

void fileExists(const string &filename){
    fstream f(filename,ios::in);
    if(!f){
        ofstream create(filename); //ofstream is used to create a file/add to a file
    }
}

//helper function to open and load a file, created to save space where multiple functions require file to be opened
vector<string> loadFile(const string &filename){
    vector<string> lines;
    ifstream file(filename);
    string line;
    while(getline(file,line)){
        lines.push_back(line);
    }

    file.close();
    return lines;
}


//helper function to save contents into the designated file.
void saveFile(const string &filename, const vector<string> &lines){
    ofstream file(filename,ios::trunc);
    for(const auto &line:lines){
        file<<line<<endl;
    }
    file.close();
}

//helper function to check whether a file is empty or not.
bool fileEmpty(const vector<string> &lines){
    return lines.empty();
}
void dispFile(const string &filename){
    vector<string> lines = loadFile(filename);
    if(lines.empty()){
        cout<<"File is empty."<<endl;
        return;
    }

    cout<<"\nDisplaying contents of file: "<<filename<<endl<<endl;
    for(int i=0;i<lines.size();i++){
        cout<<i+1<<": "<<lines[i]<<endl; 
    }
}
vector<string> readMultipleInput(){
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

//function to add more lines to a file.
void appendToFile(const string &filename){
    vector<string> fileContents = loadFile(filename);
    vector<string> newLines = readMultipleInput();
    for(const auto &line:newLines){
        fileContents.push_back(line);
    }
    saveFile(filename,fileContents);
    cout<<"Appended "<<newLines.size()<<" line(s) to file.\n"<<endl;
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
    vector<string> newLines = readMultipleInput();
    saveFile(filename,newLines);
    cout<<"File succesfully overwritten.\n"<<endl;
}

void deleteLine(const string &filename){
    vector<string> lines = loadFile(filename);
    if(lines.empty()){
        cout<<"File is empty."<<endl;
        return;
    } 

    cout<<"Enter the line number to delete (1-"<<lines.size()<<"): ";

    int linenum;
    cin>>linenum;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    if(linenum<1 || linenum > (int)lines.size()){
        cout<<"Invalid line number."<<endl;
        return;
    }

    lines.erase(lines.begin()+linenum-1);
    saveFile(filename,lines);

    cout<<"Line deleted successfully."<<endl;
}

//function to edit a line from the file and save the contents after editing
void editLine(const string&filename){
    vector<string> lines = loadFile(filename);
    if(lines.empty()){
        cout<<"File is empty."<<endl;
        return;
    }

    cout<<"Enter the line you wish to edit (1-"<<lines.size()<<"): ";

    int linenum;
    cin>>linenum;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    if(linenum<1 || linenum > (int)lines.size()){
        cout<<"Invalid line number."<<endl;
        return;
    }

    cout<<"Current text in line"<<endl;
    cout<<lines[linenum-1]<<endl;
    
    cout<<"Enter new text"<<endl;
    string newText;
    getline(cin,newText);

    lines[linenum-1]=newText;
    saveFile(filename,lines);

    cout<<"Line updated successfully."<<endl;
}

//searches for a given keyword in the file and returns the line number consisting of the keyword
void searchText(const string& filename){
    vector<string> lines = loadFile(filename);
    if(fileEmpty(lines)){
        cout<<"File is empty.\n"<<endl;
        return;
    }
    string keyword;
    cout<<"Enter text to search: ";
    getline(cin,keyword);

    bool found=false;
    int matches=0;

    cout<<"\n==========Search Results==========\n";
    for(int i=0;i<(int)lines.size();i++){
        if(lines[i].find(keyword)!=string::npos){
            cout<<"Lines "<<i+1<<": "<<lines[i]<<endl;
            found = true;
            matches++;
        }
    }

    if(!found){
        cout<<"No matches found."<<endl;
    }
    else cout<<"\nTotal Matches: "<<matches<<endl;
    cout<<"====================\n";
}

//Display statistics like line count, word count and character count of the file.
void fileStatistics(const string &filename){
    vector<string> lines = loadFile(filename);
    if(fileEmpty(lines)){
        cout<<"File is empty.\n";
        return;
    }
    int totalLines = lines.size();
    int totalWords = 0;
    int totalCharacters = 0;

    for(const auto &line: lines){
        totalCharacters += line.length();
        stringstream ss(line);
        string word;

        while(ss>>word){
            totalWords++;
        }
    }

    cout<<"========== FILE STATISTICS ===========\n";

    cout<<"Total lines\t: "<<totalLines<<endl;
    cout<<"Total words\t: "<<totalWords<<endl;
    cout<<"Total characters\t: "<<totalCharacters<<endl;

    cout<<"====================\n";

}

//find keyword in file and replace it with another word in a file.
void findAndReplace(const string& filename){
    vector<string> lines = loadFile(filename);
    if(fileEmpty(lines)){
        cout<<"File is empty.\n";
        return;
    }

    string findText, replaceText;
    cout<<"Enter text to find: ";
    getline(cin,findText);

    cout<<"Enter replacement text: ";
    getline(cin, replaceText);

    int replacements = 0;
    for(auto &line: lines){
        size_t pos = 0;
        while((pos=line.find(findText,pos))!=string::npos){
            line.replace(pos,findText.length(),replaceText);
            pos += replaceText.length();
            replacements++;
        }
    }
    saveFile(filename,lines);
    cout<<"\n"<<replacements<<" occurance(s) replaced\n";
}
//function to insert a new line of text to existing file.
void insertLine(const string &filename){
    vector<string> lines = loadFile(filename);
    cout<<"Enter position to insert (1-"<<lines.size()+1<<"): ";

    int pos;
    cin>>pos;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    if(pos<1 || pos>(int)lines.size()+1){
        cout<<"Invalid position."<<endl;
        return;
    }

    cout<<"Enter text: \n";
    string newLine;
    getline(cin,newLine);

    lines.insert(lines.begin()+pos-1,newLine);

    saveFile(filename,lines);
    cout<<"Line inserted successfully."<<endl;
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
        cout<<"5: Edit line\n";
        cout<<"6: Insert line\n";
        cout<<"7: Search Text in File\n";
        cout<<"8: Display file statistics\n";
        cout<<"9: Find & Replace\n";
        cout<<"10: Exit program\n";

        cout<<"Choose option between 1-10: \n";
        
        int x;
        //cin>>x;
        if(!(cin>>x)){
            cout<<"Invalid input. Please enter a number between 1 and 7\n";
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
                editLine(filename);
                break;
            case 6:
                insertLine(filename);
                break;
            case 7: 
                searchText(filename);
                break;
            case 8:
                fileStatistics(filename);
                break;
            case 9:
                findAndReplace(filename);
                break;
            case 10:
                cout<<"Exiting program\n";
                return 0;
            default:
                cout<<"Invalid choice. Choose between 1-8\n";
        }
    }
}
