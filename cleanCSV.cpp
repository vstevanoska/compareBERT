#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

int main() 
{
    ifstream fileToRead("archive\\LabeledText.csv");
    //ofstream fileToWrite("labeledTextClean.csv");

    string temp;
    string previousTemp;

    regex findStart("\\d+\\.txt,");
    regex findPolarity(",(positive|negative|neutral)");

    smatch m;

    bool skipNext = false;

    int fileCounter = 1;

    string filename;

    if (fileToRead.is_open()) {

        //we read the first line because it's redundant
        getline(fileToRead, temp);

        while (fileToRead) {

            getline(fileToRead, temp);

            if (!skipNext) {

                if (regex_search(temp, m, findStart))
                    temp.erase(0, temp.find_first_of(',') + 1);

                if (regex_search(temp, m, findPolarity)) {

                    temp.erase(m.position(), m.str().size());
                    
                    filename = "separatedText\\" + m.str().substr(1, m.str().size() - 1) + "\\" + to_string(fileCounter) + ".txt";

                    ofstream fileToWrite(filename);

                    fileToWrite << temp << endl;

                    fileToWrite.close();

                    fileCounter++;

                } else {
                    skipNext = true;

                    previousTemp = temp;
                }
            } else {

                if (regex_search(temp, m, findPolarity))
                    filename = "separatedText\\" + m.str().substr(1, m.str().size() - 1) + "\\" + to_string(fileCounter) + ".txt";

                ofstream fileToWrite(filename);

                fileToWrite << previousTemp << endl;

                fileToWrite.close();

                fileCounter++;

                skipNext = false;
            }
        }
    }

    fileToRead.close();

    cout << "Done\n";

    return 0;
}