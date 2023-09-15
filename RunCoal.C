#include "GetPN.h"
#include "GetDeuteron.h"
#include "GetTriton.h"
//#include "DrawTriton.h"
#include "GetInfo.h"


void RunCoal_single(double sigma_proton, double sigma_neutron, tag adtag="")
{
	tag vtag=Form("%sNsigma_proton%.1f_Nsigma_neutron%.1f", adtag.Data(), sigma_proton, sigma_neutron);
	tag vtagin=Form("v13Nsigma_proton%.1f_Nsigma_neutron%.1f", adtag.Data(), sigma_proton, sigma_neutron);

	GetPN(vtag, sigma_proton, sigma_neutron);
	GetDeuteron(vtag, vtag);
	GetTriton(vtag, vtag);
	/*
	*/
	
	GetInfo(vtag, vtag);

}

void CopyCode(tag adtag)
{
	tag optag=Form("../data/copycode/%s", adtag.Data());
	gSystem->Exec("mkdir -p "+optag);
	gSystem->Exec(Form("cp *.h %s", optag.Data()));
	gSystem->Exec(Form("cp *.C %s", optag.Data()));
	gSystem->Exec(Form("cp *.sh %s", optag.Data()));
	
}


void RunCoal()
{
	//vector<double> Nsigmas{1,2,3,4,5};
	//vector<double> Nsigmas{0, 4.2,4.4,4.6,4.8,5.2,5.4,5.6,5.8};

	vector<double> Nsigmas{0, 1 , 2, 3, 4, 5, 6};
	//vector<double> Nsigmas;for(int i=0;i<40; ++i){Nsigmas.push_back(-20+i+1);}
	//vector<double> Nsigmas{0, 1 , 2, 3, 4, 5, 6, 7, 8, 9 ,10, 11, 12, 13, 14};
	//tag adtag="v6";
	//tag adtag="v7";//pn generated Poisson(40)+Gaus(Nsigma_total), then assian as proton or neutron with 50% chance
	//tag adtag="v9";
	//tag adtag="v10"; //Ntotal correct, it should be gRandom->Gaus(0, Nsigma_total), Gaus(Nsigma_total) means gaussian random number with mean=Nsigma_total, and sigma=1 by default.
	//tag adtag="v11"; //The position of center of mass is calculated with (m1*r1+m2*r2)/(m1+m2), m1, m2 were the rest mass, now it's changed to mass, i.e. E() in the code.
	//tag adtag="v12";//	Np=Poisson(20)+Gaus(0,sigma_p), Nn=Poisson(20)+Gaus(0, sigma_n);
	//tag adtag="v13";//	sigma_r_deuteron=1.59fm, sigma_r_triton(he3)=1.96fm
	//tag adtag="v14";//	sigma_r_deuteron=1.59fm, sigma_r_triton(he3)=1.96fm   Number of neutron=20+Gauss(0,sigma), Nproton=20
	//tag adtag="v15";//	sigma_r_deuteron=1.96fm, sigma_r_triton(he3)=1.59fm   Number of neutron=20+Gauss(0,sigma), Nproton=20
	//tag adtag="v15_N10000";//	sigma_r_deuteron=1.96fm, sigma_r_triton(he3)=1.59fm   Number of neutron=20+Gauss(0,sigma), Nproton=20
	//tag adtag="v16_N10000";//	sigma_r_deuteron=1.96fm, sigma_r_triton(he3)=1.59fm   Number of neutron=Poisson(20)+Gauss(0,sigma), Nproton=Poisson(20)
//	tag adtag="v17_N1";//	sigma_r_deuteron=1.96fm, sigma_r_triton(he3)=1.59fm   Number of neutron=Poisson(20)+Gauss(0,sigma), Nproton=Poisson(20)+Gauss(0,sigma)
	tag adtag="v18_N100000_3";//bug fix in GetPN, SetX(1) added before SetPerp() to make sure Perp!=0; temperature in pt spectrum changed from 0.5 to 0.15 GeV.
	//tag adtag="v20_N100000";//Nproton=20, Nneutron=20+Gauss(0,sigma)
	CopyCode(adtag);
	//for(int i=0; i<Nsigmas.size(); ++i)
	for(int i=0; i<1; ++i)
	{
	for(int j=0; j<Nsigmas.size(); ++j)
	//for(int j=0; j<1; ++j)
	{
		//continue;
		//if(i!=j){continue;}
		double Nsigma_proton=0;
		RunCoal_single(Nsigma_proton, Nsigmas[j], adtag);
		cout<<"Finish i="<<i<<" j="<<j<<endl;
	}
	}
}
