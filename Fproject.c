#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFFER_SIZE 1000
struct count
{
    char s_Answer1[50];
    char s_category[10];
    char s_levels[10];
    int j_Qno;
    int jLineNo;
    int j_line3;
    int j_line4;
} c1;
struct player
{
    char sName[50];
    int jHints;
    int jScore;
} c2;
void instructions()
{
    printf("***Instruction to play the game***\n");
    printf("To skip a question enter skip\n ");
    printf("To take a hint enter H\n");
    printf("To see score board enter SB\n");
    printf("To  exit from the game enter exit\n");
    printf("To go back enter back\n");
    printf("To start enter start\n");
}
enum LEVEL
{
    Easy = 1,
    Medium = 2,
    Hard = 3
};
enum CATEGORY
{
    HISTORY = 1,
    GEOGRAPHY = 2,
    TECHNOLOGY = 3
};
void showQuestion(int j_Q, char chCat, char chLevel)
{
    int j_line;
    if (j_Q != 1)
    {
        j_line = (j_Q - 1) * 4 + 1;
    }
    else
    {
        j_line = j_Q;
    }

    int jCat = chCat - '0';
    int jLevel = chLevel - '0';
    if (jCat == HISTORY && jLevel == Easy)
    {
        getQuestion("HistoryEasy.txt", j_line);
    }
    else if (jCat == HISTORY && jLevel == Medium)
    {
        getQuestion("HistoryMedium.txt", j_line);
    }
    else if (jCat == HISTORY && jLevel == Hard)
    {
        getQuestion("HistoryHard.txt", j_line);
    }
}
void getQuestion(char arrFileName[50], int j_line)
{
    FILE *file = fopen(arrFileName, "r");
    char line[300];
    int i = 0;
    while (fgets(line, sizeof(line), file))
    {
        i++;
        if (i == j_line)
        {
            printf("%s", line);
        }
    }
    fclose(file);
}
void showHints(int Q, char chCat, char chLevel)
{
    int j_line;
    if (Q != 1)
    {
        j_line = (Q - 1) * 4 + 3;
    }
    else
    {
        j_line = 3;
    }
    int jCat = chCat - '0';
    int jLevel = chLevel - '0';
    if (jCat == HISTORY && jLevel == Easy)
    {
        getQuestion("HistoryEasy.txt", j_line);
    }
    else if (jCat == HISTORY && jLevel == Medium)
    {
        getQuestion("HistoryMedium.txt", j_line);
    }
    else if (jCat == HISTORY && jLevel == Hard)
    {
        getQuestion("HistoryHard.txt", j_line);
    }
}
void checkAnswers(int ques, char cate, char lev, char ans)
{
    int count = 0;
    int j_line2;
    if (ques != 1)
    {
        j_line2 = (ques - 1) * 4 + 2;
    }
    else
    {
        j_line2 = 2;
    }
    int jCat = cate - '0';
    int jLevel = lev - '0';
    if (jCat == HISTORY && jLevel == Easy)
    {
        updateScore("HistoryEasy.txt", j_line2, ans);
    }
    else if (jCat == HISTORY && jLevel == Medium)
    {
        updateScore("HistoryMedium.txt", j_line2, ans);
    }
    else if (jCat == HISTORY && jLevel == Hard)
    {
        updateScore("HistoryHard.txt", j_line2, ans);
    }
}
void updateScore(char arrFileName[50], int j_line2, char ans)
{
    FILE *file = fopen(arrFileName, "r");
    char line[300];
    int i = 0;
    while (fgets(line, sizeof(line), file))
    {
        i++;
        if (i == j_line2)
        {
            if (line[0] == ans)
            {
                c2.jScore++;
                //printf("score is %d",c2.jScore);
            }
        }
    }
    fclose(file);
}
void getHint()
{
    c1.j_line3 = c1.jLineNo + 1;
    FILE *file3 = fopen("playerInfo.txt", "r");
    char line[300];
    int i = 0;
    while (fgets(line, sizeof(line), file3))
    {
        i++;
        if (i == c1.j_line3)
        {
            printf("Your remaining hints are\n");
            printf("%c \n", line[0]);
            int jHint = (int)(line[0]);
            c2.jHints = jHint - '0';
            //printf("%d\n",c2.jHints);
        }
    }
    fclose(file3);
}
void getScore()
{
    c1.j_line4 = c1.jLineNo + 2;
    FILE *file4 = fopen("playerInfo.txt", "r");
    char line[300];
    int i = 0;
    while (fgets(line, sizeof(line), file4))
    {
        i++;
        if (i == c1.j_line4)
        {
            printf("Your score is now \n");
            printf("%c \n", line[0]);
            int jScore = (int)(line[0]);
            c2.jScore = jScore - '0';
        }
    }
    fclose(file4);
}
void login()
{
    printf("Enter your login name\n");
    scanf("%s", &c2.sName);
    FILE *file1 = fopen("playerInfo.txt", "r");
    char line[300];
    int found = 0;
    c1.jLineNo = 1;
    while (fgets(line, sizeof(line), file1))
    {
        char *s;
        s = strstr(line, c2.sName);
        if (s != NULL)
        {
            found = 1;
            break;
        }
        c1.jLineNo++;
    }
    if (found == 1)
    {
        printf("You can go ahead\n");
    }
    else
    {
        printf("enter valid name\n");
        login();
    }
    fclose(file1);
}
void updatefinalScore()
{
    FILE *fPtr = fopen("playerInfo.txt", "r");
    FILE *fTemp;

    char buffer[BUFFER_SIZE];
    char newline[BUFFER_SIZE];
    newline[0] = c2.jScore + '0';
    // printf("Hints int  %d\n", c2.jScore);
    // printf("Hints %c\n", newline[0]);
    int count;

    /* Remove extra new line character from stdin */
    fflush(stdin);

    /*  Open all required files */

    fTemp = fopen("replace.txt", "w");
    printf("file opened ");
    /* fopen() return NULL if unable to open file in given mode. */
    // if (fPtr == NULL || fTemp == NULL)
    // {
    //     /* Unable to open file hence exit */
    //     printf("\nUnable to open file.\n");
    //     printf("Please check whether file exists and you have read/write privilege.\n");
    //     exit(EXIT_SUCCESS);
    // }

    /*
     * Read line from source file and write to destination 
     * file after replacing given line.
     */
    count = 0;
    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
    {
        count++;
        //printf("%d Count %d\n", count, c1.j_line4);
        /* If current line is line to replace */
        if (count == c1.j_line4)
        {
            newline[1] = '\n';
            //printf("%d newline type", c1.j_line3);
            fputs(newline, fTemp);
        }

        else
        {
            fputs(buffer, fTemp);
        }
    }

    /* Close all files to release resource */
    fclose(fPtr);
    fclose(fTemp);

    /* Delete original source file */
    remove("playerInfo.txt");

    /* Rename temporary file as original file */
    rename("replace.txt", "playerInfo.txt");
}
void updateHints()
{

    FILE *fPtr = fopen("playerInfo.txt", "r");
    FILE *fTemp;

    char buffer[BUFFER_SIZE];
    char newline[BUFFER_SIZE];
    newline[0] = c2.jHints + '0';
    printf("Hints int  %d\n", c2.jHints);
    printf("Hints %c\n", newline[0]);
    int count;

    /* Remove extra new line character from stdin */
    fflush(stdin);

    /*  Open all required files */

    fTemp = fopen("replace.txt", "w");
    printf("file opened ");
    /* fopen() return NULL if unable to open file in given mode. */
    // if (fPtr == NULL || fTemp == NULL)
    // {
    //     /* Unable to open file hence exit */
    //     printf("\nUnable to open file.\n");
    //     printf("Please check whether file exists and you have read/write privilege.\n");
    //     exit(EXIT_SUCCESS);
    // }

    /*
     * Read line from source file and write to destination 
     * file after replacing given line.
     */
    count = 0;
    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
    {
        count++;
        printf("%d Count %d\n", count, c1.j_line3);
        /* If current line is line to replace */
        if (count == c1.j_line3)
        {
            newline[1] = '\n';
            printf("%d newline type", c1.j_line3);
            fputs(newline, fTemp);
        }

        else
        {
            fputs(buffer, fTemp);
        }
    }

    /* Close all files to release resource */
    fclose(fPtr);
    fclose(fTemp);

    /* Delete original source file */
    remove("playerInfo.txt");

    /* Rename temporary file as original file */
    rename("replace.txt", "playerInfo.txt");
}
void startGame(char chCatgory, char chLevel)
{
    int jQNo;
    printf("Please Enter Question no. out of \n");
    scanf("%d", &jQNo);
    if (jQNo > 3)
    {
        printf("questions are finished choose next level or category");
        printf("To  exit from the game enter exit\n");

        scanf("%s", &c1.s_Answer1);
        if( strcmp(c1.s_Answer1, "exit") == 0)
        {
            updateHints();
            updatefinalScore();
            exit(0);                                                       //check this
        }
    }
   
    showQuestion(jQNo, chCatgory, chLevel);
    printf("your hints are %d", c2.jHints);
    printf("To take a hint enter H\n To  exit from the game enter exit\n To skip a question enter skip\n ");
    printf("Enter your option\n");
    char s_Answer[50];
    scanf("%s", &s_Answer);
    if (strcmp(s_Answer, "H") == 0)
    {
        printf("your remaining hints are %d \n", c2.jHints);
        c2.jHints--;
        showHints(jQNo, chCatgory, chLevel);
        char ans[50];
        scanf("%s", &ans);
        checkAnswers(jQNo, chCatgory, chLevel, ans[0]);
        startGame(c1.s_category[0], c1.s_levels[0]);
    }
    else if (strcmp(s_Answer, "exit") == 0 )
    {
        updateHints();
        updatefinalScore();
        exit(0);
    }
    else if (strcmp(s_Answer, "skip") == 0)
    {
        startGame(c1.s_category[0], c1.s_levels[0]);
    }
    else if (strcmp(s_Answer, "a") == 0 || strcmp(s_Answer, "b") == 0 || strcmp(s_Answer, "c") == 0 || strcmp(s_Answer, "d") == 0)
    {
        checkAnswers(jQNo, chCatgory, chLevel, s_Answer[0]);
        startGame(c1.s_category[0], c1.s_levels[0]);
    }
}
void chooseCategoryLevel()
{
    login();
    getHint();
    getScore();
    printf("choose category by typing number of category name\n 1-History 2-Geography 3-Technology 4-Grammer\n");

    scanf("%s", &c1.s_category);
    printf("Choose level number \n 1- Easy 2-Medium 3-Hard \n");

    scanf("%s", &c1.s_levels);
    if (c1.s_category[0] == '1' || c1.s_category[0] == '2' || c1.s_category[0] == '3' || c1.s_category[0] == '4')
    {
        if (c1.s_levels[0] == '1' || c1.s_levels[0] == '2' || c1.s_levels[0] == '3' || c1.s_levels[0] == '4')
        {
            startGame(c1.s_category[0], c1.s_levels[0]);
        }
    }
}
void Register()
{
    FILE *rfile = fopen("registerDetails.txt","a+");
    printf("Enter user name\n");
    char userName[50];
    scanf("%s", &userName);
    printf("Enter password\n");
    char password[50];
    scanf("%s", &password);
    fprintf(rfile,"%s\n",userName);
    fprintf(rfile,"%s\n",password);
    fclose(rfile);
}
int main()
{
    printf("If you are already user then enter login otherwise register\n");
    char login[50];
    scanf("%s", &login);
    if(strcmp(login, "login") == 0)
    {
        //login function
    }
    else
    {
        Register();
    }
    instructions();
    char s_str2[20];
    scanf("%s", s_str2);
    if (strcmp(s_str2, "back") == 0)
    {
        printf("Are you sure you want to go back?\n");
        printf("To confirm enter Y To cancel enter N\n");
        char s_YN[20];
        scanf("%s", &s_YN);
        if (strcmp(s_YN, "Y") == 0)
        {
            exit(0);
        }
        else
        {
            chooseCategoryLevel();
        }
    }
    else if (strcmp(s_str2, "exit") == 0)
    {
        printf("Are you sure you want to exit?\n");
        printf("To confirm enter Y To cancel enter N\n");
        char s_Exit[10];
        scanf("%s", &s_Exit);
        if (strcmp(s_Exit, "Y") == 0)
        {
            exit(0);
        }
        else
        {
            chooseCategoryLevel();
        }
    }
    else if (strcmp(s_str2, "SB") == 0)
    {
        char c;
        FILE *ptr;
        ptr = fopen("playerInfo.txt", "r");
        c = fgetc(ptr);
        while (c != EOF)
        {
            printf("%c", c);
            c = fgetc(ptr);
        }
        fclose(ptr);
    }
    else if (strcmp(s_str2, "start") == 0)
    {
        chooseCategoryLevel();
    }

    return 0;
}