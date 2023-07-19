#include "./filename_pncoal.h"
#include "./GetInfo.h"
#include "/home/gu180/utility/draw_object_ut.h"

void DrawNsByFn(tags fns, tag op, tags labels)
{

//void DrawGrs(TString grname, vector<TString> filenames, vector<TString> labels, TString outputname, TString xtitle="", TString ytitle="", TString title="", tag opt="", vals ranges=vals(0))
	
	MakeDir(op);

	vector<vals> ranges{{0,50}, {0,50}, {0,20}, {0,20}, {0,20}};
	for(int i=0; i<5; ++i)
	{
		DrawGrs<TH1D>(Form("th1d_%s_free", Nnames[i].Data()), fns, labels, op+Form("dis_%s_free.pdf", Nnames[i].Data()), Ntitles[i], "Entries", "", "", ranges[i]);
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

void DrawNs()
{
	Draw_v9();
}

