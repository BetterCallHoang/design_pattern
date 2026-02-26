#include <iostream>
#include <string>

// ===== Subject =====
class IRemoteService { // [Subject]
public:
    virtual ~IRemoteService() = default;
    virtual void request() = 0;
};

// ===== RealSubject (Server side) =====
class RemoteService : public IRemoteService { // [RealSubject]
public:
    void request() override {
        std::cout << "Real service executed\n";
    }
};

// ===== Proxy (Client side stub) =====
class RemoteProxy : public IRemoteService { // [Proxy]
public:
    void request() override {
        std::cout << "Sending request over network...\n";
        std::cout << "Receiving response...\n";
    }
};

int main() { // [Client]
    IRemoteService* service = new RemoteProxy();
    service->request();
    delete service;
}