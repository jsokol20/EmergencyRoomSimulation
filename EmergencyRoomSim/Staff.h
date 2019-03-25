#ifndef _STAFF_H_
#define _STAFF_H_

class Staff {
public:
	int SkillLevel;
	int RemainingTime;

public:
	Staff() {
		SkillLevel = 0; RemainingTime = 0;
	}

	virtual int getSkillLevel() = 0;
	virtual int getRemainingTime() = 0;
	virtual void setRemainingTime(int t) = 0;
};

//Illness level up to 20 is treated by the doctor
class Doctor : public Staff {
public:
	Doctor() {
		RemainingTime = 0; SkillLevel = 20;
	}

	int getSkillLevel() {
		return SkillLevel;
	}

	int getRemainingTime() {
		return RemainingTime;
	}

	void setRemainingTime(int t) {
		RemainingTime = t;
	}
};

//Illness level up to 10 is treated by the nurse
class Nurse : public Staff {
public:
	Nurse() {
		RemainingTime = 0; SkillLevel = 10;
	}

	int getSkillLevel() {
		return SkillLevel;
	}

	int getRemainingTime() {
		return RemainingTime;
	}

	void setRemainingTime(int t) {
		RemainingTime = t;
	}
};
#endif