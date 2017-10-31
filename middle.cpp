#include "h_crane.h"


class Crain : public CraneCrane
{
private:
    ev3dev::touch_sensor touch_q;
    ev3dev::motor a;//위 아래
    ev3dev::motor b;//좌 우
    ev3dev::motor c;//집게
    ev3dev::ultrasonic_sensor ultra_q;
    
public:
    // Hardware Configuration
    Crain():m_speed(0), touch_q(ev3dev::INPUT_2), a(ev3dev::OUTPUT_B), b(ev3dev::OUTPUT_C), c(ev3dev::OUTPUT_A), ultra_q(ev3dev::INPUT_3)
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
        return 10;
    }
    
    virtual int c_get_position_sp()
    {
        return 30;
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
    //void crain();
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
    a.reset();
    
    int count = 0;
    int dist = 0;
    
    while((abs(b.position()) < 350) && (count == 0))
    {
        dist++;
        if((ultra_q.distance_centimeters() > 0) && (ultra_q.distance_centimeters() < 10))
        {
            count++;
        }
        else
        {
            b.set_speed_sp(get_speed());
            b.set_position_sp(-1*dist);
            b.run_to_abs_pos();
            b.set_stop_action("hold");
            b.stop();
        }
    }
    
    //std::cout<<"a"<<std::endl;
    
    while((abs(a.position()) >= abs(130)) || (abs(a.position()) <= abs(70)))
    {
        //std::cout<<"b"<<std::endl;
        a.set_speed_sp(get_speed());
        a.set_position_sp(-1*a_get_position_sp());
        a.run_to_abs_pos();
        a.set_stop_action("hold");
        a.stop();
    }
        
    c.reset();
    
    while((abs(c.position()) >= abs(20)) || (abs(c.position()) <= abs(40)))
    {
        c.set_speed_sp(get_speed());
        c.set_position_sp(-1*c_get_position_sp());
        c.run_to_abs_pos();
        c.set_stop_action("hold");
        c.stop();
        //std::cout<<"c"<<std::endl;
    }
    
    
    
    /*
    while((abs(c.position()) >= abs(20)) || (abs(c.position()) <= abs(40)))
    {
        c.set_speed_sp(get_speed());
        c.set_position_sp(-1*c_get_position_sp());
        c.run_to_abs_pos();
        c.set_stop_action("hold");
        c.stop();
    }*/
    
    
    /* fourth
    b.reset();
    a.reset();
    
    int count = 0;
    int dist = 0;
    
    while((abs(b.position()) < 350) && (count == 0))
    {
        dist++;
        
        if((ultra_q.distance_centimeters() > 0) && (ultra_q.distance_centimeters() < 10))
        {
            
            a.set_speed_sp(get_speed());
            a.set_position_sp(-1*a_get_position_sp());
            a.run_to_abs_pos();
            a.set_stop_action("hold");
            a.stop();
            
            count++;
        }
        else
        {
            b.set_speed_sp(get_speed());
            b.set_position_sp(-1*dist);
            b.run_to_abs_pos();
            b.set_stop_action("hold");
            b.stop();
        }
    }*/
    
    /* third
    while (1)
    {
        float a = 0 ;
        a = ultra_q.distance_centimeters();
        std::cout << a << std::endl;
    }*/
    
    /*second
    a.reset();
    b.reset();
    while(abs(b.position()) < 350)
    {
        while(abs(a.position()) != abs(a_get_position_sp()))
        {
            while(abs(b.position()) != abs(b_get_position_sp()))
            {
                if(5 < ultra_q.distance_centimeters() < 10)
                {   
                    
                    a.set_speed_sp(get_speed());
                    a.set_position_sp(-1*a_get_position_sp());
                    a.run_to_abs_pos();
                    a.set_stop_action("hold");
                    a.stop();
                    //std::cout << "a" << std::endl;
                }
                
                b.set_speed_sp(get_speed());
                b.set_position_sp(-1*b_get_position_sp());
                b.run_to_abs_pos();
                b.set_stop_action("hold");
                b.stop();
                //std::cout << "b" << std::endl;
            }
            
        }
    }*/
    
    /* first
    b.reset();
    while(abs(b.position()) != abs(b_get_position_sp()))
    {
        b.set_speed_sp(get_speed());
        b.set_position_sp(-1*b_get_position_sp());
        b.run_to_abs_pos();
        b.set_stop_action("hold");
        b.stop();
    }
    
        
    a.reset();
    while(abs(a.position()) != abs(a_get_position_sp()))
    {
        a.set_speed_sp(get_speed());
        a.set_position_sp(-1*a_get_position_sp());
        a.run_to_abs_pos();
        a.set_stop_action("hold");
        a.stop();
    }
    
    c.reset();
    while(abs(c.position()) != abs(c_get_position_sp()))
    {
        c.set_speed_sp(get_speed());
        c.set_position_sp(-1*c_get_position_sp());
        c.run_to_abs_pos();
        c.set_stop_action("hold");
        c.stop();
    } */

    a.stop();
    b.stop();
}


/*
void Crain::cali(){
    
}*/
int main()
{     
    Crain crain;
    while(true){
        
        if(crain.get_touch_pressed()==true){ 
            
        crain.example_code(); //This line is for example, you should erase this ex_code in your 'real code' 
  
        }
    }
}
