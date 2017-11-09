

/* ********************************************************* 
 * header files
 ********************************************************* */
#include"Matrix.h"
#include<iostream>
#include<cstring> // memcpy



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
Ind::Ind():ele_num(0), datax(NULL), datay(NULL), slice_start(0), slice_end(0), slice_step(0)
{
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
Ind::Ind(const int num):ele_num(num), datax(new int[num]), datay(new int[num]), slice_start(0), slice_end(0), slice_step(0)
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
    slice_start = ind.slice_start;
    slice_end = ind.slice_end;
    slice_step = ind.slice_step;

    datax = ind.datax;
    datay = ind.datay;
    
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
    slice_start = ind.slice_start;
    slice_end = ind.slice_end;
    slice_step = ind.slice_step;

    datax = ind.datax;
    datay = ind.datay;
    
    // ind.slice_start = 0;
    // ind.slice_end = 0;
    // ind.slice_step = 0;
    // ind.ele_num = 0;
    ind.datax = NULL;
    ind.datay = NULL;
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
    this->slice_start = ind.slice_start;
    this->slice_end = ind.slice_end;
    this->slice_step = ind.slice_step;
    this->datax = ind.datax;
    this->datay = ind.datay;

    ind.slice_start = 0;
    ind.slice_end = 0;
    ind.slice_end = 0;
    ind.ele_num = 0;
    ind.datax = NULL;
    ind.datay = NULL;

    return *this;
}




/* function:
 * instruction: 
 * input:
 * return:
 *  */
Ind::~Ind()
{
    delete[] datax;
    delete[] datay;

    slice_start = 0;
    slice_end = 0;
    slice_end = 0;
    ele_num = 0;
    datax = NULL;
    datay = NULL;
}




/* function:
 * instruction: 
 * input:
 * return:
 *  */
void Ind::print()
{

    if(ele_num != 0)
        for(long i = 0; i < ele_num; i++)
            cout << "(" << datax[i] << ", " << datay[i] << ")" << endl;

}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
void Ind::free()
{
    delete[] datax;
    delete[] datay;
    slice_start = 0;
    slice_end = 0;
    slice_end = 0;
    ele_num = 0;
    datax = NULL;
    datay = NULL;
}




/* function:
 * instruction: 
 * input:
 * return:
 *  */
void Ind::init(const int num)
{
    ele_num = num;
    delete [] datax;
    delete [] datay;
    datax = new int[ele_num];
    datay = new int[ele_num];
}




/* function:
 * instruction: get the slice index with one number, works like a[ar:] in numpy
 * input:
 * return:
 *  */
Ind Ind::slice(int start, int end, int step)
{
    Ind res;

    res.slice_start = start; 
    res.slice_end = end;
    res.slice_step = step;

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
