#ifndef SHELL_H
#define SHELL_H

void shell_init();
void shell_run();
void te(const char* filename);
void writecommands();
void compile(const char* filename);
void useradd(const char* username);

#endif
