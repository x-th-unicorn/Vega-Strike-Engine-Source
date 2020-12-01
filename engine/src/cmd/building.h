#ifndef __BUILDING_H
#define __BUILDING_H

#include "unit.h"
#include "unit_generic.h"

class Terrain;
class ContinuousTerrain;
class Flightgroup;

class Building : public GameUnit
{
    // Fields
protected:
    union Buildingparent
    {
        Terrain *terrain;
        ContinuousTerrain *plane;
    }
    parent;
    bool continuous;
    bool vehicle;

    // Constructors
public:
    Building( ContinuousTerrain *parent,
                     bool vehicle,
                     const char *filename,
                     bool SubUnit,
                     int faction,
                     const std::string &unitModifications = std::string( "" ),
                     Flightgroup *fg = NULL );

    Building( Terrain *parent,
              bool vehicle,
              const char *filename,
              bool SubUnit,
              int faction,
              const std::string &unitModifications = std::string( "" ),
              Flightgroup *fg = NULL );

public:

    enum _UnitType isUnit() const
    {
        return _UnitType::building;
    }

    virtual void UpdatePhysics2( const Transformation &trans,
                                 const Transformation &old_physical_state,
                                 const Vector &accel,
                                 float difficulty,
                                 const Matrix &transmat,
                                 const Vector &CumulativeVelocity,
                                 bool ResolveLast,
                                 UnitCollection *uc = NULL );


    bool ownz( void *parent )
    {
        return this->parent.terrain == (Terrain*) parent;
    }

protected:
/// default constructor forbidden
    Building();
/// copy constructor forbidden
    Building( const Building& );
/// assignment operator forbidden
    Building& operator=( const Building& );
};





#endif

