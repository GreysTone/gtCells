// Data Evolution 
// Author : GreysTone
// Copyright (C) 2007 - 2011 GreysTone.
// July 8th, 2011

#include <iostream>
#include <cstring>
using namespace std;

char DNA[26], evo[50001], fal[50001];
int err = 0, ave_last = -1, ave_now = -1, len, age = -1, aveg[50001], evocpy[50001], evocpyid[50001];
int errstop = 0;
bool stop = false;

void rando()
{
    srand ((int) time (NULL));
}

void QuickSort(int b, int e)
{
    int _L, _R, t, t1;
    if( b >= e ) return ;
    t = evocpy[b];
    t1 = evocpyid[b];
    _L = b;
    _R = e;
    while( _L < _R )
    {
        while( _L < _R && evocpy[_R] >= t ) _R--;
        {
            evocpy[_L] = evocpy[_R];
            evocpyid[_L] = evocpyid[_R];
        }
        while( _L < _R && evocpy[_L] <= t ) _L++;
        {
            evocpy[_R] = evocpy[_L];
            evocpyid[_R] = evocpyid[_L];
        }
    }
    evocpy[_L] = t;
    evocpyid[_L] = t1;
    QuickSort( b , _L - 1 );
    QuickSort( _L + 1 , e );
}

void printb(int b, int e, int _sign)
{
    int i;
    if ( _sign == 0 )
    {
        /**/cout/**/ /*ouf*/ << "   | [EVO] ";                                              ///**/cout/**/ ouf
        for ( i = b ; i <= e ; i++ )
            /**/cout/**/ /*ouf*/ << evo[i];
        /**/cout/**/ /*ouf*/ << " [AGE]" << age << endl;
    }
    else return ;
}

int ave()
{
    int i, sum = 0;

    for ( i = 0 ; i < len ; i++ )
    {
        if ( fal[i] > evo[i] )
        {
            aveg[i] = fal[i] - evo[i];
            sum += aveg[i];
        }
        else
        {
            aveg[i] = evo[i] - fal[i];
            sum += aveg[i];
        }
    }

    return sum;
}

void AGE0()
{
    int i;

    rando();

    for ( i = 0 ; i <= 25 ; i++ )
        DNA[i] = 'A' + i;
    for ( i = 0 ; i < len ; i++ )
        evo[i] = DNA[rand() % 26];

    age = 0;
    ave_last = ave();
    errstop = len * 1000;
    printb(0, len, 0);
}

void JudgeStop()
{
    if ( err >= errstop )
    {
        stop = true;
        /**/cout/**/ /*ouf*/ << "   | [ERR] " << err << " Sorry, Evolution STOP.\n";
    }
    else
    {
        ave_now = ave();
        if ( ave_now >= ave_last ) err += 1;
        if ( ave_now == 0 )
        {
            stop = true;
            /**/cout/**/ /*ouf*/ << "   | [OVE] Congratulations! A Totally Evolution.\n";
        }
        //if ( err/(errstop * 1.0) >= 0.7 && ave_now <= 26 )
        //{
        //     stop = true;
        //     /*cout/**/ /*ouf*/ << "   | [OER] Sorry, This is a Half Evolution.\n";
        //}
        ave_last = ave_now;
    }
}

void Ali(int _sign)
{
    evo[_sign] = DNA[rand() % 26];
}

void Trush()
{
    int max = -1, max2 = -1, max3 = -1, i, _s1 = -1, _s2 = -1, _s3 = -1, crgnum;
    int crg[1600];

    if ( len <= 5 )
    {
        for ( i = 0 ; i < len ; i++ )
        {
            if ( aveg[i] > max )
            {
                max = aveg[i];
                _s1 = i;
            }
        }
        Ali(_s1);
    }
    if ( len > 5 && len <= 8 )
    {
        for ( i = 0 ; i < len ; i++ )
        {
            evocpy[i] = aveg[i];
            evocpyid[i] = i;
        }
        QuickSort( 0 , len - 1 );

        _s1 = evocpyid[len - 1];
        _s2 = evocpyid[len - 2];

        Ali(_s1);
        if ( aveg[_s2] != 0 ) Ali(_s2);
    }
    if ( len > 8 && len <= 10 )
    {
        for ( i = 0 ; i < len ; i++ )
        {
            evocpy[i] = aveg[i];
            evocpyid[i] = i;
        }
        QuickSort( 0 , len - 1 );

        _s1 = evocpyid[len - 1];
        if ( aveg[_s2] != 0 ) _s2 = evocpyid[len - 2];
        if ( aveg[_s3] != 0 ) _s3 = evocpyid[len - 3];

        Ali(_s1);
        Ali(_s2);
        Ali(_s3);
    }
    if ( len > 10 )
    {
        crgnum = (int)(len * 0.3) + 1;
        for ( i = 0 ; i < crgnum ; i++ ) crg[i] = 0;

        for ( i = 0 ; i < len ; i++ )
        {
            evocpy[i] = aveg[i];
            evocpyid[i] = i;
        }
        QuickSort( 0 , len - 1 );

        for ( i = 0 ; i < crgnum ; i++ )
        {
            crg[i] = evocpyid[len - 1 - i];
            if ( aveg[crg[i]] != 0 ) Ali(crg[i]);
        }
    }
}

int main()
{
    cout << "   | Enter : ";
    cin >> fal;
    len = strlen(fal);
    cout << "   | Get " << len << " chars.\n";
    cout << "   | [SYS] Evolution Start...\n";

    AGE0();

    while ( stop != true )
    {
        JudgeStop();
        if ( stop == true) continue;

        Trush();

        age++;
        printb(0, len, 0);
    }

    return 0;
}
