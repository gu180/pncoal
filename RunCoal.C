#include "GetPN.h"
#include "GetDeuteron.h"
#include "GetTriton.h"
//#include "DrawTriton.h"
#include "GetInfo.h"


void RunCoal_single(double sigma_proton, double sigma_neutron, tag adtag="")
{
	tag vtag=Form("%sNsigma_proton%.1f_Nsigma_neutron%.1f", adtag.Data(), sigma_proton, sigma_neutron);
	/*
	*/
	GetPN(vtag, sigma_proton, sigma_neutron);
	GetDeuteron(vtag, vtag);
	GetTriton(vtag, vtag);
	//DrawTriton(vtag, vtag);
	
	GetInfo(vtag, vtag);

}




void RunCoal()
{
	//vector<double> Nsigmas{1,2,3,4,5};
	//vector<double> Nsigmas{0, 4.2,4.4,4.6,4.8,5.2,5.4,5.6,5.8};

	//vector<double> Nsigmas{0, 1 , 2, 3, 4, 5, 6};
	vector<double> Nsigmas{0, 1 , 2, 3, 4, 5, 6, 7, 8, 9 ,10, 11, 12, 13, 14};
	//tag adtag="v6";
	//tag adtag="v7";//pn generated Poisson(40)+Gaus(Nsigma_total), then assian as proton or neutron with 50% chance
	//tag adtag="v9";
	//tag adtag="v10"; //Ntotal correct, it should be gRandom->Gaus(0, Nsigma_total), Gaus(Nsigma_total) means gaussian random number with mean=Nsigma_total, and sigma=1 by default.
	tag adtag="v11"; //The position of center of mass is calculated with (m1*r1+m2*r2)/(m1+m2), m1, m2 were the rest mass, now it's changed to mass, i.e. E() in the code.	
	for(int i=1; i<Nsigmas.size(); ++i)
	//for(int i=0; i<1; ++i)
	{
	for(int j=0; j<Nsigmas.size(); ++j)
	//for(int j=0; j<1; ++j)
	{
		
		RunCoal_single(Nsigmas[i], Nsigmas[j], adtag);
		cout<<"Finish i="<<i<<" j="<<j<<endl;
	}
	}
}
