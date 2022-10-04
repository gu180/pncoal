void Integral1()//Integral of y=x^2 from 0 to 1
{
	gRandom->SetSeed(0);
	double sum_y=0;
	int N_total=1000000;
	for(int i=0; i<N_total; ++i)
	{
		double x=gRandom->Uniform(0, 1);
		double y=x*x;
		sum_y+=y;
	}

	double average_y=sum_y/double(N_total);
	double integral=average_y*(1-0);
	cout<<"The integral is: "<<integral<<". The analytical answer is 1/3."<<endl;
}

void Integral2()//
{
	gRandom->SetSeed(0);
	int  N_inside=0;
	int N_total=1000000;
	for(int i=0; i<N_total; ++i)
	{
		double x=gRandom->Uniform(-1, 1);
		double y=gRandom->Uniform(-1, 1);
		if((x*x+y*y)<=1.0)
		{
			N_inside++;
		}
	}

	double Area=double(N_inside)/double(N_total)*(2*2);
	cout<<"The area of the circle with radius=1 is: "<<Area<<" The analytical answer is pi."<<endl;

}





void  test1()
{
	Integral1();
	Integral2();
}
