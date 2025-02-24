#ifndef CREDENTIAL_H
	#define CREDENTIAL_H
	
	#include <iostream>
	#include <string>


	class Credential {
		std::string website;
		std::string username;
		std::string password;

		public:
			Credential();
			Credential(const std::string& website, const std::string& username, const std::string& password);
			virtual ~Credential();

			void setWebsite(const std::string& website);
			void setUsername(const std::string& username);
			void setPassword(const std::string& password);
			
			const std::string& getWebsite() const;
			const std::string& getUsername() const;
			const std::string& getPassword() const;
			
			void print() const;
			std::string getString() const;
	};


	Credential::Credential():
		website(""), 
		username(""), 
		password("") {}
	Credential::Credential(const std::string& website, const std::string& username, const std::string& password):
		website(website), 
		username(username), 
		password(password) {}
	Credential::~Credential() = default;


	void Credential::setWebsite(const std::string& website) {
		this->website = website;
	}
	void Credential::setUsername(const std::string& username) {
		this->username = username;
	}
	void Credential::setPassword(const std::string& password) {
		this->password = password;
	}


	const std::string& Credential::getWebsite() const {
		return this->website;
	}
	const std::string& Credential::getUsername() const {
		return this->username;
	}
	const std::string& Credential::getPassword() const {
		return this->password;
	}


	void Credential::print() const {
		std::cout << "  === " << this->website << " ===  \n"
			<< "Username: " << this->username << "\n"
			<< "Password: " << this->password << "\n"
			<< "\n";
	}
	std::string Credential::getString() const {
		return this->website + " " + this->username + " " + this->password + "\n";
	}

#endif