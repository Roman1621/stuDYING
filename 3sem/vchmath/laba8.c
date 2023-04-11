#include <float.h>
#include <math.h>
#include <stdio.h>

// Подсчёт верных цифр в числе
unsigned count_right_digits(double num, double incorr)
{
	num = fabs(num);

	incorr *= 10;
	num /= incorr; num = round(num); num *= incorr;
	while(floor(num) < num)
		num *= 10;

	long long inum = (long long)round(num);
	unsigned rdigs = 0;
	while(inum > 0)
	{ rdigs++; inum /= 10; }

	return rdigs;
}

// Разностные производные
double right_sub_deriv(double (*f)(double), double h, double x) { return (f(x + h) - f(x)) / h; }
double left_sub_deriv(double (*f)(double), double h, double x) { return (f(x) - f(x - h)) / h; }
double center_sub_deriv(double (*f)(double), double h, double x) { return (f(x + h) - f(x - h)) / (2*h); }

// Разностная производная второго порядка
double sub_deriv2(double (*f)(double), double h, double x) { return (f(x - h) - 2*f(x) + f(x + h)) / pow(h, 2); }


// Кубический сплайн
double spline(double (*f)(double), double (*f_deriv)(double), double x_i, double x_i1, double x)
{
	double f_i = f(x_i), f_i1 = f(x_i1);
	double h_i = x_i1 - x_i;
	double t = (x - x_i) / h_i;
	double m_i = f_deriv(x_i), m_i1 = f_deriv(x_i1);
	return f_i * pow((1 - t), 2) * (1 + 2*t) + f_i1 * pow(t, 2) * (3 - 2*t)
		+ m_i * h_i * t * pow((1 - t), 2) - m_i1 * pow(t, 2) * (1 - t) * h_i;
}
double spline_deriv1(double (*f)(double), double (*f_deriv)(double), double x_i, double x_i1, double x)
{
	double f_i = f(x_i), f_i1 = f(x_i1);
	double h_i = x_i1 - x_i;
	double t = (x - x_i) / h_i;
	double m_i = f_deriv(x_i), m_i1 = f_deriv(x_i1);
	return (  -6 * f_i * t * (1 - t) + 6 * f_i1 * t * (1 - t)
		+ m_i * h_i * (1 - t) * (1 - 3*t) + m_i1 * h_i * t * (3*t - 2) ) / h_i;
}
double spline_deriv2(double (*f)(double), double (*f_deriv)(double), double x_i, double x_i1, double x)
{
	double f_i = f(x_i), f_i1 = f(x_i1);
	double h_i = x_i1 - x_i;
	double t = (x - x_i) / (x_i1 - x_i);
	double m_i = f_deriv(x_i), m_i1 = f_deriv(x_i1);
	return 6*(f_i - f_i1) * (2*t - 1) / pow(h_i, 2) + 2*(m_i*(3*t - 2) + m_i1*(3*t - 1)) / h_i;
}


// Начальная функция, её производные и узлы:
double points_x[6] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0};
double f(double x){return pow((tan(x)),(sin(x)));}
double f_deriv(double x){return (pow(tan(x),sin(x))*(cos(x)*log(tan(x))+(1/cos(x))));}
double f_deriv2(double x){return ((pow(tan(x), sin(x))*(log(tan(x))*((cos(2*x) + 1)*log(tan(x)) - 2*sin(x) + 4) + 2*((1/cos(x))*(tan(x) + (1/cos(x))) + (1/sin(x)))))/2); }

// Готовая функция сплайна от одного аргумента, для передачи в sub_deriv(...)
double spline_func(double x)
{
	return spline(&f, &f_deriv, points_x[3], points_x[4], x);
}

void put_line(size_t length)
{
	for(size_t i = 0; i < length; ++i) putchar('-'); puts("");
}

int main()
{
	printf("Поиск неприемлимого (без верных цифр) значения h:\n");
	double x = 0.5; double h; for(h = 0.001; ; h += 0.001)
	{
		double res = right_sub_deriv(&f, h, x);
		double inacc = fabs(f_deriv(x) - right_sub_deriv(&f, h, x));
		if(count_right_digits(res, inacc) == 0)
			break;
	}
	printf("h = %lg;\n", h);
	printf("В точке x = %lg: f(x) = %lg f'(x) = %lg, f'*(x) = %lg (Δf'*(x) = %lg)\n", x, f(x), f_deriv(x), right_sub_deriv(&f, h, x), f_deriv(x) - right_sub_deriv(&f, h, x));

	printf("\nТочность вычисления производной при различных значениях h:\n");
	printf("%-10s|%-16s|%-20s\n", "h", "Δf'*(x)", "Верных цифр");
	for(h = 1.0; h >= DBL_EPSILON / 4; h /= 10)
	{
		double res = right_sub_deriv(&f, h, x);
		double inacc = fabs(f_deriv(x) - right_sub_deriv(&f, h, x));
		printf("%-10lg|%-15lg|%-20u\n", h, inacc, count_right_digits(res, inacc));
	}

	h = 0.01;
	printf("\nРазностные производные при h = %lg, x = %lg:\n\n", h, x);
	printf("%-30s|%-10s|%-10s\n", "Тип производной", "f*'(x)", "Δf'*(x)");
	{
		double res, inacc;

		res = f_deriv(x);
		printf("%-16s|%-10lg|%-10lg\n", "f'(x)", res, 0.);
		res = left_sub_deriv(&f, h, x);
		inacc = fabs(f_deriv(x) - res);
		printf("%-29s|%-10lg|%-10lg\n", "левая разностн.", res, inacc);
		res = right_sub_deriv(&f, h, x);
		inacc = fabs(f_deriv(x) - res);
		printf("%-16s|%-10lg|%-10lg\n", "правая разностн.", res, inacc);
		res = center_sub_deriv(&f, h, x);
		inacc = fabs(f_deriv(x) - res);
		printf("%-16s|%-10lg|%-10lg\n", "центральная раз.", res, inacc);

		put_line(40);

		res = f_deriv2(x);
		printf("%-16s|%-10lg|%-10lg\n", "f''(x)", res, 0.);
		res = sub_deriv2(&f, h, x);
		inacc = fabs(f_deriv2(x) - res);
		printf("%-25s|%-10lg|%-10lg\n", "разн. 2-го пор.", res, inacc);
	}

	printf("\nПроизводные сплайна 1-го и 2-го порядков при h = %lg, x = %lg:\n\n", h, x);
	printf("%-30s|%-10s|%-10s\n", "Тип производной", "f*'(x)", "Δf'*(x)");
	{
		double res, inacc;

		res = f_deriv(x);
		printf("%-16s|%-10lg|%-10lg\n", "f'(x)", res, 0.);
		res = spline_deriv1(&f, &f_deriv, points_x[3], points_x[4], x);
		inacc = fabs(f_deriv(x) - res);
		printf("%-16s|%-10lg|%-10lg\n", "s'(x)", res, inacc);

		put_line(40);

		res = f_deriv2(x);
		printf("%-16s|%-10lg|%-10lg\n", "f''(x)", res, 0.);
		res = spline_deriv2(&f, &f_deriv, points_x[3], points_x[4], x);
		inacc = fabs(f_deriv2(x) - res);
		printf("%-16s|%-10lg|%-10lg\n", "s''(x)", res, inacc);
	}

	printf("\nРазностные производные сплайна при h = %lg, x = %lg:\n\n", h, x);
	printf("%-30s|%-10s|%-10s\n", "Тип производной", "f*'(x)", "Δf'*(x)");
	{
		double res, inacc;

		res = f_deriv(x);
		printf("%-16s|%-10lg|%-10lg\n", "f'(x)", res, 0.);
		res = left_sub_deriv(&spline_func, h, x);
		inacc = fabs(f_deriv(x) - res);
		printf("%-23s|%-10lg|%-10lg\n", "левая р-я s'(x)", res, inacc);
		res = right_sub_deriv(&spline_func, h, x);
		inacc = fabs(f_deriv(x) - res);
		printf("%-16s|%-10lg|%-10lg\n", "правая р-я s'(x)", res, inacc);
		res = center_sub_deriv(&spline_func, h, x);
		inacc = fabs(f_deriv(x) - res);
		printf("%-16s|%-10lg|%-10lg\n", "центр. р-я s'(x)", res, inacc);

		put_line(40);

		res = f_deriv2(x);
		printf("%-16s|%-10lg|%-10lg\n", "f''(x)", res, 0.);
		res = sub_deriv2(&spline_func, h, x);
		inacc = fabs(f_deriv2(x) - res);
		printf("%-21s|%-10lg|%-10lg\n", "разн. 2п. s'(x)", res, inacc);
	}

	printf("\nТочность вычисления производной сплайна при различных значениях h:\n");
	printf("%-10s|%-16s|%-20s\n", "h", "Δf'*(x)", "Верных цифр");
	double h_opt_in_table = -INFINITY, inacc_opt_in_table = INFINITY;
	for(h = 1.0; h >= DBL_EPSILON / 4; h /= 10)
	{
		double res = right_sub_deriv(&spline_func, h, x);
		double inacc = fabs(f_deriv(x) - right_sub_deriv(&spline_func, h, x));
		printf("%-10lg|%-15lg|%-20u\n", h, inacc, count_right_digits(res, inacc));
		if(inacc < inacc_opt_in_table)
		{ inacc_opt_in_table = inacc; h_opt_in_table = h; }
	}
	printf("\nЧисло h, после которого начинается возрастание погрешности: %lg\n", h_opt_in_table);

	printf("Абсолютное число обусловленности: v_Δ = 2 / h = %lg\n", 2 / h_opt_in_table);
}