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

