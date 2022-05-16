/*
Copyright (c) 2022, TIANJIN DATA IMAGING TECHNOLOGY CO.,LTD
Copyright (c) 2022, xumm@csoneplus.com
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the copyright holder nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef unsigned short u16;

void print_help(void)
{
    printf(" ./pixel_layer_convert -I [input format] -i [inputfile] -o [outputfile] \
    input format: XY10,XY12,TY10,TY12,Y10P,Y12P\
    output format: Y10 or Y12 \r\n");
}

int __JetsonConvert(FILE * infd,FILE * outfd,int shift)
{
    unsigned short pixldata;
    size_t len = 0;
    size_t total = 0;
    while(1){
        if((len = fread(&pixldata,sizeof(u16),1,infd)) != 1){
            break;
        }
        pixldata >>= shift;
        if((len = fwrite(&pixldata,sizeof(u16),1,outfd)) != 1){
            break;
        }
        total += sizeof(u16);
    }
    return total;
}
int __XY10(FILE * infd,FILE * outfd)
{
    printf("convert XY10 to Y10 ,total len %d finished\r\n",__JetsonConvert(infd,outfd,5));
    return 0;
}

int __XY12(FILE * infd,FILE * outfd)
{
    printf("convert XY12 to Y12 ,total len %d finished\r\n",__JetsonConvert(infd,outfd,3));
    return 0;
}

int __TY10(FILE * infd,FILE * outfd)
{
    printf("convert TY10 to Y10 ,total len %d finished\r\n",__JetsonConvert(infd,outfd,4));
    return 0;
}

int __TY12(FILE * infd,FILE * outfd)
{
    printf("convert TY12 to Y12 ,total len %d finished\r\n",__JetsonConvert(infd,outfd,2));
    return 0;
}

int __Y10P(FILE * infd,FILE * outfd)
{
    unsigned char pixldata[6];
    size_t len = 0;
    int total = 0;
    unsigned char tmp;
    while(1){
        if((len = fread(&pixldata,sizeof(char),5,infd)) != 5){
            break;
        }
        tmp = pixldata[0];
        if((len = fwrite(&tmp,sizeof(char),1,outfd)) != 1){
            break;
        }
        total += sizeof(char);
        
        tmp = pixldata[1]&0x03;
        if((len = fwrite(&tmp,sizeof(char),1,outfd)) != 1){
            break;
        }
        total += sizeof(char);
        
        tmp = (pixldata[1]>>2)+(pixldata[2]<<6);
        if((len = fwrite(&tmp,sizeof(char),1,outfd)) != 1){
            break;
        }
        total += sizeof(char);
        
        tmp = (pixldata[2]>>2) & 0x3;
        if((len = fwrite(&tmp,sizeof(char),1,outfd)) != 1){
            break;
        }
        total += sizeof(char);
        
        tmp = (pixldata[2]>>4) + (pixldata[3]<<4);
        if((len = fwrite(&tmp,sizeof(char),1,outfd)) != 1){
            break;
        }
        total += sizeof(char);
        
        tmp = (pixldata[3]>>4) & 0x3;
        if((len = fwrite(&tmp,sizeof(char),1,outfd)) != 1){
            break;
        }
        total += sizeof(char);
        
        tmp = (pixldata[3]>>6) + (pixldata[4]<<2);
        if((len = fwrite(&tmp,sizeof(char),1,outfd)) != 1){
            break;
        }
        total += sizeof(char);
        
        tmp = (pixldata[4]>>6) & 0x3;
        if((len = fwrite(&tmp,sizeof(char),1,outfd)) != 1){
            break;
        }
        total += sizeof(char);

    }
    printf("convert TY12 to Y12 ,total len %d finished\r\n",total);
    return 0;
}

int __Y12P(FILE * infd,FILE * outfd)
{
    unsigned char pixldata[4];
    size_t len = 0;
    int total = 0;
    unsigned char tmp;
    while(1){
        if((len = fread(&pixldata,sizeof(char),3,infd)) != 3){
            break;
        }
        tmp = pixldata[0];
        if((len = fwrite(&tmp,sizeof(char),1,outfd)) != 1){
            break;
        }
        total += sizeof(char);
        
        tmp = pixldata[1]&0x0F;
        if((len = fwrite(&tmp,sizeof(char),1,outfd)) != 1){
            break;
        }
        total += sizeof(char);
        
        tmp = (pixldata[1]>>4)+(pixldata[2]<<4);
        if((len = fwrite(&tmp,sizeof(char),1,outfd)) != 1){
            break;
        }
        total += sizeof(char);
        
        tmp = pixldata[2]>>4;
        if((len = fwrite(&tmp,sizeof(char),1,outfd)) != 1){
            break;
        }
        total += sizeof(char);
    }
    printf("convert TY12 to Y12 ,total len %d finished\r\n",total);
    return 0;
}



int main(int argc, char *argv[])
{
    int opt;
    int ret = 0;
    int infilesize = 0;
    char *infile = NULL;
    char *outfile = NULL;
    char *informat = NULL;
    FILE *infd = NULL;
    FILE *outfd = NULL;

    char *optstring = "I:i:o:h"; 
    while ((opt = getopt(argc, argv, optstring)) != -1) {
        switch(opt) {
          case 'I': 
            informat = optarg;
            break;
          case 'i': 
            infile = optarg;
            break;
          case 'o': 
            outfile = optarg;
            break;
          case 'h':
            print_help();
            return 0;
            break;
          default:
            printf("option not supported!\r\n");
            return -1;
        }
    }
    if(infile == NULL){
         printf("No input file\r\n");
         return -1;
    }
    if(outfile == NULL){
         printf("No output file\r\n");
         return -1;
    }
    if(informat == NULL){
         printf("No informat\r\n");
         return -1;
    }
    printf("input format %s, input file %s, outputfile %s\r\n",informat,infile,outfile);
    infd = fopen(infile,"rb");
    if(infd == NULL){
        printf("open input file err \r\n");
        ret = -1;
        goto quit;
    }
    outfd = fopen(outfile,"wb+");
    if(outfd == NULL){
        printf("open output file err \r\n");
        ret = -1;
        goto quit;
    }
    
    fseek(infd,0L,SEEK_END);
    infilesize=ftell(infd);
    printf("input file size %d\r\n",infilesize);
    fseek(infd,0L,SEEK_SET);
    
    if(strcasecmp(informat,"XY10") == 0){
        __XY10(infd,outfd);
    }else if(strcasecmp(informat,"XY12") == 0){
        __XY12(infd,outfd);
    }else if(strcasecmp(informat,"TY10") == 0){
        __TY10(infd,outfd);
    }else if(strcasecmp(informat,"TY12") == 0){
        __TY12(infd,outfd);
    }else if(strcasecmp(informat,"Y10P") == 0){
        __Y10P(infd,outfd);
    }else if(strcasecmp(informat,"Y12P") == 0){
        __Y12P(infd,outfd);
    }else {
        printf("input format not supported.\r\n");
    }
    
    quit:
    if(infd) fclose(infd);
    if(outfd) fclose(outfd);
    
    return ret;
}
