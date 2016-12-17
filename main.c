#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int count;
    char str[32];
}word;

typedef struct{
    int numberOfElements;
    word words[50000];
    int totalWords;
}wordList;

void addWord(wordList * words, char name[200]);
int findElement(wordList * words, char name[200]);
void quicksort(wordList * words, int len);
int wordCompare (word *a, word *b);

int main(int argc, char *argv[])
{
    wordList words = {};
    ReadWords(argv[1], &words);
    int i = 0;
    qsort((void *) words.words, words.numberOfElements, sizeof (word), (int (*) (const void *, const void *)) wordCompare);
    printf("Total number of words: %d\n", words.totalWords);
    printf("Number of different words = %d\nThe 100 most common words:\nWORD NUMBER OF OCCURRENCES\n", words.numberOfElements);
    for(i = 0; i < 100; i++)
    {
        printf("%s %d\n", words.words[i].str, words.words[i].count);
    }

    return 0;
}

int wordCompare (word *a, word *b){
    if (a->count < b->count)
        return +1;
    if (a->count > b->count)
        return -1;
    return 0;
}

int findElement(wordList * words, char name[200])
{
    int i = 0;
    while(i <= words->numberOfElements)
    {
        if(strcmp(words->words[i].str,name) == 0)
            return i;
        i++;
    }
    return i;
}

void addWord(wordList * words, char name[200])
{
    char * pch;
    pch = strtok (name, " ");
    while(pch != NULL)
    {
        int i = findElement(words, pch);
        if (i >= words->numberOfElements)
            {
                words->words[words->numberOfElements].count = 1;
                strcpy(words->words[words->numberOfElements].str, pch);
                words->numberOfElements++;
                words->totalWords++;
            }
        else
            {
            words->words[i].count++;
            words->totalWords++;
            }
        pch = strtok (NULL, " ");
    }
}

void ReadWords(const char *filename, wordList *words)
{
    FILE *f = fopen(filename, "r");

    if(f == NULL) {
        perror ("Error opening file");
        return;
    }

    int i;
    char temp[100];

    for(i = 0; i != -1 ; ++i)
    {
        if(fscanf(f, "%s", temp) != 1)
            break;

        int j;
        for(j = 0; temp[j]; j++)
        {
            temp[j] = toupper(temp[j]);
        }
        strclean(&temp);
        addWord(words, temp);
    }
    fclose(f);

    return;
}

void strclean(char* src)
{
    char *dst = src;

    while(*src)
    {
        if(strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ\'", *src) != NULL)
            *dst++ = *src;
        else
            *dst++ = ' ';
        src++;
    }
    *dst = '\0';
}
