#include<iostream>
#include<algorithm>
#include<cmath>

int main()
{
	static const int N = 7;
	double arr[N] = {13.2, 3.2, 4.5, 1.1, 6.3, 2.7, 3.3};
	double minimo, massimo, somma, media, somma_scarti, dev_st;
	
	minimo = arr[0];
	for(int i = 1; i < N; i++)
	{
		minimo = std::min(minimo, arr[i]);
	}
	std::cout<<"Il minimo e' "<<minimo<<"\n";
	
	massimo = arr[0];
	for(int i = 1; i< N; i++)
	{
		massimo = std::max(massimo,arr[i]);
	}
	std::cout<<"Il massimo e' "<<massimo<<"\n";
	
	somma = 0;
	for(int i = 0;i < N; i++)
	{
		somma += arr[i];
	}
	media = somma/N;
	std::cout<<"La media e' "<<media<<"\n";
	
	somma_scarti = 0;
	for(int i = 0; i < N; i++)
	{
		somma_scarti += pow(arr[i]-media, 2);
	}
	dev_st = std::sqrt(somma_scarti/(N-1));
	std::cout<<"La deviazione standard e' "<<dev_st<<"\n";
	
	return 0;
}