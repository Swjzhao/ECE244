#include <galaxy-explorer/GameAI.hpp>
#include <galaxy-explorer/MyAIData.hpp>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <unordered_set>

using namespace std;



GameAI::GameAI(const GameInfo& game_info, sf::RenderTarget* debug_rt)
{
	this->debug_rt = debug_rt;
	this->game_info = game_info;
	this->asteroid_observer = AsteroidsObserver(this);
	this->my_game_ai = new MyAIData();

	// customState().debug_on = false;
}

GameAI::~GameAI() {
	delete my_game_ai;
}

SuggestedAction GameAI::suggestAction(const ShipState& ship_state) {
	debug_rt->clear(sf::Color::Transparent);

	if (customState().debug_on) {
		if (not asteroidsObserver().asteroids().isEmpty()) {
			const sf::IntRect first_ast_hb = asteroidsObserver().asteroids().front().getCurrentHitbox();
			sf::RectangleShape ast_rect(sf::Vector2f(first_ast_hb.width, first_ast_hb.height));
			ast_rect.setPosition(first_ast_hb.left, first_ast_hb.top);
			ast_rect.setOutlineThickness(33.0f); // if lines are too thin, they won't show up sometimes
			ast_rect.setOutlineColor(sf::Color::Yellow);
			ast_rect.setFillColor(sf::Color::Transparent);
			debug_rt->draw(ast_rect);
		}
	}
       
        if (!asteroidsObserver().asteroids().isEmpty()){
            AsteroidList al = asteroidsObserver().asteroids();
            AsteroidListItem* mostThreatening = nullptr;
            double currentFactor= 1000000000000000;
            sf::IntRect shipRect = ship_state.hitbox;
            
            int health = 0;
            sf::IntRect rect;
            sf::Vector2i vec;
            bool collide =  false;
            double vecMag = 0;
            
            for (AsteroidListItem* it = al.begin(); it != al.end(); it = it->getNext()) {

                health = it->getData().getHealth();
                rect = it->getData().getCurrentHitbox();
                vec = it->getData().getVelocity();
                collide = false;
                vecMag = sqrt(vec.x^2 + vec.y^2);
                
                //test if asteroid collides with ship
                for(int i = 0; i < (shipRect.top + shipRect.left); i+=100){
                    
                    sf::IntRect temp(rect.left + i*vec.x - 2000, 
                            rect.top + i*vec.y - 2000,
                            rect.width+ 2000,
                            rect.height + 2000);
                     if(shipRect.intersects(temp)){
                        collide = true;
                        break;
                    }
                 
                }
                
                double collisionFactor = collide ? 1: 20;
                // sqrt(x^2 + y^2)
                double distance = sqrt(pow((rect.left+rect.width/2 - shipRect.left - shipRect.width/2),2) 
                    + pow((rect.top + rect.height - shipRect.top),2));

             
                //priortizes asteroid based on proximity and if it will collide with ship
                double factor = (distance)*(collisionFactor);
               
                if(factor < currentFactor ){
                    mostThreatening = it;
                    currentFactor = factor;
                }
 
               
            }
            if(mostThreatening == nullptr)
                return SuggestedAction{ SuggestedAction::YawingStop, SuggestedAction::FiringTry };
           
                
            //target asteroid variables
            double tarX = mostThreatening->getData().getCurrentHitbox().left 
                + mostThreatening->getData().getCurrentHitbox().width/2;
            double tarY = mostThreatening->getData().getCurrentHitbox().top 
                + mostThreatening->getData().getCurrentHitbox().height/2;
            double tarW = mostThreatening->getData().getCurrentHitbox().width;
            double tarH = mostThreatening->getData().getCurrentHitbox().top;
            double tarVelX = mostThreatening->getData().getVelocity().x;
            double tarVelY = mostThreatening->getData().getVelocity().y;
            
            //ship variables
            double shipX = shipRect.left + shipRect.width/2;
            double shipY = shipRect.top + shipRect.height/2;
            double phaserSpeed = game_info.phaser_pulse_speed;
            
            //quadratic formula to find time it takes for bullet to hit asteroid
            //ax^2 + bx + c = 0
            double a = pow(tarVelX,2) + pow(tarVelY,2) - pow(phaserSpeed,2);
            double b = 2 * (tarVelX * (tarX-shipX)) + tarVelY * (tarY - shipY);
            double c = pow ((tarX - shipX),2) + pow((tarY - shipY),2);
           
            //find 2 times and get the smallest
            //double d = sqrt(pow(b,2) - 4*a*c);
            double t1 = (-b + sqrt(pow(b,2) - 4*a*c)) / (2*a);
            double t2 = (-b - sqrt(pow(b,2) - 4*a*c)) / (2*a);
            int t = 0;
            t = min(t1,t2);
            if(t<0) t = max(t1,t2);
            //time cant be negative
            if (t<0) t = 0;
            
            //coordinates of where the collision with bullet will occur
            double targX = t*tarVelX + tarX;
            double targY = t*tarVelY + tarY;
           
          
            double angle = 90000;
            //if(shipX - targX == 0), will it form 1/0 = infinite
            if(shipX - targX == 0)
                angle = customState().angle;
            else
                angle = atan(abs(shipY - targY)/abs(shipX - targX));
            //convert to millidegrees
            angle = angle*180/3.1415;
            angle = angle*1000;
            //minor adjustment
            angle += (90000-angle)*0.2;
            
            //retain original value
            if(angle == 0)
                angle = customState().angle;
          
            customState().angle = angle;
            //angle was in respect to x axis, now convert to y to match ship angle
            angle = 90000-angle;
            
            if(ship_state.fire_phaser_requested){
                customState().phasercounter +=1;
            }
           // double func = (2 * sqrt(pow((shipY-targY),2) + pow((shipX-targX),2))-pow(tarW,2))/(2*abs(shipX - targX)*(shipY - targY)); 
            
            double limitAngle;
            //degree of error allowed
            switch(mostThreatening->getData().getHealth()){
                case 1: limitAngle = 500; break;
                case 2: limitAngle = 500; break;
                case 3: limitAngle = 500; break;
                default: limitAngle = 500; break;
            }
            
            //the ship just needs to fire X amount of time before it can assume
            //it has destroyed the asteroid
            if(abs(90000-angle)-abs(ship_state.millidegree_rotation)  <= limitAngle)
                if(targX < shipX && ship_state.millidegree_rotation < 0 ||
                        targX > shipX && ship_state.millidegree_rotation >=0 )
                    customState().phasercounter = customState().phasercounter;
                else
                    customState().phasercounter = 0;
            else
                customState().phasercounter = 0;
           
            int max = 0;
            switch(mostThreatening->getData().getHealth()){
                case 1: max = 1; break;
                case 2: max = 3; break;
                case 3: max = 5; break;
                default: max = 5; break;
            }
           
            
            if(customState().phasercounter > max){
                if(abs(angle-abs(ship_state.millidegree_rotation)) >= limitAngle){
                    customState().phasercounter = 0;
                }else{
                    customState().phasercounter = 0;
                    asteroidsObserver().onAsteroidDestroy(mostThreatening->getData());
                }
            }
            
            //rotates the ship toward the angle needed
            if(targX < shipX){
                if(ship_state.millidegree_rotation > 0)
                    return SuggestedAction{ SuggestedAction::YawingAntiClockwise, SuggestedAction::FiringTry };
                else if(angle < abs(ship_state.millidegree_rotation)) {
                    return SuggestedAction{ SuggestedAction::YawingClockwise, SuggestedAction::FiringTry};
                }else{
                    return SuggestedAction{ SuggestedAction::YawingAntiClockwise, SuggestedAction::FiringTry };
                }
            }else{
                
                if(ship_state.millidegree_rotation < 0)
                    return SuggestedAction{ SuggestedAction::YawingClockwise, SuggestedAction::FiringTry };
                else if(angle  <  abs(ship_state.millidegree_rotation)) {
                    return SuggestedAction{ SuggestedAction::YawingAntiClockwise, SuggestedAction::FiringTry };
                }else{
                    return SuggestedAction{ SuggestedAction::YawingClockwise, SuggestedAction::FiringTry };
                }
            }
    
            
           
 
//                
            
            
        }
        //return SimpleActions::NO_CHANGE;
	//return SimpleActions::START_YAWING_CW;
	//return SimpleActions::START_YAWING_ACW;
	//return SimpleActions::STOP_YAWING_AND_FIRE;
        
        //rotates left and right if no asteroid present
        if(customState().turnLeft){
            if(ship_state.millidegree_rotation >  35000){
                customState().turnLeft = 0;
                return SuggestedAction{ SuggestedAction::YawingAntiClockwise, SuggestedAction::FiringTry };
            }else{
                return SuggestedAction{ SuggestedAction::YawingClockwise, SuggestedAction::FiringTry };
            }
        }else{    
            if(ship_state.millidegree_rotation <  -35000){
                customState().turnLeft = 1;
                return SuggestedAction{ SuggestedAction::YawingClockwise, SuggestedAction::FiringTry };
            }else{
                return SuggestedAction{ SuggestedAction::YawingAntiClockwise, SuggestedAction::FiringTry };
            }
        }
        return SuggestedAction{ SuggestedAction::YawingStop, SuggestedAction::FiringTry };
}
