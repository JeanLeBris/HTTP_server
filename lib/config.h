#ifndef __CONFIG__

#define __CONFIG__

typedef struct config_type{
    char installation_directory[101];

    char website_dir[1000]
}*config_type;

void Set_Default_Config(config_type config, char *exe_path);
void Load_Config(config_type config);

#endif