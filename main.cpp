//B877033 JJH Game AI Homework#1
//FSM based talking script
//Netflix-Goodplace S1 (Eleanor, Chidi, Michael)

#include <stdio.h>

//bool type 로 사고, 계획, 만남 설정
//각 캐릭터 별 상태, 대사 출력 코드 만들기
//상태 출력 이후 변화 type

//10.08
//마이클 상태 수정 make trap->satisfied
//deceive 삭제. make plan, plan completed, satisfied 의 세가지 상태 사용.
//엘리너 상태 수정 eat 추가.



int count_plan = 0;

bool g_accident = false;
bool g_planning = false;
bool g_meet = false;



void Eleanor_state(bool accident, bool planning, bool meet)
{
	const char* state="study";

	if (!accident && !planning && !meet)
	{
		state = "study";
		printf("Eleanor is studying ethics.\n");
	}

	else if (!accident && planning && !meet)
	{
		state = "make mistake";

		printf("Eleanor makes mistake!\n");
		printf("The town is going to break!\n");
		printf("Eleanor: OMG! What did I do!\n");
		printf("Eleanor runs to Chidi.\n");
		g_accident = true;
		g_meet = true;
	}
	else if (accident && planning && meet)
	{
		state = "regret";

		printf("Eleanor: Chidi! The town is going to break! I guess I acted selfishly again!\n");

	}
	else
	{
		state = "eat";
		printf("Eleanor eat Yogurt ice cream.\n");
	}
}

void Chidi_state(bool accident, bool planning, bool meet)
{
	const char* state = "writing thesis";

	if (!accident && !planning && !meet)
	{
		state = "writing thesis";
		printf("Chidi is writing thesis.\n");
	}

	else if (accident && planning && meet)
	{
		state = "stomachache";
		printf("Chidi is surprised and nervous.\n");
		printf("Chidi: OH... I feel bad... my stomach hurts again.\n");
		printf("Chidi: I don't like lie, I don't like accident either.\n");
		printf("Chidi: You have to study ethics a lot.\n");
		printf("Eleanor: Ok, dude. I can be a good man.\n");
		printf("Eleanor gose her home.\n");

		g_meet = false;
	}
	else if (accident && planning && !meet)
	{
		state = "fix problem";
		printf("Chidi fixes the problem.\n");

		g_accident = false;
		g_planning = false;
	}


}

void Michael_state(bool accident, bool planning)
{
	const char* state = "make plan";

	if (!accident && !planning)
	{
		if (count_plan >= 3)
		{
			state = "plan completed";

			g_planning = true;

			count_plan = 0;
			printf("Michael smiles wickedly.\n");
			printf("Michael: This plan will work!\n");
		}
		else
		{
			state = "make plan";

			count_plan++;
			printf("Michael: Aha! I have an idea!\n");
			printf("Michael makes plan. (%d/3)\n", count_plan);

		}
	}
	else if (accident && planning)
	{
		state = "satisfied";
		printf("Michael watching Eleanor's mistake.\n");
		printf("Michael: It's going as planned.\n");
		printf("Michael is satisfied.\n");
		
	}
	
}


int main()
{

	for (int i = 0; i < 30; i++)
	{
		Eleanor_state(g_accident, g_planning, g_meet);
		//엘리너 출력
		Chidi_state(g_accident, g_planning, g_meet);
		//치디 출력
		Michael_state(g_accident, g_planning);
		//마이클 출력

		printf("\n\n");
	}

}