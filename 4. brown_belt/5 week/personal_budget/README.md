### Programming Task: Personal Budget Manager

Programming Task  
"Personal Budget, Professional Mobile Version"  

Implement the extended functionality from the previous task ("Professional Desktop Version") under stricter constraints: now, up to 100,000 requests must be processed within 3.5 seconds.  

Develop a system for managing a personal budget. You must handle requests of the following types:  

- **ComputeIncome from to**: Calculate the net income for the specified date range.  

- **Earn from to value**: Record that the specified amount (`value`) was earned over the given period (distributed evenly by day).  

- **Spend from to value**: Record that the specified amount (`value`) was spent evenly over the given date range. Now, net income in `ComputeIncome` requests is calculated as the difference between earnings (after tax deductions) and expenses. When calculating taxes, spent amounts are not considered.  

- **PayTax from to percentage**: Pay the specified tax rate (`percentage`) over the given date range. It is guaranteed that `percentage` is an integer between 0 and 100.  

#### Notes:  
- In all ranges `from to`, both dates `from` and `to` are inclusive.

#### Constraints:  
- The system must handle up to 100,000 requests within 3.5 seconds.