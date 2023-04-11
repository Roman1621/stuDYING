#include <stdio.h>
#include <math.h>
#include <errno.h>
#define E ((double)2.71828)
#define ERRNO_APPROX_INTERVAL 1
#define ERRNO_APPROX_PRECISION 2
#define ERRNO_ROUND_PRECISION 2

double _round(double x, double delta){
	if(delta <= 1e-9){
	errno = ERRNO_ROUND_PRECISION;
	return NAN;
	}
	return delta * floor((x / delta) + (x > 0 ? 0.5 : -0.5));
}

double bisect(double (*f)(double),
double left, double right,
double eps, int* N){
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
		x = left - (right - left) * fleft / (fright - fleft); // предполагаемый корень хорды
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

double f(double x){
	return (cos(2*x))/(1+5*pow((x-0.1), 3));
}

double f_conditioning(double x){
	return ((-2*sin(2*x))/(1+5*pow((x-0.1), 3)) - (15*cos(2*x) * pow((x-0.1), 2))/(pow(1+5*pow((x-0.1), 3), 2)));
}

int main(){
	double left = 0.4, right = 1;

	printf("2. bisect, 0.000001 <= Δ <= 0.1, ε = 0.001, [%lg;%lg]\n", left, right);
	puts("ε\t\t\t|Δ\t\t\t|x0\t\t\t|NΔ\t\t\t|NΔmax\t\t\t|Обсуловленность задачи\t\t|Колво итераций");
	for(double eps = 0.001, delta = 0.00001; delta <= 0.1; delta *= 10){
		int N;
		double x0 = bisect(&f, left, right, eps, &N);
		x0 = _round(x0, delta);
		double cond = f_conditioning(x0);
		double cond_max = eps/delta;
		printf("%lf\t\t|%lf\t\t|%lf\t\t|%lf\t\t|%lf\t\t|%s\t\t\t|%d\n", eps, delta, x0, cond, cond_max, cond <= cond_max ? "Хорошая" : "Плохая ", N);
	}

	printf("\n3. bisect, 0.000001 <= ε <= 0.1, Δ = 0.0001, [%lg;%lg]\n", left, right);
	puts("ε\t\t\t|Δ\t\t\t|x0\t\t\t|NΔ\t\t\t|NΔmax\t\t\t|Обсуловленность задачи\t\t|Колво итераций");
	for(double eps = 0.000001, delta = 0.0001; eps <= 0.1; eps *= 10){
		int N;
		double x0 = bisect(&f, left, right, eps, &N);
		x0 = _round(x0, delta);
		double cond = f_conditioning(x0);
		double cond_max = eps/delta;
		printf("%lf\t\t|%lf\t\t|%lf\t\t|%lf\t\t|%lf\t\t|%s\t\t\t|%d\n", eps, delta, x0,
cond, cond_max, cond <= cond_max ? "Хорошая" : "Плохая ", N);
	}
	puts("\n3. График зависимости N от ε");
	int prev_N = -1;
	for(double eps = 0.000001, delta = 0.0001; eps <= 1.0; eps += 0.000001){
		int N;
		double x0 = bisect(&f, left, right, eps, &N);
		x0 = _round(x0, delta);
		double cond = f_conditioning(x0);
		double cond_max = eps/delta;
		if(N != prev_N)
			printf("(%lf;%d)\n", eps, N);
		prev_N = N;
		if(N == 0)
			break;
	}

	puts("\n4. bisect, ε = 0.001, Δ = 0.001, [m; n], 0 <= m <= 0.4, 1.0 <= n <= 1.4");
	puts("|left\t\t|right\t\t|ε\t\t\t|Δ\t\t\t|x0\t\t\t|NΔ\t\t\t|NΔmax\t\t\t|Обсуловленность задачи\t\t|Кол-во итераций");
	for(double eps = 0.000001, delta = 0.0001, left = 0.4, right = 1.0; left >= 0.01
&& right <= 1.39; left += 0.4 / 10, right += 0.4 / 10){
		int N;
		double x0 = bisect(&f, left, right, eps, &N);
		x0 = _round(x0, delta);
		double cond = f_conditioning(x0);
		double cond_max = eps/delta;
		printf("|%lf\t|%lf\t|%lf\t\t|%lf\t\t|%lf\t\t|%lf\t\t|%lf\t\t|%s\t\t\t|%d\n", left, right, eps, delta, x0, cond, cond_max, cond <= cond_max ? "Хорошая" : "Плохая ", N);
	}
	left = 0.4;
	right = 1;

	printf("5. chord, 0.000001 <= Δ <= 0.1, ε = 0.001, [%lg;%lg]\n", left, right);
	puts("ε\t\t\t|Δ\t\t\t|x0\t\t\t|NΔ\t\t\t|NΔmax\t\t\t|Обсуловленность задачи\t\t|Колво итераций");
	for(double eps = 0.001, delta = 0.00001; delta <= 0.1; delta *= 10){
		int N;
		double x0 = chord(&f, left, right, eps, &N);
		x0 = _round(x0, delta);
		double cond = f_conditioning(x0);
		double cond_max = eps/delta;
		printf("%lf\t\t|%lf\t\t|%lf\t\t|%lf\t\t|%lf\t\t|%s\t\t\t|%d\n", eps, delta, x0, cond, cond_max, cond <= cond_max ? "Хорошая" : "Плохая ", N);
	}
	
	printf("\n6. chord, 0.000001 <= ε <= 0.1, Δ = 0.001, [%lg;%lg]\n", left, right);
	puts("ε\t\t\t|Δ\t\t\t|x0\t\t\t|NΔ\t\t\t|NΔmax\t\t\t|Обсуловленность задачи\t\t|Колво итераций");
	for(double eps = 0.000001, delta = 0.0001; eps <= 0.1; eps *= 10){
		int N;	
		double x0 = chord(&f, left, right, eps, &N);
		x0 = _round(x0, delta);
		double cond = f_conditioning(x0);
		double cond_max = eps/delta;
		printf("%lf\t\t|%lf\t\t|%lf\t\t|%lf\t\t|%lf\t\t|%s\t\t\t|%d\n", eps, delta, x0, cond, cond_max, cond <= cond_max ? "Хорошая" : "Плохая ", N);
	}
	puts("\n6. График зависимости N от ε");
	prev_N = -1;
	for(double eps = 0.000001, delta = 0.0001; eps <= 1.0; eps += 0.000001){
		int N;
		double x0 = chord(&f, left, right, eps, &N);
		x0 = _round(x0, delta);
		double cond = f_conditioning(x0);
		double cond_max = eps/delta;
		if(N != prev_N)
			printf("(%lf;%d)\n", eps, N);
		prev_N = N;
		if(N == 0)
		break;
	}
	
	printf("\n7. bisect, ε = 0.001, Δ = 0.001, [%lg; -0.3], 0 <= m <= 0.4\n", left);
	puts("|left\t\t|right\t\t|ε\t\t\t|Δ\t\t\t|x0\t\t\t|NΔ\t\t\t|NΔmax\t\t\t|Обсуловленность задачи\t\t|Кол-во итераций");
	for(double eps = 0.000001, delta = 0.0001, left = 0; left <= 0.4; left += 0.05){
		int N;
		double x0 = chord(&f, left, right, eps, &N);
		x0 = _round(x0, delta);
		double cond = f_conditioning(x0);
		double cond_max = eps/delta;
		printf("|%lf\t|%lf\t|%lf\t\t|%lf\t\t|%lf\t\t|%lf\t\t|%lf\t\t|%s\t\t\t|%d\n", left, right, eps, delta, x0, cond, cond_max, cond <= cond_max ? "Хорошая" : "Плохая ", N);
	}
	left = 0.4;
	
	printf("\n8. bisect, 0.000001 <= ε <= 0.01, Δ = 0.001, [%lg;%lg]\n", left, right);
	puts("ε\t\t|Δ\t\t||bisect\t|x0\t\t|Кол-во итр.\t||chord\t|x0\t\t|Кол-во итр.\t");
	for(double eps = 0.000001, delta = 0.0001; eps <= 0.1; eps *= 10){
		int N;
		double x0 = bisect(&f, left, right, eps, &N);
		x0 = _round(x0, delta);
		double cond = f_conditioning(x0);
		double cond_max = eps/delta;
		printf("%lf\t|%lf\t\t\t|%lf\t|%d", eps, delta, x0, N);
		x0 = chord(&f, left, right, eps, &N);
		x0 = _round(x0, delta);
		printf("\t\t\t|%lf\t|%d\n", x0, N);
	}
}
