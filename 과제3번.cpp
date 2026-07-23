#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 노드 구조체 정의
typedef struct _Node {
    int data;               // 저장할 정수 데이터
    struct _Node* next;     // 다음 노드를 가리키는 포인터
} Node;

// 큐 구조체 정의
typedef struct Queue {
    Node* front;            // 맨 앞(출구) 노드를 가리키는 포인터
    Node* rear;             // 맨 뒤(입구) 노드를 가리키는 포인터
    int size;               // 현재 큐 내의 데이터 개수
} Queue;

// 큐 초기화 함수
void initQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

// isEmpty: 큐가 비어있는지 확인
bool isEmpty(Queue* q) {
    return q->size == 0;    // size가 0이면 비어있는 상태
}

// Enqueue: 큐의 맨 뒤에 데이터 추가
void enqueue(Queue* q, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return;

    newNode->data = data;
    newNode->next = NULL;

    if (isEmpty(q)) {
        // 큐가 비어있다면 front와 rear 모두 새 노드를 가리킴
        q->front = newNode;
        q->rear = newNode;
    }
    else {
        // 기존 rear 노드의 next에 새 노드를 연결하고 rear 이동
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
}

// Dequeue: 맨 앞의 데이터를 꺼내고 출력 (비어있으면 예외 처리)
void dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue가 비어있습니다.\n");
        return;
    }

    // 1. 제거할 front 노드를 임시 포인터에 저장
    Node* temp = q->front;
    int dequeuedData = temp->data;

    // 2. front 포인터를 다음 노드로 이동
    q->front = q->front->next;

    // 3. 만약 마지막 노드를 꺼내서 front가 NULL이 되었다면 rear도 NULL 처리
    if (q->front == NULL) {
        q->rear = NULL;
    }

    // 4. 동적 메모리 해제 및 크기 감소
    free(temp);
    q->size--;

    printf("Dequeue된 값: %d\n", dequeuedData);
}

// size: 큐의 크기 출력
void printQueueSize(Queue* q) {
    printf("Queue 크기: %d\n", q->size);
}

// front: 맨 앞 데이터 반환
int front(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue가 비어있습니다.\n");
        return -1;
    }
    return q->front->data;
}

// rear: 맨 뒤 데이터 반환
int rear(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue가 비어있습니다.\n");
        return -1;
    }
    return q->rear->data;
}

// printQueue: 큐의 모든 데이터 출력 (front부터 rear 순으로)
void printQueue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue가 비어있습니다.\n");
        return;
    }

    Node* curr = q->front;
    printf("Queue [Front -> Rear]: ");
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}