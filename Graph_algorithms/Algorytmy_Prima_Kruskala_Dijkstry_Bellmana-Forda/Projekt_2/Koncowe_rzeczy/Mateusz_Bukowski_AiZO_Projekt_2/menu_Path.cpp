#include <iostream>
#include <chrono>
#include <fstream>
#include <windows.h>

#include "menu_Path.h"
#include "main_menu.h"
#include "loadP.h"
#include "generateP.h"
#include "showP.h"
#include "dijkstry_algorithm.h"
#include "bellmanFord_algorithm.h"

using namespace std;

LoadP *loadP = NULL;
GenerateP *generateP = NULL;
ShowP *showP = NULL;
Dijkstry_Algorithm *dijkstry = NULL;
BellmanFord_Algorithm *bellmanFord = NULL;

void show_menu_Path() {				// wyœwietlanie g³ownego menu
	cout << "--------------------------------SHORTEST-PATH-MENU--------------------------------" << endl;
	cout << "1 - Wczytanie grafu z pliku o zadanej nazwie" << endl;
	cout << "2 - Wygenerowanie losowego grafu" << endl;
	cout << "3 - Wyœwietlenie grafu macierzowo i listowo" << endl;
	cout << "4 - Algorytm Dijkstry" << endl;
	cout << "5 - Algorytm Bellmana-Forda" << endl;
	cout << "6 - Cofnij do wyboru g³ownego problemu" << endl;
	cout << "7 - Zakoñcz program" << endl;
	cout << "----------------------------------------------------------------------------------" << endl;
}

void choice_switch_Path() {		// wybór u¿ytkownika na podstawie menu i dalsze operacje
	int choice;
	
	cout << "Podaj wybór: ";
	cin >> choice;
	system("cls");
	
	switch(choice) {
		case 1: {
			loadP = new LoadP();
			loadP->load_graph();
			generateP = NULL;
			
			cout << endl;
			show_menu_Path();
			choice_switch_Path();
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
			 
			generateP = new GenerateP(n ,g);
			generateP->generate_graph();
			loadP = NULL;
			
			show_menu_Path();
			choice_switch_Path();
			break;
		}
		case 3: {
			system("cls");
			
			if(generateP) {
				showP = new ShowP(generateP->getU(), generateP->getV(), generateP->getWeight(), generateP->getN(), generateP->getDensityEdges(), generateP->getIncidenceMatrix(), generateP->get_Suc_List());
				showP->show_graph();
			} else if(loadP) {
				showP = new ShowP(loadP->getU(), loadP->getV(), loadP->getWeight(), loadP->getN(), loadP->getEdgesNumber(), loadP->getIncidenceMatrix(), loadP->get_Suc_List());
				showP->show_graph();
			} else cout << "¯aden graf nie istnieje" << endl;
			
			show_menu_Path();
			choice_switch_Path();
			break;
		}
		case 4: {
			int a, b;
			
			if(generateP || loadP) {
				cout << "Podaj wierzcho³ek startowy: ";
				cin >> a;
				cout << "Podaj wierzcho³ek koñcowy: ";
				cin >> b;
				cout << endl;
			}
			
			if(generateP) {
				LARGE_INTEGER frequency;
				QueryPerformanceFrequency(&frequency);
				
    			LARGE_INTEGER start1;
    			LARGE_INTEGER end1;
    			LARGE_INTEGER start2;
    			LARGE_INTEGER end2;
    			
				cout << "----- ALGORYTM - DIJKSTRY -----" << endl << endl;
				// tworzenie obiektu dijkstry gdy graf zosta³ wygenerowany
				dijkstry = new Dijkstry_Algorithm(generateP->getN(), generateP->getDensityEdges(), generateP->getIncidenceMatrix(), generateP->getWeight(), generateP->get_Suc_List(), a, b);
				
					QueryPerformanceCounter(&start1);																		// rozpoczêcie mierzenia czasu
				dijkstry->dijkstry_matrix();
					QueryPerformanceCounter(&end1);																			// zakoñczenie mierzenia czasu
    				double elapsedTime1 = static_cast<double>(end1.QuadPart - start1.QuadPart) / frequency.QuadPart;		// policzenie czasu wykonywania siê algorytmu
    				cout << "Algorytm Dijkstry - macierz incydencji - czas: " << elapsedTime1*1e3 << " ms"<< endl << endl;
    				QueryPerformanceCounter(&start2);
				dijkstry->dijkstry_list();
					QueryPerformanceCounter(&end2);	
    				double elapsedTime2 = static_cast<double>(end2.QuadPart - start2.QuadPart) / frequency.QuadPart;	
    				cout << "Algorytm Dijkstry - lista s¹siedztwa - czas: " << elapsedTime2*1e3 << " ms"<< endl << endl;
			} else if(loadP) {
				LARGE_INTEGER frequency;
				QueryPerformanceFrequency(&frequency);
				
    			LARGE_INTEGER start1;
    			LARGE_INTEGER end1;
    			LARGE_INTEGER start2;
    			LARGE_INTEGER end2;
    			
				cout << "----- ALGORYTM - DIJKSTRY -----" << endl << endl;
				// tworzenie obiektu dijkstry gdy graf zosta³ wczytany
				dijkstry = new Dijkstry_Algorithm(loadP->getN(), loadP->getEdgesNumber(), loadP->getIncidenceMatrix(), loadP->getWeight(), loadP->get_Suc_List(), a, b);
				
					QueryPerformanceCounter(&start1);																		// rozpoczêcie mierzenia czasu
				dijkstry->dijkstry_matrix();
					QueryPerformanceCounter(&end1);																			// zakoñczenie mierzenia czasu
    				double elapsedTime1 = static_cast<double>(end1.QuadPart - start1.QuadPart) / frequency.QuadPart;		// policzenie czasu wykonywania siê algorytmu
    				cout << "Algorytm Dijkstry - macierz incydencji - czas: " << elapsedTime1*1e3 << " ms"<< endl << endl;
    				QueryPerformanceCounter(&start2);
				dijkstry->dijkstry_list();
					QueryPerformanceCounter(&end2);	
    				double elapsedTime2 = static_cast<double>(end2.QuadPart - start2.QuadPart) / frequency.QuadPart;	
    				cout << "Algorytm Dijkstry - lista s¹siedztwa - czas: " << elapsedTime2*1e3 << " ms"<< endl << endl;
			} else cout << "¯aden graf nie istnieje" << endl;
			
			show_menu_Path();
			choice_switch_Path();
			break;
		}
		case 5: {
			int a, b;
			
			if(generateP || loadP) {
				cout << "Podaj wierzcho³ek startowy: ";
				cin >> a;
				cout << "Podaj wierzcho³ek koñcowy: ";
				cin >> b;
				cout << endl;
			}
			
			if(generateP) {
				LARGE_INTEGER frequency;
				QueryPerformanceFrequency(&frequency);
				
    			LARGE_INTEGER start1;
    			LARGE_INTEGER end1;
    			LARGE_INTEGER start2;
    			LARGE_INTEGER end2;
    			
				cout << "----- ALGORYTM - BELLMANA - FORDA -----" << endl << endl;
				// tworzenie obiektu bellmanFord gdy graf zosta³ wygenerowany
				bellmanFord = new BellmanFord_Algorithm(generateP->getN(), generateP->getDensityEdges(), generateP->getIncidenceMatrix(), generateP->getWeight(), generateP->get_Suc_List(), a, b);
				
					QueryPerformanceCounter(&start1);																		// rozpoczêcie mierzenia czasu
				bellmanFord->bellmanFord_matrix();
					QueryPerformanceCounter(&end1);																			// zakoñczenie mierzenia czasu
    				double elapsedTime1 = static_cast<double>(end1.QuadPart - start1.QuadPart) / frequency.QuadPart;		// policzenie czasu wykonywania siê algorytmu
    				cout << "Algorytm Bellmana Forda - macierz incydencji - czas: " << elapsedTime1*1e3 << " ms"<< endl << endl;
    				QueryPerformanceCounter(&start2);
				bellmanFord->bellmanFord_list();
					QueryPerformanceCounter(&end2);	
    				double elapsedTime2 = static_cast<double>(end2.QuadPart - start2.QuadPart) / frequency.QuadPart;	
    				cout << "Algorytm Bellmana Forda - lista s¹siedztwa - czas: " << elapsedTime2*1e3 << " ms"<< endl << endl;
			} else if(loadP) {
				LARGE_INTEGER frequency;
				QueryPerformanceFrequency(&frequency);
				
    			LARGE_INTEGER start1;
    			LARGE_INTEGER end1;
    			LARGE_INTEGER start2;
    			LARGE_INTEGER end2;
    			
				cout << "----- ALGORYTM - BELLMANA - FORDA -----" << endl << endl;
				// tworzenie obiektu bellmanFord gdy graf zosta³ wczytany
				bellmanFord = new BellmanFord_Algorithm(loadP->getN(), loadP->getEdgesNumber(), loadP->getIncidenceMatrix(), loadP->getWeight(), loadP->get_Suc_List(), a, b);
				
					QueryPerformanceCounter(&start1);																		// rozpoczêcie mierzenia czasu
				bellmanFord->bellmanFord_matrix();
					QueryPerformanceCounter(&end1);																			// zakoñczenie mierzenia czasu
    				double elapsedTime1 = static_cast<double>(end1.QuadPart - start1.QuadPart) / frequency.QuadPart;		// policzenie czasu wykonywania siê algorytmu
    				cout << "Algorytm Bellmana Forda - macierz incydencji - czas: " << elapsedTime1*1e3 << " ms"<< endl << endl;
    				QueryPerformanceCounter(&start2);
				bellmanFord->bellmanFord_list();
					QueryPerformanceCounter(&end2);	
    				double elapsedTime2 = static_cast<double>(end2.QuadPart - start2.QuadPart) / frequency.QuadPart;	
    				cout << "Algorytm Bellmana Forda - lista s¹siedztwa - czas: " << elapsedTime2*1e3 << " ms"<< endl << endl;
			} else cout << "¯aden graf nie istnieje" << endl;
			
			show_menu_Path();
			choice_switch_Path();
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
			file1.open("AAADijkstry_macierz.txt", ios::app);
			file2.open("AAADijkstry_lista.txt", ios::app);
			file3.open("AAAFord_macierz.txt", ios::app);
			file4.open("AAAFord_lista.txt", ios::app);
			
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
		
				generateP = new GenerateP(200 ,99);
				generateP->generate_graph();
				dijkstry = new Dijkstry_Algorithm(generateP->getN(), generateP->getDensityEdges(), generateP->getIncidenceMatrix(), generateP->getWeight(), generateP->get_Suc_List(), 0, 9);
				bellmanFord = new BellmanFord_Algorithm(generateP->getN(), generateP->getDensityEdges(), generateP->getIncidenceMatrix(), generateP->getWeight(), generateP->get_Suc_List(), 0, 9);
				
					QueryPerformanceCounter(&start1);										// rozpoczêcie mierzenia czasu
				dijkstry->dijkstry_matrix();
					QueryPerformanceCounter(&end1);																			// zakoñczenie mierzenia czasu
    				double elapsedTime1 = static_cast<double>(end1.QuadPart - start1.QuadPart) / frequency.QuadPart;
					elapsedTime1 = elapsedTime1*1e6;
					
	    			QueryPerformanceCounter(&start2);
				dijkstry->dijkstry_list();
					QueryPerformanceCounter(&end2);																			// zakoñczenie mierzenia czasu
    				double elapsedTime2 = static_cast<double>(end2.QuadPart - start2.QuadPart) / frequency.QuadPart;
					elapsedTime2 = elapsedTime2*1e6;
	    			
	    			QueryPerformanceCounter(&start3);									
				bellmanFord->bellmanFord_matrix();
					QueryPerformanceCounter(&end3);																			// zakoñczenie mierzenia czasu
    				double elapsedTime3 = static_cast<double>(end3.QuadPart - start3.QuadPart) / frequency.QuadPart;
					elapsedTime3 = elapsedTime3*1e6;
	
	    			QueryPerformanceCounter(&start4);	
				bellmanFord->bellmanFord_list();
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
			
			show_menu_Path();
			choice_switch_Path();		
	}
}
