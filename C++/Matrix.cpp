

/* ********************************************************* 
 * header files
 ********************************************************* */
#include"Matrix.h"
#include<iostream>
#include<cstring> // memcpy
#include"numeric.h"



/* ********************************************************* 
 * usings
 ********************************************************* */
using std::cout;
using std::endl;
using std::exit;
using std::memcpy;
using std::memset;




/* ********************************************************* 
 * functions implementations
 ********************************************************* */

/////////////////////////////////////////////////////////
/* Implementation of class Ind member functions */
/////////////////////////////////////////////////////////



/* function:
 * instruction: 
 * input:
 * return:
 *  */
Ind::Ind():ele_num(0), N(0), D(0), data(NULL)
{
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
Ind::Ind(const int num):ele_num(num),N(num), D(1), data(new int[num])
{
}



/* function:
 * instruction: copying construct
 * input:
 * return:
 *  */
Ind::Ind(Ind& ind)
{
    cout << "Ind: copying construct" << endl;

    ele_num = ind.ele_num;
    N = ind.N;
    D = ind.D;

    data = ind.data;
}



/* function:
 * instruction: moving construct
 * input:
 * return:
 *  */
Ind::Ind(Ind&& ind)
{
    cout << "Ind: moving construct" << endl;

    ele_num = ind.ele_num;
    N = ind.N;
    D = ind.D;

    data = ind.data;
    
    ind.N = 0;
    ind.D = 0;
    ind.ele_num = 0;
    ind.data = NULL;
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
Ind& Ind::operator=(Ind&& ind)
{
    cout << "Ind: moving assignment" << endl;

    this->ele_num = ind.ele_num;
    this->N = ind.N;
    this->D = ind.D;
    this->data = ind.data;

    ind.ele_num = 0;
    ind.data = NULL;

    return *this;
}




/* function:
 * instruction: 
 * input:
 * return:
 *  */
Ind::~Ind()
{
    delete[] data;
    cout << "Ind deconstruction" << endl;

    N = 0;
    D = 0;
    ele_num = 0;
    data = NULL;
}




/* function:
 * instruction: 
 * input:
 * return:
 *  */
void Ind::print()
{

    cout << "[" << endl;
    if(ele_num != 0)
        for(long i = 0; i < ele_num; i++)
            cout << data[i] << ", " << endl;
    cout << "]" << endl;

}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
void Ind::free()
{
    delete[] data;
    N = 0;
    D = 0;
    ele_num = 0;
    data = NULL;
}




/* function:
 * instruction: 
 * input:
 * return:
 *  */
void Ind::init(const int num)
{
    ele_num = num;
    N = num;
    D = 1;
    delete [] data;
    data = new int[ele_num];
}





/* function:
 * instruction: 
 * input:
 * return:
 *  */
Ind Ind::randchoice(int batch_size, int N)
{
    Ind res(batch_size);
    for(int i = 0; i < batch_size; i++)
        res.data[i] = rand() % N;

    return std::move(res);
}




/* function:
 * instruction: 
 * input:
 * return:
 *  */
Ind Ind::arange(const int a)
{
    Ind res(a);

    for(int i = 0; i < a; i++)
        res.data[i] = i;

    return std::move(res);
}




/* function:
 * instruction: 
 * input:
 * return:
 *  */
Ind Ind::arange(const int a, const int b)
{
    Ind res(b-a);
    int num;

    num = a;
    for(int i = 0; i < res.ele_num; i++, num++)
        res.data[i] = num;

    return std::move(res);
}





/////////////////////////////////////////////////////////
/* Implementation of class A member functions */
/////////////////////////////////////////////////////////

A& A::operator=(A& a)
{
    cout << "operator = called" <<endl;
    this->N = a.N;
    this->D = a.D;
    free(this->data);
    this->data = (double*)malloc(sizeof(double)*D*N);
    memcpy(this->data, a.data, a.N*a.D*sizeof(double));
    return *this;
}


A& A::operator=(A&& a)
{
    cout << "moving operator = called" <<endl;
    this->N = a.N;
    this->D = a.D;
    free(this->data);
    this->data = a.data;
    a.data = NULL;
    return *this;
}


// A& A::operator=(A& a)
// {
//     cout << "moving operator = called" <<endl;
//     this->N = a.N;
//     this->D = a.D;
//     this->data = a.data;
//     a.data = NULL;
//     return *this;
// }


A::A()
{
    N = 5;
    D = 4;
    data = (double*)malloc(sizeof(double)*N*D);
    cout << "A() called" <<endl;
}

A::A(const A& a)
{
    N = a.N;
    D = a.D;
    cout << "A(A& ) called" <<endl;
    this->data = (double*)malloc(D*N*sizeof(double));
    memcpy(this->data, a.data, D*N);
}


A::A(A&& a)
{
    N = a.N;
    D = a.D;
    data = a.data;
    a.data = NULL;
    cout << "A(A&& ) called" <<endl;
}

A::~A()
{
    cout << "destroying A" <<endl;
    free(data);
}

// A* A::copy()
// {
//     A res;
//     cout << "copying object " << endl;
//     return &res;
// }


void A::print()
{
    const int DD = 5;
    // double *dd;
    //
    // dd = data;

    // double *a = new double[D];

    // d = dynamic_cast<double(*)[D]>(a);

    double (*d)[DD];
    // d = new double[2][5];(double(*)[D])
    // d = static_cast<double (*)[5]>(malloc(sizeof(double)*10));
    d = reinterpret_cast<double (*)[DD]>(data);
    // d = (double(*)[DD])data;
    // int aa[D];


    // d = (double(*)[DD])this->data;
    for(int i = 0; i < N; i++)
        cout << d[i] <<endl;
}
