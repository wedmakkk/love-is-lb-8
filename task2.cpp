#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <queue>
#include <chrono>
using namespace std;

struct node
{
    int peak;  // полезная информация
    struct node* next; // ссылка на следующий элемент 
};

struct node* head = NULL, * last = NULL, * f = NULL, * prev = NULL; // указатели на первый и последний элементы списка
int dlinna = 0;
void spstore(void), review(void), del(char* name);

char find_el[256];
struct node* find(char* name); // функция нахождения элемента

typedef struct Node 
{
    int dest; // Номер конечной вершины
    struct Node* next; // Указатель на следующую вершину в списке
} Node;

// Функция создания новой вершины
Node* create_node(int dest) 
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->dest = dest;
    new_node->next = NULL;
    return new_node;
}


Node** matrix_to_adj_list(int num_vertices, int** matrix) {
    Node** adj_list = (Node**)malloc(num_vertices * sizeof(Node*));
    if (adj_list == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }
    for (int i = 0; i < num_vertices; i++) {
        adj_list[i] = NULL; // Инициализация пустых списков
    }

    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            if (matrix[i][j] == 1) {
                Node* new_node = create_node(j);
                new_node->next = adj_list[i];
                adj_list[i] = new_node;
            }
        }
    }
    return adj_list;
}


// Функция для вывода списка смежности
void print_adj_list(int num_vertices, Node** adj_list) {
    for (int i = 0; i < num_vertices; i++) {
        printf("%d: ", i);
        Node* current = adj_list[i];
        while (current != NULL) {
            printf("%d -> ", current->dest);
            current = current->next;
        }
        printf("NULL\n");
    }
}

void review(void)
{
    struct node* struc = head;
    if (head == NULL)
    {
        printf("Список пуст\n");
    }
    while (struc)
    {
        printf("Имя - %s, \n", struc->peak);
        struc = struc->next;
    }
    return;
}


void spstore(int s)
{
    struct node* p = NULL;

	if ((p = (node*)malloc(sizeof(struct node))) == NULL)  // выделяем память под новый элемент списка
	{
		printf("Ошибка при распределении памяти\n");
		exit(1);
	}

    p->peak = s;
    p->next = NULL;
    
    if (head == NULL && p != NULL)	// если списка нет, то устанавливаем голову списка
    {
        head = p;
        last = p;
    }
    else if (head != NULL && p != NULL) // список уже есть, то вставляем в конец
    {
        last->next = p;
        last = p;
    }
    return;
}



void del(void)
{
    struct node* struc = head; // указатель, проходящий по списку установлен на начало списка
    struct node* prev = struc;// указатель на предшествующий удаляемому элемент

    if (head == NULL) // если голова списка равна NULL, то список пуст
    {
        printf("Список пуст\n");
        return;
    }
    head = struc->next; // установливаем голову на следующий элемент
    free(struc);  // удаляем первый элемент
    struc = head; // устанавливаем указатель для продолжения поиска
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
void print_list(int** adj_list, int n)
{
    printf("\n G1:\n");
    for (int i = 0; i < n; i++) 
    {
        printf("Peak %d: ", i);
        for (int j = 1; j <= adj_list[i][0]; j++) {
            printf("%d ", adj_list[i][j]);
        }
        printf("\n");
    }
}

void** BFS_list(int** G, int s, int size, int* vis)
{
    queue <int> q;
    q.push(s);
    vis[s] = 1;

    while (!q.empty())
    {
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

void** BFS_sp_list(int** G, int s, int size, int* vis)
{
    spstore(s);
    vis[s] = 1;

    while (head != NULL)
    {
        s = head->peak;
        printf("%d ", s);
        del();
        for (int i = 0; i < size; i++)
        {
            if (G[s][i] == 1 && vis[i] == 0)
            {
                spstore(i);
                vis[i] = 1;
            }
        }
    }
    return 0;
}

void matrix_to_adj_list(int num_vertices, int** matrix, Node** adj_list) 
{
    for (int i = 0; i < num_vertices; i++) {
        adj_list[i] = NULL;
    }

    for (int i = 0; i < num_vertices; i++) 
    {
        for (int j = 0; j < num_vertices; j++)
        {
            if (matrix[i][j] == 1) 
            {
                Node* new_node = create_node(j);
                new_node->next = adj_list[i];
                adj_list[i] = new_node;
            }
        }
    }
}

void print_matrix(int n, int** adjacency_matrix)
{
    printf("Matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) 
        {
            printf("%5d ", adjacency_matrix[i][j]);
        }
        printf("\n");
    }
}

void BFS_list(Node** adj_list, int s, int size, int* vis) {
    queue<int> q;
    q.push(s);
    vis[s] = 1;

    while (!q.empty()) {
        s = q.front();
        printf("%d ", s);
        q.pop();

        Node* current = adj_list[s];
        while (current != NULL) {
            if (vis[current->dest] == 0) {
                q.push(current->dest);
                vis[current->dest] = 1;
            }
            current = current->next;
        }
    }
}


// BFS_sp_list -  требует реализации spstore и del для работы со стеком
void BFS_sp_list(Node** adj_list, int s, int size, int* vis) {
    spstore(s);
    vis[s] = 1;

    while (head != NULL) {
        s = head->peak;
        printf("%d ", s);
        del();

        Node* current = adj_list[s];
        while (current != NULL) {
            if (vis[current->dest] == 0) {
                spstore(current->dest);
                vis[current->dest] = 1;
            }
            current = current->next;
        }
    }
}

void** BFS(int** G, int s, int size, int* vis)
{
    queue <int> q;
    q.push(s);
    vis[s] = 1;

    while (!q.empty()) 
    {
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

void** BFS_sp(int** G, int s, int size, int* vis)
{
    spstore(s);
    vis[s] = 1;

    while (head!=NULL) 
    {
        s = head->peak;
        printf("%d ", s);
        del();
        for (int i = 0; i < size; i++) 
        {
            if (G[s][i] == 1 && vis[i] == 0) 
            {
                spstore(i);
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
    int s = 0;

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
    adj_list = matrix_to_adj_list(n, matrix);
    print_adj_list(n, adj_list);
    auto start = chrono::high_resolution_clock::now();
    BFS(matrix,s, n, vis);
 
    for (int i = 0;i < n;i++)
    {
        vis[i] = 0;
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    printf("\nBFS time: %.3f ms\n", duration.count() / 1000.0f);
    printf("\n");
    start = chrono::high_resolution_clock::now();
    BFS_sp(matrix, s, n, vis);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start);
    printf("\nBFS_sp time: %.3f ms\n", duration.count() / 1000.0f);
    for (int i = 0;i < n;i++)
    {
        vis[i] = 0;
    }
    start = chrono::high_resolution_clock::now();
    BFS_list(matrix, s, n, vis);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start);
    printf("\nBFS_sp time: %.3f ms\n", duration.count() / 1000.0f);
    for (int i = 0;i < n;i++)
    {
        vis[i] = 0;
    }
    start = chrono::high_resolution_clock::now();
    BFS_sp_list(matrix, s, n, vis);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start);
    printf("\nBFS_sp time: %.3f ms\n", duration.count() / 1000.0f);
    getchar();
    getchar();
    getchar();
    return 0;
}
