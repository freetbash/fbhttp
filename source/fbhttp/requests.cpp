#include <requests.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <regex>
#include <httptool.h>
#include <arpa/inet.h>
#include <iostream>
#include<unistd.h>

std::string HTTP_VERSION="HTTP/1.1";
std::string HTTP_DELIM="\r\n";
Requests *const Requests::get(std::string url){
        // fisrt;
        std::smatch results;
        std::smatch sm;
        std::regex p("(https?)://(.*?)(/.+)");
        if(std::regex_match(url,results,p)){
            int sfd = socket(AF_INET,SOCK_STREAM,0);
            struct sockaddr_in  server_addr;  
            int port;
            std::string head=(
                    "HEAD "+std::string(results[3])+" "+HTTP_VERSION+HTTP_DELIM
                    +"Host: "+std::string(results[2])+HTTP_DELIM
                    +"User-Agent: Ccao Star Getter"+HTTP_DELIM
                    +"Accept: */*"+HTTP_DELIM
                    +"Connection: close"+HTTP_DELIM
                    +HTTP_DELIM
                );
            
            if(std::string(results[1])=="https"){
                // https
            }else{
                // http
                
                std::regex sp("(.*?):(.+)");
                std::string _ = results[2];
                if(std::regex_match(_,sm,sp)){
                    port=std::stoi(sm[2]);
                }else{
                    port=80;
                }
            }
            bzero(&server_addr, sizeof(server_addr));  
            server_addr.sin_family = AF_INET;  
            server_addr.sin_port = htons(port);
            // server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
            // connect(server_addr,(struct sockaddr *)&server_addr)
            std::string d_ip = sm[1];
            inet_aton(getipbydomain(d_ip).c_str(), &server_addr.sin_addr);
            socklen_t server_addr_length = sizeof(server_addr); 

            if(int c=connect(sfd, (struct sockaddr*)&server_addr, server_addr_length)<0){
                std::cout<<("connect error!\n");
                exit(1);
            }else{
                char data[1024];
                memset(data,0,sizeof(data));
                send(sfd,head.c_str(),strlen(head.c_str()),0);
                recv(sfd,data,sizeof(data),0);
                std::string cc = data;
                std::regex p("\\r\\nContent-Length: (.*?)\\r\\n");
                std::smatch sdcw;
                close(sfd);
                if(std::regex_search(cc,sdcw,p)){
                    long long int size = std::stol(sdcw[1]);
                        int nsfd = socket(AF_INET,SOCK_STREAM,0);
                        struct sockaddr_in  nserver_addr;  
                        bzero(&server_addr, sizeof(server_addr));  
                        nserver_addr.sin_family = AF_INET;  
                        nserver_addr.sin_port = htons(port);
                        inet_aton(getipbydomain(d_ip).c_str(), &nserver_addr.sin_addr);

                    connect(nsfd, (struct sockaddr*)&nserver_addr, server_addr_length);
                    head=(
                    "GET "+std::string(results[3])+" "+HTTP_VERSION+HTTP_DELIM
                    +"Host: "+std::string(results[2])+HTTP_DELIM
                    +"User-Agent: Ccao Star Getter"+HTTP_DELIM
                    +"Accept: */*"+HTTP_DELIM
                    +"Connection: close"+HTTP_DELIM
                    +HTTP_DELIM
                    );
                    char temp[1024];
                    send(nsfd,head.c_str(),strlen(head.c_str()),0);
                    char ch;
                    int trecv;
                    while((trecv=recv(nsfd,&ch,1,0))>0){
                        if(ch=='\r'){
                            trecv=recv(nsfd,&ch,1,0);
                            if(trecv>0 and ch =='\n'){
                                trecv=recv(nsfd,&ch,1,0);
                                if(trecv>0 and ch =='\r'){
                                    trecv=recv(nsfd,&ch,1,0);
                                    if(trecv>0 and ch =='\n'){
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    this->text="";
                        for(;;){
                        // /r/n/r/n 连续两个
                        if(trecv>0){
                            trecv=recv(nsfd,temp,1024,0);
                            this->text += std::string(temp);
                            bzero(temp,sizeof(temp));
                        }else{
                            //LOG(std::to_string(i));
                            break;
                        }
                        
                    }
                    close(nsfd);
                }else{
                    std::cout<<("The http server is not correct!\n");
                }


            }
        }else{
            std::cout<<"not a http request ! "<<std::endl;
        }



        return this;
        // http://asdasdasddsa:80/123123123
    //     my_addr.sin_family = AF_INET; /* host byte order */
    // 　　 my_addr.sin_port = htons(MYPORT); /* short, network byte order */
    // 　　 my_addr.sin_addr.s_addr = inet_addr("132.241.5.10");
}



void DOWNLOAD(std::string url,std::string file_path){
        // fisrt;
        std::smatch results;
        std::smatch sm;
        std::regex p("(https?)://(.*?)(/.+)");
        if(std::regex_match(url,results,p)){
            int sfd = socket(AF_INET,SOCK_STREAM,0);
            struct sockaddr_in  server_addr;  
            int port;
            std::string head=(
                    "HEAD "+std::string(results[3])+" "+HTTP_VERSION+HTTP_DELIM
                    +"Host: "+std::string(results[2])+HTTP_DELIM
                    +"User-Agent: Ccao Star Getter"+HTTP_DELIM
                    +"Accept: */*"+HTTP_DELIM
                    +"Connection: close"+HTTP_DELIM
                    +HTTP_DELIM
                );
            
            if(std::string(results[1])=="https"){
                // https
            }else{
                // http
                
                std::regex sp("(.*?):(.+)");
                std::string _ = results[2];
                if(std::regex_match(_,sm,sp)){
                    port=std::stoi(sm[2]);
                }else{
                    port=80;
                }
            }
            bzero(&server_addr, sizeof(server_addr));  
            server_addr.sin_family = AF_INET;  
            server_addr.sin_port = htons(port);
            // server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
            // connect(server_addr,(struct sockaddr *)&server_addr)
            std::string d_ip = sm[1];
            inet_aton(getipbydomain(d_ip).c_str(), &server_addr.sin_addr);
            socklen_t server_addr_length = sizeof(server_addr); 

            if(int c=connect(sfd, (struct sockaddr*)&server_addr, server_addr_length)<0){
                std::cout<<("connect error!\n");
                exit(1);
            }else{
                char data[1024];
                memset(data,0,sizeof(data));
                send(sfd,head.c_str(),strlen(head.c_str()),0);
                recv(sfd,data,sizeof(data),0);
                std::string cc = data;
                std::regex p("\\r\\nContent-Length: (.*?)\\r\\n");
                std::smatch sdcw;
                close(sfd);
                if(std::regex_search(cc,sdcw,p)){
                    long long int size = std::stol(sdcw[1]);
                        int nsfd = socket(AF_INET,SOCK_STREAM,0);
                        struct sockaddr_in  nserver_addr;  
                        bzero(&server_addr, sizeof(server_addr));  
                        nserver_addr.sin_family = AF_INET;  
                        nserver_addr.sin_port = htons(port);
                        inet_aton(getipbydomain(d_ip).c_str(), &nserver_addr.sin_addr);

                    connect(nsfd, (struct sockaddr*)&nserver_addr, server_addr_length);
                    head=(
                    "GET "+std::string(results[3])+" "+HTTP_VERSION+HTTP_DELIM
                    +"Host: "+std::string(results[2])+HTTP_DELIM
                    +"User-Agent: Ccao Star Getter"+HTTP_DELIM
                    +"Accept: */*"+HTTP_DELIM
                    +"Connection: close"+HTTP_DELIM
                    +HTTP_DELIM
                    );
                    char temp[1024];
                    FILE *fp = fopen(file_path.c_str(),"w");
                    send(nsfd,head.c_str(),strlen(head.c_str()),0);
                    int i;
                    bool flag=false;
                    long int total=0;
                    // fuck head
                    char ch;
                    int trecv;
                    while((trecv=recv(nsfd,&ch,1,0))>0){
                        if(ch=='\r'){
                            trecv=recv(nsfd,&ch,1,0);
                            if(trecv>0 and ch =='\n'){
                                trecv=recv(nsfd,&ch,1,0);
                                if(trecv>0 and ch =='\r'){
                                    trecv=recv(nsfd,&ch,1,0);
                                    if(trecv>0 and ch =='\n'){
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    for(;;){
                        // /r/n/r/n 连续两个
                        if(trecv>0){
                            trecv=recv(nsfd,temp,1024,0);
                            total+=trecv;
                            fwrite(temp,trecv,1,fp);
                            progress_bar((long int)total,size);
                        }else{
                            //LOG(std::to_string(i));
                            break;
                        }
                        
                    }
                    std::cout<<(std::to_string(total))<<std::endl;
                    std::cout<<(file_path)<<std::endl;
                    fflush(fp);
                    fclose(fp);
                    close(nsfd);
                }else{
                    std::cout<<("The http server is not correct!\n");
                }


            }
        }else{
            std::cout<<"not a http request ! "<<std::endl;
        }



        // http://asdasdasddsa:80/123123123
    //     my_addr.sin_family = AF_INET; /* host byte order */
    // 　　 my_addr.sin_port = htons(MYPORT); /* short, network byte order */
    // 　　 my_addr.sin_addr.s_addr = inet_addr("132.241.5.10");
}