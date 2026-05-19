#pragma once

#include<iostream>
#include<list>
#include "undirected_graph.hpp"

template<typename T>
class coda{
private:
	std::list<T> elementi;

public:
	coda() = default;
	
	void put(const T& valore) {
		elementi.push_back(valore);
	}
	
	T get() {
		T val = elementi.front();
		elementi.pop_front();
		return val;
	}
	
	bool empty()const{
		return elementi.empty();
	}
	
};



template<typename T> 
class pila{
private: 
	std::list<T> elementi;

public:
	pila() = default;
	
	void put(const T& valore) {
		elementi.push_back(valore);
	}
	
	T get() {
		T val = elementi.back();
		elementi.pop_back();
		return val;
		
	}
	
	bool empty()const{
		return elementi.empty();
	}
	
};


