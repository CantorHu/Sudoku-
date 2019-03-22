#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

using namespace std;

class Uni_num
{
public:
	int ans = 0;
	int tot_num[9][9];
	Uni_num() { init(); }
	void init();
	bool valid(int row, int col, int num);//是否可以填
	void tr_push();//递归填数字
	bool full();//满了吗
	void print();
};

int main(int argc, char *argv[])
{
	
	Uni_num un;
	if (argc > 1)
	{
		string temp;
		int *it = &un.tot_num[0][0];
		while (cin >> temp)
		{
			if (temp == "*")
				*it++ = 10;
			else
				*it++ = stoi(temp);
		}
		un.tr_push();
		cout << "一共" << un.ans << "种答案" << endl;
	}
	else
	{
		cout 
			<< "请以（2,3）5的方式输入第二行第三个数字为5，每次输入后请按enter换行。" 
			<< endl;
		while (true)
		{
			cout << "是否打印结果（y/n,y为输出结果）？" << endl;
			char ch;
			cin >> ch;
			if (ch == 'y')
			{
				un.tr_push();
				cout << "一共" << un.ans << "种答案" << endl;
				break;
			}
			stringstream ss;
			string s1, s2, s3, s;
			int info[3], i = 0;
			char nt;
			cin >> s;
			ss << s;
			while (ss.get(nt))
				if (nt >= '0'&&nt <= '9')
				{
					ss.putback(nt);
					ss >> info[i++];
					if (i == 3) break;
				}
			int row = info[0], col = info[1], num = info[2];

			if (!(row >= 1 && row <= 9 && num >= 1 && num <= 9 && num >= 1 && num <= 9))
			{
				cout << "数字大小输入错误，请重新输入。" << endl;
				continue;
			}
			else if (!un.valid(row,col,num))
			{
				cout << "数字违反数独规则，请重新输入。" << endl;
				continue;
			}
			else un.tot_num[row - 1][col - 1] = num;
			un.print();
		}
	}
	return 0;
}

void Uni_num::tr_push()
{
	if (full())
	{
		cout << "答案" << ++ans << ":" << endl;
		print();
		return;
	}
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (tot_num[i][j] == 10)
			{
				for (int k = 1; k <= 9; k++)
				{
					if (valid(i + 1, j + 1, k))
					{
						tot_num[i][j] = k;
						tr_push();
						tot_num[i][j] = 10;
					}
					else continue;
				}
				return;
			}
}

void Uni_num::init()
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			tot_num[i][j] = 10;
}

bool Uni_num::valid(int row, int col, int num)
{
	for (int i = 0; i < 9; i++)
		if (num == tot_num[row-1][i] || num == tot_num[i][col-1]) return false;
	int j1 = row - (row - 1) % 3 - 1;
	int j2 = col - (col - 1) % 3 - 1;
	for (int i = j1; i < j1 + 3; i++)
		for (int k = j2; k < j2 + 3; k++)
			if (num == tot_num[i][k]) return false;
	return true;
}

bool Uni_num::full()
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (tot_num[i][j] == 10) return false;
	return true;
}

void Uni_num::print()
{
	cout << "+-+-+-+-+-+-+-+-+-+" << endl;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++) 
			if(tot_num[i][j]!=10) cout << "|" << tot_num[i][j];
			else cout << "| ";
		cout << "|" << endl;
		cout << "+-+-+-+-+-+-+-+-+-+" << endl;
	}
}