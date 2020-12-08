#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 3
#define NN 3

int main(){
  double K[N][N] = {{23,42,3},{42,21,1},{3,1,19}};
  double b[N];
  double rowh[N];
  double bmag = 0;
  for(int i=0;i<N;i++){
    b[i] = 1; //+ rand();
    bmag = bmag + b[i]*b[i];
  }
  bmag = sqrt(bmag);
  for(int i=0;i<N;i++){
    b[i] = b[i]/bmag;
  }
  double q[NN][N];
  for(int i=0;i<N;i++){
    q[0][i] = b[i];
  }
  double v[N];
  for(int i=0;i<N;i++){
    v[i]=0;
    rowh[i]=0;
  }
  double h[N][NN];
  for(int i=0;i<N;i++){
    for(int j=0;j<NN;j++){
      h[i][j] = 0;
    }
  }

//we want to solve the system Kv = q[n] for v
//use Gaussian row reduction on the augmented matrix A = [K q]
  for(int n=0;n<NN-1;n++){
    double A[N][N+1];
    for(int i=0;i<N;i++){
      for(int j=0;j<N;j++) A[i][j] = K[i][j];
      A[i][N] = q[n][i];
    }
    int hh = 0;
    int kk = 0;
    while(hh < N && kk <= N+1){
      int i_max = hh;
      for(int i=hh;i<N;i++){
        if(abs(A[i][kk]>=A[i_max][kk])){
          i_max = i;
        }
      }

      if(A[i_max][kk]==0){
        kk = kk + 1;
      }
      else{

        //printf("%d %f \n",n,h[0][0]);
        printf("%d %p \n",n,*h);
        printf("%d %p \n",n,*A);

        for(int j=0;j<N+1;j++){
          rowh[j] = A[hh][j];
          A[hh][j] = A[i_max][j];
        }
        for(int j=0;j<N+1;j++){
          A[i_max][j] = rowh[j];
        }
        double f = 0;
        for(int i = hh + 1;i < N;i++){
          f = A[i][kk]/A[hh][kk];
          A[i][kk] = 0;
          for(int j=kk + 1;j<N+1;j++){
            A[i][j] = A[i][j] - A[hh][j] * f;
          }
        }
        hh = hh + 1;
        kk = kk + 1;
      }
    }

      /*for(int i=0;i<N;i++){
        v[i] = 0;
        for(int j=0;j<N;j++){
          v[i] = v[i] + K[i][j]*q[n][j];
        }
      }*/

    //back substitute to get v = K^{-1}q[n]
    for(int i=0;i<N;i++){
      double ssum = 0;
      int ii = N-1-i;
      for(int j=ii+1;j<N;j++){
        ssum = ssum + A[ii][j]*v[j];
      }
      v[ii] = (A[ii][N] - ssum)/A[ii][ii];
    }
    //now v is the solution for q[n] = K v
    for(int i=0;i<N;i++){
    }
    for(int j=0;j<n;j++){
      for(int k=0;k<N;k++){
        h[j][n] = h[j][n] + q[j][k]*v[k];

      }
      //printf("%f \n",h[j][n]);


    for(int k=0;k<N;k++){
      v[k] = v[k] - h[j][n]*q[j][k];
      //printf("%f  \n",v[k]);

    }
    }
    for(int i = 0;i<N;i++){
      h[n+1][n] = h[n+1][n] + v[i]*v[i];
    }

    h[n+1][n] = sqrt(h[n+1][n]);
  //  printf("%f  \n",h[n+1][n]);
    for(int i = 0;i<N;i++){
      q[n+1][i] = v[i]/h[n+1][n];
    }
  }
  for(int i = 0;i<N;i++){
    for(int j = 0;j<NN;j++){
      printf("%f ",h[i][j]);
    }
    printf("\n");
  }
  // now h[i][j] is a tridiagonal
  // matrix whose largest eigenvalues are the reciprocals of
  // the smallest eigenvalues of K

  return 0;
}
