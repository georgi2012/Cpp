
#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "Vector.h"

SCENARIO("Testing for vector with size 3")
{
    GIVEN("Declr vec with 3")
    {
        Vector a(3);
        WHEN("Add elements ")
        {
            a.putValue(0, 2);
            a.putValue(1, 4);
            a.putValue(2, 0);

            THEN("Are elemenet added")
            {
                CHECK(a.getValue(0) == 2);
                CHECK(a.getValue(1) == 4);
                CHECK(a.getValue(2) == 0);
            }
        }
        a.putValue(0, 2);
        a.putValue(1, 4);
        a.putValue(2, 0);
        WHEN("Test for add method")
        {
            Vector b = a;
            a.add(a);
            THEN("Is it added successfully")
            {
                REQUIRE(a.getValue(0) == b.getValue(0) * 2);
                CHECK(a.getValue(1) == b.getValue(1) * 2);
                CHECK(a.getValue(2) == b.getValue(2) * 2);
            }
        }
        WHEN("Test for += ")
        {
            Vector b = a;
            a += a;
            THEN("+= Worked fine?")
            {
                REQUIRE(a.getValue(0) == b.getValue(0) * 2);
                CHECK(a.getValue(1) == b.getValue(1) * 2);
                CHECK(a.getValue(2) == b.getValue(2) * 2);
            }
        }
        WHEN("Test for []=")
        {
            THEN("It throws error properly")
            {
                try
                {
                    a[a.getSize()] = 4;
                }
                catch (int &num)
                {
                    REQUIRE(num < 0);
                }
            }
            THEN("Does it throw errors when it shouldn't?")
            {
                REQUIRE_NOTHROW(a[a.getSize() - 1] = 4);
                REQUIRE(a[a.getSize() - 1] == 4); 
            }
        }
        WHEN("Test for  == ")
        {
            REQUIRE_FALSE(!(a == a));// not very practical way to test , just wanted to try REQUIRE_FALSE
        }
        WHEN("Test for copy constructor")
        {
            Vector b(a);
            REQUIRE(b.getSize()==a.getSize());
            bool isEqual = true;
            for(int i=0;i< a.getSize();i++)
            {
               if(a[i]!=b[i])
               {
                 isEqual=false;
                 break;
               }
            }
            REQUIRE(isEqual);
        }
        WHEN("Testing if a*5 == 5*a")
        {
            a[0]=1;
            Vector b(a);
             a=5*a;
             b=b*5;
            CHECK(a[0]==b[0]);
            REQUIRE(5*a[0]==a[0]*5);
        }
        WHEN("Testing if a-=a gives the 0 vector ")
        {
            Vector b(a);
            b-=b;
            REQUIRE(b[0]==0);
            REQUIRE(b[1]==0);
            REQUIRE(b[2]==0);
        }
        WHEN("Testing if operator- works")
        {
            Vector b(a);
            a[0]++;
            a[1]++;
            a[2]++;
            b=a-b;
            REQUIRE(b[0]==1);
            REQUIRE(b[1]==1);
            REQUIRE(b[2]==1);
        }
       /* WHEN("Testing if multiple + and - operators work")
        {
            Vector b(a);
            b=a+a-a; 
            //for(int i=0;i<b.getSize();i++)
            //{
            //    std::cout<<b.getValue(i)<<" ";
            //}std::cout<<"\n";
            
            //CHECK(a==b);
            b=a-a+a+a;//=2*a
            for(int i=0;i<b.getSize();i++)
            {
                std::cout<<b.getValue(i)<<" ";
            }std::cout<<"\n";
            //CHECK(b==2*a);
            b=a-(2*a)-(2*a)+(a*2);//=-a
          
        }*/
    } //GIVEN
    GIVEN("Wrong vector size"){
        Vector a(-1);
        THEN("Is size set to 0 automatically?")
        {
            REQUIRE(a.getSize()==0);
        }
    }
    GIVEN("Try running out of memory case")
    {
        Vector a(9000000000); //that will take some time ... RIP RAM
        THEN("Is size set to 0 automatically?")
        {
            REQUIRE(a.getSize()==0);
        }
    }

} //SCEN
