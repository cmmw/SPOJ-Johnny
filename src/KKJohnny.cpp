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
//
//using namespace std;
//
//class packet
//{
//public:
//	packet(long long value, int id) :
//			value(value), id(id)
//	{
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
//	int id;
//};
//
//void KK(vector<packet>& packets, vector<vector<int>>& edges);
//
//int main()
//{
//	int n;
//	vector<packet> packets;
//	cin >> n;
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
//	KK(packets, edges);
//
//	//reconstruct
//	vector<int> partitioning(n, -1);
//	queue<int> q;
//	q.push(0);
//	partitioning[0] = 0;
//	while (!q.empty())
//	{
//		int id = q.front();
//		q.pop();
//
//		for (unsigned int i = 0; i < edges[id].size(); i++)
//		{
//			if (partitioning[edges[id][i] - 1] == -1)
//			{
//				q.push(edges[id][i] - 1);
//				partitioning[edges[id][i] - 1] = partitioning[id] ^ 1;
//			} else
//			{
//				assert(partitioning[edges[id][i] - 1] == (partitioning[id] ^ 1));
//			}
//		}
//
//	}
//
////	{	//DBG
////		cout << "----" << endl;
////		int rhv = 0;
////		int lhv = 0;
////		for (unsigned int i = 0; i < packets.size(); i++)
////		{
////			cout << packets[i].id << ": " << packets[i].value << endl;
////			if (packets[i].partition == 0)
////				rhv += packets[i].value;
////			else
////				lhv += packets[i].value;
////		}
////		cout << "---" << endl;
////		cout << abs(rhv - lhv) << endl;
////	}
//
////Print result
//	for (unsigned int i = 0; i < partitioning.size(); i++)
//	{
//		if (partitioning[i] == 1)
//			cout << i + 1 << endl;
//	}
//
//	return 0;
//}
//
//void KK(vector<packet>& packets, vector<vector<int>>& edges)
//{
//	auto first = packets.begin();
//	auto last = packets.end();
//
//	while (last - first > 1)
//	{
//		auto diff = first->value - (first + 1)->value;
//		edges[first->id - 1].push_back((first + 1)->id);
//		edges[(first + 1)->id - 1].push_back(first->id);
//		auto pos = lower_bound(first + 2, last, diff);
//		copy(first + 2, pos, first + 1);
//		(pos - 1)->value = diff;
//		(pos - 1)->id = first->id;
//		first++;
//
////		{	//DBG
////			auto _first = first;
////			while (_first != last)
////			{
////				cout << _first->id << ": " << _first->value << endl;
////				_first++;
////			}
////			cout << "----" << endl;
////		}
//	}
//
//}
//
