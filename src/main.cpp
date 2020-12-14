/**
 * @file main.cpp
 * @author Ryan LaVigne
 * @brief Read a csv file and convert data to a graph
 * @date 12-11-2020
 */

#include "pbPlots.hpp" //used for making graphs
#include "supportLib.hpp" //used for making graphs
#include <graph_utils.h>
#include <unistd.h> //used for getopt
#include <iostream>
#include <sstream>


using namespace std;

vector<double> x{}; //Time
vector<double> y{}; //What ever you choose

void processCSV(std::ifstream &inFile, std::string Opt); //Definition

int main(int argc, char *argv[])
{
    RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();

    int option;

    bool optError = true;

    //Instead of doing the full 32 I chose to do the most important 10
    bool rpmFlag = false;
    bool boostFlag = false;
    bool oilFlag = false;
    bool tranFlag = false;
    bool fuelFlag = false;
    bool manifoldFlag = false;
    bool tqFlag = false;
    bool airFlag = false;
    bool coolFlag = false;
    bool ignitionFlag = false;

    string menuOption;
    string fileName;

    //My goal was to have select the thing u wanted to view when passing in the file
    while((option = getopt(argc, argv, "o:r:b:t:f:m:q:a:c:i:")) != EOF)
    {
        //to simplifiy you can only choose 1 thing at a time.
        //example: the graph would be what ever you choose over time for readability
        switch(option)
        {
            case 'o'://Oil Temp
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
            case 't'://Trans Temp
                tranFlag = true;
                fileName = optarg;
                menuOption = "trans";
                break;
            case 'f'://Fuel Pressure
                fuelFlag = true;
                fileName = optarg;
                menuOption = "fuel";
                break;
            case 'm'://intake manifold temp
                manifoldFlag = true; 
                fileName = optarg;
                menuOption = "man";
                break;
            case 'q'://torque
                tqFlag = true; 
                fileName = optarg;
                menuOption = "tq";
                break;
            case 'a'://AF Sens 1
                airFlag = true;
                fileName = optarg;
                menuOption = "air";
                break;
            case 'c'://Coolant Temp
                coolFlag = true; 
                fileName = optarg;
                menuOption = "cool";
                break;
            case 'i': //Ignition Timing
                ignitionFlag = true;
                fileName = optarg;
                menuOption = "ign";
                break;
            default:
                optError = true;
                break;
        }
    }

    if(rpmFlag || boostFlag || oilFlag || tranFlag || fuelFlag || manifoldFlag || tqFlag || airFlag || coolFlag || ignitionFlag) {
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
                cout << "Graph Made" << endl;     
                //printVector(x); //Shows vectors to figure out what is wrong
                //printVector(y); //Shows vectors to figure out what is wrong 
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
void processCSV(std::ifstream &inFile, std::string Opt)
{
    //All the strings below are different things that are data logged while datalogging a car.  
    // it got to long for one line because I have 32 different things that it records. so for reading it I made it 2 lines fo strings
   string time, calcLoad, clFuelTarget, commFuelFinal, transTemp, dam, feedBackKnock, fineKnockLearn, fuelPres, fuelPressureTarget, rpm, throttlePos, wasteGateDuty, strLine;
   string gear, intakeManifoldTemp, mafCorr, boost, oilTemp, reqTQ, tdBoostError, tgvMapRatio, afCorrection, afLearning, afSen, pedalPos, baroPressure, coolantTemp, ignitionTiming, injDutyCycle, intakeTemp, mafVolt;
   stringstream s_stream;

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
         else if(Opt == "fuel")
         {
             double times = stod(time);
             double fuelPre = stod(fuelPres);
             x.push_back(times);
             y.push_back(fuelPre);
         } 
         else if(Opt == "man")
         {
             double times = stod(time);
             double man = stod(intakeManifoldTemp);
             x.push_back(times);
             y.push_back(man);
         } 
         else if(Opt == "tq")
         {
             double times = stod(time);
             double torque = stod(reqTQ);
             x.push_back(times);
             y.push_back(torque);
         } 
         else if(Opt == "air")
         {
             double times = stod(time);
             double af = stod(afSen);
             x.push_back(times);
             y.push_back(af);
         } 
         else if(Opt == "cool")
         {
             double times = stod(time);
             double cool = stod(coolantTemp);
             x.push_back(times);
             y.push_back(cool);
         } 
         else if(Opt == "ign")
         {
             double times = stod(time);
             double ign = stod(ignitionTiming);
             x.push_back(times);
             y.push_back(ign);
         } 
         else
         {
             cout << "No Selection" << endl;
         }
      }
   }  
}