/**
 * Menu based circular convolution in C89
 */

#include <stdio.h>
/* #include <conio.h> */

#define MAX 20
#define MOD(X, N) ((X < 0) ? X + N : X)

/**
 * @brief  Circular Convloution of two periodic sequences
 * @param  signal[]: The input signal x[n]
 * @param  kernel[]: The response signal h[n]
 * @param  ip_size: Input size of either signal (since equal)
 * @param  result[]: Output of the system y[n]
 * @retval None
 */
void convolve(const double signal[/* MAX */], const double kernel[/* MAX */],
              int ip_size, double result[/* MAX */]) {
    int n = 0;
    int i = 0;

    for (n = 0; n < ip_size; n++) {
        result[n] = 0;
        for (i = 0; i < ip_size; i++) {
            result[n] += kernel[i] * signal[MOD(n - i, ip_size)];
        }
    }
}

void pad_zeros(double signal[], unsigned int orig_size, unsigned int padding) {
    unsigned int i = 0;
    for (i = orig_size; i < orig_size + padding; i++) {
        signal[i] = 0;
    }
}
/**
 * @brief  Print a sequence
 * @param  name: Name of the sequence
 * @param  signal[]: The sequence is saved in this array
 * @param  signal_ip_size: Length of sequence
 * @retval None
 */
void print_signal(const char* name, double signal[/* signal_len */],
                  unsigned int signal_ip_size) {
    unsigned int i;

    printf("Sequence %s[n]:\n", name);
    for (i = 0; i < signal_ip_size; i++) {
        printf("%s[%u] = %f\n", name, i, signal[i]);
    }
    printf("\n");
}

/**
 * @brief  Get a sequence
 * @param  name: Name of the sequence
 * @param  signal[]: The array where the sequence should be stored
 * @param  signal_ip_size: The assumed length of sequence
 * @retval signal_ip_size if it is smaller than MAX, else 0
 */
int get_signal(const char* name, double signal[/* signal length */],
               unsigned int signal_ip_size) {
    unsigned int i;

    printf("Enter the size of the sequence: ");
    scanf("%u", &signal_ip_size);
    if (signal_ip_size > MAX) {
        printf("Can't handle size greater than: %d!", MAX);
        return 0;
    }
    printf("Enter sequence: %s\n", name);
    for (i = 0; i < signal_ip_size; i++) {
        scanf("%lf", &signal[i]);
    }
    printf("Entered sequence is: \n");
    print_signal(name, signal, signal_ip_size);
    return signal_ip_size;
}

int main(void) {
    double signal[MAX], kernel[MAX], result[MAX];
    unsigned int signal_ip_size = 0;
    unsigned int kernel_ip_size = 0;
    unsigned int ip_size = 0;
    /* clrscr(); */

    signal_ip_size = get_signal("x", signal, signal_ip_size);
    if (signal_ip_size == 0) {
        /* Caught error */
        return signal_ip_size;
    }

    kernel_ip_size = get_signal("h", kernel, kernel_ip_size);

    if (kernel_ip_size == 0) {
        /* Caught error */
        return kernel_ip_size;
    }

    /* Determine input size */
    ip_size =
        signal_ip_size >= kernel_ip_size ? signal_ip_size : kernel_ip_size;

    /* Pad zeros to the smaller matrix */

    convolve(signal, kernel, (int)ip_size, result);

    print_signal("x", signal, ip_size);
    print_signal("h", kernel, ip_size);
    print_signal("y", result, ip_size);

    /* getch(); */

    return 0;
}
