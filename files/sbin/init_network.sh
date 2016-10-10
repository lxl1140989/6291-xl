#!/bin/sh


ifconfig eth0 up

udhcpc -b -t 0 -i eth0 -s /etc/udhcpc.script &

