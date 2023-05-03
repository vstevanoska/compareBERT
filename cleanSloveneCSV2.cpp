#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

int main() 
{
    ifstream fileToRead("slobert\\dataset.csv");
    //ofstream fileToWrite("labeledTextClean.csv");

    string temp;
    string previousTemp;

    regex findPolarity(",(Positive|Negative|Neutral)");

    smatch m;

    bool skipNext = false;

    int fileCounter = 1;

    string filename;

    if (fileToRead.is_open()) {

        while (fileToRead) {

            getline(fileToRead, temp);

            if (regex_search(temp, m, findPolarity)) {

                temp.erase(m.position(), m.str().size());

                //cout << temp << endl;
                
                filename = "separatedSloveneText\\" + m.str().substr(1, m.str().size() - 1) + "\\" + to_string(fileCounter) + ".txt";

                //cout << filename << endl;

                ofstream fileToWrite(filename);

                fileToWrite << temp << endl;

                fileToWrite.close();

                fileCounter++;

            } 
        }
    }

    fileToRead.close();

    cout << "Done\n";

    return 0;
}