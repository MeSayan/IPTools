/*----------------------------------------------------------------------
 * Name:   ipgeo
 * Author: Sayan Mahapatra
 * Date:	23/05/2016
 * Description: A small program to list out geographical details of each
 * hop in a route.
 * In short it is a route tracing program which prints geopgraphic 
 * details of each hop from host machine to another machine.
 * Details of IP are obtained from "ipinfo.io" website
 * Copyright © 2016 Sayan Mahapatra
 *---------------------------------------------------------------------
 */


#include  <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc,char *argv[])
{
	int strrec;
	char c;
	char *d;
	char command[50];
	char buffer[20];;
	
	//Program takes exactly one input .Other inputs are ignored
	//if no inputs are available program terminates
	if(argc==1)
	exit(1);
	
	//Generating Route Information File
	sprintf(command,"traceroute %s >routeinfo.txt",argv[1]);
	system(command);
	
	
	//Parsing routeinfo for list of addresss
	FILE *wp=fopen("iplist.txt","w");
	FILE *rp=fopen("routeinfo.txt","r");
	
	
	if(wp==NULL || rp==NULL)
	{
		printf("File Error try again later\n");
		exit(2);
	}
	while((c=fgetc(rp))!=EOF)
	{
		if(c==')'){
		strrec=0;
		putc('\n',wp);
		}
		
		else if(c=='('){
		strrec=1;
		continue;
		}
		
		if(strrec==1)
			putc(c,wp);
	}
	
	//Closing routeinfo and iplist
	fclose(rp);
	fclose(wp);
	
	//Parsing iplist file 
	rp=fopen("iplist.txt","r");
	
	
	if(rp==NULL)
	{
		printf("File Error Try Again Later\n");
		return -1;
	}
	
	
	
	//Ignoring First Value 
	fscanf(rp,"%s",buffer);
		
	//Generating output.txt which contains geographic details of hops
	while(fscanf(rp,"%s",buffer)!=EOF)
	{
		if(!strstr(buffer,"172."))
		sprintf(command,"curl -s ipinfo.io/%s>>output.txt",buffer);
		system(command);
	}
	fclose(rp);
	
	//Copying output.txt to final.txt so data can be properly formatted.
	rp=fopen("output.txt","r");
	wp=fopen("final.txt","w");
	
	if(rp==NULL||wp==NULL)
	{
		printf("File Error Try Again Later\n");
		exit(2);
	}
	
	//Performing some formatting on final.txt
	
	while(fgets(buffer,80,rp)!=NULL)
	{
		for(d=buffer;*d!='\n';d++)
		{   
			if(*d=='{'|| *d=='}')
			{
				fputs("-----------------------------------------------"
					  "-------------------------",wp);
				break;//Ignore further reading that line
			}
			if(*d!='"')
			putc(*d,wp);
			
			else if(*d=='"'&& *(d+1)=='"')
			fprintf(wp,"N/A");
		}
		putc('\n',wp);
	}
	
	fclose(rp);
	fclose(wp);	
	
	//Using grep to display only lines which contain city,regio etc
	system("grep -e ip -e city -e region -e country -e postal -e --"
			"final.txt");
	
	//Cleaning Up!
	system("rm ./routeinfo.txt ./output.txt  ./iplist.txt ./final.txt");
	
	
	
	exit(0);//Indicates program success
}
