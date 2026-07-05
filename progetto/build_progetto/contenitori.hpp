#pragma once
#include <queue>
#include <stack>
#include <iostream>

//FIFO
class fifo{
private:
	std::queue<int> q; 
public:
	fifo() = default;
	//put
	void put(int valore) { 
		q.push(valore); 
	}   
		
	//estrae l'elemento in testa alla coda
	int get() {
		if (q.empty()) {
			std::cerr << "Errore: tentativo di estrazine da coda vuota " << std::endl;
			exit(1); 
		}
		int valore = q.front(); 
		q.pop(); 
		return valore;
	}
		
	bool empty() const {
		return q.empty();
	}
};

//LIFO
class lifo{
private:
	std::stack<int> s; 
public:
	lifo() = default;
	//put
	void put(int valore) { 
		s.push(valore); 
	}   //inserisce un elemento in cima allo stack
		
	//estrae l'elemento sulla cima dello stack
	int get() {
		if (s.empty()) {
			std::cerr << "Errore: tentativo di estrazione da stack vuoto" << std::endl;
			exit(1);
		}
		int valore = s.top(); //ricorda l'ultimo elemento aggiunto
		s.pop(); 
		return valore;
	}
		
	bool empty() const {
		return s.empty();
	}
};
