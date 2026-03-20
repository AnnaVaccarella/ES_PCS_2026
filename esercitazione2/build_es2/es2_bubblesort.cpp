#include<iostream>

int main()
{
	static const int N = 7;
	double arr[N] = {13.2, 3.2, 4.5, 1.1, 6.3, 2.7, 3.3};
	double temp;
	int scambi;
	
	std::cout<<"arr: ";
	for(int i = 0; i<N; i++)
	{
		std::cout<<arr[i]<< " ";
	}
	std::cout<<"\n";
	
	do
	{
		scambi = 0;
		for(int i = 0; i<N-1; i++)
		{
			if (arr[i]>arr[i+1])
			{
				temp = arr[i];
				arr[i]=arr[i+1];
				arr[i+1]=temp;
				scambi++;
			}
		}
	}
	while(scambi > 0);
	
	std::cout<<"arr: ";
	for(int i = 0; i<N; i++)
	{
		std::cout<<arr[i]<< " ";
	}
	std::cout<<"\n";
	
	return 0;
}