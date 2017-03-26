#include "iostream"
using namespace std;
int main()
{
   double e,t;
      cout<<"请输入上网时间";
      cin>>t;
   if (t<10)
      e=30;
   else if (t<50)
       e=2.5*t;
   else if(t<65)
       e=2*t;
   else 
       e=130;
    cout<<"收费为="<<e<<endl;
    system("pause");
    return 0;
}

​​