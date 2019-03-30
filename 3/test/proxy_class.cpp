#include <iostream>
    #include<iomanip>
    #include<time.h>
    using namespace std;
    void cin_v(int** &mass,int n,int m)
    {
        int x;
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
            {   cout<<i+1<<"x"<<j+1<<" ";
                cin>>x;
                mass[i][j]=x;
            }
    }

    template <class T> 
    
    class Array2D 
    {
    public:
        class ArraylD 
        {
        private:
            int dim2;
            T * Array1;
        public:
            friend class Array2D ;
            ArraylD():Array1(NULL),dim2(0) {}
            T& operator[](int index);// Почему здесь перед T стоит &
            const T& operator[] (int index) const;// и почему здесь &?
        }; //class ArraylD 
    private:
        int dim1;
        ArraylD* Array2;
    public:
        Array2D():dim1(0),Array2(NULL){};
        Array2D(int d1, int d2);
        virtual ~Array2D();
        ArraylD& operator[] (int index)
        {
            return Array2[index];
        }
        const ArraylD& operator[] (int index) const
        {
            return Array2[index];
        }
    };

    
    template <class T>
    T& Array2D<T>::ArraylD::operator[](int index)
    {
        return Array1[index];
    }
    template <class T>
    const T& Array2D<T>::ArraylD::operator[](int index)const
    {
        return Array1[index];
    }
    template <class T>
    Array2D<T>::Array2D(int d1, int d2)
    {
        dim1 = d1;
        Array2 = new ArraylD[dim1];
        for (int i(0);i<d1;++i)
        {
            Array2[i].dim2 = d2;
            Array2[i].Array1 = new T [d2];
        }
    }
    template <class T>
    Array2D<T>::~Array2D()
    {
        for (int i(0);i<dim1;++i)
        {
            delete[]Array2[i].Array1;
        }
        delete[] Array2;
    }

int main()
{   try{
    setlocale(LC_ALL,"rus");
    srand(time(NULL));
    int n,m;
    cout<<"Введите n и m"<<endl;
    cin>>n>>m;
    if(n<1||m<1) throw 100;
    Array2D<int> mass(n,m);

    for(int i = 0; i<n ;cout<<endl,++i)
            for(int j = 0; j<m ;++j)
            {
                if(i==j)
                {
                    mass[i][j]=0;
                }
                else{
                    mass[i][j] = rand()%6;
                }
                cout<<mass[i][j]<<"  ";
            }
    int s[7]={0,0,0,0,0,0,0};
    for(int i=0;i<n;i++)
    {  
      for(int j=0;j<m;j++)
        {
            s[i]+=mass[i][j];
        }
    }
    for(int i=0;i<7;++i)
    { 
        cout<<"Summa"<<i+1<<" "<<"строки  "<<s[i]<<endl;
    }
     int min;
    min=s[0];
    for(int i=0;i<7;++i)
    {
    if(s[i]<min){min=s[i];}
    }
    cout<<"Минимальная сумма  "<<min<<endl;
}catch (int i)
  {cout<<"Исключение где-то неправильные коефициенты"<<endl;}
    system("pause");
    return 0;
}