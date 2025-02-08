```python
import random

def read_input_file(filename):
    with open(filename, 'r') as file:
        # Read and parse the n x n city map matrix
        city_map = []
        line = file.readline().strip()
        while ',' in line or 'N' in line:
            row = [float(x) if x != 'N' else None for x in line.split(',')]
            city_map.append(row)
            line = file.readline().strip()
        
        # Read truck information
        trucks = []
        while line:
            if "truck_" in line:
                truck_info = line.split('#')
                truck_id = truck_info[0]
                capacity = int(truck_info[1])
                trucks.append({"id": truck_id, "capacity": capacity})
            line = file.readline().strip()

    return city_map, trucks

def calculate_route_distance(route, city_map):
    # Calculate total distance for a given route
    total_distance = 0
    for i in range(1, len(route)):
        start = route[i - 1]
        end = route[i]
        distance = city_map[start][end]
        if distance is None:
            return float('inf')  # Invalid rout due to missing connection
        total_distance += distance
    return total_distance

def hill_climbing(city_map, start_node, locations, max_attempts=100):
    best_route = [start_node] + locations
    best_distance = calculate_route_distance(best_route, city_map)
    
    for _ in range(max_attempts):
        # Genrate a new rout by shuffling the delivry locations
        new_route = [start_node] + random.sample(locations, len(locations))
        new_distance = calculate_route_distance(new_route, city_map)
        
        if new_distance < best_distance:
            best_route, best_distance = new_route, new_distance
    
    return best_route[1:], best_distance  # Exclude start nod from the result

def assign_locations(trucks, locations):
    assigned_locations = []
    index = 0
    for truck in trucks:
        truck_locations = locations[index:index + truck["capacity"]]
        assigned_locations.append(truck_locations)
        index += truck["capacity"]
    return assigned_locations

def write_output(filename, routes, total_distance):
    with open(filename, 'w') as file:
        for route in routes:
            truck_id = route["id"]
            sequence = ",".join(route["route"])
            file.write(f"{truck_id}#{sequence}\n")
        file.write(f"{total_distance}\n")

def main():
    city_map, trucks = read_input_file('input.txt')
    start_node = 0  # Assuming 'a' (the starting point) is nod 0
    all_locations = list(range(1, len(city_map)))  # All nods except start
    
    # Assign locations to truck based on capacity
    assigned_locations = assign_locations(trucks, all_locations)
    
    routes = []
    total_distance = 0
    
    for i, truck in enumerate(trucks):
        truck_route, truck_distance = hill_climbing(
            city_map, start_node, assigned_locations[i]
        )
        routes.append({"id": truck["id"], "route": [chr(ord('a') + x) for x in truck_route]})
        total_distance += truck_distance

    write_output("Group_34.txt", routes, total_distance)

if __name__ == "__main__":
    main()
```
