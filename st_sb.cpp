#include <iostream>
#include <stdlib.h>
#include <vector> 
#include <ctime>
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
float** Strassen(float** A,float** B,int sz)
{
	float **ans=new float*[sz];
	for(int i=0;i<sz;i++)
		ans[i]=new float[sz];
	
	if(sz==1)
	{
		
		ans[0][0]=A[0][0]*B[0][0];
		return ans;
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
	
	float **p1=Strassen(ALL[0],ALL[1],(sz/2));
	float **p2=Strassen(ALL[2],ALL[3],(sz/2));
	float **p3=Strassen(ALL[4],ALL[5],(sz/2));
	float **p4=Strassen(ALL[6],ALL[7],(sz/2));
	float **p5=Strassen(ALL[8],ALL[9],(sz/2));
	float **p6=Strassen(ALL[10],ALL[11],(sz/2));
	float **p7=Strassen(ALL[12],ALL[13],(sz/2));

	for(int i=0;i<(sz/2);i++)
	{
		for(int j=0;j<(sz/2);j++)
		{
			ans[i][j]=p5[i][j]+p4[i][j]-p2[i][j]+p6[i][j];
			ans[i][j+(sz/2)]=p1[i][j]+p2[i][j];
			ans[i+(sz/2)][j]=p3[i][j]+p4[i][j];
			ans[i+(sz/2)][j+(sz/2)]=p1[i][j]+p5[i][j]-p3[i][j]-p7[i][j];
		}	

	}




	for (int i = 0; i < 14; ++i)
	{
		del(ALL[i],(sz/2));
		/* code */
	}
	delete []ALL;
	del(p1,(sz/2));
	del(p2,(sz/2));
	del(p3,(sz/2));
	del(p4,(sz/2));
	del(p5,(sz/2));
	del(p6,(sz/2));
	del(p7,(sz/2));

	return ans;

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
	
	stt=clock();
	ans1=Strassen(m1,m2,sz);
	print(ans1,sz);
	
	
	
	end=clock();
	cout<<"For size "<<sz<<":  "<<(end-stt)/double(CLOCKS_PER_SEC)<<" seconds"<< endl;


	del(m1,sz);
	del(m2,sz);
	del(ans1,sz);
	sz=sz*2;
		

	return 0;
	
}