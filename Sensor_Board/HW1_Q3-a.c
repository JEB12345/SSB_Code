/* 
 * File:   HW1_Q3-a.c
 * Author: jonathan
 *
 * Created on April 21, 2014, 10:14 AM
 */


// Initalize all register values here

void Question3a()
{
    for(r3=0;r3!=32768;r3+4){
        r2 = r0[r3];
        ip = r2^2;
        if(r2 <= 29){
            r1[r3] = r2;
        }
        else{
            ip = r4 * ip;
            r1[r3] = ip;
        }
    }
}