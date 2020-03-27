#ifndef ParticleMass_h
#define ParticleMass_h

#include "AnalysisSteering.h"
#include <vector>

class Event;
class MassMean;

class ParticleMass: public AnalysisSteering {

 public:

  ParticleMass();
  virtual ~ParticleMass();

  // function to be called at execution start
  virtual void beginJob();
  // function to be called at execution end
  virtual void   endJob();
  // function to be called for each event
  virtual void process( const Event& ev );


 private:

  // dummy copy constructor and assignment to prevent unadvertent copy
  ParticleMass           ( const ParticleMass& x );
  ParticleMass& operator=( const ParticleMass& x );

  // set of _____________ for different total energies
  std::vector<MassMean*> pList;

};

#endif

