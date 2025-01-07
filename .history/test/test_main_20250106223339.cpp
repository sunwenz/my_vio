#include <iostream>
#include <glog/logging.h>

int main(){
    google::InitGoogleLogging("log.txt");
    std::cout<< "hello world" << std::endl;
}