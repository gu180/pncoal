#ifndef GETDEUTERON_H_
#define GETDEUTERON_H_
#include "./filename_pncoal.h"
#include "/home/gu180/utility/vector_ut.h"
#include "./Wigner.h"
//#include "./version.h"
void GetDeuteron(tag intag, tag outtag)//This example shows the integral to calculate the average number of deutron per event
//All the values in this script are set causally, only as an example.
{


	gROOT->ProcessLine(".L loader.C+");	

	double sigma_r=1.96; //fm charge radius of deuteron
	double sigma_p=1/(5.068*sigma_r);//1.0 fm^-1=

	gRandom->SetSeed(0);


	//---------------------------
	tag in=getfilename_nucleon(intag,"");
	TFile* input=TFile::Open(in);
	TTree* tree_nucleons= (TTree*) input->Get("tree_nucleons");
	
	TTreeReader reader(tree_nucleons);
	TTreeReaderValue<vector<vector<TLorentzVector>>> protons(reader, "protons");
	TTreeReaderValue<vector<vector<TLorentzVector>>> neutrons(reader, "neutrons");
	//---------------------------
	tag on=getfilename_deuteron(outtag, "");
	MakeDir(on);
	TFile* output=TFile::Open(on, "recreate");
	//---------------------------
	
	vector<bool> used_p_;
	vector<bool> used_n_;
	vector<vector<TLorentzVector>> protons_output;
	vector<vector<TLorentzVector>> neutrons_output;

	TTree* tree_nucleons_output=new TTree("tree_nucleons", "a tree to store nucleon information");
	tree_nucleons_output->Branch("proton_useds", &used_p_);
	tree_nucleons_output->Branch("neutron_useds", &used_n_);
	tree_nucleons_output->Branch("protons", &protons_output);
	tree_nucleons_output->Branch("neutrons", &neutrons_output);
	//---------------------------

	
	
	TTree * deutree= new TTree("tree_deuterons","a tree to store the information of deuterons");
	vector<vector<TLorentzVector>> deuterons;
	deutree->Branch("deuterons", &deuterons);

	int event_N=0;
	while(reader.Next())
	{
		//if(event_N>max_event){break;}
		event_N++;
		cout<<"processing event "<<event_N<<endl;
		int N_p=protons->size();
		int N_n=neutrons->size();
		vector<bool> used_p(N_p);
		vector<bool> used_n(N_n);

		deuterons.clear();
		protons_output.clear();
		neutrons_output.clear();
	
		used_p_.clear();
		used_n_.clear();

		protons_output.assign(protons->begin(), protons->end());
		neutrons_output.assign(neutrons->begin(), neutrons->end());

		for(int i=0; i<N_p; ++i)
		{
			for(int j=0; j<N_n; ++j)
			{
				if(used_p[i]==1){continue;}
				if(used_n[j]==1){continue;}
				vector<TLorentzVector> proton=protons->at(i);	
				vector<TLorentzVector> neutron=neutrons->at(j);


				WignerResult result=wignerfunction(proton, neutron, sigma_r, sigma_p);
				double wigner=result.wigner_val;
				double r=gRandom->Uniform(0,1);
				if(r<wigner)
				{
					//TLorentzVector r_deuteron=result.r_center;
					TLorentzVector r_deuteron=result.r_lab;
					TLorentzVector p_deuteron=proton[1]+neutron[1];
#ifdef DEBUGMODE
cout<<"Wigner proton[1]:"; proton[1].Print();
cout<<"Wigner neutron[1]:"; neutron[1].Print();
#endif
					
					vector<TLorentzVector> deuteron{r_deuteron, p_deuteron};
					deuterons.push_back(deuteron);
					
					//cout<<"Deuteron sucess"<<endl;

					used_p[i]=1;
					used_n[j]=1;
					break;
				}
			}
		}
		used_p_=used_p;
		used_n_=used_n;
		//Print(used_p_);
		//Print(used_p);

		int N_p_free=CountFree(used_p_);
		int N_n_free=CountFree(used_n_);
		int N_d_free=deuterons.size();
		int N_d=N_d_free;

	
		cout<<"Event "<<event_N<<endl;
		cout<<"Np="<<N_p<<" Np_free="<<N_p_free<<endl;
		cout<<"Nn="<<N_n<<" Nn_free="<<N_n_free<<endl;
		cout<<"N_d="<<N_d<<" N_d_free="<<N_d_free<<endl;
		//cout<<"N_t="<<N_t<<" N_t_free="<<N_t_free<<endl;

		deutree->Fill();
		tree_nucleons_output->Fill();
	}
		
	output->cd();
	deutree->Write();
	tree_nucleons_output->Write();
	output->Write();
	output->Close();
	delete output;
	
	//delete tree_nucleons_output;
	//delete tree_deuterons;

	//delete input;

}

#endif
