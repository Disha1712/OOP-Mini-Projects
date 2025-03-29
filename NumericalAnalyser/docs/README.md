# Intelligent Currency Validator & Numerical Analyzer

## Overview
This project is designed to assist in detecting counterfeit currency by analyzing numerical patterns and performing advanced mathematical operations. It incorporates four core functionalities: currency sorting, Fibonacci sequence generation, prime number analysis, and divisor-based number evaluation.

## Features

### 1. CurrencySorter
- Implements a **functor** to sort an array of currency serial numbers.
- Uses **quick sort** (custom implementation, no built-in sorting functions).
- Sorts the array **in-place** for efficient memory usage.

### 2. FibonacciGenerator
- Implements a **functor** to compute the `i`-th Fibonacci number.
- Uses the recurrence formula: `Fi = Fi-1 + Fi-2`, with `F0 = 0` and `F1 = 1`.
- Returns the result **modulo 10⁹+7** to handle large values.

### 3. PrimeCalculator
- **printPrimes(L, R):** Prints all prime numbers within a given range `[L, R]`.
- **printPrimeSum(L, R):** Computes and returns the sum of all prime numbers in the range `[L, R]`.

### 4. NumberAnalyzer
- **isSquareFree(X):** Checks if a number `X` is square-free (not divisible by any perfect square except 1).
- **countDivisors(X):** Returns the total number of divisors of `X`.
- **sumOfDivisors(X):** Returns the sum of all divisors of `X`.

## Input Format

Each test case starts with a type number indicating the operation to be performed:

1. **Type 1 (Currency Sorting)**
   ```
   1
   t (number of operations)
   n (size of array)
   a1 a2 ... an (array elements)
   ```
   **Output:** Sorted array.

2. **Type 2 (Fibonacci Calculation)**
   ```
   2
   t (number of operations)
   i (index in Fibonacci sequence)
   ```
   **Output:** Fibonacci(i) % (10⁹+7).

3. **Type 3 (Prime Number Operations)**
   ```
   3
   t (number of operations)
   printPrimes L R
   printPrimeSum L R
   ```
   **Output:** List of primes or sum of primes in range `[L, R]`.

4. **Type 4 (Number Analysis)**
   ```
   4
   t (number of operations)
   isSquareFree X
   countDivisors X
   sumOfDivisors X
   ```
   **Output:** Yes/No, number of divisors, or sum of divisors.

## Sample Test Cases

### Test Case 1: Currency Sorting
**Input:**
```
1
1
6
55 34 36 46 100 72
```
**Output:**
```
34 36 46 55 72 100
```

### Test Case 2: Fibonacci Calculation
**Input:**
```
2
3
2
4
6
```
**Output:**
```
1
3
8
```

### Test Case 3: Prime Number Operations
**Input:**
```
3
2
printPrimes 1 10
printPrimeSum 1 15
```
**Output:**
```
2 3 5 7
41
```

### Test Case 4: Number Analysis
**Input:**
```
4
3
isSquareFree 6
countDivisors 24
sumOfDivisors 12
```
**Output:**
```
yes
8
28
```

## Additional Notes
- Implements functors to ensure efficient function execution.
- Avoids built-in sorting functions for manual sorting control.
- Handles large numbers using **modular arithmetic** (Fibonacci modulo 10⁹+7).
- Optimized for prime number calculations using **efficient sieving techniques**.

---

Let me know if you need modifications! 🚀

