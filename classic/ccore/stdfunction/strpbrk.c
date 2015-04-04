#include <string.h>
#include <stdio.h>

int main(void)
{
    char *story = "He shouted: \"What? I can't hear you!\"\n";
    char separators[] = " \t\n.:?!\"";
    char *start = story;
    char *end = NULL;
    char words[16][16]; /* store result words */
    int i = 0;

    while (i < 16 && (end = strpbrk(start, separators)) != NULL) {
        if (end != start) { /* if separator is not the first char */
            strncpy(words[i], start, end-start);
            words[i][end-start] = '\0'; /* append end of string */
            i++;
        }
        start = end + 1; /* next loop */
    }
    puts(story);
    for (int j = 0; j < i; j++)
        puts(words[j]);

    return 0;
}
