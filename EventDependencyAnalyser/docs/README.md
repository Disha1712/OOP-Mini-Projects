# InstaInfluencer Fest '25 - Event Dependency Analyzer

## Overview
The **InstaInfluencer Fest '25** at IIT Madras is an event-packed festival for influencers and content creators. Each event in the festival has dependencies, meaning some events must be completed before others can occur. Organizers need an efficient way to manage these dependencies while resolving conflicts caused by influencer demands.

This project models the event schedule as a **directed graph**, where:
- **Nodes** represent events.
- **Directed edges** represent dependencies (Event `u` must occur before Event `v`).
- Each event has a **hype score** that indicates its popularity.

## Features
The system supports four main functionalities:

### 1. Cycle Detection (Query Type 1)
- Determines if the event schedule contains cyclic dependencies.
- Outputs `YES` if cycles exist; otherwise, outputs `NO`.

### 2. Strongly Connected Components (SCC) Analysis (Query Type 2)
- Identifies **SCCs** in the event dependency graph.
- Computes the **largest SCC's cardinality** (number of events in the largest SCC).
- Outputs the total number of SCCs and the largest SCC's size.

### 3. Topological Sorting (Query Type 3)
- Determines a **valid topological order** of events if possible.
- Ensures that independent events are sorted **lexicographically** within their valid order.
- Outputs the order or `NO` if no valid order exists due to cycles.

### 4. Maximum Hype Score Calculation (Query Type 4)
- Condenses SCCs into single nodes by summing their **hype scores**.
- Finds the **maximum possible hype score** from a valid event sequence.
- Outputs the highest achievable total hype score.

## Input Format
1. First line: Two integers `N` and `M` representing the number of events and dependencies.
2. Second line: `N` integers representing the **hype score** of each event.
3. Next `M` lines: Two integers `u` and `v`, indicating that event `u` must occur before event `v`.
4. Next line: An integer `Q` representing the number of queries.
5. Next `Q` lines: One integer per line indicating query type (1, 2, 3, or 4).

## Output Format
- **Query Type 1**: Output `YES` or `NO`.
- **Query Type 2**: Output two integers: total SCC count and largest SCC size.
- **Query Type 3**: Output a valid **topological order** of events or `NO` if cycles exist.
- **Query Type 4**: Output the **maximum total hype score** achievable.

## Constraints
- `1 ≤ N, M ≤ 10^5`
- `1 ≤ Q ≤ 10^5`
- `1 ≤ Hype Score ≤ 10^4`
- Events are numbered from `1` to `N`.

## Example
### **Input**
```
4 4
10 20 30 40
1 2
2 3
3 1
3 4
4
1
2
3
4
```
### **Output**
```
YES
2 3
NO
100
```

## Implementation Details
- Uses **GraphAlgorithm** as a base class with virtual functions for different query types:
  - `isCycle()`: Detects cycles.
  - `indepComponent()`: Computes SCCs and their sizes.
  - `validOrder()`: Determines a valid event order.
  - `maxHype()`: Computes max hype points.
- Efficient **Tarjan’s algorithm** is used for SCC detection.
- **Topological sorting** is done using **Kahn’s algorithm**.
- **Dynamic Programming** is used for max hype computation on DAGs.

