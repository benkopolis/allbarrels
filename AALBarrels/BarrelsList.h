/*
 * BarrelsList.h
 *
 *  Created on: 2009-05-03
 *      Author: zby
 */

#ifndef BARRELSLIST_H_
#define BARRELSLIST_H_

#include "Barrel.h"


namespace AALBarrels
{

class BarrelsList
{
public:
	BarrelsList();
	explicit BarrelsList(const BarrelsList& another);

	virtual ~BarrelsList();

	/**
	 * @brief dodaje beczke na koncu listy, zwraca wskaznik do dodanej
	 * @param aNew - wzorzec z ktorego pobierane sa dane do nowo dodawanej beczki
	 * @return wskaznik na nowo dodana beczke
	 */
	Barrel* addOnEnd(const Barrel *aNew);

	/**
	 * @brief dodaje beczke na poczatku listy, zwraca wskaznik do dodanej
	 * @param aNew - wzorzec z ktorego pobierane sa dane do nowo dodawanej beczki
	 * @return  wskaznik na nowo dodana beczke
	 */
	Barrel* addOnStart(const Barrel *aNew);

	/**
	 * @brief przesuwa 3 kolejne beczki na koniec listy, poczynajac od podanej
	 * @param first - wskaznik do pierwszej przesuwanej beczki
	 * @return wskaznik do pierwszej beczki ktora "stoczy" sie do przodu
	 */
	Barrel* putTrioAtEnd(Barrel* first);

	/**
	 * @brief zwraca aktualny element
	 * @return wskaznik do aktualnego elementu
	 * NIE ROZNI SIE OD METODY current() const;
	 */
	Barrel* getCurrent() const;

	/**
	 * @brief przesuwa wskaznik aktualnego elementu o 1 w strone end'a
	 * @return wskaznik do nowego aktualnego elementu
	 * nie mozna przesunac za _end (assert(0))
	 */
	Barrel* shiftCurrentForward();

	/**
	 * @brief przesuwa wskaznik aktualnego elementu o 1 w strone start
	 * @return wskaznik do nowego aktualnego elementu
	 * nie mozna przesunac przez _start (assert(0))
	 */
	Barrel* shiftCurrentBackward();

	/**
	 * @brief ustawia wskaznik do aktualnego elementu na poczatku listy
	 * @return wskaznik do nowego aktualnego elementu
	 */
	Barrel* setCurrentAtStart();

	/**
	 * @brief ustawia wskaznik do aktualnego elementu na koniec listy
	 * @return wskaznik do nowego aktualnego elementu
	 */
	Barrel* setCurrenAtEnd();

	/**
	 * @brief usuwa wskazany element
	 * @param t - wskaznik na element ktory chcemy usunac
	 * @return wksaznik na element za usuwanym
	 * nie mozna usunac _enda (assert(0))
	 * jak wskazywalo na _current, to wykonywane jest Barrel* shiftCurrentForward();
	 * i zwracany wskaznik to tak naprawde _current
	 */
	Barrel* erase(Barrel *t);

	/**
	 * @brief usuwa wskazany zakres elementow
	 * @param f - wskazuje na poczatek usuwanego zakresu
	 * @param t - wskazuje na koniec usuwanego zakresu
	 * @return - zwraca t - bo usuwamy bez ostatniego elementu zakresu
	 * jak wskazywalo na _current, to _current jest ustawiany na t
	 * jak zakres jest niepoprawnie podany TO NIE GWARANTUJE DALSZEGO POPRAWNEGO
	 * DZIALANIA PRGORAMU
	 */
	Barrel* erase(Barrel *f, Barrel *t);

	/**
	 * @brief usuwa wszystkie elementy z listy i zwraca enda
	 * @return wskaznik na _end - czyli koncowego wartownika
	 * Usuwa wszystko, poczym _current ustawia na _end i _start ustawia na end.
	 */
	Barrel* clear();

	/**
	 * @brief zwraca wskaznik do ostatniego elementu
	 * @return wskaznik na _end
	 */
	Barrel* end() const;

	/**
	 * @brief zwraca wskaznik do pierwszego elementu
	 * @return wskaznik na _start
	 */
	Barrel* start() const;

	/**
	 * @brief zwraca wskaznik do aktualnego elementu
	 * @return wskaznik na _current
	 */
	Barrel* current() const;

	/**
	 * @brief pobiera rozmiar listy
	 * @return ilosc elementow w liscie (bez _end)
	 */
    unsigned int getSize() const;

    /**
	 * @brief pobiera rozmiar listy
	 * @return ilosc elementow w liscie (bez _end)
	 */
	unsigned int size() const;

private:

	Barrel *_start;

	Barrel *_end;

	Barrel *_current;

	unsigned int _size;
};

};

#endif /* BARRELSLIST_H_ */
