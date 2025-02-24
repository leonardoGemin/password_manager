# PasswordManager - v1.0

Questo progetto è un semplice Password Manager che utilizza `SQLite` per la memorizzazione delle credenziali. Il database è protetto con SQLCipher per garantire la sicurezza dei dati sensibili.

Si tratta di un progettino didattico pensato per esercitarsi nell'uso della programmazione ad oggetti in `C++`.


## Funzionalità principali

- Aggiunta di credenziali (sito web, username e password)
- Visualizzazione di tutte le credenziali salvate
- Ricerca di credenziali per sito web
- Modifica della password di un account salvato
- Cambio della master password per la protezione del database

## Requisiti

- `C++11`
- `SQLite3`
- `SQLCipher`

## Installazione

1. Clona il repository:
```bash
$ git clone https://github.com/leonardoGemin/password_manager.git
$ cd password_manager
```

2. Assicurati di avere `SQLite` e `SQLCipher` installati.

3. Compila il progetto:
```bash
$ g++ -std=c++11 -O3 -o provaDB provaDB.cpp -lsqlcipher
```

4. Esegui il programma:
```bash
$ ./provaDB
```

## Uso

Dopo aver avviato il programma, segui le istruzioni nel menu per:

- Aggiungere nuove credenziali
- Mostrare tutte le credenziali salvate
- Cercare credenziali specifiche
- Aggiornare password
- Cambiare la master password

## Sicurezza

Tutte le credenziali sono archiviate in un database `SQLite` cifrato con `SQLCipher`.

La master password è necessaria per accedere ai dati.

Il database può essere riassegnato con una nuova master password.

## Prossime funzionalità

Ecco alcune funzionalità pianificate per le future versioni del Password Manager:

- Integrazione con un'interfaccia grafica
- Supporto per generazione automatica di password sicure
- Esportazione e importazione delle credenziali
- Implementazione di un sistema di autenticazione a due fattori