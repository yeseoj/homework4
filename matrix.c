#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int **create_matrix(int row, int col);
void print_matrix(int **matrix, int row, int col);
int free_matrix(int **matrix, int row, int col);
int fill_data(int **matrix, int row, int col);
int addition_matrix(int **matrix_a, int **matrix_b, int row, int col);
int subtraction_matrix(int **matrix_a, int **matrix_b, int row, int col);
int transpose_matrix(int **matrix, int **matrix_t, int row, int col);
int multiply_matrix(int **matrix_a, int **matrix_t, int row, int col);

int main()
{

    char command;
    printf("[----- [장예서­]  [2021041018] -----]\n");

    int row, col;
    srand(time(NULL));                                      // rand()함수의 seed로 time 함수를 이용

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);
    int **matrix_a = create_matrix(row, col);               // matrix_a, matrix_b는 행렬의 덧셈, 뺄셈 연산에 이용되므로 같은 크기여야 한다.
    int **matrix_b = create_matrix(row, col);
    int **matrix_a_t = create_matrix(col, row);             // 전치 행렬 matrix_a_t는 matrix_a와 행, 열을 반대로 해서 생성되어야 한다.

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) {return -1;}  // matrix_a, matrix_b 행렬이 제대로 생성되지 않았다면 리턴 -1

    do
    {
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

        switch (command)
        {
        case 'z': /* 행렬 숫자 대입 */
        case 'Z':
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            break;
        case 'p': /* 행렬 출력 */
        case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': /* 같은 크기의 두 행렬 더하기 */
        case 'A':
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': /* 같은 크기의 두 헹렬 빼기 */
        case 'S':
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': /* 행렬 A의 전치 행렬 구하기 */
        case 'T':
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, col, row);
            break;
        case 'm': /* 행렬 A와 전치 행렬 A_T의 행렬곱 */
        case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': /* 모든 행렬 메모리 할당 해제 */
        case 'Q':
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default: /* 제대로 된 커맨드를 입력하지 않았을 경우 경고 */
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int **create_matrix(int row, int col) {
    /* check pre conditions */
    if (row <= 0 || col <= 0) {                             // 행과 열이 제대로 입력되지 않았다면 NULL을 리턴
        printf("Check the sizes of row and col!\n");
        return NULL;
    }

    int** matrix = (int**)malloc(row * sizeof(int*));       // int* 크기(64bit 기준 8바이트) 공간을 행 개수만큼 matrix에 동적 할당
    for (int i = 0; i < row; i++)
        matrix[i] = (int*)malloc(col * sizeof(int));        // int 크기(4바이트) 공간을 열 개수만큼 matrix가 가리키는 곳마다(행 개수) 할당

    /* check post conditions */
    if (matrix == NULL) {                                   // 행렬의 동적 할당이 실패했다면 NULL을 리턴
        printf("Out of Memory!\n");
        return NULL;
    }

    return matrix;                                          // 동적 할당 성공시 동적 할당된 이중 포인터 matrix의 주소 리턴
}

/* print matrix whose size is row x col */
void print_matrix(int **matrix, int row, int col) {
    /* check pre conditions */
    if (matrix == NULL) {                                   // 행렬의 동적 할당이 실패했을 경우 오류 메시지 출력 후 리턴
        printf("Matrix isn't created!\n");
        return;
    }

    for (int i = 0; i < row; i++) {                         // 문제가 없다면 행렬의 각 성분을 출력
        for (int j = 0; j < col; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}

/* free memory allocated by create_matrix() */
int free_matrix(int **matrix, int row, int col) {
    /* check pre conditions */
    if (matrix == NULL) {                                   // 행렬의 동적 할당이 실패했을 경우 오류 메시지 출력 후 리턴 -1
        printf("Matrix isn't created!\n");
        return -1;
    }

    for (int i = 0; i < row; i++)                           // 동적 할당된 행렬 메모리 해제
        free(matrix[i]);
    free(matrix);

    return 1;
}

/* assign random values to the given matrix */
int fill_data(int **matrix, int row, int col) {
    /* check pre conditions */
    if (row <= 0 || col <= 0) {                             // 행과 열이 제대로 입력되지 않았다면 오류 메시지 출력 후 리턴 -1
        printf("Check the sizes of row and col!\n");
        return -1;
    }

    for (int i = 0; i < row; i++) {                         // 행렬 각 성분에 0~19 사이 값 무작위로 대입
        for (int j = 0; j < col; j++) {
            matrix[i][j] = rand() % 20;                     // 난수 % 20의 결과는 0~19 사이의 난수
        }
    }

    /* check post conditions */
    for (int i = 0; i < row; i++) {                         // 0~19 사이의 값이 제대로 대입되었는지 확인
        for (int j = 0; j < col; j++) {
            if (matrix[i][j] > 19 || matrix[i][j] < 0) {
                printf("Wrong number filled!\n");           // 제대로 대입되지 않았다면 오류 메시지 출력 후 리턴 -1
                return -1;
            }
        }
    }

    return 1;                                               // 문제가 없다면 리턴 1
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int **matrix_a, int **matrix_b, int row, int col) {
    /* check pre conditions */
    for (int i = 0; i < row; i++) {                         // 각 행렬 성분이 0~19 사이 값이 아니라면 오류 메시지 출력 후 리턴 -1
        for (int j = 0; j < col; j++) {
            if(matrix_a[i][j] > 19 || matrix_b[i][j] > 19 || matrix_a[i][j] < 0 || matrix_b[i][j] < 0) {
                 printf("Wrong number filled!\n");
                 return -1;
             }
        }
    }

    int **matrix_sum = create_matrix(row, col);             // 이중 포인터 matrix_sum 선언하여 행렬 a,b와 같은 크기의 메모리 동적 할당
    for (int i = 0; i < row; i++) {                         // 이후 matrix_sum의 각 성분은 행렬 a,b의 성분을 각각 더한 값 대입
        for (int j = 0; j < col; j++)
            matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];
    }

    /* check post conditions */
    for (int i = 0; i < row; i++) {                          // 0~38(19+19) 사이의 값이 제대로 대입되었는지 확인
        for (int j = 0; j < col; j++) {
            if (matrix_sum[i][j] > 38 || matrix_sum[i][j] < 0) {
                printf("Wrong number filled!\n");           // 제대로 대입되지 않았다면 오류 메시지 출력 후 리턴 -1
                return -1;
            }
        }
    }

    print_matrix(matrix_sum, row, col);                     // matrix_sum 출력
    free_matrix(matrix_sum, row, col);                      // matrix_sum은 출력 이후 사용될 일 없으니 메모리 할당 해제

    return 1;                                               // 문제가 없다면 리턴 1
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int **matrix_a, int **matrix_b, int row, int col) {
    /* check pre conditions */
    for (int i = 0; i < row; i++) {                         // 각 행렬 성분이 0~19 사이 값이 아니라면 오류 메시지 출력 후 리턴 -1
        for (int j = 0; j < col; j++) {
            if (matrix_a[i][j] > 19 || matrix_b[i][j] > 19 || matrix_a[i][j] < 0 || matrix_b[i][j] < 0) {
                printf("Wrong number filled!\n");
                return -1;
            }
        }
    }

    int **matrix_sub = create_matrix(row, col);             // 이중 포인터 matrix_sub 선언하여 행렬 a,b와 같은 크기의 메모리 동적 할당
    for (int i = 0; i < row; i++) {                         // 이후 matrix_sub의 각 성분은 행렬 a,b의 성분을 각각 뺀 값 대입
        for (int j = 0; j < col; j++)
            matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];
    }

    /* check post conditions */
    for (int i = 0; i < row; i++) {                         // -19(0-19)~19 사이의 값이 제대로 대입되었는지 확인
        for (int j = 0; j < col; j++) {
            if (matrix_sub[i][j] > 19 || matrix_sub[i][j] < -19)
            {
                printf("Wrong number filled!\n");           // 제대로 대입되지 않았다면 오류 메시지 출력 후 리턴 -1
                return -1;
            }
        }
    }

    print_matrix(matrix_sub, row, col);                     // matrix_sub 출력
    free_matrix(matrix_sub, row, col);                      // 출력 이후 사용될 일 없으니 메모리 할당 해제

    return 1;                                               // 문제가 없다면 리턴 1
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col) {
    /* check pre conditions */
    for (int i = 0; i < col; i++) {                         // 행렬 성분이 0~19 사이 값이 아니라면 오류 메시지 출력 후 리턴 -1
        for (int j = 0; j < row; j++) {                     // 함수를 호출했을 때 인자를 col, row 순으로 넣었기 때문에 뒤바꾸어서 넣어야 한다.
            if (matrix[i][j] > 19 || matrix[i][j] < 0) {
                printf("Wrong number filled!\n");
                return -1;
            }
        }
    }

    for (int i = 0; i < row; i++) {                         // 원래 행렬의 성분을 행, 열을 반대로 해서 전치 행렬에 대입
        for (int j = 0; j < col; j++)
            matrix_t[i][j] = matrix[j][i];
    }

    /* check post conditions */
    for (int i = 0; i < row; i++) {                         // 전치 행렬에 0~19 사이의 값이 제대로 대입되었는지 확인
        for (int j = 0; j < col; j++) {
            if (matrix_t[i][j] > 19 || matrix_t[i][j] < 0) {
                printf("Wrong number filled!\n");           // 제대로 대입되지 않았다면 오류 메시지 출력 후 리턴 -1
                return -1;
            }
        }
    }

    return 1;                                               // 문제가 없다면 리턴 1
}

/* matrix_axt = matrix_a x matrix_t */
int multiply_matrix(int **matrix_a, int **matrix_t, int row, int col) {
    /* check pre conditions */
    for (int i = 0; i < row; i++) {                         // 각 행렬 성분이 0~19 사이 값이 아니라면 오류 메시지 출력 후 리턴 -1
        for (int j = 0; j < col; j++) {
            if (matrix_a[i][j] > 19 || matrix_t[i][j] > 19 || matrix_a[i][j] < 0 || matrix_t[i][j] < 0) {
                printf("Wrong number filled!\n");
                return -1;
            }
        }
    }

    int **matrix_axt = create_matrix(row, row);           // 행렬곱 규칙에 따라 원래 행렬의 행과 전치 행렬 열으로 메모리 동적 할당하여 행렬 생성

    for (int i = 0; i < row; i++)                         // matrix_axt 행렬의 성분을 넣는 부분, 제대로 완성하지 못했음.
    {
        for (int j = 0; j < col; j++) {
            for (int k = 0; k < row; k++)
                matrix_axt[i][k] = matrix_a[i][j] * matrix_t[j][i];
        }
    }
    /*
    for (int i = 0; i < row; i++) {                         // solution_hw4.c를 참고하여 수정, 실행 결과는 solution_hw4.c 실행 결과와 같다.
        for (int j = 0; j < row; j++) {
            int temp = 0;
            for (int k = 0; k < col; k++)
                temp += matrix_a[i][k] * matrix_t[k][j];
            matrix_axt[i][j] = temp;
        }
    }
    */

    /* check post conditions */
    for (int i = 0; i < row; i++) {                         // 각 행렬 성분이 0~361(19*19) 사이 값이 아니라면 오류 메시지 출력 후 리턴 -1
        for (int j = 0; j < col; j++) {
            if (matrix_axt[i][j] > 361 || matrix_axt[i][j] < 0)
            {
                printf("Wrong number filled!\n");
                return -1;
            }
        }
    }

    print_matrix(matrix_axt, row, col);                     // matrix_axt 출력
    free_matrix(matrix_axt, row, col);                      // 출력 이후 이용되지 않으므로 메모리 할당 해제

    return 1;                                               // 문제가 없다면 리턴 1
}
