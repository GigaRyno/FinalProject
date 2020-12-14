#include "pbPlots.hpp" //used for making graphs
#include "supportLib.hpp" //used for making graphs
#include <graph_utils.h>
#include <unistd.h> //used for getopt
#include <iostream>
#include <sstream>


using namespace std;

vector<double> x{}; //Time
vector<double> y{}; //What ever you choose

double processCSV(std::ifstream &inFile, std::string Opt); //Definition

int main(int argc, char *argv[])
{
    RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();

    int option;
    bool rpmFlag = false;
    bool boostFlag = false;
    bool optError = true;
    bool oilFlag = false;
    bool tranFlag = false;

    string menuOption;


    string fileName;
    string filler = "This is a Filler String";

    double RPMS;

    //My goal was to have select the thing u wanted to view when passing in the file
    while((option = getopt(argc, argv, "o:r:b:t:")) != EOF)
    {
        //to simplifiy you can only choose 1 thing at a time.
        //example: the graph would be what ever you choose over time for readability
        switch(option)
        {
            case 'o'://oil Temp
                oilFlag = true;
                fileName = optarg;
                menuOption = "oil";
                break;
            case 'r'://RPM
                rpmFlag = true; //Sets it true so it will choose that option
                fileName = optarg;
                menuOption = "rpm";
                break;
            case 'b'://Boost
                boostFlag = true; //Same thing as above
                fileName = optarg;
                menuOption = "boost";
                break;
            case 't':
                tranFlag = true;
                fileName = optarg;
                menuOption = "trans";
                break;
            default:
                optError = true;
                break;
        }
    }

    if(rpmFlag || boostFlag || tranFlag || oilFlag) {
        if(fileName.empty())
        {
            cout << "Error: Filename not set!" << endl;
        }
        else
        {
            ifstream inFile;
            inFile.open(fileName);
            if(inFile)
            {
                processCSV(inFile, menuOption);
                inFile.close();
                DrawScatterPlot(imageRef, 600, 400, &x, &y);
                vector<double> *pngData = ConvertToPNG(imageRef->image);
                WriteToFile(pngData, "graph.png");
                DeleteImage(imageRef->image);             
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
    }

    return optError;
}


//I had problems getting the data after reading the file when in another file so it is in here now and works fine.
double processCSV(std::ifstream &inFile, std::string Opt)
{
    //All the strings below are different things that are data logged while datalogging a car.  
    // it got to long for one line because I have 32 different things that it records. so for reading it I made it 2 lines fo strings
   string time, calcLoad, clFuelTarget, commFuelFinal, transTemp, dam, feedBackKnock, fineKnockLearn, fuelPres, fuelPressureTarget, rpm, throttlePos, wasteGateDuty, strLine;
   string gear, intakeManifoldTemp, mafCorr, boost, oilTemp, reqTQ, tdBoostError, tgvMapRatio, afCorrection, afLearning, afSen, pedalPos, baroPressure, coolantTemp, ignitionTiming, injDutyCycle, intakeTemp, mafVolt;
   stringstream s_stream;

   int linesParsed = 0;

   if (inFile)
   {
      getline(inFile, strLine);
      while (getline(inFile, strLine))
      {
        s_stream.str(strLine);
        getline(s_stream, time, ',');
        getline(s_stream, calcLoad, ',');
        getline(s_stream, clFuelTarget, ',');
        getline(s_stream, commFuelFinal, ',');
        getline(s_stream, transTemp, ',');
        getline(s_stream, dam, ',');
        getline(s_stream, feedBackKnock, ',');
        getline(s_stream, fineKnockLearn, ',');
        getline(s_stream, fuelPres,',');
        getline(s_stream, fuelPressureTarget, ',');
        getline(s_stream, gear, ',');
        getline(s_stream, intakeManifoldTemp, ',');
        getline(s_stream, mafCorr, ',');
        getline(s_stream, boost, ',');
        getline(s_stream, oilTemp, ',');
        getline(s_stream, reqTQ, ',');
        getline(s_stream, tdBoostError, ',');
        getline(s_stream, tgvMapRatio, ',');
        getline(s_stream, afCorrection, ',');
        getline(s_stream, afLearning, ',');
        getline(s_stream, afSen, ',');
        getline(s_stream, pedalPos, ',');
        getline(s_stream, baroPressure, ',');
        getline(s_stream, coolantTemp, ',');
        getline(s_stream, ignitionTiming, ',');
        getline(s_stream, injDutyCycle, ',');
        getline(s_stream, intakeTemp, ',');
        getline(s_stream, mafVolt, ',');
        getline(s_stream, rpm, ',');
        getline(s_stream, throttlePos, ',');
        getline(s_stream, wasteGateDuty, ',');
         if(Opt == "rpm")
         {
            double times = stod(time);
            double RPMS = stod(rpm);
            x.push_back(times);
            y.push_back(RPMS);
            
         } 
         else if(Opt == "boost")
         {
             double times = stod(time);
             double Boosts = stod(boost);
             x.push_back(times);
             y.push_back(Boosts);
         } 
         else if(Opt == "trans")
         {
            double times = stod(time);
            double TransTemp = stod(transTemp);
            x.push_back(times);
            y.push_back(TransTemp);
            
         } 
         else if(Opt == "oil")
         {
             double times = stod(time);
             double tempOil = stod(oilTemp);
             x.push_back(times);
             y.push_back(tempOil);
         } 
         else
         {
             cout << "No Selection" << endl;
         }
        linesParsed++;
      }
   }  
   return linesParsed; 
}