#include <stdio.h>

//bool type �� ���, ��ȹ, ���� ����
//�� ĳ���� �� ����, ��� ��� �ڵ� �����
//���� ��� ���� ��ȭ type

void Eleanor;
void Chidi;
void Michael;

bool accident = false;
bool planning = false;
bool meet = false;



//�������� ����... ��� �ұ�?
//���� ���θ� �ϰų� ��å �� �� �ϳ��� ������. �⺻ ��ƾ.
//��Ȳ üũ-> üũ�� ��Ȳ�� �޾� ���� ���� ������Ʈ�ϱ�.
//������Ʈ �� ������ ���¿� ���� �ùٸ� ���� ���.


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