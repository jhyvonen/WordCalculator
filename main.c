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

int main(int argc, char *argv[])
{
    wordList words = {};
    ReadWords(argv[1], &words, 50000);
    int i = 0;
    quicksort(&words, words.numberOfElements);
    printf("Sanoja yhteensä: %d\n", words.totalWords);
    printf("Erilaisia sanoja yhteensä: %d\n", words.numberOfElements);
    for(i = 0; i < 100; i++)
    {
        printf("%d kappaletta sanaa %s\n", words.words[i].count, words.words[i].str);
    }

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

void quicksort(wordList * words, int len)
{
  if (len < 2) return;

  word pivot = words->words[len / 2];

  int i, j;
  for (i = 0, j = len - 1; ; i++, j--)
  {
    while (words->words[i].count > pivot.count) i++;
    while (words->words[j].count <= pivot.count) j--;

    if (i >= j) break;

    word temp = words->words[i];
    words->words[i]     = words->words[j];
    words->words[j]     = temp;
  }

  quicksort(words, i);
  quicksort(words, len - i);
}

int ReadWords(const char *filename, wordList *words, int max_number_of_words)
{
    FILE *f = fopen(filename, "r"); // checking for NULL is boring; i omit it

  if (f == NULL) {
    perror ("Error opening file");
    return;
  }

    int i;
    char temp[100]; // assuming the words cannot be too long

    for (i = 0; i != -1; ++i)
    {
        // Read a word from the file
        if (fscanf(f, "%s", temp) != 1)
            break;
        // note: "!=1" checks for end-of-file; using feof for that is usually a bug
        int j;
        for(j = 0; temp[j]; j++)
        {
            temp[j] = tolower(temp[j]);
        }
        // Allocate memory for the word, because temp is too temporary
        strclean(&temp);
        addWord(words, temp);
    }
    fclose(f);

    // The result of this function is the number of words in the file
    return i;
}

void strclean(char* src)
{
    char *dst = src;

    while(*src)
    {
        if(strchr("abcdefghijklmnopqrstuvwxyz\'", *src) != NULL)
            *dst++ = *src;
        else
            *dst++ = ' ';
        src++;
    }
    *dst = '\0';
}
