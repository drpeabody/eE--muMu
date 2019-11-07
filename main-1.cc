
#include "Pythia8/Pythia.h"
#include "stdio.h"
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
	pythia.readString("ContactInteractions:QCffbar2mumubar = on"); // Turn on 2 Fermion -> 2 Fermion Processes
	pythia.readString("Beams:idA = 11"); // Electron id = 11
	pythia.readString("Beams:idB = -11"); // Anti Electron id = -11
    pythia.readString("PartonLevel:all = off");
    
	pythia.init();

	for (int iEvent = 0; iEvent < 5000; ++iEvent) {
		if (!pythia.next()) continue;
        
        #define Ev pythia.process
        #define mu 13
        #define mubar -13
        #define e 11
        #define ebar -11
        #define id_e 3
        #define id_mu 5
        
        if(Ev[id_e].id() != e || Ev[id_mu].id() != mu) 
            continue; // Skip anomalous Events

        double angle = 1.0/900;

        fprintf(output_file, "%f\n", angle);
        
	}

    fclose(output_file);
    
    return 0;
}
