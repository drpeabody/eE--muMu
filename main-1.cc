
#include "Pythia8/Pythia.h"
using namespace Pythia8;

int main() {

	Pythia pythia;
	pythia.readString("Beams:eCM = 12."); // Energy in Center of Mass Frame is 1 GeV (Mass of muon ~ 100 MeV)
	// pythia.readString("PromptPhoton:all = on"); // Turn on Electro Weak Processes
	pythia.readString("ContactInteractions:QCffbar2mumubar = on"); // Turn on 2 Fermion -> 2 Fermion Processes
	// pythia.readString("PhaseSpace:pTHatMin = 20."); // Transverse Momentum Min limit
	pythia.readString("Beams:idA = 11"); // Electron id = 11
	pythia.readString("Beams:idB = -11"); // Anti Electron id = -11
	pythia.init();

	// Hist mult("charged multiplicity", 100, -0.5, 799.5);
	// Begin event loop. Generate event. Skip if error. List first one.
	for (int iEvent = 0; iEvent < 1000; ++iEvent) {
		if (!pythia.next()) continue;
		// Find number of all final charged particles and fill histogram.
		int nCharged = 0;
		for (int i = 0; i < pythia.event.size(); ++i)
			if (pythia.event[i].isFinal() && pythia.event[i].isCharged())
				++nCharged;
		// mult.fill( nCharged );
		// End of event loop. Statistics. Histogram. Done.
	}
	pythia.stat();
	// cout << mult;
return 0;
}
