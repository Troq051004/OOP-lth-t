#include <iostream>
#include <cmath>
using namespace std;

class TinhBieuThuc {
	private:
		int a,b,c,d;
		//int a=3,b=4,c=-5,d=6;
	public:
    	int nhap();
    	int xuat();
		int calculate(); 
    
};

int TinhBieuThuc::nhap(){
	//cin>>a;cout<<"+(";cin>>b;cout<<" - abs(";cin>>c;cout<<"))*";cin>>d;
	cin>>a>>b>>c>>d;
	cout << a << "+(" << b << " - abs(" << c << "))*" << d<<endl;
}
int TinhBieuThuc::calculate(){
        return a + (b - abs(-c)) * d;
    }

int TinhBieuThuc::xuat(){
	int kq = calculate();
    cout << kq <<endl;
}

int main() {
	
    TinhBieuThuc x;
    x.nhap();
    x.calculate();
    x.xuat();
    return 0;
}

