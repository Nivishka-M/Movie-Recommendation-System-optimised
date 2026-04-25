#include <stdlib.h>

typedef struct {
    int movie_id;
    double rating;
} MovieRating;

int compare_movie_ratings(const void *a, const void *b) {
    MovieRating *m1 = (MovieRating *)a;
    MovieRating *m2 = (MovieRating *)b;
    // Sort descending
    if (m1->rating < m2->rating) return 1;
    if (m1->rating > m2->rating) return -1;
    return 0;
}

void sort(int *recommended_movies, double *predicted_ratings, int no_of_recommended_movies){
    if (no_of_recommended_movies <= 1) return;

    MovieRating *arr = (MovieRating *)malloc(sizeof(MovieRating) * no_of_recommended_movies);
    for (int i = 0; i < no_of_recommended_movies; i++) {
        arr[i].movie_id = recommended_movies[i];
        arr[i].rating = predicted_ratings[i];
    }

    qsort(arr, no_of_recommended_movies, sizeof(MovieRating), compare_movie_ratings);

    for (int i = 0; i < no_of_recommended_movies; i++) {
        recommended_movies[i] = arr[i].movie_id;
        predicted_ratings[i] = arr[i].rating;
    }

    free(arr);
}
