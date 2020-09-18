
#include <iostream>
#include <math.h>

#include "robot.hh"

using std::cout;
using std::endl;

const double goal_x = 20.0;
const double goal_y = 0.0;
bool done = false;

void setTurn(Robot *robot)
{
    double dx = goal_x - robot->pos_x;
    double dy = goal_y - robot->pos_y;

    double target_angle = atan2(dy, dx);
    double turn_angle = target_angle - robot->pos_t;
    double turn = -turn_angle;

    if (turn < -0.5)
    {
        robot->set_turn(-0.5);
        return;
    }
    if (turn > 0.5)
    {
        robot->set_turn(0.5);
        return;
    }
    robot->set_turn(turn);
}

void callback(Robot *robot)
{
    /*
    cout << endl;
    cout << "robot x =" << robot->pos_x << endl;
    cout << "robot y =" << robot->pos_y << endl;
    */
    double dx = goal_x - robot->pos_x;
    double dy = goal_y - robot->pos_y;
    if (abs(dx) < 0.75 && abs(dy) < 0.75)
    {
        cout << "we win!" << endl;
        robot->set_vel(0.0);
        robot->set_turn(0.0);
        robot->done();
        return;
    }

    bool turn = false;

    for (LaserHit hit : robot->hits)
    {
        if (hit.range < 1.57)
        {
            cout << "hit" << endl;
            cout << hit.angle << endl;

            if ((hit.angle < 0.4 && hit.angle > -1.0))
            {
                cout << "turning left" << endl;
                turn = true;
                robot->set_vel(3.0);
                robot->set_turn(-1);
            }
            if (hit.angle > 0.5 && hit.angle < 1.0)
            {
                cout << "turning right" << endl;
                turn = true;
                robot->set_vel(3.0);
                robot->set_turn(1);
            }
        }
    }

    if (turn)
    {
        cout << "turned" << endl;
    }
    else
    {
        cout << "going to goal" << endl;
        robot->set_vel(5.0);
        setTurn(robot);
    }
}

int main(int argc, char *argv[])
{
    cout << "making robot" << endl;
    Robot robot(argc, argv, callback);
    robot.do_stuff();

    return 0;
}
