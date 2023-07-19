#include "filename_pncoal.h"

tags Nnames{"Nn", "Np", "Nd", "Nh", "Nt"};
tags Rnames{"ratio0", "ratio1"};
tags Ntitles{"N_{neutron}", "N_{proton}", "N_{deuteron}", "N_{He3}", "N_{triton}"};
tags Rtitles{"N_{h}N_{n}/N_{d}^{2}", "N_{t}N_{p}/N_{d}^{2}"};//ratio names

int Ns[5][2];//Np, Nn, N
struct Ninfo
{
	TH1D h_Ns[5][2];
}

void GetNinfo(tag in, tag on)
{
	
}


void GetNinfo()
{
}
