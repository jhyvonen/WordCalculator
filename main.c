#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int count;
    char str[32];
}word;

typedef struct{
    int numberOfElements;
    word words[3809];
}wordList;

void addWord(wordList * words, char name[32]);
int findElement(wordList * words, char name[32]);
void quicksort(wordList * words, int len);

int main()
{
    wordList words = {};
    addWord(&words, "penis");
    addWord(&words, "penis");
    addWord(&words, "penis");
    addWord(&words, "penis");
    addWord(&words, "homo");
    addWord(&words, "homo");
    addWord(&words, "kives");
    addWord(&words, "homo");
    addWord(&words, "kives");
    addWord(&words, "kives");
    ReadWords("testi.txt", &words, 20);
    int i = 0;
    quicksort(&words, words.numberOfElements);
    for(i = 0; i < words.numberOfElements; i++)
    {
        printf("%d kappaletta sanaa %s\n", words.words[i].count, words.words[i].str);
    }

    return 0;
}

int findElement(wordList * words, char name[32])
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

void addWord(wordList * words, char name[32])
{
    int i = findElement(words, name);
    if (i > words->numberOfElements)
        {
            words->words[words->numberOfElements].count = 1;
            strcpy(words->words[words->numberOfElements].str, name);
            words->numberOfElements++;
        }
    else
        words->words[i].count++;
}

void quicksort(wordList * words, int len)
{
  if (len < 2) return;

  word pivot = words->words[len / 2];

  int i, j;
  for (i = 0, j = len - 1; ; i++, j--)
  {
    while (words->words[i].count > pivot.count) i++;
    while (words->words[j].count < pivot.count) j--;

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
    FILE *f = fopen("testi.txt", "r"); // checking for NULL is boring; i omit it

  if (f == NULL) {
    perror ("Error opening file");
    return;
  }

    int i;
    char temp[100]; // assuming the words cannot be too long

    for (i = 0; i < max_number_of_words; ++i)
    {
        // Read a word from the file
        if (fscanf(f, "%s", temp) != 1)
            break;
        // note: "!=1" checks for end-of-file; using feof for that is usually a bug
        for(int j = 0; temp[j]; j++)
        {
            temp[j] = tolower(temp[j]);
        }
        // Allocate memory for the word, because temp is too temporary
        addWord(words, temp);
    }
    fclose(f);

    // The result of this function is the number of words in the file
    return i;
}
