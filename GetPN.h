#ifndef GETPN_H_
#define GETPN_H_

#include "./filename_pncoal.h"
#include "./Wigner.h"


//const double mass_proton=0.938272088;
//const double mass_neutron=0.939565420;
const double kTemprature=0.5;
int Nevent=10000; //number of events

//double Nsigma=2;

TH1D* h_pt;

double random_r_phi()//generate random position-> phi
{
	gRandom->SetSeed(0);
	return gRandom->Uniform(-TMath::Pi(), +TMath::Pi());
}

double random_r_rho()//generate rnadom position -> rho	(here is a cylindrical coordinate, z-axis is along the beam direction)
							//This function will return a rho value with PDF proportional to rho P(rho)=rho;
{
	gRandom->SetSeed(0);
	double r_max=10; //set the maximum rho as 20 fm, this value can be modified, you can search reference for a more reasonable value. This is an occasional value for example.
	double x;
	double y;
	do
	{
		x=gRandom->Uniform(0, r_max);
		y=gRandom->Uniform(0, r_max);
	}while(x<y);
	return x;
}

double random_r_z()//generate random position -> z
{
	gRandom->SetSeed(0);
	return gRandom->Uniform(-5,5); //assume z to be uniformly distributed between -10, +10 fm. This is an occasional value for example.
}

double random_p_phi()//generate random momentum-> phi  Uniform distributed between -pi +pi;
{
	gRandom->SetSeed(0);
	return gRandom->Uniform(-TMath::Pi(), +TMath::Pi());
}

double random_p_pt()//generate rnadom momentum -> pt	(here is a cylindrical coordinate, z-axis is along the beam direction)
							//This function will return a pt value with PDF as an expoential function  P(pt)=exp(-pt/10);
{
	gRandom->SetSeed(0);
	double r_max=20; 
	double x;
	double y;
	do
	{
		x=gRandom->Uniform(0, r_max);
		y=gRandom->Uniform(0, r_max);
	//}while(exp(-x/(kTemprature))<y);
	}while(x*exp(-x/(kTemprature))<y);
	h_pt->Fill(x);
	return x;
}

double random_p_eta()//generate random momentum -> eta
{
	gRandom->SetSeed(0);
	return gRandom->Uniform(-1,1); //assume eta to be uniformly distributed between -1, +1. This is an occasional value for example. eta is pseudorapidity https://en.wikipedia.org/wiki/Pseudorapidity
}

vector<TLorentzVector> single_nucleon(int charge)
{
	TLorentzVector r;//position 4 vector
	TLorentzVector p;//momentum 4 vector
	r.SetPerp(random_r_rho());
	r.SetPhi(random_r_phi());
	r.SetZ(random_r_z());
	r.SetT(0);//assume the time to 0, which need be discussed later
	double mass;
	if(charge==0){mass=mass_neutron;}//neutron
	if(charge==1){mass=mass_proton;}//proton
	p.SetPtEtaPhiM(random_p_pt(), random_p_eta(), random_p_phi(), mass);
	vector<TLorentzVector> particle;
	particle.push_back(r);
	particle.push_back(p);
	return particle;
}

//vector<TLorentzVector> single_nucleon_withoutcollision(int charge, vector<vector<TLorentzVector>> &nucleons)



vector<int> GetNumberPN(double Nsigma_total)
{
	//int Ntotal=gRandom->Poisson(40)+gRandom->Gaus(Nsigma_total);
	int Ntotal=gRandom->Poisson(40)+gRandom->Gaus(0,Nsigma_total);
	int Np=0;
	int Nn=0;
	for(int i=0; i<Ntotal; ++i)
	{
		if(gRandom->Integer(2)==0){Nn++;}
		else{Np++;};
	}

	return vector<int>{Nn, Np};
}
	
	

void GetPN(tag outtag="debug", double Nsigma_proton=0, double Nsigma_neutron=0)
{
	gROOT->ProcessLine(".L loader.C+");	

	gRandom->SetSeed(0);
	tag on=getfilename_nucleon(outtag,"");
	MakeDir(on);

	TFile* output=TFile::Open(on, "recreate");//create a root file as output to store all the nucleon information
	TTree* tree_nucleons=new TTree("tree_nucleons", "a tree to store nucleon information");
	//TTree* tree_proton=new TTree("tree_proton", "a tree to store proton information");
	//TTree* tree_neutron=new TTree("tree_neutron", "a tree to store neutron information");
h_pt=new TH1D("h_pt", "pt spectrum of protons", 100, 0, 10);


	vector<vector<TLorentzVector>> protons;
	vector<vector<TLorentzVector>> neutrons;
	
	vector<TLorentzVector> protons_r;
	vector<TLorentzVector> protons_p;
	vector<TLorentzVector> neutrons_r;
	vector<TLorentzVector> neutrons_p;

	tree_nucleons->Branch("protons", &protons);
	tree_nucleons->Branch("neutrons", &neutrons);

	/*
	tree_nucleons->Branch("protons_r", &protons_r);
	tree_nucleons->Branch("protons_p", &protons_p);
	tree_nucleons->Branch("neutrons_r", &neutrons_r);
	tree_nucleons->Branch("neutrons_p", &neutrons_p);
	*/

	for(int i=0; i< Nevent; ++i)
	{
		int number_proton=gRandom->Poisson(20)+gRandom->Gaus(0,Nsigma_proton); //number of protons, here is just an exmaple
		int number_neutron=gRandom->Poisson(20)+gRandom->Gaus(0,Nsigma_neutron);
		cout<<"Event "<<i<<endl;
		protons.clear();
		neutrons.clear();
	
		//vector<int> number_pn=GetNumberPN(Nsigma_proton+Nsigma_neutron);
		//number_proton=number_pn[0];
		//number_neutron=number_pn[1];

		for(int j=0; j<number_proton; ++j)
		{
			vector<TLorentzVector> proton=single_nucleon(1);
			protons.push_back(proton);
			//protons_r.push_back(proton[0]);
			//protons_p.push_back(proton[1]);
		}

		for(int j=0; j<number_neutron; ++j)
		{
			vector<TLorentzVector> neutron=single_nucleon(0);
			neutrons.push_back(neutron);
			//neutrons_r.push_back(neutron[0]);
			//neutrons_p.push_back(neutron[1]);
		}
		tree_nucleons->Fill();
	}

	output->cd();
	h_pt->Write();
	output->Write();
	output->Close();
	delete output;
	//delete h_pt;
}

#endif
