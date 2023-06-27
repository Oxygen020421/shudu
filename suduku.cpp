#include<cstdio>
#include<cstdlib>
#include<iostream>
#include <fstream>
#include <string>
#include <vector>

#include"perm.h"

using namespace std;

int result[100000000];   //用于存放指向 存放数独终局数据数组 的指针
char write_type[99999999];	//用于提前存好数独终局的格式，减少写入文件的时间
int solve_map[1000005][81];  //用于存放求解数独时的数独问题

class sudo
{
private:
	int sudo_map[9][9];
	int count;
	int num;
public:
	sudo() {};
	sudo(int n)
	{
		count = 0;
		num = n;

	}
	void creat_End();
	void write_to_file();
	
	void solve_Que(int count,int que_num);
	bool is_right(int count, int que_num);
};

void sudo::creat_End()
{

	int first_line[9] = { 5,1,2,3,4,6,7,8,9 };   //数独模型第一行的某一种情况，第一个数：(6+8)%9+1=5 

	int row[8] = { 1,2,3,4,5,6,7,8 };    //进行行变化对应行的下标		

	int arr_change[8] = { 3,6,1,4,7,2,5,8 };		//由第一行的数分别向左移动 3、6、1、4、7、2、5、8 可以得到一个完整的数独终局

	do
	{
		for (int k = 0; k < 9; k++)   //为第一行赋值
			this->sudo_map[0][k] = first_line[k];

		//根据map的关系和第一行的某个排列生成其他行，得到一个数独终局的模板
		for (int i = 1; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
				this->sudo_map[i][j] = first_line[(arr_change[i - 1] + j) % 9];		//分别将first_line进行不同程度移位后的行赋给后续的行
		}

		do
		{
			do 
			{
				do
				{
					for (int j = 0; j < 9; j++)
					{

					}

					//将产生的矩阵存入result数组中
					for (int k = 0; k < 9; k++)
						result[k + 81 * this->count] = first_line[k];   //存第一行数据						

					for (int i = 1; i < 9; i++)
						for (int j = 0; j < 9; j++)
							result[i * 9 + j + 81*this->count] = this->sudo_map[row[i-1]][j];  //将数独终局存入一个一维数组中,便于输出

					this->count++;

					if (this->count == this->num)   //终局数达到要求了
						return;

				}while(Perm(row+5,row+7));			//对第7、8、9行进行排列

			} while (Perm(row+2, row+4));		//对第4、5、6行进行排列

		} while (Perm(row, row+1));		//对第2、3行进行排列

	} while (Perm(first_line + 1, first_line + 8));     //每对第一行的后8位进行排列后便据此生成一个新的数独终局模板 

	return ;
}


bool sudo::is_right(int count, int que_num)		//判断填入数据的合法性
{
	int row = count / 9;	//当前空所在行
	int col = count % 9;	//当前空所在列
	int k;

	for (k = 0; k < 9; k++)		//判断填入的数在该行是否出现过
	{
		if (solve_map[que_num][row * 9 + k] == solve_map[que_num][count] && k != col)
		{
			return false;
		}
	}
	
	for (k = 0; k < 9; k++)		//判断填入的数在该列是否出现过
	{
		if (solve_map[que_num][col * 9 + k] == solve_map[que_num][count] && k != row)
		{
			return false;
		}
	}
	
	//判断填入的数在3*3的块区内是否出现过
	int part_row = row / 3 * 3;
	int part_col = col / 3 * 3;

	for (int j = part_row; j < part_row + 3; j++)
	{
		for (int k = part_col; k < part_col + 3; k++)

		{
			if (solve_map[que_num][j * 9 + k] == solve_map[que_num][count] && j != row && k != col)
			{
				return false;
			}
		}
	}

	//满足条件的数即可填入
	return true;
}

int op = 0;   //用于表示solv_map里是否有空格0，若无则置1表示数独问题解决完毕

void sudo::solve_Que(int count,int que_num)
{
	//如果81个数字均有合法的填入，说明数独问题解决完毕，打印结果至文件
	if (count == 81 && op ==1)
	{
		for (int i = 0; i < 81; i++)
				result[i + 81* que_num] = solve_map[que_num][i];  //将解得的数独终局存入一个一维数组中

		que_num++;
		this->num++;    

		return;
	}

	int row = count / 9;	//当前空所在行
	int col = count % 9;	//当前空所在列

	//如果该位置为0，即需要进行求解
	if (solve_map[que_num][count] == '0')
	{
		op = 0;
		for (int i = 1; i <= 9; i++)
		{
			solve_map[que_num][count] = i;	//将1-9填入该空位

			if (is_right(count,que_num))	 //判断该数是否合法
			{
				op = 1;
				solve_Que(count + 1,que_num);	//如果合法，则对下一个0位置进行操作
			}
		}

		//如果该位置始终没找到合适的数字，或者dfs到某一层没有找到一个合适的数字，则重新置0等待回溯
		solve_map[que_num][count] = 0;
		op = 0;
	}

	//如果该位置不为0，则直接对下个位置进行操作
	else
	{
		solve_Que(count + 1,que_num);
	}

}

void sudo::write_to_file()
{
	int t = 0;
	for (int k = 0; k < this->num; k++)
	{
		for (int j = 0; j < 81; j++)
		{
			write_type[t] = result[81 * k + j] + '0';
			t++;

			if (j % 9 == 8)
			{
				write_type[t] = '\n';   
				t++;
				continue;
			}

			write_type[t] = ' ';
			t++;
		}

		if (k < this->num - 1)
		{
			write_type[t] = '\n';
			t++;
		}
	}

	ofstream fp;

	fp.open("sudoku.txt", ios::app);
	
	if (!fp) 
	{
		cout << "打开文件失败" << endl;
		return ;
	}

	int i = 0;
	while (write_type[i]!='\0')
	{
		fp << write_type[i];
		i++;
	}
	cout << "work" << endl;

}

int main(int argc, char const *argv[])
{
	/*		//测试用例
	sudo sudo1(1000000);

	sudo1.creat_End();
	sudo1.write_to_file();

	return 0;
	*/
	
	if (argc != 3 ) //未按照标准格式输入 
	{
		printf("请输入正确的格式\n");
		printf("如: sudo.exe -c 100\n");
		printf("    sudo.exe -s absolute_path_of_puzzlefile\n");
		
		return 0;
	}

	if (strcmp(argv[1], "-c") == 0)  //-c输出数独终局
	{
		int num = atoi(argv[2]);

		if (num <= 0 && num > 1000000)	//n不按要求输入时，报错
		{
			printf("请输入正确的格式\n");
			printf("如: sudo.exe -c 100\n");
			exit(0);
		}

		else
		{
			sudo sudo1(num);
			
			sudo1.creat_End();
			sudo1.write_to_file();

			return 0;
		}
		
	}

	if (strcmp(argv[1], "-s") == 0)  //-s求解数独问题
	{

		ifstream fi;
		fi.open(argv[2]);
		
		if (!fi)
		{
			cout << "打开文件失败" << endl;
			return 0;
		}

		sudo sudo2;

		char buff[1024];                                     // 1Kb的缓冲区
		int t = 0, que_num = 0;

		while (fi.getline(buff, 1024))                     // 按行读取文件到缓冲区
		{
			for (int i = 0; i < 1024; i++)
			{
				char tmp = buff[i];

				if (tmp >= '0'&& tmp <= '9')   //将数字存入solve_map中
				{
					if (t == 81)	//每存入81个数字即存入1一个数独问题
					{
						t = 0;
						que_num++;
					}

					solve_map[que_num][t] = tmp - '0';
					t++;
				}
			}
		}

		for (int i = 0; i < que_num; i++) 
		sudo2.solve_Que(0,i);

		sudo2.write_to_file();   //写入文件

		
	}




}
