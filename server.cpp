#include "io.cpp"
#include "statistic.cpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <netinet/in.h>
#include <unistd.h>
#include <regex>
#include <cstring>

#define PORT 8888
const int BUFFER_SIZE = 2048;
using namespace std;
bool ends_with(const std::string& str, const std::string& suffix) {
    return str.size() >= suffix.size() && str.substr(str.size() - suffix.size()) == suffix;
}
// 根据文件扩展名获取 MIME 类型
string get_mime_type(const string& file_path) {
    if (ends_with(file_path, ".html")) return "text/html";
    if (ends_with(file_path, ".css")) return "text/css";
    if (ends_with(file_path, ".js")) return "application/javascript";
    if (ends_with(file_path, ".png")) return "image/png";
    if (ends_with(file_path, ".jpg") || ends_with(file_path, ".jpeg")) return "image/jpeg";
    return "application/octet-stream"; // 默认 MIME 类型
}

// 用于返回GET的统计数据
void send_statistic(int client_socket) {
    string file_name= "tree_info.txt";
    string *trees = new string[count(file_name)];
    read(file_name, trees);
    string raw = get_statistc(trees, count(file_name));
    string response_body = statistic_string2json(raw);
    cout << response_body << endl;
    // 构造 HTTP 响应
    string http_response =
        "HTTP/1.1 200 OK\r\n"                              // 返回成功状态码
        "Content-Type: application/json\r\n"              // 明确指定 JSON 类型
        "Access-Control-Allow-Origin: *\r\n"              // 允许所有源
        "Access-Control-Allow-Methods: POST, GET, OPTIONS\r\n"
        "Access-Control-Allow-Headers: Content-Type\r\n"  // 允许 Content-Type 请求头
        "Content-Length: " + to_string(response_body.length()) + "\r\n\r\n" +
        response_body;

    // 发送响应
    send(client_socket, http_response.c_str(), http_response.length(), 0);
    close(client_socket);
}

// 处理静态文件请求
void serve_static_file(int client_socket, const string& file_path) {
    ifstream file(file_path, ios::binary);
    if (!file.is_open()) {
        // 如果文件不存在，返回 404
        string error_response =
            "HTTP/1.1 404 Not Found\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: 50\r\n\r\n"
            "<html><body><h1>404 Not Found</h1></body></html>";
        send(client_socket, error_response.c_str(), error_response.length(), 0);
        close(client_socket);
        return;
    }

    // 读取文件内容
    stringstream buffer;
    buffer << file.rdbuf();
    string file_content = buffer.str();
    file.close();

    // 获取文件的 MIME 类型
    string mime_type = get_mime_type(file_path);

    // 构造 HTTP 响应
    string http_response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: " + mime_type + "\r\n"
        "Content-Length: " + to_string(file_content.length()) + "\r\n\r\n" +
        file_content;

    send(client_socket, http_response.c_str(), http_response.length(), 0);
    close(client_socket);
}

// 处理客户端请求
void serve_request(int client_socket, const string& request) {
    if(request.find("GET /statistic") != string::npos){
        send_statistic(client_socket);
    }else if (request.find("GET ") != string::npos) {
        // 处理静态文件请求
        size_t pos = request.find("GET ");
        size_t path_end = request.find(" ", pos + 4);
        string file_path = request.substr(pos + 4, path_end - pos - 4);

        if (file_path == "/") {
            file_path = "index.html"; // 默认首页
        } else {
            file_path = file_path.substr(1); // 去掉开头的 "/"
        }

        serve_static_file(client_socket, file_path);
    }
    else {
        // 如果请求方法不为 GET 或 POST，返回 400 错误
        string error_response = "HTTP/1.1 400 Bad Request\r\n\r\n";
        send(client_socket, error_response.c_str(), error_response.length(), 0);
        close(client_socket);
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // 创建套接字
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址相关信息
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // 绑定套接字到指定地址和端口
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // 开始监听端口，允许的最大连接队列长度为3
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    while ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) >= 0) {
        char buffer[BUFFER_SIZE];
        std::string request;
        request.reserve(1024 * 1000);  // 预留一定空间，可按实际预估调整
        int valread;
        do {
            valread = read(new_socket, buffer, BUFFER_SIZE);
            if (valread > 0) {
                request.append(buffer, valread);
            } else if (valread == -1) {
                perror("Read error");
                close(new_socket);
                continue;
            }
        } while (valread == BUFFER_SIZE);

        try {
            std::cout << "request: " << request.length() << std::endl;
            serve_request(new_socket, request);
        } catch (...) {
            std::cerr << "An error occurred while serving request" << std::endl;
            // 关闭客户端套接字，释放相关资源
            close(new_socket);
            continue;
        }

        request.clear();
        memset(buffer, 0, BUFFER_SIZE);
        close(new_socket);
    }

    close(server_fd);
    return 0;
}