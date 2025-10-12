### Windows with WSL2 and Docker. The `usbipd-win` approach is the correct method for Windows. Here's how to set it up for your Docker container:

## Step 1: Install `usbipd-win` on Windows host

#### Run this in Windows PowerShell (as Administrator):

```powershell
winget install usbipd
```

## Step 2: List and identify your USB device

In Windows PowerShell:

```powershell
usbipd list
```

Look for your USB device (it might show as "Silicon Labs CP210x" or similar). Note the BUSID (e.g., 1-2, 2-1, etc.).

## Step 3: Bind the device

Replace `<busid>` with your actual device's BUSID:

```powershell
usbipd bind --busid <busid>
```

## Step 4: Attach to WSL

```powershell
usbipd attach --wsl --busid <busid>
```

### Results of Steps 1-4

> [!info]- What to expect
> 
> ```powershell
> PS C:\Users\sansi> winget install usbipd
> Found an existing package already installed. Trying to upgrade the installed package...
> No available upgrade found.
> No newer package versions are available from the configured sources.
> PS C:\Users\sansi> usbipd list
> Connected:
> BUSID  VID:PID    DEVICE                                                        STATE
> 2-1    10c4:ea60  Silicon Labs CP210x USB to UART Bridge (COM2)                 Shared
> 2-6    5986:211b  HD Webcam                                                     Not shared
> 2-10   8087:0026  Intel(R) Wireless Bluetooth(R)                                Not shared
> 2-15   21c4:b083  USB Attached SCSI (UAS) Mass Storage Device                   Not shared
> 
> Persisted:
> GUID                                  DEVICE
> 
> PS C:\Users\sansi> usbipd bind --busid 2-1
> usbipd: info: Device with busid '2-1' was already shared.
> PS C:\Users\sansi> usbipd attach --wsl --busid 2-1
> usbipd: info: Using WSL distribution 'Ubuntu' to attach; the device will be available in all WSL 2 distributions.
> usbipd: info: Loading vhci_hcd module.
> usbipd: info: Detected networking mode 'nat'.
> usbipd: info: Using IP address 172.30.128.1 to reach the host.
> ```
> 

## Step 5: Update the `devcontainer.json` to mount USB devices

Update your [`.devcontainer/devcontainer.json`]devcontainer.json ) to ensure the container can access the USB devices:

````json
{
    "name": "humble desktop",
    "dockerFile": "Dockerfile",

    "runArgs": [
        "--privileged", //can also use "-v", "/dev:/dev" instead 
        //.....
    ],

// existing code

}
````

## Step 6: Verify the device in the container

After rebuilding your dev container, check if the device is accessible:

```bash
# List USB devices
ls -la /dev/ttyUSB* /dev/ttyACM*

# Check device permissions
ls -la /dev/ttyUSB0

# Test the device (should show device info)
sudo dmesg | grep -i usb
```

## Step 7: Set proper permissions (if needed)

If the device exists but has permission issues, add your user to the `dialout group` and set permissions:

```bash
sudo usermod -a -G dialout ubuntu
sudo chmod 666 /dev/ttyUSB0
```

