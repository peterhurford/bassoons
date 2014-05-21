// HW10: Test Suite for the Simulator Class
// Peter Hurford and Brylan Fowler

#include <gtest/gtest.h>
#include "Simulator.h"
#include <iostream>
#include <string>

// ----------------------- Test Base Case ----------------------- //
TEST(SimulatorTest, StartOneCustomer) {
	cout << "1 customer, default params" << endl;
	Simulator sim;
	sim.setup(1);
	sim.doAllEvents();
	EXPECT_EQ(1, sim.pass_num());
}

TEST(SimulatorTest, TwoCustomers) {
	cout << "2 customers, default params" << endl;
	Simulator sim;
	sim.setup(2);
	sim.doAllEvents();
	EXPECT_EQ(2, sim.pass_num());
}

TEST(SimulatorTest, FiveCustomers) {
	cout << "5 customers, default params" << endl;
	Simulator sim;
	sim.setup(5);
	sim.doAllEvents();
	EXPECT_EQ(5, sim.pass_num());
}

TEST(SimulatorTest, FiftyCustomers) {
	cout << "50 customers, default params" << endl;
	Simulator sim;
	sim.setup(50);
	sim.doAllEvents();
	EXPECT_EQ(50, sim.pass_num());
}

TEST(SimulatorTest, FiftyCustomersNoFailure) {
	cout << "50 customers, arrival mean = 10, service mean = 5, failure rate = 0%, tolerance = 2" << endl;
	Simulator sim;
	sim.setup(50, 10.0, 5.0, 0.0);
	sim.doAllEvents();
	EXPECT_EQ(50, sim.pass_num());
}

TEST(SimulatorTest, FiftyCustomersHighFailure) {
	cout << "50 customers, arrival mean = 10, service mean = 5, failure rate = 80%, tolerance = 2" << endl;
	Simulator sim;
	sim.setup(50, 10.0, 5.0, 0.8);
	sim.doAllEvents();
	EXPECT_EQ(50, sim.pass_num());
}

TEST(SimulatorTest, ThousandCustomers) {
	cout << "1000 customers, default params" << endl;
	Simulator sim;
	sim.setup(1000);
	sim.doAllEvents();
	EXPECT_EQ(1000, sim.pass_num());
}

TEST(SimulatorTest, ThousandCustomersHighFailure) {
	cout << "1000 customers, arrival mean = 10, service mean = 5, failure rate = 50%, tolerance = 2" << endl;
	Simulator sim;
	sim.setup(1000, 10.0, 5.0, 0.5);
	sim.doAllEvents();
	EXPECT_EQ(1000, sim.pass_num());
}

TEST(SimulatorTest, ThousandCustomersLowTolerance) {
	cout << "1000 customers, arrival mean = 10, service mean = 5, failure rate = 50%, tolerance = 0" << endl;
	Simulator sim;
	sim.setup(1000, 10.0, 5.0, 0.5, 0);
	sim.doAllEvents();
	EXPECT_EQ(1000, sim.pass_num());
}

TEST(SimulatorTest, ThousandCustomersHighTolerance) {
	cout << "1000 customers, arrival mean = 10, service mean = 5, failure rate = 50%, tolerance = 4" << endl;
	Simulator sim;
	sim.setup(1000, 10.0, 5.0, 0.5, 4);
	sim.doAllEvents();
	EXPECT_EQ(1000, sim.pass_num());
}

TEST(SimulatorTest, ThousandCustomersEvenServiceMean) {
	cout << "1000 customers, arrival mean = 10, service mean = 10, failure rate = 10%, tolerance = 2" << endl;
	Simulator sim;
	sim.setup(1000, 10.0, 10.0);
	sim.doAllEvents();
	EXPECT_EQ(1000, sim.pass_num());
}

TEST(SimulatorTest, ThousandCustomersLongServiceMean) {
	cout << "5 customers, arrival mean = 10, service mean = 15, failure rate = 10%, tolerance = 2" << endl;
	Simulator sim;
	sim.setup(1000, 10.0, 15.0);
	sim.doAllEvents();
	EXPECT_EQ(1000, sim.pass_num());
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
