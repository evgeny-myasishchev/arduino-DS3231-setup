# Arduino sketch to setup RTC clock (DS3231)

This repo can be used to setup RTC clock (DS3231). The sketch includes a simple AT based serial communication protocol that can be used to set the time.

The solution can be embedded into existing projects if serial line is not very busy and enough flash space is available. In the other case just flash it once, setup the clock and then flash your project.

## Usage

Upload the sketch:
```bash
pio run -t upload -e nano
```
Note: specify your board or add a new board if not present on a list.

Read serial device associated with your board:
```bash
cat /dev/cu.usbserial-1420
```
Note: make sure to use appropriate serial device

In a separate shell run commands below:
```bash
# To test if all good. You should see OK as an output
echo -e "AT" > /dev/cu.usbserial-1420

# Set current date 
echo -e "AT+TIME=$(date +%s)" > /dev/cu.usbserial-1420

# Set time zone
echo -e "AT+ZONE=$(date +%z)" > /dev/cu.usbserial-1420

# Show actual time value
echo -e "AT+TIME" > /dev/cu.usbserial-1420
```

Or just use script
```
bin/set-time.sh /dev/cu.usbserial-1420
```