# <C>In-Memory Parking Ticket Database (CSE30)

This project implements an in-memory parking ticket database using a hash table in C.
It supports inserting, deleting, and looking up parking tickets by vehicle plate / state, and summons number.

## 📂 Files
- 'insert_ticket.c'  : Add a ticket to a vehicle using linked list
- 'del_ticket.c'     : Delete a ticket from the linked list of a vehicle
- 'vehicle_lookup.c' : Search for a vehicle in the hash table
- 'free_tickets.c'   : Free up all the dynamically allocated memory

## 🌟 Features
- Hash table with separate chaining using linked list
- Linked List trasversal to resolve memory collision
- Memory Management using 'malloc' and 'free'
- Command-line based structure

## 🛠️ Compile
```bash
gcc -o parking_db insert_ticket.c del_ticket.c vehicle_lookup.c free_tickets.c
```

## 🧑‍💻 Command-Line Options
Once compiled, you can run the program with the following commands :
```bash
./parking -d Tikcets.csv -f Fines.csv [-t size] [-s]

Mandatory Flags
-d Tickets.csv : specifies the name of the csv file where ticket / summons are stored
-f Fines.csv   : specifies the name of the csv file where the fines information are stored

Optional Flags
-t size        : sets the hash table size (usefule when testing)
-s             : suppresses command-line prompts (used for automated test harness)
```



(This project was completed as part of CSE30 : Computer Organization and Systems Programming at UC San Diego)
