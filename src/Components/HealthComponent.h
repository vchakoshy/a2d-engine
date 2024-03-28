#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H

struct HealthComponent {
    int healthPercentage;

    HealthComponent(int healthPercentage = 0){
        this->healthPercentage = healthPercentage;
    }
};

#endif 