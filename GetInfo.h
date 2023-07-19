#ifndef GETINFO_H_
#define GETINFO_H_
#include "./filename_pncoal.h"
#include "/home/gu180/utility/draw_object_ut.h"
#include "/home/gu180/utility/tf1_ut.h"
//#include "./version.h"

typedef vector<TLorentzVector> particle;
typedef vector<vector<TLorentzVector>> particles;


TH2D* th2d_Nn_ratio;
TH2D* th2d_Np_ratio;
TProfile* tp_Nn_ratio;
TProfile* tp_Np_ratio;
TProfile* tp_ratio_Nn;
TH2D* th2d_Nn_Np;
TH2D* th2d_Nd_Nt;
TH2D* th2d_Nh_Nt;

TH1D* th1d_Ns[5][2];//Nn, Np, Nd, Nh, Nt; total, free


tags Nnames{"Nn", "Np", "Nd", "Nh", "Nt"};
tags Rnames{"ratio0", "ratio1"};
tags Ntitles{"N_{neutron}", "N_{proton}", "N_{deuteron}", "N_{He3}", "N_{triton}"};
tags Rtitles{"N_{h}N_{n}/N_{d}^{2}", "N_{t}N_{p}/N_{d}^{2}"};//ratio names

TH2D* th2ds_ratio[5][2];
TH2D* th2ds[5][5];//Nn,Np,Nd,Nh,Nt
TProfile* tps[5][2];//Nn,Np,Nd,Nh,Nt ; ratio_NhNn/Nd^2,ratio_NtNp/Nd^2
int Ns[5];//Nn, Np, Nd, Nh, Nt
int Ns_free[5];//Nn, Np, Nd, Nh, Nt
double ratios[2];//ratio_NhNn/Nd^2, ratio_NtNp/Nd^2

void SetNs(int Nn_, int Np_, int Nd_, int Nh_, int Nt_)
{
	Ns[0]=Nn_;
	Ns[1]=Np_;
	Ns[2]=Nd_;
	Ns[3]=Nh_;
	Ns[4]=Nt_;
}

void SetNsFree(int Nn_, int Np_, int Nd_, int Nh_, int Nt_)
{
	Ns_free[0]=Nn_;
	Ns_free[1]=Np_;
	Ns_free[2]=Nd_;
	Ns_free[3]=Nh_;
	Ns_free[4]=Nt_;

}
void PrintN(tag nname, int N, int N_free)
{
	cout<<nname<<"\t total: "<<N<<"\t free:"<<N_free<<endl;
}
void PrintNs()
{
	for(int i=0; i<5; ++i)
	{
	PrintN(Nnames[i], Ns[i], Ns_free[i]);
	}
}


tag GetHname(tag adtag, int i, int j, tag typetag="hname")
{
	tag hname;
	tag htitle;
	if(adtag=="th2ds")
	{
		tag xname=Nnames[i];
		tag yname=Nnames[j];
		tag xtitle=Ntitles[i];
		tag ytitle=Ntitles[j];
		hname=Form("th2d_%s_%s",xname.Data(), yname.Data());
		htitle=Form("%s vs. %s", ytitle.Data(), xtitle.Data());
	}
	if(adtag=="th2ds_ratio")
	{
		tag xname=Nnames[i];
		tag yname=Rnames[j];
		tag xtitle=Ntitles[i];
		tag ytitle=Rtitles[j];
		hname=Form("th2d_%s_%s",xname.Data(), yname.Data());
		htitle=Form("%s vs. %s", ytitle.Data(), xtitle.Data());
	}
	if(adtag=="tps")
	{
		tag xname=Nnames[i];
		tag yname=Rnames[j];
		tag xtitle=Ntitles[i];
		tag ytitle=Rtitles[j];
		hname=Form("tp_%s_%s",xname.Data(), yname.Data());
		htitle=Form("<%s> vs. %s", ytitle.Data(), xtitle.Data());
	}

	if(typetag=="hname"){return hname;}
	if(typetag=="htitle"){return htitle;}
		
}

		
	
void SetH()
{
	for(int i=0; i<5; ++i)
	{
		{
			tag hname, htitle;
			hname=Form("th1d_%s", Nnames[i].Data());
			htitle=Form("distribution of %s (total)", Ntitles[i].Data());
			th1d_Ns[i][0]=new TH1D(hname,htitle, 200,0,200);

			hname=Form("th1d_%s_free", Nnames[i].Data());
			htitle=Form("distribution of %s (free)", Ntitles[i].Data());
			th1d_Ns[i][1]=new TH1D(hname,htitle, 200,0,200);
		}

		for(int j=0; j<5; ++j)
		{
			tag hname =GetHname("th2ds", i, j, "hname");
			tag htitle=GetHname("th2ds", i, j, "htitle");
			th2ds[i][j]=new TH2D(hname, htitle, 200,0,200, 200,0,200);
		}
	
		for(int j=0; j<2; ++j)
		{
			tag hname =GetHname("th2ds_ratio", i, j, "hname");
			tag htitle=GetHname("th2ds_ratio", i, j, "htitle");
			th2ds_ratio[i][j]=new TH2D(hname, htitle, 200,0,200, 10000,0,200);
		}

		for(int j=0; j<2; ++j)
		{
			tag hname =GetHname("tps", i, j, "hname");
			tag htitle=GetHname("tps", i, j, "htitle");
			tps[i][j]=new TProfile(hname, htitle, 200,0,200);
		}
			
	}

	/*
	th2d_Nn_ratio=new TH2D("th2d_ratio","ratio vs. Nn", 200,0,200, 100000,0,10);
	th2d_Np_ratio=new TH2D("th2d_ratio","ratio vs. Np", 200,0,200, 100000,0,10);
	tp_ratio_Nn=new TProfile("tp_ratio_Nn", "<Nn> vs. ratio", 1000,0,0.1);
	tp_Nn_ratio=new TProfile("tp_Nn_ratio", "<ratio> vs. Nn", 200,0,200);
	tp_Np_ratio=new TProfile("tp_Np_ratio", "<ratio> vs. Np", 200,0,200);

	th2d_Nn_Np=new TH2D("th2d_Nn_Np", "Np vs. Nn", 200,0,200, 200,0,200);
	th2d_Nd_Nt=new TH2D("th2d_Nd_Nt", "Nt vs. Nd", 200,0,200, 200,0,200);
	th2d_Nh_Nt=new TH2D("th2d_Nh_Nt", "Nt vs. Nh", 200,0,200, 200,0,200);
	*/
	
}

void CleanH()
{
	

	for(int i=0; i<5; ++i)
	{
		delete th1d_Ns[i][0];
		delete th1d_Ns[i][1];
		for(int j=0; j<5; ++j)
		{
			delete th2ds[i][j];
		}
	
		for(int j=0; j<2; ++j)
		{
			delete th2ds_ratio[i][j];
		}

		for(int j=0; j<2; ++j)
		{
			delete tps[i][j];
		}
			
	}
	/*
	delete th2d_Nn_ratio;
	delete th2d_Np_ratio;
	delete tp_Nn_ratio;
	delete tp_Np_ratio;
	delete tp_ratio_Nn;
	delete th2d_Nn_Np;
	delete th2d_Nd_Nt;
	delete th2d_Nh_Nt;
	*/
	
}

void LoadH(TFile* input)
{
cout<<"LoadH "<<input->GetName()<<endl;
	/*
	th2d_Nn_ratio=(TH2D*) input->Get("th2d_Nn_ratio");
	th2d_Np_ratio=(TH2D*) input->Get("th2d_Np_ratio");
	tp_ratio_Nn=(TProfile*) input->Get("tp_ratio_Nn");
	tp_Nn_ratio=(TProfile*) input->Get("tp_Nn_ratio");
	tp_Np_ratio=(TProfile*) input->Get("tp_Np_ratio");
	th2d_Nn_Np=(TH2D*) input->Get("th2d_Nn_Np");
	th2d_Nd_Nt=(TH2D*) input->Get("th2d_Nd_Nt");
	th2d_Nh_Nt=(TH2D*) input->Get("th2d_Nh_Nt");
	*/
	for(int i=0; i<5; ++i)
	{
		th1d_Ns[i][0]=(TH1D*) input->Get(Form("th1d_%s", Nnames[i].Data()));
		th1d_Ns[i][1]=(TH1D*) input->Get(Form("th1d_%s_free", Nnames[i].Data()));
		for(int j=0; j<5; ++j)
		{
			tag hname =GetHname("th2ds", i, j, "hname");
			th2ds[i][j]=(TH2D*) input->Get(hname);
		}
	
		for(int j=0; j<2; ++j)
		{
			tag hname =GetHname("th2ds_ratio", i, j, "hname");
			th2ds_ratio[i][j]=(TH2D*) input->Get(hname);
		}

		for(int j=0; j<2; ++j)
		{
			tag hname =GetHname("tps", i, j, "hname");
			tps[i][j]=(TProfile*) input->Get(hname);
		}
			
	}

}

void WriteH(TFile* output)
{

	for(int i=0; i<5; ++i)
	{
		th1d_Ns[i][0]->Write();
		th1d_Ns[i][1]->Write();
		for(int j=0; j<5; ++j)
		{
			th2ds[i][j]->Write();
		}
	
		for(int j=0; j<2; ++j)
		{
			th2ds_ratio[i][j]->Write();
		}

		for(int j=0; j<2; ++j)
		{
			tps[i][j]->Write();
		}
			
	}
}

void FillH()
{
	
	int Nd_free=Ns_free[2];

	int Nn_=Ns_free[0];
	int Np_=Ns_free[1];
	int Nd_=Ns_free[2];
	int Nh_=Ns_free[3];
	int Nt_=Ns_free[4];

	if(Nd_free!=0)
	{
		ratios[0]=Nh_*Nn_/(Nd_*Nd_);
		ratios[1]=Nt_*Np_/(Nd_*Nd_);
	}

	for(int i=0; i<5; ++i)
	{
		th1d_Ns[i][0]->Fill(Ns[i]);
		th1d_Ns[i][1]->Fill(Ns_free[i]);
		for(int j=0; j<5; ++j)
		{
			th2ds[i][j]->Fill(Ns_free[i], Ns_free[j]);
		}
	
		for(int j=0; j<2; ++j)
		{
			if(Nd_free!=0){th2ds_ratio[i][j]->Fill(Ns_free[i], ratios[j]);}
		}

		for(int j=0; j<2; ++j)
		{
			if(Nd_free!=0){tps[i][j]->Fill(Ns_free[i], ratios[j]);}
		}
			
	}
}


void GetInfoByFn(tag inif, tag onif)//if infunction
{
	SetH();

	//tag in=getfilename_triton(outtag,"");
	
	
	TFile* input=TFile::Open(inif);
	if(input==NULL){cout<<"Can't find "<< inif<<endl; return;}
	
	TTree* tree_nucleons=(TTree*) input->Get("tree_nucleons_output");
	TTree* tree_deuterons=(TTree*) input->Get("tree_deuterons");
	TTree* tree_tritons=(TTree*) input->Get("tree_tritons");
	TTree* tree_heliums=(TTree*) input->Get("tree_heliums");

	
	TTreeReader reader_nucleon(tree_nucleons);
	TTreeReaderValue<vector<vector<TLorentzVector>>> protons(reader_nucleon, "protons");
	TTreeReaderValue<vector<vector<TLorentzVector>>> neutrons(reader_nucleon, "neutrons");
	TTreeReaderValue<vector<bool>> proton_useds(reader_nucleon, "proton_useds");
	TTreeReaderValue<vector<bool>> neutron_useds(reader_nucleon, "neutron_useds");

	TTreeReader reader_deuteron(tree_deuterons);
	TTreeReaderValue<vector<vector<TLorentzVector>>> deuterons(reader_deuteron, "deuterons");
	TTreeReaderValue<vector<bool>> deuteron_useds(reader_deuteron, "deuteron_useds");

	TTreeReader reader_triton(tree_tritons);
	TTreeReaderValue<vector<vector<TLorentzVector>>> tritons(reader_triton, "tritons");
	TTreeReader reader_helium(tree_heliums);
	TTreeReaderValue<vector<vector<TLorentzVector>>> heliums(reader_helium, "heliums");
	
	int event_N=0;
	
	Long64_t Nevent_nucleons=tree_nucleons->GetEntries();
	Long64_t Nevent_deuterons=tree_deuterons->GetEntries();
	cout<<"Nevent_nucleons: "<<Nevent_nucleons<<endl;
	cout<<"Nevent_deuterons: "<<Nevent_deuterons<<endl;


//	TH1D h_pt_d

	for(Long64_t i_event=0; i_event<Nevent_nucleons; i_event++)
	{
		
		reader_nucleon.SetEntry(i_event);
		reader_deuteron.SetEntry(i_event);
		reader_triton.SetEntry(i_event);
		reader_helium.SetEntry(i_event);

		int N_p=protons->size();
		int N_n=neutrons->size();
		int N_d=deuterons->size();
		int N_t=tritons->size();
		int N_h=heliums->size();
	
		vector<bool> used_p(N_p);
		vector<bool> used_n(N_n);
		vector<bool> used_d(N_d,0);

		used_p.assign(proton_useds->begin(), proton_useds->end());
		used_n.assign(neutron_useds->begin(), neutron_useds->end());
		used_d.assign(deuteron_useds->begin(), deuteron_useds->end());
	
		particles protons_free;
		particles neutrons_free;
		particles deuterons_free;
		particles tritons_free;
		particles heliums_free;
		
		
		for(int i=0; i<deuterons->size(); ++i)
		{
			particle deuteron=deuterons->at(i);	
			bool used_=used_d[i];
			if(used_==0){deuterons_free.push_back(deuteron);}

		}

		for(int i=0; i<protons->size(); ++i)
		{
			particle proton=protons->at(i);	
			bool used_=used_p[i];
			if(used_==0){protons_free.push_back(proton);}
		}

		for(int i=0; i<neutrons->size(); ++i)
		{
			particle neutron=neutrons->at(i);	
			bool used_=used_n[i];
			if(used_==0){neutrons_free.push_back(neutron);}
		}

		
		for(int i=0; i<tritons->size(); ++i)
		{
			particle triton=tritons->at(i);	
			bool used_=0;
			if(used_==0){tritons_free.push_back(triton);}
		}
		
		for(int i=0; i<heliums->size(); ++i)
		{
			particle helium=heliums->at(i);	
			bool used_=0;
			if(used_==0){heliums_free.push_back(helium);}
		}

		SetNs(N_n, N_p, N_d, N_h, N_t);
		
		int N_t_free=tritons_free.size();
		int N_h_free=heliums_free.size();
		int N_d_free=deuterons_free.size();
		int N_p_free=protons_free.size();
		int N_n_free=neutrons_free.size();
		SetNsFree(N_n_free, N_p_free, N_d_free, N_h_free, N_t_free);
		FillH();

		PrintNs();
		
		//double ratio=double(N_t)*double(N_p)/double(N_d*N_d);

		cout<<"Event "<<i_event<<endl;
#ifdef DEBUGMODE
		cout<<"Np="<<N_p<<" Np_free="<<N_p_free<<endl;
		cout<<"Nn="<<N_n<<" Nn_free="<<N_n_free<<endl;
		cout<<"N_d="<<N_d<<" N_d_free="<<N_d_free<<endl;
		cout<<"N_t="<<N_t<<" N_t_free="<<N_t_free<<endl;
#endif

		if(N_d_free==0){cout<<"No deuteron, skip"<<endl; continue;}

		/*
		double ratio=double(N_t_free)*double(N_p_free)/double(N_d_free*N_d_free);
		th2d_Nn_ratio->Fill(N_n_free, ratio);
		tp_Nn_ratio->Fill(N_n_free, ratio);
		tp_ratio_Nn->Fill(ratio, N_n_free);

		th2d_Np_ratio->Fill(N_p_free, ratio);
		tp_Np_ratio->Fill(N_p_free, ratio);
		*/
		
	}

	MakeDir(onif);
	TFile* output=TFile::Open(onif, "recreate");
	WriteH(output);
	output->Write();
	delete output;
	
	CleanH();
}

void GetInfoByTag(tag intag, tag outtag)
{
	tag in=getfilename_triton(intag,"");
	tag on=getfilename_drawtriton(outtag);
	GetInfoByFn(in, on);
}

void RunLocal()
{
}


void GetInfo(tag intag_="he3", tag outtag_="he3")
{
	cout<<"intag_="<<intag_<<endl;
	cout<<"outtag_="<<outtag_<<endl;
	GetInfoByTag(intag_, outtag_);
}


#endif
