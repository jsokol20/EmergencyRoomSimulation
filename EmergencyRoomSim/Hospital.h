#ifndef HOSPITAL_H_
#define HOSPITAL_H_

#include "Patient.h"
#include "Staff.h"
#include <iostream>
#include <queue>
#include <utility>
#include <set>
using std::cout;
using std::endl;

class Hospital
{
private:

	vector <Staff*> Staffs;
	priority_queue < pair <int, Patient*>> PatientList;
	vector < pair <int, Patient*>> CurrentPatients;
	std::set <Patient*> log;

public:
	Hospital() {  } // default constructor

	void addStaff(char type, int amt) {
		Staff *staff;
		if (type == 'N') {
			Staff *n = new Nurse();
			staff = n;
		}
		else if (type == 'D') {
			Staff *d = new Doctor();
			staff = d;
		}
		for (int i = 0; i < amt; i++) {
			Staffs.push_back(staff);
		}
	}

	void setStaffs(vector <Staff*> m) {
		Staffs = m;
	}

	void setQueue(priority_queue <pair<int, Patient*>> p) {
		PatientList = p;
	}

	void setCurrentPatient(vector<pair<int, Patient*>> c) {
		CurrentPatients = c;
	}

	void addToQueue(Patient* P, int severity) {
		PatientList.push(make_pair(severity, P));
	}

	void addToLog(Patient* P, int severity) {
		std::set<Patient*>::iterator it;
		if (!log.empty()) {
			bool flag = false;
			for (it = log.begin(); it != log.end(); ++it)

				if ((*it)->getName() == P->getName()) {
					(*it)->addVisit(severity);
					flag = true;
					break;
				}
		if (flag == false)
				log.insert(P);
		}

		else {
			log.insert(P);
			for (it = log.begin(); it != log.end(); ++it)
				(*it)->addVisit(severity);
			}
	}

	set<Patient*> getLog() { return log; }
	vector <Staff*> getStaff() { return Staffs; }
	priority_queue <pair<int, Patient*>> getQueue() { return PatientList; }
	vector<pair<int, Patient*>> getCurrentPatient() { return CurrentPatients; }
};

#endif