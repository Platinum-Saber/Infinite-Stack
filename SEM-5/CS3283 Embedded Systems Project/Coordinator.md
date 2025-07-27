
## Why Use Raspberry Pi 4 as Wi-Fi AP?

✅ No need for an external router  
✅ Full control over IP addressing and network behavior  
✅ Reliable for **UDP streaming** from ESP32s (scouts) to Pi (coordinator)  
✅ Works outdoors or in disaster zones with no infrastructure

---

## How to Set Up Pi 4 as a Wi-Fi Access Point + UDP Server

###  Step 1: Install Required Packages

Run this on your Raspberry Pi 4:

```bash
sudo apt update
sudo apt install hostapd dnsmasq netfilter-persistent
```

### Step 2: Disable Services Temporarily

```bash
sudo systemctl stop hostapd
sudo systemctl stop dnsmasq
```

---

### Step 3: Configure a Static IP

Edit this file:

```bash
sudo nano /etc/dhcpcd.conf
```

Add at the bottom:

```conf
interface wlan0
    static ip_address=192.168.4.1/24
    nohook wpa_supplicant
```

Then:

```bash
sudo service dhcpcd restart
```

---

### Step 4: Set Up DHCP + DNS (dnsmasq)

Backup and create new config:

```bash
sudo mv /etc/dnsmasq.conf /etc/dnsmasq.conf.orig
sudo nano /etc/dnsmasq.conf
```

Paste:

```conf
interface=wlan0
dhcp-range=192.168.4.2,192.168.4.100,255.255.255.0,24h
```

---

### Step 5: Configure the Access Point (hostapd)

Create config:

```bash
sudo nano /etc/hostapd/hostapd.conf
```

Paste:

```conf
interface=wlan0
driver=nl80211
ssid=ScoutNet
hw_mode=g
channel=7
wmm_enabled=0
auth_algs=1
ignore_broadcast_ssid=0
wpa=2
wpa_passphrase=terrainmap123
wpa_key_mgmt=WPA-PSK
rsn_pairwise=CCMP
```

Tell system where config is:

```bash
sudo nano /etc/default/hostapd
```

Set:

```conf
DAEMON_CONF="/etc/hostapd/hostapd.conf"
```

---

### Step 6: Enable and Start Services

```bash
sudo systemctl unmask hostapd
sudo systemctl enable hostapd
sudo systemctl enable dnsmasq
sudo systemctl reboot
```

After reboot, your Pi 4 will create a **Wi-Fi hotspot named `ScoutNet`** with password `terrainmap123`.

Your ESP32 bots can now connect to it and send UDP packets to:

```bash
IP: 192.168.4.1
PORT: 5005 (or anything you set)
```

---


##  Updated: Use Raspberry Pi 4 as a Wi-Fi Access Point (Ubuntu MATE 22.04)

### ✅ **1. Install Required Packages**

```bash
sudo apt update
sudo apt install hostapd dnsmasq netfilter-persistent
```

---

### 🔧 **2. Configure a Static IP for `wlan0` using NetworkManager**

Ubuntu MATE uses **NetworkManager**, so skip Netplan or dhcpcd.

#### Use `nmcli` (NetworkManager CLI):

```bash
sudo nmcli connection add type wifi ifname wlan0 con-name hotspot autoconnect yes ssid ScoutNet
sudo nmcli connection modify hotspot 802-11-wireless.mode ap 802-11-wireless.band bg ipv4.method shared
sudo nmcli connection modify hotspot wifi-sec.key-mgmt wpa-psk
sudo nmcli connection modify hotspot wifi-sec.psk "terrainmap123"
sudo nmcli connection up hotspot
```

This creates a Wi-Fi access point with:

- **SSID**: `ScoutNet`
- **Password**: `terrainmap123`
- **IP**: `10.42.0.1` (default with shared mode)

✅ At this point your Pi is broadcasting `ScoutNet`, and any ESP32 should be able to connect.


#### ✅ To **Start** the Hotspot:

```bash
nmcli connection up hotspot
```

This activates the Wi-Fi Access Point named **ScoutNet**.

---

#### ✅ To **Stop** the Hotspot:

```bash
nmcli connection down hotspot
```

This turns off the access point and releases the `wlan0` interface.

---

#### ✅ To **Check Status**:

```bash
nmcli device status
```

Look for `wlan0` in **connected (hotspot)** state:

```
DEVICE  TYPE      STATE         CONNECTION
wlan0   wifi      connected     hotspot
```

---

#### 🔁 Restart the Hotspot

If you need to refresh the hotspot (e.g., after reboot or config change):

```bash
nmcli connection down hotspot
nmcli connection up hotspot
```

---


## Static IP
### Default Static IP (when using `nmcli ipv4.method shared`)

```bash
10.42.0.1
```

This is:

- The Pi's **gateway IP** for connected ESP32 M-Bots
- Where your M-Bots should send their **UDP packets**

---

### To Verify It:

Run this command on your Pi:

```bash
ip addr show wlan0
```

Look for:

```text
inet 10.42.0.1/24
```

---
