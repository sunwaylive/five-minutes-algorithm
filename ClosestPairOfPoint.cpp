#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

//************************************************************
//1 D closet pair
int closestPairOfPoint1DHelper(int x[], int n, int start, int end){
    int k = end - start;
    if(k == 1) return INT_MAX;
    else if(k == 2) return x[start + 1] - x[start];

    int mid = start + ((end - start) >> 1);
    int l = closestPairOfPoint1DHelper(x, n, start, mid);
    int r = closestPairOfPoint1DHelper(x, n, mid, end);
    int d = min(l, r);
    //左闭右开，左边半段没算到
    d = min(d, x[mid] - x[mid - 1]);
    return d;
}

int closestPairOfPoint1D(int x[], int n){
    sort(x, x + n);
    return closestPairOfPoint1DHelper(x, n, 0, n);
}

// int main()
// {
//     int a[] = {4, 5, 8};
//     const int n = sizeof(a) / sizeof(*a);
//     cout<<closestPairOfPoint1D(a, n)<<endl;
//     return 0;
// }

//************************************************************
//2 D closest pair
//http://www.cnblogs.com/pangblog/p/3304035.html
//https://class.coursera.org/algo-004/lecture/17
struct Point{
    int x, y;
};
const int MAXN = 10000;
Point p[MAXN];

#define dist(p1, p2) sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y))

bool cmp1(Point &a, Point &b){
    return a.x < b.x;
}

bool cmp2(int a, int b){
    return p[a].y < p[b].y;
}

//left closed, right open
double closestPairOfPoint2D(int start, int end){
    int k = end - start;
    if(k == 1) return INT_MAX;
    else if(k == 2) return dist(p[start], p[end - 1]);

    int mid = start + ((end - start) >> 1);
    double l = closestPairOfPoint2D(start, mid);
    double r = closestPairOfPoint2D(mid, end);
    double d = min(l, r);

    //find points in the vertical strip
    vector<int> t;
    for(int i = start; i < end; ++i){
        if((p[i].x - p[mid].x) <= d)
            t.push_back(i);
    }
    sort(t.begin(), t.end(), cmp2);//sort y-coord in Ascending order

    //update the minimum distance
    int c = t.size();
    for(int i = 0; i < c; ++i){
        for(int j = 1; j <= 7 && i + j < c; ++j){//easy proved, see stanford course
            double td = dist(p[i + j], p[i]);
            d = min(d, td);
        }
    }
    return d;
}

int main(){
    int n;
    while(scanf("%d\n", &n) && n){
        for(int i = 0; i < n; ++i){
            scanf("%d %d", &p[i].x, &p[i].y);
        }
        sort(p, p + n, cmp1);// sort by x-coord
        double dist = closestPairOfPoint2D(0, n);
        if(dist > 10000) cout<< "INFINITY"<<endl;
        else cout<<dist<<endl;
    }
    return 0;
}
