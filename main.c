#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void setBalance(int, int);
int setSpending(int, int);
int sumSpending();
void getSpending();
void getStatistics();
// 1. 식비, 2. 교통비, 3. 문화생활, 4. 쇼핑, 5. 기타
int spending[5] = {};
int restDate = 0;
int money = 0; // 돈
int main () {
  int out = 1;
  int input;
  int input1, input2;
  while (out) {
    printf("메인 메뉴\n\n==========================================================\n");
    printf("1. 이번 달 용돈 입력하기\n");
    printf("2. 지출 기록하기\n");
    printf("3. 일일 권장 소비액 확인하기\n");
    printf("4. 카테고리별 지출 통계 보기\n");
    printf("5. 프로그램 종료\n==========================================================\n메뉴 입력 => ");
    scanf(" %d",&input);
    if (!isdigit(input)){
      getchar();
    }
    switch (input){
      case 1:
        printf("이번 달 받은 용돈을 입력하세요.\n> ");
        scanf(" %d",&input1);
        printf("이번 달 남은 날짜를 입력하세요.\n> ");
        scanf(" %d",&input2);
        setBalance(input1,input2);
        break;
      case 2:
        printf("지출 비용을 입력하세요.\n> ");
        scanf(" %d", &input1);
        printf("지출 카테고리를 입력하세요. (1. 식비, 2. 교통비, 3. 문화생활, 4. 쇼핑, 5. 기타)\n> ");
        scanf(" %d", &input2);
        if (setSpending(input1, input2)) printf("입력 성공\n");
        else printf("입력 실패\n");
        break;
      case 3:
        if (money != 0) getSpending();
        else printf("돈을 먼저 입력하세요 \n");
        break;
      case 4:
        getStatistics();
        break;
      case 5:
        printf("프로그램을 종료합니다.\n");
        out = 0;
        break;
      default:
        printf("없는 메뉴입니다.\n");
        
    }
		system("pause");
  }
  
	return 0;
}
void setBalance(int balance, int remains) { // 2
  if (balance < 0 || remains < 0){
    printf("올바른 범위 내의 수를 입력 해주세요.\n");
    return;
  }
	money = balance;
  restDate = remains; 
  return;
}

int setSpending(int amount, int category) { // 2
  if (amount < 0 || category < 0){
    printf("올바른 범위 내의 수를 입력 해주세요.\n");
    return 0;
  }
	if (category < 6 && category > 0) {
    if (money >= sumSpending() + amount) { spending[category - 1] = amount; return 1; } // 1 이면 입력 성공
    else { printf("입력된 지출이 자금보다 큽니다.\n"); return 0; } // 0 이면 입력 실패
  } 
  printf("입력 실패, %d 카테고리는 존재하지 않습니다.\n", category);
  return 0; // 0 이면 입력 실패
}

int sumSpending() {
  int res = 0;
  for (int i = 0; i<5; i++){
    res += spending[i];
  }
  return res;
}

void getSpending() {
  int remaining = money;
  int remaining_date = restDate;
  int spending = sumSpending();
  int recommend = (remaining - spending) / remaining_date;
  if (recommend <= spending){
    printf("오늘의 권장 소비액: %d원\n", recommend);
    printf("오늘 입력한 지출 금액: %d원\n", spending);
    printf("\n\n");
    printf("경고! 오늘 권장 소비액을 초과했습니다.\n텅장이 가까워지고 있습니다. 소비를 줄여 보세요!\n");
  } else {
    printf("이번 달 남은 금액: %d원\n", remaining - spending);
    printf("남은 날짜: %d일\n", remaining_date);
    printf("오늘의 권장 소비액은 %d원입니다.\n오늘은 딱 %d원까지만 쓰는 것을 추천합니다!\n", recommend, recommend);
  }
  return;
}

void getStatistics() {
  printf("카테고리별 누적 지출 금액:\n\n");
  printf("식비: %d원\n교통비: %d원\n문화생활: %d원\n쇼핑: %d원\n기타: %d원",spending[0],spending[1],spending[2],spending[3],spending[4]);
  printf("\n\n총 지출 금액: %d원\n현재 남은 금액: %d원\n\n",sumSpending(),money-sumSpending());
  return;
}    