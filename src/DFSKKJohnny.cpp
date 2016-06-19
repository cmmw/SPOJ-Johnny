////============================================================================
//// Name        : Johnny.cpp
//// Author      : Christian Wagner
//// Version     :
//// Copyright   : Your copyright notice
//// Description : Hello World in C++, Ansi-style
////============================================================================
//
//#include <iostream>
//#include <vector>
//#include <cstdlib>
//#include <algorithm>
//#include <queue>
//#include <cassert>
//#include <chrono>
//
//using namespace std;
//
//class packet
//{
//public:
//	packet(long long value, int id) :
//			value(value)
//	{
//		ids.push_back(id);
//	}
//
//	//Used for std::sort  (sort non decreasing)
//	bool operator<(const packet& p2)
//	{
//		return this->value > p2.value;
//	}
//
//	//Used for std::lower_bound (since sorted non decreaseing, '<' should compare for '>')
//	bool operator<(const long long value)
//	{
//		return this->value > value;
//	}
//
//	long long value;
//	vector<int> ids;			//if contains more than 1 element, this packet is a compounded packet, representing 2 or more packets on the same side
//};
//
//void dfs(vector<packet>& packets, vector<vector<int>>& edges);
//void _dfs(vector<vector<int>>& edges, std::vector<packet>::iterator first, vector<packet>::iterator last, long long sum);
//void print_result();
//vector<vector<int>> bestEdges;
//
//bool quit = false;
//chrono::steady_clock::time_point t1;
//int main()
//{
//	int n;
//	vector<packet> packets;
//	t1 = chrono::steady_clock::now();
//	cin >> n;
//	packets.reserve(n);
//	bestEdges.resize(n);
//	for (int i = 0; i < n; i++)
//	{
//		long long p;
//		cin >> p;
//		packets.push_back( { p, i + 1 });
//	}
//	std::sort(packets.begin(), packets.end());
//
////	{	//DBG
////		for (unsigned int i = 0; i < packets.size(); i++)
////		{
////			cout << packets[i].id << ": " << packets[i].value << endl;
////		}
////		cout << "----" << endl;
////	}
//
//	vector<vector<int>> edges(n);
//	dfs(packets, edges);
//
//	//reconstruct
//	print_result();
//
//	return 0;
//}
//
//void print_result()
//{
//	vector<int> partitioning(bestEdges.size(), -1);
//	queue<int> q;
//	q.push(0);
//	partitioning[0] = 0;
//	while (!q.empty())
//	{
//		int id = q.front();
//		q.pop();
//
//		for (unsigned int i = 0; i < bestEdges[id].size(); i++)
//		{
//			if (partitioning[bestEdges[id][i] - 1] == -1)
//			{
//				q.push(bestEdges[id][i] - 1);
//				partitioning[bestEdges[id][i] - 1] = partitioning[id] ^ 1;
//			}
//		}
//	}
//
//	//Print result
//	for (unsigned int i = 0; i < partitioning.size(); i++)
//	{
//		if (partitioning[i] == 1)
//			cout << i + 1 << endl;
//	}
//
////	chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(chrono::steady_clock::now() - t1);
////	cout << "time: " << time_span.count() << endl;
//}
//
//long long sum = 0;
//void dfs(vector<packet>& packets, vector<vector<int>>& edges)
//{
//	auto first = packets.begin();
//	auto last = packets.end();
//	auto _f = first;
//	while (_f != last)
//	{
//		sum += _f->value;
//		_f++;
//	}
//	_dfs(edges, first, last, sum);
//}
//
//long long bestSol = -1;
//void _dfs(vector<vector<int>>& edges, vector<packet>::iterator first, vector<packet>::iterator last, long long sum)
//{
//	if (quit)
//	{
//		return;
//	} else if (last - first == 1)
//	{
//		//leaf
//		if (bestSol == -1 || first->value < bestSol)
//		{
//			bestEdges = edges;
//			bestSol = first->value;
//			if (bestSol == 0)
//				quit = true;
//		}
//		return;
//	} else
//	{
//		//prune
//		if (first->value >= (sum - first->value))
//		{
//			vector<vector<int>> edgesBackup = edges;
//			auto _f = first + 1;
//			while (_f != last)
//			{
//				for (auto id1 : first->ids)
//				{
//					for (auto id2 : _f->ids)
//					{
//						edges[id1 - 1].push_back(id2);
//						edges[id2 - 1].push_back(id1);
//					}
//				}
//				_f++;
//			}
//
//			_f = last - 1;
//			long long val = _f->value;
//			_f->value = 2 * first->value - sum;
//			_dfs(edges, _f, last, sum);
//			_f->value = val;
//			edges = move(edgesBackup);
//			return;
//		}
//
//		chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(chrono::steady_clock::now() - t1);
//		if (time_span.count() >= 4.9000000)
//		{
//			print_result();
//			exit(0);
//		}
//		//left
//		//store edges, ids and values to restore them
//		vector<vector<int>> e1(first->ids.size());
//		vector<vector<int>> e2((first + 1)->ids.size());
//		for (unsigned int i = 0; i < first->ids.size(); i++)
//			e1[i] = edges[first->ids[i] - 1];
//		for (unsigned int i = 0; i < (first + 1)->ids.size(); i++)
//			e2[i] = edges[(first + 1)->ids[i] - 1];
//		auto f1val = (first + 1)->value;
//		auto f1ids = (first + 1)->ids;
//
//		for (auto id1 : first->ids)
//		{
//			for (auto id2 : (first + 1)->ids)
//			{
//				edges[id1 - 1].push_back(id2);
//				edges[id2 - 1].push_back(id1);
//			}
//		}
//
//		auto diff = first->value - (first + 1)->value;
//		long long _sum = sum + diff - first->value - (first + 1)->value;
//		auto pos = lower_bound(first + 2, last, diff);
//		copy(first + 2, pos, first + 1);
//		(pos - 1)->value = diff;
//		(pos - 1)->ids = first->ids;
//
//		//recursive call with (first+1)
//		_dfs(edges, first + 1, last, _sum);
//
//		//restore edges and values
//		copy_backward(first + 1, pos - 1, pos);
//
//		(first + 1)->value = f1val;
//		(first + 1)->ids = f1ids;
//		for (unsigned int i = 0; i < first->ids.size(); i++)
//			edges[first->ids[i] - 1] = move(e1[i]);
//		for (unsigned int i = 0; i < (first + 1)->ids.size(); i++)
//			edges[(first + 1)->ids[i] - 1] = move(e2[i]);
//
//		/******************************************/
//		//right
//		//store ids to restore them
//		vector<int> ids = (first + 1)->ids;
//		long long val = (first + 1)->value;
//
//		(first + 1)->value += first->value;
//		(first + 1)->ids.insert((first + 1)->ids.end(), first->ids.begin(), first->ids.end());
//
//		//recursive call with (first+1)
//		_dfs(edges, first + 1, last, sum);
//
//		//restore ids and value
//		(first + 1)->value = val;
//		(first + 1)->ids = ids;
//
//	}
//}
//
