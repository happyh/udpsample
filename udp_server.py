#!/bin/python
#########################################################################
# File Name: udp_server.py
# Author: happyhe
# mail: heguang@qiyi.com
# Created Time: Fri 31 Jul 2020 10:40:51 AM CST
# only for python2
#########################################################################
# coding=utf8
import socket
import getopt
import sys
import time

def read_udp_data(conn):
    data,client_addr = conn.recvfrom(1024)
    if data:
        print("udp:",data)
        conn.sendto(data,client_addr)
    else:
        epoll.unregister(conn)


def print_usage():
    print("usage:")
    print("udp_server [-p 1234]")
    sys.exit()

if __name__ == '__main__':
    opts, args = getopt.getopt(sys.argv[1:], '-h-p:', ['help', 'port='])
    udp_port = 1234
    for opt_name, opt_value in opts:
        if opt_name in ('-h', '--help'):
            print_usage()
        if opt_name in ('-p', '--port'):
            udp_port = opt_value
            print("udp ports is ", udp_port)

    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.bind(("",udp_port)) 
    lastprinttime = time.time()
    received = {}
    while True:
         data, addr = s.recvfrom(1024)
         received[addr] = received.get(addr, 0) + 1
         index = int(data)
         if received[addr] != index :
            print("{}\t error need:{},get:{},from:{}".format( time.asctime( time.localtime(time.time()) ),received[addr],index,addr))
            received[addr] = index
         elif time.time()-lastprinttime>1 :
            lastprinttime = time.time()

