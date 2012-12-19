#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cassert>
#include <sstream>
#include <numeric>
#include <climits>
#include <string>
#include <cctype>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <vector>
#include <queue>
#include <list>
#include <map>
#include <set>
using namespace std;

typedef pair<int, int> Interval;
typedef unsigned long long qword;

const int P = int(1e5) + 7;
const int MAX_N = int(1e5) + 10;

struct Answer {
	int totalLength;
	vector<Interval> v;
	Answer() {
		v.clear();
		normalize();
	}
	void normalize() {
		sort(v.begin(), v.end());
		totalLength = 0;
		for (int i = 0; i < (int)v.size(); ++i)
			totalLength += v[i].second - v[i].first + 1;
	}
	bool operator <(const Answer &o) const {
		return totalLength < o.totalLength;
	}
};

inline void update(Answer &x, const Answer &t) {
	if (x < t)
		x = t;
}

int n;
char input[MAX_N];
int earliest[MAX_N];
qword pPower[MAX_N], prefix[MAX_N], suffix[MAX_N];

inline qword hashValue(qword *h, int l, int r, int length) { //(l, r]
	return h[r] - h[l] * pPower[length];
}

int main() {
	gets(input + 1);
	n = strlen(input + 1);
	pPower[0] = 1ULL;
	for (int i = 1; i <= n; ++i) {
		pPower[i] = pPower[i - 1] * P;
		prefix[i] = prefix[i - 1] * P + input[i];
	}
	for (int i = n; i >= 1; --i) {
		suffix[i] = suffix[i + 1] * P + input[i];
	}
	for (int i = n, j = 1; i >= 1; --i) {
		int length = n - i + 1;
		for (; j <= n && (j < length || hashValue(prefix, j - length, j, length) != hashValue(suffix, n + 1, i, length)); j++);
		earliest[i] = j;
	}
	Answer result;
	result.normalize();
	for (int i = 1; i <= n; ++i) {
		int longest = 1, l = 2, r = min(i, n - i + 1), pos = n + 1;
		while (l <= r) {
			int mid = l + r >> 1;
			if (hashValue(prefix, i - mid, i, mid) == hashValue(suffix, i + mid, i, mid))
				longest = mid, l = mid + 1;
			else
				r = mid - 1;
		}
		l = i + longest, r = n;
		while (l <= r) {
			int mid = l + r >> 1;
			if (earliest[mid] <= i - longest)
				pos = mid, r = mid - 1;
			else
				l = mid + 1;
		}
		Answer temp;
		temp.v.push_back(Interval(i - longest + 1, i + longest - 1));
		if (pos <= n) {
			temp.v.push_back(Interval(pos, n));
			temp.v.push_back(Interval(earliest[pos] - (n - pos), earliest[pos]));
		}
		temp.normalize();
		update(result, temp);
	}
	printf("%d\n", (int)result.v.size());
	for (int i = 0; i < (int)result.v.size(); ++i)
		printf("%d %d\n", result.v[i].first, result.v[i].second - result.v[i].first + 1);
}
