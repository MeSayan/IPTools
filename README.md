# IPTools
A collection of tools  for printing out information  about public IP's from command line itself.
---------------------------------------------------------------------------------------------------------------------------------
Tools:

a) ipinfo : Gives information about one or more IP's passed as parmeters. If no arguments are passed then  ipinfo displays informaion about the Host's IP Adress

Usage: ipinfo 89.55.1.25 89.6.2.45 /*and so on*/ or   ipinfo

b) ipgeo : Gives geographic information of each  hop from host machine to destination machine.
Description: A frontend to traceroute command which also prints out the 
geographic details of each hop . Since private IP's can't be traced they are ignored. In short it is a route tracing program which prints geopgraphic details of each hop from host machine to destination machine.

Usage : ipgeo www.google.com or ipgeo 89.52.36.21
        
Note  : ipgeo fully supports all of traceroute's parameters . Check out the man page for traceroute to get to know these options.

Data is pulled from the website https://ipinfo.io/
---------------------------------------------------------------------------------------------------------------------------------
