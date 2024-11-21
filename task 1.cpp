#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <queue>
using namespace std;


typedef struct Node {
    int dest; // Номер конечной вершины
    struct Node* next; // Указатель на следующую вершину в списке
} Node;

// Функция создания новой вершины
Node* create_node(int dest) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->dest = dest;
    new_node->next = NULL;
    return new_node;
}


void generate_matrix(int n, float p, int** adjacency_matrix) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adjacency_matrix[i][j] = 0;
        }
    }


    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((float)rand() / RAND_MAX < p) {
                adjacency_matrix[i][j] = 1;
                adjacency_matrix[j][i] = 1;
            }
        }
    }

}

void print_matrix(int n, int** adjacency_matrix)
{
    printf("Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", adjacency_matrix[i][j]);
        }
        printf("\n");
    }
}

void matrix_to_adj_list(int num_vertices, int** matrix, Node** adj_list) {
    // Инициализация списка смежности
    for (int i = 0; i < num_vertices; i++) {
        adj_list[i] = NULL;
    }

    // Преобразование матрицы в список смежности
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            if (matrix[i][j] == 1) {
                // Добавление ребра из i в j
                Node* new_node = create_node(j);
                new_node->next = adj_list[i];
                adj_list[i] = new_node;
            }
        }
    }
}

void** BFS(int** G, int s, int size, int* vis)
{
    queue <int> q;
    q.push(s);
    vis[s] = 1;

    while (!q.empty()) {
        s = q.front();
        printf("%d ", s);
        q.pop();
        for (int i = 0; i < size; i++) {
            if (G[s][i] == 1 && vis[i] == 0) {
                q.push(i);
                vis[i] = 1;
            }
        }
    }
    return 0;
}


int main()
{
    int n;
    float p;


    srand(time(NULL));


    printf("Input count of peaks  : ");
    scanf("%d", &n);

    Node** adj_list = (Node**)malloc(n * sizeof(Node*));

    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0;i < n;i++)
    {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }
    printf("Enter the probability of having an edge (0.0 to 1.0):");
    scanf("%f", &p);
    if (p < 0.0 || p > 1.0) {
        printf("The probability should be in the range from 0.0 to 1.0.\n");

        return 1;
    }
    int* vis = (int*)malloc(n * sizeof(int*));
    for (int i = 0;i < n;i++)
    {
        vis[i] = 0;
    }
    generate_matrix(n, p, matrix);
    print_matrix(n, matrix);
    matrix_to_adj_list(n, matrix, adj_list);
    int s = 0;
    printf("\n");
    BFS(matrix, s, n, vis);
    
    getchar();
    getchar();
    getchar();
    return 0;
}