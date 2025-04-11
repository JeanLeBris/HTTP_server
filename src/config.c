#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/config.h"

void Set_Default_Config(config_type config, char *exe_path){
    strncpy(config->installation_directory, exe_path, strlen(exe_path) - 15);
    config->installation_directory[strlen(exe_path) - 15] = '\0';

    strcpy(config->website_dir, ".");
}

void Load_Config(config_type config){
    char config_file_path[101] = "";
    char line[101] = "";
    char *fragmented_line = NULL;
    char seps[] = " \n=\"";
    strcat(strcat(config_file_path, config->installation_directory), "./csv_editor.conf");
    FILE *f = fopen(config_file_path, "r");
    if(f == NULL){
        printf("file error\n");
        return;
    }
    fseek(f, 0, SEEK_SET);
    while(!feof(f)){
        fgets(line, 100, f);
        fragmented_line = strtok(line, seps);
        if(strcmp(fragmented_line, "website_root_dir") == 0){
            strcpy(config->website_dir, strtok(NULL, seps));
        }
    }
    fclose(f);
}