#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "newSleep.h"

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
    Enemy* data;
    struct LinkedListNode* next;

}LinkedListNode;

typedef struct {
    LinkedListNode* head;
}linkedList;



// 30% sword (ATK+50%)  30% SHIELD(DEF+50%) 40% MED+1
// GAME OVER  CONDITION: HERO HP =0 OR HERO atk IS TOO LOW

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

int ifCriticalHit()
{

    int k = rand()%2;
    return k;
}


//int main(char* herotxt, char* enemytxt, char* seconds)
int main()
{
    // Use readFile to create a linked list

    Hero hero;
    FILE* fHero = fopen("/Users/Carl/Documents/UCP/hero.txt", "r");

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

        hero.HP = atoi(newstr[0]);
        hero.ATK = atoi(newstr[1]);
        hero.DEF = atoi(newstr[2]);
        hero.MED = atoi(newstr[3]);
        for(int j=0;j<strlen(newstr[4])-1;++j) {
            hero.heroName[j] = newstr[4][j];
        }

        fclose(fHero);
    }

    linkedList* enemyList = (linkedList*)malloc(sizeof(linkedList));
    (*enemyList).head = NULL;
    FILE* fEnemy = fopen("/Users/Carl/Documents/UCP/enemies.txt", "r");
    if (fEnemy == NULL)
    {
        perror("Error opening file: ");
    }
    else
    {
        char str[100];
        fgets(str, 100, fEnemy);
        LinkedListNode* node = (LinkedListNode*)malloc(sizeof(LinkedListNode));
        enemyList->head = node;
        do{
            char* newstr[100] = { 0 };
            int num = 0;
            split(str, ",", newstr, &num);
            Enemy *enemy = (Enemy*)malloc(sizeof(Enemy));
            enemy->HP = atoi(newstr[0]);
            enemy->ATK = atoi(newstr[1]);
            enemy->DEF = atoi(newstr[2]);
            for(int j=0;j<strlen(newstr[3])-1;++j) {
                enemy->enemyName[j] = newstr[3][j];
            }

            printf("%s\n",enemy->enemyName);
            node->data = enemy;
            node->next = NULL;
            LinkedListNode* pNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
            node->next = pNode;
            node = pNode;
            node->next = NULL;
        }while(fgets(str, 100, fEnemy)!=NULL);

        fclose(fEnemy);
    }


    //文件读取与list完成
    printf("Welcome to the auto RPG ! \n");
    newSleep(5);
    system("clear");
    printf("Hero:\n");
    printf("%s\t\t", hero.heroName);
    printf("HP: %d", hero.HP);
    printf("\tATK: %d", hero.ATK);
    printf("\tDEF: %d", hero.DEF);
    printf("\tMED: %d\n\n", hero.MED);

    printf("Enemies:\n");
    LinkedListNode* tmp;
    tmp =  enemyList->head;
    while(tmp->next!= NULL)
    {

        printf("%s\t    ", tmp->data->enemyName);
        printf("HP: %d", tmp->data->HP);
        printf("\tATK: %d", tmp->data->ATK);
        printf("\tDEF: %d\n", tmp->data->DEF);
        tmp = tmp->next;
    }

    newSleep(5);
    system("clear");

    Enemy *newEnemy = (Enemy*)malloc(sizeof(Enemy));
    newEnemy = enemyList->head->data;
//    printf("%d",newEnemy->HP);
//    newEnemy->HP = 100;
    int fullHP = hero.HP;
    while(hero.HP>0)
    {
        //fight

        // hero begins
        if(newEnemy == NULL)
        {
            printf("Arlen defeats all enemies! The world is saved! \n");
            break;
        }

        int damage = 0;
        int flag = ifCriticalHit();
        if(flag) //double hit
        {
            damage = hero.ATK * 2 - newEnemy->DEF;
        }
        else // normal hit
        {
            damage = hero.ATK - newEnemy->DEF;
        }

        newEnemy->HP -= damage;
        if(newEnemy->HP<=0)
            newEnemy->HP = 0;
        showHeroInfo(&hero);

        if(damage>0)
        {

            if(flag)
            {
                printf("\t%s attack %s,Critical hit!! dealing %d damage!\n\n", hero.heroName,newEnemy->enemyName,damage);
            }
            else
            {
                printf("\t%s attack %s, dealing %d damage!\n\n", hero.heroName,newEnemy->enemyName, damage);
            }


        }
        else
        {
            printf("\thero missed\n\n");
        }

        showEnemyInfo(newEnemy);

        //******************
        // ENEMY ATTACKs
        newSleep(5);
        system("clear");
        int flag1 = ifCriticalHit();
        if(flag1) //double hit
        {
            damage = hero.ATK * 2 - newEnemy->DEF;
        }
        else // normal hit
        {
            damage = hero.ATK - newEnemy->DEF;
        }
        hero.HP -=damage;
//        if(hero.HP<=(int)(0.3*fullHP) && hero.HP>0 && hero.MED>0)
//        {
//            hero.HP = fullHP;
//            hero.MED--;
//        }

        if(hero.HP<=0)
        {    hero.HP = 0;

        }
        showHeroInfo(&hero);
        if(damage>0)
        {
            if(hero.HP<=(int)(0.3*fullHP) && hero.HP>0 && hero.MED>0)
            {
                hero.HP = fullHP;
                hero.MED--;
                printf("\t%s is badly injured, eating 1 medicine. HP is restored!\n", hero.heroName);

            }
            if(flag1)
            {
                printf("\t%s attack %s,Critical hit!! dealing %d damage!\n\n", newEnemy->enemyName,hero.heroName,damage);
            }
            else
            {
                printf("\t%s attack %s, dealing %d damage!\n\n", newEnemy->enemyName, hero.heroName, damage);
            }

        }
        else
        {
            printf("\tenemy missed\n\n");
        }

        showEnemyInfo(newEnemy);
        newSleep(5);
        system("clear");
        if(newEnemy->HP==0)
        {
            if(newEnemy == NULL)
            {
                printf("Enemies fail\n");
                break;
            }
            else
            {
                enemyList->head = enemyList->head->next;
                newEnemy = enemyList->head->data;
            }


        }

        if(hero.HP<=0)
        {
                printf("Arlen loses the battle! The world is doomed! \n");
            break;
        }

    }


    // Memory Cleanup


    return 0;
}

