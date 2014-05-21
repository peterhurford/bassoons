#include <gtest/gtest.h>
#include "./DLList.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

TEST(DLList, EmptyConstructor) {
// create empty queue and verify string representation
	DLList<int> L;
	EXPECT_EQ(0, L.length());
	EXPECT_EQ(string("[]"), L.str());
}

TEST(DLList, AppendOne) {
  DLList<int> L;
  L.append(5);
  EXPECT_EQ(string("[5]"), L.str());

  DLList<int> T;
  T.append(-10);
  EXPECT_EQ(string("[-10]"), T.str());
}

TEST(DLList, AppendOneDouble) {
  DLList<double> L;
  L.append(5.6);
  EXPECT_EQ(string("[5.6]"), L.str());

  DLList<int> T;
  T.append(-10);
  EXPECT_EQ(string("[-10]"), T.str());
}
TEST(DLList, AppendOneString) {
  DLList<string> L;
  L.append("Peter");
  EXPECT_EQ(string("[Peter]"), L.str());

  DLList<int> T;
  T.append(-10);
  EXPECT_EQ(string("[-10]"), T.str());
}
TEST(DLList, InsertOne) {
  DLList<int> L;
  L.insert(0, 5);
  EXPECT_EQ(string("[5]"), L.str());

  DLList<int> T;
  T.insert(0, -10);
  EXPECT_EQ(string("[-10]"), T.str());
}

TEST(DLList, InsertOneDouble) {
  DLList<double> L;
  L.insert(0, 5.66);
  EXPECT_EQ(string("[5.66]"), L.str());

  DLList<int> T;
  T.insert(0, -10);
  EXPECT_EQ(string("[-10]"), T.str());
}

TEST(DLList, AppendTwo) {
  DLList<int> L;
  L.append(5);
  L.append(-10);
  EXPECT_EQ(string("[5, -10]"), L.str());
}

TEST(DLList, AppendTwoDouble) {
  DLList<double> L;
  L.append(5.66);
  L.append(-10.23);
  EXPECT_EQ(string("[5.66, -10.23]"), L.str());
}

TEST(DLList, InsertTwoAtHead) {
  DLList<int> L;
  L.insert(0, 5);
  L.insert(0, -10);
  EXPECT_EQ(string("[-10, 5]"), L.str());
}

TEST(DLList, InsertTwoDoubleAtHead) {
  DLList<double> L;
  L.insert(0, 5.66);
  L.insert(0, -10.23);
  EXPECT_EQ(string("[-10.23, 5.66]"), L.str());
}

TEST(DLList, InsertTwoInOrder) {
  DLList<int> L;
  L.insert(0, 5);
  L.insert(1, -10);
  EXPECT_EQ(string("[5, -10]"), L.str());
}

TEST(DLList, InsertTwoDoubleInOrder) {
  DLList<double> L;
  L.insert(0, 5.66);
  L.insert(1, -10.23);
  EXPECT_EQ(string("[5.66, -10.23]"), L.str());
}

TEST(DLList, AppendThree) {
  DLList<int> L;
  L.append(5);
  L.append(-10);
  L.append(7);
  EXPECT_EQ(string("[5, -10, 7]"), L.str());
}

TEST(DLList, AppendThreeDouble) {
  DLList<double> L;
  L.append(5.66);
  L.append(-10.23);
  L.append(7.5);
  EXPECT_EQ(string("[5.66, -10.23, 7.5]"), L.str());
}

TEST(DLList, InsertThreeAtHead) {
  DLList<int> L;
  L.insert(0, 5);
  L.insert(0, -10);
  L.insert(0, 7);
  EXPECT_EQ(string("[7, -10, 5]"), L.str());
}

TEST(DLList, InsertThreeDoubleAtHead) {
  DLList<double> L;
  L.insert(0, 5.66);
  L.insert(0, -10.23);
  L.insert(0, 7.5);
  EXPECT_EQ(string("[7.5, -10.23, 5.66]"), L.str());
}

TEST(DLList, AppendThreeInsertMiddle) {
  DLList<int> L;
  L.append(5);
  L.append(-10);
  L.append(7);
  L.insert(2, 1);
  EXPECT_EQ(string("[5, -10, 1, 7]"), L.str());

  DLList<int> T;
  T.append(5);
  T.append(-10);
  T.append(7);
  T.insert(1, 1);
  EXPECT_EQ(string("[5, 1, -10, 7]"), T.str());
}

TEST(DLList, AppendThreeDoubleInsertMiddle) {
  DLList<double> L;
  L.append(5.66);
  L.append(-10.23);
  L.append(7.5);
  L.insert(2, 1.3);
  EXPECT_EQ(string("[5.66, -10.23, 1.3, 7.5]"), L.str());

  DLList<double> T;
  T.append(5.66);
  T.append(-10.23);
  T.append(7.5);
  T.insert(1, 1.3);
  EXPECT_EQ(string("[5.66, 1.3, -10.23, 7.5]"), T.str());
}

TEST(DLList, AccessAscending)
{
  DLList<int> L;
  for (int i = 0; i < 5; i++) {
    L.insert(i, i);
  }
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(i, L[i]);
  }
}

TEST(DLList, AccessAscendingDoubles)
{
  DLList<double> L;
  for (double i = 0.5; i < 5.5; i++) {
    L.insert(i, i);
  }
  for (double i = 0.5; i < 5.5; i++) {
    EXPECT_EQ(i, L[i]);
  }
}

TEST(DLList, AccessDescending)
{
  DLList<int> L;
  for (int i = 0; i < 5; i++) {
    L.insert(i, 5-i);
  }
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(5-i, L[i]);
  }
}

TEST(DLList, PopOnly)
{
  int val;
  DLList<int> L;
  L.append(5);
  val = L.pop();
  EXPECT_EQ(5, val);
  EXPECT_EQ(string("[]"), L.str());
  EXPECT_EQ(0, L.length());
}

TEST(DLList, PopOnlyDouble)
{
  double val;
  DLList<double> L;
  L.append(5.66);
  val = L.pop();
  EXPECT_EQ(5.66, val);
  EXPECT_EQ(string("[]"), L.str());
  EXPECT_EQ(0, L.length());
}


TEST(DLList, PopLast)
{
  DLList<int> L;
  int val1, val2, val3;
  L.append(5);
  L.append(7);
  L.append(3);

  val1 = L.pop();
  val2 = L.pop();
  val3 = L.pop();

  EXPECT_EQ(3, val1);
  EXPECT_EQ(7, val2);
  EXPECT_EQ(5, val3);
  EXPECT_EQ(string("[]"), L.str());
  EXPECT_EQ(0, L.length());
}

TEST(DLList, PopLastDouble)
{
  DLList<double> L;
  double val1, val2, val3;
  L.append(5.66);
  L.append(7.5);
  L.append(3.5);

  val1 = L.pop();
  val2 = L.pop();
  val3 = L.pop();

  EXPECT_EQ(3.5, val1);
  EXPECT_EQ(7.5, val2);
  EXPECT_EQ(5.66, val3);
  EXPECT_EQ(string("[]"), L.str());
  EXPECT_EQ(0, L.length());
}

TEST(DLList, PopFirst)
{
  DLList<int> L;
  int val1, val2, val3;
  L.append(5);
  L.append(7);
  L.append(3);

  val1 = L.pop(0);
  val2 = L.pop(0);
  val3 = L.pop(0);

  EXPECT_EQ(5, val1);
  EXPECT_EQ(7, val2);
  EXPECT_EQ(3, val3);
  EXPECT_EQ(string("[]"), L.str());
  EXPECT_EQ(0, L.length());
}

TEST(DLList, PopFirstDouble)
{
  DLList<double> L;
  double val1, val2, val3;
  L.append(5.66);
  L.append(7.5);
  L.append(3.5);

  val1 = L.pop(0);
  val2 = L.pop(0);
  val3 = L.pop(0);

  EXPECT_EQ(5.66, val1);
  EXPECT_EQ(7.5, val2);
  EXPECT_EQ(3.5, val3);
  EXPECT_EQ(string("[]"), L.str());
  EXPECT_EQ(0, L.length());
}

TEST(DLList, PopMiddle)
{
  DLList<int> L;
  int val1, val2, val3;
  L.append(5);
  L.append(7);
  L.append(3);
  L.append(4);
  L.append(9);

  val1 = L.pop(3);
  val2 = L.pop(1);
  val3 = L.pop(1);

  EXPECT_EQ(4, val1);
  EXPECT_EQ(7, val2);
  EXPECT_EQ(3, val3);
  EXPECT_EQ(string("[5, 9]"), L.str());
  EXPECT_EQ(2, L.length());
}

TEST(DLList, PopMiddleDouble)
{
  DLList<double> L;
  double val1, val2, val3;
  L.append(5.66);
  L.append(7.5);
  L.append(3.5);
  L.append(4.2);
  L.append(9.2);

  val1 = L.pop(3);
  val2 = L.pop(1);
  val3 = L.pop(1);

  EXPECT_EQ(4.2, val1);
  EXPECT_EQ(7.5, val2);
  EXPECT_EQ(3.5, val3);
  EXPECT_EQ(string("[5.66, 9.2]"), L.str());
  EXPECT_EQ(2, L.length());
}

TEST(DLList, InsertMultiple)
{
  DLList<int> s;
  s.insert(0, 5);
  s.insert(1, 7);
  s.insert(2, 6);
  s.insert(3, 4);
  s.insert(4, 9);
  s.insert(3, 10);
  s.insert(1, 11);
  s.insert(5, 12);
  s.insert(0, 13);
  s.insert(1, 14);
  EXPECT_EQ(string("[13, 14, 5, 11, 7, 6, 10, 12, 4, 9]"), s.str());
}

TEST(DLList, Assign)
{
  DLList<int> s;
  s.insert(0, 5);
  s.insert(1, 7);
  s.insert(2, 6);
  s.insert(3, 4);
  s.insert(4, 9);
  for (int i=0; i < 5; i++) {
    s[i] = 5-i;
  }
  EXPECT_EQ(string("[5, 4, 3, 2, 1]"), s.str());
}

TEST(DLList, PopEmpty)
{
  DLList<int> L;
  EXPECT_THROW(L.pop(), IndexError);
}

TEST(DLList, PopEmptyInOut)
{
  DLList<int> L;
  L.append(5);
  L.pop();
  EXPECT_THROW(L.pop(), IndexError);
}

TEST(DLList, IterThree)
{
  DLList<int> L;
  L.append(0);
  L.append(1);
  L.append(2);

  for (int i = 0; i < L.length(); i++) {
    EXPECT_EQ(i, L.next());
  }
  EXPECT_THROW(L.next(), StopIteration);
  for (int i = 0; i < L.length(); i++) {
    EXPECT_EQ(i, L.next());
  }
}

TEST(DLList, CopyConstructor1)
{
  DLList<int> L;
  for (int i=0; i<5; i++) {
    L.append(2-i);
  }
  DLList<int> L2(L);
  for (int i=0; i<5; i++) {
    EXPECT_EQ(2-i, L2[i]);
  }
  EXPECT_EQ(5, L2.length());
}

TEST(DLList, CopyConstructorNext)
{
  DLList<int> L;
  for (int i=0; i<5; i++) {
    L.append(2-i);
  }
  DLList<int> L2(L);
  for (int i=0; i<5; i++) {
    EXPECT_EQ(2-i, L2.next());
  }
  EXPECT_EQ(5, L2.length());
}

TEST(DLList, CopyConstructorValTest)
{
  DLList<int> L;
  for (int i=0; i<5; i++) {
    L.append(2-i);
  }
  DLList<int> L2(L);
  // Change all the values in L before checking copied values in L2
  for (int i=0; i<5; i++) {
    L[i] = 10 + i;
  }
  for (int i=0; i<5; i++) {
    EXPECT_EQ(2-i, L2[i]);
  }
  EXPECT_EQ(5, L2.length());
}

TEST(DLList, Assignment1)
{
  DLList<int> L;
  for (int i=0; i<5; i++) {
    L.append(2-i);
  }
  DLList<int> L2;
  L2 = L;
  for (int i=0; i<5; i++) {
    EXPECT_EQ(2-i, L2[i]);
  }
  EXPECT_EQ(5, L2.length());
}

TEST(DLList, AssignmentValTest)
{
  DLList<int> L;
  for (int i=0; i<5; i++) {
    L.append(2-i);
  }
  DLList<int> L2;
  L2 = L;
  // Change all the values in L before checking copied values in L2
  for (int i=0; i<5; i++) {
    L[i] = 10 + i;
  }
  for (int i=0; i<5; i++) {
    EXPECT_EQ(2-i, L2[i]);
  }
  EXPECT_EQ(5, L2.length());
}

TEST(DLList, StreamOverload)
{
  stringstream s;
  DLList<int> L;
  for (int i=0; i<5; i++) {
    L.append(2-i);
  }
  s << L;
  EXPECT_EQ(string("[2, 1, 0, -1, -2]"), s.str());
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
