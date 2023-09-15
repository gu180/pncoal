#ifndef GETTRITON_H_
#define GETTRITON_H_
#include "./filename_pncoal.h"
#include "./Wigner.h"
//#include "./version.h"
#include "/home/gu180/utility/vector_ut.h"


void GetTriton(tag intag, tag outtag)
{
	gROOT->ProcessLine(".L loader.C+");	

	double sigma_r=1.59;
	//double sigma_r=1.96;
	double sigma_p=1/(5.068*sigma_r);

	gRandom->SetSeed(0);


	//---------------------------
	tag in=getfilename_deuteron(intag, "");
	TFile* input=TFile::Open(in);
	TTree* tree_nucleons= (TTree*) input->Get("tree_nucleons");
	TTree* tree_deuterons= (TTree*) input->Get("tree_deuterons");
	
	TTreeReader reader_nucleon(tree_nucleons);
	TTreeReaderValue<vector<vector<TLorentzVector>>> protons(reader_nucleon, "protons");
	TTreeReaderValue<vector<vector<TLorentzVector>>> neutrons(reader_nucleon, "neutrons");
	TTreeReaderValue<vector<bool>> proton_useds(reader_nucleon, "proton_useds");
	TTreeReaderValue<vector<bool>> neutron_useds(reader_nucleon, "neutron_useds");

	TTreeReader reader_deuteron(tree_deuterons);
	TTreeReaderValue<vector<vector<TLorentzVector>>> deuterons(reader_deuteron, "deuterons");

	//---------------------------
	//---------------------------
	tag on=getfilename_triton(outtag, "");
	MakeDir(on);
	TFile* output=TFile::Open(on, "recreate");
	//---------------------------
	
	TTree *tree_tritons= new TTree("tree_tritons","a tree to store the information of tritons");
	vector<vector<TLorentzVector>> tritons;
	tree_tritons->Branch("tritons", &tritons);

	TTree *tree_heliums= new TTree("tree_heliums","a tree to store the information of heliums");
	vector<vector<TLorentzVector>> heliums;
	tree_heliums->Branch("heliums", &heliums);

	TTree *tree_nucleons_output=new TTree("tree_nucleons_output","");
	vector<bool> used_p_;
	vector<bool> used_n_;
	vector<vector<TLorentzVector>> protons_output;
	vector<vector<TLorentzVector>> neutrons_output;
	tree_nucleons_output->Branch("proton_useds", &used_p_);
	tree_nucleons_output->Branch("neutron_useds", &used_n_);
	tree_nucleons_output->Branch("protons", &protons_output);
	tree_nucleons_output->Branch("neutrons", &neutrons_output);

	TTree *tree_deuterons_output=new TTree("tree_deuterons", "");
	vector<bool> used_d_;
	vector<vector<TLorentzVector>> deuterons_output;
	tree_deuterons_output->Branch("deuterons", &deuterons_output);
	tree_deuterons_output->Branch("deuteron_useds", &used_d_);
	
	
	//---------------------------

	int event_N=0;
	
	Long64_t Nevent_nucleons=tree_nucleons->GetEntries();
	Long64_t Nevent_deuterons=tree_deuterons->GetEntries();
	cout<<"Nevent_nucleons: "<<Nevent_nucleons<<endl;
	cout<<"Nevent_deuterons: "<<Nevent_deuterons<<endl;
	if(Nevent_nucleons!=Nevent_deuterons){cout<<"Nevent_nucleons!=Nevent_deuterons!"<<endl;return;}
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

		tritons.clear();
		heliums.clear();
		protons_output.clear();
		neutrons_output.clear();
		deuterons_output.clear();

		protons_output.assign(protons->begin(), protons->end());
		neutrons_output.assign(neutrons->begin(), neutrons->end());
		deuterons_output.assign(deuterons->begin(), deuterons->end());


		vector<int> idxs_nucleon=RandomNumbers(N_n+N_p);
		Print(idxs_nucleon);

		for(int i=0; i<N_d; ++i)
		{
			if(used_d[i]==1){continue;}
			for(int j_=0; j_<N_n+N_p; ++j_)
			{
				int j=idxs_nucleon[j_];
				int nucleon_pid;
				if(j<N_n){nucleon_pid=1;} //neutron
				if(j>=N_n){nucleon_pid=2;j=j-N_n;}//proton
				if(used_d[i]==1){continue;}
				if(nucleon_pid==1)
				{
					if(used_n[j]==1){continue;}
					vector<TLorentzVector> deuteron=deuterons->at(i);	
					vector<TLorentzVector> neutron=neutrons->at(j);
					WignerResult result=wignerfunction(deuteron, neutron, sigma_r, sigma_p);
					double wigner=result.wigner_val;
					double r=gRandom->Uniform(0,1);
					if(r<wigner)
					{
						//TLorentzVector r_deuteron=result.r_center;
						TLorentzVector r_triton=result.r_lab;
						TLorentzVector p_triton=deuteron[1]+neutron[1];
						vector<TLorentzVector> triton{r_triton, p_triton};
						tritons.push_back(triton);

						used_d[i]=1;
						used_n[j]=1;

						//break;
						goto endloop;
					}
				}
				else
				{
					if(used_p[j]==1){continue;}
					vector<TLorentzVector> deuteron=deuterons->at(i);	
					vector<TLorentzVector> proton=protons->at(j);	
					WignerResult result=wignerfunction(deuteron, proton, sigma_r, sigma_p);
					double wigner=result.wigner_val;
					double r=gRandom->Uniform(0,1);
					if(r<wigner)
					{
						//TLorentzVector r_deuteron=result.r_center;
						TLorentzVector r_helium=result.r_lab;
						TLorentzVector p_helium=deuteron[1]+proton[1];
						vector<TLorentzVector> helium{r_helium, p_helium};
						heliums.push_back(helium);

						used_d[i]=1;
						used_p[j]=1;

						//break;
						goto endloop;
					}
				}
					


			}
			endloop:
			if(0){}
		}
		used_d_=used_d;
		used_n_=used_n;
		used_p_=used_p;

		int N_n_free=CountFree(used_n_);
		int N_d_free=CountFree(used_d_);
		int N_p_free=CountFree(used_p_);
		int N_t_free=tritons.size();;
		int N_h_free=heliums.size();;
		int N_t=N_t_free;
		int N_h=N_h_free;

		cout<<"Event "<<event_N<<endl;
		cout<<"Np="<<N_p<<" Np_free="<<N_p_free<<endl;
		cout<<"Nn="<<N_n<<" Nn_free="<<N_n_free<<endl;
		cout<<"N_d="<<N_d<<" N_d_free="<<N_d_free<<endl;
		cout<<"N_t="<<N_t<<" N_t_free="<<N_t_free<<endl;
		cout<<"N_h="<<N_h<<" N_h_free="<<N_h_free<<endl;

		tree_tritons->Fill();
		tree_heliums->Fill();
		tree_deuterons_output->Fill();
		tree_nucleons_output->Fill();
	}
		
	output->cd();
	tree_nucleons_output->Write();
	tree_deuterons_output->Write();
	tree_tritons->Write();
	tree_heliums->Write();
	output->Write();
	output->Close();
	delete output;

	delete input;
}

#endif
