#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 노드 구조체 정의
typedef struct _Node {
    int data;               // 저장할 정수 데이터
    struct _Node* next;     // 다음 노드를 가리키는 포인터
} Node;

// 스택 구조체 정의
typedef struct Stack {
    Node* top;              // 스택의 가장 위(최신) 노드를 가리키는 포인터
    int size;               // 현재 스택 내의 데이터 개수
} Stack;

// 스택 초기화 함수
void initStack(Stack* s) {
    s->top = NULL;
    s->size = 0;
}

// isEmpty: 스택이 비어있는지 확인 (비어있으면 true, 아니면 false)
bool isEmpty(Stack* s) {
    return s->top == NULL;  // top이 NULL이면 비어있는 상태
}

// push: 스택의 최상단에 데이터 추가
void push(Stack* s, int data) {
    // 1. 새 노드 동적 할당
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("메모리 할당 실패\n");
        return;
    }

    newNode->data = data;
    // 2. 새 노드가 기존의 top 노드를 가리키도록 설정
    newNode->next = s->top;
    // 3. 스택의 top 포인터를 새 노드로 업데이트
    s->top = newNode;
    // 4. 스택 크기 증가
    s->size++;
}

// pop: 최상단 데이터를 꺼내고 출력 (스택이 비어있으면 예외 처리)
void pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack이 비어있습니다.\n");
        return;
    }

    // 1. 제거할 top 노드를 임시 포인터에 저장
    Node* temp = s->top;
    int poppedData = temp->data;

    // 2. top 포인터를 다음 노드로 이동
    s->top = s->top->next;

    // 3. 임시 포인터 메모리 해제 및 크기 감소
    free(temp);
    s->size--;

    printf("Pop된 값: %d\n", poppedData);
}

// size: 현재 스택의 크기 출력
void printSize(Stack* s) {
    printf("Stack 크기: %d\n", s->size);
}

// top: 최상단 노드의 값 반환 (비어있으면 -1 반환)
int top(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack이 비어있습니다.\n");
        return -1;
    }
    return s->top->data;
}

// printStack: 스택의 모든 데이터 출력 (top부터 순서대로)
void printStack(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack이 비어있습니다.\n");
        return;
    }

    Node* curr = s->top;
    printf("Stack [Top -> Bottom]: ");
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;  // 다음 노드로 이동
    }
    printf("\n");
}