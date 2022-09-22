#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include <vector>
#include <iostream>
#include "TLorentzVector.h"

void draw_nucleon()
{
	TFile* input=TFile::Open("./nucleon.root");
	TTree* tree_nucleons=(TTree*) input->Get("tree_nucleons");
	TH1D* h_pt=new TH1D("h_pt", "pt spectrum of protons", 100, 0, 10); //create a histogram to show the distribution of pt of proton
	int Nevent=tree_nucleons->GetEntries();
/*
	vector<vector<TLorentzVector>> protons[200];
	vector<vector<TLorentzVector>> *neutrons;
	tree_nucleons->SetBranchAddress("protons", &protons);
	
	for(int i=0; i<Nevent; ++i)
	{
		//tree_nucleons->GetEntry(0);
		tree_nucleons->GetEntry(i);

		int number_proton=protons->size();

		for(int j=0; j< number_proton; ++j)
		{
			cout<<"protons->size() "<<protons->size()<<endl;
			vector<TLorentzVector> proton=(*protons)[j];

			//TLorentzVector p_proton=proton[1];

			TLorentzVector p_proton=(*protons)[j][1];
			cout<<"pt "<<p_proton.Pt()<<endl;
			h_pt->Fill(p_proton.Pt());
		}
	}
*/

	TTreeReader reader(tree_nucleons);
	TTreeReaderValue<vector<vector<TLorentzVector>>> protons(reader, "protons");
	while(reader.Next())
	{
		int number_proton=protons->size();
		cout<<reader.GetCurrentEntry()<<" protons number "<<number_proton<<endl;
		for(int j=0; j< number_proton; ++j)
		{
			vector<TLorentzVector> proton=(*protons)[j];

			TLorentzVector p_proton=proton[1];
			//TLorentzVector p_proton=(*protons)[j][1];
			h_pt->Fill(p_proton.Pt());
		}
	}

	h_pt->Scale(1.0/double(Nevent)); //get pt spectrum of proton per event

	TCanvas* c=new TCanvas("c_h_pt", "c_h_pt");
	h_pt->Draw();
	h_pt->GetXaxis()->SetTitle("p_{T} (GeV)");
	h_pt->GetYaxis()->SetTitle("Entries");
	c->SaveAs("./h_pt_proton.pdf");// save the plot

}