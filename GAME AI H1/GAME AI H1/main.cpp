#include <stdio.h>

//bool type 로 사고, 계획, 만남 설정
//각 캐릭터 별 상태, 대사 출력 코드 만들기
//상태 출력 이후 변화 type

void Eleanor;
void Chidi;
void Michael;

bool accident = false;
bool planning = false;
bool meet = false;



//엘리너의 상태... 어떻게 할까?
//윤리 공부를 하거나 산책 둘 중 하나로 정하자. 기본 루틴.
//상황 체크-> 체크된 상황을 받아 각각 상태 업데이트하기.
//업데이트 후 각자의 상태에 대해 올바른 문장 출력.


const char* Eleanor_state(bool accident, bool planning, bool meet)
{
	const char* state="study";

	if (!accident && !planning && !meet)
		state = "study";
	else if (!accident && planning && !meet)
		state = "make mistake";
	else if (accident && planning && meet)
		state = "regret";

	return state;

}

const char* Chidi_state(bool accident, bool planning, bool meet)
{
	const char* state = "writing thesis";

	if (!accident && !planning && !meet)
		state = "writing thesis";
	else if (accident && planning && meet)
		state = "scold";
	else if (accident && planning && !meet)
		state = "fix problem";

	return state;

}

const char* Michael_state(bool accident, bool planning)
{
	const char* state = "make plan";

	if (!accident && !planning)
		state = "make plan";
	else if (!accident && planning)
		state = "make trap";
	else if (accident && planning)
		state = "deceive";

	return state;

}


void Update(const char* state)
{

}

int main()
{

	for (int i = 0; i < 30; i++)
	{

	}

}