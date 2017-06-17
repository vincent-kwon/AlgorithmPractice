#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdarg>
#include <fstream>

#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

using namespace std;
using namespace boost;

const int DELAY = 12;
const int  MAXRECV = 140 * 1024;
const std::string WRITE_DIR_PATH = "/home/vincent/temp";

class WebPage {
 public:
  string hostname;
  string page;

  WebPage() {
    hostname = "";
    page = "";
  }

  string parseHttp(const string str) {
    const boost::regex re("(?i)http://(.*)/?(.*)");
    boost::smatch what;
    if (boost::regex_match(str, what, re)) {
      std::string hst = what[1];
      boost::algorithm::to_lower(hst);
      return hst;
    }
    return "";
  }

  void parseHref(const string orig_host, string str) {
    const boost::regex re("(?i)http://(.*)/(.*)");
    boost::smatch what;
    if (boost::regex_match(str, what, re)) {
      hostname = what[1];
      boost::algorithm::to_lower(hostname);
      page = what[2];
    } 
    else {
      hostname = orig_host;
      page = "";
    }
  }

  void parse(const string orig_host, const string hrf) {
    string hst = parseHttp(hrf);
    if (!hst.empty()) {
      parseHref(hst, hrf);
    } else {
      hostname = orig_host;
      page = hrf;
    }
    
    if (page.length() == 0) {
      page = "/";
    }
  }
};

string string_format(string &fmt, ...) {
  int size = 255;
  string str;
  va_list ap;
  while (1) {
    str.resize(size);
    va_start(ap, fmt);
    int n = vsnprintf((char *) str.c_str(), size, fmp.c_str(), ap);
    if (n > -1 && n < size) {
      str.resize(n);
      return str;
    }

    if (n > -1) {
      size *= n + 1;
    } else {
      size *= 2
    }
  } 
  return str;
}

string request(string host, string path) {
  string request = "GET ";
  request.append(path);
  request.append(" HTTP/1.1\r\n");
  request.append("Host: ");
  request.append(host);
  request.append("\r\n");
  request.append("Accept: text/html, app...");
  request.append("User-Agent: ");
  request.append("Connection: close");
  return request;
}

string clean_href(const string host, const string path) {
  string full_url = host;
  full_url.append("/");
  full_url.append(path);
  boost::regex rmv_all("[^a-zA-Z0-9]");
  const string s2 = boost::regex_replace(full_url, rmv_all, "-");
  return s2;
}

int connect(const std::string host, const string path) {
  const int port = 80;
  int m_sock;
  sockaddr_in m_addr;
  memset(&m_addr, 0, sizeof(m_addr));
  int on = 1;
  if (setsockopt(m_sock, SOL_SOCKET, SO_REUSERADDR, (const char*) &on, sizeof(on)) == -1) {
    return false;
  }

  m_addr.sin_family = AF_INET;
  m_addr.sin_port = htons(port);
  
  int status = inet_pton(AF_INET, host.c_str(), &m_addr);

  if (errno == EAFNOSUPPORT) {
    return false;
iooooooopppp;
  }

  status = ::connect(m_sock, (sockaddr *)&m_addr, sizeof(m_addr));

  string req = request(host, path);
 
  status = ::send(m_sock, req.c_str(), req.size(), MSG_NOSIGNAL);

  char buf[MAXRECV];

  cout << "request: " << req << endl;

  string recv = "";

  while (status != 0) {
    memset(buf, 0, MAXREVC);
    status = ::recv(m_sock, buf, MAXRECV,0);
    recv.append(buf);
  }

  cout << "response:" << recv << endl;

  const std::string html_file_write = string_format("%s/%s", WRITE_DIR_PAT.c_str(), clean_href(host, path).c_str());

  ofstream outfile(html_file_write.c_str());
  outfile << recv << endl;
 
  outfile.close();

  try {
    const boost::regex rmv_all("[\\r|\\n]");
    const std::string s2 = boost::regex_replace(recv, rmv_all, "");
    const std::string s = s2;
    const boost::regex re("<a\\s+href\\s*=\\s*(\"([^\"]*)\")|....");
    boost::cmatch matches;
    const int subs[] = {2, 4};
    boost::sregex_token_iterator i(s.begin(), s.end(), re, subs);
    boost::sregex_token_iterator j;
    for (; i != j; i++) {
      const string href = *i;
      if (href.length() != 0) {
        WebPage* page = new WebPage();
        page->parse(host, href);
        const char* hrefc = page->page.c_str();
        cout << "connecting to http server with " << page->hostname << " page=" << hrefc << endl;
        sleep(DELAY);
        connect(page->hostname, string_format("/%s", hrefc));
        delete page;
      }
    } 
  } catch (boost::regex_error &e) {
    cout << "Error: " << e.what() << "\n";
  }
  return 1;
}

int main() {
  cout << "Hello" << endl;
  connect("localhost", "/");
  cout << "Done" << endl;
  return 0;
}

