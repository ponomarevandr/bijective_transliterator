#include "automata_creator.h"

#include "automata/nondeterministic_automaton.h"
#include "automata/determinizer.h"


void AutomataCreator::run() {
	rules_processor.run();
	Determinizer determinizer_ru_en(rules_processor.getAutomatonRuEn());
	determinizer_ru_en.run();
	automaton_ru_en = determinizer_ru_en.getResult();
	Determinizer determinizer_en_ru(rules_processor.getAutomatonEnRu());
	determinizer_en_ru.run();
	automaton_en_ru = determinizer_en_ru.getResult();
}

DeterministicAutomaton AutomataCreator::getAutomatonRuEn() {
	return std::move(automaton_ru_en);
}

DeterministicAutomaton AutomataCreator::getAutomatonEnRu() {
	return std::move(automaton_en_ru);
}

AutomataCreator::AutomataCreator() {
	rules_processor.addRuleText(L"а <--> a");
	rules_processor.addRuleText(L"б <--> b");
	rules_processor.addRuleText(L"в <--> v");
	rules_processor.addRuleText(L"д <--> d");
	rules_processor.addRuleText(L"з <--> z");
	rules_processor.addRuleText(L"и <--> i");
	rules_processor.addRuleText(L"к <--> k");
	rules_processor.addRuleText(L"л <--> l");
	rules_processor.addRuleText(L"м <--> m");
	rules_processor.addRuleText(L"н <--> n");
	rules_processor.addRuleText(L"о <--> o");
	rules_processor.addRuleText(L"п <--> p");
	rules_processor.addRuleText(L"р <--> r");
	rules_processor.addRuleText(L"с <--> s");
	rules_processor.addRuleText(L"т <--> t");
	rules_processor.addRuleText(L"ф <--> f");
	rules_processor.addRuleText(L"х <--> h");

	rules_processor.addRuleText(L"г <--> g");
	rules_processor.addRuleText(L"ж <--> j");
	rules_processor.addRuleText(L"й <--> y");
	rules_processor.addRuleText(L"ц <--> c");

	rules_processor.addRuleText(L"ч		<--> ch");
	rules_processor.addRuleText(L"цк*x	<--> ck+h");
	rules_processor.addRuleText(L"ш		<--> sh");
	rules_processor.addRuleText(L"ск*х	<--> sk+h");
	rules_processor.addRuleText(L"щ		<--> shch");
	rules_processor.addRuleText(L"шт*ч	<--> sht+ch");

	rules_processor.addRuleText(L"тф	<--> th");
	rules_processor.addRuleText(L"тх	<--> tf");
	rules_processor.addRuleText(L"пф	<--> ph");
	rules_processor.addRuleText(L"пх	<--> pf");

	rules_processor.addRuleText(L"е		<--> e");
	rules_processor.addRuleText(L"э		<--> oe");
	rules_processor.addRuleText(L"ой*е	<--> oy+e");
	rules_processor.addRuleText(L"ю		<--> u");
	rules_processor.addRuleText(L"у		<--> ou");
	rules_processor.addRuleText(L"ой*ю	<--> oy+u");
	rules_processor.addRuleText(L"ё		<--> yo");
	rules_processor.addRuleText(L"йи*о	<--> yi+o");
	rules_processor.addRuleText(L"я		<--> ya");
	rules_processor.addRuleText(L"йи*а	<--> yi+a");

	rules_processor.addRuleText(L"ы		<--> ea");
	rules_processor.addRuleText(L"ех*а	<--> eh+a");
	rules_processor.addRuleText(L"ь		<--> ie");
	rules_processor.addRuleText(L"ий*е	<--> iy+e");
	rules_processor.addRuleText(L"ъ		<--> oa");
	rules_processor.addRuleText(L"ох*а	<--> oh+a");

	rules_processor.addRuleText(L"ув	<--> w");
	rules_processor.addRuleText(L"оуф*в	<--> ouf+v");
	rules_processor.addRuleText(L"къ	<--> q");
	rules_processor.addRuleText(L"кх+ъ	<--> kh*oa");



	rules_processor.addRuleText(L"йи*э		<--> yi*oe");
	rules_processor.addRuleText(L"ёй*е		<--> yoy+e");
	rules_processor.addRuleText(L"йи*ой*е	<--> yi+oy+e");

	rules_processor.addRuleText(L"йи*ъ		<--> yi*oa");
	rules_processor.addRuleText(L"ёх*а		<--> yoh+a");
	rules_processor.addRuleText(L"йи*ох*а	<--> yi+oh+a");

	rules_processor.addRuleText(L"йи*у		<--> yi*ou");
	rules_processor.addRuleText(L"ёй*ю		<--> yoy+u");
	rules_processor.addRuleText(L"йи*ой*ю	<--> yi+oy+u");

	rules_processor.addRuleText(L"ой*ы		<--> oy*ea");
	rules_processor.addRuleText(L"эх*а		<--> oeh+a");
	rules_processor.addRuleText(L"ой*ех*а	<--> oy+eh+a");

	rules_processor.addRuleText(L"ий*ы		<--> iy*ea");
	rules_processor.addRuleText(L"ьх*а		<--> ieh+a");
	rules_processor.addRuleText(L"ий*ех*а	<--> iy+eh+a");

	rules_processor.addRuleText(L"ёй*ы			<--> yoy*ea");
	rules_processor.addRuleText(L"йи*ой*ы		<--> yi+oy*ea");
	rules_processor.addRuleText(L"йи*эх*а		<--> yi*oeh+a");
	rules_processor.addRuleText(L"ёй*ех*а		<--> yoy+eh+a");
	rules_processor.addRuleText(L"йи*ой*ех*а	<--> yi+oy+eh+a");

	rules_processor.addRuleText(L"йи*ув		<--> yi*w");
	rules_processor.addRuleText(L"йи*уф+в	<--> yi*ouf*v");
}