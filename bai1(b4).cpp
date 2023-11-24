#include<bits/stdc++.h>
using namespace std;

class TinhToan{
	private:
		int a, b;
	public:
		void nhap();
		int in();
};

void TinhToan::nhap(){
	cin>>a>>b;
}
int TinhToan::in(){
	cout<<a+b;
}

int main(){
	TinhToan x;
	x.nhap();
	x.in();

}
