#include "replayer.h"

Replayer::Replayer()
{
	/**********************************************************************
	VARIABLES SPECIFICATION
	**********************************************************************/
	A = plSymbol("A",PL_BINARY_TYPE);
	B = plSymbol("B",PL_BINARY_TYPE);
	C = plSymbol("C",PL_BINARY_TYPE);
	D = plSymbol("D",PL_BINARY_TYPE);
	E = plSymbol("E",PL_BINARY_TYPE);

	/**********************************************************************
	PARAMETRIC FORM SPECIFICATION
	**********************************************************************/
	// Specification of P(A)
	plProbValue tableA[] = {0.4, 0.6};
	P_A = plProbTable(A, tableA);

	// Specification of P(B)
	plProbValue tableB[] = {0.18, 0.82};
	P_B = plProbTable(B, tableB);

	// Specification of P(C)
	plProbValue tableC[] = {0.75, 0.25};
	P_C = plProbTable(C, tableC);

	// Specification of P(D | A B)
	plProbValue tableD_knowingA_B[] = {0.6, 0.4,  // P(D | [A=f]^[B=f])
		0.3, 0.7,  // P(D | [A=f]^[B=t])
		0.1, 0.9,  // P(D | [A=t]^[B=f])
		0.5, 0.5}; // P(D | [A=t]^[B=t])
	P_D = plDistributionTable(D,A^B,tableD_knowingA_B);

	// Specification of P(E | C D)
	plProbValue tableE_knowingC_D[] = {0.59, 0.41,  // P(E | [C=f]^[D=f])
		0.25, 0.75,  // P(E | [C=f]^[D=t])
		0.8,  0.2,   // P(E | [C=t]^[D=f])
		0.35, 0.65}; // P(E | [C=t]^[D=t])
	P_E = plDistributionTable(E,C^D,tableE_knowingC_D);

	/**********************************************************************
	DECOMPOSITION
	**********************************************************************/
	jd = plJointDistribution(A^B^C^D^E, P_A*P_B*P_C*P_D*P_E);

	/**********************************************************************
	PROGRAM QUESTION
	**********************************************************************/
	// Get the inferred conditional distribution representing P(C B | E D)
	CndP_CB = plCndDistribution();
	jd.ask(CndP_CB, C^B, E^D);

}

Replayer::~Replayer()
{
}

void Replayer::onFrame()
{
	// Create the value representing the evidence = [E=true]^[D=false]
	plValues evidence(E^D);
	evidence[E] = true;
	evidence[D] = false;

	// Get the distribution representing P(C B | [E=true]^[D=false] )
	plDistribution P_CB;
	CndP_CB.instantiate(P_CB,evidence);

	// Get the normalized distribution representing P(C B | [E=true]^[D=false] )
	plDistribution  T_P_CB;
	P_CB.compile(T_P_CB);
}