# mobile_robots
Project for Mobile_Robots

## HW and its Configuration
This chapter describes used hardware for project and its configuration.

### Raspberry PI 3
Raspberry PI is running Ubuntu MATE. Computer name and login name are *rpi3-2* the password is *rpi*. RPI is configured to automatically connect to wifi named *rpi3-2* with password *tatranky111*. Because the wifi is provided by Windows 10 hotspot, RPI can't use static IP and must requests DHCP server. Network adress is *192.168.137.0/24*.

## FAQ
### Unable to use apt-get on RPI3
```
E: Could not get lock /var/lib/dpkg/lock - open (11: Resource temporarily unavailable)
E: Unable to lock the administration directory (/var/lib/dpkg/), is another process using it?`
```

It is possible that auto update is running. You can check it by *ps -e | grep  unattended-upgr*. If you find any process with that name running then that it is. You must to wait for end of that process. You can also check udpates log */var/log/dpkg.log*, or the files in */var/log/unattended-upgrades/*.

### Usage of application: screen
For starting new screen session type *screen*

For detaching screen use key combination ctrl+a+d

For attaching dettached screen use command *screen -r*
