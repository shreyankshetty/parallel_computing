#include <iostream>
#include <stdlib.h>
#include <vector> 
#include <ctime>
#include <thread>
#define fl static_cast<float>
using namespace std;
void print(float**,int);
void del(float**,int);
float ** init(int sz);
void read(float**ans,int sz);
float** generate(const int n);
void print(float** arr,int n)
{

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			cout<<arr[i][j]<<" ";
		cout<<endl;
	}

	cout<<endl;
}
void del(float** arr,int n)
{
	for(int i=0;i<n;i++)
		delete []arr[i];
	delete []arr;
}
float ** init(int sz)
{
	float **ans=new float*[sz];
	for(int i=0;i<sz;i++)
		ans[i]=new float[sz];
	return ans;
}
void read(float**ans,int sz)
{
	//float ans=init(sz);
	for (int i = 0; i < sz; ++i)
	{
		for (int j = 0; j < sz; ++j)
		{
			cin>>ans[i][j];
			/* code */
		}
		/* code */
	}
}
float** generate(const int n)
{
	float** arr=init(n);
	//srand(time(NULL));
	
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			arr[i][j]=fl((fl(rand())/fl(RAND_MAX))*10);
		}
	}	
	return arr;
}
void Strassen(float** A,float** B,int sz,float **ans)
{
	
    if(sz==1)
	{
		
		ans[0][0]=A[0][0]*B[0][0];
		return;
		//return ans;
	}
	float ***p=new float**[7];
	for(int i=0;i<7;i++)
	{
		p[i]=new float*[sz/2];
		for(int j=0;j<sz/2;j++)
			p[i][j]=new float[sz/2];
	}
	
	
	float ***ALL=new float**[14];
	for(int i=0;i<14;i++)
	{
		ALL[i]=new float*[(sz/2)];
		for(int j=0;j<(sz/2);j++)
			ALL[i][j]=new float[(sz/2)];
	}


	
	//All assigns
	for(int i=0;i<(sz/2);i++)
	{
		for(int j=0;j<(sz/2);j++)
		{
			ALL[0][i][j]=A[i][j];
		}
	}
	
	for(int i=0;i<(sz/2);i++)
	{
		for(int j=0;j<(sz/2);j++)
		{
			ALL[1][i][j]=B[i][j+(sz/2)]-B[i+(sz/2)][j+(sz/2)];
		}
	}
	for(int i=0;i<(sz/2);i++)
	{
		for(int j=0;j<(sz/2);j++)
		{
			ALL[2][i][j]=A[i][j]+A[i][j+(sz/2)];
		}
	}
	for(int i=0;i<(sz/2);i++)
	{
		for(int j=0;j<(sz/2);j++)
		{
			ALL[3][i][j]=B[i+(sz/2)][j+(sz/2)];
		}
	}

	for(int i=0;i<(sz/2);i++)
	{
		for(int j=0;j<(sz/2);j++)
		{
			ALL[4][i][j]=A[i+(sz/2)][j]+A[i+(sz/2)][j+(sz/2)];
		}
	}
	for(int i=0;i<(sz/2);i++)
	{
		for(int j=0;j<(sz/2);j++)
		{
			ALL[5][i][j]=B[i][j];
		}
	}
	for(int i=0;i<(sz/2);i++)
	{
		for(int j=0;j<(sz/2);j++)
		{
			ALL[6][i][j]=A[i+(sz/2)][j+(sz/2)];
		}
	}
	for(int i=0;i<(sz/2);i++)
	{
		for(int j=0;j<(sz/2);j++)
		{
			ALL[7][i][j]=B[i+(sz/2)][j]-B[i][j];
		}
	}
	for(int i=0;i<(sz/2);i++)
	{
		for(int j=0;j<(sz/2);j++)
		{
			ALL[8][i][j]=A[i][j]+A[i+(sz/2)][j+(sz/2)];
		}
	}
	for(int i=0;i<(sz/2);i++)
	{
		for(int j=0;j<(sz/2);j++)
		{
			ALL[9][i][j]=B[i][j]+B[i+(sz/2)][j+(sz/2)];
		}
	}
	for(int i=0;i<(sz/2);i++)
	{
		for(int j=0;j<(sz/2);j++)
		{
			ALL[10][i][j]=A[i][j+(sz/2)]-A[i+(sz/2)][j+(sz/2)];
		}
	}
	for(int i=0;i<(sz/2);i++)
	{
		for(int j=0;j<(sz/2);j++)
		{
			ALL[11][i][j]=B[i+(sz/2)][j]+B[i+(sz/2)][j+(sz/2)];
		}
	}
	for(int i=0;i<(sz/2);i++)
	{
		for(int j=0;j<(sz/2);j++)
		{
			ALL[12][i][j]=A[i][j]-A[i+(sz/2)][j];
		}
	}
	for(int i=0;i<(sz/2);i++)
	{
		for(int j=0;j<(sz/2);j++)
		{
			ALL[13][i][j]=B[i][j]+B[i][j+(sz/2)];
		}
	}
	if(sz>512)
	{	
		vector<thread> pid;
		//float **p1=
		pid.push_back(thread(Strassen,ALL[0],ALL[1],(sz/2),p[0]));
		//float **p2=
		pid.push_back(thread(Strassen,ALL[2],ALL[3],(sz/2),p[1]));
		//float **p3=
		pid.push_back(thread(Strassen,ALL[4],ALL[5],(sz/2),p[2]));
		//float **p4=
		pid.push_back(thread(Strassen,ALL[6],ALL[7],(sz/2),p[3]));
		//float **p5=
		pid.push_back(thread(Strassen,ALL[8],ALL[9],(sz/2),p[4]));
		//float **p6=
		pid.push_back(thread(Strassen,ALL[10],ALL[11],(sz/2),p[5]));
		//float **p7=
		pid.push_back(thread(Strassen,ALL[12],ALL[13],(sz/2),p[6]));

		for(auto& td:pid)
		{
			td.join();
		}

	}
	else
	{
		Strassen(ALL[0],ALL[1],(sz/2),p[0]);
		//float **p2=
		Strassen(ALL[2],ALL[3],(sz/2),p[1]);
		//float **p3=
		Strassen(ALL[4],ALL[5],(sz/2),p[2]);
		//float **p4=
		Strassen(ALL[6],ALL[7],(sz/2),p[3]);
		//float **p5=
		Strassen(ALL[8],ALL[9],(sz/2),p[4]);
		//float **p6=
		Strassen(ALL[10],ALL[11],(sz/2),p[5]);
		//float **p7=
		Strassen(ALL[12],ALL[13],(sz/2),p[6]);

	}



	for(int i=0;i<(sz/2);i++)
	{
		for(int j=0;j<(sz/2);j++)
		{
			ans[i][j]=p[4][i][j]+p[3][i][j]-p[1][i][j]+p[5][i][j];
			ans[i][j+(sz/2)]=p[0][i][j]+p[1][i][j];
			ans[i+(sz/2)][j]=p[2][i][j]+p[3][i][j];
			ans[i+(sz/2)][j+(sz/2)]=p[0][i][j]+p[4][i][j]-p[2][i][j]-p[6][i][j];
		}	

	}




	for (int i = 0; i < 14; ++i)
	{
		del(ALL[i],(sz/2));
		/* code */
	}
	delete []ALL;
	for(int i=0;i<7;i++)
	{
		del(p[i],(sz/2));
	}
	delete []p;
	
}


int main()
{
	
	//seed the randomizer
	srand(time(NULL));
	int sz;
	cin>>sz;
	clock_t stt,end;
	float** m1=NULL;
	float** m2=NULL;
	float** ans1=NULL;
	//m1=init(sz);
	//m2=init(sz);
    m1=generate(sz);
    m2=generate(sz);
	ans1=init(sz);	
	stt=clock();
	Strassen(m1,m2,sz,ans1);
	print(ans1,sz);
	
	
	
	end=clock();
	cout<<"For size "<<sz<<":  "<<(end-stt)/double(CLOCKS_PER_SEC)<<" seconds"<< endl;


	del(m1,sz);
	del(m2,sz);
	del(ans1,sz);
	return 0;
	
}