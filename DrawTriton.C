#include "./filename_pncoal.h"
#include "/home/gu180/utility/draw_object_ut.h"
#include "/home/gu180/utility/tf1_ut.h"
#include "./version.h"

typedef vector<TLorentzVector> particle;
typedef vector<vector<TLorentzVector>> particles;

	tag intag=vtag; //"he3";
	tag outtag=vtag; //"he3";
//tag dataname="./triton_draw.root";
tag dataname=data_path+Form("draw_triton/triton_draw_%s.root", intag.Data());

TH2D* th2d_Nn_ratio;
TH2D* th2d_Np_ratio;
TProfile* tp_Nn_ratio;
TProfile* tp_Np_ratio;
TProfile* tp_ratio_Nn;
TH2D* th2d_Nn_Np;
TH2D* th2d_Nd_Nt;
TH2D* th2d_Nh_Nt;

void SetH()
{
	th2d_Nn_ratio=new TH2D("th2d_ratio","ratio vs. Nn", 200,0,200, 100000,0,10);
	th2d_Np_ratio=new TH2D("th2d_ratio","ratio vs. Np", 200,0,200, 100000,0,10);
	tp_ratio_Nn=new TProfile("tp_ratio_Nn", "<Nn> vs. ratio", 1000,0,0.1);
	tp_Nn_ratio=new TProfile("tp_Nn_ratio", "<ratio> vs. Nn", 200,0,200);
	tp_Np_ratio=new TProfile("tp_Np_ratio", "<ratio> vs. Np", 200,0,200);

	th2d_Nn_Np=new TH2D("th2d_Nn_Np", "Np vs. Nn", 200,0,200, 200,0,200);
	th2d_Nd_Nt=new TH2D("th2d_Nd_Nt", "Nt vs. Nd", 200,0,200, 200,0,200);
	th2d_Nh_Nt=new TH2D("th2d_Nh_Nt", "Nt vs. Nh", 200,0,200, 200,0,200);
	
}

void LoadH(TFile* input)
{
	th2d_Nn_ratio=(TH2D*) input->Get("th2d_Nn_ratio");
	th2d_Np_ratio=(TH2D*) input->Get("th2d_Np_ratio");
	tp_ratio_Nn=(TProfile*) input->Get("tp_ratio_Nn");
	tp_Nn_ratio=(TProfile*) input->Get("tp_Nn_ratio");
	tp_Np_ratio=(TProfile*) input->Get("tp_Np_ratio");
	th2d_Nn_Np=(TH2D*) input->Get("th2d_Nn_Np");
	th2d_Nd_Nt=(TH2D*) input->Get("th2d_Nd_Nt");
	th2d_Nh_Nt=(TH2D*) input->Get("th2d_Nh_Nt");
}

void WriteH(TFile* output)
{
	output->cd();
	th2d_Nn_ratio->Write("th2d_Nn_ratio");
	th2d_Np_ratio->Write("th2d_Np_ratio");
	tp_Nn_ratio->Write();
	tp_Np_ratio->Write();
	tp_ratio_Nn->Write();

	th2d_Nn_Np->Write();
	th2d_Nd_Nt->Write();
	th2d_Nh_Nt->Write();
}

void tritondata()
{
	SetH();

	tag in=getfilename_triton(outtag,"");
	
	TFile* input=TFile::Open(in);
	if(input==NULL){cout<<"Can't find "<< in <<endl; return;}
	
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
		
		int N_t_free=tritons_free.size();
		int N_h_free=heliums_free.size();
		int N_d_free=deuterons_free.size();
		int N_p_free=protons_free.size();
		int N_n_free=neutrons_free.size();
		
		//double ratio=double(N_t)*double(N_p)/double(N_d*N_d);

		cout<<"Event "<<i_event<<endl;
#ifdef DEBUGMODE
		cout<<"Np="<<N_p<<" Np_free="<<N_p_free<<endl;
		cout<<"Nn="<<N_n<<" Nn_free="<<N_n_free<<endl;
		cout<<"N_d="<<N_d<<" N_d_free="<<N_d_free<<endl;
		cout<<"N_t="<<N_t<<" N_t_free="<<N_t_free<<endl;
#endif
		th2d_Nn_Np->Fill(N_n_free, N_p_free);
		th2d_Nd_Nt->Fill(N_d_free, N_t_free);
		th2d_Nh_Nt->Fill(N_h_free, N_t_free);

		if(N_d_free==0){cout<<"No deuteron, skip"<<endl; continue;}

		double ratio=double(N_t_free)*double(N_p_free)/double(N_d_free*N_d_free);
		th2d_Nn_ratio->Fill(N_n_free, ratio);
		tp_Nn_ratio->Fill(N_n_free, ratio);
		tp_ratio_Nn->Fill(ratio, N_n_free);

		th2d_Np_ratio->Fill(N_p_free, ratio);
		tp_Np_ratio->Fill(N_p_free, ratio);
		
	}

	MakeDir(dataname);
	TFile* output=TFile::Open(dataname, "recreate");
	WriteH(output);
	output->Write();
	delete output;
	
}


void Draw_th2d(TH2D * th2d_input, tag on, tag xt, tag yt, vals range=vals(0))
{
	TCanvas c("c","c");
	th2d_input->RebinY(1000);
	th2d_input->GetYaxis()->SetRangeUser(range[2], range[3]);
	th2d_input->GetXaxis()->SetRangeUser(range[0], range[1]);
	th2d_input->GetXaxis()->SetTitle(xt);
	th2d_input->GetYaxis()->SetTitle(yt);
	th2d_input->Draw("colz");
	c.SaveAs(on);
}

void Draw_th2d(tag op)
{
	Draw_th2d(th2d_Np_ratio, op+"th2d_Np_ratio.pdf", "Np", "ratio", vals{0,30,0,10});
	Draw_th2d(th2d_Nn_ratio, op+"th2d_Nn_ratio.pdf", "Nn", "ratio", vals{0,30,0,10});
	Draw_th2d(th2d_Nn_Np, op+"th2d_Nn_Np.pdf", "Nn", "Np", vals{0,30,0,30});
	Draw_th2d(th2d_Nd_Nt, op+"th2d_Nd_Nt.pdf", "Nd", "Nt", vals{0,30,0,30});
	Draw_th2d(th2d_Nh_Nt, op+"th2d_Nh_Nt.pdf", "Nh", "Nt", vals{0,30,0,30});
}

void DrawTp(TProfile* tpin, tag xt, tag yt, tag on, vals range=vals(0))
{
	TF1 f("f", "[0]+[1]*x", -100,100);
	tpin->Fit(&f);
	TCanvas c(on, on);
	tpin->Draw();
	tpin->GetXaxis()->SetTitle(xt);
	tpin->GetYaxis()->SetTitle(yt);
	
	TLegend leg(0.6,0.2,0.99,0.7);
	leg.SetHeader(SplitLines(fpars(&f)));
	leg.Draw("same");
	
	if(range.size()>=2 and range[0]<range[1]){tpin->GetXaxis()->SetRangeUser(range[0], range[1]);}
	if(range.size()>=4 and range[2]<range[3]){tpin->GetYaxis()->SetRangeUser(range[2], range[3]);}
	c.SaveAs(on);
}

void Draw_tp(tag op)
{
	tag on1=op+"tp_ratio_Nn.pdf";
	DrawTp(tp_ratio_Nn, "ratio", "<Nn>", on1, vals{0,0.1});
	tag on_n=op+"tp_Nn_ratio.pdf";
	DrawTp(tp_Nn_ratio, "Nn", "<ratio>", on_n);

	tag on_p=op+"tp_Np_ratio.pdf";
	DrawTp(tp_Np_ratio, "Np", "<ratio>", on_p);
	
}
	

void tritondraw()
{
	TFile* input=TFile::Open(dataname);
	LoadH(input);
	tag op=plot_path+outtag+"/";
	MakeDir(op);
	Draw_th2d(op);
	Draw_tp(op);
	
	delete input;
	
}
void DrawTriton()
{
	tritondata();
	tritondraw();
}
