#include <iostream>
#include <chrono>
#include <fstream>
#include <windows.h>

#include "menu_MST.h"
#include "main_menu.h"
#include "generate.h"
#include "show.h"
#include "load.h"
#include "prim_algorithm.h"
#include "kruskal_algorithm.h"

using namespace std;

Load *load = NULL;
Generate *generate = NULL;
Show *show = NULL;
Prim_Algorithm *prim = NULL;
Kruskal_Algorithm *kruskal = NULL;

void show_menu_MST() {				// wyœwietlanie g³ownego menu
	cout << "-------------------------------------MST-MENU-------------------------------------" << endl;
	cout << "1 - Wczytanie grafu z pliku o zadanej nazwie" << endl;
	cout << "2 - Wygenerowanie losowego grafu" << endl;
	cout << "3 - Wyœwietlenie grafu macierzowo i listowo" << endl;
	cout << "4 - Algorytm Prima" << endl;
	cout << "5 - Algorytm Kruskala" << endl;
	cout << "6 - Cofnij do wyboru g³ownego problemu" << endl;
	cout << "7 - Zakoñcz program" << endl;
	cout << "----------------------------------------------------------------------------------" << endl;
}

void choice_switch_MST() {		// wybór u¿ytkownika na podstawie menu i dalsze operacje
	int choice;
	
	cout << "Podaj wybór: ";
	cin >> choice;
	system("cls");
	
	switch(choice) {
		case 1: {
			load = new Load();
			load->load_graph();
			generate = NULL;
			
			cout << endl;
			show_menu_MST();
			choice_switch_MST();
			break;
		}
		case 2: {
			int g;
			int n;
			
			cout << "Podaj iloœæ wierzcho³ków grafu: ";
			cin >> n; 
			cout << "Podaj gêstoœæ grafu (25, 50, 99 [%]): ";
			cin >> g;
			cout <<endl;
			 
			generate = new Generate(n ,g);
			generate->generate_graph();
			load = NULL;
			
			show_menu_MST();
			choice_switch_MST();
			break;
		}
		case 3: {
			system("cls");
			
			if(generate) {
				show = new Show(generate->getU(), generate->getV(), generate->getWeight(), generate->getN(), generate->getDensityEdges(), generate->getIncidenceMatrix(), generate->get_Adj_List());
				show->show_graph();
			} else if(load) {
				show = new Show(load->getU(), load->getV(), load->getWeight(), load->getN(), load->getEdgesNumber(), load->getIncidenceMatrix(), load->get_Adj_List());
				show->show_graph();
			} else cout << "¯aden graf nie istnieje" << endl;
							
			show_menu_MST();
			choice_switch_MST();
			break;
		}
		case 4: {
			if(generate) {
				LARGE_INTEGER frequency;
				QueryPerformanceFrequency(&frequency);
				
    			LARGE_INTEGER start1;
    			LARGE_INTEGER end1;
    			LARGE_INTEGER start2;
    			LARGE_INTEGER end2;
    			
				cout << "----- ALGORYTM - PRIMA -----" << endl << endl;
				// tworzenie obiektu prim gdy graf zosta³ wygenerowany
				prim = new Prim_Algorithm(generate->getN(), generate->getDensityEdges(), generate->getIncidenceMatrix(), generate->getWeight(), generate->get_Adj_List());
				
					QueryPerformanceCounter(&start1);																		// rozpoczêcie mierzenia czasu
				prim->prim_matrix();
					QueryPerformanceCounter(&end1);																			// zakoñczenie mierzenia czasu
    				double elapsedTime1 = static_cast<double>(end1.QuadPart - start1.QuadPart) / frequency.QuadPart;		// policzenie czasu wykonywania siê algorytmu
    				cout << "Algorytm Prima - macierz incydencji - czas: " << elapsedTime1*1e3 << " ms"<< endl << endl;
    				QueryPerformanceCounter(&start2);
				prim->prim_list();
					QueryPerformanceCounter(&end2);	
    				double elapsedTime2 = static_cast<double>(end2.QuadPart - start2.QuadPart) / frequency.QuadPart;	
    				cout << "Algorytm Prima - lista s¹siedztwa - czas: " << elapsedTime2*1e3 << " ms"<< endl << endl;
			} else if(load) {
				LARGE_INTEGER frequency;
				QueryPerformanceFrequency(&frequency);
				
    			LARGE_INTEGER start1;
    			LARGE_INTEGER end1;
    			LARGE_INTEGER start2;
    			LARGE_INTEGER end2;
    			
				cout << "----- ALGORYTM - PRIMA -----" << endl << endl;
				// tworzenie obiektu prim gdy graf zosta³ wczytany
				prim = new Prim_Algorithm(load->getN(), load->getEdgesNumber(), load->getIncidenceMatrix(), load->getWeight(), load->get_Adj_List());
				
					QueryPerformanceCounter(&start1);																		// rozpoczêcie mierzenia czasu
				prim->prim_matrix();
					QueryPerformanceCounter(&end1);																			// zakoñczenie mierzenia czasu
    				double elapsedTime1 = static_cast<double>(end1.QuadPart - start1.QuadPart) / frequency.QuadPart;		// policzenie czasu wykonywania siê algorytmu
    				cout << "Algorytm Prima - macierz incydencji - czas: " << elapsedTime1*1e3 << " ms"<< endl << endl;
    				QueryPerformanceCounter(&start2);
				prim->prim_list();
					QueryPerformanceCounter(&end2);	
    				double elapsedTime2 = static_cast<double>(end2.QuadPart - start2.QuadPart) / frequency.QuadPart;	
    				cout << "Algorytm Prima - lista s¹siedztwa - czas: " << elapsedTime2*1e3 << " ms"<< endl << endl;
			} else cout << "¯aden graf nie istnieje" << endl;
			
			show_menu_MST();
			choice_switch_MST();
			break;
		}
		case 5: {
			
			if(generate) {
				LARGE_INTEGER frequency;
				QueryPerformanceFrequency(&frequency);
				
    			LARGE_INTEGER start1;
    			LARGE_INTEGER end1;
    			LARGE_INTEGER start2;
    			LARGE_INTEGER end2;
    			
				cout << "----- ALGORYTM - KRUSKALA -----" << endl << endl;
				// tworzenie obiektu kruskal gdy graf zosta³ wygenerowany
				kruskal = new Kruskal_Algorithm(generate->getN(), generate->getDensityEdges(), generate->getIncidenceMatrix(), generate->getWeight(), generate->get_Adj_List());
				
					QueryPerformanceCounter(&start1);																		// rozpoczêcie mierzenia czasu
				kruskal->kruskal_matrix();
					QueryPerformanceCounter(&end1);																			// zakoñczenie mierzenia czasu
    				double elapsedTime1 = static_cast<double>(end1.QuadPart - start1.QuadPart) / frequency.QuadPart;		// policzenie czasu wykonywania siê algorytmu
    				cout << "Algorytm Kruskala - macierz incydencji - czas: " << elapsedTime1*1e3 << " ms"<< endl << endl;
    				QueryPerformanceCounter(&start2);
				kruskal->kruskal_list();
					QueryPerformanceCounter(&end2);	
    				double elapsedTime2 = static_cast<double>(end2.QuadPart - start2.QuadPart) / frequency.QuadPart;	
    				cout << "Algorytm Kruskala - lista s¹siedztwa - czas: " << elapsedTime2*1e3 << " ms"<< endl << endl;
    				
			} else if(load) {
				LARGE_INTEGER frequency;
				QueryPerformanceFrequency(&frequency);
				
    			LARGE_INTEGER start1;
    			LARGE_INTEGER end1;
    			LARGE_INTEGER start2;
    			LARGE_INTEGER end2;
    			
				cout << "----- ALGORYTM - KRUSKALA -----" << endl << endl;
				// tworzenie obiektu kruskal gdy graf zosta³ wczytany
				kruskal = new Kruskal_Algorithm(load->getN(), load->getEdgesNumber(), load->getIncidenceMatrix(), load->getWeight(), load->get_Adj_List());
				
					QueryPerformanceCounter(&start1);																		// rozpoczêcie mierzenia czasu
				kruskal->kruskal_matrix();
					QueryPerformanceCounter(&end1);																			// zakoñczenie mierzenia czasu
    				double elapsedTime1 = static_cast<double>(end1.QuadPart - start1.QuadPart) / frequency.QuadPart;		// policzenie czasu wykonywania siê algorytmu
    				cout << "Algorytm Kruskala - macierz incydencji - czas: " << elapsedTime1*1e3 << " ms"<< endl << endl;
    				QueryPerformanceCounter(&start2);
				kruskal->kruskal_list();
					QueryPerformanceCounter(&end2);	
    				double elapsedTime2 = static_cast<double>(end2.QuadPart - start2.QuadPart) / frequency.QuadPart;	
    				cout << "Algorytm Kruskala - lista s¹siedztwa - czas: " << elapsedTime2*1e3 << " ms"<< endl << endl;
			} else cout << "¯aden graf nie istnieje" << endl;
    		
			show_menu_MST();
			choice_switch_MST();
			break;
		}
		case 6: {
			main_menu();
			break;
		}
		case 7: {
			exit(0);
			break;
		}
		case 8: {										// do pomiarów do sprawozdania
			
			ofstream file1, file2, file3, file4;
			double time1_sum = 0; 
			double time2_sum = 0;
			double time3_sum = 0; 
			double time4_sum = 0;
			file1.open("AAAPrim_macierz.txt", ios::app);
			file2.open("AAAPrim_lista.txt", ios::app);
			file3.open("AAAKruskal_macierz.txt", ios::app);
			file4.open("AAAKruskal_lista.txt", ios::app);
			
			LARGE_INTEGER frequency;
			QueryPerformanceFrequency(&frequency);
				
    		LARGE_INTEGER start1;
    		LARGE_INTEGER end1;
    		LARGE_INTEGER start2;
    		LARGE_INTEGER end2;
    		LARGE_INTEGER start3;
    		LARGE_INTEGER end3;
    		LARGE_INTEGER start4;
    		LARGE_INTEGER end4;
			
			for(int i=0; i<50; i++) {
		
				generate = new Generate(200, 99);
				generate->generate_graph();
				prim = new Prim_Algorithm(generate->getN(), generate->getDensityEdges(), generate->getIncidenceMatrix(), generate->getWeight(), generate->get_Adj_List());
				kruskal = new Kruskal_Algorithm(generate->getN(), generate->getDensityEdges(), generate->getIncidenceMatrix(), generate->getWeight(), generate->get_Adj_List());
	    			
	    			QueryPerformanceCounter(&start1);										// rozpoczêcie mierzenia czasu
				prim->prim_matrix();
					QueryPerformanceCounter(&end1);																			// zakoñczenie mierzenia czasu
    				double elapsedTime1 = static_cast<double>(end1.QuadPart - start1.QuadPart) / frequency.QuadPart;
					elapsedTime1 = elapsedTime1*1e6;
					
	    			QueryPerformanceCounter(&start2);
				prim->prim_list();
					QueryPerformanceCounter(&end2);																			// zakoñczenie mierzenia czasu
    				double elapsedTime2 = static_cast<double>(end2.QuadPart - start2.QuadPart) / frequency.QuadPart;
					elapsedTime2 = elapsedTime2*1e6;
	    			
	    			QueryPerformanceCounter(&start3);									
				kruskal->kruskal_matrix();
					QueryPerformanceCounter(&end3);																			// zakoñczenie mierzenia czasu
    				double elapsedTime3 = static_cast<double>(end3.QuadPart - start3.QuadPart) / frequency.QuadPart;
					elapsedTime3 = elapsedTime3*1e6;
	
	    			QueryPerformanceCounter(&start4);	
				kruskal->kruskal_list();
					QueryPerformanceCounter(&end4);																			// zakoñczenie mierzenia czasu
    				double elapsedTime4 = static_cast<double>(end4.QuadPart - start4.QuadPart) / frequency.QuadPart;
					elapsedTime4 = elapsedTime4*1e6;	
	    			
	    			time1_sum += elapsedTime1;
	    			time2_sum += elapsedTime2;
	    			time3_sum += elapsedTime3;
	    			time4_sum += elapsedTime4;
	    	}
	    	
	    	time1_sum /= 50;
	    	time2_sum /= 50;
	    	time3_sum /= 50;
	    	time4_sum /= 50;
	    	
	    	file1 << time1_sum << endl;
	    	file2 << time2_sum << endl;
	    	file3 << time3_sum << endl;
	    	file4 << time4_sum << endl;
	    	
	    	file1.close();
	    	file2.close();
	    	file3.close();
	    	file4.close();
			
			break;
		}
		default:
			cout << "niepoprawny numer polecenia" << endl << endl;
			
			show_menu_MST();
			choice_switch_MST();		
	}
}
