#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>


#define DEBUGMODE 1
#define pdebug(...) do{if(DEBUGMODE)printf(__VA_ARGS__);}while(0)

using namespace std;

vector <string> split(string str);
void printvec(vector<string> sorted);


class Node{
    public:
        string nodeName;
        vector<string> neighbours;

};

int main(int argc,char ** argv){
    int scenarios;
    int P,N;
    string dummy;
    string paper;
    ifstream myfile("erdos.txt", ifstream::in);
    myfile >> scenarios;
    myfile >> P;
    myfile >> N;//
    pdebug("Scenarios %d\n P %d\n N %d\n",scenarios,P,N);
    while(scenarios--){
        while(P--){
            getline(myfile,paper);
            vector<string> authors;
            size_t foundErdos;
            foundErdos = paper.find("Erdos");
            //cout << "Paper"<<paper << endl;
            if (paper!="")
                authors = split(paper);
            printvec(authors);
            cout << endl;
        }
    }
}

vector<string> split(string str){
    size_t start = 0;
    size_t found;
    found = str.find(".:");
    //cout << found << endl;
    str = str.substr(0,found);
    vector <string> subStrings;
    do {
        found = str.find(".,");
        //cout << found << endl;
        //cout << str.substr(0,found) << endl
        string author= str.substr(0,found);
        author = author.substr(author.find_first_not_of(" "),author.size());
        subStrings.push_back(author);
        str = str.substr(found+2,str.size()-1);
        //cout << str << endl;
    }while(found!=string::npos);
    return subStrings;
}


void printvec(vector<string> sorted){
    for(int i=0;i<sorted.size();i++){
        cout << sorted[i]<<endl;
    }

}



