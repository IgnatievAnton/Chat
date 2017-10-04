#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>


using namespace std;
int main()
{
    int sock, listener;
    int nclient = 0;
    struct sockaddr_in addr;
    char buf[1024];
    int bytes_read;


    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        cout << "Socket initialization ERROR!!!" << endl;
        return 0;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        cout << "Socket bind ERROR!!!" << endl;
        return 0;
    }

    if(listen(listener, 20))
    {
        cout << "Socket listener ERROR!!!"<<endl;
        return 0;
    }

    while(1)
    {
        sock = accept(listener, NULL, NULL);
        nclient++;
        if(sock < 0)
        {
            return 0;
        }
        while(1)
        {
            bytes_read = recv(sock, buf, 1024, 0);
            if(bytes_read <= 0) break;
            send(sock, buf, bytes_read, 0);
        }


        close(sock);
    }

    return 0;
}
