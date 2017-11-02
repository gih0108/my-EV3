#include "h_crane.h"


class Crain : public CraneCrane
{
private:
    ev3dev::ultrasonic_sensor ultra_q;
    ev3dev::touch_sensor touch_q;
    ev3dev::motor a;
    ev3dev::motor b; 
    ev3dev::motor c;
    
public:
    // Hardware Configuration
    Crain():m_speed(0), touch_q(ev3dev::INPUT_2), a(ev3dev::OUTPUT_B), b(ev3dev::OUTPUT_C), c(ev3dev::OUTPUT_D), ultra_q(ev3dev::INPUT_3)
    {
        
    }
    
    int m_speed;
    
    bool get_touch_pressed()
    {
        return touch_q.is_pressed();
    }
    
    float get_ultrasonic_distance()
    {
        return ultra_q.distance_centimeters();
    }
    
    virtual bool get_down()
    {
        return m_down; //return true for get_down
    }

    virtual bool get_up()
    {
        return m_up;
    }

    virtual bool get_right()
    {
        return m_right;
    }

    virtual bool get_left()
    {
        return m_left;
    }

    virtual bool get_enter()
    {
        return m_enter;
    }

    virtual bool get_escape()
    {
        return m_escape;
    }

    virtual int get_speed()
    {
        return 800;
    }
    
    virtual int a_get_position_sp()
    {
        return 100;
    }
    
    virtual int b_get_position_sp()
    {
        return 100;
    }
    
    virtual int c_get_position_sp()
    {
        return 50;
    }
    
    virtual void set_down(bool val)
    {
        m_down = val;
    }
    
    virtual void set_up(bool val)
    {
        m_up = val;    
    }
    
    virtual void set_right(bool val)
    {
        m_right = val;   
    }
    virtual void set_left(bool val)
    {
        m_left = val; 
    } 
    
    virtual void set_enter(bool val)
    {
        m_enter = val;    
    }
    
    virtual void set_escape(bool val)
    {
        m_escape = val;    
    }
    
    virtual void set_speed(int val)
    {
        m_speed = val;    
    }
    
public:
    void example_code();
    
    void left_right(int sp);
    void up_down(int sp);
    void open_close(int sp);
};



void Crain::example_code()
{
    
    a.reset();
    b.reset();
    c.reset();
    
    int count = 0;
    int dist = 0;
    
    //"""FIRST SCAN"""
    //"""stop when an object is detected"""
    
    while((abs(b.position()) < 450) && (count == 0))
    {
        dist++;
        if((ultra_q.distance_centimeters() > 0) && (ultra_q.distance_centimeters() < 10))
        {
            count++;
        }
        else
        {
            left_right(dist);
        }
    }
    
    //"""OPEN"""
    open_close(200);
    
    //"""DOWN"""
    up_down(350);
    
    //"""CLOSE"""
    open_close(0);
    
    //"""UP"""
    up_down(0);
    
    //"""MOVE TO FINISH"""
    left_right(450);
    
    //"""DOWN"""
    up_down(350);
    
    //"""OPEN"""
    open_close(200);
    
    //"""UP"""
    up_down(0);
    
    //"""CLOSE"""
    open_close(0);
    
    //"""SECOND SCAN"""
    //"""stop when an object is detected"""
    
    dist = 0;
    count = 0;
    
    while((abs(b.position()) > 0) && (count == 0))
    {
        dist++;
        if((ultra_q.distance_centimeters() > 0) && (ultra_q.distance_centimeters() < 10))
        {
            count++;
        }
        else
        {
            left_right(450 - dist);
        }
    }
    
    //"""OPEN"""
    open_close(200);
    
    //"""DOWN"""
    up_down(350);
    
    //"""GRAB(CLOSE)"""
    open_close(0);
    
    //"""UP"""
    up_down(0);
    
    //"""MOVE TO FINISH"""
    left_right(450);
    
    //"""DOWN"""
    up_down(350);
    
    //"""OPEN"""
    open_close(200);
    
    //"""UP"""
    up_down(0);
    
    //"""GRAB(CLOSE)"""
    open_close(0);
    
    //"""THIRD SCAN"""
    //"""stop when an object is detected"""
    
    dist = 0;
    count =0;
    
    while((abs(b.position()) > 0) && (count == 0))
    {
        dist++;
        if((ultra_q.distance_centimeters() > 0) && (ultra_q.distance_centimeters() < 10))
        {
            count++;
        }
        else
        {
            left_right(450 - dist);
        }
    }
    
    //"""OPEN"""
    open_close(200);
    
    //"""DOWN"""
    up_down(350);
    
    //"""GRAB(CLOSE)"""
    open_close(0);
    
    //"""UP"""
    up_down(0);
    
    //"""MOVE TO FINISH"""
    left_right(450);
    
    //"""DOWN"""
    up_down(350);
    
    //"""OPEN"""
    open_close(200);

    a.stop();
    b.stop();
}

void Crain::left_right(int sp)
{
    b.set_speed_sp(get_speed());
    b.set_position_sp(sp);// - left + right
    b.run_to_abs_pos();
    b.set_stop_action("hold");
    b.stop();
}


void Crain::up_down(int sp)
{
    while( (abs(a.position()) >= (sp + 30)) || (abs(a.position()) <= (sp - 30)) ) //위에가 0
    {
        a.set_speed_sp(get_speed());
        a.set_position_sp(sp);
        a.run_to_abs_pos();
        a.set_stop_action("hold");
        a.stop();
    }
}


void Crain::open_close(int sp)
{
    while( (abs(c.position()) <= (sp - 5))  || (abs(c.position()) >= (sp + 5)) )// 열린게 0
    {
        c.set_speed_sp(get_speed());
        c.set_position_sp(sp);
        c.run_to_abs_pos();
        c.set_stop_action("hold");
        c.stop();
    }
}


int main()
{     
    Crain crain;
    while(true){
        
        
        if(crain.get_touch_pressed()==true){ 
        crain.example_code(); //This line is for example, you should erase this ex_code in your 'real code' 
  
        }
    }
}