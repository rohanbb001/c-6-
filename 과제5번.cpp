#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 주소 구조체
typedef struct Address {
    char country[30];
    char state[30];    // 도
    char city[30];     // 시
    char district[30]; // 구
} Address;

// 학생 정보 구조체
typedef struct Student {
    int id;            // 학번/번호
    char name[30];     // 이름
    Address addr;      // 주소
    double score;      // 성적
} Student;

// ------------------- [ 1. 정렬 기능 ] -------------------
// 성적순 정렬 (내림차순)
void sortByScore(Student* students, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (students[j].score < students[j + 1].score) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    printf("성적순 정렬이 완료되었습니다.\n");
}

// 이름순 정렬 (오름차순)
void sortByName(Student* students, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (strcmp(students[j].name, students[j + 1].name) > 0) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    printf("이름순 정렬이 완료되었습니다.\n");
}

// ------------------- [ 2. 학생 찾기 기능 ] -------------------
// 번호로 검색하여 이름 출력
void searchById(Student* students, int count, int searchId) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (students[i].id == searchId) {
            printf("검색 결과 -> 번호: %d, 이름: %s\n", students[i].id, students[i].name);
            found = 1;
        }
    }
    if (!found) printf("해당 번호의 학생을 찾을 수 없습니다.\n");
}

// ------------------- [ 3. 학생 추가 및 삭제 ] -------------------
// 학생 추가
int addStudent(Student* students, int count, Student newStudent) {
    students[count] = newStudent;
    printf("학생 [%s] 정보가 성공적으로 추가되었습니다.\n", newStudent.name);
    return count + 1; // 업데이트된 총 학생 수 반환
}

// 학생 삭제 (중복된 경우 인덱스 선택 삭제)
int deleteStudent(Student* students, int count, const char* name) {
    int matchIndices[100];
    int matchCount = 0;

    // 이름이 일치하는 학생들 찾기
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].name, name) == 0) {
            matchIndices[matchCount++] = i;
        }
    }

    if (matchCount == 0) {
        printf("해당 이름의 학생이 없습니다.\n");
        return count;
    }

    int targetIdx = -1;
    if (matchCount == 1) {
        targetIdx = matchIndices[0];
    }
    else {
        // 중복 시 선택 삭제
        printf("동명이인이 존재합니다. 삭제할 학생의 목록 번호를 선택하세요:\n");
        for (int i = 0; i < matchCount; i++) {
            int idx = matchIndices[i];
            printf("[%d] 학번: %d, 이름: %s, 성적: %.2f\n", i + 1, students[idx].id, students[idx].name, students[idx].score);
        }
        int choice;
        scanf("%d", &choice);
        targetIdx = matchIndices[choice - 1];
    }

    // 배열 요소를 앞으로 당겨서 삭제 처리
    for (int i = targetIdx; i < count - 1; i++) {
        students[i] = students[i + 1];
    }

    printf("학생 정보 삭제가 완료되었습니다.\n");
    return count - 1; // 업데이트된 총 학생 수 반환
}

// ------------------- [ 4. 파일 입출력 ] -------------------
// 파일 저장
void saveToFile(Student* students, int count, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("파일 열기 실패!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d %s %s %s %s %s %.2f\n",
            students[i].id,
            students[i].name,
            students[i].addr.country,
            students[i].addr.state,
            students[i].addr.city,
            students[i].addr.district,
            students[i].score);
    }
    fclose(fp);
    printf("파일 저장 성공: %s\n", filename);
}

// 파일 불러오기
int loadFromFile(Student* students, const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("파일을 찾을 수 없습니다.\n");
        return 0;
    }

    int count = 0;
    while (fscanf(fp, "%d %s %s %s %s %s %lf",
        &students[count].id,
        students[count].name,
        students[count].addr.country,
        students[count].addr.state,
        students[count].addr.city,
        students[count].addr.district,
        &students[count].score) != EOF) {
        count++;
    }
    fclose(fp);
    printf("%d명의 출석부 정보를 파일에서 불러왔습니다.\n", count);
    return count;
}