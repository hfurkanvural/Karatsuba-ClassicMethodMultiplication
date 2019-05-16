//
//  main.cpp
//  algo2_hw2
//
//  Created by Hasan Furkan Vural on 15.04.2019.
//  150140029
//  Copyright © 2019 H. Furkan Vural. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

long int multiply(string X, string Y);
int getlength(string &str1, string &str2);
string bitAddition(string xL, string xR);
long int classicmult(string num1, string num2);


int main(int argc, const char * argv[]) {

    string rand1nums[5] = {"1001","10100", "10101101", "1101011011", "101010011001" };
    string rand2nums[5] = {"1011","10010", "10101101", "11011111011", "10101011011" };

    ofstream outp("output.txt", ofstream::out);
    if(outp.is_open())
    {
        int i= 0;
    while (i < 5)
    {  
        clock_t begin = clock();
        long int x = multiply(rand1nums[i],rand2nums[i]);
        clock_t end = clock();
        double elapsedtime= double(end-begin)/ CLOCKS_PER_SEC;
        outp<<"defined:" << x << ":"<< elapsedtime<<"\n";
        cout<<"defined:" << x << ":"<< elapsedtime<<"\n";
         begin = clock();
        x = classicmult(rand1nums[i],rand2nums[i]);
         end = clock();
        elapsedtime= double(end-begin)/ CLOCKS_PER_SEC;
        outp<<"clasic:" << x << ":"<< elapsedtime<<"\n";
        cout<<"clasic:" << x << ":"<< elapsedtime<<"\n";
        i++;
    }
    }
    outp.close();



    return 0;
}

long int multiply(string x, string y)
{
    // gets largest size of string and make equal their sizes.
    int maxsize = getlength(x,y);
    int middle = maxsize/2;
    
    // check for error of no number inserted case.
    if (maxsize == 0) return 0;
    
    // by substracting with '0', we'll find the integer value of character.
    if (maxsize == 1) {return (x[0] -'0') * ( y[0] -'0');}
    
    // Find the left and right half of string x
    string xL = x.substr(0, middle);
    string xR = x.substr(middle, maxsize-middle);
    
    // Find the left and right half of string y
    string yL = y.substr(0, middle);//getLeftHalf(y);
    string yR = y.substr(middle, maxsize-middle);//getRightHalf(y);
    
    long int P1 = multiply(xL, yL);
    long int P2 = multiply(xR, yR);
    long int P3 = multiply(bitAddition(xL, xR), bitAddition(yL, yR));
    
    //I've used bit shifting operation to get 2^n and 2^n/2
    return P1*(1<<(2*(maxsize-middle))) + (P3 - P1 - P2)*(1<<(maxsize-middle)) + P2;
}


string bitAddition(string xL, string xR)
{
    //get half parts of string's maxsize.
    int maxsize = getlength(xL,xR);// (xL.length() > xR.length()) ? xL.length() : xR.length();
    int carryBit = 0;
    string xLxR;
    
    //adding operation, bit by bit
    for (int i = maxsize-1 ; i >= 0 ; i--)
    {
        int leftBit = (xL[i] - '0');
        int rightBit = (xR[i]- '0');
        
        // xOR opeartion to calculate sum with carry bit.
        int sum = (leftBit ^ rightBit ^ carryBit) + '0';
        
        // inserting bit into a string.
        xLxR = char(sum) + xLxR;
        
        // finding carry bit's last status.
        carryBit = (leftBit&rightBit) | (rightBit&carryBit) | (leftBit&carryBit);
    }
    
    // check for overflow.
    if (carryBit)
    {
        xLxR = '1' + xLxR;
    }
    return xLxR;
}

int getlength(string &str1, string &str2) 
{ 
    int len1 = str1.size(), len2 = str2.size(); 

    // I make equal the size of numbers in binary by adding 0 in front of string. So I can have half of strings in equal size.
    if (len1 < len2) 
    { 
        for (int i = 0 ; i < len2 - len1 ; i++) 
            str1 = '0' + str1;
        //returns max string length 
        return len2; 
    } 
    else  
    { 
        for (int i = 0 ; i < len1 - len2 ; i++) 
            str2 = '0' + str2; 
        //returns max string length
        return len1;
    }  
} 

long int classicmult(string num1, string num2) 
{ 
    int n1 = num1.size(); 
    int n2 = num2.size(); 
    if (n1 == 0 || n2 == 0) 
    return 0; 

    string result;
    result.append(max(n1,n2)+2, '0');
    cout<<result<<endl;
    int digitnum1=0;
    int digitnum2=0;

   // Go from right to left in num1 
    for (int i=n1-1; i>=0; i--) 
    { 
        int carry = 0;
        digitnum2=0; 
        for (int j=n2-1; j>=0; j--) 
        { 
            int fb = num1[i] - '0'; 
            int sb = num2[j] - '0';
            int tb = result[digitnum1+digitnum2] -'0';
            int sum = ((fb & sb) ^ carry);
            //carry = ((fb & sb)&tb) | (tb&carry) | ((fb & sb)&carry);
            // if ((sum + (result[digitnum1+digitnum2] - '0')) != 0) carry = 1;
            result[digitnum1+digitnum2] = char (((sum + tb)%2)+'0');
            carry = (sum + tb)/2;
            digitnum2++;
        }
        digitnum1++;
    } 
   
    // ignore '0's from the right 
    int i = result.size() - 1; 
    string s = ""; 
       
    while (i >= 0)
        s += result[i--];
    if (s[0] == '0') s = s.substr(1);
    long int retval= stoull(s,0,2);
    return retval;
}
