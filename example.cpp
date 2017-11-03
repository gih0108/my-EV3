#include "h_crane.h"


class Crain : public CraneCrane
{
private:
    ev3dev::ultrasonic_sensor ultra_q;
    ev3dev::touch_sensor touch_q1;
    ev3dev::touch_sensor touch_q2;
    ev3dev::motor a;
    ev3dev::motor b; 
    ev3dev::motor c;
    
public:
    // Hardware Configuration
    Crain():m_speed(0), touch_q1(ev3dev::INPUT_2), touch_q2(ev3dev::INPUT_4),a(ev3dev::OUTPUT_B), b(ev3dev::OUTPUT_C), c(ev3dev::OUTPUT_D), ultra_q(ev3dev::INPUT_1)
    {
        
    }
    
    int m_speed;
    
    bool get_touch_pressed_q1()
    {
        return touch_q1.is_pressed();
    }
    
    bool get_touch_pressed_q2()
    {
        return touch_q2.is_pressed();
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
    void BlackHand_code();
    void left_right(int sp);
    void left_right_FINISH(int sp);
    void up_down(int sp);
    void open_close(int sp);
};



void Crain::BlackHand_code()
{
    if(get_touch_pressed_q2()==true)
    {
        b.reset();
        b.set_position_sp(-620);
        b.run_to_abs_pos();
        a.reset();
        a.set_position_sp(400);
        a.run_to_abs_pos();
        
    }

    a.reset();
    b.reset();
    c.reset();
    
    int count = 0;
    int dist = 5;
    
    //"""FIRST SCAN"""
    //"""stop when an object is detected"""
    
    while((abs(b.position()) < 620) && (count == 0))
    {
        if((ultra_q.distance_centimeters() < 10))
        {
            count++;
        }
        else
        {
            left_right(dist);
        }
    }
    
    sleep(0.5);
    
    //"""OPEN"""
    open_close(55);
    
    sleep(0.5);
    
    //"""DOWN"""
    up_down(400);
    
    sleep(2);
    
    //"""CLOSE"""
    open_close(150);
    
    sleep(0.5);
    
    //"""UP"""
    up_down(0);
    
    //"""MOVE TO FINISH"""
    left_right_FINISH(620);
    
    sleep(1);
    
    //"""DOWN"""
    up_down(400);
    
    sleep(0.5);
    
    //"""OPEN"""
    open_close(55);
    
    sleep(0.5);
    
    //"""UP"""
    up_down(0);
    
    
    //"""CLOSE"""
    open_close(0);
    
    sleep(1);
    
    //"""SECOND SCAN"""
    //"""stop when an object is detected"""
    
    dist = 0;
    count = 0;
    dist = 5;
    
    while((abs(b.position()) > 0) && (count == 0))
    {
        if((ultra_q.distance_centimeters() < 10))
        {
            count++;
        }
        else
        {
            left_right((-1) * dist);
        }
    }
    
    sleep(0.5);
    
    //"""OPEN"""
    open_close(55);
    
    sleep(0.5);
    
    //"""DOWN"""
    up_down(400);
    
    sleep(2);
    
    //"""GRAB(CLOSE)"""
    open_close(150);
    
    sleep(0.5);
    
    //"""UP"""
    up_down(0);
    
    //"""MOVE TO FINISH"""
    left_right_FINISH(620);
    
    sleep(1);
    
    //"""DOWN"""
    up_down(400);
    
    sleep(0.5);
    
    //"""OPEN"""
    open_close(55);
    
    sleep(0.5);
    
    //"""UP"""
    up_down(0);
    
    //"""GRAB(CLOSE)"""
    open_close(0);
    
    sleep(1);
    
    //"""THIRD SCAN"""
    //"""stop when an object is detected"""
    
    dist = 0;
    count =0;
    dist = 5;
    while((abs(b.position()) > 0) && (count == 0))
    {
        if((ultra_q.distance_centimeters() < 10))
        {
            count++;
        }
        else
        {
            left_right((-1) * dist);
        }
    }
    
    //"""OPEN"""
    open_close(55);
    
    //"""DOWN"""
    up_down(400);
    
    sleep(2);
    
    //"""GRAB(CLOSE)"""
    open_close(150);
    
    sleep(1);
    
    //"""UP"""
    up_down(0);
    
    //"""MOVE TO FINISH"""
    left_right_FINISH(620);
    
    sleep(1);
    
    //"""DOWN"""
    up_down(400);
    
    //"""OPEN"""
    //open_close(55);

    a.stop();
    b.stop();

}


void Crain::left_right(int sp)
{
    b.set_speed_sp(get_speed());
    b.set_position_sp(sp);// - left + right
    b.run_to_rel_pos();
    b.set_stop_action("hold");
    b.stop();
}

void Crain::left_right_FINISH(int sp)
{
    b.set_speed_sp(10);
    b.set_position_sp(sp);// - left + right
    b.run_to_abs_pos();
    b.set_stop_action("hold");
    b.stop();
}


void Crain::up_down(int sp)
{
    while( (abs(a.position()) >= (sp + 30)) || (abs(a.position()) <= (sp - 30)) ) //위에가 0
    {
        a.set_speed_sp(10);
        a.set_position_sp(sp);
        a.run_to_abs_pos();
        a.set_stop_action("hold");
        a.stop();
    }
}


void Crain::open_close(int sp)
{
    while( (abs(c.position()) <= (sp - 5))  || (abs(c.position()) >= (sp + 5)) )// 닫힌게 0
    {
        c.set_speed_sp(get_speed());
        c.set_position_sp(-sp);
        c.run_to_abs_pos();
        c.set_stop_action("hold");
        c.stop();
    }
}


int main()
{     
    Crain crain;
    while(true){
        
        
        if(crain.get_touch_pressed_q1()==true)
        {
            crain.BlackHand_code(); //This line is for example, you should erase this ex_code in your 'real code' 
  
        }
       
    }
}