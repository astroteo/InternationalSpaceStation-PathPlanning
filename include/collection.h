#include <boost/numeric/odeint.hpp>
#include <stdlib.h>
#include <iostream>


typedef std::vector< double > state_type;

struct StateTimeCollector
{
    std::vector< state_type >& m_states;
    std::vector< double >& m_times;

    StateTimeCollector(std::vector< state_type > &states ,std::vector< double > &times)
    : m_states(states) , m_times(times){ } // also struct allows constructor ??


    void operator()(const state_type &x , double t )
    {
        m_states.push_back(x);
        m_times.push_back(t);
    }

    std::vector<state_type> get_states(void);


};
