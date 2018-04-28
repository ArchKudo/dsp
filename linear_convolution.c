
/**
 * Menu based linear convolution in C89
 * Modified version of https://stackoverflow.com/a/8425094
 * TODO: Ask for edges of sequences
 * TODO: Print sequence with consideration of edges
 */

#include <stddef.h>
#include <stdio.h>

#define MAX 20
#define ELEMENT_COUNT(X) (sizeof(X) / sizeof((X)[0]))

/**
 * @brief  The main convolution algorithm
 * @param  signal[]: x[n]
 * @param  signal_ip_size: Input size of x[n]
 * @param   kernel[]: h[n]
 * @param  kernel_ip_size: Input size of h[n]
 * @retval None
 */
void convolve(const double signal[/* signal_len */],
              unsigned int signal_ip_size,
              const double kernel[/* kernel_len */],
              unsigned int kernel_ip_size,
              double result[/* signal_len + kernel_len - 1 */]) {
    unsigned int n = 0;
    unsigned int kmin = 0, kmax = 0, k = 0;

    for (n = 0; n < signal_ip_size + kernel_ip_size - 1; n++) {
        result[n] = 0;

        /* Handling for when length of either seq is greater than the other */
        kmin = (n >= kernel_ip_size - 1) ? n - (kernel_ip_size - 1) : 0;
        kmax = (n < signal_ip_size - 1) ? n : signal_ip_size - 1;

        for (k = kmin; k <= kmax; k++) {
            result[n] += signal[k] * kernel[n - k];
        }
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
    double signal[MAX], kernel[MAX];
    double result[ELEMENT_COUNT(signal) + ELEMENT_COUNT(kernel) - 1];
    unsigned int signal_ip_size = 0;
    unsigned int kernel_ip_size = 0;

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

    convolve(signal, signal_ip_size, kernel, kernel_ip_size, result);

    print_signal("x", signal, signal_ip_size);
    print_signal("h", kernel, kernel_ip_size);
    print_signal("y", result, (signal_ip_size + kernel_ip_size - 1));

    return 0;
}
