#!/bin/python
#########################################################################
# File Name: udp_client.py
# Author: happyhe
# mail: heguang@qiyi.com
# Created Time: Fri 31 Jul 2020 10:40:51 AM CST
#########################################################################
# coding=utf8

import socket
import getopt
import sys
import time

def print_usage():
    print("usage:")
    print("udp_client -i 123.125.118.77 [-p 1234 -s 10000000]")
    sys.exit()


if __name__ == '__main__':
    opts, args = getopt.getopt(sys.argv[1:], '-h-i:-p:-s:', ['help', 'udp=','ip=',"port=","speed="])
    udp_port = 1234
    ip = ""
    speed = 10000000
    for opt_name, opt_value in opts:
        if opt_name in ('-h', '--help'):
            print_usage()
        if opt_name in ('-i', '--ip'):
            ip = opt_value
            print("[*] ip is ", ip)
        if opt_name in ('-p', '--port'):
            udp_port = int(opt_value)
            print("[*] udp_port is ", udp_port)
        if opt_name in ('-s', '--speed'):
            speed = int(opt_value)
            print("[*] speed is ", speed)

    if ip == "" :
        print_usage()
        
    client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        begintime = time.time()
        ip_port = (ip, udp_port)
        i = 1
        sendedcount = 0
        lastprinttime = time.time()
        while True:
            if (time.time()-begintime)*speed > sendedcount:
                client.sendto(str(i).ljust(1000," "),ip_port)
                sendedcount = sendedcount+1000
                i = i + 1 
            else:
                if time.time()-lastprinttime>1:
                    print("time:",time.time(),",sendindex:",i)
                    lastprinttime = time.time()
                time.sleep(0.001)
    except Exception, err:
        print("error:" + str(i), err)
    client.close()


