#ifndef _MESON_COAL_v2_H_
#define _MESON_COAL_v2_H_
//======================================AnGu====================================================================
#include "parton.h"
#include <string.h>
#include <stdio.h>


using namespace std;

void meson_coalescence_v2()
{
	//int max_event=1;
	cout<<"Processing meson_coalescence_v2"<<endl;
	TString output_tag="v54";
	TString inputfilename = "./partonstate.root";
	TFile * inputfile = new TFile(inputfilename);
	TFile * output = TFile::Open(Form("hadron_meson_%s.root", output_tag.Data()),"RECREATE");
	TTree * ftree = (TTree *)inputfile->Get("final_tree");
	TTree * hadronTree= new TTree("hadron_tree","a tree to store the information of hadron");
	//====Event info============================
	TH1D* th1d_number_of_hadron=new TH1D("th1d_number_of_hadron", "th1d_number_of_hadron", 100, 0, 100);
	TH1D* th1d_number_of_parton=new TH1D("th1d_number_of_parton", "th1d_number_of_parton", 1000, 0, 5000);
	TH1D* th1d_number_of_uquark=new TH1D("th1d_number_of_uquark", "th1d_number_of_uquark", 1000, 0, 1000);
	TH1D* th1d_number_of_dquark=new TH1D("th1d_number_of_dquark", "th1d_number_of_dquark", 1000, 0, 1000);
	TH1D* th1d_number_of_squark=new TH1D("th1d_number_of_squark", "th1d_number_of_squark", 1000, 0, 1000);
	TH1D* th1d_number_of_ubarqk=new TH1D("th1d_number_of_ubarqk", "th1d_number_of_ubarqk", 1000, 0, 1000);
	TH1D* th1d_number_of_dbarqk=new TH1D("th1d_number_of_dbarqk", "th1d_number_of_dbarqk", 1000, 0, 1000);
	TH1D* th1d_number_of_sbarqk=new TH1D("th1d_number_of_sbarqk", "th1d_number_of_sbarqk", 1000, 0, 1000);
	TH1D* h_deltar=new TH1D("h_deltar","#Delta_{r}", 1000, 0, 20);
	TH1D* h_deltap=new TH1D("h_deltap","#Delta_{p}", 1000, 0, 20);	
	TH2D* h_deltar_deltap=new TH2D("h_deltar_deltap", "#Delta_{r} #Delta_{p}", 1000, 0, 20, 1000, 0, 20);



	
//==========================================================v2-analysis==========
	TTree * v2_ana= new TTree("v2_ana","a tree to store information for v2 analysis");
//==========================================================v2-analysis==========

	TTreeReader reader(ftree);
	TTreeReaderValue<vector<int>> final_partons_PID(reader, "partons_PID_final");
	TTreeReaderValue<vector<double>> final_partons_px(reader, "partons_px_final");
	TTreeReaderValue<vector<double>> final_partons_py(reader, "partons_py_final");
	TTreeReaderValue<vector<double>> final_partons_pz(reader, "partons_pz_final");
	TTreeReaderValue<vector<double>> final_partons_mass(reader, "partons_mass_final");
	TTreeReaderValue<vector<double>> final_partons_x(reader, "partons_x_final");
	TTreeReaderValue<vector<double>> final_partons_y(reader, "partons_y_final");
	TTreeReaderValue<vector<double>> final_partons_z(reader, "partons_z_final");
	TTreeReaderValue<vector<double>> final_partons_t(reader, "partons_t_final");
	TTreeReaderValue<int> reader_EventInfo_Evnt_id(reader, "EventInfo_Evnt_id");
	TTreeReaderValue<int> reader_EventInfo_Parton_Number(reader, "EventInfo_Parton_Number");	
	TTreeReaderValue<double> reader_EventInfo_impact_parameter(reader, "EventInfo_impact_parameter");
	TTreeReaderValue<int> reader_EventInfo_N_participant_projec_elastic(reader, "EventInfo_N_participant_projec_elastic");
	TTreeReaderValue<int> reader_EventInfo_N_participant_projec_inelast(reader, "EventInfo_N_participant_projec_inelast");
	TTreeReaderValue<int> reader_EventInfo_N_participant_target_elastic(reader, "EventInfo_N_participant_target_elastic");
	TTreeReaderValue<int> reader_EventInfo_N_participant_target_inelast(reader, "EventInfo_N_participant_target_inelast");
	TTreeReaderValue<double> reader_sec_evnt_plane(reader, "sec_evnt_plane");

	vector<int>    hadrons_PID;
	vector<double> hadrons_px;
	vector<double> hadrons_py;
	vector<double> hadrons_pz;
	vector<double> hadrons_mass;
	vector<double> hadrons_x;
	vector<double> hadrons_y;
	vector<double> hadrons_z;
	vector<double> hadrons_t;
	vector<double> hadrons_phi;
	vector<double> hadrons_pt;
	vector<double> hadrons_p;
	vector<double> hadrons_eta;
	//vector<double> wignerfunction_value;
	int Evnt_id;
	int testnumber;
	int Parton_Number;	
	double impact_parameter;
	int N_participant_projec;
	int N_participant_target;
	int N_participant_projec_elastic;
	int N_participant_projec_inelast;
	int N_participant_target_elastic;
	int N_participant_target_inelast;
	double sec_evnt_plane;

	hadronTree->Branch("hadrons_PID",&hadrons_PID);
	hadronTree->Branch("hadrons_px",&hadrons_px);
	hadronTree->Branch("hadrons_py",&hadrons_py);
	hadronTree->Branch("hadrons_pz",&hadrons_pz);
	hadronTree->Branch("hadrons_mass",&hadrons_mass);
	hadronTree->Branch("hadrons_x",&hadrons_x);
	hadronTree->Branch("hadrons_y",&hadrons_y);
	hadronTree->Branch("hadrons_z",&hadrons_z);
	hadronTree->Branch("hadrons_t",&hadrons_t);
	hadronTree->Branch("hadrons_p",&hadrons_p);
	hadronTree->Branch("hadrons_pt",&hadrons_pt);
	hadronTree->Branch("hadrons_phi",&hadrons_phi);
	hadronTree->Branch("hadrons_eta",&hadrons_eta);
	//hadronTree->Branch("wignerfunction_value",&wignerfunction_value);

	hadronTree->Branch("EventInfo_Evnt_id",&Evnt_id);
	hadronTree->Branch("EventInfo_Parton_Number",&Parton_Number);
	hadronTree->Branch("EventInfo_impact_parameter",&impact_parameter);
	hadronTree->Branch("EventInfo_N_participant_projec_elastic",&N_participant_projec_elastic);
	hadronTree->Branch("EventInfo_N_participant_projec_inelast",&N_participant_projec_inelast);
	hadronTree->Branch("EventInfo_N_participant_target_elastic",&N_participant_target_elastic);
	hadronTree->Branch("EventInfo_N_participant_target_inelast",&N_participant_target_inelast);
	hadronTree->Branch("sec_evnt_plane",&sec_evnt_plane);

//==========================================================v2-analysis==========
	/*vector<double> all_hadrons_phi;
	vector<double> all_hadrons_pt;
	TProfile* cos_2phi_vs_pt=new TProfile("cos_2phi_vs_pt", "cos_2phi_vs_pt",20,0,5);
	TProfile* quark_v2=new TProfile("quark_v2", "quark_v2",20,0,5);
	TProfile* quark_s_v2=new TProfile("quark_s_v2", "quark_s_v2",20,0,5);
	TProfile* quark_ud_v2=new TProfile("quark_ud_v2", "quark_ud_v2",20,0,5);
	TH1F* dis_wigner=new TH1F("distribution of wignerfunction","distribution of wignerfunction",1000,0,1);
	//TH2* parton_px_vs_py=new TH2("parton_px_vs_py","parton_px_vs_py");
	v2_ana->Branch("all_hadrons_phi",&all_hadrons_phi);
	v2_ana->Branch("all_hadrons_pt",&all_hadrons_pt);*/

	TH1F* dis_wigner=new TH1F("distribution of wignerfunction","distribution of wignerfunction",1000,-2,2);
	TProfile* tprofile_hadron_v2=new TProfile("tprofile_hadron_v2", "tprofile_hadron_v2",100,0, 10);
//==========================================================v2-analysis==========



    gRandom->SetSeed(0);
 

	int event_N=0;

	//==============
	const double mass_dquark=0.300;//0.0099;// 0.0099 0.340
	const double mass_uquark=0.300;//0.0056;//0.0056 0.336
	const double mass_squark=0.500;//0.199;// 0.199 0.486
	const double mass_dbarqk=mass_dquark;
	const double mass_ubarqk=mass_uquark;
	const double mass_sbarqk=mass_squark;
	const double charge_dquark=-1.0/3.0;
	const double charge_uquark=2.0/3.0;
	const double charge_squark=-1.0/3.0;
	const double charge_dbarqk=1.0/3.0;
	const double charge_ubarqk=-2.0/3.0;
	const double charge_sbarqk=1.0/3.0;
	const double sqr_mean_square_Radius=0.8409;//fm
	const double mean_square_Radius=sqr_mean_square_Radius*sqr_mean_square_Radius;//fm
	//==============
	const double GeV_fm=5.068;//5.076142;//1GeV=5.076142 fm^-1

	//double sigma_r=2.402;//fm  0.6377  1.2
	//const double sigma_r=sqrt(8/3)*sqr_mean_square_Radius;
	const double m1=mass_squark;
	const double m2=mass_squark;
	const double m3=mass_uquark;
	const double m4=mass_uquark;
	const double q1=charge_squark;
	const double q2=charge_sbarqk;
	const double q3=charge_uquark;
	const double q4=charge_ubarqk;

	const double frequency=0.0678;//GeV

	const double reduced_mass_1=1/(1/m1+1/m2);
	const double reduced_mass_2=1/(1/reduced_mass_1+1/m3);
	const double reduced_mass_3=1/(1/reduced_mass_2+1/m4);

	const double sigma_r_1=0.5477;//0;//0.25 2.402 //1/(sqrt(reduced_mass_1*frequency)*GeV_fm);
	const double sigma_r_2=1/(sqrt(reduced_mass_2*frequency)*GeV_fm);
	const double sigma_r_3=1/(sqrt(reduced_mass_3*frequency)*GeV_fm);
	const double sigma_p_1=1/(sigma_r_1*GeV_fm);
	const double sigma_p_2=1/(sigma_r_2*GeV_fm);
	const double sigma_p_3=1/(sigma_r_3*GeV_fm);
	const double sigma_r2_1=sigma_r_1*sigma_r_1;
	const double sigma_r2_2=sigma_r_2*sigma_r_2;
	const double sigma_r2_3=sigma_r_3*sigma_r_3;
	const double sigma_p2_1=sigma_p_1*sigma_p_1;
	const double sigma_p2_2=sigma_p_2*sigma_p_2;
	const double sigma_p2_3=sigma_p_3*sigma_p_3;

	cout<<"sigma_r_1= "<<sigma_r_1<<endl;
	cout<<"sigma_r_2= "<<sigma_r_2<<endl;
	cout<<"sigma_r_3= "<<sigma_r_3<<endl;


	const double n_sigma=5;//3.5

	const double factor=0.25;// 6;//1;

	TString frame="cluster"; //"lab" "cluster"


	vector<double> coal_time;
	

	double px_1;
	double py_1;
	double pz_1;
	double mass_1;
	double x_1;
	double y_1;
	double z_1;
	double t_1;
	double E_1;			
	double vx_1;
	double vy_1;
	double vz_1;

	double px_2;
	double py_2;
	double pz_2;
	double mass_2;
	double x_2;
	double y_2;
	double z_2;
	double t_2;
	double E_2;
	double vx_2;
	double vy_2;
	double vz_2;

	double px_lab_1;
	double py_lab_1;
	double pz_lab_1;
	double mass_lab_1; 
	double x_lab_1;
	double y_lab_1;
	double z_lab_1;
	double t_lab_1;
	double E_lab_1;			
	double vx_lab_1;
	double vy_lab_1;
	double vz_lab_1;

	double px_lab_2;
	double py_lab_2;
	double pz_lab_2;
	double mass_lab_2;
	double x_lab_2;
	double y_lab_2;
	double z_lab_2;
	double t_lab_2;
	double E_lab_2;
	double vx_lab_2;
	double vy_lab_2;
	double vz_lab_2;

	double px_lab_cluster;
	double py_lab_cluster;
	double pz_lab_cluster;
	double E_lab_cluster;
	double beta_x;
	double beta_y;
	double beta_z;
	double gamma_factor;
	double beta;
	double n_x;
	double n_y;
	double n_z;
		
	double t_f;

	double delta_p;
	double delta_r;
	double delta_p_1;
	double delta_r_1;
	double delta_p_2;
	double delta_r_2;
	double delta_p_3;
	double delta_r_3;
	double delta_p2_1;
	double delta_r2_1;
	double delta_p2_2;
	double delta_r2_2;
	double delta_p2_3;
	double delta_r2_3;

	double px_cluster_1;
	double py_cluster_1;
	double pz_cluster_1;
	double mass_cluster_1;
	double x_cluster_1;
	double y_cluster_1;
	double z_cluster_1;

	double hadron_px;
	double hadron_py;
	double hadron_pz;
	double hadron_energy;
	double hadron_mass;
	double x_hadron;
	double y_hadron;
	double z_hadron;
	double t_hadron;
	double hadron_phi;
	double hadron_pt;
	double hadron_p;
	double hadron_eta;
	double hadron_v2;

	double x_cluster_hadron;
	double y_cluster_hadron;
	double z_cluster_hadron;
	double t_cluster_hadron;

	double wigner_function;

	vector<int>	   uquarks_PID_current_evnt;
	vector<double> uquarks_px_current_evnt;
	vector<double> uquarks_py_current_evnt;
	vector<double> uquarks_pz_current_evnt;
	vector<double> uquarks_mass_current_evnt;
	vector<double> uquarks_E_current_evnt;
	vector<double> uquarks_E2_current_evnt;
	vector<double> uquarks_x_current_evnt;
	vector<double> uquarks_y_current_evnt;
	vector<double> uquarks_z_current_evnt;
	vector<double> uquarks_t_current_evnt;	

	vector<int>	   ubarqks_PID_current_evnt;
	vector<double> ubarqks_px_current_evnt;
	vector<double> ubarqks_py_current_evnt;
	vector<double> ubarqks_pz_current_evnt;
	vector<double> ubarqks_mass_current_evnt;
	vector<double> ubarqks_E_current_evnt;
	vector<double> ubarqks_E2_current_evnt;
	vector<double> ubarqks_x_current_evnt;
	vector<double> ubarqks_y_current_evnt;
	vector<double> ubarqks_z_current_evnt;
	vector<double> ubarqks_t_current_evnt;	

	vector<int>	   squarks_PID_current_evnt;
	vector<double> squarks_px_current_evnt;
	vector<double> squarks_py_current_evnt;
	vector<double> squarks_pz_current_evnt;
	vector<double> squarks_mass_current_evnt;
	vector<double> squarks_E_current_evnt;
	vector<double> squarks_E2_current_evnt;
	vector<double> squarks_x_current_evnt;
	vector<double> squarks_y_current_evnt;
	vector<double> squarks_z_current_evnt;
	vector<double> squarks_t_current_evnt;	

	vector<int>	   sbarqks_PID_current_evnt;
	vector<double> sbarqks_px_current_evnt;
	vector<double> sbarqks_py_current_evnt;
	vector<double> sbarqks_pz_current_evnt;
	vector<double> sbarqks_mass_current_evnt;
	vector<double> sbarqks_E_current_evnt;
	vector<double> sbarqks_E2_current_evnt;
	vector<double> sbarqks_x_current_evnt;
	vector<double> sbarqks_y_current_evnt;
	vector<double> sbarqks_z_current_evnt;
	vector<double> sbarqks_t_current_evnt;


int number_id=0;
	while(reader.Next())
	{
		//if(event_N>max_event){break;}
		event_N++;
cout<<"processing event "<<event_N<<endl;
//cout<<"stage0"<<endl;
		//=================================divide the partons by flavour===================
		vector<int>    partons_PID_current_evnt;
		vector<double> partons_px_current_evnt;
		vector<double> partons_py_current_evnt;
		vector<double> partons_pz_current_evnt;
		vector<double> partons_mass_current_evnt;
		vector<double> partons_E_current_evnt;
		vector<double> partons_E2_current_evnt;
		vector<double> partons_x_current_evnt;
		vector<double> partons_y_current_evnt;
		vector<double> partons_z_current_evnt;
		vector<double> partons_t_current_evnt;	
		

		partons_PID_current_evnt.assign(final_partons_PID->begin(),final_partons_PID->end());
		partons_px_current_evnt.assign(final_partons_px->begin(),final_partons_px->end());
		partons_py_current_evnt.assign(final_partons_py->begin(),final_partons_py->end());
		partons_pz_current_evnt.assign(final_partons_pz->begin(),final_partons_pz->end());
		partons_mass_current_evnt.assign(final_partons_mass->begin(),final_partons_mass->end());
		partons_x_current_evnt.assign(final_partons_x->begin(),final_partons_x->end());
		partons_y_current_evnt.assign(final_partons_y->begin(),final_partons_y->end());
		partons_z_current_evnt.assign(final_partons_z->begin(),final_partons_z->end());
		partons_t_current_evnt.assign(final_partons_t->begin(),final_partons_t->end());

		Evnt_id=*reader_EventInfo_Evnt_id;
		Parton_Number=*reader_EventInfo_Parton_Number;	
		impact_parameter=*reader_EventInfo_impact_parameter;
		N_participant_projec_elastic=*reader_EventInfo_N_participant_projec_elastic;
		N_participant_projec_inelast=*reader_EventInfo_N_participant_projec_inelast;
		N_participant_target_elastic=*reader_EventInfo_N_participant_target_elastic;
		N_participant_target_inelast=*reader_EventInfo_N_participant_target_inelast;
		sec_evnt_plane=*reader_sec_evnt_plane;
//cout<<"stage1"<<endl;
		for(int i=0;i<partons_PID_current_evnt.size();i++)
		{
			if(partons_PID_current_evnt[i]==2)
			{
				uquarks_PID_current_evnt.push_back(partons_PID_current_evnt[i]);
				uquarks_px_current_evnt.push_back(partons_px_current_evnt[i]);
				uquarks_py_current_evnt.push_back(partons_py_current_evnt[i]);
				uquarks_pz_current_evnt.push_back(partons_pz_current_evnt[i]);
				uquarks_mass_current_evnt.push_back(mass_uquark);
				uquarks_E_current_evnt.push_back(getEnergy(partons_px_current_evnt[i],partons_py_current_evnt[i],partons_pz_current_evnt[i],mass_uquark));//if u want to use constituent quark mass, you replace partons_E_current_evnt[i] by corresponding quark mass for d,dbar, u,ubar quarks.
				uquarks_E2_current_evnt.push_back(getEnergy2(partons_px_current_evnt[i],partons_py_current_evnt[i],partons_pz_current_evnt[i],mass_uquark));//constituent quark mass calculated
				uquarks_x_current_evnt.push_back(partons_x_current_evnt[i]);
				uquarks_y_current_evnt.push_back(partons_y_current_evnt[i]);
				uquarks_z_current_evnt.push_back(partons_z_current_evnt[i]);
				uquarks_t_current_evnt.push_back(partons_t_current_evnt[i]);

			}
			else if(partons_PID_current_evnt[i]==-2)
			{
				ubarqks_PID_current_evnt.push_back(partons_PID_current_evnt[i]);
				ubarqks_px_current_evnt.push_back(partons_px_current_evnt[i]);
				ubarqks_py_current_evnt.push_back(partons_py_current_evnt[i]);
				ubarqks_pz_current_evnt.push_back(partons_pz_current_evnt[i]);
				ubarqks_mass_current_evnt.push_back(mass_ubarqk);
				ubarqks_E_current_evnt.push_back(getEnergy(partons_px_current_evnt[i],partons_py_current_evnt[i],partons_pz_current_evnt[i],mass_ubarqk));//if u want to use constituent quark mass, you replace partons_E_current_evnt[i] by corresponding quark mass for d,dbar, u,ubar quarks.
				ubarqks_E2_current_evnt.push_back(getEnergy2(partons_px_current_evnt[i],partons_py_current_evnt[i],partons_pz_current_evnt[i],mass_ubarqk));//constituent quark mass calculated
				ubarqks_x_current_evnt.push_back(partons_x_current_evnt[i]);
				ubarqks_y_current_evnt.push_back(partons_y_current_evnt[i]);
				ubarqks_z_current_evnt.push_back(partons_z_current_evnt[i]);
				ubarqks_t_current_evnt.push_back(partons_t_current_evnt[i]);

			}
			else if(partons_PID_current_evnt[i]==3)
			{
				squarks_PID_current_evnt.push_back(partons_PID_current_evnt[i]);
				squarks_px_current_evnt.push_back(partons_px_current_evnt[i]);
				squarks_py_current_evnt.push_back(partons_py_current_evnt[i]);
				squarks_pz_current_evnt.push_back(partons_pz_current_evnt[i]);
				squarks_mass_current_evnt.push_back(mass_squark);
				squarks_E_current_evnt.push_back(getEnergy(partons_px_current_evnt[i],partons_py_current_evnt[i],partons_pz_current_evnt[i],mass_squark));//if u want to use constituent quark mass, you replace partons_E_current_evnt[i] by corresponding quark mass for d,dbar, u,ubar quarks.
				squarks_E2_current_evnt.push_back(getEnergy2(partons_px_current_evnt[i],partons_py_current_evnt[i],partons_pz_current_evnt[i],mass_squark));//constituent quark mass calculated
				squarks_x_current_evnt.push_back(partons_x_current_evnt[i]);
				squarks_y_current_evnt.push_back(partons_y_current_evnt[i]);
				squarks_z_current_evnt.push_back(partons_z_current_evnt[i]);
				squarks_t_current_evnt.push_back(partons_t_current_evnt[i]);
			}
			else if(partons_PID_current_evnt[i]==-3)
			{
				sbarqks_PID_current_evnt.push_back(partons_PID_current_evnt[i]);
				sbarqks_px_current_evnt.push_back(partons_px_current_evnt[i]);
				sbarqks_py_current_evnt.push_back(partons_py_current_evnt[i]);
				sbarqks_pz_current_evnt.push_back(partons_pz_current_evnt[i]);
				sbarqks_mass_current_evnt.push_back(mass_sbarqk);
				sbarqks_E_current_evnt.push_back(getEnergy(partons_px_current_evnt[i],partons_py_current_evnt[i],partons_pz_current_evnt[i],mass_sbarqk));//if u want to use constituent quark mass, you replace partons_E_current_evnt[i] by corresponding quark mass for d,dbar, u,ubar quarks.
				sbarqks_E2_current_evnt.push_back(getEnergy2(partons_px_current_evnt[i],partons_py_current_evnt[i],partons_pz_current_evnt[i],mass_sbarqk));//constituent quark mass calculated
				sbarqks_x_current_evnt.push_back(partons_x_current_evnt[i]);
				sbarqks_y_current_evnt.push_back(partons_y_current_evnt[i]);
				sbarqks_z_current_evnt.push_back(partons_z_current_evnt[i]);
				sbarqks_t_current_evnt.push_back(partons_t_current_evnt[i]);
			}
		}

		int partons_number=partons_PID_current_evnt.size();
		int uquarks_number=uquarks_PID_current_evnt.size();
		int squarks_number=squarks_PID_current_evnt.size();
		int ubarqks_number=ubarqks_PID_current_evnt.size();
		int sbarqks_number=sbarqks_PID_current_evnt.size();

		th1d_number_of_parton->Fill(partons_number,1);
		th1d_number_of_uquark->Fill(uquarks_number,1);
		th1d_number_of_squark->Fill(squarks_number,1);
		th1d_number_of_ubarqk->Fill(ubarqks_number,1);
		th1d_number_of_sbarqk->Fill(sbarqks_number,1);

	//=================================================================================
		//============find neighbor========================================================
		int squarknumber=squarks_px_current_evnt.size(); if(squarknumber==0){continue;}
		//int sbarqknumber=sbarqks_px_current_evnt.size();
		vector<vector<int>> squarks_neighbour1(squarknumber);//squarks which are the squark's neighbour
		vector<vector<int>> squarks_neighbour2(squarknumber);//sbarqks which are the squark's neighbour
		vector<vector<int>> squarks_neighbour3(squarknumber);//uquarks which are the squark's neighbour
		vector<vector<int>> squarks_neighbour4(squarknumber);//ubarqks which are the squark's neighbour
		vector<int> squarks_candidates;

		cout<<"squarknumber="<<squarknumber<<endl;


		int count_find_neighbour1=0;
		for(int i=0;i<squarks_px_current_evnt.size();i++)
		{
			for(int j=0;j<sbarqks_px_current_evnt.size();j++)
			{
				x_lab_1=squarks_x_current_evnt[i];
				y_lab_1=squarks_y_current_evnt[i];
				z_lab_1=squarks_z_current_evnt[i];
				t_lab_1=squarks_t_current_evnt[i];
				px_lab_1=squarks_px_current_evnt[i];
				py_lab_1=squarks_py_current_evnt[i];
				pz_lab_1=squarks_pz_current_evnt[i];
				mass_lab_1=squarks_mass_current_evnt[i];
				E_lab_1=squarks_E_current_evnt[i];

				x_lab_2=sbarqks_x_current_evnt[j];
				y_lab_2=sbarqks_y_current_evnt[j];
				z_lab_2=sbarqks_z_current_evnt[j];
				t_lab_2=sbarqks_t_current_evnt[j];
				px_lab_2=sbarqks_px_current_evnt[j];
				py_lab_2=sbarqks_py_current_evnt[j];
				pz_lab_2=sbarqks_pz_current_evnt[j];
				mass_lab_2=sbarqks_mass_current_evnt[j];
				E_lab_2=sbarqks_E_current_evnt[j];

				if(frame=="lab")
				{
					vx_1=px_lab_1/E_lab_1;
					vy_1=py_lab_1/E_lab_1;
					vz_1=pz_lab_1/E_lab_1;

					vx_2=px_lab_2/E_lab_2;
					vy_2=py_lab_2/E_lab_2;
					vz_2=pz_lab_2/E_lab_2;

					t_f=t_lab_1;
					if(t_lab_2>t_f){t_f=t_lab_2;}
					x_lab_1=x_lab_1+vx_1*(t_f-t_lab_1);
					y_lab_1=y_lab_1+vy_1*(t_f-t_lab_1);
					z_lab_1=z_lab_1+vz_1*(t_f-t_lab_1);
					x_lab_2=x_lab_2+vx_2*(t_f-t_lab_2);
					y_lab_2=y_lab_2+vy_2*(t_f-t_lab_2);
					z_lab_2=z_lab_2+vz_2*(t_f-t_lab_2);

					delta_r=getdistance(x_lab_1,y_lab_1,z_lab_1,x_lab_2,y_lab_2,z_lab_2);
					delta_p=getdistance(px_lab_1,py_lab_1,pz_lab_1,px_lab_2,py_lab_2,pz_lab_2);
				}

				if(frame=="cluster")
				{
					px_lab_cluster=px_lab_1+px_lab_2;
					py_lab_cluster=py_lab_1+py_lab_2;
					pz_lab_cluster=pz_lab_1+pz_lab_2;
					E_lab_cluster=E_lab_1+E_lab_2;
					beta_x=px_lab_cluster/E_lab_cluster;
					beta_y=py_lab_cluster/E_lab_cluster;
					beta_z=pz_lab_cluster/E_lab_cluster;
					gamma_factor=1/sqrt(1-beta_x*beta_x-beta_y*beta_y-beta_z*beta_z);
					beta=get_magnitude(beta_x,beta_y,beta_z);
					n_x=beta_x/beta;
					n_y=beta_y/beta;
					n_z=beta_z/beta;

					double r_dot_n_1=x_lab_1*n_x+y_lab_1*n_y+z_lab_1*n_z;
					x_1 = x_lab_1 + (gamma_factor-1)*r_dot_n_1*n_x - gamma_factor*t_lab_1*beta_x;
					y_1 = y_lab_1 + (gamma_factor-1)*r_dot_n_1*n_y - gamma_factor*t_lab_1*beta_y;
					z_1 = z_lab_1 + (gamma_factor-1)*r_dot_n_1*n_z - gamma_factor*t_lab_1*beta_z;
					t_1 = gamma_factor*(t_lab_1 - beta*r_dot_n_1);
					double p_dot_n_1=px_lab_1*n_x+py_lab_1*n_y+pz_lab_1*n_z;
					px_1 = px_lab_1 + (gamma_factor-1)*p_dot_n_1*n_x - gamma_factor*E_lab_1*beta_x;
					py_1 = py_lab_1 + (gamma_factor-1)*p_dot_n_1*n_y - gamma_factor*E_lab_1*beta_y;
					pz_1 = pz_lab_1 + (gamma_factor-1)*p_dot_n_1*n_z - gamma_factor*E_lab_1*beta_z;
					E_1 = gamma_factor*(E_lab_1 - beta*p_dot_n_1);
					mass_1=mass_lab_1;
					vx_1=px_1/E_1;
					vy_1=py_1/E_1;
					vz_1=pz_1/E_1;

					double r_dot_n_2=x_lab_2*n_x+y_lab_2*n_y+z_lab_2*n_z;
					x_2 = x_lab_2 + (gamma_factor-1)*r_dot_n_2*n_x - gamma_factor*t_lab_2*beta_x;
					y_2 = y_lab_2 + (gamma_factor-1)*r_dot_n_2*n_y - gamma_factor*t_lab_2*beta_y;
					z_2 = z_lab_2 + (gamma_factor-1)*r_dot_n_2*n_z - gamma_factor*t_lab_2*beta_z;
					t_2 = gamma_factor*(t_lab_2 - beta*r_dot_n_2);
					double p_dot_n_2=px_lab_2*n_x+py_lab_2*n_y+pz_lab_2*n_z;
					px_2 = px_lab_2 + (gamma_factor-1)*p_dot_n_2*n_x - gamma_factor*E_lab_2*beta_x;
					py_2 = py_lab_2 + (gamma_factor-1)*p_dot_n_2*n_y - gamma_factor*E_lab_2*beta_y;
					pz_2 = pz_lab_2 + (gamma_factor-1)*p_dot_n_2*n_z - gamma_factor*E_lab_2*beta_z;
					E_2 = gamma_factor*(E_lab_2 - beta*p_dot_n_2);
					mass_2=mass_lab_2;
					vx_2=px_2/E_2;
					vy_2=py_2/E_2;
					vz_2=pz_2/E_2;

					t_f=t_1;
					if(t_2>t_f){t_f=t_2;}
					x_1=x_1+vx_1*(t_f-t_1);
					y_1=y_1+vy_1*(t_f-t_1);
					z_1=z_1+vz_1*(t_f-t_1);
					x_2=x_2+vx_2*(t_f-t_2);
					y_2=y_2+vy_2*(t_f-t_2);
					z_2=z_2+vz_2*(t_f-t_2);

					delta_r=getdistance(x_1,y_1,z_1,x_2,y_2,z_2);
					delta_p=getdistance(px_1,py_1,pz_1,px_2,py_2,pz_2);

				}
h_deltar->Fill(delta_r);
h_deltap->Fill(delta_p);
h_deltar_deltap->Fill(delta_r, delta_p,1);
				count_find_neighbour1++;
				//cout<<count_find_neighbour1<<endl;
				//delta_p=(mass_1*mass_2/(mass_1+mass_2))*getdistance(px_1/mass_1,py_1/mass_1,pz_1/mass_1,px_2/mass_2,py_2/mass_2,pz_2/mass_2);
				if(delta_r<n_sigma*sigma_r_1 and delta_p<n_sigma*sigma_p_1  )// 
				{
					squarks_neighbour2[i].push_back(j);	
				}

			}
			if(squarks_neighbour2[i].size()>=1)
			{	
				squarks_candidates.push_back(i);
			}
		}
		

		//=================coalescence=================================================
		vector<int> squark_used_id;
		vector<int> sbarqk_used_id;
		vector<int> uquark_used_id;
		vector<int> ubarqk_used_id;
		int squark_id_l;
		int sbarqk_id_l;
		int uquark_id_l;
		int ubarqk_id_l;

		bool hadronization_success=0;
		bool existed;

		int count1=0;
		int count2=0;

		for(int coal_i=0;coal_i<squarks_candidates.size();coal_i++)
		{
			hadronization_success=0;
			//===============================================
			squark_id_l=squarks_candidates[coal_i];
			existed=0;
			for(int check_i=0;check_i<squark_used_id.size();check_i++)
			{
				if(squark_id_l==squark_used_id[check_i]){existed=1;break;}
			}
			if(existed==1){continue;}
			//===============================================

			for(int j=0;j<squarks_neighbour2[squark_id_l].size();j++)
			{
				//===============================================
				sbarqk_id_l=squarks_neighbour2[squark_id_l][j];
				existed=0;
				for(int check_i=0;check_i<sbarqk_used_id.size();check_i++)
				{
					if(sbarqk_id_l==sbarqk_used_id[check_i]){existed=1;break;}
				}
				if(existed==1){continue;}
				//===============================================
					//================================================
					
						//=================================================
						x_lab_1=squarks_x_current_evnt[squark_id_l];
						y_lab_1=squarks_y_current_evnt[squark_id_l];
						z_lab_1=squarks_z_current_evnt[squark_id_l];
						t_lab_1=squarks_t_current_evnt[squark_id_l];
						px_lab_1=squarks_px_current_evnt[squark_id_l];
						py_lab_1=squarks_py_current_evnt[squark_id_l];
						pz_lab_1=squarks_pz_current_evnt[squark_id_l];
						mass_lab_1=squarks_mass_current_evnt[squark_id_l];
						E_lab_1=squarks_E_current_evnt[squark_id_l];

						x_lab_2=sbarqks_x_current_evnt[sbarqk_id_l];
						y_lab_2=sbarqks_y_current_evnt[sbarqk_id_l];
						z_lab_2=sbarqks_z_current_evnt[sbarqk_id_l];
						t_lab_2=sbarqks_t_current_evnt[sbarqk_id_l];
						px_lab_2=sbarqks_px_current_evnt[sbarqk_id_l];
						py_lab_2=sbarqks_py_current_evnt[sbarqk_id_l];
						pz_lab_2=sbarqks_pz_current_evnt[sbarqk_id_l];
						mass_lab_2=sbarqks_mass_current_evnt[sbarqk_id_l];
						E_lab_2=sbarqks_E_current_evnt[sbarqk_id_l];
							
						if(frame=="lab")
						{
		
							wigner_function=//get_meson_wigner_function( //get_qutraton_wigner_function(
											get_meson_wigner_function_swave_reducedmass(
											 factor,  sigma_r_1,  sigma_p_1, 
											 x_lab_1,y_lab_1,z_lab_1,  t_lab_1,  px_lab_1, py_lab_1, pz_lab_1,  E_lab_1, 
											 x_lab_2,y_lab_2,z_lab_2,  t_lab_2,  px_lab_2, py_lab_2, pz_lab_2,  E_lab_2);

						}
						if(frame=="cluster")
						{

							px_lab_cluster=px_lab_1+px_lab_2;
							py_lab_cluster=py_lab_1+py_lab_2;
							pz_lab_cluster=pz_lab_1+pz_lab_2;
							E_lab_cluster=E_lab_1+E_lab_2;
							beta_x=px_lab_cluster/E_lab_cluster;
							beta_y=py_lab_cluster/E_lab_cluster;
							beta_z=pz_lab_cluster/E_lab_cluster;
							gamma_factor=1/sqrt(1-beta_x*beta_x-beta_y*beta_y-beta_z*beta_z);
							beta=get_magnitude(beta_x,beta_y,beta_z);
							n_x=beta_x/beta;
							n_y=beta_y/beta;
							n_z=beta_z/beta;

							double r_dot_n_1=x_lab_1*n_x+y_lab_1*n_y+z_lab_1*n_z;
							x_1 = x_lab_1 + (gamma_factor-1)*r_dot_n_1*n_x - gamma_factor*t_lab_1*beta_x;
							y_1 = y_lab_1 + (gamma_factor-1)*r_dot_n_1*n_y - gamma_factor*t_lab_1*beta_y;
							z_1 = z_lab_1 + (gamma_factor-1)*r_dot_n_1*n_z - gamma_factor*t_lab_1*beta_z;
							t_1 = gamma_factor*(t_lab_1 - beta*r_dot_n_1);
							double p_dot_n_1=px_lab_1*n_x+py_lab_1*n_y+pz_lab_1*n_z;
							px_1 = px_lab_1 + (gamma_factor-1)*p_dot_n_1*n_x - gamma_factor*E_lab_1*beta_x;
							py_1 = py_lab_1 + (gamma_factor-1)*p_dot_n_1*n_y - gamma_factor*E_lab_1*beta_y;
							pz_1 = pz_lab_1 + (gamma_factor-1)*p_dot_n_1*n_z - gamma_factor*E_lab_1*beta_z;
							E_1 = gamma_factor*(E_lab_1 - beta*p_dot_n_1);
							mass_1=mass_lab_1;
							vx_1=px_1/E_1;
							vy_1=py_1/E_1;
							vz_1=pz_1/E_1;

							double r_dot_n_2=x_lab_2*n_x+y_lab_2*n_y+z_lab_2*n_z;
							x_2 = x_lab_2 + (gamma_factor-1)*r_dot_n_2*n_x - gamma_factor*t_lab_2*beta_x;
							y_2 = y_lab_2 + (gamma_factor-1)*r_dot_n_2*n_y - gamma_factor*t_lab_2*beta_y;
							z_2 = z_lab_2 + (gamma_factor-1)*r_dot_n_2*n_z - gamma_factor*t_lab_2*beta_z;
							t_2 = gamma_factor*(t_lab_2 - beta*r_dot_n_2);
							double p_dot_n_2=px_lab_2*n_x+py_lab_2*n_y+pz_lab_2*n_z;
							px_2 = px_lab_2 + (gamma_factor-1)*p_dot_n_2*n_x - gamma_factor*E_lab_2*beta_x;
							py_2 = py_lab_2 + (gamma_factor-1)*p_dot_n_2*n_y - gamma_factor*E_lab_2*beta_y;
							pz_2 = pz_lab_2 + (gamma_factor-1)*p_dot_n_2*n_z - gamma_factor*E_lab_2*beta_z;
							E_2 = gamma_factor*(E_lab_2 - beta*p_dot_n_2);
							mass_2=mass_lab_2;
							vx_2=px_2/E_2;
							vy_2=py_2/E_2;
							vz_2=pz_2/E_2;

							

							
							t_f=t_1;
							if(t_2>t_f){t_f=t_2;}
							x_1=x_1+vx_1*(t_f-t_1);
							y_1=y_1+vy_1*(t_f-t_1);
							z_1=z_1+vz_1*(t_f-t_1);
							x_2=x_2+vx_2*(t_f-t_2);
							y_2=y_2+vy_2*(t_f-t_2);
							z_2=z_2+vz_2*(t_f-t_2);
							
							
							px_cluster_1=px_1+px_2;
							py_cluster_1=py_1+py_2;
							pz_cluster_1=pz_1+pz_2;
							mass_cluster_1=mass_1+mass_2;
							x_cluster_1=(mass_1*x_1+mass_2*x_2)/(mass_1+mass_2);
							y_cluster_1=(mass_1*y_1+mass_2*y_2)/(mass_1+mass_2);
							z_cluster_1=(mass_1*z_1+mass_2*z_2)/(mass_1+mass_2);
							delta_r2_1=getdistance2(x_1,y_1,z_1,x_2,y_2,z_2);
							delta_p2_1=get_relativeMomentum2(px_1,py_1,pz_1,mass_1,px_2,py_2,pz_2,mass_2);
							//reduced_mass_1*reduced_mass_1*get_relatvieVelocity(px_1,py_1,pz_1,mass_1,px_2,py_2,pz_2,mass_2); this can redule calculationg

							
							count1++;

							
							//wigner_function=factor*exp(-(delta_r2_1/sigma_r2_1+delta_p2_1/sigma_p2_1+delta_r2_2/sigma_r2_2+delta_p2_2/sigma_p2_2+delta_r2_3/sigma_r2_3+delta_p2_3/sigma_p2_3));
							wigner_function=//get_meson_wigner_function( //get_qutraton_wigner_function(
											get_meson_wigner_function_swave_reducedmass(
											 factor,  sigma_r_1,  sigma_p_1, 
											 x_1,  y_1,  z_1,  t_f,  px_1,  py_1,  pz_1,  E_1, 
											 x_2,  y_2,  z_2,  t_f,  px_2,  py_2,  pz_2,  E_2);
						}

						dis_wigner->Fill(wigner_function,1);
						double random_n=gRandom->Uniform(0,1);
						if(random_n<wigner_function)
						{
							hadron_px=px_lab_1+px_lab_2;
							hadron_py=py_lab_1+py_lab_2;
							hadron_pz=pz_lab_1+pz_lab_2;
							hadron_energy=E_lab_1+E_lab_2;
							hadron_mass=getmass(hadron_energy,hadron_px,hadron_py,hadron_pz);
							if(frame=="lab")
							{
								x_hadron = (x_lab_1*mass_lab_1 + x_lab_2*mass_lab_2 )/(mass_lab_1+mass_lab_2);
								y_hadron = (y_lab_1*mass_lab_1 + y_lab_2*mass_lab_2 )/(mass_lab_1+mass_lab_2);
								z_hadron = (z_lab_1*mass_lab_1 + z_lab_2*mass_lab_2 )/(mass_lab_1+mass_lab_2);
								t_hadron = t_lab_1;
								if(t_hadron<t_lab_2){t_hadron=t_lab_2;}

							}
							if(frame=="cluster")
							{
								x_cluster_hadron=x_cluster_1;
								y_cluster_hadron=y_cluster_1;
								z_cluster_hadron=z_cluster_1;
								t_cluster_hadron=t_f;
								
								t_hadron=t_1;
								if(t_hadron<t_2){t_hadron=t_2;}

								
								double hadron_r_dot_n=x_cluster_hadron*n_x+y_cluster_hadron*n_y+z_cluster_hadron*n_z;
								x_hadron = x_cluster_hadron + (gamma_factor-1)*hadron_r_dot_n*n_x + gamma_factor*t_cluster_hadron*beta_x;
								y_hadron = y_cluster_hadron + (gamma_factor-1)*hadron_r_dot_n*n_y + gamma_factor*t_cluster_hadron*beta_y;
								z_hadron = z_cluster_hadron + (gamma_factor-1)*hadron_r_dot_n*n_z + gamma_factor*t_cluster_hadron*beta_z;
								t_hadron = gamma_factor*(t_cluster_hadron + beta*hadron_r_dot_n);
							}
							
							if(t_hadron<0)
							{
								cout<<"t_hadron<0"<<endl;
								continue;
							}
							
							hadron_pt=sqrt(pow(hadron_px,2)+pow(hadron_py,2));
							if(hadron_pt>0)
							{
								hadron_phi=atan2(hadron_py,hadron_px);
							}
							else
							{
								hadron_phi=NAN;
							}
							hadron_p=sqrt(pow(hadron_px,2)+pow(hadron_py,2)+pow(hadron_pz,2));
							if(hadron_p!=0){
								hadron_eta=atanh(hadron_pz/hadron_p);
							}
							else{
								hadron_eta=NAN;
							}

							hadrons_PID.push_back(9804);
							hadrons_px.push_back(hadron_px);
							hadrons_py.push_back(hadron_py);
							hadrons_pz.push_back(hadron_pz);
							hadrons_mass.push_back(hadron_mass);
							hadrons_x.push_back(x_hadron);
							hadrons_y.push_back(y_hadron);
							hadrons_z.push_back(z_hadron);
							hadrons_t.push_back(t_hadron);
							hadrons_phi.push_back(hadron_phi);
							hadrons_pt.push_back(hadron_pt);
							hadrons_p.push_back(hadron_p);
							hadrons_eta.push_back(hadron_eta);

							if(abs(hadron_eta)<1 and hadron_pt>0)
							{
								hadron_v2=cos( 2*(hadron_phi - sec_evnt_plane) );
								tprofile_hadron_v2->Fill(hadron_pt, hadron_v2, 1);
							}

							//all_hadrons_phi.push_back(hadron_phi);
							//all_hadrons_pt.push_back(hadron_pt);
							
							//double cos2phi=cos(2*hadron_phi)/4;
							//cos_2phi_vs_pt->Fill(hadron_pt/4,cos2phi,1);


							//=================================================
							//delete the partons which have been in the hadron
							squark_used_id.push_back(squark_id_l);
							sbarqk_used_id.push_back(sbarqk_id_l);
							uquark_used_id.push_back(uquark_id_l);
							ubarqk_used_id.push_back(ubarqk_id_l);
							hadronization_success=1;
							goto out_number1;

							//delete the partons which have been in the hadron
							//=================================================

						
					
				}
			}
			out_number1:
			if(0){}
		}
//=================coalescence=================================================
		hadronTree->Fill();

		hadrons_PID.clear();
		hadrons_px.clear();
		hadrons_py.clear();
		hadrons_pz.clear();
		hadrons_mass.clear();
		hadrons_x.clear();
		hadrons_y.clear();
		hadrons_z.clear();
		hadrons_t.clear();
		hadrons_phi.clear();
		hadrons_pt.clear();	
		hadrons_p.clear();	
		hadrons_eta.clear();
		//wignerfunction_value.clear();


		squarks_PID_current_evnt.clear();
		squarks_px_current_evnt.clear();
		squarks_py_current_evnt.clear();
		squarks_pz_current_evnt.clear();
		squarks_mass_current_evnt.clear();
		squarks_E_current_evnt.clear();
		squarks_E2_current_evnt.clear();
		squarks_x_current_evnt.clear();
		squarks_y_current_evnt.clear();
		squarks_z_current_evnt.clear();
		squarks_t_current_evnt.clear();	

		sbarqks_PID_current_evnt.clear();
		sbarqks_px_current_evnt.clear();
		sbarqks_py_current_evnt.clear();
		sbarqks_pz_current_evnt.clear();
		sbarqks_mass_current_evnt.clear();
		sbarqks_E_current_evnt.clear();
		sbarqks_E2_current_evnt.clear();
		sbarqks_x_current_evnt.clear();
		sbarqks_y_current_evnt.clear();
		sbarqks_z_current_evnt.clear();
		sbarqks_t_current_evnt.clear();
	}



	output->cd();

	//v2_ana->Fill();

h_deltar->Write();
h_deltap->Write();
h_deltar_deltap->Write();
	//ftree->Write();
	//hadronTree->Write();
	//v2_ana->Write();

	tprofile_hadron_v2->Write();
	output->Write();
	output->Close();


}





//===================================================================================

#endif
