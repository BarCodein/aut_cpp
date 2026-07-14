#include "client.h"

Client::Client(std::string id, const Server& server):id(id),server(&server){
    std::string publicK{},privateK{};
    crypto::generate_key(publicK,privateK);
    public_key = publicK;
    private_key = privateK;
}

std::string Client::get_id()const{
    return id;
}

std::string Client::get_publickey()const{
    return public_key;
}

double Client::get_wallet()const{
    return server->get_wallet(id);
}

std::string Client::sign(std::string txt)const{
    std::string sig = crypto::signMessage(private_key,txt);
    return sig;
}

bool Client::transfer_money(std::string receiver, double value)const{
    double deposit = get_wallet();
    if (value>=deposit)
        return false;
    auto ptr = server->get_client(receiver);
    if (ptr==nullptr)
        return false;
    std::string trs = id;
    trs=trs+"-"+receiver+"-"+std::to_string(value);
    std::string sig = sign(trs);
    server->add_pending_trx(trs,sig);
    return true;
}
size_t Client::generate_nonce()const{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0,9999);
    return dist(gen);
}
