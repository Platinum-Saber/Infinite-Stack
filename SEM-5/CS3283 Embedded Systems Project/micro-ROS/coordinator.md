# ascilam_coordinator (ROS 2 Foxy)

End-to-end coordinator for two LD19P-equipped scouts streaming **raw LD19 frames over UDP**. The coordinator parses packets, converts to **LaserScan** in a right‑handed frame, and fuses scans from both robots into a **nav_msgs/OccupancyGrid** using log‑odds. Designed for Ubuntu 20.04 + ROS 2 Foxy on Raspberry Pi 4.

---

## Package layout

```
ascilam_coordinator/
├─ package.xml
├─ setup.py
├─ ascilam_coordinator/
│  ├─ __init__.py
│  ├─ udp_ld19_receiver.py         # one instance per robot (port)
│  ├─ occupancy_grid_mapper.py     # multi-robot map fusion (1 m mapping radius)
│  └─ pose_relay.py                # helper: set/stream robot poses (Pose2D)
├─ launch/
│  └─ coord.launch.py
├─ params/
│  └─ coord.yaml
└─ rviz/
   └─ coord.rviz (optional)
```

---

## `package.xml`

```xml
<?xml version="1.0"?>
<package format="3">
  <name>ascilam_coordinator</name>
  <version>0.1.0</version>
  <description>Coordinator: UDP LD19 frame receivers (2 robots) + occupancy grid fusion (ROS 2 Foxy)</description>
  <maintainer email="you@example.com">ASCILAM</maintainer>
  <license>MIT</license>

  <buildtool_depend>ament_python</buildtool_depend>

  <exec_depend>rclpy</exec_depend>
  <exec_depend>std_msgs</exec_depend>
  <exec_depend>sensor_msgs</exec_depend>
  <exec_depend>geometry_msgs</exec_depend>
  <exec_depend>nav_msgs</exec_depend>
  <exec_depend>visualization_msgs</exec_depend>
  <exec_depend>tf2_ros</exec_depend>
  <exec_depend>tf2_geometry_msgs</exec_depend>

  <test_depend>ament_lint_auto</test_depend>
  <test_depend>ament_lint_common</test_depend>
</package>
```

## `setup.py`

```python
from setuptools import setup
from glob import glob
import os

package_name = 'ascilam_coordinator'

setup(
    name=package_name,
    version='0.1.0',
    packages=[package_name],
    data_files=[
        (os.path.join('share', package_name), ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob('launch/*.py')),
        (os.path.join('share', package_name, 'params'), glob('params/*.yaml')),
        (os.path.join('share', package_name, 'rviz'), glob('rviz/*.rviz')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='ASCILAM',
    maintainer_email='you@example.com',
    description='UDP LD19 receivers + occupancy grid fusion',
    license='MIT',
    entry_points={
        'console_scripts': [
            'udp_ld19_receiver = ascilam_coordinator.udp_ld19_receiver:main',
            'occupancy_grid_mapper = ascilam_coordinator.occupancy_grid_mapper:main',
            'pose_relay = ascilam_coordinator.pose_relay:main',
        ],
    },
)
```

## `ascilam_coordinator/udp_ld19_receiver.py`

```python
import socket
import struct
import threading
from collections import deque
import math

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import LaserScan

# LD19 frame constants
HEADER = 0x54
POINTS_PER_PACK = 12
FRAME_LEN = 47  # 1+1+2+2 + 12*(2+1) + 2+2+1

CRC_TABLE = [
    0x00,0x4D,0x9A,0xD7,0x79,0x34,0xE3,0xAE,0xF2,0xBF,0x68,0x25,0x8B,0xC6,0x11,0x5C,
    0xA9,0xE4,0x33,0x7E,0xD0,0x9D,0x4A,0x07,0x5B,0x16,0xC1,0x8C,0x22,0x6F,0xB8,0xF5,
    0x1F,0x52,0x85,0xC8,0x66,0x2B,0xFC,0xB1,0xED,0xA0,0x77,0x3A,0x94,0xD9,0x0E,0x43,
    0xB6,0xFB,0x2C,0x61,0xCF,0x82,0x55,0x18,0x44,0x09,0xDE,0x93,0x3D,0x70,0xA7,0xEA,
    0x3E,0x73,0xA4,0xE9,0x47,0x0A,0xDD,0x90,0xCC,0x81,0x56,0x1B,0xB5,0xF8,0x2F,0x62,
    0x97,0xDA,0x0D,0x40,0xEE,0xA3,0x74,0x39,0x65,0x28,0xFF,0xB2,0x1C,0x51,0x86,0xCB,
    0x21,0x6C,0xBB,0xF6,0x58,0x15,0xC2,0x8F,0xD3,0x9E,0x49,0x04,0xAA,0xE7,0x30,0x7D,
    0x88,0xC5,0x12,0x5F,0xF1,0xBC,0x6B,0x26,0x7A,0x37,0xE0,0xAD,0x03,0x4E,0x99,0xD4,
    0x7C,0x31,0xE6,0xAB,0x05,0x48,0x9F,0xD2,0x8E,0xC3,0x14,0x59,0xF7,0xBA,0x6D,0x20,
    0xD5,0x98,0x4F,0x02,0xAC,0xE1,0x36,0x7B,0x27,0x6A,0xBD,0xF0,0x5E,0x13,0xC4,0x89,
    0x63,0x2E,0xF9,0xB4,0x1A,0x57,0x80,0xCD,0x91,0xDC,0x0B,0x46,0xE8,0xA5,0x72,0x3F,
    0xCA,0x87,0x50,0x1D,0xB3,0xFE,0x29,0x64,0x38,0x75,0xA2,0xEF,0x41,0x0C,0xDB,0x96,
    0x42,0x0F,0xD8,0x95,0x3B,0x76,0xA1,0xEC,0xB0,0xFD,0x2A,0x67,0xC9,0x84,0x53,0x1E,
    0xEB,0xA6,0x71,0x3C,0x92,0xDF,0x08,0x45,0x19,0x54,0x83,0xCE,0x60,0x2D,0xFA,0xB7,
    0x5D,0x10,0xC7,0x8A,0x24,0x69,0xBE,0xF3,0xAF,0xE2,0x35,0x78,0xD6,0x9B,0x4C,0x01,
    0xF4,0xB9,0x6E,0x23,0x8D,0xC0,0x17,0x5A,0x06,0x4B,0x9C,0xD1,0x7F,0x32,0xE5,0xA8
]

def crc8(data: bytes) -> int:
    c = 0
    for b in data:
        c = CRC_TABLE[(c ^ b) & 0xFF]
    return c

class UdpLD19Receiver(Node):
    def __init__(self):
        super().__init__('udp_ld19_receiver')
        self.declare_parameter('udp_port', 5001)
        self.declare_parameter('frame_id', 'robot1_laser')
        self.declare_parameter('robot_namespace', 'robot1')
        self.declare_parameter('publish_topic', 'scan')
        self.declare_parameter('intensity_threshold', 0)  # keep all

        self.port = int(self.get_parameter('udp_port').value)
        self.frame_id = self.get_parameter('frame_id').value
        ns = self.get_parameter('robot_namespace').value
        topic = self.get_parameter('publish_topic').value
        self.intensity_threshold = int(self.get_parameter('intensity_threshold').value)

        self.pub = self.create_publisher(LaserScan, f'/{ns}/{topic}', 10)

        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind(('0.0.0.0', self.port))
        self.sock.setblocking(False)

        self.buffer = bytearray()
        self.timer = self.create_timer(0.002, self.read_udp)  # poll ~500 Hz

        self.get_logger().info(f'Listening for LD19 frames on UDP :{self.port}, publishing LaserScan on /{ns}/{topic}')

    def read_udp(self):
        try:
            while True:
                chunk, _ = self.sock.recvfrom(4096)
                self.buffer.extend(chunk)
        except BlockingIOError:
            pass
        # parse as many frames as possible
        idx = 0
        while len(self.buffer) - idx >= FRAME_LEN:
            if self.buffer[idx] != HEADER:
                idx += 1
                continue
            frame = self.buffer[idx:idx+FRAME_LEN]
            # verify ver_len and crc
            ver_len = frame[1]
            if ver_len != 0x2C:
                idx += 1
                continue
            if crc8(frame[:-1]) != frame[-1]:
                idx += 1
                continue
            self.publish_scan(frame)
            idx += FRAME_LEN
        if idx:
            del self.buffer[:idx]

    def publish_scan(self, frame: bytes):
        # Unpack header
        # [0]=0x54, [1]=0x2C
        speed_dps = struct.unpack_from('<H', frame, 2)[0]
        start_angle_cdeg = struct.unpack_from('<H', frame, 4)[0]   # 0.01 deg
        # 12 points follow starting at offset 6
        points = []
        off = 6
        for i in range(POINTS_PER_PACK):
            dist_mm = struct.unpack_from('<H', frame, off)[0]
            inten = frame[off+2]
            off += 3
            points.append((dist_mm, inten))
        end_angle_cdeg = struct.unpack_from('<H', frame, off)[0]; off += 2
        timestamp_ms = struct.unpack_from('<H', frame, off)[0]    # not used
        # Convert angles (CW, left-handed) -> CCW right-handed
        n = len(points)
        start_deg = start_angle_cdeg / 100.0
        end_deg = end_angle_cdeg / 100.0
        # handle wrap-around for interpolation
        span = (end_deg - start_deg)
        if span < 0:
            span += 360.0
        step = span / max(1, (n - 1))
        angles_ros = []
        ranges = []
        for i, (dmm, inten) in enumerate(points):
            if self.intensity_threshold and inten < self.intensity_threshold:
                r = float('inf')
            else:
                r = dmm / 1000.0
            theta_ld = math.radians((start_deg + step * i) % 360.0)
            theta_ros = (2.0 * math.pi - theta_ld) % (2.0 * math.pi)  # convert CW->CCW
            angles_ros.append(theta_ros)
            ranges.append(r if r > 0.0 else float('inf'))
        # Sort by angle to satisfy LaserScan monotonic requirement
        zipped = sorted(zip(angles_ros, ranges))
        angles_sorted = [a for a, _ in zipped]
        ranges_sorted = [r for _, r in zipped]
        # Prepare LaserScan
        msg = LaserScan()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.header.frame_id = self.frame_id
        msg.angle_min = angles_sorted[0]
        msg.angle_max = angles_sorted[-1]
        if len(angles_sorted) > 1:
            msg.angle_increment = (angles_sorted[-1] - angles_sorted[0]) / (len(angles_sorted) - 1)
        else:
            msg.angle_increment = 0.0
        msg.range_min = 0.05
        msg.range_max = 12.0
        msg.ranges = ranges_sorted
        msg.intensities = []
        self.pub.publish(msg)


def main():
    rclpy.init()
    node = UdpLD19Receiver()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

```

## `ascilam_coordinator/occupancy_grid_mapper.py`

```python
import math
import numpy as np
from typing import Tuple

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import LaserScan
from geometry_msgs.msg import Pose2D
from nav_msgs.msg import OccupancyGrid, MapMetaData
from visualization_msgs.msg import Marker, MarkerArray

LOG_ODDS_HIT = 0.85
LOG_ODDS_MISS = -0.4
LOG_ODDS_MIN = -4.0
LOG_ODDS_MAX = 4.0

class GridMapper(Node):
    def __init__(self):
        super().__init__('occupancy_grid_mapper')
        # Params: map size (m), resolution (m/cell), origin (world coords of map[0,0])
        self.declare_parameter('width_m', 20.0)
        self.declare_parameter('height_m', 20.0)
        self.declare_parameter('resolution', 0.1)
        self.declare_parameter('origin_x', 0.0)
        self.declare_parameter('origin_y', 0.0)
        self.declare_parameter('mapping_radius_m', 1.0)
        self.declare_parameter('robot_names', ['robot1','robot2'])

        self.width_m = float(self.get_parameter('width_m').value)
        self.height_m = float(self.get_parameter('height_m').value)
        self.res = float(self.get_parameter('resolution').value)
        self.origin = (float(self.get_parameter('origin_x').value), float(self.get_parameter('origin_y').value))
        self.r_map = float(self.get_parameter('mapping_radius_m').value)
        self.robot_names = [str(x) for x in self.get_parameter('robot_names').value]

        self.w = int(round(self.width_m / self.res))
        self.h = int(round(self.height_m / self.res))
        self.log_odds = np.zeros((self.h, self.w), dtype=np.float32)
        self.occ_grid = OccupancyGrid()
        self.occ_grid.header.frame_id = 'map'
        self.occ_grid.info = MapMetaData()
        self.occ_grid.info.resolution = self.res
        self.occ_grid.info.width = self.w
        self.occ_grid.info.height = self.h
        self.occ_grid.info.origin.position.x = self.origin[0]
        self.occ_grid.info.origin.position.y = self.origin[1]
        self.occ_grid.info.origin.orientation.w = 1.0

        # Poses
        self.poses = {name: Pose2D() for name in self.robot_names}

        # Subscribers
        for name in self.robot_names:
            self.create_subscription(LaserScan, f'/{name}/scan', lambda msg, n=name: self.scan_cb(n, msg), 10)
            self.create_subscription(Pose2D, f'/{name}/pose2d', lambda msg, n=name: self.pose_cb(n, msg), 10)

        # Publishers
        self.map_pub = self.create_publisher(OccupancyGrid, 'global_map', 1)
        self.marker_pub = self.create_publisher(MarkerArray, 'hit_points', 1)

        self.timer = self.create_timer(0.2, self.publish_map)
        self.get_logger().info(f'Grid {self.w}x{self.h} at {self.res} m/cell. Origin {self.origin}. Robots: {self.robot_names}')

    def pose_cb(self, name: str, msg: Pose2D):
        self.poses[name] = msg

    def world_to_cell(self, x: float, y: float) -> Tuple[int,int]:
        cx = int((x - self.origin[0]) / self.res)
        cy = int((y - self.origin[1]) / self.res)
        return cx, cy

    def in_bounds(self, cx:int, cy:int) -> bool:
        return 0 <= cx < self.w and 0 <= cy < self.h

    def bresenham(self, x0, y0, x1, y1):
        # integer grid line traversal
        dx = abs(x1 - x0); sx = 1 if x0 < x1 else -1
        dy = -abs(y1 - y0); sy = 1 if y0 < y1 else -1
        err = dx + dy
        x, y = x0, y0
        points = []
        while True:
            points.append((x, y))
            if x == x1 and y == y1:
                break
            e2 = 2 * err
            if e2 >= dy:
                err += dy
                x += sx
            if e2 <= dx:
                err += dx
                y += sy
        return points

    def scan_cb(self, name: str, scan: LaserScan):
        pose = self.poses[name]
        rx, ry, rth = pose.x, pose.y, pose.theta
        # Robot cell
        rcx, rcy = self.world_to_cell(rx, ry)
        if not self.in_bounds(rcx, rcy):
            return
        # Collect marker points for visualization (optional)
        markers = []
        for i, r in enumerate(scan.ranges):
            if not math.isfinite(r):
                continue
            if r <= 0.01 or r > scan.range_max:
                continue
            if r > self.r_map:
                # Only map within specified radius
                continue
            angle = scan.angle_min + i * scan.angle_increment
            th = rth + angle
            wx = rx + r * math.cos(th)
            wy = ry + r * math.sin(th)
            cx, cy = self.world_to_cell(wx, wy)
            if not self.in_bounds(cx, cy):
                continue
            # Raytrace free cells up to the hit
            for (fx, fy) in self.bresenham(rcx, rcy, cx, cy)[:-1]:
                if self.in_bounds(fx, fy):
                    self.log_odds[fy, fx] = np.clip(self.log_odds[fy, fx] + LOG_ODDS_MISS, LOG_ODDS_MIN, LOG_ODDS_MAX)
            # Mark occupied
            self.log_odds[cy, cx] = np.clip(self.log_odds[cy, cx] + LOG_ODDS_HIT, LOG_ODDS_MIN, LOG_ODDS_MAX)
        # Optional: publish hit markers sparsely (rate limited by timer)

    def publish_map(self):
        self.occ_grid.header.stamp = self.get_clock().now().to_msg()
        # Convert log-odds -> probability -> occupancy [0..100], unknown -1
        probs = 1.0 - 1.0 / (1.0 + np.exp(self.log_odds))
        grid = np.full((self.h, self.w), -1, dtype=np.int8)
        occ = (probs > 0.65)
        free = (probs < 0.35)
        grid[free] = 0
        grid[occ] = 100
        self.occ_grid.data = grid.flatten(order='C').tolist()
        self.map_pub.publish(self.occ_grid)


def main():
    rclpy.init()
    node = GridMapper()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()
```

## `ascilam_coordinator/pose_relay.py`

```python
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Pose2D

class PoseRelay(Node):
    def __init__(self):
        super().__init__('pose_relay')
        # Simple node to set / update robot poses via params or topic remaps
        self.declare_parameter('robot_names', ['robot1','robot2'])
        self.declare_parameter('initial_poses', [0.5,0.5,0.0,  3.5,0.5,0.0])  # [x1,y1,th1, x2,y2,th2]
        names = [str(x) for x in self.get_parameter('robot_names').value]
        vals = [float(v) for v in self.get_parameter('initial_poses').value]
        assert len(vals) == 3*len(names)
        self.pubs = {}
        for i, name in enumerate(names):
            pub = self.create_publisher(Pose2D, f'/{name}/pose2d', 10)
            self.pubs[name] = pub
            msg = Pose2D()
            msg.x, msg.y, msg.theta = vals[3*i], vals[3*i+1], vals[3*i+2]
            pub.publish(msg)
        self.timer = self.create_timer(0.5, self.repub)
        self._last = vals

    def repub(self):
        # keep republishing last poses (helps simple demos)
        vals = self._last
        i = 0
        for name, pub in self.pubs.items():
            msg = Pose2D()
            msg.x, msg.y, msg.theta = vals[3*i], vals[3*i+1], vals[3*i+2]
            pub.publish(msg)
            i += 1


def main():
    rclpy.init()
    node = PoseRelay()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()
```

## `launch/coord.launch.py`

```python
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration
from launch.actions import DeclareLaunchArgument
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument('params', default_value='$(find-pkg-share ascilam_coordinator)/params/coord.yaml'),

        # Robot 1 UDP receiver
        Node(
            package='ascilam_coordinator',
            executable='udp_ld19_receiver',
            name='udp_ld19_receiver_r1',
            output='screen',
            parameters=[{
                'udp_port': 6001,
                'frame_id': 'robot1_laser',
                'robot_namespace': 'robot1',
            }]
        ),
        # Robot 2 UDP receiver
        Node(
            package='ascilam_coordinator',
            executable='udp_ld19_receiver',
            name='udp_ld19_receiver_r2',
            output='screen',
            parameters=[{
                'udp_port': 6002,
                'frame_id': 'robot2_laser',
                'robot_namespace': 'robot2',
            }]
        ),
        # Poses (set starting coordinates & headings)
        Node(
            package='ascilam_coordinator',
            executable='pose_relay',
            name='pose_relay',
            output='screen',
            parameters=['$(var params)']
        ),
        # Mapper
        Node(
            package='ascilam_coordinator',
            executable='occupancy_grid_mapper',
            name='grid_mapper',
            output='screen',
            parameters=['$(var params)']
        ),
    ])
```

## `params/coord.yaml`

```yaml
ascilam_coordinator:
  ros__parameters:
    # Map defines a rectangular working area (meters)
    width_m: 8.0
    height_m: 6.0
    resolution: 0.10            # 10 cm cells
    origin_x: 0.0               # world coords of cell (0,0)
    origin_y: 0.0
    mapping_radius_m: 1.0
    robot_names: [robot1, robot2]

pose_relay:
  ros__parameters:
    robot_names: [robot1, robot2]
    # [x1, y1, th1,  x2, y2, th2] (radians)
    initial_poses: [1.0, 1.0, 0.0,  6.0, 1.0, 0.0]
```

---

## Build & run

```bash
# On the Raspberry Pi 4 (Ubuntu 20.04 + ROS 2 Foxy)
mkdir -p ~/ros2_ws/src
cd ~/ros2_ws/src
# drop this package folder here
# (copy ascilam_coordinator/ into ~/ros2_ws/src)

cd ..
colcon build --symlink-install
source install/setup.bash

# Launch (ports 6001 and 6002)
ros2 launch ascilam_coordinator coord.launch.py
```

### ESP32 UDP format (expected)

Send **raw LD19 frames** (47 bytes each) verbatim over UDP to the coordinator ports:

- Robot 1 → `raspi_ip:6001`
    
- Robot 2 → `raspi_ip:6002`
    

The receiver validates the CRC and converts **clockwise LD19 angles** into ROS‑standard **counterclockwise** `LaserScan` messages, then the mapper updates the occupancy grid within a **1 m** radius from each robot pose.

---

## RViz quick view

- Add **Map** display → Topic: `/global_map`
    
- Add **LaserScan** displays → `/robot1/scan` and `/robot2/scan`
    

---

## Notes

- Mapping uses log‑odds to fuse both robots’ observations; adjust `LOG_ODDS_*` in `occupancy_grid_mapper.py` for sensitivity.
    
- For your “cell‑to‑cell” experiment, publish discrete poses (grid centers) to `/robot*/pose2d` as robots move. The mapper will only consider returns within `mapping_radius_m` (1 m) to mimic limited sensor influence per cell.
    
- If your ESP32 sends pre‑filtered points instead of raw frames, you can adapt `udp_ld19_receiver.py` to accept a simple CSV or binary `(angle_rad, range_m)` list and skip the LD19 parser.