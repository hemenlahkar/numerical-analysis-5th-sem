#include <stdio.h>
#include <math.h>

#define MAX 50
#define EPS 1e-9

double factorial(int n)
{
    double f = 1.0;
    for (int i = 2; i <= n; i++)
    {
        f *= i;
    }
    return f;
}

int checkEqualSpacing(double x[], int n, double *h)
{
    *h = x[1] - x[0];
    for (int i = 1; i < n; i++)
    {
        if (fabs((x[i] - x[i - 1]) - *h) > EPS)
        {
            return 0;
        }
    }
    return 1;
}

/* Newton's Forward Interpolation */
double newtonForward(double x[], double y[], int n, double xp)
{
    double diff[MAX][MAX] = {0};
    double h = x[1] - x[0];

    for (int i = 0; i < n; i++)
    {
        diff[i][0] = y[i];
    }

    /* Build forward difference table */
    for (int j = 1; j < n; j++)
    {
        for (int i = 0; i < n - j; i++)
        {
            diff[i][j] = diff[i + 1][j - 1] - diff[i][j - 1];
        }
    }

    double p = (xp - x[0]) / h;
    double result = diff[0][0];
    double term = 1.0;

    for (int k = 1; k < n; k++)
    {
        term *= (p - (k - 1));
        result += (term * diff[0][k]) / factorial(k);
    }

    return result;
}

/* Newton's Backward Interpolation */
double newtonBackward(double x[], double y[], int n, double xp)
{
    double diff[MAX][MAX] = {0};
    double h = x[1] - x[0];

    for (int i = 0; i < n; i++)
    {
        diff[i][0] = y[i];
    }

    /* Build backward difference table */
    for (int j = 1; j < n; j++)
    {
        for (int i = n - 1; i >= j; i--)
        {
            diff[i][j] = diff[i][j - 1] - diff[i - 1][j - 1];
        }
    }

    double p = (xp - x[n - 1]) / h;
    double result = diff[n - 1][0];
    double term = 1.0;

    for (int k = 1; k < n; k++)
    {
        term *= (p + (k - 1));
        result += (term * diff[n - 1][k]) / factorial(k);
    }

    return result;
}

int main(void)
{
    int n, choice;
    double x[MAX], y[MAX], xp, h, ans;

    printf("Enter number of data points: ");
    scanf("%d", &n);

    printf("Enter x and y values:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%lf %lf", &x[i], &y[i]);
    }

    printf("Enter x at which f(x) is required: ");
    scanf("%lf", &xp);

    if (!checkEqualSpacing(x, n, &h))
    {
        printf("\nError: Newton's forward/backward interpolation requires equally spaced x-values.\n");
        printf("Your x-values are not equally spaced. Use Newton's divided difference method instead.\n");
        return 1;
    }

    printf("\nChoose method:\n");
    printf("1. Newton Forward Interpolation\n");
    printf("2. Newton Backward Interpolation\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        ans = newtonForward(x, y, n, xp);
        printf("Newton Forward: f(%.4lf) = %.6lf\n", xp, ans);
        break;

    case 2:
        ans = newtonBackward(x, y, n, xp);
        printf("Newton Backward: f(%.4lf) = %.6lf\n", xp, ans);
        break;

    default:
        printf("Invalid choice.\n");
    }
    return 0;
}