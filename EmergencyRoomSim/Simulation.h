#ifndef _SIMULATION_H_
#define _SIMULATION_H_
#include "Hospital.h"
#include "Patient.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>

class Sim
{
private:
	Hospital hospital;
	double OverallVisits;
	double TotalTreat;
	double Rate;

public:
	Sim(Hospital _hospital) { hospital = _hospital; OverallVisits = 0; TotalTreat = 0; }
	Sim() { OverallVisits = 0; TotalTreat = 0; }

	void getUserInput() {
		cout << "Welcome to the Emergency Room!" << endl
		<< "Enter average patient arrival rate per hour: ";
		cin >> Rate;
		OverallVisits = Rate * 168;

		cout << "Enter number of Nurses: ";
		int NumberOfNurses;
		cin >> NumberOfNurses;
		hospital.addStaff('N', NumberOfNurses);

		cout << "Enter number of Doctors: ";
		int NumberOfDoctors;
		cin >> NumberOfDoctors;
		hospital.addStaff('D', NumberOfDoctors);
		cout << endl;
	}

	Patient* GetPatient() { //get rand patient from list of resident
		Patient* PT = new Patient;
		//PT->setName(rand() % 2000);
		return PT;
	}

	int RunEvaluation() {		//get a random illness value
		int k = rand() % 100 + 1;
		if (k <= 70)
			return (rand() % 10 + 1);
		else if (k <= 90)
			return (rand() % 5 + 11);
		else
			return (rand() % 5 + 16);
	}

	void HealingProcess() {
		priority_queue <pair<int, Patient*>> TemporaryQueue = hospital.getQueue();
		vector<pair<int, Patient*>> temp_currPatients = hospital.getCurrentPatient();
		vector <Staff*> TemporaryStaff = hospital.getStaff();
		if (!TemporaryQueue.empty()) {	//if the queue is not empty

			if (TemporaryQueue.top().first > 10) { //if a doctor is required
				for (int i = 0; i < TemporaryStaff.size(); i++) {

					if ((TemporaryStaff[i])->getSkillLevel() == 20) {

						if (TemporaryQueue.empty())

							break;

						if (TemporaryStaff[i]->getRemainingTime() == 0) {	//if doctor is available
							TemporaryStaff[i]->setRemainingTime(TemporaryQueue.top().first);
							hospital.addToLog(TemporaryQueue.top().second, TemporaryQueue.top().first);
							temp_currPatients.push_back(TemporaryQueue.top());
							TemporaryQueue.pop();
						}
					}
				}
			}

			else {

				for (int i = 0; i < TemporaryStaff.size(); i++) {	//scans all Staffs

					if (TemporaryQueue.empty())

						break;

					if (TemporaryStaff[i]->getRemainingTime() == 0) {	//if there is an available nurse or doctor
						TemporaryStaff[i]->setRemainingTime(TemporaryQueue.top().first);
						hospital.addToLog(TemporaryQueue.top().second, TemporaryQueue.top().first);
						temp_currPatients.push_back(TemporaryQueue.top());
						TemporaryQueue.pop();
					}
				}
			}
		}

		for (int i = 0; i < TemporaryStaff.size(); i++) {	//updates waiting times

			if (TemporaryStaff[i]->getRemainingTime() != 0)
				TemporaryStaff[i]->setRemainingTime(TemporaryStaff[i]->getRemainingTime() - 1);
		}

		for (int i = 0; i < temp_currPatients.size(); i++) {	//updates waiting times
			if (temp_currPatients.at(i).first != 0) {
				hospital.addToLog(temp_currPatients.at(i).second, temp_currPatients.at(i).first);
				TotalTreat += temp_currPatients.at(i).first;
				temp_currPatients.erase(temp_currPatients.begin() + i);
				i--;
			}
		}
		hospital.setStaffs(TemporaryStaff);
		hospital.setQueue(TemporaryQueue);
		hospital.setCurrentPatient(temp_currPatients);
	}

	void runSim() {
		int rate = 60 / Rate;
		int count = rate;
		for (int i = 0; i < (7 * 24 * 60); i++) { //simulate on a minute-by-minute
			if (i == count) {
				Patient* P = GetPatient();
				int severity = RunEvaluation();
				hospital.addToQueue(P, severity);
				count += rate;
			}
			HealingProcess();
		}
	}

	void PrintResults() {	//prints the info of the simulation after running it
		cout << "The result: " << endl << endl;
		set <Patient*> log = hospital.getLog();
		set<Patient*>::iterator it;

		for (it = log.begin(); it != log.end(); ++it) {
			Patient* P = *it;
			vector<int> visits = (*it)->getVisits();
			for (int i = 0; i < visits.size(); i++) {
				cout << i + 1 << "th patient " << "spent " << visits[i] << " minutes at the hospital" << endl;
			}
			cout << endl;

		}

		double AverageTime = (TotalTreat / OverallVisits);
		cout << "The average visiting time for patients is ";
		cout << AverageTime;
		cout << " minutes." << endl << endl;
	}
};
#endif