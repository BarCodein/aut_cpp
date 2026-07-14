#ifndef SERVER_H
#define SERVER_H
#include<map>
#include<memory>
#include"client.h"
#include<random>
#include<sstream>
#include<iostream>
#include<regex>

class Client;
class Server
{
public:
	Server();
	std::shared_ptr<Client> add_client(std::string id);
	std::shared_ptr<Client> get_client(std::string id) const;
	double get_wallet(std::string id) const;
	static bool parse_trx(std::string trx, std::string& sender, 
        std::string& receiver, double& value);
	bool add_pending_trx(std::string trx, std::string signature) const;
	size_t mine();
	void action(std::string trx);
private:
	std::map<std::shared_ptr<Client>, double> clients;
};

void show_wallets(Server s);
#endif //SERVER_H