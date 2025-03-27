### **Programming Task: "Forbidden Domains" Under a Sanitizer**  

You are given a solution to the "Forbidden Domains" problem from the "Brown Belt" level. However, the solution contains some minor issues that can be detected using sanitizers and/or debugging defines. Your task is to find these issues, fix them, and submit the corrected solution.  

#### **Training Task**  
This is a practice task, so we recommend using it as an opportunity to better understand sanitizers rather than simply submitting a ready-made solution from a previous course.  

---

### **Original Problem Statement**  
Implement domain filtering based on a fixed set of forbidden domains.  

If a domain like `ya.ru` is forbidden, then not only should that exact domain be filtered out, but all of its subdomains as well. For example, `ya.ru`, `m.ya.ru`, `m.mail.ya.ru`, etc., should all be blocked.  

#### **Input Format**  
- The first input line contains the number of forbidden domains, followed by the list of forbidden domains themselves.  
- The next lines contain the number of domains to check, followed by the list of domains to be validated.  

#### **Output Format**  
For each domain in the second set:  
- Print `"Bad"` if the domain needs to be filtered (i.e., it is in the forbidden list or is a subdomain of a forbidden domain).  
- Print `"Good"` otherwise.  

---

### **Example**  

#### **Input:**  
```
4
ya.ru
maps.me
m.ya.ru
com
7
ya.ru
ya.com
m.maps.me
moscow.m.ya.ru
maps.com
maps.ru
ya.ya
```

#### **Output:**  
```
Bad
Bad
Bad
Bad
Bad
Good
Good
```

---

### **Constraints**  
- Each domain consists of lowercase Latin letters separated by dots (`.`).  
- A dot cannot be the first or last character.  
- Consecutive dots are not allowed (i.e., every dot must be surrounded by letters).  
- The length of each domain is at most **50**.  
- Each set contains at most **10,000** domains.  
- The program must run within **3 seconds**.