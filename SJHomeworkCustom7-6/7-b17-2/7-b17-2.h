/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define FS_MAX_LENGTH (numeric_limits<std::streamsize>::max)()
#define MAX_LENGTH 1024
#include <iostream>
#include <string.h>
#include <fcntl.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <stdio.h>  
#include <share.h> 
#include <io.h>
#include <windows.h>
#define LEN_BLOCK 8

using namespace std;

const char * const fileName = "config.ini";
const char emptyChar[] = { '\t', ' ', '\n', '\r', '\0' };
const char emptyCharWithoutNewLine[] = { '\t', ' ', '\0' };
enum ITEM_TYPE { TYPE_INT, TYPE_DOUBLE, TYPE_STRING, TYPE_CHARACTER, TYPE_NULL };

int group_add(FILE *fp, const char *group_name);
int whereIsThisGroup(FILE *fp, const char *group_name);
int whereIsNextGroup(FILE *fp);
int group_del(FILE *fp, const char *group_name);
int tail_move_outside(FILE *fp, int from, int to);
int tail_move_inside(FILE *fp, int from, int to);
int item_del(FILE *fp, const char *group_name, const char *item_name);
int item_add(FILE *fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type);
int item_update(FILE *fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type);
int item_get_value(FILE *fp, const char *group_name, const char *item_name, void *item_value, const enum ITEM_TYPE item_type);
void print(FILE *fp);
void resize(int size);
void debugCheck(FILE *fp);