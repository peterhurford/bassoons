// HW9/10: Test Suite for the Queue Class
// Peter Hurford and Bryan Fowler

#include <gtest/gtest.h>
#include "./Queue.h"
#include "Customer.h"
#include <iostream>
#include <string>

using namespace std;

// ----------------------- Test Constructor ----------------------- //
TEST(QueueTest,EmptyConstructor){	//test empty constructor
    Queue<Customer> r;					//create Queue	
    EXPECT_EQ(0,r.len());		
    EXPECT_EQ("[]",r.str());		
}

TEST(QueueTest,EmptyConstructorSize){	//test empty constructor 
    Queue<Customer> r(20);					//create queue of size 20
    EXPECT_EQ(0,r.len());
    EXPECT_EQ("[]",r.str());
}


// ---------------------------------------------------------------- //
// ----------------------- Test Enqueue ----------------------- //
TEST(QueueTest,EnqueueEmptyCustomer){		//test empty customer enqueue
    Queue<Customer> r;
    Customer c;
    r.enqueue(c);
    EXPECT_EQ(1,r.len());			//check len of queue = 1
    EXPECT_EQ("[<Customer : 0>*]",r.str());	//check string version of queue
}

TEST(QueueTest,EnqueueSingleCustomer){			//test customer enqueue
    Queue<Customer> r;
    Customer c(3.2, "First");
    r.enqueue(c);
    EXPECT_EQ(1,r.len());				//check len of queue = 1
    EXPECT_EQ("[<Customer First: 3.2>*]",r.str());	//check string version of queue
}

TEST(QueueTest,EnqueueMultipleCustomers){					//test enqueue multiple customers
    Queue<Customer> r;
    Customer c(3.2, "First"), d(4.6, "Second");
    r.enqueue(c);
    EXPECT_EQ(1,r.len());
    EXPECT_EQ("[<Customer First: 3.2>*]",r.str());				//check string version of queue
    r.enqueue(d);
    EXPECT_EQ(2,r.len());
    EXPECT_EQ("[<Customer First: 3.2>*, <Customer Second: 4.6>]",r.str());	//check string version of queue
}

TEST(QueueTest,EnqueueMultipleCustomersOverflow){	//test enqueue when size exceeds maxsize
    Queue<Customer> r(1);
    Customer c(3.2, "First"), d(4.6, "Second");
    r.enqueue(c);
    r.enqueue(d);
    EXPECT_EQ(1,r.len());
    EXPECT_EQ("[<Customer First: 3.2>*]",r.str());	//check string version of queue
}

// ---------------------------------------------------------------- //
// ----------------------- Test Dequeue ----------------------- //

TEST(QueueTest,SingleDequeue){					//test single dequeue
    Queue<Customer> r;
    Customer c(3.2, "First"), d(4.6, "Second");
    r.enqueue(c);
    r.enqueue(d);
    r.dequeue();						//dequeue
    EXPECT_EQ(1,r.len());
    EXPECT_EQ("[<Customer Second: 4.6>*]",r.str());		//check string version of queue
}



TEST(QueueTest,MultipleDequeues){					//test multiple dequeues
    Queue<Customer> r;
    Customer c(3.2, "First"), d(4.6, "Second"), e;
    r.enqueue(c);
    r.enqueue(d);
    r.enqueue(e);
    r.dequeue();							
    EXPECT_EQ(2,r.len());
    EXPECT_EQ("[<Customer Second: 4.6>*, <Customer : 0>]",r.str());	//check string version of queue
    r.dequeue();
    EXPECT_EQ(1,r.len());
    EXPECT_EQ("[<Customer : 0>*]",r.str());				//check string version of queue
    r.dequeue();
    EXPECT_EQ(0,r.len());
    EXPECT_EQ("[]",r.str());  						//check string version of queue
}


TEST(QueueTest,EmptyDequeue){		//test dequeue on empty constructor
    Queue<Customer> r;
    EXPECT_THROW(r.dequeue(), int);	//catch error
    EXPECT_EQ(0,r.len());
    EXPECT_EQ("[]",r.str());		//check string version of queue
}

// ---------------------------------------------------------------- //
// ----------------------- Test len & str----------------------- //
TEST(QueueTest,LengthString){						//test len and str functions of queue
    Queue<Customer> r;
    Customer c(3.2, "First"), d(4.6, "Second"), e, f,g ;
    r.enqueue(c);
    r.enqueue(d);
    r.enqueue(e);
    r.enqueue(f);
    r.enqueue(g);
    EXPECT_EQ(5,r.len());
    EXPECT_EQ("[<Customer First: 3.2>*, <Customer Second: 4.6>, <Customer : 0>, <Customer : 0>, <Customer : 0>]",r.str());	//check string version of queue
}

// ---------------------------------------------------------------- //


int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
