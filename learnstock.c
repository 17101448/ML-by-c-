
/*Visual Studio와 호환성 확보 */
#define _CRT_SECURE_NO_WARNINGS

/* 헤더파일 포함*/
#include <stdio.h>
#include <stdlib.h>

/*기호상수 정의*/
#define OK 1 
#define NG 0
#define SETSIZE 100 /* 학습데이터 집합 크기 */
#define CNO 10 /* 학습데이터 자릿수(=10개회사) */
#define GENMAX  10000 /* 해답 후보 생성횟수 */
#define SEED 32768 /* 난수 시드 */

/* 함수 프로토타입 선언*/
void readdata(int data[SETSIZE][CNO],int teacher[SETSIZE]) ;
/* 학습데이터 집합을 읽어옴 */
int rand012() ; /* 0, 1, 2를 반환하는 함수*/
int calcscore(int data[SETSIZE][CNO],int teacher[SETSIZE],
              int answer[CNO]) ;



int main()
{
 int i, j;
 int score = 0;/* 점수 0~setsize점*/
 int answer[CNO];/* 해답 후보 패턴 */
 int data[SETSIZE][CNO];/* 학습 데이터 집합 */
 int teacher[SETSIZE];/* 교사 데이터 */
 int bestscore = 0;/* 최고점 */
 int bestanswer[CNO];/* 최고점과 매칭되는 해답 */

 srand(SEED);/* 난수 초기화 */

 readdata(data,teacher) ;

 /*Loop1 : 해답 후보 생성과 검사 */ 
 for (i = 0; i<GENMAX; ++i) 
 {
    /* 해답 후보 패턴 생성 */
    for (j = 0; j<CNO; ++j) 
    {
     answer[j] = rand012();
    }

  /*해답 후보로 예측값 계산한 뒤 실제값과 비교 뒤 점수화 */
  score=calcscore(data,teacher,answer) ;

    if (score>bestscore) //더 높은 점수가 나오면 정답패턴을 현재 값으로 초기화 
    {
      for (j = 0; j<CNO; ++j) bestanswer[j] = answer[j];

      bestscore = score;

      for (j = 0; j<CNO; ++j) printf("%1d ", bestanswer[j]);

      printf(":score=%d\n", bestscore);
    }
 }

/*최적패턴 결과 반환 */

 printf("\n best pattern \n");
 for (j = 0; j<CNO; ++j)
  printf("%1d ", bestanswer[j]);
 printf(":score=%d\n", bestscore);

 return 0;
}


int calcscore(int data[SETSIZE][CNO],int teacher[SETSIZE],
              int answer[CNO])
{
 int score = 0;
 int point  ;
 int i,j ;
 
    for (i = 0; i<SETSIZE; ++i) 
    {

      point = 0;

      for (j = 0; j<CNO; ++j) 
      {
        if (answer[j] == 2) ++point;
        else if (answer[j] == data[i][j]) ++point;
      }

      if ((point == CNO) && (teacher[i] == 1)) 
      {
        ++score;
      }

      else if ((point != CNO) && (teacher[i] == 0)) 
      {
        ++score;
      }
    }
 return score ;
}

void readdata(int data[SETSIZE][CNO],int teacher[SETSIZE])
{
  int i,j ;
  for (i = 0; i<SETSIZE; ++i) 
  {
    for (j = 0; j<CNO; ++j) 
      {
      scanf("%d", &data[i][j]);
      }
    scanf("%d", &teacher[i]);
  }
}

int rand012()
{
 int rnd ;

 while((rnd=rand())==RAND_MAX) ;

 return (double)rnd/RAND_MAX*3 ;
}

