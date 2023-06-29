/*
* 软件工程结对编程：生成数独终局、求解数独
* 成员：黄韵竹2011064、邹胡诚钰2013958
*/
#include"head.h"

int main(int argc, char** argv) {
	if (argc == 1) {	//未输入命令行参数，报错并返回
		cout << "please input command in cmd line" << endl;
		return 0;
	}
	else {
		if (!strcmp(argv[1], "-c")) {
			int produce_num = atoi(argv[2]);
			//若无法转换则代表存在非法输入
			if (produce_num != 0) {
				int produce_num = atoi(argv[2]);
				if (produceOutputIntoTxt(produce_num) == -1) {
					cout << "终局生成失败" << endl;
					return -1;
				}
			}
			else {
				cout << "please input number after -c" << endl;
				return 0;
			}
		}
		else if (!strcmp(argv[1], "-s")) {
			if (dealQuestion(argv[2]) == -1) {
				cout << "error deal sudoku question" << endl;
				return -1;
			}
		}
		else if (!strcmp(argv[1], "-n")) {
			int produceNum = atoi(argv[2]);
			int m = -1, r = -1, type = 0;
			if (argc > 3) {
				if (!strcmp(argv[3], "-u")) {
					type = 1;
				}
				if (!strcmp(argv[3], "-m")) {
					m = atoi(argv[4]);
				}
				if (!strcmp(argv[3], "-r")) {
					r = atoi(argv[4]);
				}
			}
			int res = produceProblemIntoTxt(produceNum, m, r, type);
			if (res == -1) {
				cout << "生成失败" << endl;
			}
		}
		else {	//错误输入，报错
			cout << "input cmd error!" << endl;
			return 0;
		}
	}
}
