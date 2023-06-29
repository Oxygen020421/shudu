/*
* 软件工程结对编程：生成数独终局、求解数独
* 成员：黄韵竹2011064、邹胡诚钰2013958
*/
#include "pch.h"
#include "CppUnitTest.h"
#include"../shudu/func.cpp"
//这里的路径可能需要手动修改

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			//测试越界值
			int a = produceOutputIntoTxt(0);
			int b = produceOutputIntoTxt(1000010);
			int c = produceOutputIntoTxt(-1);
			Assert::AreEqual(a, -1);
			Assert::AreEqual(b, -1);
			Assert::AreEqual(c, -1);
		}
		TEST_METHOD(TestMethod2)
		{
			//正常值
			int a = produceOutputIntoTxt(1000);
			Assert::AreEqual(a, 0);
		}
		TEST_METHOD(TestMethod3)
		{
			//测试正确的九宫格位置
			int a = getBlockNum(3, 3);
			Assert::AreEqual(a, 4);
		}
		TEST_METHOD(TestMethod4)
		{
			//测试错误的九宫格位置
			int a = getBlockNum(0, 9);
			Assert::AreEqual(a, -1);
		}
		TEST_METHOD(TestMethod5)
		{
			//测试正确设置flag
			setFlag(1, 2, 3, 1);
			int a = getBlockNum(1, 2);
			Assert::AreEqual(DEAL::col_count[2][3], 1); 
			Assert::AreEqual(DEAL::row_count[1][3], 1);
			Assert::AreEqual(DEAL::block_count[a][3], 1);
		}
		TEST_METHOD(TestMethod6)
		{
			int a = dealQuestion("asdfadsfadga");//测试错误路径
			Assert::AreEqual(a, -1);
		}
		TEST_METHOD(TestMethod7)
		{
			int a = dealQuestion("pro.txt");//测试错误文件（问题格式错误）
			Assert::AreEqual(a, -1);
		}
		TEST_METHOD(TestMethod8)
		{
			int a = dealQuestion("ques.txt");//测试正确文件
			Assert::AreEqual(a, 0);		//返回0
		}
		TEST_METHOD(TestMethod9)
		{
			int a = dfs(1, 1);		//测试dfs返回正确
			Assert::AreEqual(a, 1);			//返回true
		}
		TEST_METHOD(TestMethod10)
		{
			memset(DEAL::col_count, 1, sizeof(DEAL::col_count));
			int a = dfs(0, 100);
			Assert::AreEqual(a, 0);		//测试错误的dfs，返回false
		}
		TEST_METHOD(TestMethod11)
		{
			memset(DEAL::col_count, 0, sizeof(DEAL::col_count));
			memset(DEAL::row_count, 0, sizeof(DEAL::row_count));
			memset(DEAL::block_count, 0, sizeof(DEAL::block_count));
			int a = judge(2, 2, 2);		//测试返回正确的judge
			Assert::AreEqual(a, 1);
		}
	};
}
