# WLAN TCP keepalive offload

This code example demonstrates the TCP keepalive offload functionality offered by Cypress Wi-Fi devices using PSoC&trade; 6 MCU. It employs the [low power assistant](https://github.com/Infineon/lpa) (LPA) middleware library, which helps in developing low-power applications for Cypress devices.

The TCP keepalive offload functionality allows the WLAN device to handle TCP keepalive packets from the network on its own so that the PSoC&trade; 6 MCU can remain longer in the low-power mode.

[View this README on GitHub.](https://github.com/Infineon/mtb-example-anycloud-offload-tcp-keepalive)

[Provide feedback on this code example.](https://cypress.co1.qualtrics.com/jfe/form/SV_1NTns53sK2yiljn?Q_EED=eyJVbmlxdWUgRG9jIElkIjoiQ0UyMjk5MjYiLCJTcGVjIE51bWJlciI6IjAwMi0yOTkyNiIsIkRvYyBUaXRsZSI6IldMQU4gVENQIGtlZXBhbGl2ZSBvZmZsb2FkIiwicmlkIjoic2RhayIsIkRvYyB2ZXJzaW9uIjoiMy4wLjAiLCJEb2MgTGFuZ3VhZ2UiOiJFbmdsaXNoIiwiRG9jIERpdmlzaW9uIjoiTUNEIiwiRG9jIEJVIjoiSUNXIiwiRG9jIEZhbWlseSI6IlBTT0MifQ==)

## Requirements

- [ModusToolbox&trade; software](https://www.cypress.com/products/modustoolbox-software-environment) v2.4
- Board support package (BSP) minimum required version: 3.0.0
- Programming language: C
- Associated parts: All [PSoC&trade; 6 MCU](https://www.cypress.com/PSoC6) parts



## Supported toolchains (make variable 'TOOLCHAIN')

- GNU Arm® embedded compiler v10.3.1 (`GCC_ARM`) - Default value of `TOOLCHAIN`
- Arm&reg; compiler v6.13 (`ARM`)
- IAR C/C++ compiler v8.42.2 (`IAR`)

## Supported kits (make variable 'TARGET')

- [PSoC&trade; 6 Wi-Fi Bluetooth® prototyping kit](https://www.cypress.com/CY8CPROTO-062-4343W) (`CY8CPROTO-062-4343W`) – Default value of `TARGET`
- [PSoC&trade; 6 Wi-Fi Bluetooth&reg; pioneer kit](https://www.cypress.com/CY8CKIT-062-WiFi-BT) (`CY8CKIT-062-WIFI-BT`)
- [PSoC&trade; 62S2 Wi-Fi Bluetooth&reg; pioneer kit](https://www.cypress.com/CY8CKIT-062S2-43012) (`CY8CKIT-062S2-43012`)
- [PSoC&trade; 62S1 Wi-Fi Bluetooth&reg; pioneer kit](https://www.cypress.com/CYW9P62S1-43438EVB-01) (`CYW9P62S1-43438EVB-01`)
- [PSoC&trade; 62S1 Wi-Fi Bluetooth&reg; pioneer kit](https://www.cypress.com/CYW9P62S1-43012EVB-01) (`CYW9P62S1-43012EVB-01`)
- [PSoC&trade; 62S3 Wi-Fi Bluetooth&reg; prototyping kit](https://www.cypress.com/CY8CPROTO-062S3-4343W) (`CY8CPROTO-062S3-4343W`)
- [PSoC&trade; 62S2 evaluation kit](https://www.cypress.com/CY8CEVAL-062S2) (`CY8CEVAL-062S2-LAI-4373M2`, `CY8CEVAL-062S2-MUR-43439M2`)
- Rapid IoT Connect developer kit (`CYSBSYSKIT-DEV-01`)

## Hardware setup

This example uses the board's default configuration. See the kit user guide to ensure that the board is configured correctly.

**Note:** The PSoC&trade; 6 Bluetooth&reg; LE pioneer kit (CY8CKIT-062-BLE) and the PSoC&trade; 6 Wi-Fi Bluetooth&reg; pioneer kit (CY8CKIT-062-WIFI-BT) ship with KitProg2 installed. The ModusToolbox&trade; software requires KitProg3. Before using this code example, make sure that the board is upgraded to KitProg3. The tool and instructions are available in the [Firmware Loader](https://github.com/Infineon/Firmware-loader) GitHub repository. If you do not upgrade, you will see an error like "unable to find CMSIS-DAP device" or "KitProg firmware is out of date".


## Software setup

Install a terminal emulator if you don't have one. Instructions in this document use [Tera Term](https://ttssh2.osdn.jp/index.html.en).

Install a Python interpreter if you do not have one. This code example is tested with [Python 3.7.7](https://www.python.org/downloads/release/python-377/).

Download [TCPDUMP](https://www.microolap.com/products/network/tcpdump/download/) and extract the .zip file. This utility is needed to capture the TCP keepalive packets in Windows. This tool is natively available in macOS and Ubuntu.

## Using the code example

Create the project and open it using one of the following:

<details><summary><b>In Eclipse IDE for ModusToolbox&trade; software</b></summary>

1. Click the **New Application** link in the **Quick Panel** (or, use **File** > **New** > **ModusToolbox Application**). This launches the [Project Creator](https://www.cypress.com/ModusToolboxProjectCreator) tool.

2. Pick a kit supported by the code example from the list shown in the **Project Creator - Choose Board Support Package (BSP)** dialog.

   When you select a supported kit, the example is reconfigured automatically to work with the kit. To work with a different supported kit later, use the [Library Manager](https://www.cypress.com/ModusToolboxLibraryManager) to choose the BSP for the supported kit. You can use the Library Manager to select or update the BSP and firmware libraries used in this application. To access the Library Manager, click the link from the **Quick Panel**.

   You can also just start the application creation process again and select a different kit.

   If you want to use the application for a kit not listed here, you may need to update the source files. If the kit does not have the required resources, the application may not work.

3. In the **Project Creator - Select Application** dialog, choose the example by enabling the checkbox.

4. (Optional) Change the suggested **New Application Name**.

5. The **Application(s) Root Path** defaults to the Eclipse workspace which is usually the desired location for the application. If you want to store the application in a different location, you can change the *Application(s) Root Path* value. Applications that share libraries should be in the same root path.

6. Click **Create** to complete the application creation process.

For more details, see the [Eclipse IDE for ModusToolbox&trade; software user guide](https://www.cypress.com/MTBEclipseIDEUserGuide) (locally available at *{ModusToolbox&trade; software install directory}/ide_{version}/docs/mt_ide_user_guide.pdf*).

</details>

<details><summary><b>In command-line interface (CLI)</b></summary>

ModusToolbox&trade; software provides the Project Creator as both a GUI tool and the command line tool, "project-creator-cli". The CLI tool can be used to create applications from a CLI terminal or from within batch files or shell scripts. This tool is available in the *{ModusToolbox&trade; software install directory}/tools_{version}/project-creator/* directory.

Use a CLI terminal to invoke the "project-creator-cli" tool. On Windows, use the command line "modus-shell" program provided in the ModusToolbox&trade; software installation instead of a standard Windows command-line application. This shell provides access to all ModusToolbox&trade; software tools. You can access it by typing `modus-shell` in the search box in the Windows menu. In Linux and macOS, you can use any terminal application.

This tool has the following arguments:

Argument | Description | Required/optional
---------|-------------|-----------
`--board-id` | Defined in the `<id>` field of the [BSP](https://github.com/Infineon?q=bsp-manifest&type=&language=&sort=) manifest | Required
`--app-id`   | Defined in the `<id>` field of the [CE](https://github.com/Infineon?q=ce-manifest&type=&language=&sort=) manifest | Required
`--target-dir`| Specify the directory in which the application is to be created if you prefer not to use the default current working directory | Optional
`--user-app-name`| Specify the name of the application if you prefer to have a name other than the example's default name | Optional

<br>

The following example will clone the "[Hello World](https://github.com/Infineon/mtb-example-psoc6-hello-world)" application with the desired name "MyHelloWorld" configured for the *CY8CKIT-062-WIFI-BT* BSP into the specified working directory, *C:/mtb_projects*:

   ```
   project-creator-cli --board-id CY8CKIT-062-WIFI-BT --app-id mtb-example-psoc6-hello-world --user-app-name MyHelloWorld --target-dir "C:/mtb_projects"
   ```

**Note:** The project-creator-cli tool uses the `git clone` and `make getlibs` commands to fetch the repository and import the required libraries. For details, see the "Project creator tools" section of the [ModusToolbox&trade; software user guide](https://www.cypress.com/ModusToolboxUserGuide) (locally available at *{ModusToolbox&trade; software install directory}/docs_{version}/mtb_user_guide.pdf*).

</details>

<details><summary><b>In third-party IDEs</b></summary>

Use one of the following options:

- **Use the standalone [Project Creator](https://www.cypress.com/ModusToolboxProjectCreator) tool:**

   1. Launch Project Creator from the Windows Start menu or from *{ModusToolbox&trade; software install directory}/tools_{version}/project-creator/project-creator.exe*.

   2. In the initial **Choose Board Support Package** screen, select the BSP, and click **Next**.

   3. In the **Select Application** screen, select the appropriate IDE from the **Target IDE** drop-down menu.

   4. Click **Create** and follow the instructions printed in the bottom pane to import or open the exported project in the respective IDE.

<br>

- **Use command-line interface (CLI):**

   1. Follow the instructions from the **In command-line interface (CLI)** section to create the application, and then import the libraries using the `make getlibs` command.

   2. Export the application to a supported IDE using the `make <ide>` command.

   3. Follow the instructions displayed in the terminal to create or import the application as an IDE project.

For a list of supported IDEs and more details, see the "Exporting to IDEs" section of the [ModusToolbox&trade; software user guide](https://www.cypress.com/ModusToolboxUserGuide) (locally available at *{ModusToolbox&trade; software install directory}/docs_{version}/mtb_user_guide.pdf*).

</details>


## Operation


If using a PSoC&trade; 64 "Secure" MCU kit (like CY8CKIT-064B0S2-4343W), the PSoC&trade; 64 device must be provisioned with keys and policies before being programmed. Follow the instructions in the ["Secure Boot" SDK user guide](https://www.cypress.com/documentation/software-and-drivers/psoc-64-secure-mcu-secure-boot-sdk-user-guide) to provision the device. If the kit is already provisioned, copy-paste the keys and policy folder to the application folder.

1. Connect the board to your PC using the provided USB cable through the KitProg3 USB connector.

2. Open *app_config.h* and modify the `WIFI_SSID`, `WIFI_PASSWORD`, and `WIFI_SECURITY_TYPE` macros to match the Wi-Fi network credentials that you want to connect to.

   All possible security types are defined in the `cy_wcm_security_t` structure in *cy_wcm.h* file.

3. Ensure that your computer is connected to the same Wi-Fi access point (AP) that you configured in Step 2.

   The TCP keepalive settings are already done for this example in the device configurator except for the IP address of the server (your PC). See [Configure TCP keepalive using device configurator](#configure-tcp-keepalive-using-device-configurator) to learn how to configure the IP address of the server.

4. Open a terminal program and select the KitProg3 COM port. Set the serial port parameters to 8N1 and 115200 baud.

5. Open a command shell and run the Python TCP echo server (*tcp_server.py*) from the project directory. The Python script starts a TCP server and the server starts listening for incoming TCP connections.

   **Note:** The default port number is defined as `50007` in the *tcp_server.py* script. Specify a custom port number between 1 and 65535 that you would like to use.

   ```
   python tcp_server.py --port 3360
   ```
   where `3360` is the port number of the server (destination port number), which was already configured in the device configurator.

   **Note:** Ensure that the firewall settings of your computer allow access to the Python software so that it can communicate with the TCP client. See this [community thread](https://community.cypress.com/thread/53662).

6. Program the board using one of the following:

   <details><summary><b>Using Eclipse IDE for ModusToolbox&trade; software</b></summary>

      1. Select the application project in the Project Explorer.

      2. In the **Quick Panel**, scroll down, and click **\<Application Name> Program (KitProg3_MiniProg4)**.
   </details>

   <details><summary><b>Using CLI</b></summary>

     From the terminal, execute the `make program` command to build and program the application using the default toolchain to the default target. The default toolchain and target are specified in the application's Makefile but you can override those values manually:
      ```
      make program TARGET=<BSP> TOOLCHAIN=<toolchain>
      ```

      Example:
      ```
      make program TARGET=CY8CPROTO-062-4343W TOOLCHAIN=GCC_ARM
      ```
   </details>

7. After programming, the application starts automatically. Verify that the following logs appear on the serial terminal:

    ```
    Info: =====================================
    Info: CE229926 - WLAN TCP Keepalive Offload
    Info: =====================================

    WLAN MAC Address : A0:C9:A0:3D:D3:6A
    WLAN Firmware    : wl0: Jan 30 2020 21:41:53 version 7.45.98.95 (r724303 CY) FWID 01-5afc8c1e
    WLAN CLM         : API: 12.2 Data: 9.10.39 Compiler: 1.29.4 ClmImport: 1.36.3 Creation: 2020-01-30 21:30:05
    WHD VERSION      : v1.92.0 : v1.92.0 : GCC 9.3 : 2020-09-25 03:12:36 -0500
    Info: Wi-Fi initialization is successful
    Info: Join to AP: WIFI_SSID
    Info: Successfully joined wifi network WIFI_SSID
    Info: Assigned IP address: 192.168.43.131
    Info: Taking TCP Keepalive configuration from the Generated sources.
    Info: Socket[0]: Created connection to IP 192.168.43.218, local port 3353, remote port 3360
    Info: Skipped TCP socket connection for socket id[1]. Check the TCP Keepalive configuration.
    Info: Skipped TCP socket connection for socket id[2]. Check the TCP Keepalive configuration.
    Info: Skipped TCP socket connection for socket id[3]. Check the TCP Keepalive configuration.
    whd_tko_toggle: Successfully enabled

    Network Stack Suspended, MCU will enter DeepSleep power mode
    ```
8. Use the TCPDUMP utility to capture the over-the-air TCP keepalive packets between the client (target kit) and the server (PC). See the [Software setup](#software-setup) to download this tool for Windows. On Ubuntu and macOS, this utility is natively available.

   **Ubuntu OS:**
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
   **Note:** TCP keepalive packets can be identified by the packet length and TCP flags. The capture logs show that the length of the packet is zero; in addition, the TCP flag `[.]` indicates that it is an ACK packet. This verifies that the TCP keepalive packets are sent and the corresponding ACKs are received from the target kit. This verifies the TCP keepalive offload functionality.

   **Windows:**

   1. Open the command prompt with administrator privileges and go to the location, where TCPDUMP was installed.

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

      Command to filter TCP keepalive packets:

      ```
      C:\>tcpdump -i 5 -n "tcp[tcpflags] == tcp-syn or tcp[tcpflags] == tcp-ack" and port 3360
      ```
      The packet capture logs will look similar to those shown for Ubuntu OS.

   **macOS:**

   Find the Wi-Fi interface for packet capture and then use the tcpdump utility to capture the packets. The TCPDUMP utility is a built-in packet trace tool available in macOS. The following command lists all the interfaces and the interface number is identified on the `Device:` row (for example, *en0*) in the command output.

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

   Command to filter TCP keepalive packets:

   ```
   $ sudo tcpdump -i en1 -n "tcp[tcpflags] == tcp-syn or tcp[tcpflags] == tcp-ack" and port 3360
   ```
   The packet capture logs will look similar to those shown for Ubuntu OS.

You can also use the Wireshark sniffer tool for capturing TCP keepalive packets on Windows, Ubuntu, and macOS.

**Figure 1. TCP keepalive capture on Wireshark**

![](images/wireshark_tko.png)

PSoC&trade; 6 MCU will wake up only when required by the WLAN device in the following conditions:

- WLAN receives any TCP data from the server. For example, a ping (ICMP request packet) from a peer device wakes the PSoC&trade; 6 MCU device.

- WLAN receives a link down event (station disconnects from the AP)

It is recommended to test this application in a less congested network to avoid possible host wakeups by the network peers.

## Debugging

You can debug the example to step through the code. In the IDE, use the **\<Application Name> Debug (KitProg3_MiniProg4)** configuration in the **Quick Panel**. For details, see the "Program and debug" section in the [Eclipse IDE for ModusToolbox&trade; software user guide](https://www.cypress.com/MTBEclipseIDEUserGuide).

**Note:** **(Only while debugging)** On the CM4 CPU, some code in `main()` may execute before the debugger halts at the beginning of `main()`. This means that some code executes twice – once before the debugger stops execution, and again after the debugger resets the program counter to the beginning of `main()`. See [KBA231071](https://community.cypress.com/docs/DOC-21143) to learn about this and for the workaround.


## Design and implementation

### Resources and settings

[Low power assistant](https://github.com/Infineon/lpa) (LPA) provides an easy way to develop low-power applications for [supported devices](#supported-kits). LPA supports the following features:

- MCU low power

- Wi-Fi and Bluetooth&reg; low power

- Wi-Fi address resolution protocol (ARP) offload

- Wi-Fi packet filter offload

- Wi-Fi TCP keepalive offload

This document focuses on Wi-Fi TCP keepalive offload. This feature offloads the TCP keepalive functionality to the WLAN device, allowing the host MCU to enter sleep and deep sleep states, thus reducing the overall system power consumption.

The WLAN firmware takes care of sending and receiving TCP keepalive packets with the TCP server (a different machine or a PC running TCP server that listens for an incoming TCP connection).

### TCP keepalive

A TCP keepalive packet is a message sent by one device to another to check whether the link between the two is operational or to prevent the link from being disconnected. When two devices are connected over a network via TCP/IP, TCP keepalive packets can be used to determine whether the connection is still valid, and terminate if needed.

If a connection has been terminated because of a TCP keepalive timeout, and the other device eventually sends a packet for the old connection, the device that terminated the connection will send a packet with the RST flag set to signal the other device that the old connection is no longer active. This will force the other device to terminate its end of the connection, so a new connection can be established.

Therefore, TCP keepalive packets can be used in checking for dead peers or for preventing disconnection because of network inactivity.

### TCP keepalive offload

Typically, TCP keepalive packets are sent every 45 or 60 seconds on an idle TCP connection; the connection is dropped after three sequential ACKs are missed. This means that the host MCU must wake up periodically to send TCP keepalive packets to maintain the TCP connection during the idle state.

The TCP keepalive offloads part of the LPA helps you improve the power consumption of your connected system by reducing the time the host needs to stay awake to support TCP keepalive requests. This is achieved by offloading the TCP keepalive functionality to the WLAN device so that the host MCU can be dedicated to your application.

This section describes how to enable TCP keepalive offload and configure four different sockets for TCP connections.

**Figure 2** shows that the host wakes up for incoming TCP traffic when offload is not enabled. On the other hand, the host can save more power by entering and staying in deep sleep for a longer time when the TCP keepalive activity is offloaded to the WLAN device.

**Figure 2. TCP keepalive offload disabled vs. enabled**

![](images/tko_enabled_vs_disabled.png)


**Note:** The TCP keepalive activity is offloaded only when the host MCU goes to sleep and the network stack is suspended.

The application does the following when the kit is powered up:

1. Initializes the WLAN device as an STA (Station) interface.

2. Initializes the offload manager (OLM) with the configuration present in the *GeneratedSources/cycfg_connectivity_wifi.c/.h* files inside *COMPONENT_CUSTOM_DESIGN_MODUS/TARGET_\<kit>*, where the source code for the feature is generated by the device configurator tool in the IDE. The offload manager will be initialized based on the *GeneratedSources* configuration.

3. Connects the kit to the AP with the Wi-Fi credentials set in the `WIFI_SSID` and `WIFI_PASSWORD` macros in the *app_config.h* file. The AP could be a mobile hotspot or a third-party AP.

4. Establishes a TCP socket connection with the configured TCP server. Note that the TCP server details are configured with the device configurator.

### Configure TCP keepalive using device configurator

Use the device configurator tool to configure TCP keepalive and the host MCU WAKE pin.

A default *design.modus* file is packaged for each [supported kit](#supported-kits-make-variable-target). This does not enable any low-power feature such as ARP offload, packet filter, or TCP keepalive offload. However, this can be a good reference to start the configuration from scratch as needed by the application.

For this TCP keepalive offload application demonstration, a pre-configured *design.modus* file that overrides the default kit configuration is provided for each supported kit. These files are located in the project folder under *COMPONENT_CUSTOM_DESIGN_MODUS/TARGET_\<kit>*.

**Note:** This section provides instructions only for the targets CY8CPROTO-062-4343W and CY8CKIT-062S2-43012. For other targets, you can follow the same instructions to create custom configuration. See the *../mtb_shared/TARGET_\<kit>/latest-v2.X/COMPONENT_BSP_DESIGN_MODUS/GeneratedSource/cycfg_pins.h* file for pin details such as CYBSP_WIFI_HOST_WAKE.

The Makefile specifies that the application should use the custom configuration instead of the default configuration by adding `"CUSTOM_DESIGN_MODUS"` to the `COMPONENTS` variable and adding `"BSP_DESIGN_MODUS"` to the `DISABLE_COMPONENTS` variable. This custom configuration has the necessary settings enabled for the feature to work except for the IP address of the server (your PC).

Do the following to configure TCP keepalive in the *design.modus* file using the device configurator tool:

**Note:** These steps are already handled in this application except for the IP address of the server (your PC). They are provided only for informational purposes.

1. Open Device Configurator from the **Quick Panel** when using Eclipse IDE for ModusToolbox&trade;, or through the `make config` command from the root directory of the code example repository.

2. On the PSoC&trade; 6 MCU **Pins** tab of the Device Configurator tool, do the following:

   **CY8CKIT-062S2-43012:**

   1. Enable the host WAKE pin **P4[1]** and name it *CYBSP_WIFI_HOST_WAKE*.

   2. In the **Parameters** pane, change the following:

      - **Drive Mode**: Analog High-Z. Input buffer off

      - **Initial Drive State**: High(1)

      - **Interrupt Trigger Type**: Rising Edge

      ![](images/configurator_pins_tab_43012.png)

<br>

   **CY8CPROTO-062-4343W:**

   1. Enable the host WAKE pin **P0[4]**, and name it as *CYBSP_WIFI_HOST_WAKE*.

   2. In the **Parameters** pane, change the following:

       - **Drive Mode**: Analog High-Z. Input buffer off

       - **Initial Drive State**: High(1)

       - **Interrupt Trigger Type**: Rising Edge

       ![](images/configurator_pins_tab.png)

       

   **Note:** The Wi-Fi host driver takes care of the drive mode configuration of the host WAKE pin.

3. Go to the tab for the connectivity device and configure the fields as follows. This configuration is applicable to all [supported kits](#supported-kits). **Figure 5** shows the TCP keepalive offload configuration for CY8CKIT-062S2-43012.

     1. Click on the connectivity device at the top, expand the **Power** option from the list, and then click **Wi-Fi**.

        **Figure 3. Navigate to the Wi-Fi device section**

        ![](images/tcpka_configuration.png)

     2. Enable Host Wake Configuration and set **Host Device Interrupt Pin** to **CYBSP_WIFI_HOST_WAKE**.

        **Figure 4. Host WAKE pin**

        ![](images/host_wake_pin.png)

     3. Enable TCP keepalive offload.

     4. Configure the interval, retry interval, and retry count as required by the application. All values are in seconds.

     5. Enter the connection information as needed. You can add up to four TCP socket connections. Specify the following for each TCP socket connection:

        - **Source Port**: Port number of the client (the target kit).

        - **Destination Port**: Port number of the server (the PC running TCP server). Select the port number as between 1 and 65535.

        - **Destination IP Address**: IP address of the server (the PC running TCP server). Get the IP address of the PC once it gets connected to the Wi-Fi network.

        **Figure 5. Wi-Fi configuration**

        ![](images/configurator_wifi_tab.png)

4. Select **File** > **Save**.

   The generated source files *cycfg_connectivity_wifi.c* and *cycfg_connectivity_wifi.h* will be in the *GeneratedSource* folder, which is present in the same location from where you opened the *design.modus* file.

## Related resources

Resources  | Links
-----------|----------------------------------
Application notes  | [AN228571](https://www.cypress.com/AN228571) – Getting started with PSoC&trade; 6 MCU on ModusToolbox&trade; software <br>  [AN215656](https://www.cypress.com/AN215656) – PSoC&trade; 6 MCU: Dual-CPU system design 
Code examples  | [Using ModusToolbox&trade; software](https://github.com/Infineon/Code-Examples-for-ModusToolbox-Software) on GitHub 
Device documentation | [PSoC&trade; 6 MCU datasheets](https://www.cypress.com/search/all?f[0]=meta_type%3Atechnical_documents&f[1]=resource_meta_type%3A575&f[2]=field_related_products%3A114026) <br> [PSoC&trade; 6 technical reference manuals](https://www.cypress.com/search/all/PSoC%206%20Technical%20Reference%20Manual?f[0]=meta_type%3Atechnical_documents&f[1]=resource_meta_type%3A583)
Development kits | Visit www.cypress.com/microcontrollers-mcus-kits and use the options in the **Select your kit** section to filter kits by *Product family* or *Features*.
Libraries on GitHub  | [mtb-pdl-cat1](https://github.com/infineon/mtb-pdl-cat1) – PSoC&trade; 6 peripheral driver library (PDL)  <br> [mtb-hal-cat1](https://github.com/infineon/mtb-hal-cat1) – Hardware abstraction layer (HAL) library <br> [retarget-io](https://github.com/infineon/retarget-io) – Utility library to retarget STDIO messages to a UART port 
Middleware on GitHub  | [lpa](https://github.com/Infineon/lpa) - Low power assistant (LPA) <br> [wifi-connection-manager](https://github.com/Infineon/wifi-connection-manager) - Wi-Fi connection manager (WCM) <br> [wifi-mw-core](https://github.com/Infineon/wifi-mw-core) - Wi-Fi middleware core Library <br> [psoc6-middleware](https://github.com/Infineon/modustoolbox-software#psoc-6-middleware-libraries) – Links to all PSoC&trade; 6 MCU middleware
Tools  | [Eclipse IDE for ModusToolbox&trade; software](https://www.cypress.com/modustoolbox) – ModusToolbox&trade; software is a collection of easy-to-use software and tools enabling rapid development with Infineon MCUs, covering applications from embedded sense and control to wireless and cloud-connected systems using AIROC&trade; Wi-Fi and Bluetooth® connectivity devices. 

<br>

## Other resources


Cypress provides a wealth of data at www.cypress.com to help you select the right device, and quickly and effectively integrate it into your design.

For PSoC&trade; 6 MCU devices, see [How to design with PSoC&trade; 6 MCU - KBA223067](https://community.cypress.com/docs/DOC-14644) in the Cypress community.


## Document history

Document title: *CE229926* - *WLAN TCP keepalive offload*

 Version | Description of change
 ------- | ---------------------
 1.0.0   | New code example
 1.1.0   | Fixed IAR compiler warning and minor changes to the Makefile
 2.0.0   | Major update to support ModusToolbox&trade; software v2.2 and LPA v3.0.0.<br/>This version is not backward compatible with ModusToolbox&trade; software v2.1
 2.1.0   | Added support for Rapid IoT Connect developer kit (CYSBSYSKIT-DEV-01)
 2.2.0   | Updated to FreeRTOS v10.3.1
 2.3.0   | Updated to FreeRTOS v10.4.3 <br> Added support for new kits |
 3.0.0   | Updated to support ModusToolbox™ software v2.4 <br> Added support for new kits <br> Updated the BSPs to v3.X

<br>

---------------------------------------------------------

© Cypress Semiconductor Corporation, 2020-2021. This document is the property of Cypress Semiconductor Corporation, an Infineon Technologies company, and its affiliates ("Cypress").  This document, including any software or firmware included or referenced in this document ("Software"), is owned by Cypress under the intellectual property laws and treaties of the United States and other countries worldwide.  Cypress reserves all rights under such laws and treaties and does not, except as specifically stated in this paragraph, grant any license under its patents, copyrights, trademarks, or other intellectual property rights.  If the Software is not accompanied by a license agreement and you do not otherwise have a written agreement with Cypress governing the use of the Software, then Cypress hereby grants you a personal, non-exclusive, nontransferable license (without the right to sublicense) (1) under its copyright rights in the Software (a) for Software provided in source code form, to modify and reproduce the Software solely for use with Cypress hardware products, only internally within your organization, and (b) to distribute the Software in binary code form externally to end users (either directly or indirectly through resellers and distributors), solely for use on Cypress hardware product units, and (2) under those claims of Cypress’s patents that are infringed by the Software (as provided by Cypress, unmodified) to make, use, distribute, and import the Software solely for use with Cypress hardware products.  Any other use, reproduction, modification, translation, or compilation of the Software is prohibited.
<br>
TO THE EXTENT PERMITTED BY APPLICABLE LAW, CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH REGARD TO THIS DOCUMENT OR ANY SOFTWARE OR ACCOMPANYING HARDWARE, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  No computing device can be absolutely secure.  Therefore, despite security measures implemented in Cypress hardware or software products, Cypress shall have no liability arising out of any security breach, such as unauthorized access to or use of a Cypress product. CYPRESS DOES NOT REPRESENT, WARRANT, OR GUARANTEE THAT CYPRESS PRODUCTS, OR SYSTEMS CREATED USING CYPRESS PRODUCTS, WILL BE FREE FROM CORRUPTION, ATTACK, VIRUSES, INTERFERENCE, HACKING, DATA LOSS OR THEFT, OR OTHER SECURITY INTRUSION (collectively, "Security Breach").  Cypress disclaims any liability relating to any Security Breach, and you shall and hereby do release Cypress from any claim, damage, or other liability arising from any Security Breach.  In addition, the products described in these materials may contain design defects or errors known as errata which may cause the product to deviate from published specifications. To the extent permitted by applicable law, Cypress reserves the right to make changes to this document without further notice. Cypress does not assume any liability arising out of the application or use of any product or circuit described in this document. Any information provided in this document, including any sample design information or programming code, is provided only for reference purposes.  It is the responsibility of the user of this document to properly design, program, and test the functionality and safety of any application made of this information and any resulting product.  "High-Risk Device" means any device or system whose failure could cause personal injury, death, or property damage.  Examples of High-Risk Devices are weapons, nuclear installations, surgical implants, and other medical devices.  "Critical Component" means any component of a High-Risk Device whose failure to perform can be reasonably expected to cause, directly or indirectly, the failure of the High-Risk Device, or to affect its safety or effectiveness.  Cypress is not liable, in whole or in part, and you shall and hereby do release Cypress from any claim, damage, or other liability arising from any use of a Cypress product as a Critical Component in a High-Risk Device. You shall indemnify and hold Cypress, including its affiliates, and its directors, officers, employees, agents, distributors, and assigns harmless from and against all claims, costs, damages, and expenses, arising out of any claim, including claims for product liability, personal injury or death, or property damage arising from any use of a Cypress product as a Critical Component in a High-Risk Device. Cypress products are not intended or authorized for use as a Critical Component in any High-Risk Device except to the limited extent that (i) Cypress’s published data sheet for the product explicitly states Cypress has qualified the product for use in a specific High-Risk Device, or (ii) Cypress has given you advance written authorization to use the product as a Critical Component in the specific High-Risk Device and you have signed a separate indemnification agreement.
<br>
Cypress, the Cypress logo, and combinations thereof, WICED, ModusToolbox, PSoC, CapSense, EZ-USB, F-RAM, and Traveo are trademarks or registered trademarks of Cypress or a subsidiary of Cypress in the United States or in other countries. For a more complete list of Cypress trademarks, visit cypress.com. Other names and brands may be claimed as property of their respective owners.
