# ROS 2 Foxy: Workspace → Package → Node → Custom Messages → Topics

> [!info] Target OS: **Ubuntu 20.04** (Foxy). Shell: **bash**. All commands are terminal‑ready.

---

## 0) Prereqs (one‑time)

- Install **ROS 2 Foxy** and `colcon` per the official instructions.
- Ensure your environment is clean: `source /opt/ros/foxy/setup.bash` in any terminal where you use ROS 2.

---

## 1) Create a workspace and build it

```bash
# 1) Make an overlay workspace
mkdir -p ~/ros2_ws/src
cd ~/ros2_ws

# 2) First (empty) build to lay out install/ and build/
colcon build

# 3) Source the overlay (do this in each new terminal)
source ~/ros2_ws/install/setup.bash

# Optional: persist the overlay in bashrc
printf '\n# ROS 2 Foxy overlay\nsource ~/ros2_ws/install/setup.bash\n' >> ~/.bashrc
```

Why overlays matter: you can stack workspaces; packages in your overlay take precedence over the underlay.

---

## 2) Create your first package (C++ or Python)

### Option A — C++ package (ament_cmake)

```bash
cd ~/ros2_ws/src
ros2 pkg create --build-type ament_cmake --dependencies rclcpp std_msgs demo_cpp_pkg
```

This creates `CMakeLists.txt`, `package.xml`, and a source directory.

Add a minimal publisher node:

```bash
mkdir -p ~/ros2_ws/src/demo_cpp_pkg/src
cat > ~/ros2_ws/src/demo_cpp_pkg/src/talker.cpp <<'CPP'
#include <chrono>
#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
using namespace std::chrono_literals;

class Talker : public rclcpp::Node {
public:
  Talker() : Node("talker"), count_(0) {
    pub_ = this->create_publisher<std_msgs::msg::String>("/chatter", 10);
    timer_ = this->create_wall_timer(500ms, [this]{
      auto msg = std_msgs::msg::String();
      msg.data = "Hello ROS 2 #" + std::to_string(count_++);
      pub_->publish(msg);
    });
  }
private:
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;
  size_t count_;
};

int main(int argc, char ** argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Talker>());
  rclcpp::shutdown();
  return 0;
}
CPP
```

Register the executable in **CMakeLists.txt** (inside `demo_cpp_pkg`):

```cmake
add_executable(talker src/talker.cpp)
ament_target_dependencies(talker rclcpp std_msgs)
install(TARGETS talker DESTINATION lib/${PROJECT_NAME})
```

### Option B — Python package (ament_python)

```bash
cd ~/ros2_ws/src
ros2 pkg create --build-type ament_python --dependencies rclpy std_msgs demo_py_pkg
```

Create a minimal publisher node:

```bash
mkdir -p ~/ros2_ws/src/demo_py_pkg/demo_py_pkg
cat > ~/ros2_ws/src/demo_py_pkg/demo_py_pkg/talker.py <<'PY'
import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class Talker(Node):
    def __init__(self):
        super().__init__('talker')
        self.pub = self.create_publisher(String, '/chatter', 10)
        self.timer = self.create_timer(0.5, self.tick)
        self.count = 0
    def tick(self):
        msg = String()
        msg.data = f'Hello ROS 2 #{self.count}'
        self.count += 1
        self.pub.publish(msg)

def main():
    rclpy.init()
    rclpy.spin(Talker())
    rclpy.shutdown()

if __name__ == '__main__':
    main()
PY
```

Expose the entry point in `setup.cfg` (or `setup.py`):

```ini
[options.entry_points]
console_scripts =
    talker = demo_py_pkg.talker:main
```

Build & run either package:

```bash
cd ~/ros2_ws
colcon build --packages-select demo_cpp_pkg demo_py_pkg
source install/setup.bash
# Run C++
ros2 run demo_cpp_pkg talker
# Or run Python
ros2 run demo_py_pkg talker
```

In another terminal:

```bash
source ~/ros2_ws/install/setup.bash
ros2 topic echo /chatter
```

---

## 3) Add a subscriber and connect via a topic

### C++ listener (subscribe to `/chatter`)

```bash
cat > ~/ros2_ws/src/demo_cpp_pkg/src/listener.cpp <<'CPP'
#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

class Listener : public rclcpp::Node {
public:
  Listener() : Node("listener") {
    sub_ = this->create_subscription<std_msgs::msg::String>(
      "/chatter", 10,
      [this](std_msgs::msg::String::SharedPtr msg){
        RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
      });
  }
private:
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
};

int main(int argc, char ** argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Listener>());
  rclcpp::shutdown();
  return 0;
}
CPP
```

Update CMake to install it:

```cmake
add_executable(listener src/listener.cpp)
ament_target_dependencies(listener rclcpp std_msgs)
install(TARGETS listener DESTINATION lib/${PROJECT_NAME})
```

Rebuild and run:

```bash
cd ~/ros2_ws && colcon build --packages-select demo_cpp_pkg
source install/setup.bash
ros2 run demo_cpp_pkg listener
```

Now you have publisher ↔ subscriber connected via **topic `/chatter`**.

Useful CLI:

```bash
ros2 topic list
ros2 topic info /chatter
ros2 topic hz /chatter
```

---

## 4) Define a **custom message** (interfaces) and use it

We’ll make a new package that defines a message `RangeBearing.msg`, and then use it from a publisher/subscriber.

### 4.1 Create an interface package

```bash
cd ~/ros2_ws/src
ros2 pkg create --build-type ament_cmake custom_interfaces
mkdir -p custom_interfaces/msg
cat > custom_interfaces/msg/RangeBearing.msg <<'MSG'
# Simple 2D polar reading (e.g., LiDAR hit summary)
std_msgs/Header header
float32 range_m       # meters
float32 bearing_rad   # radians
float32 intensity     # optional strength
MSG
```

### 4.2 Wire up `CMakeLists.txt` and `package.xml`

**CMakeLists.txt** (key parts):

```cmake
find_package(rosidl_default_generators REQUIRED)
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/RangeBearing.msg"
  DEPENDENCIES std_msgs
)
ament_export_dependencies(rosidl_default_runtime)
```

**package.xml** (key deps):

```xml
<buildtool_depend>ament_cmake</buildtool_depend>
<depend>std_msgs</depend>
<build_depend>rosidl_default_generators</build_depend>
<exec_depend>rosidl_default_runtime</exec_depend>
```

### 4.3 Build and verify interfaces

```bash
cd ~/ros2_ws
colcon build --packages-select custom_interfaces
source install/setup.bash
ros2 interface show custom_interfaces/msg/RangeBearing
```

### 4.4 Use the custom message in a publisher

Create a new C++ node in `demo_cpp_pkg`:

```bash
cat > ~/ros2_ws/src/demo_cpp_pkg/src/range_bearing_pub.cpp <<'CPP'
#include <chrono>
#include <rclcpp/rclcpp.hpp>
#include <custom_interfaces/msg/range_bearing.hpp>
using namespace std::chrono_literals;

class RBPub : public rclcpp::Node {
public:
  RBPub() : Node("rb_pub") {
    pub_ = this->create_publisher<custom_interfaces::msg::RangeBearing>(
      "/rb", rclcpp::SensorDataQoS());
    timer_ = this->create_wall_timer(100ms, [this]{
      custom_interfaces::msg::RangeBearing msg;
      msg.header.stamp = now();
      msg.range_m = 1.23f; msg.bearing_rad = 0.5f; msg.intensity = 200.f;
      pub_->publish(msg);
    });
  }
private:
  rclcpp::Publisher<custom_interfaces::msg::RangeBearing>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char** argv){
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<RBPub>());
  rclcpp::shutdown();
  return 0;
}
CPP
```

Add to **CMakeLists.txt** for `demo_cpp_pkg`:

```cmake
find_package(custom_interfaces REQUIRED)
ament_target_dependencies(rbp custom_interfaces rclcpp)
# If you named the target 'rbp' above:
add_executable(rbp src/range_bearing_pub.cpp)
ament_target_dependencies(rbp rclcpp custom_interfaces)
install(TARGETS rbp DESTINATION lib/${PROJECT_NAME})
```

Rebuild:

```bash
colcon build --packages-select custom_interfaces demo_cpp_pkg
source install/setup.bash
ros2 run demo_cpp_pkg rbp
```

### 4.5 Subscribe to the custom topic (Python)

```bash
cat > ~/ros2_ws/src/demo_py_pkg/demo_py_pkg/rb_sub.py <<'PY'
import rclpy
from rclpy.node import Node
from custom_interfaces.msg import RangeBearing

class RBSub(Node):
    def __init__(self):
        super().__init__('rb_sub')
        self.create_subscription(RangeBearing, '/rb', self.cb, 10)
    def cb(self, msg):
        self.get_logger().info(f"r={msg.range_m:.2f} m, b={msg.bearing_rad:.2f} rad, I={msg.intensity:.1f}")

def main():
    rclpy.init(); rclpy.spin(RBSub()); rclpy.shutdown()
if __name__ == '__main__':
    main()
PY
```

Expose the entry point in `demo_py_pkg/setup.cfg`:

```ini
[options.entry_points]
console_scripts =
    rb_sub = demo_py_pkg.rb_sub:main
```

Rebuild and run:

```bash
colcon build --packages-select demo_py_pkg
source install/setup.bash
ros2 run demo_py_pkg rb_sub
```

---

## 5) Connect nodes through topics (and inspect the graph)

```bash
# Discover
ros2 topic list
ros2 node list
ros2 interface list

# Inspect a topic
ros2 topic info /rb
ros2 topic type /rb
ros2 topic echo /rb

# Performance check
ros2 topic hz /rb
```

---

## 6) Add a launch file to bring both nodes up together

Create `demo_bringup` (Python launch):

```bash
cd ~/ros2_ws/src
ros2 pkg create --build-type ament_python demo_bringup
mkdir -p demo_bringup/launch
cat > demo_bringup/launch/demo.launch.py <<'PY'
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(package='demo_cpp_pkg', executable='rbp', name='rb_pub'),
        Node(package='demo_py_pkg', executable='rb_sub', name='rb_sub'),
    ])
PY
# setup.cfg entry points not needed for launch files; just ensure package is buildable
```

Build & launch:

```bash
cd ~/ros2_ws && colcon build --packages-select demo_bringup demo_cpp_pkg demo_py_pkg custom_interfaces
source install/setup.bash
ros2 launch demo_bringup demo.launch.py
```

---

## 7) QoS tips for sensors (LiDAR, IMU, cameras)

- Use **`rclcpp::SensorDataQoS()`** or equivalent when publishing fast sensor streams so late subscribers don’t block reliability.
    
- For reliable delivery (e.g., commands), prefer `ReliabilityPolicy::Reliable` with a small queue depth.
    

---

## 8) Common pitfalls & fixes

- **Forgot to source overlay**: no packages found → `source ~/ros2_ws/install/setup.bash`.
- **Colcon build order**: build interfaces **before** packages that depend on them.
- **Package.xml/CMakeLists**: if custom message not found, confirm `rosidl_default_generators` in build deps and `rosidl_default_runtime` in exec deps.
- **Multiple terminals**: source in each, or add to `~/.bashrc`.
- **Name mismatches**: topic `/rb` vs `/RB` are different; avoid accidental typos.

---

## 9) Where to go next

- Add timers, parameters, and diagnostics.
- Replace the mock `RangeBearing` values with real LiDAR parsing on your MCU and forward to this ROS graph via micro‑ROS → Agent → DDS.