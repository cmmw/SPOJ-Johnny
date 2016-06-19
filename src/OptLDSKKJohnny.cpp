//============================================================================
// Name        : Johnny.cpp
// Author      : Christian Wagner
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <cassert>
#include <chrono>

using namespace std;

class packet
{
public:
	packet(long long value, int id) :
			value(value), id(id)
	{
	}

	//Used for std::sort  (sort non decreasing)
	bool operator<(const packet& p2)
	{
		return this->value > p2.value;
	}

	//Used for std::lower_bound (since sorted non decreaseing, '<' should compare for '>')
	bool operator<(const long long value)
	{
		return this->value > value;
	}

	long long value;
	int id;
};

void lds(vector<packet>& packets, vector<vector<int>>& edges);
void _lds(vector<vector<int>>& edges, int k, std::vector<packet>::iterator first, vector<packet>::iterator last, long long sum, int depth);
void print_result();
vector<vector<int>> bestEdges;
//int leaves = 0;
bool quit = false;
chrono::steady_clock::time_point t1;
int main(int argc, char* argv[])
{
	int n;
	vector<packet> packets;
	t1 = chrono::steady_clock::now();
	cin >> n;
	packets.reserve(n);
	bestEdges.reserve(n);
	for (int i = 0; i < n; i++)
	{
		long long p;
		cin >> p;
		packets.push_back( { p, i + 1 });
	}
	std::sort(packets.begin(), packets.end());

//	{	//DBG
//		for (unsigned int i = 0; i < packets.size(); i++)
//		{
//			cout << packets[i].id << ": " << packets[i].value << endl;
//		}
//		cout << "----" << endl;
//	}

	vector<vector<int>> edges(n);
	lds(packets, edges);

	//reconstruct
	print_result();

	return 0;
}

void print_result()
{
	vector<int> partitioning(bestEdges.size(), -1);
	queue<int> q;
	q.push(1);
	partitioning[0] = 0;
	while (!q.empty())
	{
		int id = q.front() - 1;
		q.pop();
		for (unsigned int i = 0; i < bestEdges[id].size(); i++)
		{
			int neighbor = bestEdges[id][i];
			neighbor = (neighbor < 0) ? -neighbor : neighbor;
			if (partitioning[neighbor - 1] == -1)
			{
				neighbor = bestEdges[id][i];
				if (neighbor < 0)	//packet belongs to the same partition as id
				{
					q.push(-neighbor);
					partitioning[-neighbor - 1] = partitioning[id];
				} else
				{
					q.push(neighbor);
					partitioning[neighbor - 1] = partitioning[id] ^ 1;
				}
			}
		}
	}

	//Print result
	for (unsigned int i = 0; i < partitioning.size(); i++)
	{
		if (partitioning[i] == 1)
			cout << i + 1 << endl;
	}

//	cout << "solutions visited: " << leaves << endl;
//	chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(chrono::steady_clock::now() - t1);
//	cout << "time: " << time_span.count() << endl;
}

long long sum = 0;
void lds(vector<packet>& packets, vector<vector<int>>& edges)
{
	auto first = packets.begin();
	auto last = packets.end();
	auto _f = first;
	while (_f != last)
	{
		sum += _f->value;
		_f++;
	}
	unsigned int n = packets.size();
	for (unsigned int k = 0; k < n && !quit; k++)
	{
		_lds(edges, k, first, last, sum, n - 1);
	}
}

long long bestSol;
void _lds(vector<vector<int>>& edges, int k, vector<packet>::iterator first, vector<packet>::iterator last, long long sum, int depth)
{
	if (quit)
	{
		return;
	} else if (last - first == 1)
	{
//		leaves++;
		//leaf
		if (bestEdges.empty() || first->value < bestSol)
		{
			bestEdges = edges;
			bestSol = first->value;
			if (bestSol == 0)
				quit = true;
		}
		return;
	} else
	{
		//prune
		if (first->value >= (sum - first->value))
		{
			//add edges
			auto _f = first + 1;
			while (_f != last)
			{
				edges[first->id - 1].push_back(_f->id);
				edges[_f->id - 1].push_back(first->id);
				_f++;
			}
			_f = last - 1;
			long long val = _f->value;
			_f->value = 2 * first->value - sum;

			_lds(edges, k, _f, last, sum, depth - 1);

			//restore
			_f->value = val;
			_f = first + 1;
			while (_f != last)
			{
				edges[first->id - 1].pop_back();
				edges[_f->id - 1].pop_back();
				_f++;
			}
			return;
		}

		//otpimization
		if (last - first == 4)
		{
			k = 0;
		}

		chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(chrono::steady_clock::now() - t1);
		if (time_span.count() >= 4.900000)
		{
			print_result();
			exit(0);
		}
		//left
		if (depth > k)
		{
			//store id and values to restore them
			auto f1val = (first + 1)->value;
			auto f1id = (first + 1)->id;

			//create edges
			edges[first->id - 1].push_back((first + 1)->id);
			edges[(first + 1)->id - 1].push_back(first->id);

			//calculate new values
			auto diff = first->value - (first + 1)->value;
			long long _sum = sum + diff - first->value - (first + 1)->value;
			auto pos = lower_bound(first + 2, last, diff);
			copy(first + 2, pos, first + 1);
			(pos - 1)->value = diff;
			(pos - 1)->id = first->id;

			//recursive call with (first+1)
			_lds(edges, k, first + 1, last, _sum, depth - 1);

			//restore edges and values
			copy_backward(first + 1, pos - 1, pos);

			(first + 1)->value = f1val;
			(first + 1)->id = f1id;
			edges[first->id - 1].pop_back();
			edges[(first + 1)->id - 1].pop_back();

		}
		/******************************************/
		//right
		if (k > 0)
		{
			//create edges for packets in the same partition
			edges[first->id - 1].push_back(-(first + 1)->id);
			edges[(first + 1)->id - 1].push_back(-first->id);

			//store value and edges to restore them
			long long val = (first + 1)->value;
			int id = (first + 1)->id;
			(first + 1)->value += first->value;
			(first + 1)->id = first->id;

			//recursive call with (first+1)
			_lds(edges, k - 1, first + 1, last, sum, depth - 1);

			//restore value and edges
			(first + 1)->value = val;
			(first + 1)->id = id;
			edges[first->id - 1].pop_back();
			edges[(first + 1)->id - 1].pop_back();
		}

	}
}

