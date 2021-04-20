# Traffic Sim 
Tutorial to deploy the Traffic Sim application on the Beagle Bone Black.

Video Demo: https://youtu.be/4DSaTW_wFcU

## What you will need:
* SD card with 4 GB or more.
* BeagleBone Black board
* LCD Display cape
![Materials](https://github.com/jcsp2407/TrafficSim/blob/main/IMG_0640.jpg)
## Step 1: Setup your Ubuntu VM in VirtualBox.
In your VirtualBox Ubuntu VM make sure to go to Settings >> Ports >> USB. Enable the USB 3.0 Controller.

Start your VM.

Connect your microSD card to your host via a card reader, then enable it in your VM by going to the menu bar of VirtualBox and go to Devices >> USB and choose your microSD card.

## Step 2: Flash the SD card with the latest Debian image that support graphics on the BBB:
Download the latest image that support graphics for the BBB (Make sure the name of the image starts with bone-debian).
```bash
wget https://debian.beagleboard.org/images/bone-debian-9.9-lxqt-armhf-2019-08-03-4gb.img.xz
```
Unzip the image downloaded.
```bash
xz -d bone-debian-9.9-lxqt-armhf-2019-08-03-4gb.img.xz
```
Unmount the connected SD card.
```bash
sudo umount /dev/sdc
```
Write the image to the SD card.
```bash
sudo dd if=./bone-debian-9.9-lxqt-armhf-2019-08-03-4gb.img of=/dev/sdc
```

## Step 3: Boot BBB from SD card and prepare the root file system.
Eject the SD card from your host machine and connect it to the BBB using the SD card reader. Connect the BeagleBone to your VM using the USB cable. 
On your Ubuntu VM enable the BBB by going to Devices >> USB >> BeagleBoard.
Open a secure shell session with the BBB.
```bash
ssh 192.168.7.2 -l debian
```
When prompted enter the default password which is: temppwd

Navigate to the following directory.
```bash
cd /opt/scripts/tools/
```
Connect the Ethernet cable to your BBB and run the following command.
```bash
git pull || true
```
Expand the partition on your micro SD card to the full remaining available space of the SD card.
```bash
sudo ./grow_partition.sh
sudo reboot
```
Once the BBB has rebooted open a secure shell to update and upgrade to the most up-to-date software packages.
```bash
sudo apt-get update
sudo apt-get upgrade
sudo reboot
```
## Step 4: Compile WxWidgets library for the BBB.
Download source code for wxWidgets on your Ubuntu VM.
```bash
wget https://github.com/wxWidgets/wxWidgets/archive/v3.0.4.tar.gz
```
Copy the tar compression to your BBB.
```bash
scp v3.0.4.tar.gz debian@192.168.7.2:/home/debian
```
Open a secure shell with your BBB.
```bash
ssh 192.168.7.2 -l debian
```
Extract the tar file.
```bash
tar -xf v3.0.4.tar.gz
```
Change to the wxWidgets library directory.
```bash
cd wxWidgets-3.0.4
```
Install the necessary libraries for GTK and wxWidgets.
```bash
sudo apt-get install build-essential libgtk-3-dev
sudo apt-get install libwxbase3.0-dev
sudo apt-get install libwxgtk3.0-dev
```
Configure the wxWidgets library makefile for the BBB platform.
```bash
./configure
```
Compile the wxWidgets library using the make utility.
```bash
make
```
Install the wxWidgets library and update the links to the shared libraries in your BBB.
```bash
sudo make install
sudo ldconfig
```
Exit the ssh session.
``` bash
exit
```
## Step 5: Compile your WxWidgets application and run it on the BBB.

In your Ubuntu VM navigate to the directory of the Traffic Sim project. It should be zipped already.
```bash
cd ~/Traffic-Sim/TrafficSim
```

Transfer the zipped project into the BBB.

```bash
scp TrafficSim.tar debian@192.168.7.2:/home/debian
```

Open a secure shell to your BBB.

```bash
ssh 192.168.7.2 -l debian
```

Extract the project tar file.

```bash
unzip TrafficSim.zip
```

Compile your wxWidgets application using the make utility.

```bash
make
```

Execute the program.

```bash
./TrafficSim
```
