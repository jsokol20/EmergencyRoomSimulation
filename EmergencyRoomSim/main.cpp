#include <iostream>
#include <utility>
#include "Simulation.h"
#include "Hospital.h"

using namespace std;
Hospital CS273;
int main()
{
	//resident list is opened
	Sim Emergency(CS273);
	Emergency.getUserInput();

	//simulation starts
	Emergency.runSim();
	Emergency.PrintResults();

	system("PAUSE");

	return 0;
}