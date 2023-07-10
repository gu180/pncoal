
typedef TLorentzVector tv;

class particle
{
private:
	int pid;
	TLorentzVector r;
	TLorentzVector p;
	int used;
public:
	int GetPid();
	TLorentzVector GetR();
	TLorentzVector GetP();
	int GetUsed();
	
	void SetPid(int pid_in);
	void SetR(TLorentzVector r_in);
	void SetP(TLorentzVector p_in);
	void SetUsed(int used_in);
	
};


class particles
{
private;
	vector<particle> vec_particles;
	
	vector<int> pids;
	vector<TLorentzVector> rs;
	vector<TLorentzVector> ps;
	vector<int> useds;
	
	TTree* tree;
	 
	
public;
	particle GetParticle(int i);
	void Clear();
	void AddParticle(particle &a);
	void Store(TFile* file, TString particles_name);
	void Read( TFile* file, TString particles_name);//tree=file->Get("particles_name"), TTreeReadValue....

	void SetTree(TTree* tree_in); //tree=tree_in
	void FillTree(); //tree_in->Fill();
};


void LoadEvent(Long64_t ievent)
{
}


particle_collection
void LoadCollection(tag pname)
particle particle_collection. GetParticle(int i)

void StoreInTree(TTree* tree)
void ReadFromTree(TTree* tree, tag pcname)
//particle collection name



