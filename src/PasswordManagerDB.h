#ifndef PASSWORDMANAGERDB_H
	#define PASSWORDMANAGERDB_H
	
	#include <iostream>
	#include <sqlite3.h>
	#include <string>
	#include "Credential.h"


	class PasswordManager {
		sqlite3* db;
		std::string dbFilename;
		std::string masterPassword;
	
		public:
			PasswordManager(const std::string& dbFilename, const std::string& masterPassword);
			virtual ~PasswordManager();

			void changeMasterPassword(const std::string& newPassword);

			void addCredential(const Credential& credential);
			Credential findCredential(const std::string& website);
			std::vector<Credential> getAllCredential();
			void showAllCredential();
			void updatePassword(const std::string& website, const std::string& username, const std::string& newPassword);
		
		private:
			static int getAllCredentialCallback(void* data, int argc, char** argv, char** colNames);
			static int findCredentialCallback(void* data, int argc, char** argv, char** colNames);
	};


	PasswordManager::PasswordManager(const std::string& dbFilename, const std::string& masterPassword): dbFilename(dbFilename), masterPassword(masterPassword) {
		if (sqlite3_open(this->dbFilename.c_str(), &this->db) != SQLITE_OK) {
			std::cerr << "SQLite3 error on opening database: " << sqlite3_errmsg(this->db) << "\n";
			exit(1);
		}
		std::cerr << "SQLite3 database opened successfully!\n";


		std::string pragma = "PRAGMA key = '" + this->masterPassword + "';";
		if (sqlite3_exec(this->db, pragma.c_str(), NULL, NULL, NULL) != SQLITE_OK) {
			std::cerr << "SQLCipher error setting encryption key: " << sqlite3_errmsg(this->db) << "\n";
			exit(1);
		}
		std::cerr << "SQLCipher encrypted successfully!\n";

		
		char* errMsg;
		std::string sql = "CREATE TABLE IF NOT EXISTS credentials ("
							"id INTEGER PRIMARY KEY, "
							"website TEXT NOT NULL, "
							"username TEXT NOT NULL, "
							"password TEXT NOT NULL "
						  ");";

		if (sqlite3_exec(this->db, sql.c_str(), NULL, 0, &errMsg) != SQLITE_OK) {
			std::cerr << "SQLite3 error on creating table: " << errMsg << "\n";
			sqlite3_free(errMsg);
		} else
			std::cerr << "SQLite3 table created successfully!\n";
	}
	PasswordManager::~PasswordManager() {
		sqlite3_close(this->db);
	}


	void PasswordManager::changeMasterPassword(const std::string& newPassword) {
		std::string pragma = "PRAGMA rekey = '" + newPassword + "';";
		if (sqlite3_exec(this->db, pragma.c_str(), NULL, NULL, NULL) != SQLITE_OK) {
			std::cerr << "SQLCipher error changing encryption key: " << sqlite3_errmsg(this->db) << "\n";
			exit(1);
		}
		std::cerr << "Database encryption key changed successfully!\n";
		this->masterPassword = newPassword;
	}
	

	void PasswordManager::addCredential(const Credential& credential) {
		char* errMsg;
		std::string sql = "INSERT INTO credentials (website, username, password) "
							"VALUES ('" + credential.getWebsite() + "', '" + credential.getUsername() + "', '" + credential.getPassword() + "');";
		
		if (sqlite3_exec(this->db, sql.c_str(), NULL, 0, &errMsg) != SQLITE_OK) {
			std::cerr << "SQLite3 error on inserting new item: " << errMsg << "\n";
			sqlite3_free(errMsg);
		} else 
			std::cerr << "SQLite3 new item inserted successfully!\n";
	}
	Credential PasswordManager::findCredential(const std::string& website) {
		Credential credential = Credential();
		std::string sql = "SELECT * FROM credentials WHERE website = '" + website + "';";
		sqlite3_exec(this->db, sql.c_str(), findCredentialCallback, &credential, NULL);
		return credential;
	}
	std::vector<Credential> PasswordManager::getAllCredential() {
		std::vector<Credential> credentials;
		std::string sql = "SELECT * FROM credentials;";
		sqlite3_exec(this->db, sql.c_str(), getAllCredentialCallback, &credentials, NULL);
		return credentials;
	}
	void PasswordManager::showAllCredential() {
		std::vector<Credential> credentials = this->getAllCredential();
		for (const auto& credential : credentials)
			credential.print();
	}
	void PasswordManager::updatePassword(const std::string& website, const std::string& username, const std::string& newPassword) {
		char* errMsg;
		std::string sql = "UPDATE credentials "
							"SET password = '" + newPassword + "' "
							"WHERE website = '" + website + "' AND username = '" + username + "';";
		
		if (sqlite3_exec(this->db, sql.c_str(), NULL, 0, &errMsg) != SQLITE_OK) {
			std::cerr << "SQLite3 error on updating record: " << errMsg << "\n";
			sqlite3_free(errMsg);
		} else 
			std::cerr << "SQLite3 record updated successfully!\n";
	}


	int PasswordManager::findCredentialCallback(void* data, int argc, char** argv, char** colNames) {
		if (argc != 4) {
			std::cerr << "SQLite3 error on data retrieval.\n";
			return -1;
		}

		Credential* credential = static_cast<Credential*>(data);
		*credential = Credential(argv[1], argv[2], argv[3]);

		return 0;
	}
	int PasswordManager::getAllCredentialCallback(void* data, int argc, char** argv, char** colNames) {
		if (argc != 4) {
			std::cerr << "SQLite3 error on data retrieval.\n";
			return -1;
		}

		std::vector<Credential>* credentials = static_cast<std::vector<Credential>*>(data);
		credentials->push_back(Credential(argv[1], argv[2], argv[3]));
		
		return 0;
	}

#endif