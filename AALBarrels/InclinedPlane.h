/*
 * InclinedPlane.h
 *
 *  Created on: 2009-03-13
 *      Author: zby
 */

#ifndef INCLINEDPLANE_H_
#define INCLINEDPLANE_H_

#include <iostream>
#include <fstream>

#include "BarrelsList.h"
#include "Barrel.h"

using namespace std;


namespace AALBarrels
{

/**
 * Klasa reprezentujaca rownie pochyla, trzyma liste kolorowych beczulek
 * Obiekt do posortowania ma do wyboru kilka rodzajow f. sortujacych
 */
class InclinedPlane
{
public:

	/**
	 * 				PUBLIC STRUCTURS AND ENUMS DECLARATIONS
	 */


	enum SortType
	{
		SimpleSort, IntelligentSort, MarkingSort
	};

	/**
	 * 				PUBLIC CONSTRUCTORS AND DESTRUCTORS DECLARATIONS
	 */

	InclinedPlane();
	virtual ~InclinedPlane();

	/**
	 * 				PUBLIC METHODS DECLARATIONS
	 */

	/**
	 * dodaje podana beczke do listy beczek, jednoczesnie zlicza dodane beczki o danych
	 * kolorach
	 */
	Barrel* addBarrel(Barrel* b);

	/**
	 * dodaje size beczek do listy beczek
	 */
	void addBarrel(Barrel** b, int size);

	/**
	 * drukuje kolorowy ciag beczek.
	 */
	void printBarrels() const;

	/**
	 * drukuje beczki na podany strumien
	 */
	void printBarrelsToStream(ostream &f) const;

	/**
	 * drukuje beczki na podany strumien, w miejsce index wstawia ||
	 */
	void printBarrelsToStream(ostream &f, int index) const;

	/**
	 * drukuje kolorowy ciag beczek wstawiajac || w miejsce skad zostaly zabarane
	 * beczki - int index @param
	 */
	void printBarrels(int index) const;

	/**
	 * uruchamia odpowiednie sortowanie - trzeba podac typ
	 */
	void startSort(SortType s); // TODO czy to potrzebne mi jest?

	/**
	 * statyczna metoda losujaca rodzaje beczek
	 * zwraca tabele o podanej wielkosci
	 */
	static Barrel** generateBarrels(int size);

	/**
	 * Z podanego strumienia czytana jest linijka i na jej podstawie
	 * tworzona jest tablica wskaznikow na beczki.
	 */
	static Barrel** readLineOfBarrels(ifstream *f);

	/**
	 * Z podanej tablicy charow tworzy tablice wskaznikow na beczki.
	 * Tablica charow musi konczyc sie znakiem konca tekstu.
	 */
	static Barrel** convertStringToBarrels(const char *str);

	/**
	 * metoda czyszczaca rownie z beczek
	 */
	void clear();

	/**
	 * Funkcja uruchamia strumien logowania
	 */
	void makeLogs(std::ostream &a);

	/**
	 * funkcja zatrzymuje strumien logowania
	 */
	void stopLogs();

private:

	/**
	 * 					PRIVATE FIELDS DECLARATIONS
	 */

	BarrelsList list;

	int quantityOfGreen;
	int quantityOfBlue;
	int quantityOfRed;

	ostream *log;

private:
	/**
	 * 					PRIVATE METHOD DECLARATIONS
	 */

	/**
	 * Dostaje w parametrze iterator do pozycji na ktorej powinna byc beczka i kolor tej beczki.
	 * Szuka najblizszej takiej beczki i zwraca iterator do niej oraz jej odleglosc od miejsca
	 * w ktorym powinna sie znalezc. Jak odleglosc % 3 == 0, to powinno sie przeniesc ka razy trojki
	 * beczek przed nia, jak nie to trzeba sie zastanowic
	 */
	std::pair<Barrel*, int> findRight(Barrel::Color e, Barrel* ii);

	/**
	 * from - iterator do pierwszej beczki jaka ma byc przeniesiona
	 * to - iterator do beczki ktora ma pojawic sie na miejscu from.
	 * k - odleglosc beczki dobrej od dobrej pozycji
	 * i - odleglosc dobrej pozycji od poczatku listy
	 * Funkcja uwzglednia, ze beczki sa w zlej odleglosci i poprawia ich uklad.
	 */
	Barrel* moveTrios(Barrel* from, Barrel* to, int k, int i);

	/**
	 * Znajduje pierwsza niepasujaca beczke, przenosi ja razem z dwiema za/przed nia
	 * (okresla po analizie) na koniec - jezeli za przeniesionymi byly dobre beczkie
	 * to przesuwa iterator dalej, jezeli nie to znowu przenosi po analizie - robi tak
	 * doputy dopuki przesuwany iterator nie osiagnie konca listy.
	 */
	void simpleSort();

	/**
	 * Wszystkie beczki danego rodzaju ustawia w pozycji 3*n od pozycji, w ktorej
	 * powinny byc, poczynajac od czerwonych, korzysta z pomocniczych struktur:
	 * tablicy intow pamietajacej pozycje i skewencje beczek okreslonych kolorow,
	 * konczy gdy ustawi wszystkie zielone beczki w zadanej pozycji.
	 */
	void intelligentSort();

	/**
	 * Pzechodzi caly ciag beczek i po drodze wybiera te najlepsze do przeniesiani,
	 * dajac im okreslone priorytety przeniesienia, przenosi i znowu przechodzi,
	 * robi tak dopuki lista beczek do przeniesienia nie jest pusta.
	 */
	void markingSort();

	/**
	 * Podana beczke i dwie beczki za nia przenosi na koniec, zwraca iterator do
	 * beczki, ktora znajduje sie za ostania przenoszoona beczka.
	 */
	Barrel* swapTrioBehind(Barrel* first);

	/**
	 * Podana beczke i dwie beczki przed nia przenosi na koniec, zwraca iterator do
	 * beczki, ktora znajduje sie za ostatnia przenoszona beczka.
	 */
	Barrel* swapTrioBefore(Barrel* last);


};


}

#endif /* INCLINEDPLANE_H_ */
