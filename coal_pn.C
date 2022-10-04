const double mass_proton=0.938272088;
const double mass_neutron=0.939565420;

TH1D* h_pt_proton;

double random_r_phi()//generate random position-> phi
{
	gRandom->SetSeed(0);
	return gRandom->Uniform(-TMath::Pi(), -TMath::Pi());
}

double random_r_rho()//generate rnadom position -> rho	(here is a cylindrical coordinate, z-axis is along the beam direction)
							//This function will return a rho value with PDF proportional to rho P(rho)=rho;
{
	gRandom->SetSeed(0);
	double r_max=20; //set the maximum rho as 20 fm, this value can be modified, you can search reference for a more reasonable value. This is an occasional value for example.
	double x;
	double y;
	do
	{
		x=gRandom->Uniform(0, r_max);
		y=gRandom->Uniform(0, r_max);
	}while(x<y);
	return x;
}

double random_r_z()//generate random position -> z
{
	gRandom->SetSeed(0);
	return gRandom->Uniform(-10,10); //assume z to be uniformly distributed between -10, +10 fm. This is an occasional value for example.
}

double random_p_phi()//generate random momentum-> phi  Uniform distributed between -pi +pi;
{
	gRandom->SetSeed(0);
	return gRandom->Uniform(-TMath::Pi(), -TMath::Pi());
}

double random_p_pt()//generate rnadom momentum -> pt	(here is a cylindrical coordinate, z-axis is along the beam direction)
							//This function will return a pt value with PDF as an expoential function  P(pt)=exp(-pt/10);
{
	gRandom->SetSeed(0);
	double r_max=20; //set the maximum pT as 10 GeV, This is an occasional value for example.
	double x;
	double y;
	do
	{
		x=gRandom->Uniform(0, r_max);
		y=gRandom->Uniform(0, r_max);
	}while(exp(-x/(10.0))<y);
	h_pt_proton->Fill(x);
	return x;
}

double random_p_eta()//generate random momentum -> eta
{
	gRandom->SetSeed(0);
	return gRandom->Uniform(-1,1); //assume eta to be uniformly distributed between -1, +1. This is an occasional value for example. eta is pseudorapidity https://en.wikipedia.org/wiki/Pseudorapidity
}

vector<TLorentzVector> single_nucleon(int charge)//TLorentzVector is a ROOT class which describe a 4-vector. 
												 //Here use 2 TLorentzVectors to describe a particle, 1 for position, 1 for momentum.
												 //vector is a c++ class which can be used as a container. 
												 //vector<TLorentzVector> means a container and the type of the elements is TLorentzVector
{
	TLorentzVector r;//position 4 vector
	TLorentzVector p;//momentum 4 vector
	r.SetPerp(random_r_rho());
	r.SetPhi(random_r_phi());
	r.SetZ(random_r_z());
	r.SetT(0);//assume the time to 0, which need be discussed later
	double mass;
	if(charge==0){mass=mass_neutron;}//neutron
	if(charge==1){mass=mass_proton;}//proton
	p.SetPtEtaPhiM(random_p_pt(), random_p_eta(), random_p_phi(), mass);
	vector<TLorentzVector> particle;
	particle.push_back(r);
	particle.push_back(p);
	return particle;
}

double wignerfunction(vector<TLorentzVector> a, vector<TLorentzVector> b, double sigma_r, double sigma_p)
{
	if(1)//boost to the center of mass frame of particle a and b.
	{
		TLorentzVector p_hadron=a[1]+b[1];
		TVector3 boost = p_hadron.BoostVector();
		a[0].Boost(-boost); a[1].Boost(-boost);
		b[0].Boost(-boost); b[1].Boost(-boost);
	}
	TVector3 velocity_a=a[1].BoostVector();
	TVector3 velocity_b=b[1].BoostVector();
	TVector3 position_a=a[0].Vect();
	TVector3 position_b=b[0].Vect();
	double t1=a[0].T();
	double t2=b[0].T();
	double tf=max(t1,t2);

	position_a=position_a+(tf-t1)*velocity_a;
	position_b=position_b+(tf-t2)*velocity_b;

	TVector3 deltar=position_a - position_b;
	TVector3 deltap=a[1].Vect()-b[1].Vect();


	double wigner=exp(-deltar.Mag2()/(sigma_r*sigma_r)-deltap.Mag2()/(sigma_p*sigma_p)); //Gaussian Wigner function

	return wigner;

}

void coal_pn()//This example shows the integral to calculate the average number of deutron per event
//All the values in this script are set causally, only as an example.
{

	gRandom->SetSeed(0);
	TFile* output=TFile::Open("deutron_pt.root", "recreate");//create a root file as output to store all the nucleon information
	
	h_pt_proton=new TH1D("h_pt_proton", "pt spectrum of protons", 100, 0, 10);

	TH1D* h_pt_deutron=new TH1D("h_pt_proton", "pt spectrum of deutrons", 100, 0, 10);
	TH1D* h_wigner=new TH1D("h_wigner", "distribution of wigner ", 100, 0, 2);
	double sigma_r=1.0; //1.0 fm
	double sigma_p=1/(5.068*sigma_r);//1.0 fm^-1=
	int N_event=1000;//Number of proton neutron pairs
	double yield_sum=0;
	for(int i=0; i< N_event; ++i)
	{
		if(i%100==0){cout<<"Processing Event "<<i<<endl;}
		int N_proton=20;//number of proton in each event, the value here is just an example
		int N_neutron=20;
		for(int j=0;j<N_proton;++j)
		{
			for(int k=0; k<N_neutron; ++k)
			{
				vector<TLorentzVector> proton=single_nucleon(1);
				vector<TLorentzVector> neutron=single_nucleon(0);
				//You can also add some cuts here. For example:
				/*
				TLorentzVector deutron_p=proton[1]+neutron[1];
				if(deutron_p.Pt()<0.4){continue;}//If the transverse momentum of duetron is smaller than 0.4 GeV, then don't count this deutron.
				*/
				double wigner=wignerfunction(proton, neutron, sigma_r, sigma_p);
				yield_sum+=wigner;
				h_wigner->Fill(wigner);
				//=====Get pt spectrum of duetron
				TLorentzVector deutron_p=proton[1]+neutron[1];
				h_pt_deutron->Fill(deutron_p.Pt(), wigner);
			}
		}
		
	}
	double yield_perEvent=yield_sum/N_event;//This is the average number of coalescenced deutron per event.

	cout<<"There is on average "<<yield_perEvent<< " deutron in each event"<<endl;

	//==========================
	h_pt_deutron->Scale(1.0/double(N_event));//scale the pt spectrum to get the pt spectrum for each event
	//h_pt_proton->Scale(1.0/h_pt_proton->GetBinWidth(1));
	//======draw the pt spectrum
	TCanvas* c=new TCanvas();
	h_pt_deutron->Draw();
	h_pt_deutron->GetXaxis()->SetTitle("p_{T} (GeV)");
	h_pt_deutron->GetYaxis()->SetTitle("Count/Events");
	c->SaveAs("deutron_pt_specturm.pdf");
	//==========================

	//==Store the histogram to the output root file
	output->cd();
	h_pt_proton->Write();
	h_wigner->Write();
	h_pt_deutron->Write();
	//==Write the root file to disk
	output->Write();
	output->Close();
	delete output;

}
