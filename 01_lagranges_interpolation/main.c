#include <stdio.h>

int main()
{
    int n, i, j;
    double x[50], y[50], xp, yp = 0.0, term;

    printf("Enter number of data points: ");
    scanf("%d", &n);

    printf("Enter x and y values:\n");
    for (size_t i = 0; i < n; i++)
    {
        scanf("%lf %lf", x + i, y + i);
    }

    printf("Enter x at which f(x) is required: ");
    scanf("%lf", &xp);

    // Lagrange's Interpolation
    for (size_t i = 0; i < n; i++)
    {
        term = y[i];
        for (size_t j = 0; j < n; j++)
        {
            if (j != i)
            {
                term = term * (xp - x[j]) / (x[i] - x[j]);
            }
        }
        yp += term;
    }

    printf("f(%.4lf) = %.6lf\n", xp, yp);

    return 0;
}