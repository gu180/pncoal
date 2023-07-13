#ifndef WIGNER_H_
#define WIGNER_H_

//#define DEBUGMODE

const double mass_proton=0.938272088;
const double mass_neutron=0.939565420;

int CountFree(vector<bool> useds)
{
	int output=0;
	for(int i=0; i<useds.size(); ++i)
	{
		if(useds[i]==0){output++;};
	}
	return output;
}

struct WignerResult
{
	double wigner_val;
	TLorentzVector r_center;
	TLorentzVector r_lab;
};

WignerResult wignerfunction(vector<TLorentzVector> &a, vector<TLorentzVector> &b, double sigma_r, double sigma_p)
{
	//if(1)//boost to the center of mass frame of particle a and b.
	{
	}
		TLorentzVector p_hadron=a[1]+b[1];
		TVector3 boost = p_hadron.BoostVector();
		a[0].Boost(-boost); a[1].Boost(-boost);
		b[0].Boost(-boost); b[1].Boost(-boost);
	//cout<<"a.p="; a[1].Print();
	//cout<<"b.p="; b[1].Print();
	TVector3 velocity_a=a[1].BoostVector();
	TVector3 velocity_b=b[1].BoostVector();
	TVector3 position_a=a[0].Vect();
	TVector3 position_b=b[0].Vect();
	double t1=a[0].T();
	double t2=b[0].T();
	double tf=max(t1,t2);

	position_a=position_a+(tf-t1)*velocity_a;
	position_b=position_b+(tf-t2)*velocity_b;
	double mass_a=a[1].M();
	double mass_b=b[1].M();
	double mass_center=mass_a+mass_b;
	
	double part_a=mass_a/mass_center;
	double part_b=mass_b/mass_center;
	TVector3 position_center = part_a*position_a + part_b*position_b;
	double time_center=tf;

	TLorentzVector r_hadron_center;
	r_hadron_center.SetVect(position_center);
	r_hadron_center.SetT(time_center);;
	TLorentzVector r_hadron_lab=r_hadron_center;
	r_hadron_lab.Boost(boost);
#ifdef DEBUGMODE
cout<<"boost= ";boost.Print();
cout<<"a.p="; a[1].Print();
cout<<"b.p="; b[1].Print();
cout<<"r_hadron_center "; r_hadron_center.Print();
cout<<"r_hadron_lab "; r_hadron_lab.Print();
#endif

	WignerResult output;
	output.r_center=r_hadron_center;
	output.r_lab=r_hadron_lab;

	TVector3 deltar=position_a - position_b;
	TVector3 deltap=a[1].Vect()-b[1].Vect();


	output.wigner_val=8*exp(-deltar.Mag2()/(sigma_r*sigma_r)-deltap.Mag2()/(sigma_p*sigma_p)); //Gaussian Wigner function
	


	return output;

}

#endif
