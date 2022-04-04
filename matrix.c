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
    printf("[----- [�忹����]  [2021041018] -----]\n");

    int row, col;
    srand(time(NULL));                                      // rand()�Լ��� seed�� time �Լ��� �̿�

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);
    int **matrix_a = create_matrix(row, col);               // matrix_a, matrix_b�� ����� ����, ���� ���꿡 �̿�ǹǷ� ���� ũ�⿩�� �Ѵ�.
    int **matrix_b = create_matrix(row, col);
    int **matrix_a_t = create_matrix(col, row);             // ��ġ ��� matrix_a_t�� matrix_a�� ��, ���� �ݴ�� �ؼ� �����Ǿ�� �Ѵ�.

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) {return -1;}  // matrix_a, matrix_b ����� ����� �������� �ʾҴٸ� ���� -1

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
        case 'z': /* ��� ���� ���� */
        case 'Z':
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            break;
        case 'p': /* ��� ��� */
        case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': /* ���� ũ���� �� ��� ���ϱ� */
        case 'A':
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': /* ���� ũ���� �� ��� ���� */
        case 'S':
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': /* ��� A�� ��ġ ��� ���ϱ� */
        case 'T':
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, col, row);
            break;
        case 'm': /* ��� A�� ��ġ ��� A_T�� ��İ� */
        case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': /* ��� ��� �޸� �Ҵ� ���� */
        case 'Q':
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default: /* ����� �� Ŀ�ǵ带 �Է����� �ʾ��� ��� ��� */
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int **create_matrix(int row, int col) {
    /* check pre conditions */
    if (row <= 0 || col <= 0) {                             // ��� ���� ����� �Էµ��� �ʾҴٸ� NULL�� ����
        printf("Check the sizes of row and col!\n");
        return NULL;
    }

    int** matrix = (int**)malloc(row * sizeof(int*));       // int* ũ��(64bit ���� 8����Ʈ) ������ �� ������ŭ matrix�� ���� �Ҵ�
    for (int i = 0; i < row; i++)
        matrix[i] = (int*)malloc(col * sizeof(int));        // int ũ��(4����Ʈ) ������ �� ������ŭ matrix�� ����Ű�� ������(�� ����) �Ҵ�

    /* check post conditions */
    if (matrix == NULL) {                                   // ����� ���� �Ҵ��� �����ߴٸ� NULL�� ����
        printf("Out of Memory!\n");
        return NULL;
    }

    return matrix;                                          // ���� �Ҵ� ������ ���� �Ҵ�� ���� ������ matrix�� �ּ� ����
}

/* print matrix whose size is row x col */
void print_matrix(int **matrix, int row, int col) {
    /* check pre conditions */
    if (matrix == NULL) {                                   // ����� ���� �Ҵ��� �������� ��� ���� �޽��� ��� �� ����
        printf("Matrix isn't created!\n");
        return;
    }

    for (int i = 0; i < row; i++) {                         // ������ ���ٸ� ����� �� ������ ���
        for (int j = 0; j < col; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}

/* free memory allocated by create_matrix() */
int free_matrix(int **matrix, int row, int col) {
    /* check pre conditions */
    if (matrix == NULL) {                                   // ����� ���� �Ҵ��� �������� ��� ���� �޽��� ��� �� ���� -1
        printf("Matrix isn't created!\n");
        return -1;
    }

    for (int i = 0; i < row; i++)                           // ���� �Ҵ�� ��� �޸� ����
        free(matrix[i]);
    free(matrix);

    return 1;
}

/* assign random values to the given matrix */
int fill_data(int **matrix, int row, int col) {
    /* check pre conditions */
    if (row <= 0 || col <= 0) {                             // ��� ���� ����� �Էµ��� �ʾҴٸ� ���� �޽��� ��� �� ���� -1
        printf("Check the sizes of row and col!\n");
        return -1;
    }

    for (int i = 0; i < row; i++) {                         // ��� �� ���п� 0~19 ���� �� �������� ����
        for (int j = 0; j < col; j++) {
            matrix[i][j] = rand() % 20;                     // ���� % 20�� ����� 0~19 ������ ����
        }
    }

    /* check post conditions */
    for (int i = 0; i < row; i++) {                         // 0~19 ������ ���� ����� ���ԵǾ����� Ȯ��
        for (int j = 0; j < col; j++) {
            if (matrix[i][j] > 19 || matrix[i][j] < 0) {
                printf("Wrong number filled!\n");           // ����� ���Ե��� �ʾҴٸ� ���� �޽��� ��� �� ���� -1
                return -1;
            }
        }
    }

    return 1;                                               // ������ ���ٸ� ���� 1
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int **matrix_a, int **matrix_b, int row, int col) {
    /* check pre conditions */
    for (int i = 0; i < row; i++) {                         // �� ��� ������ 0~19 ���� ���� �ƴ϶�� ���� �޽��� ��� �� ���� -1
        for (int j = 0; j < col; j++) {
            if(matrix_a[i][j] > 19 || matrix_b[i][j] > 19 || matrix_a[i][j] < 0 || matrix_b[i][j] < 0) {
                 printf("Wrong number filled!\n");
                 return -1;
             }
        }
    }

    int **matrix_sum = create_matrix(row, col);             // ���� ������ matrix_sum �����Ͽ� ��� a,b�� ���� ũ���� �޸� ���� �Ҵ�
    for (int i = 0; i < row; i++) {                         // ���� matrix_sum�� �� ������ ��� a,b�� ������ ���� ���� �� ����
        for (int j = 0; j < col; j++)
            matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];
    }

    /* check post conditions */
    for (int i = 0; i < row; i++) {                          // 0~38(19+19) ������ ���� ����� ���ԵǾ����� Ȯ��
        for (int j = 0; j < col; j++) {
            if (matrix_sum[i][j] > 38 || matrix_sum[i][j] < 0) {
                printf("Wrong number filled!\n");           // ����� ���Ե��� �ʾҴٸ� ���� �޽��� ��� �� ���� -1
                return -1;
            }
        }
    }

    print_matrix(matrix_sum, row, col);                     // matrix_sum ���
    free_matrix(matrix_sum, row, col);                      // matrix_sum�� ��� ���� ���� �� ������ �޸� �Ҵ� ����

    return 1;                                               // ������ ���ٸ� ���� 1
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int **matrix_a, int **matrix_b, int row, int col) {
    /* check pre conditions */
    for (int i = 0; i < row; i++) {                         // �� ��� ������ 0~19 ���� ���� �ƴ϶�� ���� �޽��� ��� �� ���� -1
        for (int j = 0; j < col; j++) {
            if (matrix_a[i][j] > 19 || matrix_b[i][j] > 19 || matrix_a[i][j] < 0 || matrix_b[i][j] < 0) {
                printf("Wrong number filled!\n");
                return -1;
            }
        }
    }

    int **matrix_sub = create_matrix(row, col);             // ���� ������ matrix_sub �����Ͽ� ��� a,b�� ���� ũ���� �޸� ���� �Ҵ�
    for (int i = 0; i < row; i++) {                         // ���� matrix_sub�� �� ������ ��� a,b�� ������ ���� �� �� ����
        for (int j = 0; j < col; j++)
            matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];
    }

    /* check post conditions */
    for (int i = 0; i < row; i++) {                         // -19(0-19)~19 ������ ���� ����� ���ԵǾ����� Ȯ��
        for (int j = 0; j < col; j++) {
            if (matrix_sub[i][j] > 19 || matrix_sub[i][j] < -19)
            {
                printf("Wrong number filled!\n");           // ����� ���Ե��� �ʾҴٸ� ���� �޽��� ��� �� ���� -1
                return -1;
            }
        }
    }

    print_matrix(matrix_sub, row, col);                     // matrix_sub ���
    free_matrix(matrix_sub, row, col);                      // ��� ���� ���� �� ������ �޸� �Ҵ� ����

    return 1;                                               // ������ ���ٸ� ���� 1
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col) {
    /* check pre conditions */
    for (int i = 0; i < col; i++) {                         // ��� ������ 0~19 ���� ���� �ƴ϶�� ���� �޽��� ��� �� ���� -1
        for (int j = 0; j < row; j++) {                     // �Լ��� ȣ������ �� ���ڸ� col, row ������ �־��� ������ �ڹٲپ �־�� �Ѵ�.
            if (matrix[i][j] > 19 || matrix[i][j] < 0) {
                printf("Wrong number filled!\n");
                return -1;
            }
        }
    }

    for (int i = 0; i < row; i++) {                         // ���� ����� ������ ��, ���� �ݴ�� �ؼ� ��ġ ��Ŀ� ����
        for (int j = 0; j < col; j++)
            matrix_t[i][j] = matrix[j][i];
    }

    /* check post conditions */
    for (int i = 0; i < row; i++) {                         // ��ġ ��Ŀ� 0~19 ������ ���� ����� ���ԵǾ����� Ȯ��
        for (int j = 0; j < col; j++) {
            if (matrix_t[i][j] > 19 || matrix_t[i][j] < 0) {
                printf("Wrong number filled!\n");           // ����� ���Ե��� �ʾҴٸ� ���� �޽��� ��� �� ���� -1
                return -1;
            }
        }
    }

    return 1;                                               // ������ ���ٸ� ���� 1
}

/* matrix_axt = matrix_a x matrix_t */
int multiply_matrix(int **matrix_a, int **matrix_t, int row, int col) {
    /* check pre conditions */
    for (int i = 0; i < row; i++) {                         // �� ��� ������ 0~19 ���� ���� �ƴ϶�� ���� �޽��� ��� �� ���� -1
        for (int j = 0; j < col; j++) {
            if (matrix_a[i][j] > 19 || matrix_t[i][j] > 19 || matrix_a[i][j] < 0 || matrix_t[i][j] < 0) {
                printf("Wrong number filled!\n");
                return -1;
            }
        }
    }

    int **matrix_axt = create_matrix(row, row);           // ��İ� ��Ģ�� ���� ���� ����� ��� ��ġ ��� ������ �޸� ���� �Ҵ��Ͽ� ��� ����

    for (int i = 0; i < row; i++)                         // matrix_axt ����� ������ �ִ� �κ�, ����� �ϼ����� ������.
    {
        for (int j = 0; j < col; j++) {
            for (int k = 0; k < row; k++)
                matrix_axt[i][k] = matrix_a[i][j] * matrix_t[j][i];
        }
    }
    /*
    for (int i = 0; i < row; i++) {                         // solution_hw4.c�� �����Ͽ� ����, ���� ����� solution_hw4.c ���� ����� ����.
        for (int j = 0; j < row; j++) {
            int temp = 0;
            for (int k = 0; k < col; k++)
                temp += matrix_a[i][k] * matrix_t[k][j];
            matrix_axt[i][j] = temp;
        }
    }
    */

    /* check post conditions */
    for (int i = 0; i < row; i++) {                         // �� ��� ������ 0~361(19*19) ���� ���� �ƴ϶�� ���� �޽��� ��� �� ���� -1
        for (int j = 0; j < col; j++) {
            if (matrix_axt[i][j] > 361 || matrix_axt[i][j] < 0)
            {
                printf("Wrong number filled!\n");
                return -1;
            }
        }
    }

    print_matrix(matrix_axt, row, col);                     // matrix_axt ���
    free_matrix(matrix_axt, row, col);                      // ��� ���� �̿���� �����Ƿ� �޸� �Ҵ� ����

    return 1;                                               // ������ ���ٸ� ���� 1
}
