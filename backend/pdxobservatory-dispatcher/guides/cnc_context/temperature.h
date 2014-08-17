/* 
 * File:   temperature.h
 * Author: Basem Elazzabi
 *
 */

#ifndef TEMPERATURE_H
#define	TEMPERATURE_H

#include <iostream>
#include <cnc/cnc.h>
#include <cnc/debug.h>
#include "../types.h"

struct temperature_context;


template <>
struct cnc_hash< TempTag >
{
    size_t operator()( const TempTag & t ) const { return t.task_id; }
};

template<>
struct cnc_equal< TempTag >
{
    bool operator()( const TempTag &a, const TempTag &b) const { return a == b; }
};

inline std::ostream & cnc_format( std::ostream& os, const TempTag & t )
{
    os << t;
    return os;
}



// The step classes

struct temperature_step
{
    int execute( const TempTag & t, temperature_context & c ) const;
};

struct airport_temp_step
{
    int execute( const TempTag & t, temperature_context & c ) const;
};

struct deq_temp_step
{
    int execute( const TempTag & t, temperature_context & c ) const;
};

struct weather_ug_temp_step
{
    int execute( const TempTag & t, temperature_context & c ) const;
};

// The context class
struct temperature_context : public CnC::context< temperature_context >
{
    // step collections
    CnC::step_collection< temperature_step > temperature_steps;
    CnC::step_collection< airport_temp_step > airport_steps;
    CnC::step_collection< deq_temp_step > deq_steps;
    CnC::step_collection< weather_ug_temp_step > weather_ug_steps;
    
    // Item collections
    CnC::item_collection< TempTag, TempType > temp_temperature;
    CnC::item_collection< TempTag, TempType > temp_airport;
    CnC::item_collection< TempTag, TempType > temp_deq;
    CnC::item_collection< TempTag, TempType > temp_weather_ug;
    
    // Tag collections
    CnC::tag_collection< TempTag > temperature_tags;

    // The context class constructor
    temperature_context()
        : CnC::context< temperature_context >(),
          // Initialize each step collection
          temperature_steps( *this ),
          airport_steps( *this ),
          deq_steps( *this ),
          weather_ug_steps( *this ),
          
          // Initialize each item collection
          temp_temperature( *this ),
          temp_airport( *this ),
          temp_deq( *this ),
          temp_weather_ug( *this ),
          
          // Initialize each tag collection
          temperature_tags( *this )
    {
        // Prescriptive relations
        temperature_tags.prescribes( airport_steps, *this );
        temperature_tags.prescribes( deq_steps, *this );
        temperature_tags.prescribes( weather_ug_steps, *this );
        temperature_tags.prescribes( temperature_steps, *this );
        
        // Producer relations
        airport_steps.produces( temp_airport );
        deq_steps.produces( temp_deq );
        weather_ug_steps.produces( temp_weather_ug );
        temperature_steps.produces( temp_temperature );
        
        // Consumer relations
        //temperature_steps.consumes( temp_airport );
        //temperature_steps.consumes( temp_deq );
        //temperature_steps.consumes( temp_weather_ug );
    }
};

#endif	/* TEMPERATURE_H */

