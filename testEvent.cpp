// HW10: Test Suite for the Event Class
// Peter Hurford and Bryan Fowler

#include <gtest/gtest.h>
#include "Event.h"
#include <iostream>
#include <string>

using namespace std;

// ----------------------- Test Constructor ----------------------- //
TEST(EventTest, DefaultConstructor) {
    Event e;                        // Construct an event using the default constructor
    EXPECT_EQ(0, e.id());           // Expect id to be 0
    EXPECT_EQ(-1.0, e.time());      // Expect time to be -1.0
}

TEST(EventTest, SetConstructor) {
    Event e(1, 3.0);                // Construct an event using arguments
    EXPECT_EQ(1, e.id());           // Expect id to be 1
    EXPECT_EQ(3.0, e.time());       // Expect time to be 3.0
}

TEST(EventTest, ConstructorIntToFloat) {
    Event e(1, 3);                  // Construct an event using int arguments
    EXPECT_EQ(1, e.id());           // Expect id to be 1
    EXPECT_EQ(3.0, e.time());       // Expect time to be 3.0
}

TEST(EventTest, HalfConstructor) {
    Event e(1);                     // Construct an event with only one argument
    EXPECT_EQ(1, e.id());           // Expect id to be 1 (as defined)
    EXPECT_EQ(-1.0, e.time());      // Expect time to be -1.0 (as per default constructor)
}


// -------------------------- Test str ---------------------------- //
TEST(EventTest, Str) {
    Event e(1, 3);
    string s("<Event 1: 3>");
    EXPECT_EQ(s, e.str());          // Expect string of id=1, time=3 to be <Event 1: 3.0>
}

TEST(EventTest, NegativeStr) {
    Event e;
    string s("<Event 0: -1>");
    EXPECT_EQ(s, e.str());          // Expect default constructor string to be <Event 0: -1.0>
}


// -------------------------- Test < operator overload ---------------------------- //
TEST(EventTest, LessThan){
    Event e1(1, 1);
    Event e2(2, 2);
    Event e3(3, 2);
    EXPECT_TRUE(e1 < e2);   // Lesser events are less than
    EXPECT_FALSE(e2 < e1);  // Greater events are not less than
    EXPECT_FALSE(e3 < e2);  // Equal events are not less than
}

TEST(EventTest, LessThanNegatives){
    Event e1(1, -2);
    Event e2(2, -1);
    Event e3(3, -1);
    EXPECT_TRUE(e1 < e2);   // Lesser events are less than
    EXPECT_FALSE(e2 < e1);  // Greater events are not less than
    EXPECT_FALSE(e3 < e2);  // Equal events are not less than
}

TEST(EventTest, LessThanFloats){
    Event e1(1, 1.1);
    Event e2(2, 1.4);
    Event e3(3, 1.4);
    EXPECT_TRUE(e1 < e2);   // Lesser events are less than
    EXPECT_FALSE(e2 < e1);  // Greater events are not less than
    EXPECT_FALSE(e3 < e2);  // Equal events are not less than
}


// -------------------------- Test > operator overload ---------------------------- //
TEST(EventTest, GreaterThan){
    Event e1(1, 1);
    Event e2(2, 2);
    Event e3(3, 2);
    EXPECT_FALSE(e1 > e2);   // Lesser events are not greater than
    EXPECT_TRUE(e2 > e1);  // Greater events are greater than
    EXPECT_FALSE(e3 > e2);  // Equal events are not greater than
}

TEST(EventTest, GreaterThanNegatives){
    Event e1(1, -2);
    Event e2(2, -1);
    Event e3(3, -1);
    EXPECT_FALSE(e1 > e2);   // Lesser events are not greater than
    EXPECT_TRUE(e2 > e1);  // Greater events are greater than
    EXPECT_FALSE(e3 > e2);  // Equal events are not greater than
}

TEST(EventTest, GreaterThanFloats){
    Event e1(1, 1.1);
    Event e2(2, 1.4);
    Event e3(3, 1.4);
    EXPECT_FALSE(e1 > e2);   // Lesser events are not greater than
    EXPECT_TRUE(e2 > e1);  // Greater events are greater than
    EXPECT_FALSE(e3 > e2);  // Equal events are not greater than
}


// -------------------------- Test <= operator overload ---------------------------- //
TEST(EventTest, LessThanEqual){
    Event e1(1, 1);
    Event e2(2, 2);
    Event e3(3, 2);
    EXPECT_TRUE(e1 <= e2);   // Lesser events are less than / equal
    EXPECT_FALSE(e2 <= e1);  // Greater events are not less than / equal
    EXPECT_TRUE(e3 <= e2);  // Equal events are less than / equal
}

TEST(EventTest, LessThanEqualNegatives){
    Event e1(1, -2);
    Event e2(2, -1);
    Event e3(3, -1);
    EXPECT_TRUE(e1 <= e2);   // Lesser events are less than / equal
    EXPECT_FALSE(e2 <= e1);  // Greater events are not less than / equal
    EXPECT_TRUE(e3 <= e2);  // Equal events are less than / equal
}

TEST(EventTest, LessThanEqualFloats){
    Event e1(1, 1.1);
    Event e2(2, 1.4);
    Event e3(3, 1.4);
    EXPECT_TRUE(e1 <= e2);   // Lesser events are less than / equal
    EXPECT_FALSE(e2 <= e1);  // Greater events are not less than / equal
    EXPECT_TRUE(e3 <= e2);  // Equal events are less than / equal
}


// -------------------------- Test >= operator overload ---------------------------- //
TEST(EventTest, GreaterThanEqual){
    Event e1(1, 1);
    Event e2(2, 2);
    Event e3(3, 2);
    EXPECT_FALSE(e1 >= e2); // Lesser events are not greater than / equal
    EXPECT_TRUE(e2 >= e1);  // Greater events are greater than / equal
    EXPECT_TRUE(e3 >= e2);  // Equal events are not greater than / equal
}

TEST(EventTest, GreaterThanEqualNegatives){
    Event e1(1, -2);
    Event e2(2, -1);
    Event e3(3, -1);
    EXPECT_FALSE(e1 >= e2); // Lesser events are not greater than / equal
    EXPECT_TRUE(e2 >= e1);  // Greater events are greater than / equal
    EXPECT_TRUE(e3 >= e2);  // Equal events are greater than / equal
}

TEST(EventTest, GreaterThanEqualFloats){
    Event e1(1, 1.1);
    Event e2(2, 1.4);
    Event e3(3, 1.4);
    EXPECT_FALSE(e1 >= e2); // Lesser events are not greater than / equal
    EXPECT_TRUE(e2 >= e1);  // Greater events are greater than / equal
    EXPECT_TRUE(e3 >= e2);  // Equal events are not greater than / equal
}


// -------------------------- Test == operator overload ---------------------------- //
TEST(EventTest, Equal){
    Event e1(1, 1);
    Event e2(2, 2);
    Event e3(3, 2);
    EXPECT_FALSE(e1 == e2); // Lesser events are not equal
    EXPECT_FALSE(e2 == e1);  // Greater events are not equal
    EXPECT_TRUE(e3 == e2);  // Equal events are equal
}

TEST(EventTest, EqualNegatives){
    Event e1(1, -2);
    Event e2(2, -1);
    Event e3(3, -1);
    EXPECT_FALSE(e1 == e2); // Lesser events are not equal
    EXPECT_FALSE(e2 == e1);  // Greater events are not equal
    EXPECT_TRUE(e3 == e2);  // Equal events are equal
}

TEST(EventTest, EqualFloats){
    Event e1(1, 1.1);
    Event e2(2, 1.4);
    Event e3(3, 1.4);
    EXPECT_FALSE(e1 == e2); // Lesser events are not equal
    EXPECT_FALSE(e2 == e1);  // Greater events are not equal
    EXPECT_TRUE(e3 == e2);  // Equal events are equal
}


// -------------------------- Test != operator overload ---------------------------- //
TEST(EventTest, NotEqual){
    Event e1(1, 1);
    Event e2(2, 2);
    Event e3(3, 2);
    EXPECT_TRUE(e1 != e2); // Lesser events are not equal
    EXPECT_TRUE(e2 != e1);  // Greater events are not equal
    EXPECT_FALSE(e3 != e2);  // Equal events are not not equal
}

TEST(EventTest, NotEqualNegatives){
    Event e1(1, -2);
    Event e2(2, -1);
    Event e3(3, -1);
    EXPECT_TRUE(e1 != e2); // Lesser events are not equal
    EXPECT_TRUE(e2 != e1);  // Greater events are not equal
    EXPECT_FALSE(e3 != e2);  // Equal events are not not equal
}

TEST(EventTest, NotEqualFloats){
    Event e1(1, 1.1);
    Event e2(2, 1.4);
    Event e3(3, 1.4);
    EXPECT_TRUE(e1 != e2); // Lesser events are not equal
    EXPECT_TRUE(e2 != e1);  // Greater events are not equal
    EXPECT_FALSE(e3 != e2);  // Equal events are not not equal
}


// -------------------------- Test settime ---------------------------- //
TEST(EventTest, SetTime) {
    Event e;                        // Create an event with default constructor
    EXPECT_EQ(-1.0, e.time());      // Expect time to be -1.0 (as per default)
    e.setTime(3);                   // Use set time to change time to 3
    EXPECT_EQ(3.0, e.time());      // Expect time to now be 3.0 (as per set)
}


// -------------------------- Test execute ---------------------------- //
TEST(EventTest, Execute) {
    Event e;                        // Create an event with default constructor
    e.execute();                    // Invoke execute method
    // Look for <Event 1: -1.0> to be printed (no formal tests)
}


// ---------------------------------------------------------------- //

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
