#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct l {
    struct l* next;
};

typedef struct l l;

const size_t INITIAL_NUMBER_OF_ELEM = 800 / sizeof(l);
const size_t MAX_NUMBER_OF_ELEM = 15*1024*1024 / sizeof(l);
const double SIZE_STEP = 1.2;
const size_t NUMBER_OF_CICLES = 100;

void calculate_time(l* array, size_t count, FILE* file);
void prepare_list(l* list, size_t elements);

int main() {
    FILE* result = fopen("results", "w");
    for(size_t elements = INITIAL_NUMBER_OF_ELEM; elements <= MAX_NUMBER_OF_ELEM; elements *= SIZE_STEP) {
        l *list = (l*)calloc(elements, sizeof(l *));
        prepare_list(list, elements);
        calculate_time(list, elements, result);
        free(list);
    }
    return 0;
}

void calculate_time(l* array, size_t elements, FILE* file) {
    l temp;
    clock_t start = clock();
    for(int i = 0; i < NUMBER_OF_CICLES; i++) {
        for(int j = 0; j < elements; j++) {
            temp = array[j];
        }
    }
    clock_t end = clock();
    double seq_time = ((double) (end - start) * 1000000000) / (NUMBER_OF_CICLES * elements * CLOCKS_PER_SEC);

    l* iterator = array;
    clock_t start_rand = clock();
    for(int i = 0; i < NUMBER_OF_CICLES; i++) {
        for(int j = 0; j < elements; j++) {
            iterator = iterator->next;
        }
    }
    clock_t end_rand = clock();
    double rand_time = ((double) (end_rand - start_rand) * 1000000000) / (NUMBER_OF_CICLES * elements * CLOCKS_PER_SEC);
    fprintf(file, "%lu    %f    %f\n", elements * sizeof(l *), seq_time, rand_time);
    fflush(file);
    printf("%lu    %f    %f\n", elements * sizeof(l *), seq_time, rand_time);
}

void prepare_list(l* list, size_t elements) {
    for(int i = 0; i < elements; i++) list[i].next = NULL;
    size_t prev_index = 0;
    for (size_t i = 0; i < elements - 1; ++i) {
        size_t current_index = rand() % elements;
        while (list[current_index].next) {
            current_index = (current_index + 1) % elements;
        }
        list[prev_index].next = list + current_index;
        prev_index = current_index;
    }
    list[prev_index].next = list;
}
