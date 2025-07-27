---
tags: 
Created: 2025-06-30 17:23
About: 
Reviewed: false
Completion: 0
---
**Name** : Waduge S.S.
**Index** : 220673K


## Workspace Setup

```bash
mkdir -p ~/ros2_ws/src
cd ~/ros2_ws
colcon build
source install/setup.bash
````

---

## Package Creation

```bash
cd ~/ros2_ws/src
ros2 pkg create --build-type ament_python ros2_tasks --dependencies rclpy geometry_msgs std_msgs
```

---

## setup.py Configuration

Edit `ros2_tasks/setup.py` → `entry_points` block:

```python
entry_points={
    'console_scripts': [
        'pose_re_pub = ros2_tasks.task1_pose_re_pub:main',
        'params_setter = ros2_tasks.task2_params_setter:main',
        'twist_from_database = ros2_tasks.task3_twist_from_database:main',
        'zero_twist = ros2_tasks.task4_zero_twist:main',
        'param_reader = ros2_tasks.task6_param_reader:main',
    ],
},
```

---

##  Project Structure

```
ros2_ws/
└── src/
    └── ros2_tasks/
        ├── setup.py
        ├── package.xml
        └── ros2_tasks/
            ├── __init__.py
            ├── task1_pose_re_pub.py
            ├── task2_params_setter.py
            ├── task3_twist_from_database.py
            ├── task4_zero_twist.py
            ├── task6_param_reader.py
            ├── values.csv
        └── launch/
            └── test_launch.py
```

---

## Task 1 – `pose_re_pub`

###  Description

Subscribe to `/pose_with_covariance_stamped` and republish only `pose` data.

### Code

```python
# task1_pose_re_pub.py
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import PoseWithCovarianceStamped, Pose

class PoseRepub(Node):
    def __init__(self):
        super().__init__('pose_re_pub')
        self.sub = self.create_subscription(PoseWithCovarianceStamped, 'pose_with_covariance_stamped', self.callback, 10)
        self.pub = self.create_publisher(Pose, 'pose', 10)

    def callback(self, msg):
        pose_msg = msg.pose.pose
        self.pub.publish(pose_msg)

def main():
    rclpy.init()
    rclpy.spin(PoseRepub())
    rclpy.shutdown()
```

### ▶️ Command

```bash
ros2 run ros2_tasks pose_re_pub
```

### Output

![[task1.png]]


---

## Task 2 – `params_setter`

###  Description

Declare and set a custom parameter at runtime.

###  Code

```python
# task2_params_setter.py
import rclpy
from rclpy.node import Node

class ParamSetter(Node):
    def __init__(self):
        super().__init__('params_setter')
        param = 'example_param'
        value = 'hello_ros'
        self.declare_parameter(param, value)
        self.get_logger().info(f'Set parameter {param} = {value}')

def main():
    rclpy.init()
    ParamSetter()
    rclpy.shutdown()
```

### ▶️ Command

```bash
ros2 run ros2_tasks params_setter
```

###  Output

![[task2.png]]


---

## Task 3 – `twist_from_database`

### Description

Reads from `values.csv` and publishes a `Twist` message.

### Sample `values.csv`

```
0.1,0.2,0.3,0.0,0.0,0.1
0.0,0.0,0.0,0.1,0.2,0.3
```

### Code

```python
# task3_twist_from_database.py
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
import csv

class TwistPublisher(Node):
    def __init__(self):
        super().__init__('twist_from_database')
        self.pub = self.create_publisher(Twist, 'twist_from_database', 20)
        self.file = open('values.csv', 'r')
        self.reader = csv.reader(self.file)
        self.timer = self.create_timer(0.1, self.timer_callback)

    def timer_callback(self):
        try:
            line = next(self.reader)
            twist = Twist()
            values = list(map(float, line))
            twist.linear.x, twist.linear.y, twist.linear.z = values[:3]
            twist.angular.x, twist.angular.y, twist.angular.z = values[3:]
            self.pub.publish(twist)
        except StopIteration:
            self.get_logger().info("End of CSV")
            self.timer.cancel()

def main():
    rclpy.init()
    rclpy.spin(TwistPublisher())
    rclpy.shutdown()
```

### ▶️ Command

```bash
ros2 run ros2_tasks twist_from_database
```

### Output

![[task3.png]]

---

## Task 4 – `zero_twist`

### Description

When the `/is_stopped` topic publishes `"true"`, publish zero Twist.

### Code

```python
# task4_zero_twist.py
import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from geometry_msgs.msg import Twist

class ZeroTwist(Node):
    def __init__(self):
        super().__init__('zero_twist')
        self.sub = self.create_subscription(String, 'is_stopped', self.callback, 10)
        self.pub = self.create_publisher(Twist, 'twist', 10)

    def callback(self, msg):
        if msg.data == "true":
            self.pub.publish(Twist())

def main():
    rclpy.init()
    rclpy.spin(ZeroTwist())
    rclpy.shutdown()
```

### ▶️ Command

```bash
ros2 run ros2_tasks zero_twist
```

### Output

![[task4.png]]

---

## Task 5 – Launch File

### File: `launch/test_launch.py`

```python
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import ExecuteProcess

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='ros2_tasks',
            executable='task1_pub',
            name='chatter'
        ),
        Node(
            package='ros2_tasks',
            executable='task5_listener',
            name='listener'
        ),
        ExecuteProcess(
		    cmd=[
		        'bash', '-c',
		        'ros2 topic pub --once /twist geometry_msgs/Twist '
		        "'{linear: {x: 0.0, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 0.0}}'"
		    ],
	   
            shell=True
        )
    ])
```

### ▶️ Command

```bash
ros2 launch ros2_tasks test_launch.py
```

- Add launch and data files in setup.py:
  ```python
  data_files=[
    ('share/ros2_tasks/launch', glob('launch/*.py')),
    ('share/ros2_tasks/data', glob('data/*.csv')),
  ]
  ```
### Output

![[task5.png]]

---

## Task 6 – `param_reader`

### Description

Reads declared parameter and logs it.

### Code

```python
# task6_param_reader.py
import rclpy
from rclpy.node import Node

class ParamReader(Node):
    def __init__(self):
        super().__init__('param_reader')
        self.declare_parameter('robot_name', 'default_bot')
        name = self.get_parameter('robot_name').get_parameter_value().string_value
        self.get_logger().info(f'Robot name: {name}')

def main():
    rclpy.init()
    ParamReader()
    rclpy.shutdown()
```

### ▶️ Command

```bash
ros2 run ros2_tasks param_reader
```

### Output
![[suhantask6.png]]


---

## Build and Source Commands

```bash
cd ~/ros2_ws
colcon build --packages-select ros2_tasks
source install/setup.bash
```




