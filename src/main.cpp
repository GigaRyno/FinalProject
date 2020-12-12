#include <graph_utils.h>
#include <unistd.h> //used for getopt
#include <iostream>


using namespace std;

int main(int argc, char *argv[])
{
    int option;
    bool rpmFlag = false;
    bool boostFlag = false;
    bool optError = true;
    string fileName;
    string filler = "This is a Filler String";

    //My goal was to have select the thing u wanted to view when passing in the file
    while((option = getopt(argc, argv, "o:r:b:")) != EOF)
    {
        //to simplifiy you can only choose 1 thing at a time.
        //example: the graph would be what ever you choose over time for readability
        switch(option)
        {
            case 'o':
            cout << "Test of O" << endl;
                break;
            case 'r'://RPM
                rpmFlag = true; //Sets it true so it will choose that option
                fileName = optarg;
                //cout << "DEBUG: Setting RPM Flag" << endl; 
                break;
            case 'b'://Boost
                boostFlag = true; //Same thing as above
                fileName = optarg;
                //cout << "DEBUG: Setting Boost Flag" << endl;
                break;
            default:
                optError = true;
                break;
        }
    }

    if(rpmFlag) {
        cout << "RPM FLAG SET" << endl;
        if(fileName.empty())
        {
            cout << "Error: Filename not set!" << endl;
        }
        else
        {
            ifstream inFile;
            inFile.open(fileName);
            //cout << "Opening File: " << fileName << endl;
            if(inFile)
            {
                //cout << "In File" << endl;
                int linesParsed = processCSV(inFile, fileName + ".txt", filler);
                inFile.close();
                if(linesParsed)
                {
                    cout << "Lines Parsed: " << linesParsed << endl;
                    optError = false;
                }
                else
                {
                    optError = true;
                }
            }
            else
            {
                cout << "Can't Open File" << endl;
                optError = true;
            }
        }
    }
    else if(boostFlag)
    {
        cout << "Boost Flag Set!" << endl;
        if(fileName.empty())
        {
            cout << "Error: Filename not set!" << endl;
        }
        else
        {
            ifstream inFile;
            inFile.open(fileName);
            //cout << "Opening File: " << fileName << endl;
            if(inFile)
            {
                //cout << "In File" << endl;
                int linesParsed = processCSV(inFile, fileName + ".txt", filler);
                inFile.close();
                if(linesParsed)
                {
                    cout << "Lines Parsed: " << linesParsed << endl;
                    optError = false;
                }
                else
                {
                    optError = true;
                }
            }
            else
            {
                cout << "Can't Open File" << endl;
                optError = true;
            }
        }
    }
    else
    {
        cout << "Error: Arguments Not Set!" << endl;
        optError = true;
    }

    if(optError)
    {
        return EXIT_FAILURE;
        //cout << "ERRRRORRRRR" << endl;
    }

    //cout << "fileName: " << fileName << endl;
    //cout << "optError: " << optError << endl;

    return optError;
}