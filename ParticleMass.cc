#include "ParticleMass.h"

#include "Event.h"
#include "MassMean.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

float massMinK0 = 0.490;
float massMaxK0 = 0.505;
float massMinL0 = 1.114;
float massMaxL0 = 1.118;

ParticleMass::ParticleMass() {
}


ParticleMass::~ParticleMass() {
}


// function to be called at execution start
void ParticleMass::beginJob() {

  // create mass distributions for different particles
  pList.reserve( 10 );
  pList.push_back( new MassMean( massMinK0, massMaxK0 ) );
  pList.push_back( new MassMean( massMinL0, massMaxL0 ) );
  return;

}


// function to be called at execution end
void ParticleMass::endJob() {
  // loop over elements
  int n = pList.size();
  int i;
  for ( i = 0; i < n; ++i ) {
    // get mass informations
    MassMean* pMean = pList[ i ];
    // compute results
    pMean->compute();
    // get mean and rms mass
    double mean = pMean->mMeanM();
    double rms  = pMean->mRMS  ();

    // print results
    std::cout << pMean->nEvents() << ' ' 
              << mean             << ' ' 
              << rms              << std::endl;
  
  }

  return;

}


// function to be called for each event
void ParticleMass::process( const Event& ev ) {
  // loop over mass distributions and pass event to each of them
  unsigned int n = pList.size();
  unsigned int i;
  for ( i = 0; i < n; ++i ) 
    pList[ i ]->add( ev );

  return;
}