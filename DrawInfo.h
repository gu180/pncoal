


void Draw_tp(tag op)
{
	tag on1=op+"tp_ratio_Nn.pdf";
	DrawTp(tp_ratio_Nn, "ratio", "<Nn>", on1, vals{0,0.1});
	tag on_n=op+"tp_Nn_ratio.pdf";
	DrawTp(tp_Nn_ratio, "Nn", "<ratio>", on_n);

	tag on_p=op+"tp_Np_ratio.pdf";
	DrawTp(tp_Np_ratio, "Np", "<ratio>", on_p);
	
}

void tritondraw()
{
	TFile* input=TFile::Open(dataname);
	LoadH(input);
	tag op=plot_path+outtag+"/";
	MakeDir(op);
	DrawH(op);
	
	delete input;
	
}

void DrawInfo()
{
}
