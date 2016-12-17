#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <time.h>

using namespace std;

struct Node		//����ʾ��·Ԫ��
{
	int id;		//id��ʶ���	
	int D;		//���ڷ��������ڷ���֮��
	bool flag;	//��ס��ʶ
	int set;	//��������	
};

int ** graph;	//����ͼ��ʾ��·����
Node * node;	//���
int nodeNum;	//������
int * G1;		//����һ
int * G2;		//���ֶ�

//����Dֵ����
int getD(int x);

int main(int argc, char ** argv)
{
	time_t start_time, end_time;
	double cost;
	time(&start_time);
	cout << start_time << endl;
	//���ļ����õ�����ͼ
	fstream fin;
	fin.open("200_1.txt");
	fin >> nodeNum;
	graph = new int*[nodeNum];
	for (int i = 0; i < nodeNum; i++)
	{
		graph[i] = new int[nodeNum];
	}
	for (int i = 0; i < nodeNum; i++)
	{
		for (int j = 0; j < nodeNum; j++)
		{
			fin >> graph[i][j];
		}
	}
	fin.close();

	//step 0
	//��ʼ���ڵ㡢����һ�ͻ��ֶ���ǰ�벿�ֽڵ���뻮��һ����벿�ֽڵ���뻮�ֶ�
	node = new Node[nodeNum];
	int n = nodeNum / 2;
	for (int i = 0; i < nodeNum; i++)
	{
		node[i].id = i;
		node[i].D = 0;
		node[i].flag = false;
		node[i].set = 0;
	}

	G1 = new int[n];
	G2 = new int[n];
	for (int i = 0; i < n; i++)
	{
		G1[i] = i;
		node[i].set = 1;
		G2[i] = n + i;
		node[n + i].set = 2;
	}

	//step 1
	//��temp_G1��temp_G2�ݴ潻����Ļ���
	int* temp_G1;
	int* temp_G2;
	temp_G1 = new int[n];
	temp_G2 = new int[n];
	int temp_gain = 0;
	int final_gain = 0;

	for (int i = 0; i < n; i++)
	{
		temp_G1[i] = G1[i];
		temp_G2[i] = G2[i];
	}

	//step2
	//
	int init = n;
	while (init > 0)
	{
		//����ÿһ���ڵ��Dֵ��������ԸĽ���ÿ�ν�����ֻ��Ҫ���㽻������ڽӵ��Dֵ
		for (int i = 0; i < nodeNum; i++)
		{
			node[i].D = getD(i);
		}


		int max_gain = -10000;
		int temp_a_index = -1;
		int temp_b_index = -1;
		int tempResult0;

		for (int i = 0; i < n; i++)
		{
			if (node[G1[i]].flag == true)
			{
				continue;
			}
			for (int j = 0; j < n; j++)
			{
				if (node[G2[j]].flag == true)
				{
					continue;
				}
				//���㽻��������
				int tempResult = getD(G1[i]) + getD(G2[j]) - 2 * graph[G1[i]][G2[j]];
				if (tempResult > max_gain)
				{
					temp_a_index = i;
					temp_b_index = j;
					max_gain = tempResult;
				}
			}
		}
		//���ҵ��Ľ����������������㽻��������
		node[G1[temp_a_index]].flag = true;
		node[G2[temp_b_index]].flag = true;
		int temp = G1[temp_a_index];
		G1[temp_a_index] = G2[temp_b_index];
		G2[temp_b_index] = temp;
		node[G1[temp_a_index]].set = 1;
		node[G2[temp_b_index]].set = 2;

		init--;

		temp_gain += max_gain;
		if (temp_gain > final_gain)
		{
			final_gain = temp_gain;
			for (int i = 0; i < n; i++)
			{
				temp_G1[i] = G1[i];
				temp_G2[i] = G2[i];
			}
		}
	}

	//��G1��G2������ļ�
	if (freopen("output.txt", "w", stdout) == NULL)
	{
		fprintf(stderr, "error redirecting stdout\n");
	}
	cout << "final_G1 is " << endl;
	for (int i = 0; i < n; i++)
	{
		cout << temp_G1[i] + 1 << ' ';
	}
	cout << endl;
	cout << "final_G2 is " << endl;
	for (int i = 0; i < n; i++)
	{
		cout << temp_G2[i] + 1 << ' ';
	}
	cout << endl;
	
	time(&end_time);
	cost = difftime(end_time, start_time);
	cout << "cost time:" << cost << endl;


	fclose(stdout);
	

	return 0;
}

//����Dֵ������D = ���ڷ��� - ���ڷ���
int getD(int x)
{
	int D = 0;
	for (int i = 0; i < nodeNum; i++)
	{
		if (graph[x][i] == 1)
		{
			if (node[x].set != node[i].set)
			{
				D++;
			}
			else
			{
				D--;
			}
		}
	}
	return D;
}
