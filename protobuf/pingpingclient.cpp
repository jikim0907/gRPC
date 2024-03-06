#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>

#include <grpc/grpc.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/grpcpp.h>

#include "pingpong.grpc.pb.h"
#include "pingpong.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Channel;
using grpc::ClientContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;

using helloworld::Ping;
using helloworld::PingPongService;
using helloworld::Pong;

class PingPongClient{
    public:
        PingPongClient(std::shared_ptr<Channel> channel) : stub_(PingPongService::NewStub(channel)){}

        bool pingpong(const int& pci_phycellid){
            Ping request;
            request.set_count(1);

            Pong reply;

            ClientContext context;

            Status status = stub_->pingpong(&context, request, &reply);
            std::cout << "received :: " << reply <<std::endl;
            std::cout << "received :: " << status.code << std::endl;
            if(status.ok()){
                std::cout << "::: 111 :::" << std::endl;
                return reply.count();
            } else {
                std::cout << "::: 222 :::" << std::endl;
                std::cout << status.error_code() << ":" << status.errror_message() << std::endl;
                return false;
            }

            std::cout << "::: 333 :::" <<std::endl;
            return true;
        }

    private:
        std::unique_ptr<PingPongService::Stub> stub_;

};

int main(int argc, char** argv){
    PingPongClient pcicli(grpc::CreateChannel("0.0.0.0:50051",grpc::InsecureChannelCredentials()));
    bool reply = pcicli.pingpong(32);
    std::cout << "Greeter received : " << reply <<std::endl;
    return 0;
}
