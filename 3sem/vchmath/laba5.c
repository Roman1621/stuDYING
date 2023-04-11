#include <math.h>
#include <stdio.h>

double int_rect(double (*f)(double), double a, double b,
		unsigned n)
{
	double h = (b - a) / n;
	double xi = a;

	double I = 0;
	for(unsigned i = 1; i <= n; ++i, xi += h)
		I += f(xi + h/2);
	I *= h;
	return I;
}

double int_trap(double (*f)(double), double a, double b,
		  unsigned n)
{
	double h = (b - a) / n;
	double xi = a;

	double I = (f(a) + f(b)) / 2;
	for(unsigned i = 1; i <= n; ++i, xi += h)
		I += (f(xi) + f(xi + h)) / 2;
	I *= h;
	return I;
}

double int_simps(double (*f)(double), double a, double b,
		  unsigned n)
{
	double h = (b - a) / n;

	double I = 0;
	for(unsigned i = 0, xi = a; i < n; ++i)
		I += f(a + i*h) + 4*f(a + (i + 0.5)*h) + f(a + (i + 1)*h);
	I *= h / 6;
	return I;
}

double f(double x) { return ((log(x) * (x+1))/x);}

double achieve_eps_int(double(*int_mt)(double (*)(double), double, double, unsigned), double (*f)(double),
			double a, double b, unsigned* n,
			double inacc_divider, double target_val, double target_eps)
{
	double Ih = int_mt(f, a, b, *n);
	if(fabs(Ih - target_val) <= target_eps){
		double Ih2 = int_mt(f, a, b, (*n) * 2);
		return fabs(Ih2 - Ih) / inacc_divider;
	}
	for(;; (*n) *= 2){
		double Ih2 = int_mt(f, a, b, (*n) * 2);
		double eps = fabs(Ih2 - target_val);
		if(eps <= target_eps)
			return fabs(Ih2 - Ih) / inacc_divider;
		Ih = Ih2;
	};
}


int main()
{
	double a = 1, b = 2;
	double real_int_val = 0.6265208680789913; // "точное" значение интеграла
	double teps = 1e-6; // искомое ε (разница между "точным" и вычисленным приблизительным значением

	printf("Метод прямоугольников:\n");
	printf("%13s%13s%13s%40s%8s\n", "ε", "I", "ΔI", "Неточность по Рунге", "N");
	for(double eps = 1e-6; eps < 0.01; eps *= 10)
	{
		unsigned n = 2;
		double inacc = achieve_eps_int(&int_rect, &f,
					a, b, &n,
					3, real_int_val, eps);
		double I = int_rect(&f, a, b, n);
		printf("%12.8lf%13.8lf%12.8lf%23.12lf%8u\n", eps, I, fabs(real_int_val - I), inacc, n);
	}

	printf("\nМетод трапеций:\n");
	printf("%13s%13s%13s%40s%8s\n", "ε", "I", "ΔI", "Неточность по Рунге", "N");
	for(double eps = 1e-6; eps < 0.01; eps *= 10)
	{
		unsigned n = 2;
		double inacc = achieve_eps_int(&int_trap, &f,
					a, b, &n,
					3, real_int_val, eps);
		double I = int_rect(&f, a, b, n);
		printf("%12.8lf%13.8lf%12.8lf%23.12lf%8u\n", eps, I, fabs(real_int_val - I), inacc, n);
	}

	printf("\nМетод Симпсона:\n");
	printf("%13s%13s%13s%40s%8s\n", "ε", "I", "ΔI", "Неточность по Рунге", "N");
	for(double eps = 1e-6; eps < 0.01; eps *= 10)
	{
		unsigned n = 2;
		double inacc = achieve_eps_int(&int_simps, &f,
					a, b, &n,
					15, real_int_val, eps);
		double I = int_rect(&f, a, b, n);
		printf("%12.8lf%13.8lf%12.8lf%23.12lf%8u\n", eps, I, fabs(real_int_val - I), inacc, n);
	}
}
