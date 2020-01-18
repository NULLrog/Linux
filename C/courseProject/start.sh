#!/bin/bash
echo Start!
xterm -geometry 60x25+10+0 -e ./server & 
xterm -geometry 60x25+1000+10 -e ./client1 &
xterm -geometry 60x25+1000+1000 -e ./client1 &
xterm -geometry 60x25+500+10 -e ./client2 &
xterm -geometry 60x25+500+1000 -e ./client2 &
