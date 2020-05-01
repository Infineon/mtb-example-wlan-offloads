# AnyCloud Example: WLAN TCP Keepalive Offload

This code example demonstrates the TCP keepalive Offload functionality offered by Cypress Wi-Fi devices using PSoC® 6 MCU. It employs the [Low Power Assistant](https://github.com/cypresssemiconductorco/lpa) (LPA) middleware library, which helps in developing low-power applications for Cypress devices.

The TCP keepalive offload functionality allows the WLAN device to handle the TCP keepalive packets from the network on its own so that the PSoC 6 MCU can remain in a low-power mode longer.

## Requirements

- [ModusToolbox™ software](https://www.cypress.com/products/modustoolbox-software-environment) v2.1
- Programming Language: C
- Associated Parts: All [PSoC 6 MCU](http://www.cypress.com/PSoC6) parts

## Supported Kits

- [PSoC 6 Wi-Fi BT Prototyping Kit](https://www.cypress.com/CY8CPROTO-062-4343W) (CY8CPROTO-062-4343W) - Default target
- [PSoC 62S2 Wi-Fi BT Pioneer Kit](https://www.cypress.com/CY8CKIT-062S2-43012) (CY8CKIT-062S2-43012)

## Hardware Setup

This example uses the board's default configuration. See the kit user guide to ensure that the board is configured correctly.

**Note**: The PSoC 6 BLE Pioneer Kit (CY8CKIT-062-BLE) and the PSoC 6 WiFi-BT Pioneer Kit (CY8CKIT-062-WIFI-BT) ship with KitProg2 installed. ModusToolbox software requires KitProg3. Before using this code example, make sure that the board is upgraded to KitProg3. The tool and instructions are available in the [Firmware Loader](https://github.com/cypresssemiconductorco/Firmware-loader) GitHub repository. If you do not upgrade, you will see an error like "unable to find CMSIS-DAP device" or "KitProg firmware is out of date".

## Software Setup

- Install a terminal emulator if you don't have one. Instructions in this document use [Tera Term](https://ttssh2.osdn.jp/index.html.en).
- Install a Python Interpreter if you don't have one. This code example is tested with [Python 3.7.7](https://www.python.org/downloads/release/python-377/).
- Download [TCPDUMP](https://www.microolap.com/products/network/tcpdump/download/) and extract the .zip file. This utility is needed to capture the TCP keepalive packets in Windows. This tool is natively available in macOS and Ubuntu.

## Using the Code Example

### In Eclipse IDE for ModusToolbox:

1. Click the **New Application** link in the Quick Panel (or, use **File** > **New** > **ModusToolbox Application**).

2. Pick a kit supported by the code example from the list shown in the **Project Creator - Choose Board Support Package (BSP)** dialog.

   When you select a supported kit, the example is reconfigured automatically to work with the kit. To work with a different supported kit later, use the **Library Manager** to choose the BSP for the supported kit. You can use the Library Manager to select or update the BSP and firmware libraries used in this application. To access the Library Manager, right-click the application name from the Project Workspace window in the IDE, and select **ModusToolbox** > **Library Manager**. You can also access it from the **Quick Panel**.

   You can also just start the application creation process again and select a different kit.

   If you want to use the application for a kit not listed here, you may need to update the source files. If the kit does not have the required resources, the application may not work.

3. In the **Project Creator - Select Application** dialog, choose the example.

4. Optionally, update the **Application Name** and **Location** fields with the application name and local path where the application is created.

5. Click **Create** to complete the application creation process.

For more details, see the Eclipse IDE for ModusToolbox User Guide: *{ModusToolbox install directory}/ide_{version}/docs/mt_ide_user_guide.pdf*.

### In Command-line Interface (CLI):

1. Download and unzip this repository onto your local machine, or clone the repository.

2. Open a CLI terminal and navigate to the application folder. 
   
   On Linux and macOS, you can use any terminal application. On Windows, navigate to the modus-shell directory (*{ModusToolbox install directory}/tools_\<version>/modus-shell*) and run *Cygwin.bat*.

3. Import the required libraries by executing the `make getlibs` command.

### In Third-party IDEs:

1. Follow the instructions from the CLI section to download or clone the repository, and import the libraries using the `make getlibs` command.

2. Export the application to a supported IDE using the `make <ide>` command.

3. Follow the instructions displayed in the terminal to create or import the application as an IDE project.

For more details, see the "Exporting to IDEs" section of the ModusToolbox User Guide: *{ModusToolbox install directory}/ide_{version}/docs/mtb_user_guide.pdf*.

## Operation

1. Connect the board to your PC using the provided USB cable through the KitProg3 USB connector.

2. Open *app_config.h* and modify the `WIFI_SSID`, `WIFI_PASSWORD`, and `WIFI_SECURITY_TYPE` macros to match the Wi-Fi network credentials that you want to connect to.

   All possible security types are defined in the `cy_wcm_security_t` structure in *cy_wcm.h* file.

3. Ensure that your computer is connected to the same Wi-Fi access point that you configured in Step 2.

   The TCP keepalive settings are already done for this example in the Device Configurator except for the IP address of the server (your PC). See [Configure TCP Keepalive Using Device Configurator](#configure-tcp-keepalive-using-device-configurator) to learn how to configure the IP address of the server.

4. Open a terminal program and select the KitProg3 COM port. Set the serial port parameters to 8N1 and 115200 baud.

5. Open a command shell and run the Python TCP echo server (*tcp_server.py*) from the project directory. The Python script starts a TCP server and the server starts listening for incoming TCP connections.

   **Note:** The default port number is defined as `50007` in the *tcp_server.py* script. Specify a custom port number between 1 and 65535 that you would like to use.

   ```
   python tcp_server.py --port 3360
   ```
   where `3360` is the port number of the server (destination port number), which was already configured in the Device Configurator.

   **Note:** Ensure that the firewall settings of your computer allow access to the Python software so that it can communicate with the TCP client. See this [community thread](https://community.cypress.com/thread/53662).

6. Program the board.

   - **Using Eclipse IDE for ModusToolbox**:

     1. Select the application project in Project Explorer.

     2. In the **Quick Panel**, scroll down, and click **\<Application Name> Program (KitProg3)**.

   - **Using CLI**:

     From the terminal, execute the `make program` command to build and program the application using the default toolchain to the default target. You can specify a target and toolchain manually:
        ```
        make program TARGET=<BSP> TOOLCHAIN=<toolchain>
        ```
        Example:

        ```
        make program TARGET=CY8CPROTO-062-4343W TOOLCHAIN=GCC_ARM
        ```
        **Note**:  Before building the application, ensure that the *deps* folder contains the BSP file (*TARGET_xxx.lib*) corresponding to the TARGET. Execute the `make getlibs` command to fetch the BSP contents before building the application.

7. After programming, the application starts automatically. Verify that the following logs appear on the serial terminal:

    ```
    Info: ============================================
    Info: AnyCloud Example: WLAN TCP Keepalive Offload
    Info: ============================================
 
    WLAN MAC Address : 44:91:60:9A:35:5A
    WLAN Firmware    : wl0: Jan 27 2020 21:57:29 version 13.10.271.236 (5a526db) FWID 01-61e2b002
    WLAN CLM         : API: 18.2 Data: 9.10.0 Compiler: 1.36.1 ClmImport: 1.34.1 Creation: 2020-01-27 21:54:33
    WHD VERSION      : v1.90.2 : v1.90.2 : GCC 7.2 : 2020-04-13 02:49:57 -0500
    Info: Wi-Fi initialization is successful
    Info: Join to AP: <WIFI_SSID>
    Info: Successfully joined wifi network <WIFI_SSID>
    Info: Assigned IP address: <IP_ADDRESS>
    Info: Taking TCP Keepalive configuration from the Generated sources.
    TCP remote IP Address 6900a8c0  remote port:3360
    TCP Connection Established Successfully ctx:8010fd8
    Info: Socket[0]: Created connection to IP 192.168.0.105, local port 3353, remote port 3360
    Info: Skipped TCP socket connection for socket id[1]. Check the TCP Keepalive configuration.
    Info: Skipped TCP socket connection for socket id[2]. Check the TCP Keepalive configuration.
    Info: Skipped TCP socket connection for socket id[3]. Check the TCP Keepalive configuration.
    whd_tko_toggle: Successfully enabled
 
    Network Stack Suspended, MCU will enter DeepSleep power mode
    ```
8. Use the tcpdump utility to capture the over-the-air TCP keepalive packets between the client (target kit) and the server (the PC). See [Software Setup](#software-setup) to download this tool for Windows. On Ubuntu and macOS, this utility is natively available.

   - **Ubuntu OS:**
     ```
     $ sudo tcpdump -n "tcp[tcpflags] == tcp-syn or tcp[tcpflags] == tcp-ack" and port 3360
      tcpdump: verbose output suppressed, use -v or -vv for full protocol decode
      listening on wlp3s0, link-type EN10MB (Ethernet), capture size 262144 bytes
      15:18:34.457203 IP 192.168.43.131.3353 > 192.168.43.38.3360: Flags [.], ack 2994052043, win 9205, length 0
      15:18:34.457274 IP 192.168.43.38.3360 > 192.168.43.131.3353: Flags [.], ack 1, win 29200, length 0
      15:18:39.500001 IP 192.168.43.131.3353 > 192.168.43.38.3360: Flags [.], ack 1, win 9205, length 0
      15:18:39.500066 IP 192.168.43.38.3360 > 192.168.43.131.3353: Flags [.], ack 1, win 29200, length 0
      15:18:44.545006 IP 192.168.43.131.3353 > 192.168.43.38.3360: Flags [.], ack 1, win 9205, length 0
      15:18:44.545082 IP 192.168.43.38.3360 > 192.168.43.131.3353: Flags [.], ack 1, win 29200, length 0
      15:18:49.586017 IP 192.168.43.131.3353 > 192.168.43.38.3360: Flags [.], ack 1, win 9205, length 0
      15:18:49.586078 IP 192.168.43.38.3360 > 192.168.43.131.3353: Flags [.], ack 1, win 29200, length 0
      15:18:54.630125 IP 192.168.43.131.3353 > 192.168.43.38.3360: Flags [.], ack 1, win 9205, length 0
      15:18:54.630191 IP 192.168.43.38.3360 > 192.168.43.131.3353: Flags [.], ack 1, win 29200, length 0
      15:18:59.673084 IP 192.168.43.131.3353 > 192.168.43.38.3360: Flags [.], ack 1, win 9205, length 0
      15:18:59.673150 IP 192.168.43.38.3360 > 192.168.43.131.3353: Flags [.], ack 1, win 29200, length 0
      15:19:04.715285 IP 192.168.43.131.3353 > 192.168.43.38.3360: Flags [.], ack 1, win 9205, length 0
     ```
     **Note:** TCP keepalive packets can be identified by the packet length and TCP flags. The capture logs show that the length of the packet is zero; In addition, the TCP flag `[.]` indicates that it is an ACK packet. This verifies that the TCP keepalive packets are sent and the corresponding ACKs are received from the target kit. This verifies the TCP keepalive Offload functionality.

   - **Windows:**

      1. Open the command prompt with administrator privileges and go to the location where tcpdump was installed.
      
      2. Find the Wi-Fi interface number on which over-the-air packets will be captured using the following command. The Wi-Fi interface number is the sequence number that is at the beginning of each line.
      
         ```
         C:\>tcpdump -D
         1.\Device\{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx} (Microsoft Wi-Fi Direct Virtual Adapter)
         2.\Device\{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx} (Microsoft Wi-Fi Direct Virtual Adapter)
         3.\Device\{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx} (WAN Miniport (Network Monitor))
         4.\Device\{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx} (PANGP Virtual Ethernet Adapter)
         5.\Device\{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx} (Intel(R) Dual Band Wireless-AC 8260)
         6.\Device\{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx} (Intel(R) Ethernet Connection I219-LM)
         ```

         Command syntax:

         ```
         C:\>tcpdump -i <Wi-Fi interface number> -n <expression>
         ```

         Command to filter TCP Keepalive packets:

         ```
         C:\>tcpdump -i 5 -n "tcp[tcpflags] == tcp-syn or tcp[tcpflags] == tcp-ack" and port 3360
         ```
         The packet capture logs will look similar to those shown for Ubuntu OS.

   - **MacOS:**

      Find the Wi-Fi interface for packet capture and then use the tcpdump utility to capture the packets. The tcpdump utility is a built-in packet trace tool available in MacOS. The following command lists all the interfaces and the interface number is identified on `Device:` row (eg. en0) in the command output.

      ```
      $ networksetup -listallhardwareports

      Hardware Port: Ethernet
      Device: en0
      Ethernet Address: xx:xx:xx:xx:xx:xx

      Hardware Port: Wi-Fi
      Device: en1
      Ethernet Address: xx:xx:xx:xx:xx:xx
      ```

      Command syntax:

      ```
      $ sudo tcpdump -i <Wi-Fi interface number> -n <expression>
      ```

      Command to filter TCP Keepalive packets:

      ```
      $ sudo tcpdump -i en1 -n "tcp[tcpflags] == tcp-syn or tcp[tcpflags] == tcp-ack" and port 3360
      ```
      The packet capture logs will look similar to those shown for Ubuntu OS.

You can also use the Wireshark sniffer tool for capturing TCP keepalive packets on Windows, Ubuntu, and MacOS.

**Figure 1. TCP Keepalive Capture on Wireshark**
![](images/wireshark_tko.png)

PSoC 6 MCU will wake up only when required by the WLAN device in the following conditions:
   - WLAN receives any TCP data from the server. For example, a ping (ICMP request packet) from a peer device wakes the PSoC 6 MCU device.
   - WLAN receives a link down event (station disconnects from the access point (AP))

It is recommended to test this application in a less congested network to avoid possible host wakeups by the network peers.

## Debugging

You can debug the example to step through the code. In the IDE, use the **\<Application Name> Debug (KitProg3)** configuration in the **Quick Panel**. For more details, see the "Program and Debug" section in the Eclipse IDE for ModusToolbox User Guide: *{ModusToolbox install directory}/ide_{version}/docs/mt_ide_user_guide.pdf*.

## Design and Implementation

Cypress [Low Power Assistant](https://github.com/cypresssemiconductorco/lpa) (LPA) provides an easy way to develop low-power applications for [Cypress devices](#supported-kits). LPA supports the following features:
- MCU Low Power
- Wi-Fi and Bluetooth Low Power
- Wi-Fi Address Resolution Protocol (ARP) Offload
- Wi-Fi Packet Filter Offload
- Wi-Fi TCP keepalive Offload

This document focuses on Wi-Fi TCP keepalive Offload. This feature offloads the TCP keepalive functionality to the WLAN device, allowing the host MCU to enter sleep and deep sleep states, thus reducing the overall system power consumption.

The WLAN firmware takes care of sending and receiving TCP keepalive packets with the TCP server (a different machine or a PC running TCP server that listens for incoming TCP connection).

### TCP Keepalive
A TCP keepalive packet is a message sent by one device to another to check whether the link between the two is operational or to prevent the link from being disconnected. When two devices are connected over a network via TCP/IP, TCP keepalive packets can be used to determine whether the connection is still valid, and terminate if needed.

If a connection has been terminated due to a TCP keepalive timeout, and the other device eventually sends a packet for the old connection, the device that terminated the connection will send a packet with the RST flag set to signal the other device that the old connection is no longer active.  This will force the other device to terminate its end of the connection, so a new connection can be established.

Therefore, TCP keepalive packets can be used in checking for dead peers or for preventing disconnection due to network inactivity.

### TCP Keepalive Offload

Typically, TCP keepalive packets are sent every 45 or 60 seconds on an idle TCP connection; the connection is dropped after three sequential ACKs are missed. This means that the host MCU must wake up periodically to send TCP keepalive packets to maintain the TCP connection during the idle state.

The TCP keepalive offload part of the LPA helps you improve the power consumption of your connected system by reducing the time the host needs to stay awake to support TCP keepalive requests. This is achieved by offloading the TCP keepalive functionality to the WLAN device so that the host MCU can be dedicated for your application.

This section describes how to enable TCP keepalive offload and configure four different sockets for TCP connections.

Figure 2 shows that the host wakes up for incoming TCP traffic when offload is not enabled. On the other hand, the host can save more power by entering and staying in deep sleep for a longer time when the TCP keepalive activity is offloaded to the WLAN device.

**Figure 2. TCP Keepalive Offload Disabled vs. Enabled**
![](images/tko_enabled_vs_disabled.png)


**Note:** The TCP keepalive activity is offloaded only when the host MCU goes to sleep and the network stack is suspended.

The application does the following when the kit is powered up:

1. Initializes the WLAN device as a STA (Station) interface.

2. Initializes the Offload Manager (OLM) with the configuration present in the *GeneratedSources/cycfg_connectivity_wifi.c/.h* files inside *COMPONENT_CUSTOM_DESIGN_MODUS/TARGET_\<kit>*, where the source code for the feature is generated by the Device Configurator tool in the IDE. The Offload Manager will be initialized based on the *GeneratedSources* configuration.

3. Connects the kit to the AP with the Wi-Fi credentials set in the `WIFI_SSID` and `WIFI_PASSWORD` macros in the *app_config.h* file. The AP could be a mobile hotspot or a third-party AP.

4. Establishes a TCP socket connection with the configured TCP server. Note that the TCP server details are configured with the Device Configurator.

### Configure TCP Keepalive Using Device Configurator

Use the Device Configurator tool to configure TCP keepalive and the host MCU WAKE pin.

Cypress packages a default *design.modus* file for each [supported kit](#supported-kits). This does not enable any low-power feature such as ARP offload, packet filter, or TCP keepalive offload. However, this can be a good reference to start the configuration from scratch as needed by the application.

For this TCP keepalive Offload application demonstration, a pre-configured *design.modus* file that overrides the default kit configuration is provided for each supported kit. These files are located in the project folder under *COMPONENT_CUSTOM_DESIGN_MODUS/TARGET_\<kit>*.

The Makefile specifies that the application should use the custom configuration instead of the default configuration by adding `"CUSTOM_DESIGN_MODUS"` to the `COMPONENTS` variable and adding `"BSP_DESIGN_MODUS"` to the `DISABLE_COMPONENTS` variable. This custom configuration has the necessary settings enabled for the feature to work except for the IP address of the server (your PC). 

Do the following to configure TCP keepalive in the *design.modus* file using the Device Configurator tool:

**Note:** These steps are already handled in this application except for the IP address of the server (your PC). They are provided only for informational purpose.

1. Open Device Configurator from the **Quick Panel** when using Eclipse IDE for ModusToolbox, or through the `make config` command from the root directory of the code example repository.

2. On the PSoC 6 MCU **Pins** tab of the Device Configurator tool, do the following:

    - **CY8CKIT-062S2-43012**

        1. Enable the host WAKE pin **P4[1]** and name it *CYBSP_WIFI_HOST_WAKE*.

        2. In the **Parameters** pane, change the following:

            - **Drive Mode**: Analog High-Z. Input buffer off

            - **Initial Drive State**: High(1)

            - **Interrupt Trigger Type**: Rising Edge

        ![](images/configurator_pins_tab_43012.png)

    - **CY8CPROTO-062-4343W**

        1. Enable the host WAKE pin **P0[4]**, and name it as *CYBSP_WIFI_HOST_WAKE*.

        2. In the **Parameters** pane, change the following:

            - **Drive Mode**: Analog High-Z. Input buffer off

            - **Initial Drive State**: High(1)

            - **Interrupt Trigger Type**: Rising Edge

        ![](images/configurator_pins_tab.png)

   **Note:** The Wi-Fi host driver takes care of the drive mode configuration of the host WAKE pin.

3. Go to the tab for the connectivity device and configure the fields as follows. This configuration is applicable to all [supported kits](#supported-kits). Figure 5 shows the TCP keepalive Offload configuration for CY8CKIT-062S2-43012.
   
     1. Click on the connectivity device at the top, expand the **Power** option from the list, and then click **Wi-Fi**.

        **Figure 3. Navigate to Wi-Fi Device Section**
        ![](images/tcpka_configuration.png)

     1. Enable Host Wake Configuration and set **Host Device Interrupt Pin** to **CYBSP_WIFI_HOST_WAKE**.

        **Figure 4. Host Wake Pin**
        ![](images/host_wake_pin.png)

     2. Enable TCP keepalive Offload.

     3. Configure the Interval, Retry Interval, and Retry Count as required by the application. All values are in seconds.

     4. Enter the connection information as needed. You can add up to four TCP socket connections. Specify the following for each TCP socket connection:

        - **Source Port**: Port number of the client (the target kit).

        - **Destination Port**: Port number of the server (the PC running TCP server). Select the port number as between 1 and 65535.

        - **Destination IP Address**: IP address of the server (the PC running TCP server). Get the IP address of the PC once it gets connected to the Wi-Fi network.

        **Figure 5. Wi-Fi Configuration**
        ![](images/configurator_wifi_tab.png)

4. Select **File** > **Save**. 

   The generated source files *cycfg_connectivity_wifi.c* and *cycfg_connectivity_wifi.h* will be in the *GeneratedSource* folder, which is present in the same location from where you opened the *design.modus* file.

## Related Resources

| Application Notes                                            |                                                              |
| :----------------------------------------------------------- | :----------------------------------------------------------- |
| [AN228571](https://www.cypress.com/AN228571) – Getting Started with PSoC 6 MCU on ModusToolbox | Describes PSoC 6 MCU devices and how to build your first application with ModusToolbox |
| [AN227910](http://www.cypress.com/AN227910) – Low-Power System Design with PSoC 6 MCU and CYW43012 | Describes how to implement a low-power system design.        |
| **Code Examples**                                            |                                                              |
| [Using ModusToolbox](https://github.com/cypresssemiconductorco/Code-Examples-for-ModusToolbox-Software) | [Using PSoC Creator](https://www.cypress.com/documentation/code-examples/psoc-6-mcu-code-examples) |
| **Device Documentation**                                     |                                                              |
| [PSoC 6 MCU Datasheets](https://www.cypress.com/search/all?f[0]=meta_type%3Atechnical_documents&f[1]=resource_meta_type%3A575&f[2]=field_related_products%3A114026) | [PSoC 6 Technical Reference Manuals](https://www.cypress.com/search/all/PSoC%206%20Technical%20Reference%20Manual?f[0]=meta_type%3Atechnical_documents&f[1]=resource_meta_type%3A583) |
| **Development Kits**                                         | Buy at www.cypress.com                                       |
| [CY8CKIT-062S2-43012](https://www.cypress.com/CY8CKIT-062S2-43012) PSoC 62S2 Wi-Fi BT Pioneer Kit | [CY8CPROTO-062S3-4343W](https://www.cypress.com/CY8CPROTO-062S3-4343W) PSoC 62S3 Wi-Fi BT Prototyping Kit |                                                             |
| **Libraries**                                                |                                                              |
| PSoC 6 Peripheral Driver Library and docs                    | [psoc6pdl](https://github.com/cypresssemiconductorco/psoc6pdl) on GitHub |
| Cypress Hardware Abstraction Layer Library and docs          | [psoc6hal](https://github.com/cypresssemiconductorco/psoc6hal) on GitHub |
| RetargetIO - A utility library to retarget the standard input/output (STDIO) messages to a UART port | [retarget-io](https://github.com/cypresssemiconductorco/retarget-io) on GitHub |
| **Middleware**                                               | Middleware libraries are distributed on GitHub               |
| Low Power Assistant (LPA)                    | [lpa](https://github.com/cypresssemiconductorco/lpa) on GitHub |
| Wi-Fi Connection Manager (WCM)                                    | [wifi-connection-manager](https://github.com/cypresssemiconductorco/wifi-connection-manager) on GitHub |
| Wi-Fi Middleware core | [wifi-mw-core](https://github.com/cypresssemiconductorco/wifi-mw-core) on GitHub |
| Connectivity-Utilities                                    | [connectivity-utilities](https://github.com/cypresssemiconductorco/connectivity-utilities) on GitHub |
| Links to all PSoC 6 MCU Middleware                               | [psoc6-middleware](https://github.com/cypresssemiconductorco/psoc6-middleware) on GitHub |
| **Tools**                                                    |                                                              |
| [Eclipse IDE for ModusToolbox](https://www.cypress.com/modustoolbox)     | The multi-platform, Eclipse-based Integrated Development Environment (IDE) that supports application configuration and development for PSoC 6 MCU and IoT designers.             |
| [PSoC Creator](https://www.cypress.com/products/psoc-creator-integrated-design-environment-ide) | The Cypress IDE for PSoC and FM0+ MCU development.            |

## Other Resources

Cypress provides a wealth of data at www.cypress.com to help you select the right device, and quickly and effectively integrate it into your design.

For PSoC 6 MCU devices, see [How to Design with PSoC 6 MCU - KBA223067](https://community.cypress.com/docs/DOC-14644) in the Cypress community.

## Document History

Document Title: CE229926 - AnyCloud Example: WLAN TCP Keepalive Offload

| Version |                 Description of Change              |
| -------- | -------------------------------------------------- |
|  1.0.0   |   New code example  |

------

All other trademarks or registered trademarks referenced herein are the property of their respective owners.

![Banner](images/footer_banner.png)

-------------------------------------------------------------------------------

© Cypress Semiconductor Corporation, 2020. This document is the property of Cypress Semiconductor Corporation and its subsidiaries ("Cypress"). This document, including any software or firmware included or referenced in this document ("Software"), is owned by Cypress under the intellectual property laws and treaties of the United States and other countries worldwide. Cypress reserves all rights under such laws and treaties and does not, except as specifically stated in this paragraph, grant any license under its patents, copyrights, trademarks, or other intellectual property rights. If the Software is not accompanied by a license agreement and you do not otherwise have a written agreement with Cypress governing the use of the Software, then Cypress hereby grants you a personal, non-exclusive, nontransferable license (without the right to sublicense) (1) under its copyright rights in the Software (a) for Software provided in source code form, to modify and reproduce the Software solely for use with Cypress hardware products, only internally within your organization, and (b) to distribute the Software in binary code form externally to end users (either directly or indirectly through resellers and distributors), solely for use on Cypress hardware product units, and (2) under those claims of Cypress's patents that are infringed by the Software (as provided by Cypress, unmodified) to make, use, distribute, and import the Software solely for use with Cypress hardware products. Any other use, reproduction, modification, translation, or compilation of the Software is prohibited.
TO THE EXTENT PERMITTED BY APPLICABLE LAW, CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH REGARD TO THIS DOCUMENT OR ANY SOFTWARE OR ACCOMPANYING HARDWARE, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. No computing device can be absolutely secure. Therefore, despite security measures implemented in Cypress hardware or software products, Cypress shall have no liability arising out of any security breach, such as unauthorized access to or use of a Cypress product. CYPRESS DOES NOT REPRESENT, WARRANT, OR GUARANTEE THAT CYPRESS PRODUCTS, OR SYSTEMS CREATED USING CYPRESS PRODUCTS, WILL BE FREE FROM CORRUPTION, ATTACK, VIRUSES, INTERFERENCE, HACKING, DATA LOSS OR THEFT, OR OTHER SECURITY INTRUSION (collectively, "Security Breach"). Cypress disclaims any liability relating to any Security Breach, and you shall and hereby do release Cypress from any claim, damage, or other liability arising from any Security Breach. In addition, the products described in these materials may contain design defects or errors known as errata which may cause the product to deviate from published specifications. To the extent permitted by applicable law, Cypress reserves the right to make changes to this document without further notice. Cypress does not assume any liability arising out of the application or use of any product or circuit described in this document. Any information provided in this document, including any sample design information or programming code, is provided only for reference purposes. It is the responsibility of the user of this document to properly design, program, and test the functionality and safety of any application made of this information and any resulting product. "High-Risk Device" means any device or system whose failure could cause personal injury, death, or property damage. Examples of High-Risk Devices are weapons, nuclear installations, surgical implants, and other medical devices. "Critical Component" means any component of a High-Risk Device whose failure to perform can be reasonably expected to cause, directly or indirectly, the failure of the High-Risk Device, or to affect its safety or effectiveness. Cypress is not liable, in whole or in part, and you shall and hereby do release Cypress from any claim, damage, or other liability arising from any use of a Cypress product as a Critical Component in a High-Risk Device. You shall indemnify and hold Cypress, its directors, officers, employees, agents, affiliates, distributors, and assigns harmless from and against all claims, costs, damages, and expenses, arising out of any claim, including claims for product liability, personal injury or death, or property damage arising from any use of a Cypress product as a Critical Component in a High-Risk Device. Cypress products are not intended or authorized for use as a Critical Component in any High-Risk Device except to the limited extent that (i) Cypress's published data sheet for the product explicitly states Cypress has qualified the product for use in a specific High-Risk Device, or (ii) Cypress has given you advance written authorization to use the product as a Critical Component in the specific High-Risk Device and you have signed a separate indemnification agreement.
Cypress, the Cypress logo, Spansion, the Spansion logo, and combinations thereof, WICED, PSoC, CapSense, EZ-USB, F-RAM, and Traveo are trademarks or registered trademarks of Cypress in the United States and other countries. For a more complete list of Cypress trademarks, visit cypress.com. Other names and brands may be claimed as property of their respective owners.