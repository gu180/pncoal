
#include "./filename_pncoal.h"
#include "./Wigner.h"
#include "./version.h"

void reader_test()
{
	gROOT->ProcessLine(".L loader.C+");	
	
	tag in=getfilename_deuteron(vtag, "");
	TFile* input=TFile::Open(in);
	TTree* tree_deuterons= (TTree*) input->Get("tree_deuterons");

	TTreeReader reader;
	reader.SetTree(tree_deuterons);
	//TTreeReaderValue<vector<TLorentzVector>> ps;
	TTreeReaderValue<vector<vector<TLorentzVector>>> protons(reader, "protons");

}
