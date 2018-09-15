#ifndef MATERIAL_H
#define MATERIAL_H

class material
{
public:
    enum type { NONE, ONE, TWO }; //the number of processes needed
    enum state { RAW, HALF, RIPE, BAD };
    material();
    material(bool is_one);
    ~material();
    state get_state();
    void set_state(state s);
    bool is_one();
    bool is_init();
private:
    type _type = NONE;  //just as null object
    state _state = RAW;
};


#endif // !MATERIAL_H
