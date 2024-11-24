#include <stdio.h>
#include <string.h>

// 사용자 정보를 저장할 구조체 정의
typedef struct {
    char username[50]; // 사용자 ID를 저장할 배열
    char password[50]; // 비밀번호를 저장할 배열
} User; //구조체의 이름 typedef 를 사용해서 User 라는 이름으로 간단하게 참조 가능하도록 함 그래서 User를 사용하여 이후 구조체 타입의 변수 선언 가능 

void signup(User *user); // 사용자 가입 함수 선언

int main() {
    User user; // 사용자 구조체 User에 user 변수 선언

    signup(&user); // 사용자로부터 사용자 이름과 비밀번호 입력 받기

    FILE *file = fopen("users.txt", "a"); // 파일을 append 모드로 열고 사용자 정보를 파일에 저장 
    if (file != NULL) {
        fprintf(file, "%s %s\n", user.username, user.password); // 사용자 정보 저장
        fclose(file); // 파일 닫기
        // 회원가입 성공 메시지 출력
        printf("%s 님 환영합니다!\n", user.username);
    } else {
        printf("파일 열기 실패!\n");
    }

    return 0; // 프로그램 종료
}

// 사용자 가입 함수 정의
void signup(User *user) { // 사용자로부터 사용자명과 비밀번호 입력 받기
    printf("ID를 입력하세요: "); //출력문
    scanf("%s", user->username); // User 구조체의 user 구조체 변수를  username 팔드에 저장하는 코드
    printf("Password를 입력하세요: "); //출력문
    scanf("%s", user->password); // User 구조체의 user 구조체 변수를  password 팔드에 저장하는 코드
}