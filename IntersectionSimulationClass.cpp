#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "IntersectionSimulationClass.h"
#include "random.h"

void IntersectionSimulationClass::readParametersFromFile(
     const string &paramFname
     )
{
  bool success = true;;
  ifstream paramF;

  paramF.open(paramFname.c_str());

  //Check that the file was able to be opened...
  if (paramF.fail())
  {
    success = false;
    cout << "ERROR: Unable to open parameter file: " << paramFname << endl;
  }
  else
  {
    //Now read in all the params, according to the specified format of
    //the text-based parameter file.
    if (success)
    {
      paramF >> randomSeedVal;
      if (paramF.fail() ||
          randomSeedVal < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set random generatsor seed" << endl;
      }
    }

    if (success)
    {
      paramF >> timeToStopSim;
      if (paramF.fail() ||
          timeToStopSim <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set simulation end time" << endl;
      }
    }

    if (success)
    {
      paramF >> eastWestGreenTime >> eastWestYellowTime;
      if (paramF.fail() ||
          eastWestGreenTime <= 0 ||
          eastWestYellowTime <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set east-west times" << endl;
      }
    }

    if (success)
    {
      paramF >> northSouthGreenTime >> northSouthYellowTime;
      if (paramF.fail() ||
          northSouthGreenTime <= 0 ||
          northSouthYellowTime <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set north-south times" << endl;
      }
    }

    if (success)
    {
      paramF >> eastArrivalMean >> eastArrivalStdDev;
      if (paramF.fail() ||
          eastArrivalMean <= 0 ||
          eastArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set east arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> westArrivalMean >> westArrivalStdDev;
      if (paramF.fail() ||
          westArrivalMean <= 0 ||
          westArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set west arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> northArrivalMean >> northArrivalStdDev;
      if (paramF.fail() ||
          northArrivalMean <= 0 ||
          northArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set north arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> southArrivalMean >> southArrivalStdDev;
      if (paramF.fail() ||
          southArrivalMean <= 0 ||
          southArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set south arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> percentCarsAdvanceOnYellow;
      if (paramF.fail() || 
          percentCarsAdvanceOnYellow < 0 ||
          percentCarsAdvanceOnYellow > 100)
      {
        success = false;
        cout << "ERROR: Unable to read/set percentage yellow advance" << endl;
      }

      //Use the specified seed to seed the random number generator
      setSeed(randomSeedVal);
    }

    paramF.close();
  }

  //Let the caller know whether things went well or not by printing the
  if (!success)
  {
    cout << "ERROR: Parameter file was NOT read in successfully, so the " <<
            "simulation is NOT setup properly!" << endl;
    isSetupProperly = false;
  }
  else
  {
    cout << "Parameters read in successfully - simulation is ready!" << endl;
    isSetupProperly = true;
  }
}

void IntersectionSimulationClass::printParameters() const
{
  cout << "===== Begin Simulation Parameters =====" << endl;
  if (!isSetupProperly)
  {
    cout << "  Simulation is not yet properly setup!" << endl;
  }
  else
  {
    cout << "  Random generator seed: " << randomSeedVal << endl;
    cout << "  Simulation end time: " << timeToStopSim << endl;

    cout << "  East-West Timing -" <<
            " Green: " << eastWestGreenTime << 
            " Yellow: " << eastWestYellowTime <<
            " Red: " << getEastWestRedTime() << endl;

    cout << "  North-South Timing -" <<
            " Green: " << northSouthGreenTime << 
            " Yellow: " << northSouthYellowTime <<
            " Red: " << getNorthSouthRedTime() << endl;

    cout << "  Arrival Distributions:" << endl;
    cout << "    East - Mean: " << eastArrivalMean << 
            " StdDev: " << eastArrivalStdDev << endl;
    cout << "    West - Mean: " << westArrivalMean << 
            " StdDev: " << westArrivalStdDev << endl;
    cout << "    North - Mean: " << northArrivalMean << 
            " StdDev: " << northArrivalStdDev << endl;
    cout << "    South - Mean: " << southArrivalMean << 
            " StdDev: " << southArrivalStdDev << endl;

    cout << "  Percentage cars advancing through yellow: " <<
            percentCarsAdvanceOnYellow << endl;
  }
  cout << "===== End Simulation Parameters =====" << endl;
}

void IntersectionSimulationClass::scheduleArrival(
     const string &travelDir
     )
{  
  int arrivalTime = 0;
  int arrivalType = EVENT_UNKNOWN;
  if (travelDir == EAST_DIRECTION)
  {
    double arrivalTime = currentTime + getPositiveNormal(eastArrivalMean, 
                                                         eastArrivalStdDev);
    EventClass eastArrival(arrivalTime, EVENT_ARRIVE_EAST);
    eventList.insertValue(eastArrival);
    arrivalType = EVENT_ARRIVE_EAST;
  }
  if (travelDir == WEST_DIRECTION)
  {
    double arrivalTime = currentTime + getPositiveNormal(westArrivalMean, 
                                                         westArrivalStdDev);
    EventClass westArrival(arrivalTime, EVENT_ARRIVE_WEST);
    eventList.insertValue(westArrival);
    arrivalType = EVENT_ARRIVE_WEST;
  }
  if (travelDir == NORTH_DIRECTION)
  {
    double arrivalTime = currentTime + getPositiveNormal(northArrivalMean, 
                                                         northArrivalStdDev);
    EventClass northArrival(arrivalTime, EVENT_ARRIVE_NORTH);
    eventList.insertValue(northArrival);
    arrivalType = EVENT_ARRIVE_NORTH;
  }
  if (travelDir == SOUTH_DIRECTION)
  {
    double arrivalTime = currentTime + getPositiveNormal(southArrivalMean, 
                                                         southArrivalStdDev);
    EventClass southArrival(arrivalTime, EVENT_ARRIVE_SOUTH);
    eventList.insertValue(southArrival);
    arrivalType = EVENT_ARRIVE_SOUTH;
  }
  EventClass currentArrival(arrivalTime, arrivalType);
  cout << "Time: " << currentTime << " Scheduled " << currentArrival << endl;
}

void IntersectionSimulationClass::scheduleLightChange(
     )
{
  if (currentLight == LIGHT_YELLOW_EW)
  {
    int eastWestYellow = currentTime + eastWestYellowTime;
    EventClass changeEWYellow(eastWestYellow, EVENT_CHANGE_GREEN_NS);
    eventList.insertValue(changeEWYellow);
    cout << "Time: " << currentTime << " Scheduled " << changeEWYellow << endl;
    cout << endl;
  }
  if (currentLight == LIGHT_YELLOW_NS)
  {
    int northSouthYellow = currentTime + northSouthYellowTime;
    EventClass changeNSYellow(northSouthYellow, EVENT_CHANGE_GREEN_EW);
    eventList.insertValue(changeNSYellow);
    cout << "Time: " << currentTime << " Scheduled " << changeNSYellow << endl;
    cout << endl;
  }
  if (currentLight == LIGHT_GREEN_EW)
  {
    int eastWestGreen = currentTime + eastWestGreenTime;
    EventClass changeEWGreen(eastWestGreen, EVENT_CHANGE_YELLOW_EW);
    eventList.insertValue(changeEWGreen);
    cout << "Time: " << currentTime << " Scheduled " << changeEWGreen << endl;
    cout << endl;
  }
  if (currentLight == LIGHT_GREEN_NS)
  {
    int northSouthGreen = currentTime + northSouthGreenTime;
    EventClass changeNSGreen(northSouthGreen, EVENT_CHANGE_YELLOW_NS);
    eventList.insertValue(changeNSGreen);
    cout << "Time: " << currentTime << " Scheduled " << changeNSGreen << endl;
    cout << endl;
  }
}

bool IntersectionSimulationClass::handleNextEvent(
     )
{
  bool wasHandled = false;
  EventClass nextEvent;
  eventList.removeFront(nextEvent);
  currentTime = nextEvent.getTimeOccurs();
  if (nextEvent.getTimeOccurs() > timeToStopSim)
  {
    cout << "Next event occurs AFTER the simulation end time (" 
         << nextEvent << ")!" << endl;
    return wasHandled;
  }
  else if (nextEvent.getType() == EVENT_ARRIVE_EAST)
  {
    cout << "Handling " << nextEvent << endl; 
    CarClass nextDir(EAST_DIRECTION, currentTime);
    eastQueue.enqueue(nextDir);
    // Update east bound longest queue
    if (eastQueue.getNumElems() > maxEastQueueLength)
    {
      maxEastQueueLength = eastQueue.getNumElems();
    }
    cout << "Time: " << currentTime << " " << nextDir << endl;
    scheduleArrival(EAST_DIRECTION);
    cout << endl;
    wasHandled = true;
  }
  else if (nextEvent.getType() == EVENT_ARRIVE_SOUTH)
  {
    cout << "Handling " << nextEvent << endl; 
    CarClass nextDir(SOUTH_DIRECTION, currentTime);
    southQueue.enqueue(nextDir);
    // Update south bound longest queue
    if (southQueue.getNumElems() > maxSouthQueueLength)
    {
      maxSouthQueueLength = southQueue.getNumElems();
    }
    cout << "Time: " << currentTime << " " << nextDir << endl;
    scheduleArrival(SOUTH_DIRECTION);
    cout << endl;
    wasHandled = true;
  }
  else if (nextEvent.getType() == EVENT_ARRIVE_WEST)
  {
    cout << "Handling " << nextEvent << endl; 
    CarClass nextDir(WEST_DIRECTION, currentTime);
    westQueue.enqueue(nextDir);
    // Update west bound longest queue
    if (westQueue.getNumElems() > maxWestQueueLength)
    {
      maxWestQueueLength = westQueue.getNumElems();
    }
    cout << "Time: " << currentTime << " " << nextDir << endl;
    scheduleArrival(WEST_DIRECTION);
    cout << endl;
    wasHandled = true;
  }
  else if (nextEvent.getType() == EVENT_ARRIVE_NORTH)
  {
    cout << "Handling " << nextEvent << endl; 
    CarClass nextDir(NORTH_DIRECTION, currentTime);
    northQueue.enqueue(nextDir);
    // Update north bound longest queue
    if (northQueue.getNumElems() > maxNorthQueueLength)
    {
      maxNorthQueueLength = northQueue.getNumElems();
    }
    cout << "Time: " << currentTime << " " << nextDir << endl;
    scheduleArrival(NORTH_DIRECTION);
    cout << endl;
    wasHandled = true;
  }
  else if (nextEvent.getType() == EVENT_CHANGE_GREEN_EW)
  {
    cout << "Handling " << nextEvent << endl; 
    cout << "Advancing cars on north-south yellow" << endl;
    bool notGoingNorth = false;
    bool notGoingSouth = false;
    int carsAdvancedYellowNorth = 0;
    int carsAdvancedYellowSouth = 0;
    CarClass northYellow;
    CarClass southYellow;
    while (!notGoingNorth && carsAdvancedYellowNorth < northSouthYellowTime )
    {
      int goVal = 0;
      goVal = getUniform(0, 100);
      if (northQueue.getNumElems() == 0)
      {
        cout << "  No north-bound cars waiting to advance on yellow" << endl;
        notGoingNorth = true;
      }
      else if (goVal <= percentCarsAdvanceOnYellow)
      {
        northQueue.dequeue(northYellow);
        cout << northYellow << "advances north-bound" << endl;
        carsAdvancedYellowNorth++;
        numTotalAdvancedNorth++;
      }
      else
      {
        cout << "  Next north-bound car will NOT advance on yellow" << endl;
        notGoingNorth = true;
      }
    }
    while (!notGoingSouth && carsAdvancedYellowSouth < northSouthYellowTime )
    {
      int goVal = 0;
      goVal = getUniform(0, 100);
      if (southQueue.getNumElems() == 0) 
      {
        cout << "  No south-bound cars waiting to advance on yellow" << endl;
        notGoingSouth = true;
      }
      else if (goVal <= percentCarsAdvanceOnYellow)
      {
        southQueue.dequeue(southYellow);
        cout << southYellow << "advances south-bound" << endl;
        carsAdvancedYellowSouth++;
        numTotalAdvancedSouth++;
      }
      else
      {
        cout << "  Next south-bound car will NOT advance on yellow" << endl;
        notGoingSouth = true;
      }
    }
    cout << "North-bound cars advanced on yellow: " << carsAdvancedYellowNorth 
         << " Remaining queue: " << northQueue.getNumElems() << endl;
    cout << "South-bound cars advanced on yellow: " << carsAdvancedYellowSouth 
         << " Remaining queue: " << southQueue.getNumElems() << endl;
    currentLight = LIGHT_GREEN_EW;
    scheduleLightChange();
    wasHandled = true;
  }
  else if (nextEvent.getType() == EVENT_CHANGE_YELLOW_EW)
  {
    int numCarsEast = 0;
    int numCarsWest = 0;
    CarClass movingCarEast;
    CarClass movingCarWest;
    cout << "Handling " << nextEvent << endl; 
    cout << "Advancing cars on east-west green" << endl;
    
    for (int i = 0; i < eastWestGreenTime; i++)
    {
      if (eastQueue.getNumElems() > 0)
      {
        eastQueue.dequeue(movingCarEast);
        cout << "  Car #" << movingCarEast.getId() << " advances east-bound" 
             << endl;
        numCarsEast++;
        numTotalAdvancedEast++;
      }
      if (westQueue.getNumElems() > 0)
      {
        westQueue.dequeue(movingCarWest);
        cout << "  Car #" << movingCarWest.getId() << " advances west-bound" 
             << endl;
        numCarsWest++;
        numTotalAdvancedWest++;
      }
    }
    cout << "East-bound cars advanced on green: " << numCarsEast
         << " Remaining queue: " << eastQueue.getNumElems() << endl;
    cout << "West-bound cars advanced on green: " << numCarsWest
         << " Remaining queue: " << westQueue.getNumElems() << endl;
    currentLight = LIGHT_YELLOW_EW; 
    scheduleLightChange();
    wasHandled = true;
  }
  else if (nextEvent.getType() == EVENT_CHANGE_GREEN_NS)
  {
    cout << "Handling " << nextEvent << endl; 
    cout << "Advancing cars on east-west yellow" << endl;
    bool notGoingEast = false;
    bool notGoingWest = false;
    int carsAdvancedYellowEast = 0;
    int carsAdvancedYellowWest = 0;
    CarClass eastYellow;
    CarClass westYellow;
    while (!notGoingEast && carsAdvancedYellowEast < eastWestYellowTime ) 
    {
      int goVal = 0;
      goVal = getUniform(0, 100);
      if (eastQueue.getNumElems() == 0)
      {
        cout << "  No east-bound cars waiting to advance on yellow" << endl;
        notGoingEast = true;
      }
      else if (goVal <= percentCarsAdvanceOnYellow)
      {
        eastQueue.dequeue(eastYellow);
        cout << eastYellow << "advances east-bound" << endl;
        carsAdvancedYellowEast++;
        numTotalAdvancedEast++;
      }
      else
      {
        cout << "  Next east-bound car will NOT advance on yellow" << endl;
        notGoingEast = true;
      }
    }
    while (!notGoingWest && carsAdvancedYellowWest < eastWestYellowTime )
    {
      int goVal = 0;
      goVal = getUniform(0, 100);
      if (westQueue.getNumElems() == 0)
      {
        cout << "  No west-bound cars waiting to advance on yellow" << endl;
        notGoingWest = true;
      }
      else if (goVal <= percentCarsAdvanceOnYellow)
      {
        westQueue.dequeue(westYellow);
        cout << westYellow << "advances west-bound" << endl;
        carsAdvancedYellowWest++;
        numTotalAdvancedWest++;
      }
      else
      {
        cout << "  Next west-bound car will NOT advance on yellow" << endl;
        notGoingWest = true;
      }
    }
    cout << "East-bound cars advanced on yellow: " << carsAdvancedYellowEast 
         << " Remaining queue: " << eastQueue.getNumElems() << endl;
    cout << "West-bound cars advanced on yellow: " << carsAdvancedYellowWest 
         << " Remaining queue: " << westQueue.getNumElems() << endl;
    currentLight = LIGHT_GREEN_NS;
    scheduleLightChange();
    wasHandled = true;
  }
  else if (nextEvent.getType() == EVENT_CHANGE_YELLOW_NS)
  {
    int numCarsNorth = 0;
    int numCarsSouth = 0;
    CarClass movingCarNorth;
    CarClass movingCarSouth;
    cout << "Handling " << nextEvent << endl; 
    cout << "Advancing cars on north-south green" << endl;

    for (int i = 0; i < northSouthGreenTime; i++)
    {
      if (northQueue.getNumElems() > 0)
      {
        northQueue.dequeue(movingCarNorth);
        cout << "  Car #" << movingCarNorth.getId() << " advances north-bound" 
             << endl;
        numCarsNorth++;
        numTotalAdvancedNorth++;
      }
      if (southQueue.getNumElems() > 0)
      {  
        southQueue.dequeue(movingCarSouth);
        cout << "  Car #" << movingCarSouth.getId() << " advances south-bound" 
             << endl;
        numCarsSouth++;
        numTotalAdvancedSouth++;
      }  
    }
    cout << "North-bound cars advanced on green: " << numCarsNorth
         << " Remaining queue: " << northQueue.getNumElems() << endl;
    cout << "South-bound cars advanced on green: " << numCarsSouth
         << " Remaining queue: " << southQueue.getNumElems() << endl;
    currentLight = LIGHT_YELLOW_NS;
    scheduleLightChange();
    wasHandled = true;
  }
  return wasHandled;
}

void IntersectionSimulationClass::printStatistics(
     ) const
{
  cout << "===== Begin Simulation Statistics =====" << endl;
  cout << "  Longest east-bound queue: " << maxEastQueueLength << endl;
  cout << "  Longest west-bound queue: " << maxWestQueueLength << endl;
  cout << "  Longest north-bound queue: " << maxNorthQueueLength << endl;
  cout << "  Longest south-bound queue: " << maxSouthQueueLength << endl;
  cout << "  Total cars advanced east-bound: " <<
          numTotalAdvancedEast << endl;
  cout << "  Total cars advanced west-bound: " <<
          numTotalAdvancedWest << endl;
  cout << "  Total cars advanced north-bound: " <<
          numTotalAdvancedNorth << endl;
  cout << "  Total cars advanced south-bound: " <<
          numTotalAdvancedSouth << endl;
  cout << "===== End Simulation Statistics =====" << endl;
}
