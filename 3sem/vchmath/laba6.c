#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Многочлен Лагранжа
double lagrange_mult(double x, int i,
			double* arr_x, size_t arr_x_sz)
{
	double ret = 1;
	double x_i = arr_x[i];
	for(size_t k = 0; k < arr_x_sz; ++k)
	{
		if(k == i) continue;
		ret *= (x - arr_x[k]) / (x_i - arr_x[k]);
	}
	return ret;
}

double interp_lagrange(double x,
			double* arr_x, double* arr_y, size_t arr_xy_sz)
{
	double y = 0;
	for(size_t i = 0; i < arr_xy_sz; ++i)
		y += arr_y[i] * lagrange_mult(x, i, arr_x, arr_xy_sz);
	return y;
}
void print_lagrange(double* arr_x, double* arr_y, size_t arr_xy_sz)
{
	for(size_t i = 0; i < arr_xy_sz; ++i){
		double x_i = arr_x[i];
		for(size_t k = 0; k < arr_xy_sz; ++k)
		{
			if(k == i) continue;
			printf(" ((x - %lf) / %lf) %c", arr_x[k], (x_i - arr_x[k]), (k == arr_xy_sz - 1) || (i == arr_xy_sz - 1 && k == arr_xy_sz - 2) ? ' ' : '*');
		}
		printf("* %lf %c \n", arr_y[i], i == arr_xy_sz - 1 ? ' ' : '+');
	}
	puts("");
}

// Конечные разности
double** get_fdiffs(double* arr_y, size_t arr_y_sz)
{
	double** ret = malloc(sizeof(double*) * arr_y_sz);
	for(size_t i = 0; i < arr_y_sz; ++i)
		ret[i] = malloc(sizeof(double) * arr_y_sz);

	for(size_t n = 0; n < arr_y_sz; ++n)
		ret[0][n] = arr_y[n];
	for(size_t i = 1; i < arr_y_sz; ++i)
		for(size_t n = 0; n < arr_y_sz - i; ++n)
			ret[i][n] = ret[i-1][n+1] - ret[i-1][n];

	return ret;
}

// Многочлен Ньютона
// с начала:
double interp_newton_fw(double x, double** fdiffs,
			double* arr_x, double* arr_y, size_t arr_xy_sz)
{
	double y = arr_y[0];
	double denom = 1;
	double mult = 1;
	double h = arr_x[1] - arr_x[0];
	for(size_t i = 1; i < arr_xy_sz; ++i)
	{
		denom *= i * h;
		mult *= x - arr_x[i-1];
		y += fdiffs[i][0] * mult / denom;
	}
	return y;
}
void print_newton_fw(double** fdiffs,
			double* arr_x, double* arr_y, size_t arr_xy_sz)
{
	double denom = 1;
	double h = arr_x[1] - arr_x[0];
	printf("%lf ", fdiffs[0][0]);
	for(size_t i = 1; i < arr_xy_sz; ++i)
	{
		denom *= i * h;
		printf("%lf ", fdiffs[i][0] / denom);
	}
	puts("");
}
// с конца:
double interp_newton_bw(double x, double** fdiffs,
			double* arr_x, double* arr_y, size_t arr_xy_sz)
{
	double y = arr_y[arr_xy_sz-1];
	double denom = 1;
	double mult = 1;
	double h = arr_x[1] - arr_x[0];
	for(int i = arr_xy_sz - 2; i > -1; --i)
	{
		denom *= (arr_xy_sz - i - 1) * h;
		mult *= x - arr_x[i+1];
		y += fdiffs[arr_xy_sz - i - 1][i] * mult / denom;
	}
	return y;
}
void print_newton_bw(double** fdiffs,
			double* arr_x, double* arr_y, size_t arr_xy_sz)
{
	double denom = 1;
	double h = arr_x[1] - arr_x[0];
	printf("%lf ", fdiffs[0][arr_xy_sz-1]);
	for(int i = arr_xy_sz - 2; i > -1; --i)
	{
		denom *= (arr_xy_sz - i - 1) * h;
		printf("%lf ", fdiffs[arr_xy_sz - i - 1][i] / denom);
	}
	puts("");
}

// Аппроксимация методом наименьших квадратов
void approx_coeffs(double* arr_x, double* arr_y, size_t arr_xy_sz,
			double* a, double* b)
{
	double x_sum = 0, xpow2_sum = 0, y_sum = 0, xy_sum = 0;
	size_t n = arr_xy_sz;

	for(size_t i = 0; i < arr_xy_sz; ++i)
	{
		x_sum += arr_x[i];
		y_sum += arr_y[i];
		xy_sum += arr_x[i] * arr_y[i];
		xpow2_sum += arr_x[i]*arr_x[i];
	}
	*a = (n * xy_sum - x_sum * y_sum) /
	     (n * xpow2_sum - x_sum * x_sum);
	*b = (y_sum - (*a) * x_sum) / n;
}
double approx_result(double x, double a, double b)
{
	return a*x + b;
}

// Значащие и верные цифры
void sign_corr_digits(double approx_y, double exact_y,
			int* sign, int* corr)
{
	int isign, icorr;
	size_t digits = 8;
	int correct_cnt = 0;
	double inacc = fabs(exact_y - approx_y);
	for(size_t i = 0; i < digits; ++i)
	{
		if(correct_cnt == 0 && inacc < 1)
			inacc *= 10;
		else if(correct_cnt == 0)
			correct_cnt = i;

		approx_y *= 10;
		exact_y *= 10;
	}

	isign = (int)approx_y; icorr = (int)exact_y;
	int digit_cnt = 0;
	{ int _isign = isign; while(_isign > 0) { ++digit_cnt; _isign /= 10; } }
	int ch_c = isign / pow(10, digit_cnt - correct_cnt);
	int ch_e = icorr / pow(10, digit_cnt - correct_cnt);
	if(ch_c == ch_e)
		icorr = ch_c;
	else
		icorr = isign / pow(10, digit_cnt - correct_cnt + 1);
	*sign = isign;
	*corr = icorr;
}

double f(double x) { return (1/tan(cos(x) - sin(x))); }

int main()
{
	const int arr_xy_sz = 5;
	double arr_x[5] = {0.0, 0.15, 0.30, 0.45, 0.60};
	double arr_y[5] = {0.64, 0.90, 1.29, 1.99, 3.75};

	double** fdiffs = get_fdiffs(arr_y, arr_xy_sz);
	double approx_a, approx_b;
	approx_coeffs(arr_x, arr_y, arr_xy_sz, &approx_a, &approx_b);

	double calc_x[3] = {0.11, 0.33, 0.55};

	// Вычисления значений для 4 методов в 3 точках
	printf("%25s|%4s|%21s|%20s|%11s|%11s|%21s|%12s\n",
		"метод", "x", "точное y", "прибл. y", "Δy", "δy", "знач. цифры", "верные цифры");
	for(size_t i = 0; i < 3; ++ i)
	{
		double exact = f(calc_x[i]);
		double y = interp_lagrange(calc_x[i], arr_x, arr_y, arr_xy_sz);
		double dy_abs = fabs(exact - y);
		double dy_rel = fabs(dy_abs / exact);
		int sign, corr; sign_corr_digits(y, exact, &sign, &corr);
		printf("%30s|%4lg|%15.12lf|%15.12lf|%10lf|%10lf|%12d|%12d\n",
			"мн. Лагранжа",
			calc_x[i], exact, y, dy_abs, dy_rel, sign, corr);

		y = interp_newton_fw(calc_x[i], fdiffs, arr_x, arr_y, arr_xy_sz);
		dy_abs = fabs(exact - y);
		dy_rel = fabs(dy_abs / exact);
		sign_corr_digits(y, exact, &sign, &corr);
		printf("%33s|%4lg|%15.12lf|%15.12lf|%10lf|%10lf|%12d|%12d\n",
			"мн. Ньютона с нач.",
			calc_x[i], exact, y, dy_abs, dy_rel, sign, corr);

		y = interp_newton_bw(calc_x[i], fdiffs, arr_x, arr_y, arr_xy_sz);
		dy_abs = fabs(exact - y);
		dy_rel = fabs(dy_abs / exact);
		sign_corr_digits(y, exact, &sign, &corr);
		printf("%33s|%4lg|%15.12lf|%15.12lf|%10lf|%10lf|%12d|%12d\n",
			"мн. Ньютона с кнц.",
			calc_x[i], exact, y, dy_abs, dy_rel, sign, corr);

		y = approx_result(calc_x[i], approx_a, approx_b);
		dy_abs = fabs(exact - y);
		dy_rel = fabs(dy_abs / exact);
		sign_corr_digits(y, exact, &sign, &corr);
		printf("%30s|%4lg|%15.12lf|%15.12lf|%10lf|%10lf|%12d|%12d\n",
			"аппр. мет. наим. кв.",
			calc_x[i], exact, y, dy_abs, dy_rel, sign, corr);
	}

	// Таблицы конечных разностей
	printf("\nКонечные разности:\n");
	printf("%10s|%10s|%11s|%14s\n", "x", "y*", "Δy*", "Δ^2y*");
	for(size_t i = 0; i < arr_xy_sz; ++i)
	{
		if(arr_xy_sz - i > 2)
			printf("%10.5lg|%10.5lg|%10.5lg|%13.5lg\n",
				arr_x[i], fdiffs[0][i], fdiffs[1][i], fdiffs[2][i]);
		else if(arr_xy_sz - i == 1)
			printf("%10.5lg|%10.5lg|%10s|%13s\n",
				arr_x[i], fdiffs[0][i], "--", "--");
		else
			printf("%10.5lg|%10.5lg|%10.5lg|%13s\n",
				arr_x[i], fdiffs[0][i], fdiffs[1][i], "--");
	}

	double prev_arr_y3 = arr_y[3];
	arr_y[3] *= 1.1;
	double** _fdiffs = get_fdiffs(arr_y, arr_xy_sz);
	printf("\nКонечные разности с добавленной погрешностью:\n");
	printf("%10s|%10s|%11s|%14s\n", "x", "y*", "Δy*", "Δ^2y*");
	for(size_t i = 0; i < arr_xy_sz; ++i)
	{
		if(arr_xy_sz - i > 2)
			printf("%10.5lg|%10.5lg|%10.5lg|%13.5lg\n",
				arr_x[i], _fdiffs[0][i], _fdiffs[1][i], _fdiffs[2][i]);
		else if(arr_xy_sz - i == 1)
			printf("%10.5lg|%10.5lg|%10s|%13s\n",
				arr_x[i], _fdiffs[0][i], "--", "--");
		else
			printf("%10.5lg|%10.5lg|%10.5lg|%13s\n",
				arr_x[i], _fdiffs[0][i], _fdiffs[1][i], "--");
	}
	arr_y[3] = prev_arr_y3;

	// Сводная таблица (сравнение интерполяции и аппроксимации)
	printf("\n%25s|%4s|%21s|%20s|%11s|%11s|%21s|%12s\n",
		"метод", "x", "точное y", "прибл. y", "Δy", "δy", "знач. цифры", "верные цифры");
	for(size_t i = 0; i < 3; ++i)
	{
		double exact = f(calc_x[i]);
		double y = interp_lagrange(calc_x[i], arr_x, arr_y, arr_xy_sz);
		double dy_abs = fabs(exact - y);
		double dy_rel = fabs(dy_abs / exact);
		int sign, corr; sign_corr_digits(y, exact, &sign, &corr);
		printf("%30s|%4lg|%15.12lf|%15.12lf|%10lf|%10lf|%12d|%12d\n",
			"мн. Лагранжа",
			calc_x[i], exact, y, dy_abs, dy_rel, sign, corr);
	}
	for(size_t i = 0; i < 3; ++i)
	{
		double exact = f(calc_x[i]);
		double y = approx_result(calc_x[i], approx_a, approx_b);
		double dy_abs = fabs(exact - y);
		double dy_rel = fabs(dy_abs / exact);
		int sign, corr; sign_corr_digits(y, exact, &sign, &corr);
		printf("%30s|%4lg|%15.12lf|%15.12lf|%10lf|%10lf|%12d|%12d\n",
			"аппр. мет. наим. кв.",
			calc_x[i], exact, y, dy_abs, dy_rel, sign, corr);
	}

	// вывод коэффициентов:
	printf("\n\nМногочлен Лагранжа:\n");
	print_lagrange(arr_x, arr_y, arr_xy_sz);
	printf("\nКоэффициенты многочлена Ньютона с начала:\n");
	print_newton_fw(fdiffs, arr_x, arr_y, arr_xy_sz);
	printf("\nКоэффициенты многочлена Ньютона с конца:\n");
	print_newton_bw(fdiffs, arr_x, arr_y, arr_xy_sz);
	printf("\nПрямая в методе линейной аппроксимации:\n");
	printf("%lfx + %lf\n", approx_a, approx_b);
}
