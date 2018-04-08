#include<iostream>
#include<ctime>
#include<cstdlib>
#include<math.h>
#include<vector>
#include<algorithm>
using namespace std;
long long gcd(const long long a, const long long b);

long long modAdd( long long a,  long long b,const long long m );

unsigned long long modMult(unsigned long long a, unsigned long long b, unsigned long long mod);

unsigned long long modInv(unsigned long long e, unsigned long long n);

unsigned long long modExp(unsigned long long a, unsigned long long b, unsigned long long mod);

long long disLog(long long a,long long N, long long b);

bool primecheck(unsigned long long a);

void polyresize(vector<int> &A);

vector<int> binMult(const vector<int> &a, const vector<int> &b, const vector<int> &mod);

vector<int> binRem(const vector<int> &res, const vector<int> &mod);

void print(const vector<int> &A);

vector<int> binAdd(const vector<int> &a, const vector<int> &b);

class RSA{
    unsigned long long n,e,d;
    unsigned long long p,q;

    public:
    RSA(){
    n=0;e=0;d=0;
    p=0;q=0;
    }
    void keygen();
    void encryptor();
    void decryptor();
};

void RSA::encryptor()
{
    if(n==0)
    {
        cout<<"\n\tPlease generate a key";
        keygen();
    }
    char message[4];
    unsigned long long m=0,c;

    cout<<"\n\tEnter a message (max 3 characters):";
    cin>>message;
    for(int i=0;message[i]!='\0';i++)
    {
        m+=((int)message[i]-31);
        m*=100;
    }
    m/=100;
    c=modExp(m,e,n);
    cout<<"\n\tEncrypted message is:"<<c;
}

void RSA::decryptor()
{
    char ch;
    if(d==0)
    {
    cout<<"\n\tDo you have the private key?( enter y/n )";
    cin>>ch;
    if(ch=='n')
    return;
    else
    {
        cout<<"\n\tPlease enter the private key:";
        cin>>d;
    }
    }
    unsigned long long c,decrypt;
    char message[4];
    cout<<"\n\tEnter encrypted message:";
    cin>>c;

    decrypt=modExp(c,d,n);  //c is encrypted message, d is private key, n is public key
    unsigned long long temp=decrypt;
    int len=0;              //len is length of message
    while(temp>0)
    {
        temp/=100;
        len++;
    }
    for(int i=len-1;i>=0 && decrypt>0 ;i--)
    {
        message[i]=char((decrypt%100))+31;
        decrypt/=100;
    }
    message[len]='\0';

    cout<<"\n\tDecrypted message is: "<<message;
}

void RSA::keygen()
{
        /* n=pq */
        char ch;
        cout<<"\n\tDo you have 2 prime numbers?enter 'y' or 'n' ";
        cin>>ch;
        if(ch=='y'){
            cout<<"\n\tEnter 2 prime numbers"<<endl;
            cin>>p>>q;
        /* check if p,q is prime */
            while(!(primecheck (p)&&primecheck(q)))
            {
            cout<<"\n\tBoth numbers are not prime \nEnter 2 prime numbers:  ";
            cin>>p>>q;
            }
        }
        else
        {   //randomly generates prime numbers
            srand((unsigned)time(0));
            p=rand();
            q=rand();
            while(!(primecheck (p)&&primecheck(q)))
            {
            p=rand();
            q=rand();
            }

    }
        n=p*q;

        unsigned long long totn=n-p-q+1;  //totn is totient of n
        cout<<"\n\tChoose any integer between 1 and "<<totn<<" that is coprime to "<<totn<<": ";
        cin>>e;
        /* Check e */
        while(!(e<totn&&(gcd(e,totn)==1))){
            cout<<endl<<"\t"<<e<<" is not comprime with "<<totn<<"\nChose another integer  "; cin>>e;
        }
        d=modInv(e,totn);
        cout<<"\n\tDo you want to view the public key?(y/n)";
        cin>>ch;
        if(ch=='y')
        cout<<"\n\tPublic Key: n="<<n<<", Public exponent= "<<e;
        cout<<"\n\tDo you want to view the private key?(y/n)";
        cin>>ch;
        if(ch=='y')
        cout<<"\n\tPrivate Key: Private exponent= "<<d<<" , n= "<<n;
        cout<<"\n\tThe key is now saved.";
    }



int main(){
 int input;
vector <int>a,b,res,modl;
int choice=0;
RSA rsa1;
long long dlog,n1,n2,mod,p;
 do{
    system("cls");
    cout<<"\t \t|||||   |||||    |||    ||||||    |||     \n";
    cout<<"\t \t||      ||        ||    ||  ||     ||     \n";
    cout<<"\t \t||      |||||     ||    ||  ||     ||     \n";
    cout<<"\t \t||         ||     ||    ||  ||     ||     \n";
    cout<<"\t \t|||||   |||||    ||||   ||||||    ||||    \n";
    cout<<"\n \n Project by:  Parthsarathi Samir Khirwadakar (16D070001) \n";
    cout<<"              and \n";
    cout<<"              Sarthak Consul (16D100012) \n\n\n";


    cout<<"\n\n\t\t CRYPTOSUITE\n";
    cout<<"\n\tMAIN MENU:";
    //cout<<"\n\n\t\t Main menu";
    cout<<"\n\t1) Find GCD";
    cout<<"\n\t2) Do Modular Arithmetic";
    cout<<"\n\t3) Encrypt a Message";
    cout<<"\n\t4) Decrypt a Message";
    cout<<"\n\t5) Find Discrete Logarithm";
    cout<<"\n\t6) Prime Field Operations";
    cout<<"\n\t7) Binary Field Operations";
    cout<<"\n\t8) Exit";
    cout<<"\n\n\tEnter choice:";
    cin>>choice;
    switch(choice)
    {
    case 1:
        cout<<"\n\tEnter two integers of which you wish to find GCD:";
        cin>>n1>>n2;
        cout<<"\n\tGCD("<<n1<<" , "<<n2<<" ) = "<<gcd(n1,n2)<<"\n\t";
        system("pause");
        break;
    case 2:
        cout<<"\n\tModular Arithmetic:";
        cout<<"\n\t\t1) Addition";
        cout<<"\n\t\t2) Subtraction";
        cout<<"\n\t\t3) Multiplication";
        cout<<"\n\t\t4) Exponentiation";
        cout<<"\n\t\t5) Inverse";
        cout<<"\n\t\tEnter choice:";
        cin>>choice;
        switch(choice)
        {
            case 1:
                cout<<"\n\tEnter two integers to add:";
                cin>>n1>>n2;
                cout<<"\n\tEnter modulus:";
                cin>>mod;
                cout<<"\n\t("<<n1<<" + "<<n2<<") mod("<<mod<<") = "<<modAdd(n1,n2,mod);
                break;
            case 2:
                cout<<"\n\tEnter two integers to subtract:";
                cin>>n1>>n2;
                n2*=(-1);
                cout<<"\n\tEnter modulus:";
                cin>>mod;
                cout<<"\n\t("<<n1<<" - "<<n2*(-1)<<") mod("<<mod<<") = "<<modAdd(n1,n2,mod);
                break;
            case 3:
                cout<<"\n\tEnter two integers to multiply:";
                cin>>n1>>n2;
                cout<<"\n\tEnter modulus:";
                cin>>mod;
                cout<<"\n\t("<<n1<<" x "<<n2<<") mod("<<mod<<") = "<<modMult(n1,n2,mod);
                break;
            case 4:
                cout<<"\n\tEnter an integer and the exponent:";
                cin>>n1>>n2;
                cout<<"\n\tEnter modulus:";
                cin>>mod;
                cout<<"\n\t("<<n1<<" ^ "<<n2<<") mod("<<mod<<") = "<<modExp(n1,n2,mod);
                break;
            case 5:
                cout<<"\n\tEnter the integer of which you wish to find Modular inverse:";
                cin>>n1;
                cout<<"\n\tEnter modulus";
                cin>>mod;
                cout<<"\n\tInverse of "<<n1<<" mod("<<mod<<") = "<<modInv(n1,mod)<<"\n\t";
                break;
            default: cout<<"\n\tWrong choice";
            break;
        }
        cout<<"\n\t";
        system("pause");
        break;
    case 3:
        rsa1.encryptor();
        cout<<"\n\t";
        system("pause");
        break;
    case 4:
        rsa1.decryptor();
        cout<<"\n\t";
        system("pause");
        break;
    case 5:
    cout<<"\n\tTo find x satisfying a^x mod N = b \n";
    cout<<"\n\tEnter base of logarithm, a="; cin>>n1;
    cout<<"\n\tEnter modulus, N="; cin>>mod;
    cout<<"\n\tEnter the integer of which you wish to find discrete logarithm, b="; cin>>n2;
    dlog=disLog(n1,mod,n2);
    if(dlog==-1) cout<<"\n\tNo discrete logarithm exists";
    else
    cout<<"\n\t"<<n1<<"^x mod("<<mod<<") = "<<n2<<" for x="<<disLog(n1,mod,n2);
    cout<<"\n\t"; system("pause");
    break;
    case 6:
        cout<<"\n\tEnter modulus of the Prime Field (any prime number)";
        cin>>p;
        while(!(primecheck(p)))
            {
            cout<<"\n\tThe number is not prime \n\tEnter a prime number:";
            cin>>p;
            }
        cout<<"\n\tPrime Field Operations:";
        cout<<"\n\t\t1) Addition";
        cout<<"\n\t\t2) Subtraction";
        cout<<"\n\t\t3) Multiplication";
        cout<<"\n\t\t4) Inverse";
        cout<<"\n\t\tEnter choice:";
        cin>>choice;
        mod=p;
        switch(choice)
        {
            case 1:
                cout<<"\n\tEnter two integers (from 0 to "<<p-1<<") to add:";
                cin>>n1>>n2;
                while((n1>=p || n2>=p))
                {
                    cout<<"\n\tIntegers do not belong to this Prime field\n\tEnter again:";
                    cin>>n1>>n2;
                }
                cout<<"\n\t"<<n1<<" + "<<n2<<" = "<<modAdd(n1,n2,p);
                break;
            case 2:
                cout<<"\n\tEnter two integers (from 0 to "<<p-1<<") to subtract:";
                cin>>n1>>n2;
                while((n1>=p || n2>=p))
                {
                    cout<<"\n\tIntegers do not belong to this Prime field\n\tEnter again:";
                    cin>>n1>>n2;
                }
                n2*=(-1);
                cout<<"\n\t"<<n1<<" - "<<n2*(-1)<<" = "<<modAdd(n1,n2,mod);
                break;
            case 3:
                cout<<"\n\tEnter two integers (from 0 to "<<p-1<<") to multiply:";
                cin>>n1>>n2;
                while((n1>=p || n2>=p))
                {
                    cout<<"\n\tIntegers do not belong to this Prime field\n\tEnter again:";
                    cin>>n1>>n2;
                }
                cout<<"\n\t"<<n1<<" x "<<n2<<" = "<<modMult(n1,n2,mod);
                break;
            case 4:
                cout<<"\n\tEnter the integer (from 0 to "<<p-1<<") of which you wish to find inverse:";
                cin>>n1;
                while((n1>=p))
                {
                    cout<<"\n\tInteger does not belong to this Prime field\n\tEnter again:";
                    cin>>n1;
                }
                cout<<"\n\tInverse of "<<n1<<" = "<<modInv(n1,mod)<<"\n\t";
                break;
            default: cout<<"\n\tWrong choice";
            break;
        }
        cout<<"\n\t";
        system("pause");
        break;

    case 7:
        cout<<"\n\tCoefficients of polynomials can only be 0 or 1.\n";
        cout<<"\n\tEnter the modulus polynomial in decreasing order of power(separated by spaces) Enter -1 to stop.\n\t";
        cin>>input;
        while(input==0||input==1){
            modl.push_back(input); cin>>input;
        }

        cout<<"\n\tEnter the first polynomial in decreasing order of power(separated by spaces) Enter -1 to stop.\n\t";
        cin>>input;
        while(input==0||input==1){
            a.push_back(input); cin>>input;
        }

        cout<<"\n\tEnter the second polynomial in decreasing order of power(separated by spaces) Enter -1 to stop.\n\t";
        cin>>input;
        while(input==0||input==1){
            b.push_back(input); cin>>input;
        }

        cout<<"\n\t Binary Field Operations:";
        cout<<"\n\t\t1) Addition";
        cout<<"\n\t\t2) Subtraction";
        cout<<"\n\t\t3) Multiplication";
        cout<<"\n\t\tEnter choice:";
        cin>>choice;

        switch(choice){
        case 1: {
                    cout<<"\n\t(";print(a);cout<<") + (";print(b);cout<<") = (";print(binAdd(a,b));cout<<")\n";
                    break;
                }
        case 2: {
                    cout<<"\n\t(";print(a);cout<<") - (";print(b);cout<<") = (";print(binAdd(a,b));cout<<")\n";
                    break;
                }
        case 3: {
                    cout<<"\n\t(";print(a);cout<<") * (";
                    print(b);
                    cout<<") = (";
                    print(binRem(binMult(a,b,modl),modl));
                    cout<<")\n";
                     break;
                }
   }
   cout<<"\n\t";
   system("pause");
   break;

    case 8:
        break;
    default:
        cout<<"\n\tWrong choice";
        choice=1;
        break;
    }

}while(choice!=8);
return 0;
}

long long gcd(const long long a, const long long b){
    if(a%b==0) return b;
    else
    return gcd(b,a%b);
}

long long modAdd( long long a,  long long b,const long long m ){
    //return ((a%n)+(b%n))%n;
    if(a>m/2) a=(a-m)%m;
    else a=a%m;
    if(b>m/2) b=(b-m)%m;
    else b=b%m;

    if (a+b<0) return m+(a+b)%m;
    else return(a+b)%m;

}

unsigned long long modMult(unsigned long long a, unsigned long long b, unsigned long long mod){
    unsigned long long product = 0;
    a = a % mod;
    while (b > 0)
    {
        // If b is odd, add 'a' to result
        if (b % 2 == 1)
            product = (product + a) % mod;

        a = (a * 2) % mod;
        b /= 2;
    }


    return product % mod;
}


unsigned long long modInv(unsigned long long e, unsigned long long n){
    int  old=0,new=1;
    unsigned long long b=n, c=e, r=2;
    while(r>1){
        unsigned long long q=b/c;
        r=b%c;
        
        unsigned long long temp=old-new*q;
        old=new;
        new=temp;
        b=c;
        c=r;
    }
    if(new2>=0) return new2;
    else return n+new2;
}

unsigned long long modExp(unsigned long long a, unsigned long long b, unsigned long long mod){
    unsigned long long product = 1;
    a = a % mod;
    while (b > 0)
    {
        // If b is odd, add 'a' to result
        if (b % 2 == 1)
            product = (product *a) % mod;

        a = (a*a) % mod;
        b /= 2;
    }


    return product % mod;
}

long long disLog(long long a,long long N, long long b){
    long long k=sqrt(N);
    for(int n=0;n<k;n++){
        for(int m=0; m<k; m++){
        if(m==0&&n==0) continue;
        if(modExp(a,n,N)==((b%N)*modExp(modInv(a,N),m*k,N)) %N) return ((m*k)+n);
        }
    }
    return -1;
}

bool primecheck(unsigned long long a){
    if(a==0||a==1)return 0;
    if(a==2) return 1;
    else if(a==3) return 1;
    else
    for(int i=2;i<=sqrt(a);i++){
        if(a%i==0) return 0;
    }
    return 1;
}

void polyresize(vector<int> &A){
        while (A[0]==0){
            A.erase(A.begin());
        }
}

vector<int> binAdd(const vector<int> &a, const vector<int> &b){
     vector<int> res(max(a.size(),b.size()),0);
    size_t x=a.size(), y=b.size(), z=res.size();
    while(x>0&&y>0){
        res[z-1]=abs((a[x-1]+b[y-1])%2);
        z--;x--;y--;
   }
   if(x>0){
     while(x>0){
        res[z-1]=abs(a[x-1]);
        z--;x--;
     }
   }
   if(y>0){
     while(y>0){
        res[z-1]=abs(b[y-1]);
        z--;y--;
     }
   }

    polyresize(res);
    return res;
}

vector<int> binMult(const vector<int> &a, const vector<int> &b, const vector<int> &mod){
vector<int> res((a.size()+b.size() ),0);
    for(size_t i=0; i<a.size(); i++){
        for(size_t j=0; j<b.size();j++){
            res[res.size()-i-j-1]=(res[res.size()-i-j-1]+a[a.size()-i-1]*b[b.size()-j-1])%2;
        }//coeff of ith power is at ---[n-1-i]

    }
    polyresize(res);
    return res;
}

//Remainder Evaluation
vector<int> binRem(const vector<int> &res, const vector<int> &mod){
    vector<int> quot(mod.size(),0);
    vector<int> rem; rem=res;


    while(rem.size()>=mod.size() ){
        //power =rem.size()-mod.size();
            quot[quot.size()-(rem.size()-mod.size())-1]=1;    //(quot[quot.size()-(rem.size()-mod.size()-1)]+1)%2;
            rem=binAdd(res,binMult(quot,mod,mod)); //subtraction
            polyresize(rem);

        }
        return rem;

}

void print(const vector<int> &A){
    size_t h=0;
    for(size_t g= 0; g<A.size(); g++){
         if(A[g]==1){
            if(h==0) cout<<"z^"<<A.size()-1-g;
            else cout<<" + "<<"z^"<<A.size()-1-g;
            h++;
        }
    }
}
