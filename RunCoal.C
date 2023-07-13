#include "GetPN.h"
#include "GetDeuteron.h"
#include "GetTriton.h"
#include "DrawTriton.h"


void RunCoal_single(double sigma_proton, double sigma_neutron, tag adtag="")
{
	tag vtag=Form("%sNsigma_proton%.1f_Nsigma_neutron%.1f", adtag.Data(), sigma_proton, sigma_neutron);
	/*
	GetPN(vtag, sigma_proton, sigma_neutron);
	GetDeuteron(vtag, vtag);
	GetTriton(vtag, vtag);
	*/
	DrawTriton(vtag, vtag);
	

}




void RunCoal()
{
	//vector<double> Nsigmas{1,2,3,4,5};
	//vector<double> Nsigmas{0, 4.2,4.4,4.6,4.8,5.2,5.4,5.6,5.8};

	vector<double> Nsigmas{0, 1 , 2, 3, 4, 5, 6};
	tag adtag="v6";
	for(int i=0; i<Nsigmas.size(); ++i)
	{
	for(int j=0; j<Nsigmas.size(); ++j)
	{
		
		RunCoal_single(Nsigmas[i], Nsigmas[j], adtag);
		cout<<"Finish i="<<i<<" j="<<j<<endl;
	}
	}
}
