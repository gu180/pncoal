#include "./filename_pncoal.h"
#include "./Wigner.h"

void GetTriton()
{
	gROOT->ProcessLine(".L loader.C+");	

	double sigma_r=2.126;
	double sigma_p=1/(5.068*sigma_r);

	gRandom->SetSeed(0);


	//---------------------------
	tag in=getfilename_deuteron("v1", "");
	TFile* input=TFile::Open(in);
	TTree* tree_nucleons= (TTree*) input->Get("tree_nucleons");
	TTree* tree_deuterons= (TTree*) input->Get("tree_deuterons");
	
	TTreeReader reader_nucleon(tree_nucleons);
	TTreeReaderValue<vector<vector<TLorentzVector>>> protons(reader_nucleon, "protons");
	TTreeReaderValue<vector<vector<TLorentzVector>>> neutrons(reader_nucleon, "neutrons");
	TTreeReaderValue<vector<bool>> proton_useds(reader_nucleon, "proton_useds");
	TTreeReaderValue<vector<bool>> neutron_useds(reader_nucleon, "neutron_useds");

	TTreeReader reader_deuteron(tree_deuterons);
	TTreeReaderValue<vector<vector<TLorentzVector>>> deuteron(reader_deuteron, "deuterons");
	//---------------------------
	tag on=getfilename_triton("v1", "");
	MakeDir(on);
	TFile* output=TFile::Open(on, "recreate");
	//---------------------------
	
	TTree *tree_triton= new TTree("tree_tritons","a tree to store the information of tritons");
	vector<vector<TLorentzVector>> tritons;
	tree_triton->Branch("tritons", &tritons);

	int event_N=0;
	
	Long64_t Nevent_nucleons=tree_nucleons->GetEntries();
	Long64_t Nevent_deuterons=tree_deuterons->GetEntries();
	cout<<"Nevent_nucleons: "<<Nevent_nucleons<<endl;
	cout<<"Nevent_deuterons: "<<Nevent_deuterons<<endl;
	for(Long64_t i_event=0; i_event<Nevent_nucleons; i_event++)
	{
		reader_nucleon.SetEntry(i_event);
		reader_deuteron.SetEntry(i_event);
		//if(event_N>max_event){break;}
		event_N++;
		cout<<"processing event "<<event_N<<endl;
		int N_p=protons->size();
		int N_n=neutrons->size();
		int N_d=deuterons->size();
		vector<bool> used_p(N_p);
		vector<bool> used_n(N_n);
		vector<bool> used_d(N_d,0);

		used_p.assign(proton_useds->begin(), proton_useds->end());
		used_n.assign(neutron_useds->begin(), neutron_useds->end());


		for(int i=0; i<N_d; ++i)
		{
			for(int j=0; j<N_n; ++j)
			{
				if(used_d[i]==1){continue;}
				if(used_n[j]==1){continue;}
				
				//vector<TLorentzVector> proton=protons->at(i);	
				vector<TLorentzVector> deuteron=deuterons->at(i);	
				vector<TLorentzVector> neutron=neutrons->at(j);


				WignerResult result=wignerfunction(proton, neutron, sigma_r, sigma_p);
				double wigner=result.wigner_val;
				double r=gRandom->Uniform(0,1);
				if(r<wigner)
				{
					TLorentzVector r_deuteron=result.r_center;
					TLorentzVector p_deuteron=proton[1]+neutron[1];
					vector<TLorentzVector> deuteron{r_deuteron, p_deuteron};
					deuterons.push_back(deuteron);

					used_p[i]==1;
					used_n[j]==1;
					break;
				}
			}
		}
		used_p_=used_p;
		used_n_=used_n;

		tree_triton->Fill();
	}
		
	output->cd();
	tree_triton->Write();
	output->Write();
	output->Close();
	delete output;
}
