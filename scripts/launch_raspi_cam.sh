sudo chmod 777 /dev/vchiq
sudo ifconfig eth0 192.168.0.1 netmask 255.255.255.0
while true; do raspivid -t 0 -n -w 1280 -h 720 -fps 48 -ex fixedfps -b 3000000 -vf -sa -100 -o - | nc -l 8080; done
