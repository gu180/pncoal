const double mass_proton=0.938272088;
const double mass_neutron=0.939565420;

TH1D* h_pt;

double random_r_phi()//generate random position-> phi
{
	gRandom->SetSeed(0);
	return gRandom->Uniform(-TMath::Pi(), +TMath::Pi());
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
	h_pt->Fill(x);
	return x;
}

double random_p_eta()//generate random momentum -> eta
{
	gRandom->SetSeed(0);
	return gRandom->Uniform(-1,1); //assume eta to be uniformly distributed between -1, +1. This is an occasional value for example. eta is pseudorapidity https://en.wikipedia.org/wiki/Pseudorapidity
}

vector<TLorentzVector> single_nucleon(int charge)
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

void generate_pn()
{gRandom->SetSeed(0);
	TFile* output=TFile::Open("nucleon.root", "recreate");//create a root file as output to store all the nucleon information
	TTree* tree_nucleons=new TTree("tree_nucleons", "a tree to store nucleon information");
	//TTree* tree_proton=new TTree("tree_proton", "a tree to store proton information");
	//TTree* tree_neutron=new TTree("tree_neutron", "a tree to store neutron information");
h_pt=new TH1D("h_pt", "pt spectrum of protons", 100, 0, 10);
	int Nevent=10; //number of events

	vector<vector<TLorentzVector>> protons;
	vector<vector<TLorentzVector>> neutrons;

	tree_nucleons->Branch("protons", &protons);
	tree_nucleons->Branch("neutrons", &neutrons);

	for(int i=0; i< Nevent; ++i)
	{
		int number_proton=100; //number of protons, here is just an exmaple
		int number_neutron=100;
		cout<<"Event "<<i<<endl;
		protons.clear();
		neutrons.clear();

		for(int j=0; j<number_proton; ++j)
		{
			vector<TLorentzVector> proton=single_nucleon(1);
			protons.push_back(proton);
		}

		for(int j=0; j<number_neutron; ++j)
		{
			vector<TLorentzVector> neutron=single_nucleon(0);
			neutrons.push_back(neutron);
		}
		tree_nucleons->Fill();
	}

	output->cd();
	h_pt->Write();
	output->Write();
	output->Close();
}
