#!/bin/sh

mac_addr=84:5d:d7:00:11:22

ifconfig eth0 hw ether $mac_addr up

udhcpc -b -t 0 -i eth0 -s /etc/udhcpc.script &

