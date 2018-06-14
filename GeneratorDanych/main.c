#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int s, m;
    FILE *f = fopen("in1m.txt", "wt");
    fprintf(f, "1000000 \n");
    srand(time(NULL));
    for (unsigned int i = 0; i < 1000000; i++) {

        s = rand() % 360;
        m = rand() % 60;
        fprintf(f, "%d %d\n", s, m);
    }
    fclose(f);
    return 0;
}
