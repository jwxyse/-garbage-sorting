#include <stdio.h>
#include <string.h>

// 사용자 정보를 저장할 구조체 정의
typedef struct {
    char username[50]; // 사용자 ID를 저장할 배열
    char password[50]; // 비밀번호를 저장할 배열
} User;

// 함수 선언
void signup(User *user); // 사용자 가입 함수
int login(const char *inputUsername, const char *inputPassword); // 로그인 함수
void trashtype(const char* trash); // 쓰레기 분류 함수
void 분리수거안내(char* 물품); // 분리수거 정보를 안내하는 함수

int main() {
    int choice;
    char inputUsername[50];
    char inputPassword[50];
    char trash[100];

    printf("1. 회원가입\n2. 로그인\n선택하세요 (1 또는 2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        // 회원가입
        User user;
        signup(&user);

        FILE *file = fopen("users.txt", "a"); // 파일을 append 모드로 열기
        if (file != NULL) {
            fprintf(file, "%s %s\n", user.username, user.password); // 사용자 정보 저장
            fclose(file);
            printf("%s 님 회원가입이 완료되었습니다!\n", user.username);
            
            // 로그인 기능 호출
            printf("로그인창으로 이동합니다.\n");
            printf("ID: ");
            scanf("%49s", inputUsername);
            printf("Password: ");
            scanf("%49s", inputPassword);

            if (login(inputUsername, inputPassword)) {
                printf("%s 님 환영합니다. 오늘도 유익한 분리수거 정보를 드릴게요!\n", inputUsername);
            } else {
                printf("ID 또는 Password가 잘못 입력되었습니다.\n");
                return 1; // 프로그램 종료
            }
        } else {
            printf("파일 열기 실패!\n");
            return 1; // 프로그램 종료
        }
    } else if (choice == 2) {
        // 로그인
        printf("ID: ");
        scanf("%49s", inputUsername);
        printf("Password: ");
        scanf("%49s", inputPassword);

        if (login(inputUsername, inputPassword)) {
            printf("%s 님 환영합니다. 오늘도 유익한 분리수거 정보를 드릴게요!\n", inputUsername);
        } else {
            printf("ID 또는 Password가 잘못 입력되었습니다.\n");
            return 1; // 프로그램 종료
        }
    } else {
        printf("잘못된 선택입니다.\n");
        return 1; // 프로그램 종료
    }

    // 기능 선택 메뉴
    while (1) {
        printf("\n원하는 기능을 선택하세요:\n");
        printf("1. 쓰레기 분류\n2. 분리수거 안내\n3. 로그아웃\n선택: ");
        int 기능선택;
        scanf("%d", &기능선택);

        if (기능선택 == 1) {
            // 쓰레기 분류 기능
            printf("쓰레기의 이름을 입력하세요: ");
            getchar(); // 이전 입력 버퍼 정리
            scanf("%[^\n]", trash); // 개행 문자 전까지 입력 받기
            trashtype(trash); // 쓰레기 분류 함수 호출
        } else if (기능선택 == 2) {
            // 분리수거 안내 기능
            printf("분리수거할 물품을 입력하세요: ");
            getchar(); // 이전 입력 버퍼 정리
            scanf("%[^\n]", trash); // 개행 문자 전까지 입력 받기
            분리수거안내(trash); // 분리수거 안내 함수 호출
        } else if (기능선택 == 3) {
            printf("로그아웃 되셨습니다.\n");
            break; // 프로그램 종료
        } else {
            printf("잘못된 선택입니다.\n");
        }
    }

    return 0; // 프로그램 종료
}

// 사용자 가입 함수 정의
void signup(User *user) {
    printf("ID를 입력하세요: ");
    scanf("%s", user->username);
    printf("Password를 입력하세요: ");
    scanf("%s", user->password);
}

// 로그인 함수 정의
int login(const char *inputUsername, const char *inputPassword) {
    FILE *file = fopen("users.txt", "r"); // users.txt 파일 읽기 모드로 열기
    if (file == NULL) {
        printf("파일 열기 실패! 로그인 기능을 사용할 수 없습니다.\n");
        return 0;
    }

    User user;
    while (fscanf(file, "%49s %49s", user.username, user.password) != EOF) {
        if (strcmp(user.username, inputUsername) == 0 && strcmp(user.password, inputPassword) == 0) {
            fclose(file);
            return 1; // 로그인 성공
        }
    }

    fclose(file);
    return 0; // 로그인 실패
}

// 쓰레기 분류 함수 정의
void trashtype(const char* trash) {
    char response[10];

    if (strstr(trash, "병") != NULL) {
        printf("유리류 입니다.\n");
    } 
    else if (strstr(trash, "캔") != NULL) {
        printf("캔류 입니다.\n");
    }
    else if (strstr(trash, "껍질") != NULL) {
        printf("딱딱한 껍질일 경우 일반쓰레기, 아닐 경우 음식물 쓰레기 입니다.\n");
    }
    else if (strstr(trash, "비닐") != NULL) {
        printf("음식물이 묻어 있습니까? (y/n): ");
        scanf("%s", response);
        if (strcmp(response, "y") == 0 || strcmp(response, "Y") == 0) {
            printf("일반 쓰레기 입니다.\n");
        } else {
            printf("비닐류 입니다.\n");
        }
    }
    else if (strstr(trash, "뼈") != NULL) {
        printf("일반쓰레기 입니다.\n");
    }
    else if (strstr(trash, "곽") != NULL || strstr(trash, "박스") != NULL) {
        printf("종이류 입니다.\n");
    }
    else {
        printf("분류할 수 없는 쓰레기입니다.\n");
    }
}

// 분리수거 정보를 안내하는 함수 정의
void 분리수거안내(char* 물품) {
    if (strcmp(물품, "귤껍질") == 0 || strcmp(물품, "사과껍질") == 0) {
        printf("%s: 음식물 쓰레기로 배출하세요.\n", 물품);
    }
    else if (strcmp(물품, "수박껍질") == 0) {
        printf("%s: 지역에 따라 일반 쓰레기로 배출하세요.\n", 물품);
    }
    else if (strcmp(물품, "배달용기") == 0) {
        printf("%s: 세척 후 플라스틱이나 스티로폼으로 분리 배출하세요.\n", 물품);
    }
    else if (strcmp(물품, "영수증") == 0) {
        printf("%s: 일반 쓰레기로 배출하세요. 재활용 불가입니다.\n", 물품);
    }
    else if (strcmp(물품, "칫솔") == 0 || strcmp(물품, "치약튜브") == 0) {
        printf("%s: 일반 쓰레기로 배출하세요. 복합 재질입니다.\n", 물품);
    }
    else if (strcmp(물품, "우유팩") == 0 || strcmp(물품, "종이팩") == 0) {
        printf("%s: 종이팩 전용 수거함에 배출하세요.\n", 물품);
    }
    else if (strcmp(물품, "깨진유리") == 0) {
        printf("%s: 일반 쓰레기로 배출하며, 종이나 박스로 감싸세요.\n", 물품);
    }
    else if (strcmp(물품, "알약포장재") == 0) {
        printf("%s: 일반 쓰레기로 배출하세요. 재활용 불가입니다.\n", 물품);
    }
    else if (strcmp(물품, "스티커") == 0 || strcmp(물품, "라벨지") == 0) {
        printf("%s: 일반 쓰레기로 배출하세요. 재활용 불가입니다.\n", 물품);
    }
    else if (strcmp(물품, "견과류껍질") == 0 || strcmp(물품, "달걀껍데기") == 0) {
        printf("%s: 일반 쓰레기로 배출하세요. 단단한 껍질은 재활용이 어렵습니다.\n", 물품);
    }
    else if (strcmp(물품, "커피찌꺼기") == 0) {
        printf("%s: 지역에 따라 음식물 쓰레기 또는 일반 쓰레기로 배출하세요.\n", 물품);
    }
    else if (strcmp(물품, "플라스틱용기") == 0) {
        printf("%s: 세척 후 재활용으로 분리 배출하세요. 세척이 어려우면 일반 쓰레기입니다.\n", 물품);
    }
    else if (strcmp(물품, "헌옷") == 0) {
        printf("%s: 상태에 따라 의류 수거함이나 일반 쓰레기로 배출하세요.\n", 물품);
    }
    else if (strcmp(물품, "배터리") == 0) {
        printf("%s: 전용 수거함이나 주민센터에 배출하세요.\n", 물품);
    }
    else if (strcmp(물품, "전자제품") == 0) {
        printf("%s: 소형 가전은 주민센터, 대형 가전은 수거 신청을 통해 배출하세요.\n", 물품);
    }
    else {
        printf("%s: 분리수거 정보를 찾을 수 없습니다. 지역 지침을 확인하세요.\n", 물품);
    }
}