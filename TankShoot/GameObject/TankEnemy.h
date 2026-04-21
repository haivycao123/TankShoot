#ifndef TankEnemy_h
#define TankEnemy_h

class TankEnemy : public Enemy {
public:
    TankEnemy();
    ~TankEnemy() = default;
    void move(float deltaTime) override; //Di thang
    std::vector<Bullet*> shoot() override;
    std::string getType();
};

#endif