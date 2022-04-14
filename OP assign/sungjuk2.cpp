/** 객체지향프로그래밍 HW#3
*	파일명: sungjuk2.cpp
*	학과: 소프트웨어학과
*	학번: 2021041018
*	이름: 장예서
*/

#include<iostream>
#include<string.h>
#define STDNUM 2		// 정보 입력할 학생 수
using namespace std;


struct Subject {		// 과목 정보
	char SubName[30];	// 과목이름
	int Hakjum;			// 과목학점
	char Grade[10];		// 과목등급
	float GPA;			// 과목평점
};
struct Student {		// 학생 정보
	char StdName[30];	// 학생이름
	int Hakbun;			// 학번
	Subject Sub[3];		// 과목
	float AveGPA;		// 교과목 평균 평점
};

void PrintMenu();							// 메뉴 출력
void EnterStdInfo(Student& StIn);			// 학생 정보 입력
void EnterSubInfo(Subject& SbIn);			// 과목 정보 입력
void CalcGPA(Subject& Sub);					// 교과목 평점 계산
float CalcAveGPA(Subject* Sub);				// 개인 학생의 평균 평점 계산
void PrintAllData(const Student* pSt);		// 전체 학생 신상/성적 정보 출력
void PrintOneData(const Student& rSt);		// 개인 학생 신상/성적 정보 출력
Student* StdSearch(Student* pSt); 			// 학생 이름 검색 후 해당 학생 정보 있는 곳 주소 리턴


int main() {

	int menunum;												// 메뉴 선택지를 저장하는 변수
	int check = 0;												// 1 실행했는지 체크하는 변수
	Student Stu[STDNUM];

	do {

		/* 메뉴 출력 및 선택 */
		PrintMenu();
		cin >> menunum;
		cout << "\n";

		if (menunum == 1) {
			/* 학생 성적 입력 및 성적 계산 */
			check = 1;											// 1 실행시 변수 값 변경
			for (int i = 0; i < STDNUM; i++) {
				cout << "* " << i + 1 << "번째 학생 이름과 학번을 입력하세요.\n";
				EnterStdInfo(Stu[i]);							// 학생 정보 입력
				cout << "\n\n\n";
				cout << "* 수강한 과목 3개와 각 교과목명, 과목학점, 과목등급을 입력하세요.\n";
				for (int j = 0; j < 3; j++) {
					EnterSubInfo(Stu[i].Sub[j]);				// 과목 정보 입력
					CalcGPA(Stu[i].Sub[j]);						// 교과목 평점 계산
					Stu[i].AveGPA = CalcAveGPA(Stu[i].Sub);		// 평균 평점 계산
				}
				cout << "\n\n\n";
			}
		}
		else if (menunum == 2) {
			/* 전체 학생 성적 보기 */
			if (check == 1)										// 1 먼저 실행했는지 체크
				PrintAllData(Stu);								// 전체 학생의 성적 출력
			else
				cout << "1번부터 실행해 주세요.\n\n";
		}
		else if (menunum == 3) {
			/* 학생 이름 검색 */
			if (check == 1) {									// 1 먼저 실행했는지 체크
				Student* SearchStd;
				SearchStd = StdSearch(Stu);						// 학생 이름 입력(없을 시 SearchStd = NULL)
				if (SearchStd != NULL)							// SearchStd에 학생 이름이 제대로 입력됐다면
					PrintOneData(*SearchStd);					// 개인 학생의 성적 출력
			}
			else
				cout << "1번부터 실행해 주세요.\n\n";
		}
	} while (menunum != 4);										// 4 누를 때까지 반복(4 누르면 루프 끝)

	/* 프로그램 종료 */
	cout << "프로그램을 종료합니다." << "\n";

	return 0;

}


void PrintMenu() {
	/* 메뉴 출력 */
	cout << "===== 메뉴 =====\n";
	cout << "1. 학생 성적 입력\n2. 전체 학생 성적 보기\n3. 학생 이름 검색\n4. 프로그램 종료\n\n";
	cout << "원하는 기능을 입력하세요 : ";
}

void EnterStdInfo(Student& StIn) {
	/* 학생 정보 입력 */
	cout << "이름 : ";
	cin >> StIn.StdName;
	cout << "학번 : ";
	cin >> StIn.Hakbun;
}

void EnterSubInfo(Subject& SbIn) {
	/* 과목 정보 입력 */
	cout << "교과목명 : ";
	cin >> SbIn.SubName;
	cout << "과목학점수 : ";
	cin >> SbIn.Hakjum;
	cout << "과목등급<A+ ~ F> : ";
	cin >> SbIn.Grade;
	cout << "\n";
}

void CalcGPA(Subject& Sub) {
	/* 교과목별 평점 계산 */
	switch (Sub.Grade[0]) {									// 문자열의 첫 번째 문자 기준으로 기본점수 부여
	case 'A':
		Sub.GPA = 4.0; break;
	case 'B':
		Sub.GPA = 3.0; break;
	case 'C':
		Sub.GPA = 2.0; break;
	case 'D':
		Sub.GPA = 1.0; break;
	default:
		Sub.GPA = 0; break;
	}
	if (Sub.Grade[1] == '+') {								// 문자열의 두 번째 문자가 +인 경우 0.5점 추가 
		Sub.GPA += 0.5;
	}
	Sub.GPA *= Sub.Hakjum; 									// 교과목별 평점 최종 계산(=등급별 점수 * 학점)
}

float CalcAveGPA(Subject* Sub) {
	/* 교과목 평균 평점 계산 */
	float GPAtot = 0;										// 평점의 합을 저장하는 변수
	for (int i = 0; i < 3; i++) {							// for문을 통해 각 교과목 평점의 합 계산
		GPAtot += Sub[i].GPA;
	}
	return GPAtot / 3.0f;									// 평균 평점 계산 (=각 교과목 평점의 합 / 총 과목수)
}

void PrintAllData(const Student* pSt) {
	/* 전체 학생 정보 출력 */
	cout.width(35);
	cout << "전체 학생 성적 보기\n";
	cout << "=================================================\n";
	for (int i = 0; i < STDNUM; i++)
		PrintOneData(pSt[i]);								// 개인 학생 정보 출력 함수를 호출
}

void PrintOneData(const Student& rSt) {
	/* 개인 학생 정보 출력 */
	cout << "이름 : " << rSt.StdName << "	학번 : " << rSt.Hakbun << "\n";
	cout << "=================================================\n";
	cout << "	과목명	    과목학점 과목등급 과목평점\n";
	cout << "=================================================\n";
	for (int i = 0; i < 3; i++)
	{
		cout.width(15);
		cout << rSt.Sub[i].SubName;
		cout.width(10);
		cout << rSt.Sub[i].Hakjum;
		cout.width(10);
		cout << rSt.Sub[i].Grade;
		cout.width(10);
		cout.precision(2);
		cout << fixed;
		cout << rSt.Sub[i].GPA << "\n";
	}
	cout << "=================================================\n";
	cout.width(37);
	cout << "평균평점";
	cout.width(8);
	cout.precision(2);
	cout << fixed;
	cout << rSt.AveGPA << "\n\n\n";
}

Student* StdSearch(Student* pSt) {
	/* 특정 학생 정보 검색 */
	cout << "검색할 학생 이름: ";
	char SearchName[30];
	cin >> SearchName;
	cout << "\n";
	for (int i = 0; i < STDNUM; i++) {
		if (!strcmp(SearchName, pSt[i].StdName))			// 검색한 이름과 저장된 이름 문자열 비교(같으면 0)
			return &pSt[i];									// 찾으면 해당 학생 정보가 저장된 곳 시작 주소 리턴
	}
	cout << "검색한 학생의 데이터가 존재하지 않습니다.\n\n\n";		// 끝까지 돌아도 없으면 해당 메시지 출력 후 NULL 리턴
	return NULL;
}