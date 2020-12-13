/**
 * @file graph_utils.cpp
 * @author Ryan LaVigne
 * @brief Final Project
 * @date 12-11-2020
 * @credit Lab10.2 modified to work
 */

#include <graph_utils.h>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

int processCSV(std::ifstream &inFile, std::string FileName)
{
    //All the strings below are different things that are data logged while datalogging a car.  
    // it got to long for one line because I have 32 different things that it records. so for reading it I made it 2 lines fo strings
   string time, calcLoad, clFuelTarget, commFuelFinal, transTemp, dam, feedBackKnock, fineKnockLearn, fuelPres, fuelPressureTarget, rpm, throttlePos, wasteGateDuty, strLine;
   string gear, intakeManifoldTemp, mafCorr, boost, oilTemp, reqTQ, tdBoostError, tgvMapRatio, afCorrection, afLearning, afSen, pedalPos, baroPressure, coolantTemp, ignitionTiming, injDutyCycle, intakeTemp, mafVolt;
   stringstream s_stream;

   int linesParsed = 0;

   if (inFile)
   {
      ofstream CSVFile(FileName);

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
        linesParsed++;
      }
   }  
   return linesParsed; 
}