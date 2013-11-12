#include <iostream>
#include <bitset>

typedef std::bitset<64> Block ;
typedef std::bitset<56> Key ;
typedef std::bitset<48> Code ;

typedef std::bitset<32> HBlock ;
typedef std::bitset<28> HKey ;
typedef std::bitset<24> HCode ;

typedef enum { e , d } Method ;

int ip(const Block & block , HBlock & left , HBlock & right) ;
int des_turn(HBlock & left , HBlock & right , const Code & subkey) ;
int exchange(HBlock & left , HBlock & right) ;
int rip(const HBlock & left , const HBlock & right , Block & block) ;
Code getkey(const unsigned int n , const Block & bkey) ;
int des(Block & block , Block & bkey , const Method method) ;
