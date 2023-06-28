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
		else {	//错误输入，报错
			cout << "input cmd error!" << endl;
			return 0;
		}
	}
}
