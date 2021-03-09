#!/usr/bin/env bash

# Set current date 
echo -e "AT+TIME=$(date +%s)" > $1

# Set time zone
echo -e "AT+ZONE=$(date +%z)" > $1

# Show actual time value
echo -e "AT+TIME" > $1
