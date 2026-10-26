#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../lib/tinyexpr.h"

static te_expr *g_expr = NULL;
static double g_x = 0.0;
static int g_bad = 0;

static double user_f(double x)
{
    g_x = x;
    double y = te_eval(g_expr);

    if (isnan(y)) {
        const double eps = 1e-9;
        g_x = x - eps;
        double l = te_eval(g_expr);
        g_x = x + eps;
        double r = te_eval(g_expr);

        if (isfinite(l) && isfinite(r) && fabs(l - r) < 1e-6)
            y = 0.5 * (l + r);
    }

    if (!isfinite(y)) g_bad = 1;
    return y;
}

double trapezoidalRule(double (*func)(double), double a, double b, int n)
{
    double h = (b - a) / n;
    double sum = func(a) + func(b);
    for (int i = 1; i < n; i++)
        sum += 2.0 * func(a + i * h);
    return (h / 2.0) * sum;
}

int main()
{
    char expr[256];
    double a, b;
    int n, err;

    printf("Enter f(x), e.g. sin(x)/x or x^3-2*x+1: ");
    if (!fgets(expr, sizeof expr, stdin))
        return 1;
    expr[strcspn(expr, "\r\n")] = '\0';

    te_variable vars[] = {{"x", &g_x}};
    g_expr = te_compile(expr, vars, 1, &err);
    if (!g_expr)
    {
        printf("Parse error at position %d.\n", err);
        return 1;
    }

    printf("Enter a, b, n: ");
    if (scanf("%lf %lf %d", &a, &b, &n) != 3 || n <= 0 || a >= b)
    {
        printf("Invalid input.\n");
        te_free(g_expr);
        return 1;
    }

    double result = trapezoidalRule(user_f, a, b, n);

    if (g_bad || !isfinite(result)) {
        printf("The integrand is undefined (NaN/inf) somewhere in [%g, %g].\n", a, b);
        te_free(g_expr);
        return 1;
    }

    printf("\nf(x)       = %s\n", expr);
    printf("Integral   = %.10lf\n", result);

    te_free(g_expr);
    return 0;
}