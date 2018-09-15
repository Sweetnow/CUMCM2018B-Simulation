#ifndef MATERIAL_H
#define MATERIAL_H

class material
{
public:
    enum type { NONE, ONE, TWO }; //the number of processes needed
    enum state { RAW, HALF, RIPE, BAD };
    material();
    explicit material(bool is_one);
    ~material();
    state get_state() const;
    void set_state(state s);
    bool is_one() const;
    bool is_init() const;
    int get_id() const;

private:
    type _type = NONE;  //just as null object
    state _state = RAW;
    int _material_id = 0;   //if 0, be not initialized correctly
    static int _next_id;
};


#endif // !MATERIAL_H
