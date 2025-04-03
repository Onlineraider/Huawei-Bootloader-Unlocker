# Huawei Bootloader Unlocker
This tool let you unlock the bootloader of your Huawei / Honor Device even if the code can't be found.

After closing the official EMUI website, which allowed to retrieve the code to unlock the bootloader of Huawei/Honor phones, here's the fastest free way to retrieve it by yourself.
it reboots ur phone to the bootloader after 4 attempts to prevent it rebooting in the system after 5 attempts. this saves much time


### How To use it
1. Compile the .C file
    1. `gcc source.c -o exec`
    2. `chmod +x exec`
2. Install Android Developer Tools
3. Enable USB Debug on your device
4. Enable OEM Unlock
3. Connect your device to your computer
4. Use ```adb reboot bootloader``` to reboot your device in bootloader mode
5. Run the program
    1. `./exec`
6. Wait

## FAQ & Troubleshooting
**The app on Windows doesn't detect my device. What could be the issue?**
Windows most likely doesn't recognise your device in ADB mode. 
Install the universal ADB drivers from [here](http://dl.adbdriver.com/upload/adbdriver.zip) then
reboot your PC and try again.

thank the original coder
