/*------------------------------------------------------------------------------
 * Name:   ipgeo
 * Author: Sayan Mahapatra
 * Date:	23/05/2016
 * Description: A frontend to traceroute command which also prints out the 
 * geographic details of each hop . Since private IP's can't be traced they are
 * ignored.
 * In short it is a route tracing program which prints geopgraphic 
 * details of each hop from host machine to destination machine.
 * Details of IP are obtained from "ipinfo.io" website
 * Copyright © 2016 Sayan Mahapatra.
 *------------------------------------------------------------------------------
 */

#include  <stdio.h>
#include <stdlib.h>
#include <string.h>

void cleanup();


int main(int argc,char *argv[])
{
	int strrec,i;
	char c;
	char *d;
	char command[255]="";
	char buffer[255]="";
	
	//Program takes exactly one input .Other inputs are ignored
	//if no inputs are available program terminates
	if(argc==1)
	exit(1);
	
	for(i=1;i<argc;i++)
	{
		strcat(buffer," ");
		strcat(buffer,argv[i]);
	}
		
	//Generating Route Information File
	sprintf(command,"traceroute %s > routeinfo.txt",buffer);
	system(command);
	
	//Restoring buffer to empty state
	strcpy(buffer,"");
	
	//Parsing routeinfo for list of addresss
	FILE *wp=fopen("iplist.txt","w");
	FILE *rp=fopen("routeinfo.txt","r");
	
	
	if(wp==NULL || rp==NULL)
	{
		cleanup();
		exit(2);
	}
	
	//Getting Status from traceroute
	fgets(buffer,255,rp);
	
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
		cleanup();
		exit(2);
	}
	
	
	
	printf("%s",buffer);
	
	//Skipping first line of iplist
	fscanf(rp,"%s",buffer);
	
	//Generating output.txt which contains geographic details of hops
	while(fscanf(rp,"%s",buffer)!=EOF)
	{
		if(!strstr(buffer,"172."))
		sprintf(command,"curl -s ipinfo.io/%s>>output.txt",buffer);
		system(command);
	}
	fclose(rp);
	
	/*****/
	
	//Copying output.txt to final.txt so data can be properly formatted.
	rp=fopen("output.txt","r");
	wp=fopen("final.txt","w");
	
	if(rp==NULL||wp==NULL)
	{       
		cleanup();
		exit(4);
	}
	//Performing some formatting on final.txt
	
	while(fgets(buffer,80,rp)!=NULL)
	{
		for(d=buffer;*d!='\n';d++)
		{   
			if(*d=='{'|| *d=='}')
			{
				fputs("--------------------------------------------------------"
				"-----------------------",wp);
				break;//Ignore further reading that line
			}
			if(*d!='"' && *d!=',' )
			putc(*d,wp);
			
			else if(*d=='"'&& *(d+1)=='"')
			fprintf(wp,"N/A");
		}
		putc('\n',wp);
	}
	
	fclose(rp);
	fclose(wp);	
	
	//Displaying only lines which contain desired geo details
	rp=fopen("final.txt","r");
	if(rp == NULL)
	{	
		cleanup();
		exit(5);
    }
	
	while(fgets(buffer,80,rp)!=NULL)
	{
		if(!strstr(buffer,"hostname") && !strstr(buffer,"org"))
		printf("%s",buffer);
	}
	
	//Cleaning Up!
	fclose(rp);
	cleanup();
	exit(0);//Indicates program success
	
}

void cleanup()
{
	//Removing Files
	remove("routeinfo.txt");
	remove("iplist.txt");
	remove("output.txt");
	remove("final.txt");
}
