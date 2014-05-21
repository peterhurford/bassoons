// HW9/10: Test Suite for the OrderedSet Class for DES
// Peter Hurford and Bryan Fowler

#include <gtest/gtest.h>
#include "OrderedSet.h"
#include "Event.h"
#include <iostream>
#include <string>

using namespace std;

// ----------------------- Test Constructor ----------------------- //
TEST(OrderedSetTest, DefaultConstructor) {
    OrderedSet<Event*> o;        // Create an ordered set with the default constructor.
    EXPECT_EQ(0, o.len());      // Expect length to be 0.
    EXPECT_EQ("[]", o.str());   // Expect set to print as [].
}

TEST(OrderedSetTest, ConstructorWithSize) {
    OrderedSet<Event*> o(20);   // Create an ordered set with maxlength of 20.
    EXPECT_EQ(0, o.len());      // Expect length to still be 0.
    EXPECT_EQ("[]", o.str());   // Expect set to still print as [].
}


// ----------------------- Test Insert ---------------------------- //
TEST(OrderedSetTest, InsertEmptyEvent){
    OrderedSet<Event*> o;
    Event e;                                   // Create an event using the default constructor.
    o.insert(&e);                               	// Insert that event.
    EXPECT_EQ(1, o.len());                      // Expect length to be 1.
    EXPECT_EQ("[<Event 0: -1>*]", o.str());     // Expect set to print "[<Event 0: -1>*]".
}

TEST(OrderedSetTest, InsertSingleEvent) {
    OrderedSet<Event*> o;
    Event e(5, 3.0);                              // Create event with arguments.
    o.insert(&e);
    EXPECT_EQ(1, o.len());
    EXPECT_EQ("[<Event 5: 3>*]", o.str());
}

TEST(OrderedSetTest, InsertMultipleEvents) {
    OrderedSet<Event*> o;
    Event e1(1, 3), e2(2, 6);                                   // Create two different events with mutlple, though pre-sorted times.
    o.insert(&e1); o.insert(&e2);                               // Insert both.
    EXPECT_EQ(2, o.len());                                      // Expect length to be 2.
    EXPECT_EQ("[<Event 1: 3>*, <Event 2: 6>]", o.str());
}

TEST(OrderedSetTest, InsertMultipleEventsUnsorted) {
    OrderedSet<Event*> o;
    Event e1(1, 3), e2(2, 1), e3(3, 4), e4(4, 2), e5(5, 5);                                    // Create five events, not pre-sorted.
    o.insert(&e1); o.insert(&e2); o.insert(&e3); o.insert(&e4); o.insert(&e5);
    EXPECT_EQ(5, o.len());
    EXPECT_EQ("[<Event 2: 1>*, <Event 4: 2>, <Event 1: 3>, <Event 3: 4>, <Event 5: 5>]", o.str());     // Expect OrderedSet to sort events by time.
}

TEST(OrderedSetTest, MultipleInsert) {
    OrderedSet<Event*> o;
    Event e1(2, 3);
    o.insert(&e1);                                        // Insert one event.
    EXPECT_EQ(1, o.len());
    EXPECT_EQ("[<Event 2: 3>*]", o.str());                // Expect set only to have that first event.
    
    Event e2(1, 1);
    o.insert(&e2);                                        // Insert a second event.
    EXPECT_EQ(2, o.len());
    EXPECT_EQ("[<Event 1: 1>*, <Event 2: 3>]", o.str());  // Expect set to have both events, sorted by time.
}

TEST(OrderedSetTest, InsertMultipleEventsOverflow) {
    OrderedSet<Event*> o(1);                             // Create a set with a maxlength of 1.
    Event e1(1, 3), e2(2, 4);
    int t1 = o.insert(&e1);
    int t2 = o.insert(&e2);                      // Attempt to insert two events.
    EXPECT_EQ(1, t1);                            // Expect first insert to be successful.
    EXPECT_EQ(0, t2);                            // Expect second insert to be unsuccessful.
    EXPECT_EQ(1, o.len());                       // Expect length to be 1.
    EXPECT_EQ("[<Event 1: 3>*]", o.str());       // Expect set to only have the first inserted event.
}


// ----------------------- Test removeFirst ----------------------- //

TEST(OrderedSetTest, RemoveOne) {
    OrderedSet<Event*> o;
    Event e1;
    o.insert(&e1);
    EXPECT_EQ(1, o.len());                      // Expect length to be 1.
    EXPECT_EQ("[<Event 0: -1>*]", o.str());     // Expect set to have inserted event.

    Event* r = o.removeFirst();               // Remove event.
    EXPECT_EQ("<Event 0: -1>", r->str());       // Expect return value of removeFirst() to match inserted event.
    EXPECT_EQ(0, o.len());                      // Expect length to now be 0.
    EXPECT_EQ("[]", o.str());                   // Expect set to now be empty.
}

TEST(OrderedSetTest, RemoveTwice) {
    OrderedSet<Event*> o;
    Event e1(1, 3), e2(2, 4);
    o.insert(&e1); o.insert(&e2);
    EXPECT_EQ(2, o.len());                                      // Expect length to be 2.
    EXPECT_EQ("[<Event 1: 3>*, <Event 2: 4>]", o.str());        // Expect set to have inserted events.

    Event* r1 = o.removeFirst();                              // Remove first event.
    EXPECT_EQ("<Event 1: 3>", r1->str());                       // Expect return value of removeFirst() to match first inserted event.
    EXPECT_EQ(1, o.len());                                      // Expect length to now be 1.
    EXPECT_EQ("[<Event 2: 4>*]", o.str());                      // Expect set to only have second event.

    Event* r2 = o.removeFirst();                              // Remove other event.
    EXPECT_EQ("<Event 2: 4>", r2->str());                       // Expect return value of removeFirst() to match second inserted event.
    EXPECT_EQ(0, o.len());                                      // Expect length to now be 0.
    EXPECT_EQ("[]", o.str());                                   // Expect set to now be empty.
}

TEST(OrderedSetTest, RemoveOnEmpty) {
    OrderedSet<Event*> o;
    EXPECT_THROW(o.removeFirst(), int);     // Expect an integer to be thrown indicating remove on empty.
}


// ----------------------- Test Remove ----------------------- //

TEST(OrderedSetTest, RemoveById) {
    OrderedSet<Event*> o;
    Event e1(10, 3), e2(11, 4), e3(12, 5);
    o.insert(&e1); o.insert(&e2); o.insert(&e3);            // Set up set with three elements.

    int t1 = o.remove(11);                                  // Remove middle event by id.
    EXPECT_EQ(t1, 1);                                       // Expect remove to be successful.
    EXPECT_EQ(2, o.len());                                  // Expect length to now be 2.
    EXPECT_EQ("[<Event 10: 3>*, <Event 12: 5>]", o.str());  // Expect set to only have first and third event.
}

TEST(OrderedSetTest, RemoveByIdTwice) {
    OrderedSet<Event*> o;
    Event e1(10, 3), e2(11, 4), e3(12, 5);
    o.insert(&e1); o.insert(&e2); o.insert(&e3);            // Set up set with three elements.

    int t1 = o.remove(11);                                  // Remove middle event by id.
    EXPECT_EQ(t1, 1);                                       // Expect remove to be successful.
    EXPECT_EQ(2, o.len());                                  // Expect length to now be 2.
    EXPECT_EQ("[<Event 10: 3>*, <Event 12: 5>]", o.str());  // Expect set to only have first and third event.

    int t2 = o.remove(10);                                  // Remove first event by id.
    EXPECT_EQ(t2, 1);                                       // Expect remove to be successful.
    EXPECT_EQ(1, o.len());                                  // Expect length to now be 1.
    EXPECT_EQ("[<Event 12: 5>*]", o.str());                 // Expect set to only have third event.
}

TEST(OrderedSetTest, RemoveNonexistantId) {
    OrderedSet<Event*> o;
    Event e1(10, 3), e2(11, 4), e3(12, 5);
    o.insert(&e1); o.insert(&e2); o.insert(&e3);    	// Set up set with three elements.

    int t1 = o.remove(13);                          // Remove an id that doesn't exist.
    EXPECT_EQ(t1, 0);                               // Expect remove to be unsuccessful.
    EXPECT_EQ(3, o.len());                          // Expect length to still be 3.
}

TEST(OrderedSetTest, RemoveByIdOnEmpty) {
    OrderedSet<Event*> o;
    int t1 = o.remove(13);                          // Remove with an empty ordered set.
    EXPECT_EQ(t1, 0);                               // Expect remove to be unsuccessful.
    EXPECT_EQ(0, o.len());                          // Expect length to still be 0.
}


// ---------------------------------------------------------------- //


int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
