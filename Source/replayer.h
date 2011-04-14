#pragma once

#include <pl.h>

class Replayer
{
	plSymbol A;
	plSymbol B;
	plSymbol C;
	plSymbol D; 
	plSymbol E;
	plProbTable P_A;
	plProbTable P_B;
	plProbTable P_C;
	plDistributionTable P_D; 
	plDistributionTable P_E;
	plJointDistribution jd;
	plCndDistribution CndP_CB;
public:
	Replayer();
	~Replayer();
	virtual void onFrame();
};
