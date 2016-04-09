/* CS261- HW1 - Program6.c*/
/* Name: Fauzi Kliman
 * Date: 4/8/16
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

void lowerCase(char* word){
    /* Convert to lower case letters */
    int i = 0;

    for(i = 0; word[i] != '\0'; i++)
        if(word[i] >= 'A' && word[i] <= 'Z')
            word[i] = toLowerCase(word[i]);
}

void upperCase(char* word){
	/* Convert to upper case letters */
    int i = 0;

    for(i = 0; word[i] != '\0'; i++)
        if(word[i] >= 'a' && word[i] <= 'z')
            word[i] = toUpperCase(word[i]);
}

int main(){
    /* Input a word and flag */
    char word[100];
    char flag[100];

    scanf("%s", word);
    scanf("%s", flag);

    /* Print the input word and flag */
    printf("Word: %s\n", word);
    printf("Flag: %c\n", flag[0]);
	
    /* Based on the value of flag
	  Call lowerCase()
	  or
	  Call upperCase() */
    if(flag[0] == '1')
        upperCase(word);

    else if(flag[0] == '0')
        lowerCase(word);
    
    /* Print the new word */
    printf("New Word: %s\n", word);	
    
    return 0;
}
