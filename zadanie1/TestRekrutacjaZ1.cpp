// TestRekrutacjaZ1.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include<iostream>
#include<thread>
#include<fstream>
#include<string>

float arytmetyczna;
float mediana;
int dane1[10000];
int dane2[10000];
int ile;

using namespace std;

void sortowanko(int *dane, int n)
{
	int bufor;
	for (int i = 1; i < n; i++)
	{
		for (int j = n - 1; j >= 1; j--)
		{
			if (dane[j - 1] > dane[j])
			{
				bufor = dane[j-1];
				dane[j-1] = dane[j];
				dane[j] = bufor;
			}
		}
	}

}

void threadFn1()
{
	int suma=0;
	for (int i = 0; i < ile; i++)
		suma += dane1[i];
	arytmetyczna = suma / ile;
	cout << "ukonczono watek 1. Srednia arytmetyczna wynosi: " << arytmetyczna << endl;
}

void threadFn2()
{
	int dzielenie = ile % 2;
	if(dzielenie==0)
	mediana = (dane2[(ile / 2)-1] + dane2[(ile / 2)]) / 2;
	else
	{
		mediana = dane2[((ile+1) / 2)];
	}
	cout << "ukonczono watek 2. Mediana wynosi: " << mediana << endl;
}

int main()
{
	string line_;
	int dane_wejsciowe[10000];
	int i = 0;
	ifstream file_("dane.txt");
	if (file_.is_open())
	{
		while (getline(file_, line_))
		{
			dane_wejsciowe[i] = stoi(line_);
			//cout << dane_wejsciowe[i] << endl;
			i++;
			if (i == 10000)
				break;
	
		}
		file_.close();
	}
	else
	{
		cout << "file is not open" << endl;
	}
	



	sortowanko(dane_wejsciowe,10000);
	
	
	cout << "skonczylem sortowac" << endl;
	//przepisywanie do zmiennych globalnych
	for (int i = 0; i < 10000; i++)
	{
		dane1[i] = dane_wejsciowe[i];
	}
	for (int i = 0; i < 10000; i++)
	{
		dane2[i] = dane_wejsciowe[i];
	}

	// okreslenie liczby elementow
	ile = 10000;
	
	thread t1(threadFn1);
	thread t2(threadFn2);

	thread::id id1 = t1.get_id();
	thread::id id2 = t2.get_id();

	if (t1.joinable())
	{
		t1.join();
		cout << "t1 id=" << id1 << endl;
	}

	if (t2.joinable())
	{
		t2.join();
		cout << "t2 id=" << id2 << endl;
	}

	if (mediana < arytmetyczna)
	{
		cout << "Wartosc mediany jest mniejsza od wartosci sredniej arytmetycznej" << endl;
	}
	else if (mediana > arytmetyczna)
	{
		cout << "Wartosc mediany jest wieksza od wartosci sredniej arytmetycznej" << endl;
	}
	else if (mediana == arytmetyczna)
	{
		cout << "Wartosc mediany jest rowna wartosci sredniej arytmetycznej" << endl;
	}
	/*
	for (int i = 0; i < 10000; i++)
	{
		cout << dane_wejsciowe[i] << endl;
	}
	*/
	
	return 0;
}