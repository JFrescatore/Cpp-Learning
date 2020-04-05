#include "KnightTour.h"

using namespace std;

int main() {
  KnightTour knightTour(1, 1);
  knightTour.wipeData();
  for(int i = 1; i <= 500; i++){
    KnightTour knightTour(i, i);
  }
}

