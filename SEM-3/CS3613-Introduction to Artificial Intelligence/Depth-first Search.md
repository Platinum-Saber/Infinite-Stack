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
> 
> > [!code]- Java
> > ```java
> > import java.util.* ;
> > 
> > public class DFSRecursive {
> >    private Map<String, List<String>> graph = new HashMap<> ();
>  >   public void addEdge(String node, String neighbor) {
>  >        graph.computeIfAbsent(node, k -> new ArrayList<>()).add(neighbor);
>  >       graph.computeIfAbsent(neighbor, k -> new ArrayList<>()).add(node); 
>  >    }
> 
>     public void dfs(String start) {
>         Set<String> visited = new HashSet<>();
>         dfsHelper(start, visited);
>     }
> 
>     private void dfsHelper(String node, Set<String> visited) {
>         visited.add(node);
>         System.out.println(node);
> 
>         for (String neighbor : graph.get(node)) {
>             if (!visited.contains(neighbor)) {
>                 dfsHelper(neighbor, visited);
>             }
>         }
>     }
> 
>     public static void main(String[] args) {
>         DFSRecursive dfs = new DFSRecursive();
>         dfs.addEdge("A", "B");
>         dfs.addEdge("A", "C");
>         dfs.addEdge("B", "D");
>         dfs.addEdge("B", "E");
>         dfs.addEdge("C", "F");
>         dfs.addEdge("E", "F");
> 
>         dfs.dfs("A");
>     }
> }
> ```




