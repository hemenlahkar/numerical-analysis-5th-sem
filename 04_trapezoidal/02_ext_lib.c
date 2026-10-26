#include <stdio.h>
#include <string.h>
#include "../lib/tinyexpr.h"

static te_expr *g_expr = NULL;
static double g_x = 0.0;

static double user_f(double x)
{
    g_x = x;
    return te_eval(g_expr);
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
    printf("\nf(x)       = %s\n", expr);
    printf("Integral   = %.10lf\n", result);

    te_free(g_expr);
    return 0;
}