#include <stdio.h>
#include <math.h>

typedef double (*FuncPtr)(double);

double f_rational(double x) { return 1.0 / (1.0 + x * x); }
double f_sin(double x)      { return sin(x); }
double f_gauss(double x)    { return exp(-x * x); }
double f_cubic(double x)    { return x * x * x - 2.0 * x + 1.0; }
double f_inverse(double x)  { return 1.0 / x; }

FuncPtr chooseFunction(const char **name) {
    int c;
    printf("Choose integrand:\n");
    printf("  1. 1/(1+x^2)\n");
    printf("  2. sin(x)\n");
    printf("  3. exp(-x^2)\n");
    printf("  4. x^3 - 2x + 1\n");
    printf("  5. 1/x\n");
    printf("Choice: ");
    if (scanf("%d", &c) != 1) return NULL;

    switch (c) {
        case 1: *name = "1/(1+x^2)";   return f_rational;
        case 2: *name = "sin(x)";      return f_sin;
        case 3: *name = "exp(-x^2)";   return f_gauss;
        case 4: *name = "x^3-2x+1";    return f_cubic;
        case 5: *name = "1/x";         return f_inverse;
        default: return NULL;
    }
}

double trapezoidalRule(FuncPtr func, double a, double b, int n) {
    double h = (b - a) / n;
    double sum = func(a) + func(b);
    for (int i = 1; i < n; i++)
        sum += 2.0 * func(a + i * h);
    return (h / 2.0) * sum;
}

int main(void) {
    double a, b;
    int n;
    const char *name = NULL;

    FuncPtr f = chooseFunction(&name);
    if (!f) { printf("Invalid choice.\n"); return 1; }

    printf("Enter a, b, n: ");
    if (scanf("%lf %lf %d", &a, &b, &n) != 3 || n <= 0 || a >= b) {
        printf("Invalid input.\n");
        return 1;
    }

    double result = trapezoidalRule(f, a, b, n);
    printf("\nf(x)      = %s\n", name);
    printf("Integral  = %.10lf\n", result);
    return 0;
}