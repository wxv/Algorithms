 #include <iostream>
 #include "mersenne_twister.h"

 int main()
 {
     initialize_generator(time(NULL));
     for(int i=0; i<20; i++)
     {
         std::cout << extract_number() << '\n';
     }

     return 0;
 }
