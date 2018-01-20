#pragma once
#include<iostream>

namespace patterns
{
	const int MAX_OPTIONS_FOR_ANALYST = 5;
	const std::string optionsForAnalist[5] =
	{
		"[1] Pregled za odredjenog kupca",
		"[2] Pregled za odredjeni proizvod",
		"[3] Pregled za odredjeni mjesec",
		"[0] Odjava",
		"[-1] Izlaz iz programa"
	};
	const int MAX_OPTIONS_FOR_ADMIN = 8;
	const std::string optionsForAdmin[8] =
	{
		"[1] Dodaj odredjeni nalog",
		"[2] Obrisi odredjeni nalog",
		"[3] Ispisi naloge na sistemu",
		"[4] Izmjeni odredjeni nalog",
		"[5] Promjena korisnickog interfejsa",
		"[6] Pregled valute sistema",
		"[0] Odjava",
		"[-1] Izlaz iz programa"
	};
}
