/******************************************
 * Adam Bajguz
 ******************************************/

#include <stdio.h>
#include <time.h>

#define BASES_NUM 21600 // Size of array that stores number of bases for each position
#define FRAME_LENGTH (90 * 60)

int main() {
    clock_t exec_begin = clock();

    unsigned int operations_counter = 0, bases_count, maximum = 0, frame_start_index = BASES_NUM;

    unsigned int bases[BASES_NUM] = {0};

    //##################################################
    //              FILE READING - START
    //==================================================
    FILE *in = fopen("in.txt", "rt");
    if (in) {
        fscanf(in, "%u", &bases_count);

        unsigned int tmp_degree, tmp_minutes;
        while (!feof(in)) {
            ++operations_counter;

            if (fscanf(in, "%d %d", &tmp_degree, &tmp_minutes) == 2) {
                tmp_minutes += tmp_degree * 60;
                ++bases[tmp_minutes];

                if (tmp_minutes < frame_start_index)
                    frame_start_index = tmp_minutes;
                if (tmp_minutes > maximum)
                    maximum = tmp_minutes;
            }
        }

        fclose(in);
    } else {
        printf("Error opening in.txt");
        return 1;
    }
    clock_t exec_begin_no_data_load = clock();
    //==================================================
    //              FILE READING - END
    //##################################################

    unsigned int operations_counter_no_load = 0;

    unsigned int max_sum = 1;
    if (bases_count > 1) {
        //##################################################
        //                ALGORITHM - START
        //==================================================
        unsigned int frame_end_index = frame_start_index + FRAME_LENGTH;

        unsigned int frame_sum = 0;
        for (int i = frame_start_index; i <= frame_end_index; ++i) {
            ++operations_counter_no_load;
            frame_sum += bases[i];
        }

        max_sum = frame_sum;

        while (frame_start_index < maximum - 1) {
            frame_sum -= bases[frame_start_index];

            do {
                ++operations_counter_no_load;

                ++frame_start_index;
                frame_end_index = (frame_end_index + 1) % BASES_NUM;
                frame_sum += bases[frame_end_index];
            } while (!bases[frame_start_index]); //moving frame and then skipping zeros if necessary

            if (frame_sum > max_sum)
                max_sum = frame_sum;
        }

        //==================================================
        //                ALGORITHM - END
        //##################################################

        //##################################################
        //              FILE WRITING - START
        //==================================================
        FILE *out = fopen("out.txt", "wt");
        if (out) {
            fprintf(out, "%d", max_sum);
            fclose(out);
        } else {
            printf("Error writing to out.txt");
            return 1;
        }
        //==================================================
        //              FILE WRITING - END
        //##################################################
    }
    clock_t exec_end = clock();
    double exec_time = ((double) (exec_end - exec_begin)) / CLOCKS_PER_SEC;
    double exec_time_no_load = ((double) (exec_end - exec_begin_no_data_load)) / CLOCKS_PER_SEC;

    operations_counter += operations_counter_no_load;

    printf("%d military bases can be destroyed.\n", max_sum);
    printf("Execution time: %f seconds.\n", exec_time);
    printf("Execution time without data loading: %f seconds.\n", exec_time_no_load);
    printf("Number of performed operations: %u.\n", operations_counter);
    printf("Number of performed operations without data loading: %u.\n", operations_counter_no_load);

    return 0;
}
