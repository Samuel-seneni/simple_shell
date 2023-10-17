#include "shell.h"
/**
 * strtok - split the string of tokens
 * @str: strings to be splited
 * @delim: delimeter of the string
 */
char split_str(void)
{
        char *str = "This is separated word by space";
        char *stc = malloc(sizeof (char) * strlen(str));
        char delim[5] = " ";
        char *trunks;
        int i;

        strcpy(stc, str);
        trunks = strtok(stc, delim);
        /* printf("%p\n %p\n", str, trunks);*/

        while (trunks != NULL)
        {
                printf("%s\n", trunks);
                trunks = strtok(NULL, delim);
        }
	for (i = 0; i < 32; i++)
        {
                if (stc[i] == '\0')
                        printf("\\0");
                else
                printf("%c", stc[i]);
        }
        return (0);
}
