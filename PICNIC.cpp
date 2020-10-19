#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;

// 학생 수
int n;

// 친구 쌍 수
int m;

// 짝
int a, b;

// 서로 친구인지 아닌지 확인
bool areFriends[10][10] = { false, };

// 짝을 찾았는지 확인
bool taken[10] = { false, };

int wrongCountPairings(bool taken[]) {
	// 문제점
	// 1. 같은 학생 쌍을 두 번 짝지음
	// 2. 다른 순서로 학생들 짝지어 주는 것을 서로 다른 경우로 셈

	// 기저 사례 : 모든 학생이 짝을 찾았으면 한 가지 방법을 찾았으므로 종료
	bool finished = true;

	for (int i = 0; i < n; ++i)
		if (!taken[i])
			finished = false;

	if (finished)
		return 1;

	// 리턴값
	int ret = 0;

	// 서로 친구인 두 학생을 찾아 짝을 지어줌
	// 1. (0,1)과 (1,0)을 따로 셈
	// 2. (0,1)(2,3)과 (2,3)(0,1)을 따로 셈
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (!taken[i] && !taken[j] && areFriends[i][j]) {
				taken[i] = taken[j] = true;
				ret += wrongCountPairings(taken);
				taken[i] = taken[j] = false;
			}

	return ret;
}

int countPairings(bool taken[]) {
	// 해결책
	// 특정 형태(가장 번호가 빠른 학생의 짝 찾기)를 갖는 답만 셈

	int firstFree = -1;

	// 짝을 맞춰 줄 친구(A)가 짝이 있는지 없는지 확인
	for (int i = 0; i < n; ++i)
		if (!taken[i]) {
			firstFree = i;
			break;
		}

	// 기저 사례 : 모든 학생이 짝을 찾았으면 한 가지 방법을 찾음
	if (firstFree == -1)
		return 1;

	int ret = 0;

	// firstFree : A , pairWith : B
	// A의 짝인 B를 찾아줌
	for (int pairWith = firstFree + 1; pairWith < n; ++pairWith) {
		if (!taken[pairWith] && areFriends[firstFree][pairWith]) {
			taken[firstFree] = taken[pairWith] = true;
			ret += countPairings(taken);
			taken[firstFree] = taken[pairWith] = false;
		}
	}

	return ret;
}

int main() {
	// 반복 시 taken[]과 areFriends[] 항상 초기화
	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		cin >> a >> b;
		areFriends[a][b] = areFriends[b][a] = true;
	}
	cout << countPairings(taken) << endl;
}
