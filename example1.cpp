#include "h_crane.h"


class Crain : public CraneCrane
{
private:
    ev3dev::touch_sensor touch_q;
    ev3dev::motor a;
    ev3dev::motor b; 
    ev3dev::motor c;
    //ev3dev::ultrasonic_sensor ultra;
    
public:
    // Hardware Configuration
    Crain():m_speed(0), touch_q(ev3dev::INPUT_2), a(ev3dev::OUTPUT_B), b(ev3dev::OUTPUT_C), c(ev3dev::OUTPUT_A)
    {
        
    }
    
    int m_speed;
    
    bool get_touch_pressed()
    {
        return touch_q.is_pressed();
    }
    /*
    bool get_ultrasonic_pressed()
    {
        return ultra.distance_centimeters();
    }*/
    
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

    virtual int  get_speed()
    {
        return 100;
    }
    
    virtual int a_get_position_sp()
    {
        return 100;
    }
    
    virtual int b_get_position_sp()
    {
        return 350;
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
    
    /*
    virtual float set_ultra_distance_sp(float val)
    {
        return 10.0;
    }*/
    // 집게와 물체사이의 거리가 10.0cm차이가 나면..
    
public:
    void example_code();
};

void Crain::example_code()
{ //This function is for example, you should develop your own logics

    set_down(ev3dev::button::down.pressed());
    set_up(ev3dev::button::up.pressed());
    set_right(ev3dev::button::right.pressed());
    set_left(ev3dev::button::left.pressed());
    set_escape(ev3dev::button::back.pressed());
    set_enter(ev3dev::button::enter.pressed());
    
    
    b.reset();
    
    while(b.position() < b_get_position_sp())
    {
        b.set_speed_sp(get_speed());
        b.set_position_sp(-1*b_get_position_sp());
        b.run_to_abs_pos();
        b.set_stop_action("hold");
        b.stop();
    }
    
        
    a.reset();
        
    while(a.position() != a_get_position_sp())
    {
        a.set_speed_sp(get_speed());
        a.set_position_sp(-1*a_get_position_sp());
        a.run_to_abs_pos();
        a.set_stop_action("hold");
        a.stop();
    }
    
    c.reset();
    
    while(c.position() != c_get_position_sp())
    {
        c.set_speed_sp(get_speed());
        c.set_position_sp(-1*c_get_position_sp());
        c.run_to_abs_pos();
        c.set_stop_action("hold");
        c.stop();
    }
        
        
        //오른쪽으로 가는 거랑, 위로 가는 것, 집게 벌리는 것 아직 안됨.
        
        //b.reset();
        //b.set_speed_sp(get_speed());
        //b.set_position_sp(-50);
        //b.run_to_abs_pos();
        //b.stop();
    
        //a.set_speed_sp(-1*get_speed());
        //a.run_forever();
        
        //b.set_position_sp(130);
        //b.set_command("run-to-abs-pos");
        
        //b.set_stop_action("brake");
        //b.set_command("stop");
        
        //b.run_to_abs_pos();
        
        //reset!!
        
        
        /*
        if(get_up())
        {   
                a.set_speed_sp(-1*get_speed());
                a.run_forever();
        }   
        if(get_down())
        {
                a.set_speed_sp(get_speed());
                a.run_forever();
        }
        if(get_left())
        {
               b.set_speed_sp(-1*get_speed());
               b.run_forever();
        }
        if(get_right())
        {
               b.set_speed_sp(get_speed());
               b.run_forever();
        }
       
       
        if(!(get_up() | get_down() | get_right() | get_left() | get_enter()))
        {
            a.set_speed_sp(0);
            a.run_forever();
            b.set_speed_sp(0);
            b.run_forever();
        }
        */

    a.stop();
    b.stop();
}

int main()
{     
    Crain crain;
    while(true){
        
        /*
        if(crain.get_ultrasonic_pressed()==true)
        {
        }*/
        if(crain.get_touch_pressed()==true){ 
            
        crain.example_code(); //This line is for example, you should erase this ex_code in your 'real code' 
  
        }
    }
}
