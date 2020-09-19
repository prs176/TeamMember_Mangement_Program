#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

struct TeamMember
{
	char name[9];
	int field;
} teamMember[60];

FILE* list;
int count = 0;

void Run();
int Select();

int Make_Struct();
int InputLimit(int, int);
char* PrintField(int);

void Add_Member();
void LookUp_All();
void LookUp();
void Move();
void Delete();

int main()
{
	count = Make_Struct();
	Run();

	return 0;
}

void Run()
{
	int selection;
	while ((selection = Select()) != 0)
	{
		switch (selection) {
		case 1:
			Add_Member();
			break;
		case 2:
			LookUp_All();
			break;
		case 3:
			LookUp();
			break;
		case 4:
			Move();
			break;
		default:
			Delete();
			Make_Struct();
			break;
		}
	}

	return;
}

int Select()
{
	printf("팀원 등록 : 1\nB1ND팀 전체 팀원 조회 : 2\n특정 팀원 조회 : 3\n팀원 부서 이동 : 4\n팀원 삭제 : 5\n종료 : 0\n-> ");

	return InputLimit(0, 5);
}

int Make_Struct()
{
	int i;

	list = fopen("list.txt", "r");
	if (list == NULL) {
		list = fopen("list.txt", "w");
		fclose(list);
		list = fopen("list.txt", "r");
	}

	fscanf(list, "%d", &teamMember[0].field);
	for (i = 0; teamMember[i].field != NULL; i++) fscanf(list, "%s%d", teamMember[i].name, &teamMember[i + 1].field);

	fclose(list);

	return i;
}

int InputLimit(int n1, int n2) {
	char in[50];
	int isNotDigit;

	while (1)
	{
		isNotDigit = 0;
		scanf("%s", in);

		for (int i = 0; in[i] != NULL; i++) {
			if (!isdigit(in[i])) {
				isNotDigit = 1;
				break;
			}
		}
		if (!isNotDigit && atoi(in) >= n1 && atoi(in) <= n2) {
			return atoi(in);
		}

		printf("\n재입력하십시오.\n-> ");
	}
}

char* PrintField(int idx)
{
	switch (teamMember[idx].field)
	{
	case 1:
		return "윈도우";
	case 2:
		return "서버";
	case 3:
		return "웹";
	default:
		return "모바일";
	}
}

void Add_Member()
{
	list = fopen("list.txt", "a");
	int enroll;

	printf("\n이름\n-> ");
	scanf("%s", teamMember[count].name);
	printf("\n부서 [윈도우 : 1 | 서버 : 2 | 웹 : 3 | 모바일 : 4]\n-> ");
	teamMember[count].field = InputLimit(1, 4);

	printf("\n[이름 : %s | 부서 : %s]\n등록하시겠습니까? Y : 1 | N : 0\n-> ", teamMember[count].name, PrintField(count));
	enroll = InputLimit(0, 1);

	if (enroll == 1)
	{
		fprintf(list, "%d %s\n", teamMember[count].field, teamMember[count].name);
		printf("\n등록되었습니다.\n\n");
		++count;
	}
	else
	{
		printf("\n취소되었습니다.\n\n");
	}
	fclose(list);

	return;
}

void LookUp_All()
{
	printf("\n   이름   |   부서   |  식별번호\n");
	for (int i = 0; i < count; i++) {
		if (teamMember[i].field != 0)
		{
			printf("%-9s | %8s | %9d\n", teamMember[i].name, PrintField(i), i + 1);
		}
	}
	printf("\n");

	return;
}

void LookUp()
{
	int i;
	printf("\n식별번호를 입력하세요.\n취소 : 0\n-> ");
	i = InputLimit(0, count);
	if (i == 0)
	{
		printf("\n취소되었습니다.\n\n");
		return;
	}
	i--;

	printf("\n[이름 : %s | 부서 : %s]\n\n", teamMember[i].name, PrintField(i));

	return;
}

void Move()
{
	int i, move, newField;

	printf("\n식별번호를 입력하세요.\n취소 : 0\n-> ");
	i = InputLimit(0, count);
	if (i == 0)
	{
		printf("\n취소되었습니다.\n\n");
		return;
	}
	i--;

	printf("\n[이름 : %s | 부서 : %s]\n\n", teamMember[i].name, PrintField(i));


	printf("어디로 이동 시킬 것입니까?\n[윈도우 : 1 | 서버 : 2 | 웹 : 3 | 모바일 : 4]\n-> ");
	newField = InputLimit(1, 4);

	printf("\n변경전 - [이름 : %s | 부서 : %s]\n변경후 - [이름 : %s | 부서 : %3s]\n\n이동시키겠습니까? Y : 1 / N : 0\n-> ",
		teamMember[i].name, PrintField(i), teamMember[i].name, PrintField(newField));
	move = InputLimit(0, 1);

	if (move == 1) {
		list = fopen("list.txt", "w");
		teamMember[i].field = newField;
		for (int j = 0; j < count; j++)
		{
			fprintf(list, "%d %s\n", teamMember[j].field, teamMember[j].name);
		}
		printf("\n이동되었습니다.\n");
		fclose(list);
	}
	else
	{
		printf("\n취소되었습니다.\n");
	}
	printf("\n");
}

void Delete()
{
	int i, remove;

	printf("\n식별번호를 입력하세요.\n취소 : 0\n-> ");
	i = InputLimit(0, count);
	if (i == 0)
	{
		printf("\n취소되었습니다.\n\n");
		return;
	}
	i--;

	printf("\n[이름 : %s | 부서 : %s]\n\n", teamMember[i].name, PrintField(i));

	printf("삭제하시겠습니까? Y : 1 / N : 0\n-> ");
	remove = InputLimit(0, 1);

	if (remove == 1) {
		list = fopen("list.txt", "w");
		for (int j = 0; j < count; j++)
		{
			if (j == i)
			{
				continue;
			}
			fprintf(list, "%d %s\n", teamMember[j].field, teamMember[j].name);
		}
		--count;
		printf("\n삭제되었습니다.\n\n");
		fclose(list);
	}
	else
	{
		printf("\n취소되었습니다.\n\n");
	}
	printf("\n");

	return;
}