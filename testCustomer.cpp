// HW10: Test Suite for the Customer Class
// Peter Hurford and Bryan Fowler

#include <gtest/gtest.h>
#include "./Customer.h"
#include <iostream>
#include <string>

using namespace std;

// ----------------------- Test Constructor ----------------------- //
TEST(CustomerTest,EmptyConstructor){	//test empty constructor
    Customer r;
    EXPECT_EQ(0.0,r.time());
    EXPECT_EQ("",r.label());		
}

TEST(CustomerTest,Constructor){		//test constructor
    Customer r(5.2, "First");		//create customer event
    EXPECT_EQ(5.2,r.time());
    EXPECT_EQ("First",r.label());
    Customer r1(1.8, "Second");		//create customer event
    EXPECT_EQ(1.8,r1.time());
    EXPECT_EQ("Second",r1.label());
}

TEST(CustomerTest,PartConstructor){	//test constructor with only time argument
    Customer r(1.3);
    EXPECT_EQ(1.3,r.time());
    EXPECT_EQ("",r.label());
}


// ---------------------------------------------------------------- //
// -------------------------- Test str ---------------------------- //
TEST(CustomerTest,Str){			//test str() function 
    Customer a(3.0, "First");
    string s("<Customer First: 3>");
    EXPECT_EQ(s,a.str());
}

TEST(CustomerTest,EmptyStr){		//test str() function for empty constructor
    Customer a;
    string s("<Customer : 0>");
    EXPECT_EQ(s,a.str());
}


// ---------------------------------------------------------------- //
// -------------------------- Test time ---------------------------- //
TEST(CustomerTest,EmptyTime){		//test time() function for empty constructor 
    Customer a;
    EXPECT_EQ(a.time(),0);
}

TEST(CustomerTest,Time){		//test time() function
    Customer a(4.3);
    EXPECT_EQ(a.time(),4.3);
}

// ---------------------------------------------------------------- //
// -------------------------- Test label ---------------------------- //
TEST(CustomerTest,EmptyLabel){		//test label() function for empty constructor 
    Customer a;
    EXPECT_EQ(a.label(),"");
}

TEST(CustomerTest,Label){		//test label() function 
    Customer a(4.3, "First");
    EXPECT_EQ(a.label(),"First");
}

// ---------------------------------------------------------------- //
// -------------------------- Test settime ---------------------------- //
TEST(CustomerTest,EmptySetTime){	//test setTime() for empty constructor
    Customer r;
    r.setTime(-2.0);			//set time
    EXPECT_EQ(-2,r.time());
    EXPECT_EQ("",r.label());
}

TEST(CustomerTest,SetTime1){		//test setTime()
    Customer r(4.5);
    r.setTime(2);			//set time
    EXPECT_EQ(2,r.time());
    EXPECT_EQ("",r.label());
}

// ---------------------------------------------------------------- //

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
