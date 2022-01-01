#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <stack>

using namespace  std;


int** create_array(const int n, const int m)
{
	int** arr = new int* [n];
	for (int i = 0; i < n; i++)
	{
		arr[i] = new int[m];
	}
	return arr;
}

void delete_array(int** arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		delete[] arr[i];
	}
	delete arr;
}

void fill_zero(int** arr, int n, int m)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			arr[i][j] = 0;
}

void adjacency_matrix_create(int** input_arr, int** output_arr, int n, int m)
{
	fill_zero(output_arr, n, n);
	for (int i = 0; i < m; i++)
	{
		output_arr[(input_arr[i][0] - 1)][(input_arr[i][1] - 1)] = 1;
	}
}

void show_queue(queue<int> r)
{
	if (r.empty())
		cout << char(30);
	while (!r.empty())
	{
		cout << ++r.front() << ',';
		r.pop();
	}
	cout << endl;
}

void show_stack(stack<int> r)
{
	if (r.empty())
		cout << char(30);
	while (!r.empty())
	{
		cout << ++r.top() << ',';
		r.pop();
	}
	cout << endl;
}


void bfs(queue<int>& q, int* bfs_num, int** adj_matrix, int n)
{
	cout << "Vertex\tBFS-number\tQueue\n";
	cout << q.front() + 1 << "\t1\t\t" << q.front() + 1 << endl;
	int bfs_num_counter = 2;
	while (!q.empty())
	{
		int front = q.front();
		for (int i = 0; i < n; i++)
		{
			if (adj_matrix[front][i] == 1 && bfs_num[i] == 0)
			{
				bfs_num[i] = bfs_num_counter;
				
				q.push(i);
				cout << i + 1<< '\t' << bfs_num_counter << "\t\t";
				show_queue(q);
					bfs_num_counter++;
			}
		}
		q.pop();
		cout << "-\t-\t\t";
		show_queue(q);
	}
}

void dfs(stack<int>& q, int* dfs_num, int** adj_matrix, int n)
{
	cout << "Vertex\tDFS-number\tStack\n";
	cout << q.top() + 1 << "\t1\t\t" << q.top() + 1 << endl;
	int dfs_num_counter = 2;
	while (!q.empty())
	{

		for (int i = 0; i < n; i++)
		{
			if (adj_matrix[q.top()][i] == 1 && dfs_num[i] == 0)
			{
				dfs_num[i] = dfs_num_counter;
				q.push(i);
				cout << i + 1 << '\t' << dfs_num_counter << "\t\t";
				show_stack(q);
				dfs_num_counter++;
				i = -1;
			}
		}
		q.pop();
		cout << "-\t-\t\t";
		show_stack(q);
	}
}

int main()
{
	
	int n, m;
	string s;
	cout << "Create file with the list of edges.\nWhere in first row written a number of vertexes and number of edges.\n";
	cout << "The next lines are given by the vertices that are connected by an edge\n";
	cout << "Example:\n4 5\n1 2\n2 4\n1 4\n4 3\n3 1\n";
	cout << "If you already created ";
	system("pause");
	cout << "Enter the path to the file (example: C:\\\Users\\illia\\Desktop\\TextFile1.txt ): ";
	cin >> s;
	ifstream fin(s);
	fin >> n >> m;
	int** input_arr = create_array(m, 2);
	for (int i = 0; i < m; i++)
	{
		fin >> input_arr[i][0] >> input_arr[i][1];
	}
	fin.close();
	cout << "Reading completed\n";

	int** adj_matrix = create_array(n, n);
	adjacency_matrix_create(input_arr, adj_matrix, n, m);

	char ch;
	cout << "Is graph directed? (y/n): ";
	cin >> ch;

	if(ch=='y')
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (adj_matrix[i][j] == 1)
					adj_matrix[j][i] = 1;
	}

	////// bfs /////
	cout << "BFS\n";
	cout << "Chose begging vertex: ";
	int beginning_vertex;
	cin >> beginning_vertex;
	queue<int> q;
	q.push(beginning_vertex - 1);
	int* bfs_num = new int[n];
	for (int i = 0; i < n; i++)
	{
		bfs_num[i] = 0;
	}
	bfs_num[beginning_vertex - 1 ] = 1;
	bfs(q, bfs_num, adj_matrix, n);

	////// dfs /////
	cout << "DFS\n";
	cout << "Chose begging vertex: ";
	cin >> beginning_vertex;
	stack<int> st;
	st.push(beginning_vertex - 1);
	int* dfs_num = new int[n];
	for (int i = 0; i < n; i++)
	{
		dfs_num[i] = 0;
	}
	dfs_num[beginning_vertex - 1] = 1;
	dfs(st, dfs_num, adj_matrix, n);

	system("pause");
}
