// g++ -std=c++11 -O3 -o provaDB provaDB.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -lsqlcipher

#include <iostream>
#include <string>
#include "src/PasswordManagerDB.h"


int main(int argc, char* argv[]) {
	std::string dbFilename, masterPassword;
	std::cout << "Selezionare database: "; std::cin >> dbFilename;
	std::cout << "Inserire MASTER PASSWORD: "; std::cin >> masterPassword;
	PasswordManager manager = PasswordManager(dbFilename, masterPassword);

	int choice;
	do {
		std::cout << "\n\nPassword Manager";
		std::cout << "\n1. Aggiungi credenziale";
		std::cout << "\n2. Mostra tutte le credenziali";
		std::cout << "\n3. Cerca credenziale";
		std::cout << "\n4. Modifica password";
		std::cout << "\n5. Modifica MASTER PASSWORD";
		std::cout << "\n6. Esci";
		std::cout << "\nScegli un'opzione: ";
		std::cin >> choice;

		std::string website, username, password;
		switch (choice) {
			case 1:
				std::cout << "Sito: "; std::cin >> website;
				std::cout << "Username: "; std::cin >> username;
				std::cout << "Password: "; std::cin >> password;
				manager.addCredential(Credential(website, username, password));
				break;
			case 2:
				manager.showAllCredential();
				break;
			case 3:
				std::cout << "Inserisci il sito da cercare: "; std::cin >> website;
				manager.findCredential(website);
				break;
			case 4:
				std::cout << "Sito: "; std::cin >> website;
				std::cout << "Username: "; std::cin >> username;
				std::cout << "Nuova Password: "; std::cin >> password;
				manager.updatePassword(website, username, password);
				break;
			case 5:
				std::cout << "Inserire nuova password: "; std::cin >> password;
				manager.changeMasterPassword(password);
				break;
			case 6:
				std::cout << "Uscita..." << std::endl;
				break;
			default:
				std::cout << "Scelta non valida!" << std::endl;
		}
	} while (choice != 6);

	return 0;
}
