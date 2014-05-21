=========================================
====          HW10 README           =====
==== Peter Hurford and Bryan Fowler =====
=========================================

For HW10, we decided to create Dr. Bressoud’s Bassoon Saloon, a company that has one main worker and a backup worker.  If the main worker is busy, the backup worker can come in to continue the assembly process.

Furthermore, either worker has a chance of failing to make their bassoon correctly, which results in needing to start over.  If the bassoon fails too many times, it is trashed and never sent out.  Both the chance of failure and the failure tolerance are variables that can be customized by the user.

This M/M/2 Queueing Simulation can be tested the standard way by running “./testSimulator”.  However, there is also a user-friendly interactive that can be run by running “./bassoons”, which allows the user to see statistics for custom set variables.