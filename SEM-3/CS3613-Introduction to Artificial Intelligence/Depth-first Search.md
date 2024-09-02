> [!code]- DFS code
> 
> > [!code]- Python
> > ```python
> > def dfs(graph, start, visited=None):
> >     if visited is None:
> >         visited = set()
> >     
> >     visited.add(start)
> >     print(start)  # Visit the node
> > 
> >     for neighbor in graph[start]:
> >         if neighbor not in visited:
> >             dfs(graph, neighbor, visited)
> >     
> >     return visited
> > 
> > # Example graph represented as an adjacency list
> > graph = {
> >     'A': ['B', 'C'],
> >     'B': ['A', 'D', 'E'],
> >     'C': ['A', 'F'],
> >     'D': ['B'],
> >     'E': ['B', 'F'],
> >     'F': ['C', 'E']
> > }
> > 
> > # Start DFS from node 'A'
> > dfs(graph, 'A')
> > 
> > ```


```python
def dfs(graph, start, visited=None):
    if visited is None:
        visited = set()
    
    visited.add(start)
    print(start)  # Visit the node

    for neighbor in graph[start]:
        if neighbor not in visited:
            dfs(graph, neighbor, visited)
    
    return visited

# Example graph represented as an adjacency list
graph = {
    'A': ['B', 'C'],
    'B': ['A', 'D', 'E'],
    'C': ['A', 'F'],
    'D': ['B'],
    'E': ['B', 'F'],
    'F': ['C', 'E']
}

# Start DFS from node 'A'
dfs(graph, 'A')

```


other content

::: tabs

@tab python
```python
def dfs(graph, start, visited=None):
    if visited is None:
        visited = set()
    
    visited.add(start)
    print(start)  # Visit the node

    for neighbor in graph[start]:
        if neighbor not in visited:
            dfs(graph, neighbor, visited)
    
    return visited

# Example graph represented as an adjacency list
graph = {
    'A': ['B', 'C'],
    'B': ['A', 'D', 'E'],
    'C': ['A', 'F'],
    'D': ['B'],
    'E': ['B', 'F'],
    'F': ['C', 'E']
}

# Start DFS from node 'A'
dfs(graph, 'A')

```
...

@tab java
```java
import java.util.*;

public class DFSRecursive {
    private Map<String, List<String>> graph = new HashMap<>();

    public void addEdge(String node, String neighbor) {
        graph.computeIfAbsent(node, k -> new ArrayList<>()).add(neighbor);
        graph.computeIfAbsent(neighbor, k -> new ArrayList<>()).add(node); // for undirected graph
    }

    public void dfs(String start) {
        Set<String> visited = new HashSet<>();
        dfsHelper(start, visited);
    }

    private void dfsHelper(String node, Set<String> visited) {
        visited.add(node);
        System.out.println(node);

        for (String neighbor : graph.get(node)) {
            if (!visited.contains(neighbor)) {
                dfsHelper(neighbor, visited);
            }
        }
    }

    public static void main(String[] args) {
        DFSRecursive dfs = new DFSRecursive();
        dfs.addEdge("A", "B");
        dfs.addEdge("A", "C");
        dfs.addEdge("B", "D");
        dfs.addEdge("B", "E");
        dfs.addEdge("C", "F");
        dfs.addEdge("E", "F");

        dfs.dfs("A");
    }
}

```
...

@tab C++
```C++
#include <iostream>
#include <map>
#include <vector>
#include <set>
using namespace std;

class DFSRecursive {
    map<char, vector<char>> graph;

public:
    void addEdge(char node, char neighbor) {
        graph[node].push_back(neighbor);
        graph[neighbor].push_back(node); // for undirected graph
    }

    void dfs(char start) {
        set<char> visited;
        dfsHelper(start, visited);
    }

private:
    void dfsHelper(char node, set<char>& visited) {
        visited.insert(node);
        cout << node << endl;

        for (char neighbor : graph[node]) {
            if (visited.find(neighbor) == visited.end()) {
                dfsHelper(neighbor, visited);
            }
        }
    }
};

int main() {
    DFSRecursive dfs;
    dfs.addEdge('A', 'B');
    dfs.addEdge('A', 'C');
    dfs.addEdge('B', 'D');
    dfs.addEdge('B', 'E');
    dfs.addEdge('C', 'F');
    dfs.addEdge('E', 'F');

    dfs.dfs('A');

    return 0;
}

```
...

:::


## Code
[title2tab]

### python
```python
def dfs(graph, start, visited=None):
    if visited is None:
        visited = set()
    
    visited.add(start)
    print(start)  # Visit the node

    for neighbor in graph[start]:
        if neighbor not in visited:
            dfs(graph, neighbor, visited)
    
    return visite
# Example graph represented as an adjacency list
graph = {
    'A': ['B', 'C'],
    'B': ['A', 'D', 'E'],
    'C': ['A', 'F'],
    'D': ['B'],
    'E': ['B', 'F'],
    'F': ['C', 'E']
}

# Start DFS from node 'A'
dfs(graph, 'A')
```