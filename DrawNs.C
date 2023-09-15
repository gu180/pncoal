#include "./filename_pncoal.h"
#include "./GetInfo.h"
#include "/home/gu180/utility/draw_object_ut.h"

void DrawNsByFn(tags fns, tag op, tags labels)
{

//void DrawGrs(TString grname, vector<TString> filenames, vector<TString> labels, TString outputname, TString xtitle="", TString ytitle="", TString title="", tag opt="", vals ranges=vals(0))
	
	MakeDir(op);

	vector<vals> ranges{{0,50}, {0,50}, {0,10, 1E4, 1E5}, {0,5}, {0,5}};
	for(int i=0; i<5; ++i)
	{
		//cout<<Nnames[i]<<": "<<endl;
		tag hname=Form("th1d_%s_free", Nnames[i].Data());
		vector<TH1D> hs=GetTs<TH1D>(hname, fns);
		Print(fns);
		tags labels_;
		for(int j=0; j<fns.size(); ++j)
		{
			cout<<fns[j]<<endl;
			double N_allevent=ReadNum(fns[j], Nnames[i]+"_free");
			cout<<"N_allevent="<<N_allevent<<" ";
			double N_allevent_th1d=hs[j].GetMean()*hs[j].GetEntries();
			cout<<"N_allevent_th1d="<<N_allevent_th1d<<endl;
			cout<<"In DrawRatio hs[j].GetBincontent(20)= "<<hs[j].GetBinContent(20)<<endl;
			labels_.push_back(Form("%s <N>=%lf stddev=%lf", labels[j].Data(), hs[j].GetMean(), hs[j].GetStdDev()));
			
		}
		//DrawObjGrs<TH1D>(hname, fns, labels_, op+Form("dis_%s_free.png", Nnames[i].Data()), Ntitles[i], "Entries", "", "", ranges[i]);
		DrawObjGrs<TH1D>(hname, fns, labels_, op+Form("dis_%s_free.pdf", Nnames[i].Data()), Ntitles[i], "Entries", "", "setlogy histo", ranges[i]);
	}
}

tags GetFns(tags itags)
{
	tags fns;
	for(int i=0; i<itags.size(); ++i)
	{
		fns.push_back(getfilename_drawtriton(itags[i]));
	}
	return fns;
}

tag GetOp(tag otag)
{
	return plot_path+Form("Ns/%s/", otag.Data());
}
	

void DrawNsByTag(tags itags, tag otag, tags labels)
{
	tags fns=GetFns(itags);
	tag op=GetOp(otag);
	Print(fns);

	DrawNsByFn(fns, op, labels);
}

void Draw_v9()
{
	tag adtag="v10";
	//vector<double> Nsigmas{0, 1 , 2, 3, 4, 5, 6, 7, 8, 9 ,10, 11, 12, 13, 14};
	vector<double> Nsigmas{0, 1 , 2, 3, 4, 5, 6, 7, 8, 9 ,10, 11, 12, 13, 14};
	tags itags;
	tags labels;
	for(int i=0; i<Nsigmas.size(); ++i)
	{
		if(i%3!=0){continue;}
		double sigma_proton=Nsigmas[0];	
		double sigma_neutron=Nsigmas[i];
		tag itag=Form("%sNsigma_proton%.1f_Nsigma_neutron%.1f", adtag.Data(), sigma_proton, sigma_neutron);
		itags.push_back(itag);
		labels.push_back(Form("#sigma=%.1f", sigma_neutron));
	}

	tag otag=adtag;
	DrawNsByTag(itags, otag, labels);
}	

void Draw_v15()
{
	tag adtag="v18_N100000";
	//vector<double> Nsigmas{0, 1 , 2, 3, 4, 5, 6, 7, 8, 9 ,10, 11, 12, 13, 14};
	//vector<double> Nsigmas{0, 1 , 2, 3, 4, 5, 6, 7, 8, 9 ,10, 11, 12, 13, 14};
	vector<double> Nsigmas{0, 1 , 2, 3, 4, 5, 6};
	//vector<double> Nsigmas{0, 1,6};
	tags itags;
	tags labels;
	for(int i=0; i<Nsigmas.size(); ++i)
	{
		//if(i%3!=0){continue;}
		//double sigma_proton=Nsigmas[0];	
		double sigma_proton=0;
		double sigma_neutron=Nsigmas[i];
		tag itag=Form("%sNsigma_proton%.1f_Nsigma_neutron%.1f", adtag.Data(), sigma_proton, sigma_neutron);
		itags.push_back(itag);
		labels.push_back(Form("#sigma_{neutron}=%.1f", sigma_neutron));
	}

	tag otag=adtag;
	DrawNsByTag(itags, otag, labels);
}	
void DrawNs()
{
	Draw_v15();
}

