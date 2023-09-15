#include "GetPN.h"
#include "GetDeuteron.h"
#include "GetTriton.h"
#include "GetInfo.h"


void RunCoal_single(double sigma_proton, double sigma_neutron, tag adtag="")
{
	tag vtag=Form("%sNsigma_proton%.1f_Nsigma_neutron%.1f", adtag.Data(), sigma_proton, sigma_neutron);
	tag vtagin=Form("v13Nsigma_proton%.1f_Nsigma_neutron%.1f", adtag.Data(), sigma_proton, sigma_neutron);

	GetPN(vtag, sigma_proton, sigma_neutron);
	GetDeuteron(vtag, vtag);
	GetTriton(vtag, vtag);
	/*
	*/
	
	GetInfo(vtag, vtag);

}

void CopyCode(tag adtag)
{
	tag optag=Form("../data/copycode/%s", adtag.Data());
	gSystem->Exec("mkdir -p "+optag);
	gSystem->Exec(Form("cp *.h %s", optag.Data()));
	gSystem->Exec(Form("cp *.C %s", optag.Data()));
	gSystem->Exec(Form("cp *.sh %s", optag.Data()));
}

void RunCoalSingleVtag()
{
	tag adtag=INSERTVTAG;
	double nsp=INSETNSP;
	double nsn=INSETNSN;
	RunCoal_single(nsp, nsn, adtag);
}
