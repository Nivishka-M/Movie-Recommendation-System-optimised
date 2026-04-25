//creates utility matrix
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void get_movie_names(char *movienames, char *s){
	char tmp[1024];
	int i=0;
	FILE *fstream = fopen(s,"r");
	while(fgets(tmp,sizeof(tmp),fstream)){
		char *p = tmp;
		// Skiping first column (movie_id)
		strtol(p, &p, 10);
		if (*p == ',') p++;
		
		// second column is the movie name. Copying up to the next comma or newline.
		char *end = p;
		while(*end != ',' && *end != '\n' && *end != '\r' && *end != '\0') end++;
		int len = end - p;
		if (len > 1023) len = 1023; // prevent overflow
		strncpy(&movienames[i*1024], p, len);
		movienames[i*1024 + len] = '\0';
		
		i++;
	}
	fclose(fstream);
}

void get_movie_genres(char *moviegenres, char *s){
	char tmp[1024];
	int i=0;
	FILE *fstream = fopen(s,"r");
	while(fgets(tmp,sizeof(tmp),fstream)){
		char *p = tmp;
		// Skip first column (movieId)
		strtol(p, &p, 10);
		if (*p == ',') p++;
		
		// Second column is genre
		char *end = p;
		while(*end != ',' && *end != '\n' && *end != '\r' && *end != '\0') end++;
		int len = end - p;
		if (len > 1023) len = 1023;
		strncpy(&moviegenres[i*1024], p, len);
		moviegenres[i*1024 + len] = '\0';
		
		i++;
	}
	fclose(fstream);
}

void get_utility_matrix(double *utility_matrix, char *s, int No_of_movies, int No_of_users, int uid){
	char tmp[1024];
	FILE *fstream = fopen(s,"r");
	// in format: userId,movieId,rating,timestamp
	while(fgets(tmp,sizeof(tmp),fstream)){
		char *p = tmp;
		int i = strtol(p, &p, 10) - 1;
		if (*p == ',') p++;
		int j = strtol(p, &p, 10) - 1;
		if (*p == ',') p++;
		double val = strtod(p, &p);
		
		if (i >= 0 && i < No_of_users && j >= 0 && j < No_of_movies) {
			utility_matrix[i*No_of_movies + j] = val;
		}
	}
	fclose(fstream);
}

void new_user_movies(double *newuser, char *s, int uid){
	char tmp[1024];
	FILE *fstream = fopen(s,"r");
	while(fgets(tmp,sizeof(tmp),fstream)){
		char *p = tmp;
		int i = strtol(p, &p, 10) - 1;
		if (*p == ',') p++;
		int j = strtol(p, &p, 10) - 1;
		if (*p == ',') p++;
		double val = strtod(p, &p);
		
		if (i + 1 == uid) {
			newuser[j] = val;
		}
	}
	fclose(fstream);
}
