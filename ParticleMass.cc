#include "ParticleMass.h"

#include "Event.h"
#include "MassMean.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;

ParticleMass::ParticleMass() {
}


ParticleMass::~ParticleMass() {
}


// function to be called at execution start
void ParticleMass::beginJob() {

  // create energy distributions for different total energy ranges
  pList.reserve( 10 );
  pList.push_back( new MassMean( 3000.0, 5000.0 ) );
  pList.push_back( new MassMean( 6000.0, 6499.0 ) );
  pList.push_back( new MassMean( 6500.0, 6799.0 ) );
  pList.push_back( new MassMean( 6800.0, 7200.0 ) );
  return;

}


// function to be called at execution end
void ParticleMass::endJob() {

  // number of points
  int nBinD = Event::minSize();
  int iBinD;

  // loop over elements
  int n = pList.size();
  int i;
  for ( i = 0; i < n; ++i ) {
    // get Bragg curve informations
    MassMean* bMean = pList[i];
    // compute results
    bMean->compute();
    // get mean and rms energies
    const vector<double>& mean = bMean->eMean();
    const vector<double>& rms  = bMean->eRMS ();
    // loop over points
    for ( iBinD = 0; iBinD < nBinD; ++iBinD ) {
      // print results
      cout << iBinD << " " << mean[iBinD] << " " << rms[iBinD] << endl;
    }
    // print number of events
    cout << bMean->nEvents() << endl;
  }

  return;

}


// function to be called for each event
void ParticleMass::process( const Event& ev ) {
  // loop over energy distributions and pass event to each of them
  unsigned int n = pList.size();
  unsigned int i;
  for ( i = 0; i < n; ++i ) pList[i]->add( ev );
  return;
}

