#ifndef PASSWORDMANAGER_H
	#define PASSWORDMANAGER_H
	
	#include <fstream>
	#include <string>
	#include <sstream>
	#include <vector>
	#include "Credential.h"


	class PasswordManager {
		std::vector<Credential> credentials;
		const std::string filename;
		const std::string masterPassword;
	
		public:
			PasswordManager(const std::string& filename, const std::string& masterPassword);
			virtual ~PasswordManager();

			void addCredential(const std::string& website, const std::string& username, const std::string& password);
			void showAll();
			void findCredential(const std::string& website);
		
		private:
			std::string encryptDecrypt(const std::string& data, char key = 'K') {
				std::string result = data;
				for (char& c : result) {
					c ^= key;
				}
				return result;
			}
	};


	PasswordManager::PasswordManager(const std::string& filename, const std::string& masterPassword): filename(filename), masterPassword(masterPassword) {
		std::ifstream file(this->filename);
		if (!file) {
			std::cerr << "Errore: impossibile aprire " << filename << ".\n";
			return;
		}

		std::string encryptedData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        std::string decryptedData = encryptDecrypt(encryptedData, this->masterPassword[0]);

		std::istringstream iss(decryptedData);
		std::string website, username, password;
		while (iss >> website >> username >> password) {
			this->credentials.push_back(Credential(website, username, password));
		}
	}
	PasswordManager::~PasswordManager() {
		std::ofstream file(this->filename, std::ios::trunc);
		if (!file) {
			std::cerr << "Errore: impossibile scrivere su " << filename << ".\n";
			return;
		}

        std::string data;
        for (const auto& credential : credentials) {
            data += credential.getString();
        }

        std::string encryptedData = encryptDecrypt(data, this->masterPassword[0]);
        file << encryptedData;
        file.close();
	}


	void PasswordManager::addCredential(const std::string& website, const std::string& username, const std::string& password) {
		this->credentials.push_back(Credential(website, username, password));
	}
	void PasswordManager::showAll() {
		for (const auto& credential : this->credentials) {
			credential.print();
		}
	}
	void PasswordManager::findCredential(const std::string& website) {
		for (const auto& credential : this->credentials) {
			if (credential.getWebsite() == website) {
				credential.print();
				return;
			}
		}
		std::cout << "Nessuna credenziale trovata per " << website << ".\n";
	}

#endif