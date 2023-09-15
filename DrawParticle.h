#ifndef DRAWPARTICLE_H_
#define DRAWPARTICLE_H_

#include "./filename_pncoal.h"
#include "./Particle.h"

const int Nhs=8;
TH1D* hs[Nhs];//x,y,z,t pt,eta,phi,m
TH2D* hxy;//x,y
vector<TString> hnames{"x", "y", "z", "t", "pt", "eta", "phi", "m"};
vector<TString> htitles{"x", "y", "z", "t", "p_{T}", "#eta", "#phi", "m"};
void SetHs()
{
	for(int i=0; i<4; ++i)
	{
		hs[i]=new TH1D(hnames[i], htitles[i], 100,-20,20);
	}
	hs[4]=new TH1D(hnames[4], htitles[4], 100,0,20);
	hs[5]=new TH1D(hnames[5], htitles[5], 100,-2,2);
	hs[6]=new TH1D(hnames[6], htitles[6], 100,-M_PI, M_PI);
	hs[7]=new TH1D(hnames[7], htitles[7], 100,0, 2);

	hxy=new TH2D("xy","xy", 100,-20,20,100,-20,20);

}

void CleanHs()
{
	for(int i=0; i<Nhs; ++i)
	{
		delete hs[i];
	}
	delete hxy;
}

void FillHs(particle a)
{
	TLorentzVector r=a[0];
	TLorentzVector p=a[1];
	hs[0]->Fill(r.X());
	hs[1]->Fill(r.Y());
	hs[2]->Fill(r.Z());
	hs[3]->Fill(r.T());
	hs[4]->Fill(p.Pt());
	hs[5]->Fill(p.Eta());
	hs[6]->Fill(p.Phi());
	hs[7]->Fill(p.M());

	hxy->Fill(r.X(), r.Y());
}

void WriteHs(tag on)
{
	MakeDir(on);
	TFile output(on,"recreate");
	output.cd();
	for(int i=0; i<Nhs; ++i)
	{
		hs[i]->Write();
	}
	hxy->Write();
	output.Write();
	output.Close();
	
}
	
void GetHs(tag in, tag treename, tag branchname, tag on)
{
	SetHs();

	gROOT->ProcessLine(".L loader.C+");	
	TFile* input=TFile::Open(in);
	TTree* tree=(TTree*) input->Get(treename);
	TTreeReader reader(tree);
	TTreeReaderValue<vector<vector<TLorentzVector>>> as(reader, branchname);

	int event_N=0;
	while(reader.Next())
	{
		event_N++;
		cout<<"processing event "<<event_N<<endl;
		for(int i=0;i<as->size(); ++i)
		{
		vector<TLorentzVector> a=as->at(i);	
		FillHs(a);
		}
	}

	WriteHs(on);
	CleanHs();
}

void DrawParticle()
{
	tag vtag="v18_N10000";
	double sigma_proton=0;
	double sigma_neutron=0;
	tag in=Form("../data/nucleon/nucleon_%sNsigma_proton%.1f_Nsigma_neutron%.1f.root", vtag.Data(), sigma_proton, sigma_neutron);
	tag treename="tree_nucleons";
	tag branchnamep="protons";
	tag onp=Form("../data/hs/hs_proton_%sNsigma_proton%.1f_Nsigma_neutron%.1f.root", vtag.Data(), sigma_proton, sigma_neutron);
		
	tag branchnamen="neutrons";
	tag onn=Form("../data/hs/hs_neutron_%sNsigma_proton%.1f_Nsigma_neutron%.1f.root", vtag.Data(), sigma_proton, sigma_neutron);

	GetHs(in, treename, branchnamep, onp);
	GetHs(in, treename, branchnamen, onn);
}

#endif
