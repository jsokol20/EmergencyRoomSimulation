#ifndef PATIENT_H_
#define PATIENT_H_

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <utility>

using namespace std;

class Patient
{
private:
	int NameOfPatient;
	vector<int> VisitsOfPatient;

public:
	Patient(int n) {
		NameOfPatient = n;
	}

	Patient() {
		NameOfPatient = 1;
	}

	void setName(int n) {
		NameOfPatient = n;
	}
	int getName() {
		return NameOfPatient;
	}

	void addVisit(int v) {
		VisitsOfPatient.push_back(v);
	}

	vector<int> getVisits() {
		return VisitsOfPatient;
	}
};

#endif