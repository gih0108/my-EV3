#include "h_crane.h"


class Crain : public CraneCrane
{
private:
    ev3dev::ultrasonic_sensor ultra_q;
    ev3dev::touch_sensor touch_q;
    ev3dev::motor a;//위아래
    ev3dev::motor b;//상하
    ev3dev::motor c;//집게
    
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
        return 800;//original speed = 100, 800으로 높여봄
    }
    
    /* 사실 상 필요없는 부분
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
    */
    
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
    //void move();
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
        dist++;//1씩 움직임
        if((ultra_q.distance_centimeters() > 0) && (ultra_q.distance_centimeters() < 10))//물체가 감지될 때(센서와의 거리가 줄음)
        {
            count++;//count 1 증가, while문 빠져나옴
        }
        else//물체가 감지되지 않았을 때
        {
            left_right(dist);// 1씩 왼쪽으로 움직임(dist가 양수이므로 오른쪽으로 1만큼 이동)
        }
    }
    
    //"""DOWN"""
    up_down(350);//아래로 350만큼 내려감
    
    //"""GRAB(CLOSE)"""
    open_close(50);//50만큼 닫힘, 물건을 집는 부분
    
    //"""UP"""
    up_down(0);//물건을 가지고, 기준점 0으로 올라감
    
    //"""MOVE TO FINISH"""
    left_right(450);//finish지점이 450이라고 가정할 때 오른쪽으로 끝까지 이동
    
    //"""DOWN"""
    up_down(350);//아래로 350만큼 내려간 후 물건 내려놓음
    
    //"""RELEASE"""
    open_close(0);//집게 초기화, 기준점 0에서 열림
    
    //"""UP"""
    up_down(0);//기준점 0으로 돌아감
    
    //"""SECOND SCAN"""
    //"""stop when an object is detected"""
    
    dist = 0;
    count = 0;
    
    while((abs(b.position()) > 0) && (count == 0))//지금 450으로 가 있는 상황, while문 빠져나올 때 까지는 b위치가 0보다 작을 일은 없음
    {
        dist++;//1만큼 움직임
        if((ultra_q.distance_centimeters() > 0) && (ultra_q.distance_centimeters() < 10))
        {
            count++;
        }
        else
        {
            left_right(450 - dist);//왼쪽으로 물체감지하면서 1만큼 씩 움직임
        }
    }
    
    //"""DOWN"""
    up_down(350);
    
    //"""GRAB(CLOSE)"""
    open_close(50);
    
    //"""UP"""
    up_down(0);
    
    //"""MOVE TO FINISH"""
    left_right(450);
    
    //"""DOWN"""
    up_down(350);
    
    //"""RELEASE"""
    open_close(0);
    
    //"""UP"""
    up_down(0);
    
    //"""THIRD SCAN"""
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
    
    //"""DOWN"""
    up_down(350);
    
    //"""GRAB(CLOSE)"""
    open_close(50);
    
    //"""UP"""
    up_down(0);
    
    //"""MOVE TO FINISH"""
    left_right(450);
    
    //"""DOWN"""
    up_down(350);
    
    //"""RELEASE"""
    open_close(0);//물체를 내려놓고 끝
    //함수로 바꾸면 move();로 대체됨

    a.stop();
    b.stop();
}

void Crain::left_right(int sp)//left_right function
{
    //std::cout << "dd" << std::endl;
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
    while( (abs(c.position()) <= (sp - 20))  || (abs(c.position()) >= (sp + 20)) )// 열린게 0
    {
        c.set_speed_sp(get_speed());
        c.set_position_sp(sp);
        c.run_to_abs_pos();
        c.set_stop_action("hold");
        c.stop();
    }
}
/*
void Crain::move();
{
    up_down(350);
    
    
    open_close(50);
    
   
    up_down(0);
    
   
    left_right(450);
    
   
    up_down(350);
    
    
    open_close(0);
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