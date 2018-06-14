/******************************************
 * Adam Bajguz
 ******************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define BASES_NUM 21600 // Size of array that stores number of bases for each position
#define RANGE (90 * 60)

int main() {
    clock_t exec_begin = clock();

    unsigned long long int operations_counter = 0;
    unsigned int *bases, bases_count;

    //##################################################
    //              FILE READING - START
    //==================================================
    FILE *in = fopen("in.txt", "rt");
    if (in) {
        fscanf(in, "%u", &bases_count);
        bases = (unsigned int *) malloc( sizeof(*bases) * bases_count );

        unsigned int tmp_degree, tmp_minutes, pos = 0;
        while (!feof(in)) {
            ++operations_counter;
            if (fscanf(in, "%d %d", &tmp_degree, &tmp_minutes) == 2) {
                bases[pos] = (tmp_degree * 60) + tmp_minutes;
                ++pos;
            }
        }

        fclose(in);
    } else {
        printf("Error opening 'in.txt'");
        return 1;
    }
    clock_t exec_begin_no_data_load = clock();
    //==================================================
    //              FILE READING - END
    //##################################################

    unsigned long long int operations_counter_no_load = 0;

    //##################################################
    //                ALGORITHM - START
    //==================================================
    //Finding max number of bases
    unsigned int max_bases_num = 0;

    for (unsigned int i = 0; i < bases_count; ++i) {
        unsigned int curr_num = 0;
        for (unsigned int j = 0; j < bases_count; ++j) {
            ++operations_counter_no_load;

            if (bases[i] + (90 * 60) >= BASES_NUM) {
                if (bases[j] >= bases[i] && bases[j] <= bases[i] + RANGE)
                    ++curr_num;

                if (bases[j] >= 0 && bases[j] <= (bases[i] + RANGE) % BASES_NUM) // for 330-60 case
                    ++curr_num;
            } else {
                if (bases[j] >= bases[i] && bases[j] <= bases[i] + RANGE)
                    ++curr_num;
            }
        }

        if (curr_num > max_bases_num)
            max_bases_num = curr_num;
    }
    //==================================================
    //                ALGORITHM - END
    //##################################################


    //##################################################
    //              FILE WRITING - START
    //==================================================
    FILE *out = fopen("out.txt", "wt");
    if (out) {
        fprintf(out, "%d", max_bases_num);
        fclose(out);
    } else {
        printf("Error writing to 'out.txt'");
        return 1;
    }
    //==================================================
    //              FILE WRITING - END
    //##################################################

    clock_t exec_end = clock();
    double exec_time = ((double) (exec_end - exec_begin)) / CLOCKS_PER_SEC;
    double exec_time_no_load = ((double) (exec_end - exec_begin_no_data_load)) / CLOCKS_PER_SEC;

    operations_counter += operations_counter_no_load;

    printf("%d military bases can be destroyed.\n", max_bases_num);
    printf("Execution time: %f seconds.\n", exec_time);
    printf("Execution time without data loading: %f seconds.\n", exec_time_no_load);
    printf("Number of performed operations: %u.\n", operations_counter);
    printf("Number of performed operations without data loading: %u.\n", operations_counter_no_load);

    free(bases);
    return 0;
}
