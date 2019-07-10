#include <graphenelib/graphene.hpp>
using namespace graphene;

class cardgame : public contract {

  public:
    cardgame(uint64_t id)
        : contract(id)
	{
    }
};