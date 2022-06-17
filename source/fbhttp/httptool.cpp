#include <httptool.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <regex>
std::string getipbydomain(std::string domain){
    struct in_addr **addr_list;
    struct hostent *he = gethostbyname(domain.c_str());
    addr_list = (struct in_addr **)he->h_addr_list;
    return std::string(inet_ntoa(*addr_list[0]));
}
std::vector<std::string> split(std::string s, std::string d) { 
	// 正则实现
    std::string text = s;
	std::regex ws_re(d); 
	// whitespace 
	std::vector<std::string> tokens(std::sregex_token_iterator(text.begin(), text.end(), ws_re, -1), std::sregex_token_iterator()); 
	return tokens;
}
void progress_bar(long int x,long int total)
{
    int i;
    char tmp[100] = {0};
    static int x_old = 0;
    double cc = (double)x/(double)(total);
    int s;
    s = (int)(100.0*cc);
    if(s == x_old)
    {
        return;
    }
    x_old = s;
    i = s/2;
    if(i > 50)
        i = 50;
    memset(tmp, '-', i);
    tmp[i]='>';
    printf("\r%d%|%s|", s, tmp);
    fflush(stdout);//立刻输出
}