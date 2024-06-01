#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_authentification(char * password){
    int auth_flag=0;
    char password_buffer[16];
    strcpy(password_buffer, password);
    if(strcmp(password_buffer, "samglish")==0)
    auth_flag=1;
    if(strcmp(password_buffer, "glish")==0)
    auth_flag=1;
    return auth_flag;
}
int maim(int argc, char* argv[]){
    if(argc<2){
        printf("Usage: %s &lt;password&gt;\n", argb[0]);
        exit(0);
    }
    if(check_authentification(argb[1])){
        printf("Acces granted\n");
} else{
    printf("Acces denied\n");
}