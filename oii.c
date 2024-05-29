#include <stdio.h>

int main()
{
    int x[7] = {10, 75, 50, 12, 15, 55, 25};
    int *ptr = x; // pointer menunjuk ke alamat awal array

    // x[5] = 100; // mengubah nilai x[5] menjadi 100
    // Output: 100
    printf("Nilai : %d\n", *(ptr + 2)); // Output: 100

    return 0;
}