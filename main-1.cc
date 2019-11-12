
#include "Pythia8/Pythia.h"
#include "stdio.h"
#include "stdlib.h"
using namespace Pythia8;

int main(int argc, char *argv[]) {

    if(argc < 2){
        cout << "Center of Mass Energy not specified.";
        return 1;
    }
    else if(argc < 3){
        cout << "Output file not Specified.";
        return 1;
    }
    
    FILE *output_file = fopen(argv[2], "w");   
    if(output_file == NULL){
        printf("Error opening output file!");
        return 1;
    }
    
    char argument[50] = "Beams:eCM = ";
    strcat(argument, argv[1]); // Concat the command line argument
    strcat(argument, "."); // Concat a full stop

    // argument = "Beams:eCM = 500." for example

	Pythia pythia;
	pythia.readString(argument); // (Mass of muon ~ 100 MeV)
	pythia.readString("Top:qqbar2ttbar = on"); // Turn on 2 Fermion -> 2 Fermion Processes
	pythia.readString("Beams:idA = 2212"); // Proton id = 2212
	pythia.readString("Beams:idB = 2212"); // Proton id = 2212
    pythia.readString("PartonLevel:all = off");
    char result[100];
    srand(time(0));
    sprintf(result, "Random:seed = %d", rand() % (900000 + 1));
    pythia.readString(result);
    
	pythia.init();

	for (int iEvent = 0; iEvent < 10000; ++iEvent) {
		if (!pythia.next()) continue;
        
        #define Ev pythia.process
        #define id_t 5
        #define id_t_bar 6
        #define top 6
        #define top_bar -6
        #define id_u 3
        #define id_u_bar 4
        #define u 2
        
        if((abs(Ev[id_t].id()) != top || abs(Ev[id_t_bar].id()) != top) &&
         (abs(Ev[id_u].id()) != u || abs(Ev[id_u_bar].id()) != u) ){
            // Skip anomalous Events
            continue;
        }

        int top_index = (Ev[id_t].id() == top)? id_t: id_t_bar;
        int top_bar_index = (Ev[id_t].id() == top)? id_t_bar: id_t;
        int u_index = (Ev[id_u].id() == u)? id_u: id_u_bar;

        double beta = -(Ev[top_index].pz() + Ev[top_bar_index].pz()) / (Ev[top_index].e() + Ev[top_bar_index].e());
        double gamma = sqrt(1.0/(1.0 - beta * beta));

        double pz_t_new = gamma * (Ev[top_index].pz() + beta * Ev[top_index].e());
        double pz_u_new = gamma * (Ev[u_index].pz() + beta * Ev[u_index].e());

        double p_t = sqrt(
            pow(Ev[top_index].px(), 2) + 
            pow(Ev[top_index].py(), 2) + 
            pow(pz_t_new, 2));
        double p_u = sqrt(
            pow(Ev[u_index].px(), 2) + 
            pow(Ev[u_index].py(), 2) + 
            pow(pz_u_new, 2));

        double angle = Ev[top_index].px() * Ev[u_index].px() + 
                Ev[top_index].py() * Ev[u_index].py() + 
                pz_t_new           * pz_u_new;
        angle = angle / ( p_t * p_u );

        fprintf(output_file, "%f\n", angle);
	}

    fclose(output_file);
    
    return 0;
}
