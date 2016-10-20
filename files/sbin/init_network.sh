#!/bin/sh

MAC_ADDR=`cfg get mac | awk -F = '{print $2}'`

if [ -n "$MAC_ADDR" ]; then
	macaddr="${MAC_ADDR:0:2}:${MAC_ADDR:2:2}:${MAC_ADDR:4:2}:${MAC_ADDR:6:2}:${MAC_ADDR:8:2}:${MAC_ADDR:10:2}"
else
	macaddr=84:5d:d7:00:11:22
fi

ifconfig eth0 hw ether $macaddr up

udhcpc -b -t 0 -i eth0 -s /etc/udhcpc.script &

