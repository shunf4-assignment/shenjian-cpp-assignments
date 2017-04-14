/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define FS_MAX_LENGTH (numeric_limits<std::streamsize>::max)()
#define MAX_LENGTH 1024
#include <iostream>
#include <fstream>
#include <filesystem>
#include <strstream>

#define LEN_BLOCK 8

using namespace std;

const char * const fileName = "config.ini";
const char emptyChar[] = { '\t', ' ', '\n', '\r', '\0' };
const char emptyCharWithoutNewLine[] = { '\t', ' ', '\0' };
enum ITEM_TYPE{TYPE_INT, TYPE_DOUBLE, TYPE_STRING, TYPE_CHARACTER, TYPE_NULL};

int group_add(fstream &fp, const char *group_name);
int whereIsThisGroup(fstream &fp, const char *group_name);
int whereIsNextGroup(fstream &fp);
int group_del(fstream &fp, const char *group_name);
int tail_move_outside(fstream &fp, int from, int to);
int tail_move_inside(fstream &fp, int from, int to);
int item_del(fstream &fp, const char *group_name, const char *item_name);
int item_add(fstream &fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type);
int item_update(fstream &fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type);
int item_get_value(fstream &fp, const char *group_name, const char *item_name, void *item_value, const enum ITEM_TYPE item_type);
void print(fstream &fp);
void resize(int size);
void debugCheck(fstream &fp);