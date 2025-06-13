#include<bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

void Print(Point *p) {
    cout << "Point coordinates: (" << p -> x << ", " << p -> y << ")" << endl;
}

int main() {
    Point p1 = {10, 20};
    Point p2 = {30, 40};
    Point *ptr = &p2;

    Print(ptr);
}