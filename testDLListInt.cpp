#include <gtest/gtest.h>
#include "./DLListInt.h"
#include <iostream>
#include <sstream>

using namespace std;

TEST(DLListInt, EmptyConstructor) {
// create empty queue and verify string representation
	DLListInt L;
	EXPECT_EQ(0, L.length());
	EXPECT_EQ(string("[]"), L.str());
}

TEST(DLListInt, AppendOne) {
  DLListInt L;
  L.append(5);
  EXPECT_EQ(string("[5]"), L.str());

  DLListInt T;
  T.append(-10);
  EXPECT_EQ(string("[-10]"), T.str());
}

TEST(DLListInt, InsertOne) {
  DLListInt L;
  L.insert(0, 5);
  EXPECT_EQ(string("[5]"), L.str());

  DLListInt T;
  T.insert(0, -10);
  EXPECT_EQ(string("[-10]"), T.str());
}

TEST(DLListInt, AppendTwo) {
  DLListInt L;
  L.append(5);
  L.append(-10);
  EXPECT_EQ(string("[5, -10]"), L.str());
}

TEST(DLListInt, InsertTwoAtHead) {
  DLListInt L;
  L.insert(0, 5);
  L.insert(0, -10);
  EXPECT_EQ(string("[-10, 5]"), L.str());
}

TEST(DLListInt, InsertTwoInOrder) {
  DLListInt L;
  L.insert(0, 5);
  L.insert(1, -10);
  EXPECT_EQ(string("[5, -10]"), L.str());
}

TEST(DLListInt, AppendThree) {
  DLListInt L;
  L.append(5);
  L.append(-10);
  L.append(7);
  EXPECT_EQ(string("[5, -10, 7]"), L.str());
}

TEST(DLListInt, InsertThreeAtHead) {
  DLListInt L;
  L.insert(0, 5);
  L.insert(0, -10);
  L.insert(0, 7);
  EXPECT_EQ(string("[7, -10, 5]"), L.str());
}

TEST(DLListInt, AppendThreeInsertMiddle) {
  DLListInt L;
  L.append(5);
  L.append(-10);
  L.append(7);
  L.insert(2, 1);
  EXPECT_EQ(string("[5, -10, 1, 7]"), L.str());

  DLListInt T;
  T.append(5);
  T.append(-10);
  T.append(7);
  T.insert(1, 1);
  EXPECT_EQ(string("[5, 1, -10, 7]"), T.str());
}

TEST(DLListInt, AccessAscending)
{
  DLListInt L;
  for (int i = 0; i < 5; i++) {
    L.insert(i, i);
  }
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(i, L[i]);
  }
}

TEST(DLListInt, AccessDescending)
{
  DLListInt L;
  for (int i = 0; i < 5; i++) {
    L.insert(i, 5-i);
  }
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(5-i, L[i]);
  }
}

TEST(DLListInt, PopOnly)
{
  int val;
  DLListInt L;
  L.append(5);
  val = L.pop();
  EXPECT_EQ(5, val);
  EXPECT_EQ(string("[]"), L.str());
  EXPECT_EQ(0, L.length());
}

TEST(DLListInt, PopLast)
{
  DLListInt L;
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

TEST(DLListInt, PopFirst)
{
  DLListInt L;
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

TEST(DLListInt, PopMiddle)
{
  DLListInt L;
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

TEST(DLListInt, InsertMultiple)
{
  DLListInt s;
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

TEST(DLListInt, Assign)
{
  DLListInt s;
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

TEST(DLListInt, PopEmpty)
{
  DLListInt L;
  EXPECT_THROW(L.pop(), IndexError);
}

TEST(DLListInt, PopEmptyInOut)
{
  DLListInt L;
  L.append(5);
  L.pop();
  EXPECT_THROW(L.pop(), IndexError);
}

TEST(DLListInt, IterThree)
{
  DLListInt L;
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

TEST(DLListInt, CopyConstructor1)
{
  DLListInt L;
  for (int i=0; i<5; i++) {
    L.append(2-i);
  }
  DLListInt L2(L);
  for (int i=0; i<5; i++) {
    EXPECT_EQ(2-i, L2[i]);
  }
  EXPECT_EQ(5, L2.length());
}

TEST(DLListInt, CopyConstructorNext)
{
  DLListInt L;
  for (int i=0; i<5; i++) {
    L.append(2-i);
  }
  DLListInt L2(L);
  for (int i=0; i<5; i++) {
    EXPECT_EQ(2-i, L2.next());
  }
  EXPECT_EQ(5, L2.length());
}

TEST(DLListInt, CopyConstructorValTest)
{
  DLListInt L;
  for (int i=0; i<5; i++) {
    L.append(2-i);
  }
  DLListInt L2(L);
  // Change all the values in L before checking copied values in L2
  for (int i=0; i<5; i++) {
    L[i] = 10 + i;
  }
  for (int i=0; i<5; i++) {
    EXPECT_EQ(2-i, L2[i]);
  }
  EXPECT_EQ(5, L2.length());
}

TEST(DLListInt, Assignment1)
{
  DLListInt L;
  for (int i=0; i<5; i++) {
    L.append(2-i);
  }
  DLListInt L2;
  L2 = L;
  for (int i=0; i<5; i++) {
    EXPECT_EQ(2-i, L2[i]);
  }
  EXPECT_EQ(5, L2.length());
}

TEST(DLListInt, AssignmentValTest)
{
  DLListInt L;
  for (int i=0; i<5; i++) {
    L.append(2-i);
  }
  DLListInt L2;
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

TEST(DLListInt, StreamOverload)
{
  stringstream s;
  DLListInt L;
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
