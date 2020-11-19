#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void split(char *src, const char *separator, char **dest, int *num) {
	char *pNext;
	int count = 0;
	if (src == NULL || strlen(src) == 0)
		return;
	if (separator == NULL || strlen(separator) == 0)
		return;
	pNext = strtok(src, separator);
	while (pNext != NULL) {
		*dest++ = pNext;
		++count;
		pNext = strtok(NULL, separator);
	}
	*num = count;
}

typedef struct LinkedListNode {
	void* data;
	struct LinkedListNode* next;

}LinkedListNode;

typedef struct {
	LinkedListNode* head;
}linkedList;



// 30% sword (ATK+50%)  30% SHIELD(DEF+50%) 40% MED+1
// GAME OVER  CONDITION: HERO HP =0 OR HERO atk IS TOO LOW
typedef struct {
	int HP;
	int ATK;
	int DEF;
	int MED; // when the hp is 30% or lower, the med will full the hp automatically
	char heroName[50];
}Hero;

typedef struct {
	int HP;
	int ATK;
	int DEF;
	char enemyName[50];
}Enemy;

void showHeroInfo(Hero* hero)
{
	printf("%s\n", hero->heroName);
	printf("HP: %d\n", hero->HP);
	printf("ATK: %d\n", hero->ATK);
	printf("DEF: %d\n", hero->DEF);
	printf("MED: %d\n", hero->MED);
}

void showEnemyInfo(Enemy* enemy)
{
	printf("\t%s\n", enemy->enemyName);
	printf("\tHP: %d\n", enemy->HP);
	printf("\tATK: %d\n", enemy->ATK);
	printf("\tDEF: %d\n", enemy->DEF);

}


//int main(char* herotxt, char* enemytxt, char* seconds)
int main()
{
	// Use readFile to create a linked list

	Hero hero;
	FILE* fHero = fopen("C:\\Users\\Administrator\\Desktop\\hero.txt", "r");
	if (fHero == NULL)
	{
		perror("Error opening file: ");
	}
	else
	{
		char str[100];
		fgets(str, 100, fHero);
		char* newstr[100] = { 0 };
		int num = 0;
		split(str, ",", newstr, &num);
		for (int i = 0;i < num;i++)
		{
			printf("%s\n", newstr[i]);
		}
		fclose(fHero);
	}


	linkedList* enemyList = (linkedList*)malloc(sizeof(linkedList));
	(*enemyList).head = NULL;




	// Use writeFile to save the filtered linked list



	// Memory Cleanup


	return 0;
}

