#include "/home/gu180/utility/vector_ut.h"
#include "/home/gu180/utility/tstring_ut.h"
#include "./filename_pncoal.h"
#include "/home/gu180/utility/gr_operator_ut.h"
#include "GetInfo.h"
#include "/home/gu180/utility/draw_object_ut.h"

tag gAdtag="v18_N100000";
//tag gAdtag="v12";
//vals gSigmas{0, 1 , 2, 3, 4, 5, 6, 7, 8, 9 ,10, 11, 12, 13, 14};
vals gSigmas{0, 1 , 2, 3, 4, 5, 6};
vals gSigmas_err(100,0);

vector<double> GetRatio(double sigma_proton, double sigma_neutron, int idx_ratio, tag adtag)
{
	//tag vtag=Form("%sNsigma%.0f", adtag.Data(), sigma);
	tag vtag=Form("%sNsigma_proton%.1f_Nsigma_neutron%.1f", adtag.Data(), sigma_proton, sigma_neutron);
	cout<<"GetRatio vtag="<<vtag<<endl;
	tag in=getfilename_drawtriton(vtag);
	tag hname=GetHname("tps", 0,idx_ratio);
	TFile* input=TFile::Open(in);

	cout<<"input: "<<input->GetName()<<" hname="<<hname<<endl;
	TProfile* tp_Nn_ratio=(TProfile*) input->Get(hname);
	int nbins=tp_Nn_ratio->GetXaxis()->GetNbins();
	tp_Nn_ratio->RebinX(nbins);
	//double ratio_val=tp_Nn_ratio->GetBinContent(1);
	double ratio_val=ReadNum(input, Rnames[idx_ratio]);
	double ratio_err=ReadNum(input, Rnames[idx_ratio]+"_err");
	double ratio_err_old=tp_Nn_ratio->GetBinError(1);
	cout<<"Check ratio_err new: "<<ratio_err<<" ratio_err old: "<<ratio_err_old<<endl;
	
	delete input;
	

	vector<double> output{ratio_val, ratio_err};
	return output;
}
/*	
vector<double> GetRatioVals(vector<double> sigmas, tag adtag)
{
	vals ratiovals;
	for(int i=0; i<sigmas.size(); ++i)
	{
		vals ratio=GetRatio(sigmas[i], adtag);
		double ratio_val=ratio[0];
		ratiovals.push_back(ratio_val);
	}
	return ratiovals;
}

vector<double> GetRatioErrs(vector<double> sigmas, tag adtag)
{
	vals ratioerrs;
	for(int i=0; i<sigmas.size(); ++i)
	{
		vals ratio=GetRatio(sigmas[i], adtag);
		double ratio_err=ratio[1];
		ratioerrs.push_back(ratio_err);
	}
	return ratioerrs;
}
*/

void DrawRatioSigma_v5()
{
	
	tag adtag="v5";
	vals Nsigmas{1,2,3,4,5};
	vals Nsigmas_err(5,0);
	vals ratiovals;//=GetRatioVals(Nsigmas, adtag);
	vals ratioerrs;//=GetRatioErrs(Nsigmas, adtag);
	
	gr gr_rs=GetGrObj(Nsigmas, ratiovals, Nsigmas_err, ratioerrs);
	
	TCanvas c("c","c");
	gr_rs.Draw("APL");
	gr_rs.GetXaxis()->SetTitle("#sigma_{N}");
	gr_rs.GetYaxis()->SetTitle("ratio");
	
	tag on_plot=plot_path+Form("ratio_sigma/gr_ratio_sigma%s.pdf", adtag.Data());
	MakeDir(on_plot);
	c.SaveAs(on_plot);
}

TH2D GetTH2DRatio(vals sigmas, int idx_ratio, tag adtag)
{
	TH2D h("th2d_ratio_sigma_proton_sigma_neutron", "", 10, 0-0.5, 10-0.5, 10, 0-0.5, 10-0.5);
	int n=sigmas.size();
	for(int i=0; i<n; ++i)
	{
		for(int j=0; j<n; ++j)
		{
			double xval=sigmas[i];
			double yval=sigmas[j];
		
			int xbin=h.GetXaxis()->FindBin(xval);
			int ybin=h.GetYaxis()->FindBin(yval);
			
			vector<double> ratio=GetRatio(xval, yval, idx_ratio, adtag);
			h.SetBinContent(xbin, ybin, ratio[0]);
			h.SetBinError(xbin, ybin, ratio[1]);
		}
	}
	return h;
}

void DrawTH2DRatio(int idx_ratio)
{
	tag adtag=gAdtag;
	TH2D h=GetTH2DRatio(gSigmas, idx_ratio, adtag);
	TCanvas c("c","c");
	PlotStyleTCanvas(c);
	h.Draw("lego");
	PlotStyleTH2D(h);
	h.GetXaxis()->SetTitle("#sigma_{proton}");
	h.GetYaxis()->SetTitle("#sigma_{neutron}");
	h.GetZaxis()->SetTitle(Rtitles[idx_ratio]);
	
	tag on=plot_path+Form("%s/th2d_ratio%d_sigmap_sigman.root", adtag.Data(), idx_ratio);
	c.SaveAs(on);
}
void DrawTH2DRatio()
{
	DrawTH2DRatio(0);			
	DrawTH2DRatio(1);			
}
	
	
void DrawRS()
{
	tag adtag=gAdtag;//"v7";
	//vals sigmas{0,1,2,3,4,5,6};
	tags pnames{"neutron", "proton"};
	//tags pnames{"total"};
	
	vals sigmas=gSigmas;
	vals sigmas_err=gSigmas_err;

	for(int idx_N=0; idx_N<1; ++idx_N)
	{
	for(int idx_ratio=0; idx_ratio<Nratio; ++idx_ratio)
	{

	vector<gr> grs_rs;
	vector<TF1> tf1s_rs;
	tags labels;	
	tags labels_fit;	
	tag on=plot_path+Form("%s/%s_vs_sigma_%s.pdf", adtag.Data(), Rnames[idx_ratio].Data(), pnames[idx_N].Data());
	//tag on_fit=plot_path+Form("%s/%s_vs_sigma_%s_withfits.pdf", adtag.Data(), Rnames[idx_ratio].Data(), pnames[idx_N].Data());
	tag on_fit=plot_path+Form("%s/%s_Nmean_Ratio_vs_dn2_%s_withfits_NmeanUncertaintyUnrel.pdf", adtag.Data(), Rnames[idx_ratio].Data(), pnames[idx_N].Data());
	MakeDir(on);

	for(int i=0; i<1; ++i)
	{
		double sigma1=sigmas[i];
		//labels.push_back(Form("#sigma_{%s}=%.1f", pnames[1-idx_N].Data(), sigma1));
		labels.push_back(Form("#sigma_{%s}=%.1f", pnames[idx_N].Data(), sigma1));

		vals ratio_vals;
		vals ratio_errs;
		vals xvals;
		for(int j=0; j<sigmas.size(); ++j)
		{
			double sigma2=sigmas[j];//*sigmas[j]/(20*20);
			vector<double> ratio;
			//if(idx_N==0){ratio=GetRatio(sigma1, sigma2, idx_ratio, adtag);}
			//if(idx_N==1){ratio=GetRatio(sigma2, sigma1, idx_ratio, adtag);}
			//ratio=GetRatio(sigma2, sigma2, idx_ratio, adtag);
			ratio=GetRatio(sigma1, sigma2, idx_ratio, adtag);
			ratio_vals.push_back(ratio[0]);
			ratio_errs.push_back(ratio[1]);

			double xval=sigmas[j]*sigmas[j]/(20*20);
			xvals.push_back(xval);
			
		}
		//gr gr_rs=GetGrObj(sigmas, ratio_vals, sigmas_err, ratio_errs);
		gr gr_rs=GetGrObj(xvals, ratio_vals, sigmas_err, ratio_errs);
		TF1 tf1_rs("tf1_rs", "pol1", 0, 10);
		gr_rs.Fit(&tf1_rs);
		double slope_val=tf1_rs.GetParameter(1);
		double slope_err=tf1_rs.GetParError(1);
		//labels_fit.push_back(Form("%s, slope=%s",labels[i].Data(), ValErr(slope_val, slope_err).Data()));
		double chi2=tf1_rs.GetChisquare();
		double ndf=tf1_rs.GetNDF();
		labels_fit.push_back(Form("slope=%s #chi^{2}/dof=%.2f", ValErr(slope_val, slope_err).Data(), chi2/ndf));
	
		grs_rs.push_back(gr_rs);
		tf1s_rs.push_back(tf1_rs);
	}

	DrawObjGrs(grs_rs, labels, on, Form("#sigma_{%s}",pnames[idx_N].Data()), Rtitles[idx_ratio]);
	//DrawObjGrsFits(grs_rs, tf1s_rs, labels_fit, on_fit, Form("#sigma_{%s}",pnames[idx_N].Data()), Rtitles[idx_ratio],"","", vals{0,15,0,1.2});
	//DrawObjGrsFits(grs_rs, tf1s_rs, labels_fit, on_fit, Form("(#sigma/<N>)^{2}_{%s}",pnames[idx_N].Data()), Rtitles[idx_ratio],"","", vals{-0.0,0.1,0.35,0.55});
	//pnames[idx_N]="nucleon";
	//DrawObjGrsFits(grs_rs, tf1s_rs, labels_fit, on_fit, Form("(#sigma/<N>)^{2}_{%s}",pnames[idx_N].Data()), Rtitles[idx_ratio],"","", vals{-0.0,0.1,0.35,0.55});
	//DrawObjGrsFits(grs_rs, tf1s_rs, labels_fit, on_fit, Form("(#sigma/<N>)^{2}_{%s}",pnames[idx_N].Data()), Rtitles[idx_ratio],"","");
	DrawObjGrsFits(grs_rs, tf1s_rs, labels_fit, on_fit, Form("(#sigma/<N>)^{2}_{%s}",pnames[idx_N].Data()), Rtitles_allevent[idx_ratio],"","");
	
	}
	}
}
	
void DrawRatioSigma()
{
	
	DrawRS();
	//DrawTH2DRatio();
}
