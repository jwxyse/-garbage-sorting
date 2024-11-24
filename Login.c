#include <stdio.h>
#include <string.h>

// 사용자 정보를 저장할 구조체 정의
typedef struct {
    char username[50]; //사용자 ID 저장할 배열
    char password[50]; // 비밀번호 저장할 배열 
} User;  //구조체의 이름 typedef 를 사용해서 User 라는 이름으로 간단하게 참조 가능하도록 함 그래서 User를 사용하여 이후 구조체 타입의 변수 선언 가능 

// 로그인 함수 선언
int login(const char *inputUsername, const char *inputPassword);

int main() {
    char inputUsername[50]; //사용자에게 입력을 받을 ID 배열 선언 
    char inputPassword[50]; //사용자에게 입력을 받을 password 배열 선언 

    // 사용자로부터 입력 받기
    printf("ID: "); //출력문
    scanf("%49s", inputUsername); // 입력 길이 제한하고 사용자에게 입력 받은 ID 불러옴 
    printf("Password: "); //출력문 
    scanf("%49s", inputPassword); // // 입력 길이 제한하고 사용자에게 입력 받은 ID 불러옴

    // 로그인 시도
    if (login(inputUsername, inputPassword)) { //로그인 함수 호출 
        printf("%s 님 환영합니다. 오늘도 유익한 분리수거 정보를 드릴게요! \n", inputUsername);
    } else {
        printf("ID 또는 Password가 잘못 입력되었습니다.\n"); 
    }

    return 0; //프로그램 종료
}

// 로그인 함수 정의
int login(const char *inputUsername, const char *inputPassword) {
    // 입력된 사용자명과 비밀번호를 확인하기 위한 함수
    // inputUsername: 사용자가 입력한 ID
    // inputPassword: 사용자가 입력한 password
    FILE *file = fopen("users.txt", "r"); // 파일을 읽기 모드로 열기
    if (file == NULL) { // 파일이 정상적으로 열리지 않았는지 확인(파일 포인터가 NULL인지 확인)
        printf("파일 열기 실패!\n");
        return 0; // 파일 열기 실패
    }

    User user; // 사용자 정보를 저장할 구조체 변수 선언
    while (fscanf(file, "%49s %49s", user.username, user.password) != EOF) { 
    // fscanf 함수는 파일에서 최대 49자의 사용자명과 비밀번호를 읽어 user 구조체에 저장
    // 입력 길이 제한: %49s는 최대 49자까지 읽도록 제한하여 버퍼 오버플로우를 방지
    // 루프는 EOF에 도달할 때까지 반복
        if (strcmp(user.username, inputUsername) == 0 && strcmp(user.password, inputPassword) == 0) { // 입력된 사용자명과 비밀번호가 파일의 값과 일치하는지 확인
            fclose(file); // 파일 닫기
            return 1; // 로그인 성공
        }
    }

    fclose(file); // 파일 닫기
    return 0; // 로그인 실패
} //으아아ㅏㅏㅏㅏ