
```cpp
// ESP32_Robot2_Complete.ino
// Complete code for Robot 2 ESP32 with LD19 LiDAR and M-Bot integration
// Same as Robot 1 but with different network settings and namespaces

#include <micro_ros_arduino.h>
#include <stdio.h>
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <sensor_msgs/msg/laser_scan.h>
#include <nav_msgs/msg/odometry.h>
#include <geometry_msgs/msg/twist.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <WiFiUdp.h>

// WiFi Configuration - DIFFERENT PORT FOR ROBOT 2
const char* ssid = "MultiRobot_Network";
const char* password = "multirobot2024";
const char* agent_ip = "192.168.4.1";  // Raspberry Pi IP
const int agent_port = 8889;            // micro-ROS agent port for Robot 2

// Hardware Configuration (same as Robot 1)
#define LIDAR_SERIAL Serial2
#define LIDAR_BAUDRATE 230400
#define LIDAR_RX_PIN 16
#define LIDAR_TX_PIN 17

#define MBOT_SERIAL Serial1
#define MBOT_RX_PIN 4
#define MBOT_TX_PIN 2

#define STATUS_LED 2

// LiDAR packet structure from LD19 manual
#define POINT_PER_PACK 12
#define HEADER 0x54

typedef struct __attribute__((packed)) {
    uint16_t distance;
    uint8_t intensity;
} LidarPointStructDef;

typedef struct __attribute__((packed)) {
    uint8_t header;
    uint8_t ver_len;
    uint16_t speed;
    uint16_t start_angle;
    LidarPointStructDef point[POINT_PER_PACK];
    uint16_t end_angle;
    uint16_t timestamp;
    uint8_t crc8;
} LiDARFrameTypeDef;

// micro-ROS entities
rcl_publisher_t scan_publisher;
rcl_publisher_t odom_publisher;
rcl_subscription_t cmd_vel_subscriber;
rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;
rcl_timer_t timer;

// Messages
sensor_msgs__msg__LaserScan scan_msg;
nav_msgs__msg__Odometry odom_msg;
geometry_msgs__msg__Twist cmd_vel_msg;

// LiDAR data
float ranges[360];
float intensities[360];
bool new_scan_ready = false;

// Robot state
float robot_x = 0.0;
float robot_y = 0.0;
float robot_theta = 0.0;
float last_cmd_linear = 0.0;
float last_cmd_angular = 0.0;
unsigned long last_odom_time = 0;
unsigned long last_cmd_time = 0;

// Connection status
bool wifi_connected = false;
bool micro_ros_connected = false;
unsigned long last_wifi_check = 0;
unsigned long last_status_blink = 0;
bool status_led_state = false;

// Robot parameters
const float wheel_base = 0.15; // meters
const float max_speed = 0.5; // m/s

// CRC table from LD19 manual (same as Robot 1)
static const uint8_t CrcTable[256] = {
    0x00, 0x4d, 0x9a, 0xd7, 0x79, 0x34, 0xe3, 0xae, 0xf2, 0xbf, 0x68, 0x25, 0x8b, 0xc6, 0x11, 0x5c,
    0xa9, 0xe4, 0x33, 0x7e, 0xd0, 0x9d, 0x4a, 0x07, 0x5b, 0x16, 0xc1, 0x8c, 0x22, 0x6f, 0xb8, 0xf5,
    0x1f, 0x52, 0x85, 0xc8, 0x66, 0x2b, 0xfc, 0xb1, 0xed, 0xa0, 0x77, 0x3a, 0x94, 0xd9, 0x0e, 0x43,
    0xb6, 0xfb, 0x2c, 0x61, 0xcf, 0x82, 0x55, 0x18, 0x44, 0x09, 0xde, 0x93, 0x3d, 0x70, 0xa7, 0xea,
    0x3e, 0x73, 0xa4, 0xe9, 0x47, 0x0a, 0xdd, 0x90, 0xcc, 0x81, 0x56, 0x1b, 0xb5, 0xf8, 0x2f, 0x62,
    0x97, 0xda, 0x0d, 0x40, 0xee, 0xa3, 0x74, 0x39, 0x65, 0x28, 0xff, 0xb2, 0x1c, 0x51, 0x86, 0xcb,
    0x21, 0x6c, 0xbb, 0xf6, 0x58, 0x15, 0xc2, 0x8f, 0xd3, 0x9e, 0x49, 0x04, 0xaa, 0xe7, 0x30, 0x7d,
    0x88, 0xc5, 0x12, 0x5f, 0xf1, 0xbc, 0x6b, 0x26, 0x7a, 0x37, 0xe0, 0xad, 0x03, 0x4e, 0x99, 0xd4,
    0x7c, 0x31, 0xe6, 0xab, 0x05, 0x48, 0x9f, 0xd2, 0x8e, 0xc3, 0x14, 0x59, 0xf7, 0xba, 0x6d, 0x20,
    0xd5, 0x98, 0x4f, 0x02, 0xac, 0xe1, 0x36, 0x7b, 0x27, 0x6a, 0xbd, 0xf0, 0x5e, 0x13, 0xc4, 0x89,
    0x63, 0x2e, 0xf9, 0xb4, 0x1a, 0x57, 0x80, 0xcd, 0x91, 0xdc, 0x0b, 0x46, 0xe8, 0xa5, 0x72, 0x3f,
    0xca, 0x87, 0x50, 0x1d, 0xb3, 0xfe, 0x29, 0x64, 0x38, 0x75, 0xa2, 0xef, 0x41, 0x0c, 0xdb, 0x96,
    0x42, 0x0f, 0xd8, 0x95, 0x3b, 0x76, 0xa1, 0xec, 0xb0, 0xfd, 0x2a, 0x67, 0xc9, 0x84, 0x53, 0x1e,
    0xeb, 0xa6, 0x71, 0x3c, 0x92, 0xdf, 0x08, 0x45, 0x19, 0x54, 0x83, 0xce, 0x60, 0x2d, 0xfa, 0xb7,
    0x5d, 0x10, 0xc7, 0x8a, 0x24, 0x69, 0xbe, 0xf3, 0xaf, 0xe2, 0x35, 0x78, 0xd6, 0x9b, 0x4c, 0x01,
    0xf4, 0xb9, 0x6e, 0x23, 0x8d, 0xc0, 0x17, 0x5a, 0x06, 0x4b, 0x9c, 0xd1, 0x7f, 0x32, 0xe5, 0xa8
};

uint8_t CalCRC8(uint8_t *p, uint8_t len) {
    uint8_t crc = 0;
    uint16_t i;
    for (i = 0; i < len; i++) {
        crc = CrcTable[(crc ^ *p++) & 0xff];
    }
    return crc;
}

// Custom WiFi transport functions (same as Robot 1)
bool transport_open(struct uxrCustomTransport* transport) {
    WiFiUDP* udp = (WiFiUDP*) transport->args;
    return udp->begin(2020); // Different port for Robot 2
}

bool transport_close(struct uxrCustomTransport* transport) {
    WiFiUDP* udp = (WiFiUDP*) transport->args;
    udp->stop();
    return true;
}

size_t transport_write(struct uxrCustomTransport* transport, uint8_t* buf, size_t len, uint8_t* err) {
    WiFiUDP* udp = (WiFiUDP*) transport->args;
    udp->beginPacket(agent_ip, agent_port);
    size_t sent = udp->write(buf, len);
    udp->endPacket();
    return sent;
}

size_t transport_read(struct uxrCustomTransport* transport, uint8_t* buf, size_t len, int timeout, uint8_t* err) {
    WiFiUDP* udp = (WiFiUDP*) transport->args;
    
    uint32_t start_time = millis();
    while (millis() - start_time < timeout) {
        int packet_size = udp->parsePacket();
        if (packet_size > 0) {
            size_t bytes_read = udp->read(buf, len);
            return bytes_read;
        }
        delay(1);
    }
    return 0;
}

// Callback functions
void cmd_vel_callback(const void * msgin) {
    const geometry_msgs__msg__Twist * msg = (const geometry_msgs__msg__Twist *)msgin;
    
    last_cmd_linear = msg->linear.x;
    last_cmd_angular = msg->angular.z;
    last_cmd_time = millis();
    
    // Convert to M-Bot commands
    float linear = msg->linear.x;
    float angular = msg->angular.z;
    
    // Simple differential drive approximation
    float left_speed = linear - (angular * wheel_base / 2.0);
    float right_speed = linear + (angular * wheel_base / 2.0);
    
    // Convert to PWM values
    int left_pwm = constrain(left_speed * 255 / max_speed, -255, 255);
    int right_pwm = constrain(right_speed * 255 / max_speed, -255, 255);
    
    // Send to M-Bot
    if (abs(left_pwm) < 10 && abs(right_pwm) < 10) {
        MBOT_SERIAL.println("S0");
    } else {
        float avg_speed = (left_pwm + right_pwm) / 2.0;
        MBOT_SERIAL.print("M");
        MBOT_SERIAL.println(avg_speed);
        
        if (abs(angular) > 0.1) {
            float turn_angle = angular * 57.2958; // Convert to degrees
            MBOT_SERIAL.print("T");
            MBOT_SERIAL.println(turn_angle);
        }
    }
}

void timer_callback(rcl_timer_t * timer, int64_t last_call_time) {
    RCLC_UNUSED(last_call_time);
    if (timer != NULL && micro_ros_connected) {
        if (new_scan_ready) {
            publish_scan();
            new_scan_ready = false;
        }
        publish_odometry();
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(STATUS_LED, OUTPUT);
    
    // Initialize hardware
    LIDAR_SERIAL.begin(LIDAR_BAUDRATE, SERIAL_8N1, LIDAR_RX_PIN, LIDAR_TX_PIN);
    MBOT_SERIAL.begin(9600, SERIAL_8N1, MBOT_RX_PIN, MBOT_TX_PIN);
    
    // Initialize data arrays
    for (int i = 0; i < 360; i++) {
        ranges[i] = 12.0;
        intensities[i] = 0.0;
    }
    
    // Connect to WiFi
    connect_wifi();
    
    // Setup micro-ROS
    if (wifi_connected) {
        setup_micro_ros();
    }
    
    Serial.println("Robot 2 initialized");
}

void loop() {
    check_wifi_status();
    read_lidar_data();
    read_mbot_data();
    
    if (micro_ros_connected) {
        rclc_executor_spin_some(&executor, RCL_MS_TO_NS(10));
    }
    
    update_status_led();
    delay(1);
}

void connect_wifi() {
    Serial.print("Robot 2 connecting to WiFi: ");
    Serial.println(ssid);
    
    WiFi.begin(ssid, password);
    WiFi.setHostname("robot2"); // Different hostname
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 30) {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        wifi_connected = true;
        Serial.println();
        Serial.print("Robot 2 WiFi connected! IP: ");
        Serial.println(WiFi.localIP());
    } else {
        wifi_connected = false;
        Serial.println();
        Serial.println("Robot 2 WiFi connection failed!");
    }
}

void check_wifi_status() {
    unsigned long now = millis();
    if (now - last_wifi_check > 10000) { // Check every 10 seconds
        if (WiFi.status() != WL_CONNECTED && wifi_connected) {
            wifi_connected = false;
            micro_ros_connected = false;
            Serial.println("Robot 2 WiFi disconnected! Reconnecting...");
            connect_wifi();
        } else if (WiFi.status() == WL_CONNECTED && !wifi_connected) {
            wifi_connected = true;
            Serial.println("Robot 2 WiFi reconnected!");
            setup_micro_ros();
        }
        last_wifi_check = now;
    }
}

void setup_micro_ros() {
    if (!wifi_connected) return;
    
    // Custom WiFi transport
    static WiFiUDP udp;
    rmw_uros_set_custom_transport(
        false,
        (void *) &udp,
        transport_open,
        transport_close,
        transport_write,
        transport_read
    );
    
    allocator = rcl_get_default_allocator();
    
    rcl_ret_t ret = rclc_support_init(&support, 0, NULL, &allocator);
    if (ret != RCL_RET_OK) return;
    
    ret = rclc_node_init_default(&node, "robot2_node", "", &support); // Robot 2 node name
    if (ret != RCL_RET_OK) return;
    
    // Create publishers - Robot 2 topics
    ret = rclc_publisher_init_default(
        &scan_publisher, &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, LaserScan),
        "/robot2/scan");
    if (ret != RCL_RET_OK) return;
    
    ret = rclc_publisher_init_default(
        &odom_publisher, &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(nav_msgs, msg, Odometry),
        "/robot2/odom");
    if (ret != RCL_RET_OK) return;
    
    // Create subscriber - Robot 2 topic
    ret = rclc_subscription_init_default(
        &cmd_vel_subscriber, &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist),
        "/robot2/cmd_vel");
    if (ret != RCL_RET_OK) return;
    
    // Create timer
    ret = rclc_timer_init_default(&timer, &support, RCL_MS_TO_NS(100), timer_callback);
    if (ret != RCL_RET_OK) return;
    
    // Create executor
    ret = rclc_executor_init(&executor, &support.context, 2, &allocator);
    if (ret != RCL_RET_OK) return;
    
    ret = rclc_executor_add_subscription(&executor, &cmd_vel_subscriber, &cmd_vel_msg, &cmd_vel_callback, ON_NEW_DATA);
    if (ret != RCL_RET_OK) return;
    
    ret = rclc_executor_add_timer(&executor, &timer);
    if (ret != RCL_RET_OK) return;
    
    // Initialize messages
    init_messages();
    
    micro_ros_connected = true;
    Serial.println("Robot 2 micro-ROS initialized");
}

void init_messages() {
    // Scan message - Robot 2 frame
    scan_msg.header.frame_id.data = "robot2/lidar_link";
    scan_msg.header.frame_id.size = strlen("robot2/lidar_link");
    scan_msg.header.frame_id.capacity = scan_msg.header.frame_id.size + 1;
    
    scan_msg.angle_min = 0.0;
    scan_msg.angle_max = 2.0 * M_PI;
    scan_msg.angle_increment = M_PI / 180.0;
    scan_msg.time_increment = 0.0;
    scan_msg.scan_time = 0.1;
    scan_msg.range_min = 0.15;
    scan_msg.range_max = 12.0;
    
    scan_msg.ranges.data = ranges;
    scan_msg.ranges.size = 360;
    scan_msg.ranges.capacity = 360;
    
    scan_msg.intensities.data = intensities;
    scan_msg.intensities.size = 360;
    scan_msg.intensities.capacity = 360;
    
    // Odometry message - Robot 2 frames
    odom_msg.header.frame_id.data = "robot2/odom";
    odom_msg.header.frame_id.size = strlen("robot2/odom");
    odom_msg.header.frame_id.capacity = odom_msg.header.frame_id.size + 1;
    
    odom_msg.child_frame_id.data = "robot2/base_link";
    odom_msg.child_frame_id.size = strlen("robot2/base_link");
    odom_msg.child_frame_id.capacity = odom_msg.child_frame_id.size + 1;
}

// LiDAR processing functions (same as Robot 1)
void read_lidar_data() {
    static uint8_t buffer[47];
    static int buffer_index = 0;
    static bool frame_started = false;
    
    while (LIDAR_SERIAL.available()) {
        uint8_t byte = LIDAR_SERIAL.read();
        
        if (!frame_started && byte == HEADER) {
            frame_started = true;
            buffer[0] = byte;
            buffer_index = 1;
        } else if (frame_started) {
            buffer[buffer_index++] = byte;
            
            if (buffer_index >= 47) {
                process_lidar_frame(buffer);
                frame_started = false;
                buffer_index = 0;
            }
        }
    }
}

void process_lidar_frame(uint8_t* buffer) {
    LiDARFrameTypeDef* frame = (LiDARFrameTypeDef*)buffer;
    
    if (frame->header != HEADER || frame->ver_len != 0x2C) return;
    
    uint8_t calculated_crc = CalCRC8(buffer, 46);
    if (calculated_crc != frame->crc8) return;
    
    float start_angle = frame->start_angle * 0.01 * M_PI / 180.0;
    float end_angle = frame->end_angle * 0.01 * M_PI / 180.0;
    
    if (end_angle < start_angle) end_angle += 2 * M_PI;
    
    float angle_step = (end_angle - start_angle) / (POINT_PER_PACK - 1);
    
    for (int i = 0; i < POINT_PER_PACK; i++) {
        float angle = start_angle + i * angle_step;
        if (angle >= 2 * M_PI) angle -= 2 * M_PI;
        
        int angle_index = (int)(angle * 180.0 / M_PI);
        if (angle_index >= 0 && angle_index < 360) {
            float distance = frame->point[i].distance / 1000.0;
            uint8_t intensity = frame->point[i].intensity;
            
            if (distance >= 0.15 && distance <= 12.0) {
                ranges[angle_index] = distance;
                intensities[angle_index] = intensity;
            }
        }
    }
    
    new_scan_ready = true;
}

void read_mbot_data() {
    if (MBOT_SERIAL.available()) {
        String data = MBOT_SERIAL.readStringUntil('\n');
        data.trim();
        
        if (data.startsWith("SENSOR:")) {
            // Process additional sensor data if needed
            // Format: SENSOR:distance,autonomous,emergency,robot_id
        } else if (data.startsWith("EMERGENCY:")) {
            // Handle emergency stop from M-Bot
            last_cmd_linear = 0.0;
            last_cmd_angular = 0.0;
            Serial.println("Emergency stop received from M-Bot");
        }
    }
}

void publish_scan() {
    if (!micro_ros_connected) return;
    
    int64_t time_us = esp_timer_get_time();
    scan_msg.header.stamp.sec = time_us / 1000000;
    scan_msg.header.stamp.nanosec = (time_us % 1000000) * 1000;
    
    rcl_ret_t ret = rcl_publish(&scan_publisher, &scan_msg, NULL);
    if (ret != RCL_RET_OK) {
        micro_ros_connected = false;
        Serial.println("Failed to publish scan, reconnecting...");
        setup_micro_ros();
    }
}

void publish_odometry() {
    static unsigned long last_odom_publish = 0;
    unsigned long current_time = millis();
    
    if (current_time - last_odom_publish > 50) { // 20Hz
        float dt = (current_time - last_odom_time) / 1000.0;
        
        if (dt > 0 && last_odom_time > 0) {
            // Simple dead reckoning
            float linear_vel = last_cmd_linear;
            float angular_vel = last_cmd_angular;
            
            // Apply timeout
            if (current_time - last_cmd_time > 500) {
                linear_vel = 0.0;
                angular_vel = 0.0;
            }
            
            // Update pose
            robot_x += linear_vel * cos(robot_theta) * dt;
            robot_y += linear_vel * sin(robot_theta) * dt;
            robot_theta += angular_vel * dt;
            
            // Normalize theta
            while (robot_theta > M_PI) robot_theta -= 2 * M_PI;
            while (robot_theta < -M_PI) robot_theta += 2 * M_PI;
        }
        
        // Populate message
        int64_t time_us = esp_timer_get_time();
        odom_msg.header.stamp.sec = time_us / 1000000;
        odom_msg.header.stamp.nanosec = (time_us % 1000000) * 1000;
        
        odom_msg.pose.pose.position.x = robot_x;
        odom_msg.pose.pose.position.y = robot_y;
        odom_msg.pose.pose.position.z = 0.0;
        
        odom_msg.pose.pose.orientation.x = 0.0;
        odom_msg.pose.pose.orientation.y = 0.0;
        odom_msg.pose.pose.orientation.z = sin(robot_theta / 2.0);
        odom_msg.pose.pose.orientation.w = cos(robot_theta / 2.0);
        
        odom_msg.twist.twist.linear.x = last_cmd_linear;
        odom_msg.twist.twist.linear.y = 0.0;
        odom_msg.twist.twist.linear.z = 0.0;
        odom_msg.twist.twist.angular.x = 0.0;
        odom_msg.twist.twist.angular.y = 0.0;
        odom_msg.twist.twist.angular.z = last_cmd_angular;
        
        rcl_ret_t ret = rcl_publish(&odom_publisher, &odom_msg, NULL);
        if (ret != RCL_RET_OK) {
            micro_ros_connected = false;
        }
        
        last_odom_time = current_time;
        last_odom_publish = current_time;
    }
}

void update_status_led() {
    unsigned long now = millis();
    if (now - last_status_blink > 500) {
        status_led_state = !status_led_state;
        
        if (micro_ros_connected) {
            digitalWrite(STATUS_LED, HIGH); // Solid on when fully connected
        } else if (wifi_connected) {
            digitalWrite(STATUS_LED, status_led_state); // Slow blink when WiFi only
        } else {
            digitalWrite(STATUS_LED, (now % 200) < 100); // Fast blink when disconnected
        }
        
        last_status_blink = now;
    }
}

// Error handling macro
#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){Serial.printf("Failed status on line %d: %d. Aborting.\n",__LINE__,(int)temp_rc); return;}}
```