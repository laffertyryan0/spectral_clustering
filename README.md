# Spectral Clustering

The purpose of this repository is to implement a spectral clustering algorithm in C, completely from scratch, without any outside libraries. 
I am doing this for two reasons. 
One is to refresh myself in C, which I haven't used for quite a while.
Second is to develop my understanding of spectral clustering to prepare for a presentation in Stat 618. 
I am using (inversed) Lancsoz Iteration to compute the second smallest eigenvalue of the discrete Laplacian of a similarity graph. 
Then solve the system to obtain the second smallest eigenvector. The components can be divided into positive and negative parts, which 
will give the indices for data points in two clusters. 
