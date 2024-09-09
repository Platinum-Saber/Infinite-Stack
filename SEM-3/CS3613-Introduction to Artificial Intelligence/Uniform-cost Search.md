---
tags:
  - AI
  - SearchAlgorithms
Reviewed: 
Created: 2024-09-09T09:33:00
About: Note generated using GPT on uniform-cost search algorithm
---
Uniform-Cost Search (UCS) is a type of **uninformed search algorithm** used to find the least-cost path in a graph. It is similar to Dijkstra's algorithm and is used when the path cost is not uniform, meaning some paths may have higher or lower costs than others. UCS is essentially a **BFS variant** but takes into account the **cost of edges**.

### Key Characteristics of Uniform-Cost Search:

1. **Cost-Based Expansion**: UCS expands the node with the **lowest cumulative cost** from the start node to the current node.
2. **Priority Queue**: UCS uses a priority queue (min-heap) to ensure that nodes with the least cost are expanded first.
3. **Optimal**: UCS guarantees finding the optimal path (least cost) if the cost is non-negative.
4. **Uninformed**: UCS doesn't have prior knowledge about the goal, unlike informed search algorithms like A*.

### How UCS Works:

1. UCS starts at the initial node and explores all the possible paths by expanding the least costly path at each step.
2. It uses a priority queue to store the nodes along with their cumulative costs.
3. At each step, UCS dequeues the node with the smallest cost, examines its neighbors, and adds them to the queue with their updated cumulative costs.
4. The process continues until the goal node is expanded.

