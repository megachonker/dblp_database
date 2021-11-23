#include <stdlib.h>
#include <stdio.h>


char * gettitle(char * ligne){
    if(strstr(ligne,"<title")){
        char * start = strcspn(ligne,">") +1;
        int diff = strcspn(ligne,"<");
        
        //maloc diff
    }

}
// getauthor

int search(FILE * file_in)
{
    char * ligne[1000];
    
    while (fgets(ligne,1000,file_in))
    {

    }
    
    return 0;
}
