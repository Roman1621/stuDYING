#include <stdio.h>
#include <math.h>
#include <errno.h>
const double delta_min = 1e-6;
#define ERRNO_APPROX_INTERVAL 1
#define ERRNO_APPROX_PRECISION 2
#define ERRNO_APPROX_INVALID_DERIVATIVE 3
#define ERRNO_ROUND_PRECISION 2

double _round(double x, double delta){
	if(delta <= 1e-9){
		errno = ERRNO_ROUND_PRECISION;
		return NAN;
	}
	return delta * floor((x / delta) + (x > 0 ? 0.5 : -0.5));
}

double min_f(double (*f)(double), double left, double right, int abs, double delta){
	double _min = INFINITY;
	if(abs)
		for(double x = left; x <= right+delta; x += delta){
		       	if(fabs(f(x)) < _min) _min = fabs(f(x)); 
		}
	else
		for(double x = left; x <= right+delta; x += delta){ 
			if(f(x) < _min) _min = f(x);
		}
	return _min;
}

double max_f(double (*f)(double), double left, double right, int abs, double delta){
	double _max = abs ? 0 : -INFINITY;
	if(abs)
		for(double x = left; x <= right+delta; x += delta){ 
			if(fabs(f(x)) > _max) _max = fabs(f(x)); 
		}
	else
		for(double x = left; x <= right+delta; x += delta){ 
			if(f(x) > _max) _max = f(x); 
		}
	return _max;
}

double bisect(double (*f)(double), double left, double right, double eps, int* N){
	double e = fabs(eps) * 2;
	double fleft = f(left);
	double fright = f(right);
	double x = (left + right) / 2, y;
	if(fleft*fright > 0){
		errno = ERRNO_APPROX_INTERVAL;
		return NAN;
	}
	if(eps <= 0){
		errno = ERRNO_APPROX_PRECISION;
		return NAN;
	}
	*N = 0;
	if(fleft == 0) return left;
	if(fright == 0) return right;
	while((right - left) >= e){
		x = (left + right) / 2;
		y = f(x);
		if(y == 0)
			return x;
		if(y*fleft < 0)
			right = x;
		else {
			left = x;
			fleft = y;
		}
		(*N)++;
	}
	return x;
}

double chord(double (*f)(double), double left, double right, double eps, int* N){
	double fleft = f(left);
	double fright = f(right);
	double x, y;
	if(fleft*fright > 0){
		errno = ERRNO_APPROX_INTERVAL;
		return NAN;
	}
	if(eps <= 0){
		errno = ERRNO_APPROX_PRECISION;
		return NAN;
	}
	*N = 0;
	if(fleft == 0) return left;
	if(fright == 0) return right;
	do{
		x = left - (right - left) * fleft / (fright - fleft); //предполагаемый корень хорды
		y = f(x);
		if(y == 0)
			return x;
		if(y * fleft < 0){
			right = x;
			fright = y;
		}
		else{
			left = x;
			fleft = y;
		}
	(*N)++;
	} while(fabs(y) >= eps);
	return x;
}

double newton(double (*f)(double), double (*fd1)(double), double m1, double M2, double x, double eps, int* N, double* eps2_out){
	if(eps <= 0){
		errno = ERRNO_APPROX_PRECISION;
		return NAN;
	}
	double y, y1, dx, eps0;
	*N = 0;
	eps0 = sqrt(2 * m1 * eps / M2);
	do {
		y = f(x);
		if(y == 0)
			return x;
		y1 = fd1(x);
		if(y1 == 0){
			errno = ERRNO_APPROX_INVALID_DERIVATIVE;
			return NAN;
		}
	dx = y / y1;
	x -= dx;
	(*N)++;
	}
	while(fabs(dx) >= eps0);
	*eps2_out = eps0;
	return x;
}

double phi(double (*f)(double), double (*fd1)(double), double x, double left, double right, double delta){
	if(x == 0)
		return NAN;
	double _min = min_f(fd1, left, right, 0, delta_min);
	double _max = max_f(fd1, left, right, 0, delta_min);
	double s = x - 2 / (_min + _max) * f(x);
	s = _round(s, delta);
	return s;
}

double iter(double (*f)(double), double (*fd1)(double), double x0, double left, double right, double eps, double delta, int* N){
	if(eps <= 0){
		errno = ERRNO_APPROX_PRECISION;
		return NAN;
	}
	double x1 = phi(f, fd1, x0, left, right, delta);
	double x2 = phi(f, fd1, x1, left, right, delta);
	for(*N = 2; pow(x1 - x2, 2) > fabs((2*x1 - x0 - x2) * eps); ++(*N)){
		x0 = x1; x1 = x2;
		x2 = phi(f, fd1, x1, left, right, delta);
	}
	return x2;
}

double f(double x) { return (2* pow(x,2) - pow(x, 4) -1 - log(x));}

double fd1(double x) { return (4*x - 4*pow(x, 3) - (1/x));}

double fd2(double x) { return (4 - 12*pow(x,2) + (1/pow(x,2)));}

double f_cond(double x) { return 1 / fabs(fd1(x)); }

int main(){
	double left = 0.8, right = 1.2;
	double m1 = min_f(&fd1, left, right, 0, delta_min);
	double M1 = max_f(&fd1, left, right, 0, delta_min);
	double m2 = min_f(&fd2, left, right, 0, delta_min);
	double M2 = max_f(&fd2, left, right, 0, delta_min);
	printf("m1 = %lf, M1 = %lf, m2 = %lf, M2 = %lf\n", m1, M1, m2, M2);
	double alpha = 2 / (m1 + M1);
	
	puts("Метод Ньютона, Δ = 1e-6, 1e-6 <= ε <= 1e-1");
	puts("|left|right| ε| x0| ε2|итераций|");
	for(double delta = 1e-6, eps = 1e-6; eps <= 1e-1 + 1e-3; eps *= 10){
		int N; double eps2;
		double x0 = newton(&f, &fd1, m1, M2, right, eps, &N, &eps2);
		x0 = _round(x0, delta);
		printf("|%4g|%5g|%7g|%7g|%10g|%8d|\n", left, right, eps, x0, eps2, N);
	}

	puts("Метод Ньютона, ε = 1e-3, 1e-6 <= Δ <= 1e-1");
	puts("|left|right| Δ| x0| N| N max| итераций|");
	for(double delta = 1e-6, eps = 1e-3; delta <= 1e-2 + 1e-3; delta *= 10){
		int N; double eps2;
		double x0 = newton(&f, &fd1, m1, M2, right, eps, &N, &eps2);
		x0 = _round(x0, delta);
		double cond = f_cond(x0);
		double cond_max = eps/delta;
		printf("|%4g|%5g|%7g|%8g|%9g|%7g|%8d|\n", left, right, delta, x0, cond, cond_max, N);
	}

	puts("Метод простых итераций, Δ = 1e-6, 1e-6 <= ε <= 1e-1");
	puts("|left|right| ε| x0| phi'|итераций|");
	for(double delta = 1e-6, eps = 1e-6; eps <= 1e-1 + 1e-3; eps *= 10){
		int N;
		double x0 = iter(&f, &fd1, right, left, right, eps, delta, &N);
		x0 = _round(x0, delta);
		double dphi = 1 - alpha * fd1(x0);
		printf("|%4g|%5g|%7g|%8g|%11g|%8d|\n", left, right, eps, x0, dphi, N);
	}

	puts("Метод простых итераций, ε = 1e-3, 1e-6 <= Δ <= 1e-1");
	puts("|left|right| Δ| x0| N| N max| итераций|");
	for(double delta = 1e-6, eps = 1e-3; delta <= 1e-2 + 1e-3; delta *= 10){
		int N;
		double x0 = iter(&f, &fd1, right, left, right, eps, delta, &N);
		x0 = _round(x0, delta);
		double cond = f_cond(x0);
		double cond_max = eps/delta;
		printf("|%4g|%5g|%7g|%8g|%9g|%7g|%8d|\n", left, right, delta, x0, cond, cond_max, N);
	}

	puts("Метод простых итераций, Δ = 1e-6, ε = 1e-6, 0.8 <= left <= 0.9, 1.1 <= right <= 1.2");
	puts("|left | right| x0| min f'(x)|max f'(x)| q|");
	for(double delta = 1e-6, eps = 1e-6; right >= 1.1; right -= 0.01, left -= 0.01){
		int N;
		double x0 = iter(&f, &fd1, right, left, right, eps, delta, &N);
		x0 = _round(x0, delta);
		double dphi = 1 - alpha * fd1(x0);
		double m1 = min_f(&fd1, left, right, 0, delta_min);
		double M1 = max_f(&fd1, left, right, 0, delta_min);
		double q = (M1 - m1) / (M1 + m1);
		printf("|%5g|%6g|%9g|%9g|%9g|%9g|\n", left, right, x0, m1, M1, q);
	}
	left = 0.9; right = 1.4;

	puts("Сравнение методов:");
	printf("Метод бисекции, x0 = [%lf; %lf]\n", left, right);
	puts("|    ε|     x0|    итераций|");
	for(double delta = 1e-6, eps = 1e-6; eps <= 1e-1 + 1e-3; eps *= 10){
		int N;
		double x0 = bisect(&f, left, right, eps, &N);
		x0 = _round(x0, delta);
		printf("|%7g|%9g|%8d|\n", eps, x0, N);
	}

	printf("\nМетод хорд, x0 = [%lf; %lf]\n", left, right);
	puts("|    ε|     x0|    итераций|");
	for(double delta = 1e-6, eps = 1e-6; eps <= 1e-1 + 1e-3; eps *= 10){
		int N;
		double x0 = chord(&f, left, right, eps, &N);
		x0 = _round(x0, delta);
		printf("|%7g|%9g|%8d|\n", eps, x0, N);
	}

	printf("\nМетод Ньютона, x0 = %lf\n", right);
	puts("|    ε|     x0|    итераций|");
	for(double delta = 1e-6, eps = 1e-6; eps <= 1e-1 + 1e-3; eps *= 10){
		int N; double eps2;
		double x0 = newton(&f, &fd1, m1, M2,
		right, eps, &N, &eps2);
		x0 = _round(x0, delta);
		printf("|%7g|%9g|%8d|\n", eps, x0, N);
	}
	
	printf("\nМетод простых итераций, x0 = %lf\n", right);
	puts("|    ε|     x0|    итераций|");
	for(double delta = 1e-6, eps = 1e-6; eps <= 1e-1 + 1e-3; eps *= 10){
		int N;
		double x0 = iter(&f, &fd1, right, left, right, eps, delta, &N);
		x0 = _round(x0, delta);
		printf("|%7g|%9g|%8d|\n", eps, x0, N);
	}
}
