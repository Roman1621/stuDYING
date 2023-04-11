#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <limits.h>

//-------
// Вектор
//-------

typedef struct{
	double* data;
	size_t dim;
} vec;


void vec_copy(vec* dest, const vec* src)
{
	dest->dim = src->dim;
	dest->data = malloc(src->dim * sizeof(double));
	for(size_t i = 0; i < src->dim; ++i)
		dest->data[i] = src->data[i];
}

void vec_cleanup(vec* v)
{
	for(size_t i = 0; i < v->dim; ++i)
		if(v->data[i] == 0)
			v->data[i] = 0;
}


void vec_print(const vec* v)
{
	printf("[");
	for(size_t i = 0; i < v->dim; ++i)
		printf("%lg%s", v->data[i],
				i == v->dim - 1 ? "]\n" : " ");
}


static inline void vec_add_vec(vec* v1, vec* v2)
{
	for(size_t i = 0; i < v1->dim; ++i)
		v1->data[i] += v2->data[i];
}
static inline void vec_sub_vec(vec* v1, vec* v2)
{
	for(size_t i = 0; i < v1->dim; ++i)
		v1->data[i] -= v2->data[i];
}
static inline void vec_mul_double(vec* v1, double a)
{
	for(size_t i = 0; i < v1->dim; ++i)
		v1->data[i] *= a;
}
static inline void vec_div_double(vec* v1, double a)
{
	for(size_t i = 0; i < v1->dim; ++i)
		v1->data[i] /= a;
}

// вычисление нормы вектора
double vec_norm1(const vec* v)
{
	double norm = 0;
	for(size_t i = 0; i < v->dim; ++i)
		norm += fabs(v->data[i]);
	return norm;
}

//-------------------
// Квадратная матрица
//-------------------

typedef struct{
	double* data;
	size_t dim;
} sq_matrix;


void sq_matrix_copy(sq_matrix* dest, const sq_matrix* src)
{
	size_t elems = src->dim * src->dim;
	dest->data = malloc(elems * sizeof(double));
	for(size_t i = 0; i < elems; ++i)
		dest->data[i] = src->data[i];
	dest->dim = src->dim;
}

void sq_matrix_alloc_ident(sq_matrix* dest, size_t dim)
{
	dest->dim = dim;
	dest->data = malloc(dim * dim * sizeof(double));
	for(size_t i = 0; i < dim; ++i)
		for(size_t j = 0; j < dim; ++j)
			dest->data[i * dim + j] = (i == j) ? 1 : 0;
}

void sq_matrix_cleanup(sq_matrix* m)
{
	for(size_t i = 0; i < m->dim * m->dim; ++i)
		if(m->data[i] == 0)
			m->data[i] = 0;
}


static inline vec sq_matrix_get_row(sq_matrix* m, size_t row)
{
	return (vec){.data = m->data + row * m->dim, .dim = m->dim};
}


void sq_matrix_print(const sq_matrix* m)
{
	char sbuf[64];
	int* max_w = malloc(m->dim * sizeof(int));
	for(size_t i = 0; i < m->dim; ++i)
		max_w[i] = 0;

	for(size_t i = 0; i < m->dim; ++i)
	{
		for(size_t j = 0; j < m->dim; ++j){
			sprintf(sbuf, "%lg", m->data[i * m->dim + j]);
			int sym_count = (int)strlen(sbuf);
			if(sym_count > max_w[j])
				max_w[j] = sym_count;
		}
	}

	for(size_t i = 0; i < m->dim; ++i)
	{
		for(size_t j = 0; j < m->dim; ++j)
			printf("%*lg ", max_w[j], m->data[i * m->dim + j]);
		puts("");
	}

	free(max_w);
}


// умножение матрицы на вектор-столбец
vec sq_matrix_mul_vec(sq_matrix* m, vec* v)
{
	vec res;
	res.data = malloc(sizeof(double) * v->dim);
	res.dim = v->dim;
	for(size_t i = 0; i < m->dim; ++i){
		res.data[i] = 0;
		for(size_t j = 0; j < m->dim; ++j)
			res.data[i] += m->data[i * m->dim + j] * v->data[j];
	}
	return res;
}

static inline void sq_matrix_sub_sq_matrix(sq_matrix* m1, const sq_matrix* m2)
{
	for(size_t i = 0; i < m1->dim * m1->dim; ++i)
		m1->data[i] -= m2->data[i];
}


// вычисление нормы матрицы
double sq_matrix_norm1(const sq_matrix* m)
{
	double norm = -INFINITY;
	for(size_t j = 0; j < m->dim; ++j)
	{
		double sum = 0;
		for(size_t i = 0; i < m->dim; ++i)
			sum += m->data[i * m->dim + j];
		if(sum > norm)
			norm = sum;
	}
	return norm;
}


void sq_matrix_inverse(sq_matrix* m1, int free_m1)
{
	// Прямой ход (получаем верхнетреугольную матрицу с единицами на диагонали в m1)
	sq_matrix m2;
	sq_matrix_alloc_ident(&m2, m1->dim);

	for(size_t j = 0; j < m1->dim; ++j)
	{
		// делим текущий ряд на опорный (диагональный) элемент
		vec v1 = sq_matrix_get_row(m1, j);
		vec v2 = sq_matrix_get_row(&m2, j);
		double base = v1.data[j];
		vec_div_double(&v1, base);
		vec_div_double(&v2, base);

		// отнимаем текущий ряд от всех более нижних рядов
		for(size_t i = j+1; i < m1->dim; ++i)
		{
			vec v1i = sq_matrix_get_row(m1, i); // i - текущий ряд
			vec v2i = sq_matrix_get_row(&m2, i);

			// "Выбиваем" ноль в столбце j
			double base = v1i.data[j];
			vec_mul_double(&v1, base); vec_mul_double(&v2, base);
			vec_sub_vec(&v1i, &v1); vec_sub_vec(&v2i, &v2);
			vec_div_double(&v1, base); vec_div_double(&v2, base);
		}
	}

	// Обратный ход (превращаем верхнетреугольную матрицу в диагональную
	for(size_t _j = 0; _j < m1->dim; ++_j)
	{
		// начинаем с последнего ряда (в котором стоит одна единица в последнем столбце)
		size_t j = m1->dim - 1 - _j;

		vec v1 = sq_matrix_get_row(m1, j);
		vec v2 = sq_matrix_get_row(&m2, j);

		for(size_t _i = _j+1; _i < m1->dim; ++_i)
		{
			size_t i = m1->dim - 1 - _i;

			vec v1i = sq_matrix_get_row(m1, i);
			vec v2i = sq_matrix_get_row(&m2, i);

			double base = v1i.data[j];
			vec_mul_double(&v1, base); vec_mul_double(&v2, base);
			vec_sub_vec(&v1i, &v1); vec_sub_vec(&v2i, &v2);
			vec_div_double(&v1, base); vec_div_double(&v2, base);
		}
	}

	if(free_m1)
		free(m1->data);
	sq_matrix_cleanup(&m2);
	m1->data = m2.data;
}

//------------------
// Система уравнений
//------------------

typedef struct{
	sq_matrix A;
	vec B;
} eq_sys;

void eq_sys_print(const eq_sys* sys)
{
	char sbuf[64];
	int* max_w = malloc((sys->A.dim + 1) * sizeof(int));
	for(size_t i = 0; i < sys->A.dim + 1; ++i)
		max_w[i] = 0;

	for(size_t i = 0; i < sys->A.dim; ++i)
	{
		for(size_t j = 0; j < sys->A.dim; ++j){
			sprintf(sbuf, "%lg", sys->A.data[i * sys->A.dim + j]);
			int sym_count = (int)strlen(sbuf);
			if(sym_count > max_w[j])
				max_w[j] = sym_count;
		}
	}
	for(size_t i = 0; i < sys->A.dim; ++i){
		sprintf(sbuf, "%lg", sys->B.data[i]);
		int sym_count = (int)strlen(sbuf);
		if(sym_count > max_w[sys->A.dim])
			max_w[sys->A.dim] = sym_count;
	}

	for(size_t i = 0; i < sys->A.dim; ++i)
	{
		for(size_t j = 0; j < sys->A.dim; ++j)
			printf("%*lg ", max_w[j], sys->A.data[i * sys->A.dim + j]);
		printf("| %*lg\n", max_w[sys->A.dim], sys->B.data[i]);
	}

	free(max_w);
}


vec eq_sys_solve_gauss(eq_sys* sys)
{
	// Прямой ход (получаем верхнетреугольную матрицу с единицами на диагонали)
	sq_matrix A;
	sq_matrix_copy(&A, &sys->A);
	vec B;
	vec_copy(&B, &sys->B);

	for(size_t j = 0; j < A.dim; ++j)
	{
		// делим текущий ряд на опорный (диагональный) элемент
		vec v1 = sq_matrix_get_row(&A, j);
		B.data[j] /= v1.data[j]; vec_div_double(&v1, v1.data[j]);

		// отнимаем текущий ряд от всех более нижних рядов
		for(size_t i = j+1; i < A.dim; ++i)
		{
			vec v2 = sq_matrix_get_row(&A, i); // i - текущий ряд

			// "Выбиваем" ноль в столбце j
			double base = v2.data[j];
			vec_mul_double(&v1, base);
			vec_sub_vec(&v2, &v1); B.data[i] -= B.data[j] * base;
			vec_div_double(&v1, base);
		}
	}

	// Обратный ход (превращаем верхнетреугольную матрицу в диагональную
	for(size_t _j = 0; _j < A.dim; ++_j)
	{
		// начинаем с последнего ряда (в котором стоит одна единица в последнем столбце)
		size_t j = A.dim - 1 - _j;

		for(size_t _i = _j+1; _i < A.dim; ++_i)
		{
			size_t i = A.dim - 1 - _i;

			vec v2 = sq_matrix_get_row(&A, i);

			double base = v2.data[j];
			v2.data[j] = 0; // "отнимаем" текущий ряд
			B.data[i] -= B.data[j] * base;
		}
	}

	// очищаем выделенную память
	free(A.data);
	// выводим результат в вектор X
	vec X = (vec){.data = B.data, .dim = B.dim};
	vec_cleanup(&X);
	return X;
}

vec eq_sys_solve_inverse(eq_sys* sys)
{
	// находим A^{-1}
	sq_matrix inv_A;
	sq_matrix_copy(&inv_A, &sys->A);
	sq_matrix_inverse(&inv_A, 1);

	// умножаем A^{-1} на b, находя X
	vec X = sq_matrix_mul_vec(&inv_A, &sys->B);
	vec_cleanup(&X);
	free(inv_A.data);
	return X;
}


#define TCLR_RED_B "\033[1;31m"
#define TCLR_RESET "\033[0m"
#define TCLR_GREEN_B "\033[1;32m"

#define EXECUTE_TWICE(action, presecond)\
{ action; }\
{ presecond; }\
{ action; }

int main()
{
	static const size_t rand_seed = 1637509548;
	static const double rand_distr = 0.2; // погрешности генерируются в интервале [-rand_distr; rand_distr]
	srand(rand_seed);
	printf("Зерно ГСЧ: %lu\n\n", rand_seed);

	eq_sys esys;
	esys.A = (sq_matrix){.data = (double[]){6,  5, -8,
						 3, -1, -10,
						 -1,  2,  3},
		   .dim = 3};
	esys.B = (vec){.data = (double[]){-7, -24, 5}, .dim = 3};

	EXECUTE_TWICE(
	printf("%sЭталонная СЛУ%s\n", TCLR_RED_B, TCLR_RESET);
	{
		eq_sys_print(&esys);

		vec X1 = eq_sys_solve_gauss(&esys);
		vec X2 = eq_sys_solve_inverse(&esys);

		printf("Вектор решений метода Гаусса: X = "); vec_print(&X1);
		printf("Вектор решений метода обратной матрицы: X = "); vec_print(&X2);

		sq_matrix A_inv;
		sq_matrix_copy(&A_inv, &esys.A);
		sq_matrix_inverse(&A_inv, 1);

		double cond_A = sq_matrix_norm1(&A_inv) * sq_matrix_norm1(&esys.A);
		printf("\nСтандартное число обусловленности: cond(A) = %lg\n", cond_A);
		double abs_cond_A = sq_matrix_norm1(&A_inv);
		printf("Абсолютное число обусловленности: 𝛎_Δ = %lg\n", abs_cond_A);
		double nat_cond_A = sq_matrix_norm1(&A_inv) * vec_norm1(&esys.B) / vec_norm1(&X1);
		printf("Естественное число обсусловленности: 𝛎_δ = %lg\n", nat_cond_A);

		free(A_inv.data);
	}

	printf("\n%sAX = B*%s\n", TCLR_RED_B, TCLR_RESET);
	{
		eq_sys esys1;
		sq_matrix_copy(&esys1.A, &esys.A);
		vec_copy(&esys1.B, &esys.B);

		for(size_t i = 0; i < esys1.B.dim; ++i)
			esys1.B.data[i] += ((double)rand() / RAND_MAX) * rand_distr * 2 - rand_distr;

		eq_sys_print(&esys1);

		vec X = eq_sys_solve_gauss(&esys);
		vec X1 = eq_sys_solve_gauss(&esys1);
		vec X2 = eq_sys_solve_inverse(&esys1);

		printf("Вектор решений метода Гаусса: X = "); vec_print(&X1);
		printf("Вектор решений метода обратной матрицы: X = "); vec_print(&X2);

		sq_matrix A_inv;
		sq_matrix_copy(&A_inv, &esys1.A);
		sq_matrix_inverse(&A_inv, 1);

		double max_cond_A = sq_matrix_norm1(&A_inv) * sq_matrix_norm1(&esys1.A);
		printf("\nСтандартное число обусловленности: cond(A) = %lg\n", max_cond_A);
		double abs_cond_A = sq_matrix_norm1(&A_inv);
		printf("Абсолютное число обусловленности: 𝛎_Δ = %lg\n", abs_cond_A);
		double nat_cond_A = sq_matrix_norm1(&A_inv) * vec_norm1(&esys1.B) / vec_norm1(&X1);
		printf("Естественное число обсусловленности: 𝛎_δ = %lg\n", nat_cond_A);

		vec delta_X; vec_copy(&delta_X, &X1); vec_sub_vec(&delta_X, &X);
		vec delta_B; vec_copy(&delta_B, &esys1.B); vec_sub_vec(&delta_B, &esys.B);
		double cond_estimate_A = vec_norm1(&delta_X) / vec_norm1(&delta_B);
		printf("Оценка стандартного числа обусловленности: cond(A) >= δ(X*) / δ(B*) = %lg / %lg = %lg\n",
			vec_norm1(&delta_X), vec_norm1(&delta_B), cond_estimate_A);

		free(A_inv.data);
		free(delta_X.data);
		free(delta_B.data);
	}

	printf("\n%sA* X = B%s\n", TCLR_RED_B, TCLR_RESET);
	{
		eq_sys esys1;
		sq_matrix_copy(&esys1.A, &esys.A);
		vec_copy(&esys1.B, &esys.B);

		for(size_t i = 0; i < esys1.A.dim * esys.A.dim; ++i)
			esys1.A.data[i] += ((double)rand() / RAND_MAX) * rand_distr * 2 - rand_distr;

		eq_sys_print(&esys1);

		vec X = eq_sys_solve_gauss(&esys);
		vec X1 = eq_sys_solve_gauss(&esys1);
		vec X2 = eq_sys_solve_inverse(&esys1);

		printf("Вектор решений метода Гаусса: X = "); vec_print(&X1);
		printf("Вектор решений метода обратной матрицы: X = "); vec_print(&X2);

		sq_matrix A_inv;
		sq_matrix_copy(&A_inv, &esys1.A);
		sq_matrix_inverse(&A_inv, 1);

		double max_cond_A = sq_matrix_norm1(&A_inv) * sq_matrix_norm1(&esys1.A);
		printf("\nСтандартное число обусловленности: cond(A) = %lg\n", max_cond_A);
		double abs_cond_A = sq_matrix_norm1(&A_inv);
		printf("Абсолютное число обусловленности: 𝛎_Δ = %lg\n", abs_cond_A);
		double nat_cond_A = sq_matrix_norm1(&A_inv) * vec_norm1(&esys1.B) / vec_norm1(&X1);
		printf("Естественное число обсусловленности: 𝛎_δ = %lg\n", nat_cond_A);

		vec delta_X; vec_copy(&delta_X, &X1); vec_sub_vec(&delta_X, &X);
		sq_matrix delta_A; sq_matrix_copy(&delta_A, &esys1.A); sq_matrix_sub_sq_matrix(&delta_A, &esys.A);
		double cond_estimate_A = vec_norm1(&delta_X) / sq_matrix_norm1(&delta_A);
		printf("Оценка стандартного числа обусловленности: cond(A) >= δ(X*) / δ(A*) = %lg / %lg = %lg\n",
			vec_norm1(&delta_X), sq_matrix_norm1(&delta_A), cond_estimate_A);

		free(A_inv.data);
		free(delta_X.data);
		free(delta_A.data);
	}

	printf("\n%sA* X = B*%s\n", TCLR_RED_B, TCLR_RESET);
	{
		eq_sys esys1;
		sq_matrix_copy(&esys1.A, &esys.A);
		vec_copy(&esys1.B, &esys.B);

		for(size_t i = 0; i < esys1.A.dim * esys.A.dim; ++i)
			esys1.A.data[i] += ((double)rand() / RAND_MAX) * rand_distr * 2 - rand_distr;
		for(size_t i = 0; i < esys1.B.dim; ++i)
			esys1.B.data[i] += ((double)rand() / RAND_MAX) * rand_distr * 2 - rand_distr;

		eq_sys_print(&esys1);

		vec X = eq_sys_solve_gauss(&esys);
		vec X1 = eq_sys_solve_gauss(&esys1);
		vec X2 = eq_sys_solve_inverse(&esys1);

		printf("Вектор решений метода Гаусса: X = "); vec_print(&X1);
		printf("Вектор решений метода обратной матрицы: X = "); vec_print(&X2);

		sq_matrix A_inv;
		sq_matrix_copy(&A_inv, &esys1.A);
		sq_matrix_inverse(&A_inv, 1);

		double max_cond_A = sq_matrix_norm1(&A_inv) * sq_matrix_norm1(&esys1.A);
		printf("\nСтандартное число обусловленности: cond(A) = %lg\n", max_cond_A);
		double abs_cond_A = sq_matrix_norm1(&A_inv);
		printf("Абсолютное число обусловленности: 𝛎_Δ = %lg\n", abs_cond_A);
		double nat_cond_A = sq_matrix_norm1(&A_inv) * vec_norm1(&esys1.B) / vec_norm1(&X1);
		printf("Естественное число обсусловленности: 𝛎_δ = %lg\n", nat_cond_A);

		vec delta_X; vec_copy(&delta_X, &X1); vec_sub_vec(&delta_X, &X);
		sq_matrix delta_A; sq_matrix_copy(&delta_A, &esys1.A); sq_matrix_sub_sq_matrix(&delta_A, &esys.A);
		vec delta_B; vec_copy(&delta_B, &esys1.B); vec_sub_vec(&delta_B, &esys.B);
		double cond_estimate_A = vec_norm1(&delta_X) / (sq_matrix_norm1(&delta_A) + vec_norm1(&delta_B));
		printf("Оценка стандартного числа обусловленности: cond(A) >= δ(X*) / (δ(A*) + δ(B*)) = %lg / (%lg + %lg) = %lg\n",
			vec_norm1(&delta_X), sq_matrix_norm1(&delta_A), vec_norm1(&delta_B), cond_estimate_A);

		free(A_inv.data);
		free(delta_A.data);
		free(delta_B.data);
	}
	,

	printf("\n\n%sЗаменим 1 и 3 строки на строки Гильбертовой матрицы:%s\n\n", TCLR_GREEN_B, TCLR_RESET);
	size_t i = 0;
	vec v = sq_matrix_get_row(&esys.A, i);
	for(size_t j = 0; j < v.dim; ++j)
		v.data[j] = 1. / ((i+1) + (j+1) - 1.);
	i = 2;
	v = sq_matrix_get_row(&esys.A, i);
	for(size_t j = 0; j < v.dim; ++j)
		v.data[j] = 1. / ((i+1) + (j+1) - 1.);

	);
}
