   
  Project Name: Vaccine Carrier Cold Box Temperature Monitoring
  
  Author: Markel Robregado          

  Hackster project: https://www.hackster.io/mtrobregado/aws-iot-vaccine-carrier-cold-box-9c7fba
  
  Date Created: 8/5/2021
  
  Project Description:
  - AWS IOT EduKit, collect sensor data via UART from a Texas Instruments Sub 1-Ghz sensor network, 
    and send these data to AWS IOT. Sub 1-Ghz sensor network consist of collector and sensor nodes. 
    Each sensor node is attached to a vaccine carrier cold box.
  
  Hardware:
  - AWS IOT EduKit
  - CC1352R Launchpad (collector)
  - LPSTK-CC1352R (sensor node connected to vaccine carrier cold box)  
  
  Programming Guide
  - Install SimpleLink™ CC13xx and CC26xx software development kit (SDK) version 5.10.
  - Import CCS Project to TI Code Composer Studio v10.3 workspace.
  - Rebuild All. BIN file generated can be found at \Release folder
  - Program bin file using TI SmartRF FLash Programmer v1.8.0.
  - Red led will blink upon power on.
  - With the collector running and blinking red led. Press the LPSTK-CC1352R left button
    to provision credentials from collector. Green led will blink at led if succesfful provision.
  - Manual provisioning, connect using Bluetooth and using IOS LightBlue App, write 0xDD then 0xAA
    to Provision Sensor characteristics.  
	
  Smart RF Flash Programmer 2 Settings:
  - Erase pages in range
  - Program entire source file.		
