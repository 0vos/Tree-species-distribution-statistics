#include "io.cpp"
#include "statistic.cpp"
#include <thread>
#include <fstream>
#include <iostream>
#include <string>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8192
const int BUFFER_SIZE = 8192;
std::atomic<bool> running(true);
using namespace std;
bool ends_with(const string& str, const string& suffix) {
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
    string *trees = new string[count_useful_lines(file_name)];
    read(file_name, trees, count_lines(file_name));
    string raw = get_statistic(trees, count_useful_lines(file_name));
    string response_body = statistic_string2json(raw);
    // cout << response_body << endl;
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
    try {
        if (request.find("GET /statistic") != string::npos) {
            send_statistic(client_socket);
        } else if (request.find("GET ") != string::npos) {
            size_t pos = request.find("GET ");
            size_t path_end = request.find(" ", pos + 4);
            string file_path = request.substr(pos + 4, path_end - pos - 4);

            if (file_path == "/") {
                file_path = "index.html"; // 默认首页
            } else {
                file_path = file_path.substr(1); // 去掉开头的 "/"
            }

            // 检查路径是否包含危险字符
            if (file_path.find("..") != string::npos) {
                string error_response =
                    "HTTP/1.1 400 Bad Request\r\n\r\n";
                send(client_socket, error_response.c_str(), error_response.length(), 0);
                close(client_socket);
                return;
            }

            serve_static_file(client_socket, file_path);
        } else {
            // 如果请求方法不为 GET，返回 405 错误
            string error_response =
                "HTTP/1.1 405 Method Not Allowed\r\n"
                "Content-Length: 0\r\n\r\n";
            send(client_socket, error_response.c_str(), error_response.length(), 0);
            close(client_socket);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error while serving request: " << e.what() << std::endl;
        string error_response =
            "HTTP/1.1 500 Internal Server Error\r\n"
            "Content-Length: 0\r\n\r\n";
        send(client_socket, error_response.c_str(), error_response.length(), 0);
        close(client_socket);
    } catch (...) {
        std::cerr << "Unknown error occurred while serving request." << std::endl;
        string error_response =
            "HTTP/1.1 500 Internal Server Error\r\n"
            "Content-Length: 0\r\n\r\n";
        send(client_socket, error_response.c_str(), error_response.length(), 0);
        close(client_socket);
    }
}

// 服务器主线程
void server_thread() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // 创建套接字
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }
    std::cout << "Socket created successfully\n";

    // 设置服务器地址相关信息
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // 绑定套接字到指定地址和端口
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    std::cout << "Bind successful\n";

    // 开始监听端口，允许的最大连接队列长度为3
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    std::cout << "Listening on port " << PORT << "\n";

    // 循环接受请求
    while ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) >= 0) {
        if(!running){
            break;
        }
        char buffer[BUFFER_SIZE];
        std::string request;
        request.reserve(1024 * 1000); // 预留空间，可按实际预估调整
        int valread;

        // 读取 HTTP 请求头和数据
        while ((valread = read(new_socket, buffer, BUFFER_SIZE - 1)) > 0) {
            buffer[valread] = '\0'; // 确保缓冲区以 null 结尾
            request.append(buffer, valread);

            // 检查是否包含完整的 HTTP 报文
            auto header_end = request.find("\r\n\r\n");
            if (header_end != std::string::npos) {
                // HTTP 报文包含头部，检查 Content-Length
                size_t content_length_pos = request.find("Content-Length: ");
                if (content_length_pos != std::string::npos) {
                    size_t start = content_length_pos + 16; // "Content-Length: " 长度
                    size_t end = request.find("\r\n", start);
                    int content_length = std::stoi(request.substr(start, end - start));
                    size_t total_length = header_end + 4 + content_length; // 头部 + \r\n\r\n + 内容

                    if (request.length() >= total_length) {
                        break; // 接收完整
                    }
                } else {
                    break; // 没有 Content-Length，默认认为是完整的
                }
            }
        }

        if (valread < 0) {
            perror("Read error");
            close(new_socket);
            continue;
        }

        // std::cout << "Request received. Length: " << request.length() << " bytes\n";

        try {
            serve_request(new_socket, request); // 调用处理函数
        } catch (...) {
            std::cerr << "An error occurred while serving the request\n";
        }

        request.clear();
        memset(buffer, 0, BUFFER_SIZE);
        close(new_socket);
    }

    if (new_socket < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    close(server_fd);
}

// 控制台输入线程
void console_thread() {
    string command;
    while (running) {
        string hint = "\n<----------树种统计程序---------->\n*         1. 查找一棵树          *\n*         2. 增加一棵树          *\n*         3. 删除一棵树          *\n*         4. 退出                *\n请输入功能对应的序号进行操作: ";
        cout << hint << endl;
        cin >> command;

        if (command == "1") {
            try {
                search_trees("tree_info.txt");
            } catch (const exception& e) {
                cerr << "搜索时出现错误：" << e.what() << endl;
            }
        } else if (command == "2") {
            printf("请输入树名及其他信息\n(树名和其他信息之间用英文逗号隔开)，输入exit退出：");
            try {
                add("tree_info.txt");
            } catch (const exception& e) {
                cerr << "增加时出现错误：" << e.what() << endl;
            }
        } else if (command == "3") {
            printf("请输入树名进行删除，输入exit退出：");
            try {
                remove_info("tree_info.txt");
            } catch (const exception& e) {
                cerr << "删除时出现错误：" << e.what() << endl;
            }
        } else if (command == "4") {
            printf("正在退出...\n");
            running = false; // 让服务器线程退出
        } else {
            cout << "未知命令:" << command << endl;
        }
    }
}

int main() {
    // 启动服务器线程
    thread server(server_thread);

    // 启动控制台输入线程
    thread console(console_thread);

    // 等待两个线程完成
    console.join();
    server.join();
    printf("结束\n");

    return 0;
}
