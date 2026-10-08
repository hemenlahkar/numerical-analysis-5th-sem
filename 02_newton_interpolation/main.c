#include <stdio.h>

int main() {
    int n;
    double x[50], y[50], dd[50];
    double xp, yp;

    printf("Enter number of data points: ");
    scanf("%d", &n);

    printf("Enter x and y values:\n");
    for (size_t i = 0; i < n; i++)
    {
        scanf("%lf %lf", x + i, y + i);
        dd[i] = y[i];
    }

    printf("Enter x at which f(x) is required: ");
    scanf("%lf", &xp);

    // Compute divide difference table
    for (int i = 1; i < n; i++)
    {
        for (int j = n - 1; j >= i; j--)
        {
            dd[j] = (dd[j] - dd[j - 1]) / (x[j] - x[j - i]);
        }
    }

    // Evaluate using Newton's divided difference polynomial
    yp = dd[n - 1];
    for (int i = n - 2; i >= 0; i--)
    {
        yp = yp * (xp - x[i]) + dd[i];
    }
    
    printf("f(%.4lf) = %.6lf\n", xp, yp);

    return 0;
}