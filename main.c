#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define L 100000
#define max(x, y) ((x) > (y) ? (x) : (y))

void setNumZero(int *a) {
    for (long i = 1; i <= L; i++)
        *(a + i) = 0;
}

void setNum(int *a, long x) {
    setNumZero(a);
    long i = 1;
    while (x > 0) {
        *(a + i) = x % 10;
        x /= 10;
        i++;
    }
}

long lengthNum(int *a) {
    for (long i = L; i > 0; i--)
        if (*(a + i) != 0)
            return i;
    return 1;
}

void addNum(int *a, int *b, int *x) {
    long i = 1;
    long c = 0;
    setNumZero(x);
    long m = max(lengthNum(a), lengthNum(b));
    while (i <= m + 1) {
        c += *(a + i) + *(b + i);
        *(x + i) = c % 10;
        c /= 10;
        i++;
    }
}

void dedByte(int *a, int i) {
    if (*(a + i) - 1 < 0) {
        *(a + i) = 10 + *(a + i) - 1;
        dedByte(a, i + 1);
    }
    else *(a + i) -= 1;
}

void dedNum(int *a, int *b, int *x) {
    long c = 0;
    long m = max(lengthNum(a), lengthNum(b));
    for (long i = 1; i <= m; i++) {
        if ((*(a + i) - *(b + i) + c) < 0) {
            c = 10;
            dedByte(a, i + 1);
        }
        *(x + i) = c + *(a + i) - *(b + i);
        c = 0;
    }
}

void copy(int *a, int *b) {
    for (long i = 1; i <= L; i++)
        *(b + i) = *(a + i);
}

void printNum(int *a) {
    for (long i = lengthNum(a); i > 0; i--)
        printf("%d", *(a + i));
    putchar('\n');
    putchar('\n');
}

int main(int argc, char *argv[]) {
    int *a, *b, *c, *two; // initialization of long numbers
    a = (int *)malloc(sizeof(int) * L);
    b = (int *)malloc(sizeof(int) * L);
    c = (int *)malloc(sizeof(int) * L);
    two = (int *)malloc(sizeof(int) * L);

    FILE *f;
    f = fopen("a000043", "r");

    int N;
    printf("input N: ");
    scanf("%d", &N);

    for (int x = 1; x <= N; x++) {
   
        setNum(a, 0);
        setNum(b, 0);
        setNum(two, 2);

        long p;
        fscanf(f, "%ld ", &p);
        long k = 1;

        while (k < 2 * p - 1) {
            setNumZero(a);
            for (int i = 1; i <= 2; i++) {
                addNum(a, two, c);
                copy(c, a);
            }
            copy(a, two);
            k++;
        }
        copy(two, a);

        setNum(two, 2);
        k = 1;
        while (k < p - 1) {
            setNumZero(b);
            for (int i = 1; i<= 2; i++) {
                addNum(b, two, c);
                copy(c, b);
            }
            copy(b, two);
            k++;
        }
        copy(two, b);

        dedNum(a, b, c);
        printNum(c);
    }
    fclose(f);
    return 0;
}
