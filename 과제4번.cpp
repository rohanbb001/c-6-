#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// 문자형 전용 연결 리스트 노드
typedef struct CharNode {
    char data;
    struct CharNode* next;
} CharNode;

// 문자형 전용 스택
typedef struct {
    CharNode* top;
} CharStack;

// 문자형 전용 큐
typedef struct {
    CharNode* front;
    CharNode* rear;
} CharQueue;

// 스택/큐 초기화 및 유틸리티 함수
void initCharStack(CharStack* s) { s->top = NULL; }
void initCharQueue(CharQueue* q) { q->front = q->rear = NULL; }

void pushChar(CharStack* s, char ch) {
    CharNode* newNode = (CharNode*)malloc(sizeof(CharNode));
    newNode->data = ch;
    newNode->next = s->top;
    s->top = newNode;
}

char popChar(CharStack* s) {
    if (s->top == NULL) return '\0';
    CharNode* temp = s->top;
    char ch = temp->data;
    s->top = s->top->next;
    free(temp);
    return ch;
}

void enqueueChar(CharQueue* q, char ch) {
    CharNode* newNode = (CharNode*)malloc(sizeof(CharNode));
    newNode->data = ch;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    }
    else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

char dequeueChar(CharQueue* q) {
    if (q->front == NULL) return '\0';
    CharNode* temp = q->front;
    char ch = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return ch;
}

// 회문 판별 함수
bool isPalindrome(const char* str) {
    CharStack s;
    CharQueue q;
    initCharStack(&s);
    initCharQueue(&q);

    // 1. 문자열을 순회하며 알파벳/숫자만 소문자로 변환하여 스택과 큐에 추가
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalnum((unsigned char)str[i])) { // 공백 및 특수문자 제외
            char ch = tolower((unsigned char)str[i]);
            pushChar(&s, ch);        // 스택에 삽입 (LIFO)
            enqueueChar(&q, ch);     // 큐에 삽입 (FIFO)
        }
    }

    // 2. 스택(역순)과 큐(정순)에서 문자를 하나씩 꺼내며 동일한지 비교
    while (s.top != NULL) {
        char c1 = popChar(&s);
        char c2 = dequeueChar(&q);

        if (c1 != c2) {
            return false; // 문자가 하나라도 다르면 회문이 아님
        }
    }

    return true; // 모두 일치하면 회문
}

int main() {
    char input[100] = "was it a cat i saw";

    if (isPalindrome(input)) {
        printf("\"%s\" -> 회문입니다.\n", input);
    }
    else {
        printf("\"%s\" -> 회문이 아닙니다.\n", input);
    }
    return 0;
}