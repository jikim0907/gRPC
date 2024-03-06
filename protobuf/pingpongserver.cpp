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

#include "pingpong.grpc.pb.h"
#include "pingpong.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;

using helloworld::Ping;
using helloworld::PingPongService;
using helloworld::Pong;

class Listener final 
: public PingPongService::Service{
    Status pingpong(ServerContext* context, const Ping* ping, Pong* pong) override{
        pong->set_count(12);
        return Status::OK;
    }
};

void Run(){
    std::string server_address("0.0.0.0:50051");
    Listener service;

    grpc::ServerBuilder builder;
    builder.AccListenerPort(server_address, grpc::InsecureSErverCredentials());
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on ... " << server_address << std::endl;
    server-> Wait();
}

int main(int argc, char** argv){
    Run();
    return 0;
}