//Centered cosine similarity
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double pearson_correlation(double *A, double *B, unsigned int size){
    double dot_p=0.0;
    double mag_a=0.0;
    double mag_b=0.0;
    int i;
    //Vectorizing the inner loop
    #pragma omp simd reduction(+:dot_p,mag_a,mag_b)
    for(i=0; i<size; i++){
        dot_p += A[i]*B[i];
        mag_a += A[i]*A[i];
        mag_b += B[i]*B[i];
    }
    
    // To prevent division by zero
    if (mag_a == 0.0 || mag_b == 0.0) return 0.0;
    
    return dot_p/(sqrt(mag_a)*sqrt(mag_b));
}

void calc_similarity(double *normalizeduser, double *normalized_matrix, double *similarity, int No_of_users, int No_of_movies){
	int i=0;
	#pragma omp parallel for schedule(dynamic)
	for(i=0;i<No_of_users;i++){ //traverse through each user
		//find similarity between new user and ith user directly using memory pointers
		similarity[i] = pearson_correlation(normalizeduser, &normalized_matrix[i*No_of_movies], No_of_movies);
	}
}
