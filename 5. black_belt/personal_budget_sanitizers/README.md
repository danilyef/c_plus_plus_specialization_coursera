### **Programming Assignment: Personal Budget under a Sanitizer**  

You are given a solution to the problem **"Personal Budget, Professional Mobile Version"** from the **Brown Belt**. It contains a number of issues that can be detected using sanitizers and/or debugging defines. Your task is to find, fix, and submit the corrected solution.  

**orignal.cpp**  

This is a practice problem, so we recommend using it as an opportunity to better understand sanitizers rather than simply submitting a ready-made solution from the previous course.  

---

### **Original Problem Statement**  
Implement a system for managing a personal budget. You need to handle the following types of queries:  

- **`ComputeIncome from to`**: Calculate the net income for the specified date range.  
- **`Earn from to value`**: Account for income of `value`, evenly distributed over the given date range.  
- **`Spend from to value`**: Spend the specified amount, evenly distributed over the given date range.  
- **`PayTax from to percentage`**: Pay the specified tax for the given date range.  
  - The tax percentage is guaranteed to be an integer between `0` and `100`.  
  - Tax is calculated as multiplying all earnings in the range by `(1 − percentage / 100)`, regardless of whether tax has already been paid for some of these days.  
  - Future earnings in these days are not affected by past taxes.  

---

### **Notes**  
- In all date ranges **from** and **to**, both dates are **inclusive**.  

---

### **Input Format**  
- The first line contains an integer **Q** — the number of queries.  
- Each of the following **Q** lines contains a query in one of the formats described above.  

### **Output Format**  
For each **`ComputeIncome`** query, output a floating-point number representing the **net income** (earnings after tax deductions) for the specified date range.  

---

### **Constraints**  
- **Q** is a natural number, not exceeding **100,000**.  
- Dates are given in the format **YYYY-MM-DD**.  
- Dates are valid (including leap years) and fall within the range **2000 to 2100** (inclusive).  
- **value** is a positive integer, not exceeding **1,000,000**.  
- The program must process all queries within **3.5 seconds**.  

---

### **Example**  

#### **Input**  
```
8
Earn 2000-01-02 2000-01-06 20
ComputeIncome 2000-01-01 2001-01-01
PayTax 2000-01-02 2000-01-03 13
ComputeIncome 2000-01-01 2001-01-01
Spend 2000-12-30 2001-01-02 14
ComputeIncome 2000-01-01 2001-01-01
PayTax 2000-12-30 2000-12-30 13
ComputeIncome 2000-01-01 2001-01-01
```

#### **Output**  
```
20
18.96
8.46
8.46
```