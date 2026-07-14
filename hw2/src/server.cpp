#include"server.h"
extern std::vector<std::string> pending_trxs;
Server::Server(){}

std::shared_ptr<Client> Server::add_client(std::string id){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0,9999);
    if (get_client(id)!=nullptr){
        id+=std::to_string(dist(gen));
    }
    std::shared_ptr<Client> ptr = std::make_shared<Client>(id,*this);
    clients[ptr]=5;
    return ptr;

}

std::shared_ptr<Client> Server::get_client(std::string id) const{
    for (const auto& pair :clients){
        std::shared_ptr<Client> key = pair.first;
        if (key->get_id()==id)
            return key;
    }
    return nullptr;
}

double Server::get_wallet(std::string id) const{
    std::shared_ptr<Client> ptr = get_client(id);
    return clients.at(ptr);
}

bool Server::parse_trx(std::string trx, std::string& sender, 
    std::string& receiver, double& value){
    std::regex pattern(R"(^[a-zA-Z]+-[a-zA-Z]+-\d+(\.\d+)?$)");
    if (!std::regex_match(trx,pattern))
        throw std::runtime_error("not match");
    std::stringstream ss(trx);
    std::getline(ss,sender,'-');
    std::getline(ss,receiver,'-');
    std::string v;
    std::getline(ss,v);
    value = std::stod(v);

    return true;
}
bool Server::add_pending_trx(std::string trx, std::string signature) const{
    std::string sender,reciever,public_key;
    double value;
    parse_trx(trx,sender,reciever,value);
    public_key = get_client(sender)->get_publickey();
    bool authentic = crypto::verifySignature(public_key,trx,signature);
    double deposit = get_wallet(sender);
    if (authentic && deposit>=value)
        pending_trxs.push_back(trx);
    return false;
}

bool ver(std::string s){
    int c = 0;
    for(int i=0;i<10;i++){
        if (s.at(i)!='0')c=0;
        else c++;
        if(c==3)return true;
    }
    return false;
}

void Server::action(std::string trx){
    std::string sender,reciever;
    double value;
    Server::parse_trx(trx,sender,reciever,value);
    clients[get_client(sender)]-=value;
    clients[get_client(reciever)]+=value;
}

size_t Server::mine(){
    std::string mempool;
    for(auto item :pending_trxs)
        mempool+=item;
    bool flag=true;
    int nounce;
    while(flag){
        for(const auto& pairs:clients){
            auto key = pairs.first;
            nounce = key->generate_nonce();
            std::string m = mempool + std::to_string(nounce);
            std::string hash{crypto::sha256(m)};
            if (ver(hash)){
                clients[key]+=6.25;
                flag = false;
                break;
            }
        }
    }
    for(auto trx:pending_trxs)
        action(trx);
    pending_trxs.clear();

    return nounce;
}

void show_wallets(Server s){
    return;
}