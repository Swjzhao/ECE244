/*
 * This file was developed for the Fall 2018 instance of ECE244 at the University of Toronto.
 * Creator: Matthew J. P. Walker
 */


#include <galaxy-explorer/AsteroidsObserver.hpp>
#include <iostream>
#include <set>

void AsteroidsObserver::onAsteroidInRange(Asteroid asteroid) {
    asteroid_list.pushFront(asteroid);
}

void AsteroidsObserver::onAsteroidUpdate(Asteroid asteroid) {
    
    for (AsteroidListItem* it = asteroid_list.begin(); it != asteroid_list.end(); it = it->getNext()) {
        if(it->getData().getID() == asteroid.getID()){
            it->getData() = asteroid;
        }
    }
    
}

void AsteroidsObserver::onAsteroidOutOfRange(Asteroid asteroid) {
    AsteroidListItem* before = asteroid_list.beforeBegin();
    for (AsteroidListItem* it = asteroid_list.begin(); it != asteroid_list.end(); it = it->getNext()) {
        if(it->getData().getID() == asteroid.getID()){
            asteroid_list.eraseAfter(before);
            return;
        }
        before = it;
    }
}   

void AsteroidsObserver::onAsteroidDestroy(Asteroid asteroid) {
    AsteroidListItem* before = asteroid_list.beforeBegin();
      for (AsteroidListItem* it = asteroid_list.begin(); it != asteroid_list.end(); it = it->getNext()) {
          if(it->getData().getID() == asteroid.getID()){
              asteroid_list.eraseAfter(before);
              //std::cout<<"destoryed"<<std::endl;
              return;
          }
          before = it;
      }
    
}

