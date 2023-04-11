#include <stdio.h>
#include <math.h>
#include <errno.h>

#define ERRNO_BISECT_INTERVAL 1
#define ERRNO_BISECT_PRECISION 2

#define ERRNO_ROUND_PRECISION 2

double bisect(double (*f)(double),
double left, double right,
double eps, int* N){
	double e = fabs(eps) * 2;
	double fleft = f(left);
	double fright = f(right);
	double x = (left + right) / 2, y;

	if(fleft*fright > 0){
		errno = ERRNO_BISECT_INTERVAL;
		return NAN;
	}
	if(eps <= 0){
		errno = ERRNO_BISECT_PRECISION;
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

double _round(double x, double delta){
	if(delta <= 1e-9){
		errno = ERRNO_ROUND_PRECISION;
		return NAN;
	}
	return delta * floor((x / delta) + (x > 0 ? 0.5 : -0.5));
}


#define d 19

double f_c;
double f(double x){
	return f_c*(x - d);
}

double f_conditioning(){
	return 1 / fabs(f_c);
}

int main(){
	int N;

	puts("1. Параметр с варьируется от 0.01 до 1000. Параметры eps и delta постоянны и равны значению 0.01.\n");
	puts("c\t\t\teps\t\t\tdelta\t\t\tx0\t\t\tNΔ\t\t\tNΔ max");
	for(f_c = 0.01; f_c <= 1000; f_c *= 10){
		double x0 = bisect(&f, d - 2, d + 2, 0.01, &N);
		x0 = _round(x0, 0.01);
		double cond = f_conditioning();
		printf("%lf\t\t%lf\t\t%lf\t\t%lf\t\t%lf\t\t%lf\n", f_c, 0.01, 0.01, x0, cond, 0.01/0.01);
	}

	puts("\n2. Параметр с постоянен и равен 1, eps постоянен и равен 0.01, delta варьируется от 0.00001 до 0.1.\n");
	puts("c\t\t\teps\t\t\tdelta\t\t\tx0\t\t\tNΔ\t\t\tNΔ max");
	f_c = 1;
	for(double delta = 0.00001; delta <= 0.1; delta *= 10){
		double x0 = bisect(&f, d - 2, d + 2, 0.01, &N);
		x0 = _round(x0, delta);
		double cond = f_conditioning();
		printf("%lf\t\t%lf\t\t%lf\t\t%lf\t\t%lf\t\t%lf\n", f_c, 0.01, delta, x0, cond, 0.01/delta);
	}

	puts("\n3. Параметр с постоянен и равен 10, delta постоянна и равна 0.01, eps варьируется от 0.000001 до 10.\n");
	puts("c\t\t\teps\t\t\tdelta\t\t\tx0\t\t\tNΔ\t\t\tNΔ max");
	f_c = 10;
	for(double eps = 0.00001; eps <= 10; eps *= 10){
		double x0 = bisect(&f, d - 2, d + 2, eps, &N);
		x0 = _round(x0, 0.01);
		double cond = f_conditioning();
		printf("%lf\t\t%lf\t\t%lf\t\t%lf\t\t%lf\t\t%lf\n", f_c, eps, 0.01, x0, cond, eps/0.01);
	}
	
	puts("\n4. Параметр с постоянен и равен 10, delta и eps одновременно варьируются от 0.000001 до 1.\n");
    	puts("c\t\t\teps\t\t\tdelta\t\t\tx0\t\t\tNΔ\t\t\tNΔ max\t\t\tN");
    	f_c = 10;
    	for(double delta = 0.00001, eps = 0.00001; delta <= 1; delta *= 10, eps *= 10){
		double x0 = bisect(&f, d - 2, d + 4, eps, &N);
		x0 = _round(x0, delta);
		double cond = f_conditioning();
		printf("(%lf;%d)\n", eps, N);
	}

	puts("\n5. Параметр eps постоянен и равен 0.01, c и delta варьируются независимым друг от друга образом.\n");
	puts("c\t\t\teps\t\t\tdelta\t\t\tx0\t\t\tNΔ\t\t\tNΔ max");
	f_c = 0.01;
	for(f_c = 0.01; f_c <= 1000; f_c *= 10)
		for(double delta = 0.00001; delta <= 0.1; delta *= 10){
			double x0 = bisect(&f, d - 2, d + 2, 0.01, &N);
			x0 = _round(x0, delta);
			double cond = f_conditioning();
			printf("%lf\t\t%lf\t\t%lf\t\t%lf\t\t%lf\t\t%lf\n", f_c, 0.01, delta, x0, cond, 0.01/delta);
		}
}

