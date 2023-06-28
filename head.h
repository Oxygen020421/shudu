#pragma once
#ifndef HGY
#define HGY

#include<iostream>
#include<string>
#include <algorithm>

using namespace std;

typedef struct BlockForSort {
	int x, y;	//数独空白点的位置
	int count;			//计数器，用来排序
	int size;		//一个数独中空白点的个数
}BLFS;	//用来找最小的块


bool judge(int x, int y, int i);
int getBlockNum(int x, int y);
bool cmp(BLFS& a, BLFS& b);
int writeSudokuFinality(char** final, FILE* fp);
int produceOutputIntoTxt(int produce_num);
int dealQuestion(char* path);
int dfs(int num, int size);
void setFlag(int x, int y, int i, int flag);

#endif
