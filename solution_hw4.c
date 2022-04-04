#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col);										// 메모리 동적 할당하여 행렬 생성
void print_matrix(int** matrix, int row, int col);							// 행렬 출력
int free_matrix(int** matrix, int row, int col);							// 할당된 메모리 해제
int fill_data(int** matrix, int row, int col);								// 0~19 사이 값을 행렬 성분에 대입
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);		// 행렬의 덧셈 연산
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);	// 행렬의 뺄셈 연산
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);		// 전치 행렬 구하기
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);		// 행렬의 곱 연산

int main()
{
    char command;
    printf("[----- [장예서]  [2021041018] -----]\n");

	int row, col;
	srand(time(NULL));										// rand()함수의 seed로 time 함수를 이용

	printf("Input row and col : ");
	scanf("%d %d", &row, &col);
    int** matrix_a = create_matrix(row, col);				// matrix_a, matrix_b는 행렬의 덧셈, 뺄셈 연산에 이용되므로 같은 크기여야 한다.
	int** matrix_b = create_matrix(row, col);
    int** matrix_a_t = create_matrix(col, row);				// 전치 행렬 matrix_a_t는 matrix_a와 행, 열을 반대로 해서 생성되어야 한다.

	printf("Matrix Created.\n");

	if (matrix_a == NULL || matrix_b == NULL) {return -1;}	// matrix_a, matrix_b 행렬이 제대로 생성되지 않았다면 리턴 -1

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Matrix Manipulation                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Matrix   = z           Print Matrix        = p \n");
		printf(" Add Matrix          = a           Subtract Matrix     = s \n");
		printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
		printf(" Quit                = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		/* 행렬 숫자 대입 */
		case 'z': case 'Z':
		    printf("Matrix Initialized\n");
			fill_data(matrix_a, row, col);
			fill_data(matrix_b, row, col);
			break;
		/* 행렬 출력 */
        case 'p': case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
			print_matrix(matrix_a, row, col);
			printf("matrix_b\n");
			print_matrix(matrix_b, row, col);
			break;
		/* 크기가 같은 두 행렬의 합 */
        case 'a': case 'A':
			printf("Add two matrices\n");
			addition_matrix(matrix_a, matrix_b, row, col);
			break;
		/* 크기가 같은 두 행렬의 차 */
        case 's': case 'S':
			printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
			break;
		/* matrix_a의 전치 행렬 구하기 */
        case 't': case 'T':
			printf("Transpose matrix_a \n");
			printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, col, row);
			break;
		/* matrix_a와 전치 행렬 matrix_a_t의 행렬곱 */
        case 'm': case 'M':
			printf("Multiply matrix_a with transposed matrix_a \n");
			transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
			break;
		/* 행렬에 동적 할당된 메모리 해제 */
        case 'q': case 'Q':
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
			break;
		/* 제대로 된 커맨드를 입력하지 않았을 경우 경고 메시지 출력 */
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {								// 행과 열이 제대로 입력되지 않았다면 오류 메시지 출력 후 NULL을 리턴
		printf("Check the size of row and col!\n");
		return NULL;
	}

	int** matrix = (int**)malloc(sizeof(int*) * row);		// 이중 포인터 matrix에 포인터 크기 공간(64bit 기준 8바이트)을 행 개수만큼 동적 핟당
	for (int r = 0; r < row; r++) {
		matrix[r] = (int*)malloc(sizeof(int) * col);		// matrix가 가리키는 행마다 int 크기 공간(4바이트)을 열 개수만큼 동적 할당
	}

	/* Check post conditions */
	if (matrix == NULL) {									// 행렬의 동적 할당에 실패했다면 malloc()이 NULL 리턴
		printf("Memory Allocation Failed.\n");				// 실패가 확인되었다면 오류 메시지 출력 후 NULL을 리턴
		return NULL;
	}

	return matrix;											// 문제가 없다면 matrix(주소) 리턴
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {											// 행과 열이 제대로 입력되지 않았다면 오류 메시지 출력 후 리턴
		printf("Check the size of row and col!\n");
		return;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) {			// for문을 통해 행렬 성분을 출력
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			printf("%3d ", matrix[matrix_row][matrix_col]);
		printf("\n");
	}
	printf("\n");
	/* Check post conditions */
	 if (matrix == NULL) {												// 행렬의 동적 할당에 실패했을 경우 오류 메시지 출력 후 리턴
		printf("Memory Allocation Failed.\n");
		return;
	}


	return;
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {											// 행과 열이 제대로 입력되지 않았다면 오류 메시지 출력 후 리턴 -1
		printf("Check the size of row and col!\n");
		return -1;
	}

	for (int matrix_row = 0; matrix_row < row; matrix_row++) {			// matrix가 가리키는 행에 할당된 메모리 해제
		free(matrix[matrix_row]);
	}

	free(matrix);														// matrix에 할당된 메모리 해제
	return 1;															// 문제 없었다면 리턴 1
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {											// 행과 열이 제대로 입력되지 않았다면 오류 메시지 출력 후 리턴 -1
		printf("Check the size of row and col!\n");
		return -1;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++)			// for문을 통해 행렬의 성분에 0~19 사이 값을 대입
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix[matrix_row][matrix_col] = rand() % 20;				// 난수 % 20의 결과는 0~19 사이의 난수 
	/* Check post conditions */
    if (matrix == NULL) {												// 행렬의 동적 할당에 실패했을 경우 오류 메시지 출력 후 리턴 -1
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	return 1;															// 문제 없었다면 리턴 1
}

/* mmatrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sum = create_matrix(row, col);							// 두 행렬과 크기가 같은 행렬 matrix_sum을 생성(메모리 동적 할당)
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {											// 행과 열이 제대로 입력되지 않았다면 오류 메시지 출력 후 리턴 -1
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {			// for문을 통해 matrix_sum의 성분에 두 행렬 성분의 합을 대입
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_sum[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] + matrix_b[matrix_row][matrix_col];
	}
	/* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) {	// 각 행렬의 동적 할당이 실패했을 경우라면 오류 메시지 출력 후 리턴 -1
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	print_matrix(matrix_sum, row, col);
	free_matrix(matrix_sum, row, col);									// matrix_sum은 출력 후 이용될 일 없으므로 할당 해제
	return 1;															// 문제 없었다면 리턴 1
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sub = create_matrix(row, col);							// 두 행렬과 크기가 같은 행렬 matrix_sub 생성(메모리 동적 할당)
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {											// 행과 열이 제대로 입력되지 않았다면 오류 메시지 출력 후 리턴 -1
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {			// for문을 통해 matrix_sub의 성분에 두 행렬 성분의 차를 대입
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_sub[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] - matrix_b[matrix_row][matrix_col];
	}
	/* Check post conditions */
    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) {	// 각 행렬의 동적 할당이 실패했을 경우 오류 메시지 출력 후 리턴 -1
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	print_matrix(matrix_sub, row, col);
	free_matrix(matrix_sub, row, col);									// matrix_sub은 출력 후 이용될 일 없으므로 할당 해제

	return 1;															// 문제 없었다면 리턴 1
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {											// 행과 열이 제대로 입력되지 않았다면 오류 메시지 출력 후 리턴 -1
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {			// for문을 통해 matrix의 성분 값을 matrix_t의 행, 열이 반대되는 위치에 대입
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_t[matrix_row][matrix_col] = matrix[matrix_col][matrix_row];
	}
	/* Check post conditions */
    if (matrix == NULL || matrix_t ==NULL) {							// 각 행렬의 동적 할당이 실패했을 경우 오류 메시지 출력 후 리턴 -1
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	return 1;															// 문제가 없다면 리턴 1
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    int** matrix_axt = create_matrix(row, row);							// matrix_a의 행, matrix_a_t의 열을 가진 행렬 생성(메모리 동적 할당)
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {											// 행, 열이 제대로 입력되지 않았다면 오류 메시지 출력 후 리턴 -1
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_a_row = 0; matrix_a_row < row; matrix_a_row++) {	// matrix_axt는 rowXrow 크기 행렬이므로 row의 중첩 for문에만 해당하도록 한다.
		for (int matrix_t_row = 0; matrix_t_row < row; matrix_t_row++) {
			int temp = 0;
			for (int matrix_col = 0; matrix_col < col; matrix_col++) 	// for문을 통해 matrix_a와 matrix_a_t의 각 성분의 곱을 temp에 대입
				temp += matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row];
			matrix_axt[matrix_a_row][matrix_t_row] = temp; 				// 이후 temp의 값을 matrix_axt에 대입
		}
	}
	/* Check post conditions */
    if (matrix_t == NULL || matrix_axt == NULL) {						// 각 성분의 동적 할당이 실패했을 경우 오류 메시지 출력 후 리턴 -1
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	print_matrix(matrix_axt, row, row);
	free_matrix(matrix_axt, row, col);									// matrix_axt는 출력 이후 이용될 일 없으므로 메모리 할당 해제
	return 1;															// 문제가 없다면 리턴 1
}


