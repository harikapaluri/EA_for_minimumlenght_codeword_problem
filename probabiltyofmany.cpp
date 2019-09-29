#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include "MersenneTwister.h"
using namespace std;
MTRand mtrand1;
int ** add(int **G,int i, int j,int k)
{// same as rows in B
  for(int p=0; p<k; p++)
  {
    G[i][p] = G[i][p] ^ G[p][j];

  }
  return G;
}
int costofsol(int **G,int n,int k)
{
int b[k];
for(int i=0;i<k;i++){b[i]=0;}
for( int i=0;i<k;i++)
    for( int j=0;j<n;j++)
	{
		if(G[i][j]==1)
			b[i]=b[i]+1;

	}
	int cost=n+1;
  for( int i=0;i<k;i++)
    {
	if(b[i]<cost)
	{cost=b[i];
	}
    }


return cost;
}

int main() {
  int i,j;
  int r1,r2;
  const int n=511;
  const int k=58;
  char fn[]="bch511_58_183.txt";
  int **G;//G is the generator matrix
  int **G1;//the transformed matrix
  G = new int *[k];
  for(i=0; i<k; i++)
    G[i]= new int[n];
  ifstream file;
  file.open(fn);
  for(i=0; i<k; i++)
    for(j=0; j<n; j++){
      file>>G[i][j];
    }
  file.close();
  int step,m;
  int r;
  step=1;
  m=0.2;
   while ((costofsol(G,n,k)>m)&&step<=1000)
  {
  for(i=0;i<k;i++)
     {
         r=mtrand1.randInt(k-1);
           if(r==i){
            r1=mtrand1.randInt(k-1);
            r2=mtrand1.randInt(n-1);
            if(r1==r2)
            {
              r1=mtrand1.randInt(k-1);
            r2=mtrand1.randInt(n-1);
            }
            G1=add(G,r1,r2,k);
            if( (costofsol(G1,n,k)) > (costofsol(G,n,k)) )
       G=G1;
         }
     }
    step=step+1;
  }



 return 0;

}

