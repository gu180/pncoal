#ifndef FILENAME_PNCOAL_H_
#define FILENAME_PNCOAL_H_
typedef TString tag;
typedef TString name;
typedef vector<TString> tags;

const static tag data_path="../data/";
const static tag plot_path="../plot/";

name getpath(name filename)
{
	int N=filename.Sizeof()-2;cout<<"getpath "<<filename<<" N="<<N<<endl;
	int idx=0;
	for(int i=N; i>=0; --i)
	{
		//cout<<"filename["<<i<<"]="<<filename[i]<<endl;
		if(filename[i]=='/')
		{
			idx=i;
			break;
		}
	}
	filename.Remove(idx, 	N);
	cout<<filename<<endl;
	return filename;
}

void MakeDir(name filename)
{
	tag op=getpath(filename);
	gSystem->Exec("mkdir -p "+op);
}

name getfilename_nucleon(tag vtag, tag adtag)
{
	return data_path+"nucleon/"+Form("nucleon_%s%s.root", vtag.Data(), adtag.Data());
}

name getfilename_deuteron(tag vtag, tag adtag)
{
	return data_path+"deuteron/"+Form("deuteron_%s%s.root", vtag.Data(), adtag.Data());
}

name getfilename_triton(tag vtag, tag adtag)
{
	return data_path+"triton/"+Form("triton_%s%s.root", vtag.Data(), adtag.Data());
}
#endif
