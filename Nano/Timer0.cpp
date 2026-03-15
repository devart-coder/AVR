#include "Timer0.h"


Nano::Prescaling Nano::Timer0::prescaling = Nano::Prescaling::NoSource;


namespace Nano {
Prescaling Timer0::getPrescaling()
{
    return prescaling;
}

}
