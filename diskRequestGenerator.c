#include <stdlib.h>
#include <stdio.h>

int main()
{
    FILE *fp = fopen("s_requests.txt", "w");

    int time = 0;
    
    for (int i = 0; i < 10; i++)
    {
        time += rand() % 11;
        fprintf(fp, "%d %d %d\n", time, rand() % (1 << 20), rand() % 100);
    } //time, process address (random), process ID

    fclose(fp);
}