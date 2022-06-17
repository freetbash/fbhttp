#ifndef FB_HTTP_REQUESTS
#define FB_HTTP_REQUESTS
#include <string>
#include <vector>
#include <map>
class Requests{
public:
    std::map<std::string,std::string> headers;
    std::string text;
    std::string status;
    std::string status_code;
    Requests *const get(std::string url);
    Requests *const post(std::string url,std::map<std::string,std::string> kwargs);

};
std::vector<std::string> split(std::string s, std::string d);
extern std::string HTTP_VERSION;
extern std::string HTTP_DELIM;
void DOWNLOAD(std::string url,std::string file_path);





#endif