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
//#include <cmath>
//#include <chrono>
//#include <cstdlib>
//#include <algorithm>
//using namespace std;
//
//class packet
//{
//public:
//	packet(long long value, unsigned int hand, int id) :
//			value(value), hand(hand), id(id)
//	{
//	}
//
//	bool operator<(const packet& p2)
//	{
//		return this->value > p2.value;
//	}
//
//	long long value;
//	unsigned int hand;		//0 = right, 1 = left
//	int id;
//};
//
//void ils(vector<packet>& packets, int rhv, int lhv);
//void perturb(vector<packet>& packets, int& rhv, int& lhv);
//int localSearch(vector<packet>& packets, int rhv, int lhv);
//
//chrono::steady_clock::time_point t1;
//int _count = 0;
//int _perturbSize = 0;
//int main()
//{
//	srand(time(NULL));
//	vector<packet> packets;
//	cin >> _count;
//	_perturbSize = (_count / 10) + 1;
//	for (int i = 0; i < _count; i++)
//	{
//		long long p;
//		cin >> p;
//		packets.push_back( { p, 0, i + 1 });
//	}
//
//	std::sort(packets.begin(), packets.end());
//
//	int rhv = 0, lhv = 0;
//	for (int i = 0; i < _count; i++)
//	{
//		packet& p = packets[i];
//		if (rhv < lhv)
//		{
//			p.hand = 0;
//			rhv += packets[i].value;
//		} else
//		{
//			p.hand = 1;
//			lhv += packets[i].value;
//		}
//	}
//
//	t1 = chrono::steady_clock::now();
//
////	{	//DBG
////		for (unsigned int i = 0; i < packets.size(); i++)
////		{
////			cout << packets[i].id << "/" << packets[i].hand << ": " << packets[i].value << endl;
////		}
////		cout << "----" << endl;
////	}
//
//	ils(packets, rhv, lhv);
//
////	{	//DBG
////		cout << "----" << endl;
////		rhv = lhv = 0;
////		for (unsigned int i = 0; i < packets.size(); i++)
////		{
////			cout << packets[i].id << "/" << packets[i].hand << ": " << packets[i].value << endl;
////			if (packets[i].hand == 0)
////				rhv += packets[i].value;
////			else
////				lhv += packets[i].value;
////		}
////		cout << "---" << endl;
////		cout << abs(rhv - lhv) << endl;
////	}
//
//	for (unsigned int i = 0; i < packets.size(); i++)
//	{
//		const packet& p = packets[i];
//		if (p.hand == 1)
//			cout << p.id << endl;
//	}
//
//	return 0;
//}
//
//void ils(vector<packet>& packets, int rhv, int lhv)
//{
//	int val = localSearch(packets, rhv, lhv);		//initial solution
//	while (true)
//	{
//		int _rhv = rhv;
//		int _lhv = lhv;
//		vector<packet> curSol = packets;
//
//		perturb(curSol, _rhv, _lhv);
//
//		int tmp = localSearch(curSol, rhv, lhv);
//		if (tmp < val)
//		{
//			val = tmp;
//			packets = curSol;
//			rhv = _rhv;
//			lhv = _lhv;
//		}
//
//		chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(chrono::steady_clock::now() - t1);
//		if (time_span.count() >= 4.4000000)
//			return;
//	}
//}
//
//void perturb(vector<packet>& packets, int& rhv, int& lhv)
//{
//	for (int i = 0; i < _perturbSize; i++)
//	{
//		int idx = rand() % packets.size();
//		packet& p = packets[idx];
//		if (p.hand == 0)
//		{
//			rhv -= p.value;
//			lhv += p.value;
//			p.hand = 1;
//		} else
//		{
//			rhv += p.value;
//			lhv -= p.value;
//			p.hand = 0;
//		}
//	}
//}
//
//int localSearch(vector<packet>& packets, int rhv, int lhv)
//{
//	int val = abs(rhv - lhv);
//	while (true)
//	{
//		if (val == 0)
//			break;
//
//		int bestVal = val;
//		int bestIdx = -1;
//		int moveTo = -1;
//		for (unsigned int i = 0; i < packets.size(); i++)
//		{
//			packet& p = packets[i];
//			if (rhv > lhv)
//			{
//				if (p.hand == 0)
//				{
//					int tmp = abs((rhv - p.value) - (lhv + p.value));
//					if (tmp < bestVal)
//					{
//						bestVal = tmp;
//						bestIdx = i;
//						moveTo = 1;
//					}
//				}
//			} else
//			{
//				if (p.hand == 1)
//				{
//					int tmp = abs((rhv + p.value) - (lhv - p.value));
//					if (tmp < bestVal)
//					{
//						bestVal = tmp;
//						bestIdx = i;
//						moveTo = 0;
//					}
//				}
//			}
//		}
//		if (bestIdx != -1)
//		{
//			packets[bestIdx].hand = moveTo;
//			val = bestVal;
//		} else
//		{
//			break; //local optimum
//		}
//	}
//	return val;
//}
