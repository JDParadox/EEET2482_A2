#include "Guest.h"

Guest::Guest() : Account() {
}

Guest::Guest(string id, string name, string address, string phone) : Account(id, name, address, phone, "guest") {
}

Guest::Guest(string id, string name, string address, string phone, int numRented, int numReturned) : Account(id, name, address, phone, numRented, numReturned, "guest") {
}